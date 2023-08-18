#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "solver.h"
#include "heading.h"
#include "miscellaneous.h"

using namespace std;

int main()
{
    printTitle();
    printBanner("Aditya Kumawat");
    solver newCube;
    cin >> newCube;
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();
    // CALLING CROSS_SOLVER..........
    newCube.shortest_cube_solution();
    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    newCube.print_solution(duration.count());
    cin.clear();
    getchar();
    return 0;
}
