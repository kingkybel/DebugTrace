#include <iostream>

// Scenario 1: Trace enabled
#define DO_TRACE_ // NOSONAR: for testing toggling
#include <traceutil.h>

void test_enabled()
{
    std::cout << "--- Scenario: Trace Enabled ---" << std::endl;
    int x = 42;
    TRACE1(x);
    TRACE0;
}

// Scenario 2: Trace disabled
#undef DO_TRACE_       // NOSONAR: for testing toggling
#include <traceutil.h> // NOSONAR: for testing toggling

void test_disabled()
{
    std::cout << "--- Scenario: Trace Disabled ---" << std::endl;
    int y = 100;
    TRACE1(y); // Should produce no output
    TRACE0;    // Should produce no output
}

// Scenario 3: Trace re-enabled
#define DO_TRACE_      // NOSONAR: for testing toggling
#include <traceutil.h> // NOSONAR: for testing toggling

void test_reenabled()
{
    std::cout << "--- Scenario: Trace Re-enabled ---" << std::endl;
    int z = 7;
    TRACE1(z);
    TRACE0;
}

int main()
{
    test_enabled();
    test_disabled();
    test_reenabled();
    return 0;
}
