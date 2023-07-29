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

    cin >> newCube;
    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();
    // CALLING CROSS_SOLVER..........
    string sideName = newCube.shortest_cube_solution();

    cout << "\n\n-----------------------------------------------------------------------------------------\n\t\t\t\t BEST SOLUTION ON \"" << sideName << "\" SIDE \t\t\t\t\n-----------------------------------------------------------------------------------------\n"
         << endl;
    // SHOWING TOTAL MOVES COUNT.......
    cout << "TOTAL MOVES COUNT : " << newCube.get_solution_size("crs") + newCube.get_solution_size("f2l") + newCube.get_solution_size("oll") + newCube.get_solution_size("pll") << endl;

    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "CROSS SOLUTION IN " << newCube.get_solution_size("crs") << " MOVES:  ";
    newCube.get_cross_solution();
    // CALLING F2L_SOLVER..........
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    cout << "F2L SOLUTION IN " << newCube.get_solution_size("f2l") << " MOVES:  ";
    newCube.get_f2l_solution();
    // CALLING OLL_SOLVER..........
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    cout << "OLL SOLUTION IN " << newCube.get_solution_size("oll") << " MOVES:  ";
    newCube.get_oll_solution();
    // CALLING PLL_SOLVER..........
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    cout << "PLL SOLUTION IN " << newCube.get_solution_size("pll") << " MOVES:  ";
    newCube.get_pll_solution();
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
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
