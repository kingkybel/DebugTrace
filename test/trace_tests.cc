#include <iostream>

// Scenario 1: Trace enabled
#define DO_TRACE_ // NOSONAR: for testing toggling

#include "traceutil.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <string>
#include <tuple>

using namespace std;

class TraceTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // just in case
    }

    void TearDown() override
    {
        // just in case
    }
};

TEST_F(TraceTest, is_tracing)
{
    std::cout << "--- Scenario: Trace Enabled ---" << std::endl;
    testing::internal::CaptureStdout();
    int x = 42;
    TRACE1(x)
    TRACE0
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, ::testing::HasSubstr("x=42"));
    EXPECT_THAT(output, ::testing::HasSubstr("test/trace_tests.cc"));
}

// Scenario 2: Trace disabled
#undef DO_TRACE_       // NOSONAR: for testing toggling
#include <traceutil.h> // NOSONAR: for testing toggling

TEST_F(TraceTest, is_not_tracing)
{
    std::cout << "--- Scenario: Trace Disabled ---" << std::endl;
    testing::internal::CaptureStdout();
    int y = 100;
    TRACE1(y) // Should produce no output
    TRACE0    // Should produce no output
        std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty()) << "Expected no output when tracing is disabled, but got: " << output;
}

// Scenario 3: Trace re-enabled
#define DO_TRACE_      // NOSONAR: for testing toggling
#include <traceutil.h> // NOSONAR: for testing toggling

TEST_F(TraceTest, is_tracing_again)
{
    std::cout << "--- Scenario: Trace Re-enabled ---" << std::endl;
    testing::internal::CaptureStdout();
    int z = 7;
    TRACE1(z)
    TRACE0
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, ::testing::HasSubstr("z=7"));
    EXPECT_THAT(output, ::testing::HasSubstr("test/trace_tests.cc"));
}
