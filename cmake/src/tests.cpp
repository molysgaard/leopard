#include <leopard.h>
#include <vector>
#include <cassert>

void test_i_outside()
{
  // Our system is of size 3x3
  uintptr_t n = 3;

  std::vector<uintptr_t> is = {0, 1, 2, 1, 3, 2};
  std::vector<uintptr_t> js = {0, 0, 0, 1, 1, 2};

  // First we create the index-set data structure, IJ. It stores the indices of the sparse matrix.
  IjResult ij = leopard_ij_new_i_j_array_uintptr(n, is.size(), is.data(), js.data(), true);
  assert(ij.code == LeopardReturnCode_Ij_ErrorIjOutsideN);
}

void test_j_outside()
{
  // Our system is of size 3x3
  uintptr_t n = 3;

  std::vector<uintptr_t> is = {0, 1, 2, 1, 4, 2};
  std::vector<uintptr_t> js = {0, 0, 0, 1, 4, 2};

  // First we create the index-set data structure, IJ. It stores the indices of the sparse matrix.
  IjResult ij = leopard_ij_new_i_j_array_uintptr(n, is.size(), is.data(), js.data(), true);
  assert(ij.code == LeopardReturnCode_Ij_ErrorIjOutsideN);
}

void test_row_major_order()
{
  // Our system is of size 3x3
  uintptr_t n = 3;

  std::vector<uintptr_t> is = {0, 1, 1, 2, 2, 2};
  std::vector<uintptr_t> js = {0, 0, 1, 0, 1, 2};

  // First we create the index-set data structure, IJ. It stores the indices of the sparse matrix.
  IjResult ij = leopard_ij_new_i_j_array_uintptr(n, is.size(), is.data(), js.data(), true);
  assert(ij.code == LeopardReturnCode_Ij_ErrorIjNotColMajorOrder);
}

void test_upper_triangular()
{
  // Our system is of size 3x3
  uintptr_t n = 3;

  // These indices are upper triangular
  std::vector<uintptr_t> is = {0, 0, 1, 0, 1, 2};
  std::vector<uintptr_t> js = {0, 1, 1, 2, 2, 2};

  // First we create the index-set data structure, IJ. It stores the indices of the sparse matrix.
  IjResult ij = leopard_ij_new_i_j_array_uintptr(n, is.size(), is.data(), js.data(), true);
  assert(ij.code == LeopardReturnCode_Ij_ErrorIjMustBeLowerTriangular);
}

int main()
{
  test_i_outside();
  test_j_outside();
  test_row_major_order();
  test_upper_triangular();
}
