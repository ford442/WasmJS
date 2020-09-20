#include <console.hpp>

int main() {
    console.log("Log message");
    console.warn("Warning message");
    console.error("Error message");

    // printf() style functions
    console.logf("Log message %u", 1);
    console.warnf("Warning message %u", 2);
    console.errorf("Error message %u", 3);

    return 0;
}
