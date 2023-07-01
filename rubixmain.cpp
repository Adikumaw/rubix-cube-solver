#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "makeCubie.h"

enum side
{
    face,
    back,
    left,
    right,
    top,
    bottom,
    mid,
    equator,
    stand

};

#define F newCube.sideRotate(side::face, "clk");
#define L newCube.sideRotate(side::left, "clk");
#define R newCube.sideRotate(side::right, "clk");
#define U newCube.sideRotate(side::top, "clk");
#define D newCube.sideRotate(side::bottom, "clk");
#define B newCube.sideRotate(side::back, "clk");
#define FP newCube.sideRotate(side::face, "antclk");
#define LP newCube.sideRotate(side::left, "antclk");
#define RP newCube.sideRotate(side::right, "antclk");
#define UP newCube.sideRotate(side::top, "antclk");
#define DP newCube.sideRotate(side::bottom, "antclk");
#define BP newCube.sideRotate(side::back, "antclk");

using namespace std;

int main()
{
    makeCubie newCube;
    newCube.setcube();
    auto startTime = std::chrono::high_resolution_clock::now();
    // CALLING CROSS_SOLVER..........
    newCube.crossSolver();
    cout << "---------------------------------------------------------------" << endl;
    cout << "CROSS SOLUTION:  ";
    newCube.getCrossSolution();
    newCube.getcube();
    cout << "\n---------------------------------------------------------------" << endl;
    // CALLING F2L_SOLVER..........
    newCube.shortestF2LSolver();
    cout << "\n---------------------------------------------------------------" << endl;
    cout << "F2L SOLUTION:  ";
    newCube.getF2LSolution();
    cout << "\n---------------------------------------------------------------" << endl;
    // CALLING OLL_SOLVER..........
    newCube.OLLSolver();
    cout << "---------------------------------------------------------------" << endl;
    cout << "OLL SOLUTION:  ";
    newCube.getOLLSolution();
    cout << "\n---------------------------------------------------------------" << endl;
    // newCube.getcube();

    // faceTranspose(&cubeMain);
    // using namespace std::this_thread; // sleep_for, sleep_until
    // chrono::sleep_until(system_clock::now() + seconds(1));
    // using namespace std::chrono; // nanoseconds, system_clock, seconds
    // this_thread::sleep_for(chrono::nanoseconds(60000000));
    // Stop the timer
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Display the time taken in the terminal window
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    getchar();
    return 0;
}
