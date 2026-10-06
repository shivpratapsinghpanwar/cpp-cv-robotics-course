// This is a comment. The compiler ignores everything after // on a line.

#include <iostream>

// A function that adds two whole numbers and gives back the result.
int add(int a, int b) {
    return a + b;
}

// Every C++ program starts here.
int main() {
    std::cout << "Hello, robot!\n";

    int a = 2;
    int b = 3;
    int sum = add(a, b);

    std::cout << "2 + 3 = " << sum << "\n";

    return 0;
}
