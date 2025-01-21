
#include <stdio.h>

void function_a() {
    for (int i = 0; i < 1000; i++) {}
}

void function_b() {
    for (int i = 0; i < 5000; i++) {}
}

int main() {
    function_a();
    function_b();
    return 0;
}
