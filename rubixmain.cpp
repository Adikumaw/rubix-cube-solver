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
    string sideName = newCube.shortest_cube_solution();
    // best solution_on banner...
    cout << "\n\n-----------------------------------------------------------------------------------------\n\t\t\t   BEST SOLUTION ON \"" << BOLD << sideName << DEFAULT << "\" SIDE \t\t\t\n-----------------------------------------------------------------------------------------\n"
         << endl;
    // SHOWING TOTAL MOVES COUNT.......
    set_font_color("TOTAL MOVES COUNT : ", "green");
    cout << RED << newCube.get_solution_size("crs") + newCube.get_solution_size("f2l") + newCube.get_solution_size("oll") + newCube.get_solution_size("pll") << DEFAULT << endl;
    // printing solutions in formated way...
    cout << "-----------------------------------------------------------------------------------------" << endl;
    set_font_color("CRS SOLUTION IN " + to_string(newCube.get_solution_size("crs")) + " MOVES:  ", "green");
    newCube.get_cross_solution();
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("F2L SOLUTION IN " + to_string(newCube.get_solution_size("f2l")) + " MOVES:  ", "green");
    newCube.get_f2l_solution();
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("OLL SOLUTION IN " + to_string(newCube.get_solution_size("oll")) + " MOVES:  ", "green");
    newCube.get_oll_solution();
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("PLL SOLUTION IN " + to_string(newCube.get_solution_size("pll")) + " MOVES:  ", "green");
    newCube.get_pll_solution();
    cout << "\n-----------------------------------------------------------------------------------------" << endl;

    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    // Display the time taken in the terminal window
    set_font_color("Time taken: ", "green");
    std::cout << RED << duration.count() << DEFAULT << " milliseconds" << std::endl;
    getchar();
    return 0;
}
