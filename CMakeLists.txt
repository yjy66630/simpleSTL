cmake_minimum_required(VERSION 3.14)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME simpleSTL)
set(GTEST_DIR "D:\\gtest")

project(${PROJECT_NAME})

# force static runtime libraries for msvc builds
if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

################################
# Normal Libraries & Executables
################################

add_executable(main main.cpp)

################################
# Testing
################################
if (test)

  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(${GTEST_DIR} gtest)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  message(STATUS "gtest_SOURCE_DIR is ${gtest_SOURCE_DIR}")
  include_directories(${gtest_SOURCE_DIR}/googletest/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(test_utils test_utils.cpp)

  # Standard linking to gtest stuff.
  target_link_libraries(test_utils gtest gtest_main)

  # Extra linking for the project.
#  target_link_libraries(runUnitTests project1_lib)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME test-utils COMMAND test_utils)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
#  add_test(another-test-utils test_utils)
endif()
