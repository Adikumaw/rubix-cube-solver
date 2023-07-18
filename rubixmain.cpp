#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "makeCubie.h"

using namespace std;

int main()
{
    makeCubie newCube;

    newCube.set_cube();
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();
    // CALLING CROSS_SOLVER..........
    string sideName = newCube.shortest_cube_solution();
    cout << "\nBEST SOLUTION ON \"" << sideName << "\" SIDE ------>" << endl;
    cout << "TOTAL MOVES COUNT : " << newCube.get_solution_size("crs") + newCube.get_solution_size("f2l") + newCube.get_solution_size("oll") + newCube.get_solution_size("pll") << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "CROSS SOLUTION IN " << newCube.get_solution_size("crs") << " MOVES:  ";
    newCube.get_cross_solution();
    cout << "\n---------------------------------------------------------------" << endl;
    // CALLING F2L_SOLVER..........
    cout << "---------------------------------------------------------------" << endl;
    cout << "F2L SOLUTION IN " << newCube.get_solution_size("f2l") << " MOVES:  ";
    newCube.get_f2l_solution();
    cout << "\n---------------------------------------------------------------" << endl;
    // CALLING OLL_SOLVER..........
    cout << "---------------------------------------------------------------" << endl;
    cout << "OLL SOLUTION IN " << newCube.get_solution_size("oll") << " MOVES:  ";
    newCube.get_oll_solution();
    cout << "\n---------------------------------------------------------------" << endl;
    // CALLING PLL_SOLVER..........
    cout << "---------------------------------------------------------------" << endl;
    cout << "PLL SOLUTION IN " << newCube.get_solution_size("pll") << " MOVES:  ";
    newCube.get_pll_solution();
    cout << "\n---------------------------------------------------------------" << endl;
    // newCube.get_cube();
    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Display the time taken in the terminal window
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    getchar();
    return 0;
}
