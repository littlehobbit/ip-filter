cmake_minimum_required(VERSION 3.15)

set(VERSION "0.0.0" CACHE STRING "Project patch version")
project(ip_filter VERSION ${VERSION})

option(BUILD_TESTS OFF)
option(BUILD_PACKAGE OFF)

add_library(
  ${PROJECT_NAME}_lib STATIC
  src/dummy.cpp
)

target_include_directories(
  ${PROJECT_NAME}_lib PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(
  ${PROJECT_NAME}_lib PRIVATE  -Wall -Wpedantic -Werror
)

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wpedantic -Werror)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if (${BUILD_TESTS})
  enable_testing()
  add_subdirectory(tests)
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if (${BUILD_PACKAGE})
  set(CPACK_GENERATOR DEB)
  set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
  set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
  set(CPACK_PACKAGE_CONTACT gataullinruslandev@gmain.com)
  include(CPack)
endif()
