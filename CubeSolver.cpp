#include "CubeSolver.h"
#include "Cube.h"
#include "Cross.h"
#include "F2l.h"
#include "Oll.h"
#include "Pll.h"
#include "colors.h"
#include <thread>
#include <chrono>

int CubeSolver::getTotalSolutionSize()
{
    return (getSize(bestInCubeCross) + getSize(bestInCubeF2l) + getSize(bestInCubeOll) + getSize(bestInCubePll));
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   SETTER AND GETTER FOR THE RUBIX Cube
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void CubeSolver::print(const int &duration)
{
    string bestSolutionBanner;
    unsigned int currentStep{0};
    int intTotalSolution{getTotalSolutionSize()}, linesNeed;
    bool choice;
    vector<string> totalSteps = allInOneSolution();

    // best solution_on banner...
    bestSolutionBanner = "\n\n-----------------------------------------------------------------------------------------\n\t\t\t   BEST SOLUTION ON \"";
    bestSolutionBanner += BOLD + side_name(bestSide) + DEFAULT;
    bestSolutionBanner += "\" SIDE \t\t\t\n-----------------------------------------------------------------------------------------\n\n";
    std::cout << bestSolutionBanner; // printing best solution banner

    linesNeed = printSolutionSteps(0); // print solutions in formatted way

    // Display the time taken in the terminal window
    set_font_color("Time taken: ", "green");
    std::cout << RED << duration << DEFAULT << " milliseconds" << std::endl;

    // showing options for continue and end....
    std::cout << "Press 1 to continue STEPS or 0 to exit: ";
    cin >> choice;
    if (choice == 0)
        return;

    for (int i{0}; i < intTotalSolution; i++) // looping till all the steps finishes
    {
        currentStep = i;
        // Applying current step to the Cube...
        cube.setalgo(0, totalSteps.at(i), Cube::_false);
        clearLines(28 + linesNeed);
        cube.Cube_state();

        std::cout << RED << trials << DEFAULT << " TIMES Cube SOLVED...";
        std::cout << bestSolutionBanner;

        printSolutionSteps(currentStep);
        // Display the time taken in the terminal window
        set_font_color("Time taken: ", "green");
        std::cout << RED << duration << DEFAULT << " milliseconds" << std::endl;
        // Display current step...
        set_font_color("Current step => ", "green");
        std::cout << RED << totalSteps.at(i) << DEFAULT << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Holding the program for two seconds...
    }
}

int CubeSolver::printSolutionSteps(int currentStep)
{
    int linesNeed{0};
    // SHOWING TOTAL MOVES COUNT
    set_font_color("TOTAL MOVES COUNT : ", "green");
    std::cout << RED << getTotalSolutionSize() << DEFAULT << endl;
    // printing solutions in formated way
    std::cout << "-----------------------------------------------------------------------------------------" << endl;
    set_font_color("CRS SOLUTION IN " + to_string(getSize(bestInCubeCross)) + " MOVES:  ", "green");
    printDirectSteps(bestInCubeCross, currentStep);

    std::cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("F2L SOLUTION IN " + to_string(getSize(bestInCubeF2l)) + " MOVES:  ", "green");
    currentStep -= getSize(bestInCubeCross);
    linesNeed = printDirectSteps(bestInCubeF2l, currentStep); // taking how many extra lines does f2l solution will take

    std::cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("OLL SOLUTION IN " + to_string(getSize(bestInCubeOll)) + " MOVES:  ", "green");
    currentStep -= getSize(bestInCubeF2l);
    printDirectSteps(bestInCubeOll, currentStep);

    std::cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("PLL SOLUTION IN " + to_string(getSize(bestInCubePll)) + " MOVES:  ", "green");
    currentStep -= getSize(bestInCubeOll);
    printDirectSteps(bestInCubePll, currentStep);

    std::cout << "\n-----------------------------------------------------------------------------------------" << endl;

    return linesNeed;
}

int CubeSolver::printDirectSteps(const vector<string> &solution, const int &currentStep)
{
    int linesNeed{0};
    if (!getSize(solution))
        std::cout << BOLD << "SOLVED" << DEFAULT;
    else
    {
        cout << BOLD;
        for (size_t i{0}; i < solution.size(); i++)
        {
            if (i != 0 && !(i % 20))
            {
                std::cout << endl;
                linesNeed++;
            }
            if (i == currentStep)
                std::cout << "[" << solution.at(i) << "]"
                          << " ";
            else
                std::cout << solution.at(i) << " ";
        }
        cout << DEFAULT;
    }
    return linesNeed;
}

void CubeSolver::solve()
{
    // initialising solver classes..
    Cube *cross = new Cross(cube);
    Cube *f2l = new F2l(cube);
    Cube *oll = new Oll(cube);
    Cube *pll = new Pll(cube);

    int side{0};
    vector<vector<string>> crossSolutions, f2lSolutions, ollSolutions, pllSolutions;
    vector<vector<string>> bestInSideCross, bestInSideF2l, bestInSideOll, bestInSidePll;

    int bestInCubeSize{1000}, bestInCubeIndex{0}, currentCubeSize{0};
    for (side = 0; side < 6; side++)
    {
        Cube_orienter(cube, side); // orienting the cube according to the current solving side...
        // getting cross solutions...
        *cross = cube;
        cross->solver(crossSolutions);
        // size_t crscount{0}, f2lcount{0};
        vector<vector<string>> inSideF2l, inSideOll, inSidePll;
        int bestInSideSize{1000}, bestInSideIndex{0}, currentSideSize{0};
        for (size_t crscount{0}; crscount < crossSolutions.size(); crscount++)
        {
            // applying cross solution...
            *cross = cube;
            cross->setalgo(0, crossSolutions.at(crscount), Cube::_false);
            // getting f2l solutions...
            *f2l = *cross;
            f2l->solver(f2lSolutions);
            // int crsSize = getSize(crossSolutions.at(crscount));
            int bestInF2lSize{1000}, currentF2lSize{0}, bestInf2lIndex{0};
            for (size_t f2lcount{0}; f2lcount < f2lSolutions.size(); f2lcount++)
            {
                // printing How Many Times Cube is solved
                trials++;
                std::cout << "\r" << RED << trials << DEFAULT << " TIMES Cube SOLVED...";
                // applying f2l soliution...
                *f2l = *cross;
                f2l->setalgo(0, f2lSolutions.at(f2lcount), Cube::_false);
                // getting oll solution...
                *oll = *f2l;
                oll->solver(ollSolutions);
                // getting pll solution...
                *pll = *oll;
                pll->solver(pllSolutions);
                // finding shortest solutions in f2l, oll and pll...
                currentF2lSize = getSize(f2lSolutions.at(f2lcount)) + getSize(ollSolutions.at(f2lcount)) + getSize(pllSolutions.at(f2lcount)); // taking current size of solutions...
                if (currentF2lSize < bestInF2lSize)
                // storing shorter sized solutions index
                {
                    bestInF2lSize = currentF2lSize;
                    bestInf2lIndex = f2lcount;
                }
            }
            // storing best in f2l, oll and pll soltuion after one crossSolution
            inSideF2l.push_back(f2lSolutions.at(bestInf2lIndex));
            inSideOll.push_back(ollSolutions.at(bestInf2lIndex));
            inSidePll.push_back(pllSolutions.at(bestInf2lIndex));
            f2lSolutions.clear();
            ollSolutions.clear();
            pllSolutions.clear();
            // finding shortest solutions in cross, f2l, oll and pll....
            currentSideSize = getSize(crossSolutions.at(crscount)) + getSize(inSideF2l.at(crscount)) + getSize(inSideOll.at(crscount)) + getSize(inSidePll.at(crscount)); // taking current size of solutions....
            if (currentSideSize < bestInSideSize)
            {
                bestInSideSize = currentSideSize;
                bestInSideIndex = crscount;
            }
        }
        // storing best in cross, f2l, oll and pll solutions in one side...
        bestInSideCross.push_back(crossSolutions.at(bestInSideIndex));
        bestInSideF2l.push_back(inSideF2l.at(bestInSideIndex));
        bestInSideOll.push_back(inSideOll.at(bestInSideIndex));
        bestInSidePll.push_back(inSidePll.at(bestInSideIndex));
        crossSolutions.clear();

        // finding shortest solutions in all sides...
        currentCubeSize = getSize(bestInSideCross.at(side)) + getSize(bestInSideF2l.at(side)) + getSize(bestInSideOll.at(side)) + getSize(bestInSidePll.at(side));
        if (currentCubeSize < bestInCubeSize)
        {
            bestInCubeSize = currentCubeSize;
            bestInCubeIndex = side;
            bestSide = side;
        }

        Cube_reorienter(cube, side); // reorienting the cube to main...
    }
    bestInCubeCross = bestInSideCross.at(bestInCubeIndex);
    bestInCubeF2l = bestInSideF2l.at(bestInCubeIndex);
    bestInCubeOll = bestInSideOll.at(bestInCubeIndex);
    bestInCubePll = bestInSidePll.at(bestInCubeIndex);
    bestInSideCross.clear();
    bestInSideF2l.clear();
    bestInSideOll.clear();
    bestInSidePll.clear();

    // correcting solution on the basis of user orientation...
    algorithmCorrector(bestSide, bestInCubeCross);
    algorithmCorrector(bestSide, bestInCubeF2l);
    algorithmCorrector(bestSide, bestInCubeOll);
    algorithmCorrector(bestSide, bestInCubePll);
}

int CubeSolver::getSize(const vector<string> &solution)
{
    if (solution.size() == 1)
    {
        if (solution.at(0) == "")
            return 0;
    }
    return solution.size();
}

vector<string> CubeSolver::allInOneSolution()
{
    vector<string> totalSteps;
    if (getSize(bestInCubeCross))
        totalSteps.insert(totalSteps.end(), bestInCubeCross.begin(), bestInCubeCross.end());
    if (getSize(bestInCubeF2l))
        totalSteps.insert(totalSteps.end(), bestInCubeF2l.begin(), bestInCubeF2l.end());
    if (getSize(bestInCubeOll))
        totalSteps.insert(totalSteps.end(), bestInCubeOll.begin(), bestInCubeOll.end());
    if (getSize(bestInCubePll))
        totalSteps.insert(totalSteps.end(), bestInCubePll.begin(), bestInCubePll.end());
    return totalSteps;
}

void CubeSolver::algorithmCorrector(const int &side, vector<string> &algorithm)
{
    if (algorithm.size() == 0)
    {
        return;
    }
    else if (algorithm.at(0) == "")
    {
        return;
    }
    if (side == 0) // face
    {
        for (size_t i{0}; i < algorithm.size(); i++)
        {
            // L will remain same in this case....
            // R will remain same in this case....
            // M will remain same in this case....
            if (algorithm.at(i).at(0) == 'F')
                algorithm.at(i).at(0) = 'U';
            else if (algorithm.at(i).at(0) == 'U')
                algorithm.at(i).at(0) = 'B';
            else if (algorithm.at(i).at(0) == 'D')
                algorithm.at(i).at(0) = 'F';
            else if (algorithm.at(i).at(0) == 'B')
                algorithm.at(i).at(0) = 'D';
            else if (algorithm.at(i).at(0) == 'E')
                algorithm.at(i).at(0) = 'S';
            else if (algorithm.at(i) == "S")
                algorithm.at(i) = "EP";
            else if (algorithm.at(i) == "SP")
                algorithm.at(i) = "E";
            else if (algorithm.at(i) == "S2")
                algorithm.at(i) = "E2";
        }
    }
    else if (side == 2) // left
    {
        for (size_t i{0}; i < algorithm.size(); i++)
        {
            // F will remain same in this case....
            // B will remain same in this case....
            // S will remain same in this case....
            if (algorithm.at(i).at(0) == 'L')
                algorithm.at(i).at(0) = 'U';
            else if (algorithm.at(i).at(0) == 'R')
                algorithm.at(i).at(0) = 'D';
            else if (algorithm.at(i).at(0) == 'U')
                algorithm.at(i).at(0) = 'R';
            else if (algorithm.at(i).at(0) == 'D')
                algorithm.at(i).at(0) = 'L';
            else if (algorithm.at(i) == "M")
                algorithm.at(i) = "EP";
            else if (algorithm.at(i) == "MP")
                algorithm.at(i) = "E";
            else if (algorithm.at(i) == "M2")
                algorithm.at(i) = "E2";
            else if (algorithm.at(i).at(0) == 'E')
                algorithm.at(i).at(0) = 'M';
        }
    }
    else if (side == 3) // right
    {
        for (size_t i{0}; i < algorithm.size(); i++)
        {
            // F will remain same in this case....
            // B will remain same in this case....
            // S will remain same in this case....
            if (algorithm.at(i).at(0) == 'L')
                algorithm.at(i).at(0) = 'D';
            else if (algorithm.at(i).at(0) == 'R')
                algorithm.at(i).at(0) = 'U';
            else if (algorithm.at(i).at(0) == 'U')
                algorithm.at(i).at(0) = 'L';
            else if (algorithm.at(i).at(0) == 'D')
                algorithm.at(i).at(0) = 'R';
            else if (algorithm.at(i).at(0) == 'M')
                algorithm.at(i).at(0) = 'E';
            else if (algorithm.at(i) == "E")
                algorithm.at(i) = "MP";
            else if (algorithm.at(i) == "EP")
                algorithm.at(i) = "M";
            else if (algorithm.at(i) == "E2")
                algorithm.at(i) = "M2";
        }
    }
    else if (side == 1) // back
    {
        for (size_t i{0}; i < algorithm.size(); i++)
        {
            // L will remain same in this case....
            // R will remain same in this case....
            // M will remain same in this case....
            if (algorithm.at(i).at(0) == 'F')
                algorithm.at(i).at(0) = 'D';
            else if (algorithm.at(i).at(0) == 'U')
                algorithm.at(i).at(0) = 'F';
            else if (algorithm.at(i).at(0) == 'D')
                algorithm.at(i).at(0) = 'B';
            else if (algorithm.at(i).at(0) == 'B')
                algorithm.at(i).at(0) = 'U';
            else if (algorithm.at(i) == "E")
                algorithm.at(i) = "SP";
            else if (algorithm.at(i) == "EP")
                algorithm.at(i) = "S";
            else if (algorithm.at(i) == "E2")
                algorithm.at(i) = "S2";
            else if (algorithm.at(i).at(0) == 'S')
                algorithm.at(i).at(0) = 'E';
        }
    }
    else if (side == 4) // top
    {
        for (size_t i{0}; i < algorithm.size(); i++)
        {
            // L will remain same in this case....
            // R will remain same in this case....
            // M will remain same in this case....
            if (algorithm.at(i).at(0) == 'F')
                algorithm.at(i).at(0) = 'B';
            else if (algorithm.at(i).at(0) == 'U')
                algorithm.at(i).at(0) = 'D';
            else if (algorithm.at(i).at(0) == 'D')
                algorithm.at(i).at(0) = 'U';
            else if (algorithm.at(i).at(0) == 'B')
                algorithm.at(i).at(0) = 'F';
            else if (algorithm.at(i) == "E")
                algorithm.at(i) = "EP";
            else if (algorithm.at(i) == "EP")
                algorithm.at(i) = "E";
            else if (algorithm.at(i) == "S")
                algorithm.at(i) = "SP";
            else if (algorithm.at(i) == "SP")
                algorithm.at(i) = "S";
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION ORIENTS THE Cube BY MAKING THE GIVEN SIDE TO THE BASE SIDE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void CubeSolver::Cube_orienter(Cube &cube, const int &side)
{
    // Orienting the Cube on the basis of side value passed....
    switch (side)
    {
    case 0: // face
        cube.XP;
        break;
    case 2: // left
        cube.ZP;
        break;
    case 3: // right
        cube.Z;
        break;
    case 1: // back
        cube.X;
        break;
    case 4: // top
        cube.X;
        cube.X;
        break;
    default:
        break;
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION RE-ORIENTS THE Cube TO THE PAST CONDIDTION...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void CubeSolver::Cube_reorienter(Cube &cube, const int &side)
{
    // Re Orienting the Cube on the basis of side value passed....
    switch (side)
    {
    case 0: // face
        cube.X;
        break;
    case 2: // left
        cube.Z;
        break;
    case 3: // right
        cube.ZP;
        break;
    case 1: // back
        cube.XP;
        break;
    case 4: // top
        cube.X;
        cube.X;
        break;
    default:
        break;
    }
}
