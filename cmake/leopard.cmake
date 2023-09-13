### BEGIN External leopard CMake integration
include(ExternalProject)
ExternalProject_Add(leopard-external
        URL "https://github.com/molysgaard/leopard/releases/download/v0.1.0/leopard_0.1.0_amd64.zip"
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/leopard"
        EXCLUDE_FROM_ALL
)
add_library(leopard INTERFACE)
add_dependencies(leopard INTERFACE leopard-external)
target_include_directories(leopard INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/leopard/include")
target_link_directories(leopard INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/leopard/lib")
target_link_libraries(leopard INTERFACE libleopard.so)
### END External leopard CMake integration
