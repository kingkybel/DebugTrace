#define DO_TRACE_
#include <traceutil.h>

int main() {
    int x = 42;
    TRACE1(x);
    TRACE0;
    return 0;
}
