#include <eigen3/Eigen/Dense>
#include <leopard.h>
#include <vector>
#include <iostream>
#include <tuple>

// Takes a dense symmetric Eigen::Matrix and outputs sparse triplet format, sorted in col-major order, only including the lower triangular part.
std::tuple<std::vector<uintptr_t>, std::vector<uintptr_t>, std::vector<double>> eigen_dense_to_sparse(Eigen::MatrixXd &dense)
{
  std::vector<uintptr_t> is, js;
  std::vector<double> vs;
  for (int j = 0; j < dense.cols(); j++)
  {
    for (int i = j; i < dense.rows(); i++)
    {
      double v = dense(i, j);
      if (std::abs(v) > 0.0)
      {
        is.push_back(i);
        js.push_back(j);
        vs.push_back(v);
      }
    }
  }

  return std::make_tuple(is, js, vs);
}

int main()
{
  // Our system is of size 4x4
  uintptr_t n = 4;

  // We create our matrix
  Eigen::MatrixXd dense(n, n);
  dense << 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 5, 1, 1, 1, 1, 6;

  // We define the rigth hand side we want to solve for
  Eigen::VectorXd rhs(n);
  rhs << 1, 2, 3, 4;

  printf("Input matrix is:\n");
  std::cout << dense << std::endl
            << std::endl;

  printf("rhs is:\n");
  std::cout << rhs.transpose() << std::endl
            << std::endl;

  // Using the utility function, we create a lower triangular, including diagonal, column major ordered set of indices and values from the dense matrix.
  // In a practical implementation, with large sparse matrices, your application should directly generate this data as input.
  auto [is, js, vs] = eigen_dense_to_sparse(dense);

  // First we create the index-set data structure, Ij. It stores the indices of the sparse matrix.
  IjResult ij = leopard_ij_new_i_j_array_uintptr(n, is.size(), is.data(), js.data(), true);
  if ((int32_t)ij.code)
  {
    std::cout << leopard_explain_return_code(ij.code) << std::endl;
    exit(1);
  }

  // Given these indices, we can compute a matrix ordering. The goal of an ordering is to minimize the amount of fill-in in the factorization.
  // Here we are using an AMD ordering, but any ordering you want can bu specified using leopard_ordering_new_from_array().
  OrderingResult ordering = leopard_ordering_new_amd_default(ij.object);
  if ((int32_t)ordering.code)
  {
    std::cout << leopard_explain_return_code(ordering.code) << std::endl;
    exit(1);
  }

  // After we have computed an ordering, we have to compute an ordered index set. This datastructure holds the indices taking into account the ordering.
  OrderedIjResult ordered_ij = leopard_ordered_ij_new(ij.object, ordering.object);
  if ((int32_t)ordered_ij.code)
  {
    std::cout << leopard_explain_return_code(ordered_ij.code) << std::endl;
    exit(1);
  }

  // The factorization then requires an assembly tree to be computed from the ordered index set.
  AssemblyTreeResult assembly_tree = leopard_assembly_tree_new(ordered_ij.object, true);
  if ((int32_t)assembly_tree.code)
  {
    std::cout << leopard_explain_return_code(assembly_tree.code) << std::endl;
    exit(1);
  }

  FactorizationSettingsF64* factorization_settings = leopard_factorization_settings_new_default_f64();
  std::cout << "pivot_tolerance: " << leopard_factorization_settings_get_pivot_tolerance_f64(factorization_settings) << std::endl;
  leopard_factorization_settings_set_pivot_tolerance_f64(factorization_settings, 0.02);
  std::cout << "new pivot_tolerance: " << leopard_factorization_settings_get_pivot_tolerance_f64(factorization_settings) << std::endl << std::endl;

  // Finally we can compute the factorization.
  // NOTE: Only at this point do we need the values of the elements in the matrix.
  //       Because of this, if you have a matrix with static pattern, but changing values, you can speed up the computation
  //       by only recomputing the factorization, and not recomputing the index sets, orderings or assembly tree.
  LDLFactorizationResultF64 ldl = leopard_ldl_factorize_f64(ordered_ij.object, vs.data(), ordering.object, assembly_tree.object, factorization_settings);
  if ((int32_t)ldl.code)
  {
    std::cout << leopard_explain_return_code(ldl.code) << std::endl;
    exit(1);
  }

  // We define our result vector, x_test
  Eigen::VectorXd x_test = rhs;
  // And solve A*x_test = rhs
  // NOTE: The solve is in place, this means that on input, x_test holds the right hand side, and when the function returns, it holds the solution to the linear system.
  LeopardReturnCode solve_return_code = leopard_ldl_solve_f64(ldl.object, x_test.data());
  if (!(int)solve_return_code)
  {
    leopard_explain_return_code(solve_return_code);
  }

  // To properly handle resources, you should destroy the different objects when they are not needed anymore,
  // but keep in mind that you can reuse these datastructures for better performance as long as the information used to generate them has not changed.
  leopard_ldl_destroy_f64(ldl.object);
  leopard_factorization_settings_destroy_f64(factorization_settings);
  leopard_assembly_tree_destroy(assembly_tree.object);
  leopard_ordered_ij_destroy(ordered_ij.object);
  leopard_ordering_destroy(ordering.object);
  leopard_ij_destroy(ij.object);

  // We use eigens build-in dense solver to verify that leopard finds the correct solution.

  // Our reference solution
  Eigen::VectorXd x_ref = dense.colPivHouseholderQr().solve(rhs);
  // The residual of the reference linear solver (Eigen).
  double err_ref = (dense * x_ref - rhs).norm();
  // The residual of the test linear solver (leopard).
  double err_test = (dense * x_test - rhs).norm();
  // The norm of the difference between the solution of the reference solver and the test solver.
  double sol_diff = (x_test - x_ref).norm();

  printf("err_ref:  %f\n", err_ref);
  printf("err_test: %f\n", err_test);
  printf("sol_diff: %f\n\n", sol_diff);

  printf("reference solution (Eigen)\n");
  std::cout << x_ref.transpose() << std::endl;
  printf("test solution (leopard)\n");
  std::cout << x_test.transpose() << std::endl;
}