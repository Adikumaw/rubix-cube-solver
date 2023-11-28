#include <iostream>
#include <string>
#include <chrono>
#include "CubeSolver.h"
#include "heading.h"
#include "miscellaneous.h"

using namespace std;

int main()
{
    printTitle();
    printBanner("Aditya Kumawat");
    CubeSolver cube;
    cin >> cube;
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();
    // CALLING CROSS_SOLVER..........
    cube.solve();
    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    // Printing the solution
    cube.print(duration.count());
    return 0;
}
