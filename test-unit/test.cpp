#include <valarray>
#include <iostream>
#include <catch2/internal/catch_preprocessor_internal_stringify.hpp>
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_compiler_capabilities.hpp"
#include "catch2/internal/catch_decomposer.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_test_macro_impl.hpp"
#include "catch2/internal/catch_test_registry.hpp"
using namespace std;
#define CATCH_CONFIG_MAIN

/*
    To check output (At the maze_escape directory):
        g++ -std=c++14 -Werror -Wuninitialized -o test test-unit/test.cpp && ./test
*/

TEST_CASE("Function: getAdjacent, source", "[given]")
{
    int actualOutput = 0;
    int expectedOutput = 0;

    REQUIRE(actualOutput == expectedOutput);
}
