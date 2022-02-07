#include <stdio.h>

int num = 9;
 
// Function to find the nth Fibonacci number
int fib(int n) {
    int curr_fib = 0, next_fib = 1;
    int new_fib;
    for (int i = n; i > 0; i--) {
        new_fib = curr_fib + next_fib;
        curr_fib = next_fib;
        next_fib = new_fib;
    }
 
    return curr_fib;
}
 
int main(void) {
    int i = fib(num);
    printf("i: %d\n", i);
}