find_package(GTest CONFIG REQUIRED)

add_executable(run_tests
        run_tests.cc
        trace_tests.cc
)

target_link_libraries(run_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)
target_compile_features(run_tests PRIVATE cxx_std_23)
add_test(NAME run_tests COMMAND run_tests)
