// Day 1 - Exercise 2: the corrected program. The 5 fixes are marked FIX.

#include <iostream>

int main() {
    int battery = 80;                                          // FIX 1: missing ;
    std::cout << "Robot battery: " << battery << "%\n";       // FIX 2: typo "batery" -> undeclared identifier

    if (battery > 20) {                                        // FIX 3: missing )
        std::cout << "Battery OK\n";                           // FIX 4: cout lives in the std namespace -> std::cout
    }

    std::cout << "Countdown: ";
    for (int count = 3; count > 0; --count) {                  // FIX 5: a new variable needs its type: int count
        std::cout << count << " ";
    }
    std::cout << "\n";

    return 0;
}
