#include "solver.h"
#include "colors.h"
#include <thread>
#include <chrono>

void solution_optimizer(vector<std::string> &solution);
/* ----------------------------------------------------------------------------------------------------------------------------------------
   CONSTRUCTORS FOR cube CLASS
   ----------------------------------------------------------------------------------------------------------------------------------------*/
solver::solver() : cube() {}
solver::solver(const solver &src) : cube(src) {}

/* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
solver &solver::operator=(const solver &src)
{
    if (this == &src) // FOR THE CONDITION WHEN SAME CLASS ARE ASSIGNED;
        return *this;

    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                this->cubeMain[l][m][n] = src.cubeMain[l][m][n];
            }
        }
    }
    this->f2lSolution = src.f2lSolution;
    this->crossSolution = src.crossSolution;
    this->ollSolution = src.ollSolution;
    this->pllSolution = src.pllSolution;
    return *this;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   SETTER AND GETTER FOR THE RUBIX CUBE
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::get_cross_solution(int currentStep)
{
    if (crossSolution.size() == 0)
        std::cout << BOLD << "SOLVED" << DEFAULT;
    else
    {
        cout << BOLD;
        for (size_t i{0}; i < crossSolution.size(); i++)
            if (i == currentStep)
                std::cout << "[" << crossSolution.at(i) << "]"
                          << " ";
            else
                std::cout << crossSolution.at(i) << " ";
        cout << DEFAULT;
    }
}
int solver::get_f2l_solution(int currentStep)
{
    int linebreak{0};
    if (f2lSolution.size() == 0)
        std::cout << BOLD << "SOLVED" << DEFAULT;
    else
    {
        cout << BOLD;
        for (size_t i{0}; i < f2lSolution.size(); i++)
        {
            if ((i % 22) == 0)
            {
                linebreak++;
                if (linebreak == 2)
                    std::cout << "\n                           ";
            }
            if (i == currentStep)
                std::cout << "[" << f2lSolution.at(i) << "]"
                          << " ";
            else
                std::cout << f2lSolution.at(i) << " ";
        }
        cout << DEFAULT;
        return linebreak - 1;
    }
    return 0;
}
void solver::get_oll_solution(int currentStep)
{
    if (ollSolution.size() == 0)
        std::cout << BOLD << "SOLVED" << DEFAULT;
    else
    {
        cout << BOLD;
        for (size_t i{0}; i < ollSolution.size(); i++)
            if (i == currentStep)
                std::cout << "[" << ollSolution.at(i) << "]"
                          << " ";
            else
                std::cout << ollSolution.at(i) << " ";
        cout << DEFAULT;
    }
}
void solver::get_pll_solution(int currentStep)
{
    if (pllSolution.size() == 0)
        std::cout << BOLD << "SOLVED" << DEFAULT;
    else
    {
        cout << BOLD;
        for (size_t i{0}; i < pllSolution.size(); i++)
            if (i == currentStep)
                std::cout << "[" << pllSolution.at(i) << "]"
                          << " ";
            else
                std::cout << pllSolution.at(i) << " ";
        cout << DEFAULT;
    }
}
int solver::get_total_solution_size()
{
    return get_solution_size("crs") + get_solution_size("f2l") + get_solution_size("oll") + get_solution_size("pll");
}
int solver::get_solution_size(string_view solutionName)
{
    if (solutionName == "crs")
        if (crossSolution.size() == 0)
            return 0;
        else
            return crossSolution.size();
    else if (solutionName == "f2l")
        if (f2lSolution.size() == 0)
            return 0;
        else
            return f2lSolution.size();
    else if (solutionName == "oll")
        if (ollSolution.size() == 0)
            return 0;
        else
            return ollSolution.size();
    else if (solutionName == "pll")
        if (pllSolution.size() == 0)
            return 0;
        else
            return pllSolution.size();
    return -1;
}
void solver::print_solution(int duration)
{
    string bestSolutionBanner;
    unsigned int currentStep{0};
    int intTotalSolution{get_total_solution_size()}, choice;
    vector<string> totalSteps;
    totalSteps.insert(totalSteps.end(), crossSolution.begin(), crossSolution.end());
    totalSteps.insert(totalSteps.end(), f2lSolution.begin(), f2lSolution.end());
    totalSteps.insert(totalSteps.end(), ollSolution.begin(), ollSolution.end());
    totalSteps.insert(totalSteps.end(), pllSolution.begin(), pllSolution.end());
    // best solution_on banner...
    bestSolutionBanner = "\n\n-----------------------------------------------------------------------------------------\n\t\t\t   BEST SOLUTION ON \"";
    bestSolutionBanner += BOLD + side_name(solutionSide) + DEFAULT;
    bestSolutionBanner += "\" SIDE \t\t\t\n-----------------------------------------------------------------------------------------\n\n";
    cout << bestSolutionBanner; // printing best solution banner
    // SHOWING TOTAL MOVES COUNT
    set_font_color("TOTAL MOVES COUNT : ", "green");
    cout << RED << intTotalSolution << DEFAULT << endl;
    // printing solutions in formated way
    cout << "-----------------------------------------------------------------------------------------" << endl;
    set_font_color("CRS SOLUTION IN " + to_string(get_solution_size("crs")) + " MOVES:  ", "green");
    get_cross_solution(currentStep);
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("F2L SOLUTION IN " + to_string(get_solution_size("f2l")) + " MOVES:  ", "green");
    currentStep -= get_solution_size("crs");
    int f2lLine = get_f2l_solution(currentStep); // taking how many extra lines does f2l solution will take
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("OLL SOLUTION IN " + to_string(get_solution_size("oll")) + " MOVES:  ", "green");
    currentStep -= get_solution_size("f2l");
    get_oll_solution(currentStep);
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    set_font_color("PLL SOLUTION IN " + to_string(get_solution_size("pll")) + " MOVES:  ", "green");
    currentStep -= get_solution_size("oll");
    get_pll_solution(currentStep);
    cout << "\n-----------------------------------------------------------------------------------------" << endl;
    // Display the time taken in the terminal window
    set_font_color("Time taken: ", "green");
    std::cout << RED << duration << DEFAULT << " milliseconds" << std::endl;
    // showing options for continue and end....
    cout << "Press 1 to continue STEPS or 0 to exit: ";
    cin >> choice;
    if (choice == 0)
    {
        return;
    }

    for (int i{0}; i < intTotalSolution; i++) // looping till all the steps finishes
    {
        currentStep = i;
        // Applying current step to the cube...
        setalgo(0, totalSteps.at(i), "null");
        clearLines(28 + f2lLine);
        cube_state();
        std::cout << RED << trials << DEFAULT << " TIMES CUBE SOLVED...";
        cout << bestSolutionBanner;
        // SHOWING TOTAL MOVES COUNT.......
        set_font_color("TOTAL MOVES COUNT : ", "green");
        cout << RED << intTotalSolution << DEFAULT << endl;
        // Printing solutions in formated way...
        cout << "-----------------------------------------------------------------------------------------" << endl;
        set_font_color("CRS SOLUTION IN " + to_string(get_solution_size("crs")) + " MOVES:  ", "green");
        get_cross_solution(currentStep);
        cout << "\n-----------------------------------------------------------------------------------------" << endl;
        set_font_color("F2L SOLUTION IN " + to_string(get_solution_size("f2l")) + " MOVES:  ", "green");
        currentStep -= get_solution_size("crs");
        get_f2l_solution(currentStep);
        cout << "\n-----------------------------------------------------------------------------------------" << endl;
        set_font_color("OLL SOLUTION IN " + to_string(get_solution_size("oll")) + " MOVES:  ", "green");
        currentStep -= get_solution_size("f2l");
        get_oll_solution(currentStep);
        cout << "\n-----------------------------------------------------------------------------------------" << endl;
        set_font_color("PLL SOLUTION IN " + to_string(get_solution_size("pll")) + " MOVES:  ", "green");
        currentStep -= get_solution_size("oll");
        get_pll_solution(currentStep);
        cout << "\n-----------------------------------------------------------------------------------------" << endl;
        // Display the time taken in the terminal window
        set_font_color("Time taken: ", "green");
        std::cout << RED << duration << DEFAULT << " milliseconds" << std::endl;
        // Display current step...
        set_font_color("Current step => ", "green");
        std::cout << RED << totalSteps.at(i) << DEFAULT << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Holding the program for two seconds...
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE BOTTOM CROSS OF TEH RUBIX CUBE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::cross_solver(solver &storeSolution)
{
    int block{0}, side{0}, crossColorCount{0}, count{0}, twocorrect{0}, limit{0};
    bool solve{false}, tenTimeSolve{false};
    const char bottomColor{cubeMain[bottom][1][1]};
    char edgeColor{};
    vector<char> mainOrientation{}, currentOrientation{};
    vector<int> crsEdges{};
    mainOrientation = move(get_equator_colors_orientation(*this));
    currentOrientation = move(get_cross_colors_orientation(*this));
    crossColorCount = count_bottom_lyr_edge(*this);

    if (crossColorCount == 4)
    {
        // for the condition when crosscolor count == 4....
        currentOrientation = move(get_cross_colors_orientation(*this));
        for (int i{0}; i < 4; i++)
        {
            count = 0;
            for (int j{0}; j < 4; j++)
                if (currentOrientation[j] == mainOrientation[j])
                    count++;
            if (count == 4 || count == 2)
                break;
            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
            // moving bottom to the correct location...
            setalgo(face, "D", "crs");
        }
        if (count == 4)
        {
            // Optimising f2lSolution....
            solution_optimizer(crossSolution);
            storeSolution.crossSolutions.push_back(crossSolution);
            return;
        }
        else
        {
            int icside{};
            for (icside = 0; icside < 4; icside++)
                if (currentOrientation[icside] != mainOrientation[icside])
                    break;
            switch (icside)
            {
            case 0:
                side = face;
                break;
            case 1:
                side = right;
                break;
            case 2:
                side = back;
                break;
            case 3:
                side = left;
                break;
            default:
                break;
            }
            for (int checkside{0}; checkside < 3; checkside++)
            {
                switch (checkside)
                {
                case 0:
                    setalgo(side, "FP DP F D FP", "crs");
                    break;
                case 1:
                    setalgo(side, "F D FP DP F", "crs");
                    break;
                case 2:
                    setalgo(side, "F D2 FP D2 F", "crs");
                    break;
                default:
                    break;
                }
                // Verifying the current orientation...
                currentOrientation = move(get_cross_colors_orientation(*this));
                for (int i{0}; i < 4; i++)
                {
                    count = 0;
                    for (int j{0}; j < 4; j++)
                        if (currentOrientation[j] == mainOrientation[j])
                            count++;
                    if (count == 4)
                        break;
                    std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                }
                if (count == 4)
                    break;
                // reverting the previour solution....
                switch (checkside)
                {
                case 0:
                    setalgo(side, "F DP FP D F", "null");
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    break;
                case 1:
                    setalgo(side, "FP D F DP FP", "null");
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    break;
                case 2:
                    setalgo(side, "FP D2 F D2 FP", "null");
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    crossSolution.pop_back();
                    break;
                default:
                    break;
                }
            }
        }
    }
    if (mainOrientation[0] != currentOrientation[0] && mainOrientation[0] != currentOrientation[1] && mainOrientation[0] != currentOrientation[2] && mainOrientation[0] != currentOrientation[3])
        crsEdges.push_back(1);
    // second f2l corner...
    if (mainOrientation[1] != currentOrientation[0] && mainOrientation[1] != currentOrientation[1] && mainOrientation[1] != currentOrientation[2] && mainOrientation[1] != currentOrientation[3])
        crsEdges.push_back(2);
    // third f2l corner...
    if (mainOrientation[2] != currentOrientation[0] && mainOrientation[2] != currentOrientation[1] && mainOrientation[2] != currentOrientation[2] && mainOrientation[2] != currentOrientation[3])
        crsEdges.push_back(3);
    // fourth f2l corner...
    if (mainOrientation[3] != currentOrientation[0] && mainOrientation[3] != currentOrientation[1] && mainOrientation[3] != currentOrientation[2] && mainOrientation[3] != currentOrientation[3])
        crsEdges.push_back(4);

    solver sourceBackup, sourceCpy;
    for (size_t i{0}; i < crsEdges.size(); i++)
    {
        // cornerColors.clear();
        switch (crsEdges[i])
        {
        case 1:
            /* code */
            edgeColor = mainOrientation[0];
            break;
        case 2:
            /* code */
            edgeColor = mainOrientation[1];
            break;
        case 3:
            /* code */
            edgeColor = mainOrientation[2];
            break;
        case 4:
            /* code */
            edgeColor = mainOrientation[3];
            break;
        default:
            break;
        }
        sourceBackup = *this;
        if (!get_edge_location(edgeColor, side, block))
            std::cout << "error finding coordinate...." << endl;
        crossColorCount = count_bottom_lyr_edge(*this);
        if (crossColorCount != 4)
        {
            if (side >= face && side <= right)
            {
                switch (block)
                {
                // this case is for checking the top side edge....
                case 1:
                    if (cubeMain[side][0][1] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                            // No edges on the bottom...
                        case 0:
                            crossColorCount = -1;
                            for (int two_t{0}; two_t < 2; two_t++)
                            {
                                sourceBackup = *this;
                                switch (two_t)
                                {
                                case 0:
                                    setalgo(side, "F RP", "crs");
                                    break;
                                case 1:
                                    setalgo(side, "FP L", "crs");
                                    break;
                                default:
                                    break;
                                }
                                sourceCpy = *this;
                                *this = sourceBackup;
                                sourceCpy.cross_solver(storeSolution);
                            }
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 2)
                                    break;
                                else
                                    count = 1;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            limit = count + 1;
                            for (int twotimes{0}; twotimes < 2; twotimes++)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    if (twotimes == 0)
                                        setalgo(side, "F RP", "crs");
                                    else
                                        setalgo(side, "FP L", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (limit == 3 && crossColorCount == 2)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "FP", "crs");
                                        else
                                            setalgo(side, "F", "crs");
                                        // using twoCorrect as a singnal.....
                                        twocorrect = -1;
                                    }
                                    else
                                        twocorrect = 0;
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount >= limit)
                                    {
                                        // Verifying the current Orientation......
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= limit)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= limit)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    if (twocorrect == -1)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "F", "null");
                                        else
                                            setalgo(side, "FP", "null");
                                        crossSolution.pop_back();
                                    }
                                    if (twotimes == 0)
                                        setalgo(side, "R FP", "null");
                                    else
                                        setalgo(side, "LP F", "null");
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                                // this is for breaking the two times loop .....
                                if (count >= limit)
                                    break;
                            }
                            break;
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 3)
                                    break;
                                if (count >= 2)
                                    twocorrect = 2;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            // here the arising three conditions will be checked by count number........
                            // When all three are correct...
                            if (count >= 3)
                            {
                                for (int twotimes{0}; twotimes < 2; twotimes++)
                                {
                                    for (int checkside{0}; checkside < 4; checkside++)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "F RP FP", "crs");
                                        else
                                            setalgo(side, "FP L F", "crs");
                                        crossColorCount = count_bottom_lyr_edge(*this);
                                        if (crossColorCount == 4)
                                        {
                                            if (checkside == 2)
                                            {
                                                // reverting to get even shorter solution....
                                                setalgo(side, "F R FP", "null");
                                                crossSolution.pop_back();
                                                crossSolution.pop_back();
                                                crossSolution.pop_back();
                                                // for removing last two D operatrions...
                                                setalgo(side, "D2", "null");
                                                crossSolution.pop_back();
                                                crossSolution.pop_back();
                                                break;
                                            }
                                            // using count as a signal to what to do next....
                                            count = -1;
                                            break;
                                        }
                                        // reverting the previour solution....
                                        if (twotimes == 0)
                                            setalgo(side, "F R FP", "null");
                                        else
                                            setalgo(side, "FP LP F", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        setalgo(side, "D", "crs");
                                    }
                                    if (count == -1)
                                        break;
                                }
                            }
                            // When two edges are correct...
                            else if (twocorrect == 2)
                            {
                                for (int twotimes{0}; twotimes < 2; twotimes++)
                                {
                                    for (int checkside{0}; checkside < 4; checkside++)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "F RP", "crs");
                                        else
                                            setalgo(side, "FP L", "crs");
                                        crossColorCount = count_bottom_lyr_edge(*this);
                                        if (crossColorCount == 2)
                                        {
                                            if (twotimes == 0)
                                                setalgo(side, "FP", "crs");
                                            else
                                                setalgo(side, "F", "crs");
                                            // using twoCorrect as a singnal.....
                                            twocorrect = -1;
                                        }
                                        else
                                            twocorrect = 0;
                                        crossColorCount = count_bottom_lyr_edge(*this);
                                        if (crossColorCount == 3)
                                        {
                                            // Verifying the current orientation...
                                            currentOrientation = move(get_cross_colors_orientation(*this));
                                            for (int i{0}; i < 4; i++)
                                            {
                                                count = 0;
                                                for (int j{0}; j < 4; j++)
                                                    if (currentOrientation[j] == mainOrientation[j])
                                                        count++;
                                                if (count >= 3)
                                                    break;
                                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                            }
                                            if (count >= 3)
                                                break;
                                        }
                                        // reverting the previour solution....
                                        if (twocorrect == -1)
                                        {
                                            if (twotimes == 0)
                                                setalgo(side, "F", "null");
                                            else
                                                setalgo(side, "FP", "null");
                                            crossSolution.pop_back();
                                        }
                                        if (twotimes == 0)
                                            setalgo(side, "R FP", "null");
                                        else
                                            setalgo(side, "LP F", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        setalgo(side, "D", "crs");
                                    }
                                    // this is for breaking the two times loop .....
                                    if (count >= 3)
                                        break;
                                }
                            }
                            // When only one edge is correct...
                            else
                            {
                                for (int twotimes{0}; twotimes < 2; twotimes++)
                                {
                                    for (int checkside{0}; checkside < 4; checkside++)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "F RP", "crs");
                                        else
                                            setalgo(side, "FP L", "crs");
                                        crossColorCount = count_bottom_lyr_edge(*this);
                                        if (crossColorCount <= 3)
                                        {
                                            // Verifying the current orientation...
                                            currentOrientation = move(get_cross_colors_orientation(*this));
                                            for (int i{0}; i < 4; i++)
                                            {
                                                count = 0;
                                                for (int j{0}; j < 4; j++)
                                                    if (currentOrientation[j] == mainOrientation[j])
                                                        count++;
                                                if (count >= 2)
                                                    break;
                                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                            }
                                            if (count >= 2)
                                                break;
                                        }
                                        // reverting the previour solution....
                                        if (twotimes == 0)
                                            setalgo(side, "R FP", "null");
                                        else
                                            setalgo(side, "LP F", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        setalgo(side, "D", "crs");
                                    }
                                    // this is for breaking the two times loop .....
                                    if (count >= 2)
                                        break;
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                    // this is for checking the right side edge....
                case 2:
                    if (cubeMain[side][1][2] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                        case 0:
                            setalgo(side, "RP", "crs");
                            break;
                        // one or two edges on the bottom
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 2)
                                    break;
                                else
                                    count = 1;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            limit = count + 1;
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side, "RP", "crs");
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation(*this));
                                    for (int i{0}; i < 4; i++)
                                    {
                                        count = 0;
                                        for (int j{0}; j < 4; j++)
                                            if (currentOrientation[j] == mainOrientation[j])
                                                count++;
                                        if (count >= limit)
                                            break;
                                        std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                    }
                                    if (count >= limit)
                                        break;
                                }
                                // reverting the previour solution....
                                setalgo(side, "R", "null");
                                crossSolution.pop_back();
                                setalgo(side, "D", "crs");
                            }
                            break;
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 3)
                                    break;
                                if (count >= 2)
                                    twocorrect = 2;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            // When three edges are correct...
                            if (count >= 3)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "RP", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount == 4)
                                    {
                                        break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "R", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            // When two edges are correct...
                            else if (twocorrect == 2)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "RP", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= 3)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= 3)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "R", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            // When one edge is correct...
                            else
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "RP", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount <= 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= 2)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= 2)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "R", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                    // this case is for checking the bottom side edge....
                case 3:
                    if (cubeMain[side][2][1] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                            // no edges on the bottom...
                        case 0:
                            crossColorCount = -1;
                            for (int two_t{0}; two_t < 2; two_t++)
                            {
                                sourceBackup = *this;
                                switch (two_t)
                                {
                                case 0:
                                    setalgo(side, "FP RP", "crs");
                                    break;
                                case 1:
                                    setalgo(side, "F L", "crs");
                                    break;
                                default:
                                    break;
                                }
                                sourceCpy = *this;
                                *this = sourceBackup;
                                sourceCpy.cross_solver(storeSolution);
                            }
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                // there is a flow in the below code and should be corrected...
                                if (count >= 2)
                                    break;
                                else
                                    count = 1;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            limit = count + 1;
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                switch (checkside)
                                {
                                case 0:
                                    setalgo(side, "FP D RP", "crs");
                                    break;
                                case 1:
                                    setalgo(side, "FP RP", "crs");
                                    break;
                                case 2:
                                    setalgo(side, "F D L", "crs");
                                    break;
                                case 3:
                                    setalgo(side, "F L", "crs");
                                    break;
                                default:
                                    break;
                                }
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation(*this));
                                    for (int i{0}; i < 4; i++)
                                    {
                                        count = 0;
                                        for (int j{0}; j < 4; j++)
                                            if (currentOrientation[j] == mainOrientation[j])
                                                count++;
                                        if (count >= limit)
                                            break;
                                        std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                    }
                                    if (count >= limit)
                                        break;
                                }
                                // reverting the previour solution....
                                switch (checkside)
                                {
                                case 0:
                                    setalgo(side, "R DP F", "null");
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    break;
                                case 1:
                                    setalgo(side, "R F", "null");
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    break;
                                case 2:
                                    setalgo(side, "LP DP FP", "null");
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    break;
                                case 3:
                                    setalgo(side, "LP FP", "null");
                                    crossSolution.pop_back();
                                    crossSolution.pop_back();
                                    break;
                                default:
                                    break;
                                }
                            }
                            break;
                            // three edges on the bottom...
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 3)
                                    break;
                                if (count >= 2)
                                    twocorrect = 2;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            // here the arising three conditions will be checked by count number........
                            // When three edges are correct...
                            if (count >= 3)
                            {
                                crossColorCount = -1;
                                for (int two_t{0}; two_t < 2; two_t++)
                                {
                                    sourceBackup = *this;
                                    switch (two_t)
                                    {
                                    case 0:
                                        setalgo(side, "FP D RP", "crs");
                                        break;
                                    case 1:
                                        setalgo(side, "F DP L", "crs");
                                        break;
                                    default:
                                        break;
                                    }
                                    sourceCpy = *this;
                                    *this = sourceBackup;
                                    sourceCpy.cross_solver(storeSolution);
                                }
                            }
                            // When two edges are correct...
                            else if (twocorrect == 2)
                            {
                                for (int checkside{0}; checkside < 3; checkside++)
                                {
                                    switch (checkside)
                                    {
                                    case 0:
                                        setalgo(side, "FP RP", "crs");
                                        break;
                                    case 1:
                                        setalgo(side, "F D L", "crs");
                                        break;
                                    case 2:
                                        setalgo(side, "F L", "crs");
                                        break;
                                    default:
                                        break;
                                    }
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= 3)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= 3)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    switch (checkside)
                                    {
                                    case 0:
                                        setalgo(side, "R F", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        break;
                                    case 1:
                                        setalgo(side, "LP DP FP", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        break;
                                    case 2:
                                        setalgo(side, "LP FP", "null");
                                        crossSolution.pop_back();
                                        crossSolution.pop_back();
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                            // When one edge is correct...
                            else
                            {
                                crossColorCount = -1;
                                for (int two_t{0}; two_t < 2; two_t++)
                                {
                                    sourceBackup = *this;
                                    switch (two_t)
                                    {
                                    case 0:
                                        setalgo(side, "F L", "crs");
                                        break;
                                    case 1:
                                        setalgo(side, "FP RP", "crs");
                                        break;
                                    default:
                                        break;
                                    }
                                    sourceCpy = *this;
                                    *this = sourceBackup;
                                    sourceCpy.cross_solver(storeSolution);
                                }
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                    // this is for checking the right side edge....
                case 4:
                    if (cubeMain[side][1][0] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                            // no edges on the bottom...
                        case 0:
                            setalgo(side, "L", "crs");
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 2)
                                    break;
                                else
                                    count = 1;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            limit = count + 1;
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side, "L", "crs");
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation(*this));
                                    for (int i{0}; i < 4; i++)
                                    {
                                        count = 0;
                                        for (int j{0}; j < 4; j++)
                                            if (currentOrientation[j] == mainOrientation[j])
                                                count++;
                                        if (count >= limit)
                                            break;
                                        std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                    }
                                    if (count >= limit)
                                        break;
                                }
                                // reverting the previour solution....
                                setalgo(side, "LP", "null");
                                crossSolution.pop_back();
                                setalgo(side, "D", "crs");
                            }
                            break;
                            // When three edges on the bottom...
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation(*this));
                            for (int i{0}; i < 4; i++)
                            {
                                count = 0;
                                for (int j{0}; j < 4; j++)
                                    if (currentOrientation[j] == mainOrientation[j])
                                        count++;
                                if (count >= 3)
                                    break;
                                if (count >= 2)
                                    twocorrect = 2;
                                std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                            }
                            // here the arising three conditions will be checked by count number........
                            // three correct edges...
                            if (count >= 3)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "L", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount == 4)
                                    {
                                        break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "LP", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            // two correct edges...
                            else if (twocorrect == 2)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "L", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= 3)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= 3)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "LP", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            // one edge correct...
                            else
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "L", "crs");
                                    crossColorCount = count_bottom_lyr_edge(*this);
                                    if (crossColorCount <= 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation(*this));
                                        for (int i{0}; i < 4; i++)
                                        {
                                            count = 0;
                                            for (int j{0}; j < 4; j++)
                                                if (currentOrientation[j] == mainOrientation[j])
                                                    count++;
                                            if (count >= 2)
                                                break;
                                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                        }
                                        if (count >= 2)
                                            break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "LP", "null");
                                    crossSolution.pop_back();
                                    setalgo(side, "D", "crs");
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else if (side == top)
            {
                int side_2{-1};
                switch (block)
                {
                case 1:
                    // this is for checking the face side edge....
                    if (cubeMain[side][2][1] == bottomColor)
                        side_2 = face;
                    break;
                case 2:
                    // this is for checking the right side edge....
                    if (cubeMain[side][1][2] == bottomColor)
                        side_2 = right;
                    break;
                case 3:
                    // this is for checking the back side edge....
                    if (cubeMain[side][0][1] == bottomColor)
                        side_2 = back;
                    break;
                case 4:
                    // this is for checking the left side edge....
                    if (cubeMain[side][1][0] == bottomColor)
                        side_2 = left;
                    break;
                default:
                    break;
                }
                if (side_2 != -1)
                {
                    switch (crossColorCount)
                    {
                        // no edges on the bottom...
                    case 0:
                        setalgo(side_2, "F2", "crs");
                        break;
                        // one or two edges on the bottom...
                    case 1:
                    case 2:
                        currentOrientation = move(get_cross_colors_orientation(*this));
                        for (int i{0}; i < 4; i++)
                        {
                            count = 0;
                            for (int j{0}; j < 4; j++)
                                if (currentOrientation[j] == mainOrientation[j])
                                    count++;
                            if (count >= 2)
                                break;
                            else
                                count = 1;
                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                        }
                        limit = count + 1;
                        for (int checkside{0}; checkside < 4; checkside++)
                        {
                            setalgo(side_2, "F2", "crs");
                            crossColorCount = count_bottom_lyr_edge(*this);
                            if (crossColorCount >= limit)
                            {
                                // Verifying the current orientation...
                                currentOrientation = move(get_cross_colors_orientation(*this));
                                for (int i{0}; i < 4; i++)
                                {
                                    count = 0;
                                    for (int j{0}; j < 4; j++)
                                        if (currentOrientation[j] == mainOrientation[j])
                                            count++;
                                    if (count >= limit)
                                        break;
                                    std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                }
                                if (count >= limit)
                                    break;
                            }
                            // reverting the previour solution....
                            setalgo(side_2, "F2", "null");
                            crossSolution.pop_back();
                            setalgo(side_2, "D", "crs");
                        }
                        break;
                        // three edges on the bottom...
                    case 3:
                        currentOrientation = move(get_cross_colors_orientation(*this));
                        for (int i{0}; i < 4; i++)
                        {
                            count = 0;
                            for (int j{0}; j < 4; j++)
                                if (currentOrientation[j] == mainOrientation[j])
                                    count++;
                            // there is a flow in the below code and should be corrected...
                            if (count >= 3)
                                break;
                            if (count >= 2)
                                twocorrect = 2;
                            std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                        }
                        // here the arising three conditions will be checked by count number........
                        // When three edges are correct...
                        if (count >= 3)
                        {
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side_2, "F2", "crs");
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount == 4)
                                {
                                    break;
                                }
                                // reverting the previour solution....
                                setalgo(side_2, "F2", "null");
                                crossSolution.pop_back();
                                setalgo(side_2, "D", "crs");
                            }
                        }
                        // When two edges are correct...
                        else if (twocorrect == 2)
                        {
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side_2, "F2", "crs");
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount == 3)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation(*this));
                                    for (int i{0}; i < 4; i++)
                                    {
                                        count = 0;
                                        for (int j{0}; j < 4; j++)
                                            if (currentOrientation[j] == mainOrientation[j])
                                                count++;
                                        if (count >= 3)
                                            break;
                                        std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                    }
                                    if (count >= 3)
                                        break;
                                }
                                // reverting the previour solution....
                                setalgo(side_2, "F2", "null");
                                crossSolution.pop_back();
                                setalgo(side_2, "D", "crs");
                            }
                        }
                        // one correct edge on the bottom...
                        else
                        {
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side_2, "F2", "crs");
                                crossColorCount = count_bottom_lyr_edge(*this);
                                if (crossColorCount <= 3)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation(*this));
                                    for (int i{0}; i < 4; i++)
                                    {
                                        count = 0;
                                        for (int j{0}; j < 4; j++)
                                            if (currentOrientation[j] == mainOrientation[j])
                                                count++;
                                        if (count >= 2)
                                            break;
                                        std::rotate(currentOrientation.begin(), currentOrientation.end() - 1, currentOrientation.end());
                                    }
                                    if (count >= 2)
                                        break;
                                }
                                // reverting the previour solution....
                                setalgo(side_2, "F2", "null");
                                crossSolution.pop_back();
                                setalgo(side_2, "D", "crs");
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            if (crossColorCount != -1)
            {
                sourceCpy = *this;
                *this = sourceBackup;
                sourceCpy.cross_solver(storeSolution);
            }
        }
    }
    // *this = ;
    // this->crossSolution = .crossSolution;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION COUNTS THE NUMBER OF BASE EDGES CURENTLY LOCATED AT THE BOTTOM...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
int solver::count_bottom_lyr_edge(const solver &src)
{
    int colorCount{0};
    if (src.cubeMain[bottom][0][1] == src.cubeMain[bottom][1][1])
        colorCount++;
    if (src.cubeMain[bottom][1][0] == src.cubeMain[bottom][1][1])
        colorCount++;
    if (src.cubeMain[bottom][1][2] == src.cubeMain[bottom][1][1])
        colorCount++;
    if (src.cubeMain[bottom][2][1] == src.cubeMain[bottom][1][1])
        colorCount++;
    return colorCount;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION THIS FUNCTION RETURNS THE MAIN ORIENTATION OF THE CROSS COLORS.....
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<char> solver::get_equator_colors_orientation(const solver &source)
{
    vector<char> crossColorOrientation{};
    crossColorOrientation.push_back(source.cubeMain[face][1][1]);
    crossColorOrientation.push_back(source.cubeMain[right][1][1]);
    crossColorOrientation.push_back(source.cubeMain[back][1][1]);
    crossColorOrientation.push_back(source.cubeMain[left][1][1]);
    return std::move(crossColorOrientation);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION THIS FUNCTION RETURNS THE CURRENT ORIENTATION OF THE CROSS EDGES ON THE BOTTOM...
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<char> solver::get_cross_colors_orientation(const solver &source)
{
    vector<char> baseCross{};
    if (source.cubeMain[bottom][0][1] == source.cubeMain[bottom][1][1])
        baseCross.push_back(source.cubeMain[face][2][1]);
    else
        baseCross.push_back('\0');
    if (source.cubeMain[bottom][1][2] == source.cubeMain[bottom][1][1])
        baseCross.push_back(source.cubeMain[right][2][1]);
    else
        baseCross.push_back('\0');
    if (source.cubeMain[bottom][2][1] == source.cubeMain[bottom][1][1])
        baseCross.push_back(source.cubeMain[back][2][1]);
    else
        baseCross.push_back('\0');
    if (source.cubeMain[bottom][1][0] == source.cubeMain[bottom][1][1])
        baseCross.push_back(source.cubeMain[left][2][1]);
    else
        baseCross.push_back('\0');
    return move(baseCross);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE F2L_LAYER OF THE RUBIX CUBE....
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::f2l_solver(solver &temp_cube)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rang0to1(0, 1);
    int side{}, sentinel{}, block{};
    const char bottomColor{cubeMain[bottom][1][1]};
    vector<int> incorrectF2lCorners{};
    bool cornerLocMatch{false}, boolEdgeSetter{false};

    // first f2l corner...
    if (cubeMain[bottom][1][1] != cubeMain[bottom][0][0] || cubeMain[face][1][1] != cubeMain[face][1][0] || cubeMain[face][1][1] != cubeMain[face][2][0] || cubeMain[left][1][1] != cubeMain[left][1][2] || cubeMain[left][1][1] != cubeMain[left][2][2])
        incorrectF2lCorners.push_back(1);
    // second f2l corner...
    if (cubeMain[bottom][1][1] != cubeMain[bottom][0][2] || cubeMain[face][1][1] != cubeMain[face][1][2] || cubeMain[face][1][1] != cubeMain[face][2][2] || cubeMain[right][1][1] != cubeMain[right][1][0] || cubeMain[right][1][1] != cubeMain[right][2][0])
        incorrectF2lCorners.push_back(2);
    // third f2l corner...
    if (cubeMain[bottom][1][1] != cubeMain[bottom][2][0] || cubeMain[back][1][1] != cubeMain[back][1][2] || cubeMain[back][1][1] != cubeMain[back][2][2] || cubeMain[left][1][1] != cubeMain[left][1][0] || cubeMain[left][1][1] != cubeMain[left][2][0])
        incorrectF2lCorners.push_back(3);
    // fourth f2l corner...
    if (cubeMain[bottom][1][1] != cubeMain[bottom][2][2] || cubeMain[back][1][1] != cubeMain[back][1][0] || cubeMain[back][1][1] != cubeMain[back][2][0] || cubeMain[right][1][1] != cubeMain[right][1][2] || cubeMain[right][1][1] != cubeMain[right][2][2])
        incorrectF2lCorners.push_back(4);

    if (incorrectF2lCorners.size() == 0) // IT WILL WORK IF THE CUBE IS SOLVED....
    {
        solution_optimizer(f2lSolution); // Optimising f2lSolution....
        oll_solver();
        pll_solver();
        correct_last_layer();
        temp_cube.f2lSolutions.push_back(f2lSolution);
        temp_cube.ollSolutions.push_back(ollSolution);
        temp_cube.pllSolutions.push_back(pllSolution);
        trials++;
        std::cout << "\r" << RED << trials << DEFAULT << " TIMES CUBE SOLVED...";
    }
    else
    {
        solver sourceBackup, sourceCpy;
        for (size_t i{0}; i < incorrectF2lCorners.size(); i++)
        {
            cornerColors.clear();
            switch (incorrectF2lCorners.at(i))
            {
            case 1:
                cornerColors.push_back(cubeMain[face][1][1]);
                cornerColors.push_back(cubeMain[left][1][1]);
                break;
            case 2:
                cornerColors.push_back(cubeMain[face][1][1]);
                cornerColors.push_back(cubeMain[right][1][1]);
                break;
            case 3:
                cornerColors.push_back(cubeMain[back][1][1]);
                cornerColors.push_back(cubeMain[left][1][1]);
                break;
            case 4:
                cornerColors.push_back(cubeMain[back][1][1]);
                cornerColors.push_back(cubeMain[right][1][1]);
                break;
            default:
                break;
            }
            sourceBackup = *this;
            if (!get_corner_location(cornerColors.at(0), cornerColors.at(1), side, block))
                cerr << "error finding coordinate...." << endl;
            // -------------------------------------------------- BOTTOM SIDE ---------------------------------------------------------------
            if (side == bottom)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        if (cornerLocMatch)
                        {
                            // for optimization purposes....
                            boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == left)
                                {
                                    setalgo(left, "U R UP RP UP FP U F", "f2l");
                                }
                                else if (edgeSide == face)
                                {
                                    setalgo(left, "UP FP U F U R UP RP", "f2l");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(left, "R UP R2 U2 R UP FP U F", "f2l");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    };
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == face)
                                {
                                    setalgo(face, "U R UP RP UP FP U F", "f2l");
                                }
                                else if (edgeSide == right)
                                {
                                    setalgo(face, "UP FP U F U R UP RP", "f2l");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(face, "R UP R2 U2 R UP FP U F", "f2l");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == back)
                                {
                                    setalgo(back, "U R UP RP UP FP U F", "f2l");
                                }
                                else if (edgeSide == left)
                                {
                                    setalgo(back, "UP FP U F U R UP RP", "f2l");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(back, "R UP R2 U2 R UP FP U F", "f2l");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == right)
                                {
                                    setalgo(right, "U R UP RP UP FP U F", "f2l");
                                }
                                else if (edgeSide == back)
                                {
                                    setalgo(right, "UP FP U F U R UP RP", "f2l");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(right, "R UP R2 U2 R UP FP U F", "f2l");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            // -------------------------------------------------- FACE SIDE ---------------------------------------------------------------
            else if (side == face)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "U FP U F U FP U2 F", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "U FP UP F UP R U RP", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R UP RP U2 FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "UP R UP RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U FP U2 F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U FP UP F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "UP R U RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "F RP FP R", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "U FP U2 F UP R U RP", "f2l");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "UP R UP RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "UP R U RP U FP UP F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP U F U2 R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "U FP U F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "UP R U2 RP U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP R U RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "U FP UP F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP R U2 RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R UP RP U R U2 RP U R UP RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R U RP UP R UP RP U2 FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == face)
                            {
                                setalgo(left, "R U RP UP R U RP", "f2l");
                            }
                            else if (edgeSide == left)
                            {
                                setalgo(left, "FP U F UP FP U F", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R UP RP UP R U RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R UP RP U FP UP F UP FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == face)
                            {
                                setalgo(face, "FP UP F U FP UP F", "f2l");
                            }
                            else if (edgeSide == right)
                            {
                                setalgo(face, "R UP RP U R UP RP", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            // -------------------------------------------------- RIGHT SIDE ---------------------------------------------------------------
            else if (side == right)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "U FP U F U FP U2 F", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "U FP UP F UP R U RP", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "R UP RP U2 FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "UP R UP RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U FP U2 F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U FP UP F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "UP R U RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "F RP FP R", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "U FP U2 F UP R U RP", "f2l");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "UP R UP RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "UP R U RP U FP UP F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "FP U F U2 R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "U FP U F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "UP R U2 RP U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "UP R U RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "U FP UP F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "UP R U2 RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R UP RP U R U2 RP U R UP RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R U RP UP R UP RP U2 FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == right)
                            {
                                setalgo(face, "R U RP UP R U RP", "f2l");
                            }
                            else if (edgeSide == face)
                            {
                                setalgo(face, "FP U F UP FP U F", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R UP RP UP R U RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R UP RP U FP UP F UP FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == right)
                            {
                                setalgo(right, "FP UP F U FP UP F", "f2l");
                            }
                            else if (edgeSide == back)
                            {
                                setalgo(right, "R UP RP U R UP RP", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            // -------------------------------------------------- BACK SIDE ---------------------------------------------------------------
            else if (side == back)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "U FP U F U FP U2 F", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "U FP UP F UP R U RP", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R UP RP U2 FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "UP R UP RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U FP U2 F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U FP UP F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "UP R U RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "F RP FP R", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "U FP U2 F UP R U RP", "f2l");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "UP R UP RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "UP R U RP U FP UP F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP U F U2 R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "U FP U F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "UP R U2 RP U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP R U RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "U FP UP F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP R U2 RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R UP RP U R U2 RP U R UP RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R U RP UP R UP RP U2 FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == back)
                            {
                                setalgo(right, "R U RP UP R U RP", "f2l");
                            }
                            else if (edgeSide == right)
                            {
                                setalgo(right, "FP U F UP FP U F", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R UP RP UP R U RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R UP RP U FP UP F UP FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == back)
                            {
                                setalgo(back, "FP UP F U FP UP F", "f2l");
                            }
                            else if (edgeSide == left)
                            {
                                setalgo(back, "R UP RP U R UP RP", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            // -------------------------------------------------- LEFT SIDE ---------------------------------------------------------------
            else if (side == left)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "U FP U F U FP U2 F", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "U FP UP F UP R U RP", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "R UP RP U2 FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "UP R UP RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U FP U2 F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U FP UP F U FP U2 F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "UP R U RP U R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "F RP FP R", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "U FP U2 F UP R U RP", "f2l");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "UP R UP RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "UP R U RP U FP UP F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "FP U F U2 R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "U FP U F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "UP R U2 RP U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "UP R U RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "U FP UP F UP FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "UP R U2 RP UP R U2 RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R UP RP U R U2 RP U R UP RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R U RP UP R UP RP U2 FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == left)
                            {
                                setalgo(back, "R U RP UP R U RP", "f2l");
                            }
                            else if (edgeSide == back)
                            {
                                setalgo(back, "FP U F UP FP U F", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R UP RP UP R U RP UP R U2 RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R UP RP U FP UP F UP FP UP F", "f2l");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == left)
                            {
                                setalgo(left, "FP UP F U FP UP F", "f2l");
                            }
                            else if (edgeSide == face)
                            {
                                setalgo(left, "R UP RP U R UP RP", "f2l");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F", "f2l");
                                set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            // -------------------------------------------------- TOP SIDE ---------------------------------------------------------------
            else if (side == top)
            {
                switch (block)
                {
                case 1:
                    if (cubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R U RP UP R U RP UP R U RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R UP RP U FP U F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U2 FP UP F UP FP U F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "U R U2 RP U R UP RP", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP FP U2 F UP FP U F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "U2 R U RP U R UP RP", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP U2 F U FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "R U RP U2 R U RP UP R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP UP F U2 FP UP F U FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(back, "R U2 RP UP R U RP", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (cubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R U RP UP R U RP UP R U RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R UP RP U FP U F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U R U2 RP U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "U2 FP UP F UP FP U F", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U2 R U RP U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "UP FP U2 F UP FP U F", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R U RP U2 R U RP UP R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "FP U2 F U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R U2 RP UP R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(right, "FP UP F U2 FP UP F U FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (cubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R U RP UP R U RP UP R U RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R UP RP U FP U F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U R U2 RP U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "U2 FP UP F UP FP U F", "f2l");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U2 R U RP U R UP RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "UP FP U2 F UP FP U F", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R U RP U2 R U RP UP R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "FP U2 F U FP UP F", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R U2 RP UP R U RP", "f2l");
                                }
                                else
                                {
                                    setalgo(left, "FP UP F U2 FP UP F U FP UP F", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 4:
                    if (cubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R U RP UP R U RP UP R U RP", "f2l");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R UP RP U FP U F", "f2l");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U2 FP UP F UP FP U F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "U R U2 RP U R UP RP", "f2l");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP FP U2 F UP FP U F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "U2 R U RP U R UP RP", "f2l");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP U2 F U FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "R U RP U2 R U RP UP R U RP", "f2l");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP UP F U2 FP UP F U FP UP F", "f2l");
                                }
                                else
                                {
                                    setalgo(face, "R U2 RP UP R U RP", "f2l");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            sourceCpy = *this;
            *this = sourceBackup;
            sourceCpy.f2l_solver(temp_cube);
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE OLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE OLL CONDITIONS WILL MATCHES AND SOLVES THE OLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::oll_solver()
{
    ollSolution.clear();
    bool solve{false};
    string OLLcode{};
    OLLcode = oll_coder();
    for (int i{0}; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            solve = oll_logic(face, OLLcode);
            if (solve == false)
            {
                U;
            }
            break;
        case 1:
            UP;
            solve = oll_logic(right, OLLcode);
            if (solve == false)
            {
                U;
                U;
            }
            break;
        case 2:
            U;
            U;
            solve = oll_logic(back, OLLcode);
            if (solve == false)
            {
                UP;
            }
            break;
        case 3:
            U;
            solve = oll_logic(left, OLLcode);
            break;
        default:
            break;
        }
        if (solve == true)
        {
            solution_optimizer(ollSolution);
            return;
        }
        OLLcode = oll_coder();
    }
    cerr << "error solving Oll layer...." << endl;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE PLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE PLL CONDITIONS WILL MATCHES AND SOLVES THE PLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::pll_solver()
{
    pllSolution.clear();
    bool solve{false};
    string PLLcode{};
    vector<char> orientation = get_equator_colors_orientation(*this);
    for (int ornt_chng{0}; ornt_chng < 4; ornt_chng++)
    {
        PLLcode = pll_coder(orientation);
        for (int rotate{0}; rotate < 4; rotate++)
        {
            switch (rotate)
            {
            case 0:
                solve = pll_logic(face, PLLcode);
                if (solve == false)
                    U;
                break;
            case 1:
                UP;
                solve = pll_logic(right, PLLcode);
                if (solve == false)
                    U2;
                break;
            case 2:
                U2;
                solve = pll_logic(back, PLLcode);
                if (solve == false)
                    UP;
                break;
            case 3:
                U;
                solve = pll_logic(left, PLLcode);
                break;
            default:
                break;
            }
            if (solve == true)
            {
                solution_optimizer(pllSolution);
                return;
            }
            PLLcode = pll_coder(orientation);
        }
        // changing the orientation...
        std::rotate(orientation.begin(), orientation.end() - 1, orientation.end());
    }
    cerr << "error solving Pll layer...." << endl;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CODES THE PLL LAYER IN 0, 1, 2, 3 IN RESPECT TO THEIR COLOR ORIENTATION CHARACTER.
   THE FIRST THREE CHAR IS FOR FIRST ROW OF FACE AND
   THE OTHER THREE CHAR IS FOR FIRST ROW OF RIGHT AND
   THE OTHER THREE CHAR IS FOR FIRST ROW OF BACK AND
   THE LAST THREE CHARACHTER IS FOR FIRST ROW OF LEFT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string solver::pll_coder(const vector<char> &orientation)
{
    string PLLcode{};
    // CODING FIRST ROW OF FACE SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[face][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF RIGHT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[right][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF BACK SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[back][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF LEFT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[left][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    return PLLcode;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION HAVE SOLUTION FOR ALL THE CONDITIONS POSSIBLE IN PLL
   LAYER AND IT DIRECTLY CALLS THE SETALGO TO APPLY THE CONDITION.
   IT RETURNS TRUE IF THE CONDITION MATCHES THE CODE AND FALSE WHEN PLLCODE DOSEN'T MATCHES ANY CONDITION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::pll_logic(const int &side, string_view PLLcode)
{
    if (PLLcode == "000111222333")
        return true;
    // A-PERMS..
    else if (PLLcode == "001212320133")
        setalgo(side, "R2 B2 R F RP B2 R FP R", "pll");
    else if (PLLcode == "300113021232")
        setalgo(side, "L2 B2 LP FP L B2 LP F LP", "pll");
    // U-PERMS.
    else if (PLLcode == "030101222313")
        setalgo(side, "R2 U R U RP UP RP UP RP U RP", "pll");
    else if (PLLcode == "010131222303")
        setalgo(side, "R UP R U R U R UP RP UP R2", "pll");
    // H-PERM..
    else if (PLLcode == "020131202313")
        setalgo(side, "M2 U M2 U2 M2 U M2", "pll");
    // T-PERM..
    else if (PLLcode == "001230122313")
        setalgo(side, "R U RP UP RP F R2 UP RP UP R U RP FP", "pll");
    // J-PERMS..
    else if (PLLcode == "000112331223")
        setalgo(side, "RP U LP U2 R UP RP U2 R L UP", "pll");
    else if (PLLcode == "011200122333")
        setalgo(side, "R U RP FP R U RP UP RP F R2 UP RP UP", "pll");
    // R-PERMS...
    else if (PLLcode == "030112321203")
        setalgo(side, "L U2 LP U2 L FP LP UP L U L F L2 U", "pll");
    else if (PLLcode == "010102321233")
        setalgo(side, "RP U2 R U2 RP F R U RP UP RP FP R2 UP", "pll");
    // V-PERM...
    else if (PLLcode == "002321210133")
        setalgo(side, "RP U RP UP BP RP B2 UP BP U BP R B R", "pll");
    // G-PERMS...
    else if (PLLcode == "300123031212")
        setalgo(side, "R2 D BP U BP UP B DP R2 FP U F", "pll");
    else if (PLLcode == "132311203020")
        setalgo(side, "RP UP R B2 D LP U L UP L DP B2", "pll");
    else if (PLLcode == "132301223010")
        setalgo(side, "R2 DP F UP F U FP D R2 B UP BP", "pll");
    else if (PLLcode == "320113031202")
        setalgo(side, "R U RP F2 DP L UP LP U LP D F2", "pll");
    // F-PERM...
    else if (PLLcode == "103031222310")
        setalgo(side, "RP U2 RP UP BP RP B2 UP BP U BP R B UP R", "pll");
    // Z-PERM...
    else if (PLLcode == "010101232323")
        setalgo(side, "M2 U M2 U MP U2 M2 U2 MP U2", "pll");
    // Y-PERM...
    else if (PLLcode == "002311230123")
        setalgo(side, "F R UP RP UP R U RP FP R U RP UP RP F R FP", "pll");
    // N-PERMS...
    else if (PLLcode == "022311200133")
        setalgo(side, "L UP R U2 LP U RP L UP R U2 LP U RP U", "pll");
    else if (PLLcode == "220113002331")
        setalgo(side, "RP U LP U2 R UP L RP U LP U2 R UP L UP", "pll");
    // E-PERM...
    else if (PLLcode == "301210123032")
        setalgo(side, "R BP RP F R B RP F2 LP B L F LP BP L", "pll");
    else
        return false;
    return true;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE PARTNER SIDE OF THE WHITE CORNER TO THE CORNERCOLORS VECTOR AND CHECKS IF IT IS ON THE RIGHT LOCATION.
   IF IT SI THAN IT RETURNS TRUE ELSE RETURNS FALSE.
      -> PRIORITIES FOR SAVING THE CORNER COLORS ARE -:
        * TOP AND BOTTOM
        * FACE BACK
        * LEFT AND RIGHT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::find_corner_colors(const char &bottomColor, const int &side, const int &row, const int &col)
{
    cornerColors.clear();
    vector<int> sideloc;
    if ((side == face && row == 0 && col == 2) ||
        (side == top && row == 2 && col == 2) ||
        (side == right && row == 0 && col == 0))
    {
        sideloc.push_back(face);
        sideloc.push_back(top);
        sideloc.push_back(right);
        if (cubeMain[top][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[top][2][2]);
        ;
        if (cubeMain[face][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[face][0][2]);
        ;
        if (cubeMain[right][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[right][0][0]);
        ;
    }
    else if ((side == face && row == 0 && col == 0) ||
             (side == top && row == 2 && col == 0) ||
             (side == left && row == 0 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (cubeMain[top][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[top][2][0]);
        ;
        if (cubeMain[face][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[face][0][0]);
        ;
        if (cubeMain[left][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[left][0][2]);
        ;
    }
    else if ((side == left && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 0) ||
             (side == back && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (cubeMain[top][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[top][0][0]);
        ;
        if (cubeMain[back][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[back][0][2]);
        ;
        if (cubeMain[left][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[left][0][0]);
        ;
    }
    else if ((side == back && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 2) ||
             (side == right && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(right);
        if (cubeMain[top][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[top][0][2]);
        ;
        if (cubeMain[back][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[back][0][0]);
        ;
        if (cubeMain[right][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[right][0][2]);
        ;
    }
    // bottom corners...
    else if ((side == face && row == 2 && col == 2) ||
             (side == bottom && row == 0 && col == 2) ||
             (side == right && row == 2 && col == 0))
    {
        sideloc.push_back(face);
        sideloc.push_back(bottom);
        sideloc.push_back(right);
        if (cubeMain[bottom][0][2] != bottomColor)
            cornerColors.push_back(cubeMain[bottom][0][2]);
        ;
        if (cubeMain[face][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[face][2][2]);
        ;
        if (cubeMain[right][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[right][2][0]);
        ;
    }
    else if ((side == face && row == 2 && col == 0) ||
             (side == bottom && row == 0 && col == 0) ||
             (side == left && row == 2 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(bottom);
        sideloc.push_back(left);
        if (cubeMain[bottom][0][0] != bottomColor)
            cornerColors.push_back(cubeMain[bottom][0][0]);
        ;
        if (cubeMain[face][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[face][2][0]);
        ;
        if (cubeMain[left][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[left][2][2]);
        ;
    }
    else if ((side == left && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 0) ||
             (side == back && row == 2 && col == 2))
    {
        sideloc.push_back(left);
        sideloc.push_back(bottom);
        sideloc.push_back(back);
        if (cubeMain[bottom][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[bottom][2][0]);
        ;
        if (cubeMain[back][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[back][2][2]);
        ;
        if (cubeMain[left][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[left][2][0]);
        ;
    }
    else if ((side == back && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 2) ||
             (side == right && row == 2 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(bottom);
        sideloc.push_back(right);
        if (cubeMain[bottom][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[bottom][2][2]);
        ;
        if (cubeMain[back][2][0] != bottomColor)
            cornerColors.push_back(cubeMain[back][2][0]);
        ;
        if (cubeMain[right][2][2] != bottomColor)
            cornerColors.push_back(cubeMain[right][2][2]);
        ;
    }
    // the bellow code checks the corner is on the right location or not......
    int x{0};
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[sideloc.at(i)][1][1] == cornerColors.at(0) || cubeMain[sideloc.at(i)][1][1] == cornerColors.at(1))
            x++;
    }
    if (x == 2)
        return true;
    else
        return false;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE LOCATION OF THE BOTTOM COLOR CORNER ON THE BASIS OF THE CORESPONDING COLORS PROVIDED...
   IT SAVES THE SIDE AND BLOCK OF THE CORNER..
   AND RETURNS TRUE IF IT FINDS THE CORNER..
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::get_corner_location(const char &color_1, const char &color_2, int &side, int &block)
{
    vector<char> colors{color_1, color_2, cubeMain[bottom][1][1]};
    int count{0};
    // first corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[face][0][2] == colors[i] ||
            cubeMain[top][2][2] == colors[i] ||
            cubeMain[right][0][0] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[face][0][2] == colors[i])
            {
                side = face;
                block = 2;
            }
            else if (cubeMain[top][2][2] == colors[i])
            {
                side = top;
                block = 4;
            }
            else if (cubeMain[right][0][0] == colors[i])
            {
                side = right;
                block = 1;
            }
            return true;
        }
    }
    // second corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[face][0][0] == colors[i] ||
            cubeMain[top][2][0] == colors[i] ||
            cubeMain[left][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[face][0][0] == colors[i])
            {
                side = face;
                block = 1;
            }
            else if (cubeMain[top][2][0] == colors[i])
            {
                side = top;
                block = 3;
            }
            else if (cubeMain[left][0][2] == colors[i])
            {
                side = left;
                block = 2;
            }
            return true;
        }
    }
    // third corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[left][0][0] == colors[i] ||
            cubeMain[top][0][0] == colors[i] ||
            cubeMain[back][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[left][0][0] == colors[i])
            {
                side = left;
                block = 1;
            }
            else if (cubeMain[top][0][0] == colors[i])
            {
                side = top;
                block = 1;
            }
            else if (cubeMain[back][0][2] == colors[i])
            {
                side = back;
                block = 2;
            }
            return true;
        }
    }
    // fourth corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[back][0][0] == colors[i] ||
            cubeMain[top][0][2] == colors[i] ||
            cubeMain[right][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[back][0][0] == colors[i])
            {
                side = back;
                block = 1;
            }
            else if (cubeMain[top][0][2] == colors[i])
            {
                side = top;
                block = 2;
            }
            else if (cubeMain[right][0][2] == colors[i])
            {
                side = right;
                block = 2;
            }
            return true;
        }
    }
    // fifth corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[face][2][2] == colors[i] ||
            cubeMain[bottom][0][2] == colors[i] ||
            cubeMain[right][2][0] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[face][2][2] == colors[i])
            {
                side = face;
                block = 4;
            }
            else if (cubeMain[bottom][0][2] == colors[i])
            {
                side = bottom;
                block = 2;
            }
            else if (cubeMain[right][2][0] == colors[i])
            {
                side = right;
                block = 3;
            }
            return true;
        }
    }
    // sixth corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[face][2][0] == colors[i] ||
            cubeMain[bottom][0][0] == colors[i] ||
            cubeMain[left][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[face][2][0] == colors[i])
            {
                side = face;
                block = 3;
            }
            else if (cubeMain[bottom][0][0] == colors[i])
            {
                side = bottom;
                block = 1;
            }
            else if (cubeMain[left][2][2] == colors[i])
            {
                side = left;
                block = 4;
            }
            return true;
        }
    }
    // seventh corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[left][2][0] == colors[i] ||
            cubeMain[bottom][2][0] == colors[i] ||
            cubeMain[back][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[left][2][0] == colors[i])
            {
                side = left;
                block = 3;
            }
            else if (cubeMain[bottom][2][0] == colors[i])
            {
                side = bottom;
                block = 3;
            }
            else if (cubeMain[back][2][2] == colors[i])
            {
                side = back;
                block = 4;
            }
            return true;
        }
    }
    // eighth corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain[back][2][0] == colors[i] ||
            cubeMain[bottom][2][2] == colors[i] ||
            cubeMain[right][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (cubeMain[back][2][0] == colors[i])
            {
                side = back;
                block = 3;
            }
            else if (cubeMain[bottom][2][2] == colors[i])
            {
                side = bottom;
                block = 4;
            }
            else if (cubeMain[right][2][2] == colors[i])
            {
                side = right;
                block = 4;
            }
            return true;
        }
    }
    return false;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE LOCATION OF THE BOTTOM COLOR EDGE ON THE BASIS OF THE CORESPONDING COLOR PROVIDED...
   IT SAVES THE SIDE AND BLOCK OF THE EDGE..
   AND RETURNS TRUE IF IT FINDS THE EDGE..
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::get_edge_location(const char &color_1, int &side, int &block)
{
    int count{0};
    vector<char> colors{color_1, cubeMain[bottom][1][1]};
    // BELLOW FOUR ARE TOP SIDE EDGES....
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[top][2][1] == colors[i] || cubeMain[face][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[top][2][1] == colors[i])
            {
                side = top;
                block = 1;
            }
            else if (cubeMain[face][0][1] == colors[i])
            {
                side = face;
                block = 1;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[top][1][2] == colors[i] || cubeMain[right][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[top][1][2] == colors[i])
            {
                side = top;
                block = 2;
            }
            else if (cubeMain[right][0][1] == colors[i])
            {
                side = right;
                block = 1;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[top][0][1] == colors[i] || cubeMain[back][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[top][0][1] == colors[i])
            {
                side = top;
                block = 3;
            }
            else if (cubeMain[back][0][1] == colors[i])
            {
                side = back;
                block = 1;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[top][1][0] == colors[i] || cubeMain[left][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[top][1][0] == colors[i])
            {
                side = top;
                block = 4;
            }
            else if (cubeMain[left][0][1] == colors[i])
            {
                side = left;
                block = 1;
            }
            return true;
        }
    }
    // BELLOW FOUR ARE BOTTOM SIDE EDGES....
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[bottom][0][1] == colors[i] || cubeMain[face][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[face][2][1] == colors[i])
            {
                side = face;
                block = 3;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[bottom][1][2] == colors[i] || cubeMain[right][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[right][2][1] == colors[i])
            {
                side = right;
                block = 3;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[bottom][2][1] == colors[i] || cubeMain[back][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[back][2][1] == colors[i])
            {
                side = back;
                block = 3;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[bottom][1][0] == colors[i] || cubeMain[left][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[left][2][1] == colors[i])
            {
                side = left;
                block = 3;
            }
            return true;
        }
    }
    // BELLOW FOUR ARE MIDDLE SIDE EDGES....
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[face][1][2] == colors[i] || cubeMain[right][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[face][1][2] == colors[i])
            {
                side = face;
                block = 2;
            }
            else if (cubeMain[right][1][0] == colors[i])
            {
                side = right;
                block = 4;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[right][1][2] == colors[i] || cubeMain[back][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[right][1][2] == colors[i])
            {
                side = right;
                block = 2;
            }
            else if (cubeMain[back][1][0] == colors[i])
            {
                side = back;
                block = 4;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[back][1][2] == colors[i] || cubeMain[left][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[back][1][2] == colors[i])
            {
                side = back;
                block = 2;
            }
            else if (cubeMain[left][1][0] == colors[i])
            {
                side = left;
                block = 4;
            }
            return true;
        }
    }
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (cubeMain[left][1][2] == colors[i] || cubeMain[face][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (cubeMain[left][1][2] == colors[i])
            {
                side = left;
                block = 2;
            }
            else if (cubeMain[face][1][0] == colors[i])
            {
                side = face;
                block = 4;
            }
            return true;
        }
    }
    return false;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CHECKS IF THE SIDE ELEMENT IS ON THE TOP OF THE CUBE IF IT IS IT RERURNS "TRUE" ELSE IT RETURNS "FALSE".
   IF THE EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT MOVES THE SIDE EDGE TO THE CORRECT LOCATION, ELSE LET IT STAY ON THE SAME LOCATION
   AND MAKES TOPSIDECOLOR === "THE COLOR IN THE TOP OF SIDE ELEMENT"
   AND EDGESIDE === "TO THE SIDE OF TEH EDGE ELEMENT ON THE CUBE"
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::find_edge_in_top_lyr(solver &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter)
{
    if (edgeSetter == "CALL_EDGE_SETTER")
        temp_cube = *this;
    bool pos{false};
    int moveCount{0};
    // the bellow two assignment is for the precaution of removing past assignments....
    edgeSide = -1;
    topSideColor = 'x';
    while (!pos)
    {
        if (temp_cube.cubeMain[face][0][1] == color_1 && temp_cube.cubeMain[top][2][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[face][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = face;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top][1][2] == color_2 && temp_cube.cubeMain[right][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[right][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = right;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top][1][0] == color_2 && temp_cube.cubeMain[left][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[left][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = left;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top][0][1] == color_2 && temp_cube.cubeMain[back][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[back][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = back;
            topSideColor = color_2;
        }
        // if second color is not on the face.....
        else if (temp_cube.cubeMain[face][0][1] == color_2 && temp_cube.cubeMain[top][2][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[face][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = face;
            topSideColor = color_1;
        }
        else if (temp_cube.cubeMain[top][1][2] == color_1 && temp_cube.cubeMain[right][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[right][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = right;
            topSideColor = color_1;
        }
        else if (temp_cube.cubeMain[top][1][0] == color_1 && temp_cube.cubeMain[left][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[left][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = left;
            topSideColor = color_1;
        }
        // back side edges
        else if (temp_cube.cubeMain[top][0][1] == color_1 && temp_cube.cubeMain[back][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[back][1][1])
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = back;
            topSideColor = color_1;
        };
        // this block is for stoping the loop from running infinite times...
        if (moveCount == 0)
        {
            pos = true;
        }
    }
    // IF MOVECOUNT IS 3 IT IS GOING TO APPLY U-PRIME ELSE IN OTHER TWO CONDITIONS (2,1) IT IS GOING TO APPLY SIMPLE U OPERATIONS.....
    switch (moveCount)
    {
    case 3:
        this->tempSolution.push_back("UP");
        break;
    case 2:
        this->tempSolution.push_back("U");
        this->tempSolution.push_back("U");
        break;
    case 1:
        this->tempSolution.push_back("U");
        break;
    default:
        break;
    }
    applySolution("f2l");
    if (edgeSide == -1)
    {
        return false;
    }
    return true;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
THIS FUNCTION SIMPLY MOVES THE CORNER ELEMENT TO THE CORRECT LOCATION, IF IT IS ON THE TOP SIDE OF THE CUBE
   AND IF F2LHELPER === "CALL_F2LHELPER" THAN IT WILL CALL THE REQUIRED SIDE OF F2LHELPER FUNCTION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::set_corner_on_top(solver &temp_cube, const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper)
{
    temp_cube = *this;
    vector<char> colors{color_2, color_3};
    int colorCount{0}, moveCount{0}, side{-1}, colorBlock{-1};
    bool pos{false};
    while (!pos)
    {
        colorCount = 0;
        //--------------------- ifs for TOP , FACE AND RIGHT ANGLED CORNER ---------------------
        if (temp_cube.cubeMain[top][2][2] == color_1 && temp_cube.cubeMain[face][0][2] == color_2 && temp_cube.cubeMain[right][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 4;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][2] == color_3 && temp_cube.cubeMain[face][0][2] == color_1 && temp_cube.cubeMain[right][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][2] == color_2 && temp_cube.cubeMain[face][0][2] == color_3 && temp_cube.cubeMain[right][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][2] == color_3 && temp_cube.cubeMain[face][0][2] == color_2 && temp_cube.cubeMain[right][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][2] == color_1 && temp_cube.cubeMain[face][0][2] == color_3 && temp_cube.cubeMain[right][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 4;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][2] == color_2 && temp_cube.cubeMain[face][0][2] == color_1 && temp_cube.cubeMain[right][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , BACK AND RIGHT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top][0][2] == color_1 && temp_cube.cubeMain[back][0][0] == color_2 && temp_cube.cubeMain[right][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][2] == color_3 && temp_cube.cubeMain[back][0][0] == color_1 && temp_cube.cubeMain[right][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][2] == color_2 && temp_cube.cubeMain[back][0][0] == color_3 && temp_cube.cubeMain[right][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][2] == color_3 && temp_cube.cubeMain[back][0][0] == color_2 && temp_cube.cubeMain[right][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][2] == color_1 && temp_cube.cubeMain[back][0][0] == color_3 && temp_cube.cubeMain[right][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][2] == color_2 && temp_cube.cubeMain[back][0][0] == color_1 && temp_cube.cubeMain[right][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[right][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , BACK AND LEFT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top][0][0] == color_1 && temp_cube.cubeMain[back][0][2] == color_2 && temp_cube.cubeMain[left][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][0] == color_3 && temp_cube.cubeMain[back][0][2] == color_1 && temp_cube.cubeMain[left][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][0] == color_2 && temp_cube.cubeMain[back][0][2] == color_3 && temp_cube.cubeMain[left][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][0] == color_3 && temp_cube.cubeMain[back][0][2] == color_2 && temp_cube.cubeMain[left][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][0] == color_1 && temp_cube.cubeMain[back][0][2] == color_3 && temp_cube.cubeMain[left][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][0][0] == color_2 && temp_cube.cubeMain[back][0][2] == color_1 && temp_cube.cubeMain[left][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , FACE AND LEFT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top][2][0] == color_1 && temp_cube.cubeMain[face][0][0] == color_2 && temp_cube.cubeMain[left][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 3;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][0] == color_3 && temp_cube.cubeMain[face][0][0] == color_1 && temp_cube.cubeMain[left][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][0] == color_2 && temp_cube.cubeMain[face][0][0] == color_3 && temp_cube.cubeMain[left][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][0] == color_3 && temp_cube.cubeMain[face][0][0] == color_2 && temp_cube.cubeMain[left][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][0] == color_1 && temp_cube.cubeMain[face][0][0] == color_3 && temp_cube.cubeMain[left][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 3;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top][2][0] == color_2 && temp_cube.cubeMain[face][0][0] == color_1 && temp_cube.cubeMain[left][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face][1][1] == colors[i] || temp_cube.cubeMain[left][1][1] == colors[i])
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        if (moveCount == 0)
        {
            pos = true;
        }
    }

    switch (moveCount)
    {
    case 3:
        this->tempSolution.push_back("UP");
        break;
    case 2:
        this->tempSolution.push_back("U");
        this->tempSolution.push_back("U");
        break;
    case 1:
        this->tempSolution.push_back("U");
        break;
    default:
        break;
    }
    applySolution("f2l");
    f2LHelper(temp_cube, side, colorBlock);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHECKS FOR THE EDGE ELEMENTS IN THE MID LAYER OF THE CUBE.
   AND IF THE EDGE IN ON THE CORRECT LOCATION THAN IT RETURNS "1"
   ELSE IF THE EDGE IN ON THE CORRECT LOCATION BUT IN REVER DIRECTION THAN IT RETURN "0"
   ELSE IF EDGE IS IN NEAR LOCATION THAN IT WILL RETURN "-1" AND WILL MOVE THE EDGE OUT OF THE MID LAYER.
   AND IF EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT WILL CALL THE EDGESETTER_ON_TOP FUNCTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
int solver::find_edge_in_mid_lyr(solver &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter)
{
    if (cubeMain[face][1][2] == color_1 && cubeMain[right][1][0] == color_2)
    {
        if (color_1 == cubeMain[face][1][1] && color_2 == cubeMain[right][1][1])
        {
            return 1;
        }
        else if (color_2 == cubeMain[face][1][1] && color_1 == cubeMain[right][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[face][1][1] || color_2 == cubeMain[face][1][1])
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == cubeMain[right][1][1] || color_2 == cubeMain[right][1][1])
        {
            tempSolution.push_back("FP");
            tempSolution.push_back("UP");
            tempSolution.push_back("F");
        }
        else
        {
            tempSolution.push_back("R");
            tempSolution.push_back("UP");
            tempSolution.push_back("RP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face][1][2] == color_2 && cubeMain[right][1][0] == color_1)
    {
        if (color_2 == cubeMain[face][1][1] && color_1 == cubeMain[right][1][1])
        {
            return 1;
        }
        else if (color_1 == cubeMain[face][1][1] && color_2 == cubeMain[right][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[face][1][1] || color_2 == cubeMain[face][1][1])
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == cubeMain[right][1][1] || color_2 == cubeMain[right][1][1])
        {
            tempSolution.push_back("FP");
            tempSolution.push_back("UP");
            tempSolution.push_back("F");
        }
        else
        {
            tempSolution.push_back("R");
            tempSolution.push_back("UP");
            tempSolution.push_back("RP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face][1][0] == color_1 && cubeMain[left][1][2] == color_2)
    {
        if (color_1 == cubeMain[face][1][1] && color_2 == cubeMain[left][1][1])
        {
            return 1;
        }
        else if (color_2 == cubeMain[face][1][1] && color_1 == cubeMain[left][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[face][1][1] || color_2 == cubeMain[face][1][1])
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == cubeMain[left][1][1] || color_2 == cubeMain[left][1][1])
        {
            tempSolution.push_back("F");
            tempSolution.push_back("U");
            tempSolution.push_back("FP");
        }
        else
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("U");
            tempSolution.push_back("L");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face][1][0] == color_2 && cubeMain[left][1][2] == color_1)
    {
        if (color_2 == cubeMain[face][1][1] && color_1 == cubeMain[left][1][1])
        {
            return 1;
        }
        else if (color_1 == cubeMain[face][1][1] && color_2 == cubeMain[left][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[face][1][1] || color_2 == cubeMain[face][1][1])
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == cubeMain[left][1][1] || color_2 == cubeMain[left][1][1])
        {
            tempSolution.push_back("F");
            tempSolution.push_back("U");
            tempSolution.push_back("FP");
        }
        else
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("U");
            tempSolution.push_back("L");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    // BACK SIDE-EDGES
    else if (cubeMain[right][1][2] == color_1 && cubeMain[back][1][0] == color_2)
    {
        if (color_1 == cubeMain[right][1][1] && color_2 == cubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_2 == cubeMain[right][1][1] && color_1 == cubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[right][1][1] || color_2 == cubeMain[right][1][1])
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == cubeMain[back][1][1] || color_2 == cubeMain[back][1][1])
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("UP");
            tempSolution.push_back("R");
        }
        else
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("U");
            tempSolution.push_back("R");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[right][1][2] == color_2 && cubeMain[back][1][0] == color_1)
    {
        if (color_2 == cubeMain[right][1][1] && color_1 == cubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_1 == cubeMain[right][1][1] && color_2 == cubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[right][1][1] || color_2 == cubeMain[right][1][1])
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == cubeMain[back][1][1] || color_2 == cubeMain[back][1][1])
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("UP");
            tempSolution.push_back("R");
        }
        else
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("U");
            tempSolution.push_back("R");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[left][1][0] == color_1 && cubeMain[back][1][2] == color_2)
    {
        if (color_1 == cubeMain[left][1][1] && color_2 == cubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_2 == cubeMain[left][1][1] && color_1 == cubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[left][1][1] || color_2 == cubeMain[left][1][1])
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == cubeMain[back][1][1] || color_2 == cubeMain[back][1][1])
        {
            tempSolution.push_back("L");
            tempSolution.push_back("U");
            tempSolution.push_back("LP");
        }
        else
        {
            tempSolution.push_back("L");
            tempSolution.push_back("UP");
            tempSolution.push_back("LP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[left][1][0] == color_2 && cubeMain[back][1][2] == color_1)
    {
        if (color_2 == cubeMain[left][1][1] && color_1 == cubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_1 == cubeMain[left][1][1] && color_2 == cubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == cubeMain[left][1][1] || color_2 == cubeMain[left][1][1])
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == cubeMain[back][1][1] || color_2 == cubeMain[back][1][1])
        {
            tempSolution.push_back("L");
            tempSolution.push_back("U");
            tempSolution.push_back("LP");
        }
        else
        {
            tempSolution.push_back("L");
            tempSolution.push_back("UP");
            tempSolution.push_back("LP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            find_edge_in_top_lyr(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    return -1;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON EXECUTES THE ELGORITHEMS OF F2L_LAYER ON THE BASIS OF THE SIDE AND COLORBLOCK VALUE PROVIDED
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::f2LHelper(solver &temp_cube, const int &side, const int &colorBlock)
{
    temp_cube = *this;
    int sentinel;
    const char bottomColor{cubeMain[bottom][1][1]};
    bool cornerLocMatch{false}, boolEdgeSetter{false};

    // -------------------------------------------------- FACE SIDE ---------------------------------------------------------------
    if (side == face)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "U FP U F U FP U2 F", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R UP RP U2 FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP U2 F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP UP F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP U2 F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "UP R UP RP UP R U2 RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U F U2 R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R U2 RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U2 RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- RIGHT SIDE ---------------------------------------------------------------
    else if (side == right)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "U FP U F U FP U2 F", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "R UP RP U2 FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP U2 F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP UP F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP U2 F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "UP R UP RP UP R U2 RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "FP U F U2 R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R U2 RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U2 RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- BACK SIDE ---------------------------------------------------------------
    else if (side == back)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "U FP U F U FP U2 F", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R UP RP U2 FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP U2 F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP UP F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP U2 F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "UP R UP RP UP R U2 RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U F U2 R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R U2 RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U2 RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- LEFT SIDE ---------------------------------------------------------------
    else if (side == left)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "U FP U F U FP U2 F", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "R UP RP U2 FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP U2 F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP UP F U FP U2 F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP U2 F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "UP R UP RP UP R U2 RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "FP U F U2 R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R U2 RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U2 RP UP R U2 RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- TOP SIDE ---------------------------------------------------------------
    else if (side == top)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U2 FP UP F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U R U2 RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP FP U2 F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U2 R U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U2 F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U RP U2 R U RP UP R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP UP F U2 FP UP F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U2 RP UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R U2 RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U2 FP UP F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U2 R U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP FP U2 F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U RP U2 R U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP U2 F U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U2 RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP UP F U2 FP UP F U FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        case 3:
            if (cubeMain[side][2][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R U2 RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U2 FP UP F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U2 R U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP FP U2 F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U RP U2 R U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP U2 F U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U2 RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP UP F U2 FP UP F U FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        case 4:
            if (cubeMain[side][2][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                boolEdgeSetter = find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(temp_cube, bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U2 FP UP F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U R U2 RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP FP U2 F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U2 R U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U2 F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U RP U2 R U RP UP R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP UP F U2 FP UP F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U2 RP UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHANGES THE CUBE_SOLVING_ALGORITHEMS TO THE REQUIRED IMPLEMENTAION SIDE ON THE BASIS OF SIDE PROVIDED.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::setalgo(const int &side, string str_algo, string_view applySolutionOn)
{
    string move{};
    if (side == right)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'M')
                str_algo[i] = 'S';
            else if (str_algo[i] == 'S')
            {
                // S will become MP
                if (str_algo[i + 1] == ' ' || str_algo[i + 1] == '\0')
                {
                    str_algo.erase(i, 1);
                    str_algo.insert(i, "MP");
                }
                else if (str_algo[i + 1] == '2')
                {
                    str_algo[i] = 'M';
                }
                else
                {
                    // SP will become M
                    str_algo[i] = 'M';
                    str_algo.erase(i + 1, 1);
                }
            }
            // but E will remain E...
        }
    }
    else if (side == back)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'M')
            {
                // M will become MP
                if (str_algo[i + 1] == ' ' || str_algo[i + 1] == '\0')
                {
                    str_algo.insert(i + 1, 1, 'P');
                }
                else if (str_algo[i + 1] == '2')
                {
                    // M2 will remain M2
                }
                else
                {
                    // MP will become M
                    str_algo.erase(i + 1, 1);
                }
            }
            else if (str_algo[i] == 'S')
            {
                // S will become SP
                if (str_algo[i + 1] == ' ' || str_algo[i + 1] == '\0')
                {
                    str_algo.insert(i + 1, 1, 'P');
                }
                else if (str_algo[i + 1] == '2')
                {
                }
                else
                {
                    // SP will become S
                    str_algo.erase(i + 1, 1);
                }
            }
        }
    }
    else if (side == left)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'M')
            {
                // M will become SP
                if (str_algo[i + 1] == ' ' || str_algo[i + 1] == '\0')
                {
                    str_algo.erase(i, 1);
                    str_algo.insert(i, "SP");
                }
                else if (str_algo[i + 1] == '2')
                {
                    str_algo[i] = 'S';
                }
                else
                {
                    // MP will become S
                    str_algo[i] = 'S';
                    str_algo.erase(i + 1, 1);
                }
            }
            else if (str_algo[i] == 'S')
                str_algo[i] = 'M';
        }
    };
    // this loop extracts the operations from the string (str_algo) and pushbacks it to the arr_algo vector....
    for (size_t i{0}; i < str_algo.length(); i++)
    {
        if (str_algo[i] != ' ')
        {
            move += str_algo[i];
        }
        else if (str_algo[i] == ' ')
        {
            tempSolution.push_back(move);
            move.clear();
        }
    }
    tempSolution.push_back(move);
    applySolution(applySolutionOn);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE F2LSOLVER ON TEMPRORY CUBE UNTIL IT FINDES THE SHORTEST POSSIBLE F2L SOLUTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::shortest_cube_solution()
{
    int side{0}, bestSolutionIndex{0}, bestSolutionSize{0};
    solver solveF2L(*this), passF2L(*this), passCrs{*this}, temp_cube(*this);
    vector<int> solutionSides{};
    vector<vector<string>> crs_solutions_on_one_side, f2l_solutions_on_one_side, oll_solutions_on_one_side, pll_solutions_on_one_side, best_crs_solutions, best_f2l_solutions, best_oll_solutions, best_pll_solutions;

    for (side = face; side <= bottom; side++)
    {
        cube_orienter(*this, side);
        temp_cube = *this;
        temp_cube.cross_solver(passCrs);
        // for (auto crossSolution : passCrs.crossSolutions)
        int crssol{0};
        do
        {
            temp_cube = *this;
            // apply cross solution on temp_cube....
            temp_cube.tempSolution = passCrs.crossSolutions.at(crssol);
            temp_cube.applySolution("crs");
            // get all f2l solutions in passf2l cube...
            solveF2L = passF2L = temp_cube;
            solveF2L.f2l_solver(passF2L);
            // get best solution from all f2l solutions on passf2l...
            if (passF2L.f2lSolutions.size() > 0 || passF2L.ollSolutions.size() > 0 || passF2L.pllSolutions.size() > 0)
            {
                bestSolutionIndex = 0;
                bestSolutionSize = passF2L.f2lSolutions.at(0).size() + passF2L.ollSolutions.at(0).size() + passF2L.pllSolutions.at(0).size();
                for (size_t i{0}; i < passF2L.f2lSolutions.size() || i < passF2L.ollSolutions.size() || i < passF2L.pllSolutions.size(); i++)
                {
                    if (bestSolutionSize > (passF2L.f2lSolutions.at(i).size() + passF2L.ollSolutions.at(i).size() + passF2L.pllSolutions.at(i).size()))
                    {
                        bestSolutionSize = passF2L.f2lSolutions.at(i).size() + passF2L.ollSolutions.at(i).size() + passF2L.pllSolutions.at(0).size();
                        bestSolutionIndex = i;
                    }
                }
                // saving the best solution to crs_solutions_on_one_side, f2l_solutions_on_one_side ,oll_solutions_on_one_side and pll_solutions_on_one_side..
                crs_solutions_on_one_side.push_back(passCrs.crossSolutions.at(crssol));
                f2l_solutions_on_one_side.push_back(passF2L.f2lSolutions.at(bestSolutionIndex));
                oll_solutions_on_one_side.push_back(passF2L.ollSolutions.at(bestSolutionIndex));
                pll_solutions_on_one_side.push_back(passF2L.pllSolutions.at(bestSolutionIndex));
            }
            // clearing the past f2l, oll and pll solutions..
            passF2L.f2lSolutions.clear();
            passF2L.ollSolutions.clear();
            passF2L.pllSolutions.clear();
            crssol++;
        } while (crssol < passCrs.crossSolutions.size());
        // get best solution from all one_side-solutions ....
        if (crs_solutions_on_one_side.size() > 0 || f2l_solutions_on_one_side.size() > 0 || oll_solutions_on_one_side.size() > 0 || pll_solutions_on_one_side.size() > 0)
        {
            bestSolutionIndex = 0;
            bestSolutionSize = crs_solutions_on_one_side.at(0).size() + f2l_solutions_on_one_side.at(0).size() + oll_solutions_on_one_side.at(0).size() + pll_solutions_on_one_side.at(0).size();
            for (size_t i{0}; i < crs_solutions_on_one_side.size(); i++)
            {
                if (bestSolutionSize > (crs_solutions_on_one_side.at(i).size() + f2l_solutions_on_one_side.at(i).size() + oll_solutions_on_one_side.at(i).size() + pll_solutions_on_one_side.at(i).size()))
                {
                    bestSolutionSize = crs_solutions_on_one_side.at(i).size() + f2l_solutions_on_one_side.at(i).size() + oll_solutions_on_one_side.at(i).size() + pll_solutions_on_one_side.at(i).size();
                    bestSolutionIndex = i;
                }
            }
            // saving the best solution to crs_solutions_on_one_side, f2l_solutions_on_one_side and oll_solutions_on_one_side
            solutionSides.push_back(side);
            best_crs_solutions.push_back(crs_solutions_on_one_side.at(bestSolutionIndex));
            best_f2l_solutions.push_back(f2l_solutions_on_one_side.at(bestSolutionIndex));
            best_oll_solutions.push_back(oll_solutions_on_one_side.at(bestSolutionIndex));
            best_pll_solutions.push_back(pll_solutions_on_one_side.at(bestSolutionIndex));
        }
        // clearing the past f2l and oll solutions..
        passCrs.crossSolutions.clear();
        passF2L.f2lSolutions.clear();
        passF2L.ollSolutions.clear();
        passF2L.pllSolutions.clear();
        crs_solutions_on_one_side.clear();
        f2l_solutions_on_one_side.clear();
        oll_solutions_on_one_side.clear();
        pll_solutions_on_one_side.clear();
        cube_reorienter(*this, side);
    }
    // get best solution index from best_solutions vector....
    bestSolutionIndex = 0;
    bestSolutionSize = best_crs_solutions.at(0).size() + best_f2l_solutions.at(0).size() + best_oll_solutions.at(0).size() + best_pll_solutions.at(0).size();
    for (size_t i{0}; i < solutionSides.size(); i++)
    {
        if (bestSolutionSize > (best_crs_solutions.at(i).size() + best_f2l_solutions.at(i).size() + best_oll_solutions.at(i).size() + best_pll_solutions.at(i).size()))
        {
            bestSolutionSize = best_crs_solutions.at(i).size() + best_f2l_solutions.at(i).size() + best_oll_solutions.at(i).size() + best_pll_solutions.at(i).size();
            bestSolutionIndex = i;
        }
    }
    // correcting solution on the basis of user orientation...
    algorithmCorrector(solutionSides.at(bestSolutionIndex), best_crs_solutions.at(bestSolutionIndex));
    algorithmCorrector(solutionSides.at(bestSolutionIndex), best_f2l_solutions.at(bestSolutionIndex));
    algorithmCorrector(solutionSides.at(bestSolutionIndex), best_oll_solutions.at(bestSolutionIndex));
    algorithmCorrector(solutionSides.at(bestSolutionIndex), best_pll_solutions.at(bestSolutionIndex));
    this->crossSolution = best_crs_solutions.at(bestSolutionIndex);
    this->f2lSolution = best_f2l_solutions.at(bestSolutionIndex);
    this->ollSolution = best_oll_solutions.at(bestSolutionIndex);
    this->pllSolution = best_pll_solutions.at(bestSolutionIndex);
    this->solutionSide = solutionSides.at(bestSolutionIndex);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CODES THE OLL LAYER IN '1' AND '0' CHARACTER.
   THE VERY FIRST 9 CHARACTERS ARE FOR TOP SIDE
   THE OTHER THREE FOR FIRST ROW OF FACE AND
   THE OTHER THREE FOR FIRST ROW OF RIGHT AND
   THE OTHER THREE FOR FIRST ROW OF BACK AND
   THE LAST THREE CHARACHTER IS FOR FIRST ROW OF LEFT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string solver::oll_coder()
{
    const char top_color{cubeMain[top][1][1]};
    string OLLCode{};
    // CODING TOP SIDE OF THE CUBE.....
    for (auto vecOfvec : cubeMain[top])
        for (auto vecOfchar : vecOfvec)
            if (vecOfchar == top_color)
                OLLCode += '1';
            else
                OLLCode += '0';
    // CODING FIRST ROW OF FACE SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[face][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF RIGHT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[right][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF BACK SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[back][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF LEFT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[left][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';

    return OLLCode; // RETURNING THE FULLY CODED STRING.....
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION HAVE SOLUTION FOR ALL THE CONDITIONS POSSIBLE IN OLL
   LAYER AND IT DIRECTLY CALLS THE SETALGO TO APPLY THE CONDITION.
   IT RETURNS TRUE IF THE CONDITION MATCHES THE CODE AND FALSE WHEN OLLCODE DOSEN'T MATCHES ANY CONDITION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool solver::oll_logic(const int &side, string_view OLLcode)
{
    if (OLLcode == "111111111000000000000")
    {
        return true;
    }
    // DOT CONDITIONS...
    else if (OLLcode == "000010000010111010111")
    {
        setalgo(side, "R U BP R B R2 UP RP F R FP", "oll");
    }
    else if (OLLcode == "000010000111011010110")
    {
        setalgo(side, "RP F R FP U2 RP F R F2 U2 F", "oll");
    }
    else if (OLLcode == "000010001010011011011")
    {
        setalgo(side, "B U L UP LP BP U B L U LP UP BP", "oll");
    }
    else if (OLLcode == "001010000110110010110")
    {
        setalgo(side, "RP U2 RP F R FP UP FP UP F UP R", "oll");
    }
    else if (OLLcode == "100010001010010110011")
    {
        setalgo(side, "R U RP U RP F R FP U2 RP F R FP", "oll");
    }
    else if (OLLcode == "101010101010010010010")
    {
        setalgo(side, "MP U2 M U2 MP U M U2 MP U2 M", "oll");
    }
    else if (OLLcode == "101010000010110010011")
    {
        setalgo(side, "RP U2 F R U RP UP F2 U2 F R", "oll");
    }
    else if (OLLcode == "000010101010010111010")
    {
        setalgo(side, "F R U RP U FP U2 FP L F LP", "oll");
    }
    // LINE CONDITIONS...
    else if (OLLcode == "010010010100111001010")
    {
        setalgo(side, "RP UP FP U FP L F LP F R", "oll");
    }
    else if (OLLcode == "010010010000111000111")
    {
        setalgo(side, "R UP B2 D BP U2 B DP B2 U RP", "oll");
    }
    else if (OLLcode == "000111000110101011000")
    {
        setalgo(side, "F U R UP RP U R UP RP FP", "oll");
    }
    else if (OLLcode == "000111000010101010101")
    {
        setalgo(side, "LP BP L UP RP U R UP RP U R LP B L", "oll");
    }
    // CROSS CONDITION....
    else if (OLLcode == "010111010100101001000")
    {
        setalgo(side, "L UP RP U LP U R U RP U R", "oll");
    }
    else if (OLLcode == "010111010000101000101")
    {
        setalgo(side, "R U RP U R UP RP U R U2 RP", "oll");
    }
    else if (OLLcode == "010111011100000100100")
    {
        setalgo(side, "LP U R UP L U RP", "oll");
    }
    else if (OLLcode == "010111011000001001001")
    {
        setalgo(side, "RP U2 R U RP U R", "oll");
    }
    else if (OLLcode == "110111110001000100000")
    {
        setalgo(side, "RP FP L F R FP LP F", "oll");
    }
    else if (OLLcode == "111111010101000000000")
    {
        setalgo(side, "R2 D RP U2 R DP RP U2 RP", "oll");
    }
    else if (OLLcode == "110111011000000100001")
    {
        setalgo(side, "RP FP LP F R FP L F", "oll");
    }
    // 4 CORNERS....
    else if (OLLcode == "101110111000010010000")
    {
        setalgo(side, "MP UP M U2 MP UP M", "oll");
    }
    else if (OLLcode == "101111101010000010000")
    {
        setalgo(side, "LP R U RP UP L RP F R FP", "oll");
    }
    // SHAPE _| .......
    else if (OLLcode == "010110100011011001000")
    {
        setalgo(side, "L F RP F R F2 LP", "oll");
    }
    else if (OLLcode == "110110001110011000000")
    {
        setalgo(side, "F RP FP R U R UP RP", "oll");
    }
    else if (OLLcode == "010110001110010100100")
    {
        setalgo(side, "RP UP R F RP FP U F R FP", "oll");
    }
    else if (OLLcode == "010110101010010101000")
    {
        setalgo(side, "UP R U2 RP UP R UP R2 FP UP F U R", "oll");
    }
    else if (OLLcode == "010110000011010100101")
    {
        setalgo(side, "F R U RP UP R U RP UP FP", "oll");
    }
    else if (OLLcode == "010110000111010101000")
    {
        setalgo(side, "L FP LP F U2 L2 B L BP L", "oll");
    }
    // SHAPE \_ .....
    else if (OLLcode == "010011101010000101010")
    {
        setalgo(side, "UP RP U2 R U RP U R2 B U BP UP RP", "oll");
    }
    else if (OLLcode == "011011000110100000110")
    {
        setalgo(side, "L F2 RP FP R FP LP", "oll");
    }
    else if (OLLcode == "010011000110101001010")
    {
        setalgo(side, "FP LP UP L U LP UP L U F", "oll");
    }
    else if (OLLcode == "011011100010100001010")
    {
        setalgo(side, "RP U2 R2 BP RP B RP U2 R", "oll");
    }
    else if (OLLcode == "010011000111000101010")
    {
        setalgo(side, "RP F R FP U2 R2 BP RP B RP", "oll");
    }
    else if (OLLcode == "010011000011000100111")
    {
        setalgo(side, "RP F RP FP R2 U2 BP R B RP", "oll");
    }
    // SHAPE -\ .....
    else if (OLLcode == "001110010001010011001")
    {
        setalgo(side, "R U RP BP R B UP BP RP B", "oll");
    }
    else if (OLLcode == "100110010100110110000")
    {
        setalgo(side, "LP BP L UP RP U R LP B L", "oll");
    }
    else if (OLLcode == "000110011100010110100")
    {
        setalgo(side, "M LP UP L UP LP U2 L UP MP", "oll");
    }
    else if (OLLcode == "101110010000110010001")
    {
        setalgo(side, "BP R BP R2 U R U RP UP R B2", "oll");
    }
    // SHAPE \- ....
    else if (OLLcode == "000011010001000110111")
    {
        setalgo(side, "LP B L2 FP L2 BP L2 F LP", "oll");
    }
    else if (OLLcode == "000011110001001011010")
    {
        setalgo(side, "M R U RP U R U2 RP U MP", "oll");
    }
    else if (OLLcode == "000011011000001011011")
    {
        setalgo(side, "LP B2 R B RP B L", "oll");
    }
    else if (OLLcode == "101011010000100010011")
    {
        setalgo(side, "R2 U RP BP R UP R2 U R B RP", "oll");
    }
    // SHAPE C ....
    else if (OLLcode == "110010110000111000010")
    {
        setalgo(side, "R U R BP RP B UP RP", "oll");
    }
    else if (OLLcode == "000111101010001010100")
    {
        setalgo(side, "R U RP UP BP RP F R FP B", "oll");
    }
    // SHAPE L ....
    else if (OLLcode == "000111001110000110100")
    {
        setalgo(side, "RP F R U RP FP R F UP FP", "oll");
    }
    else if (OLLcode == "000111100011001011000")
    {
        setalgo(side, "L FP LP UP L F LP FP U F", "oll");
    }
    else if (OLLcode == "000111001010001011001")
    {
        setalgo(side, "LP BP L RP UP R U LP B L", "oll");
    }
    else if (OLLcode == "000111100010100110100")
    {
        setalgo(side, "R B RP L U LP UP R BP RP", "oll");
    }
    // SHAPE P .....
    else if (OLLcode == "110110100010111000000")
    {
        setalgo(side, "F U R UP RP FP", "oll");
    }
    else if (OLLcode == "011011001110000001010")
    {
        setalgo(side, "RP UP F U R UP RP FP R", "oll");
    }
    else if (OLLcode == "110110100011010100000")
    {
        setalgo(side, "L U FP UP LP U L F LP", "oll");
    }
    else if (OLLcode == "011011001010000000111")
    {
        setalgo(side, "FP UP LP U L F", "oll");
    }
    // SHAPE T .....
    else if (OLLcode == "001111001010000010101")
    {
        setalgo(side, "F R U RP UP FP", "oll");
    }
    else if (OLLcode == "001111001110000011000")
    {
        setalgo(side, "R U RP UP RP F R FP", "oll");
    }
    // SHAPE W ....
    else if (OLLcode == "001011110001000010110")
    {
        setalgo(side, "L U LP U L UP LP UP LP B L BP", "oll");
    }
    else if (OLLcode == "100110011100011010000")
    {
        setalgo(side, "RP UP R UP RP U R U R BP RP B", "oll");
    }
    // SHAPE Z ....
    else if (OLLcode == "100111001010000110001")
    {
        setalgo(side, "RP F R U RP UP FP U R", "oll");
    }
    else if (OLLcode == "001111100010100011000")
    {
        setalgo(side, "L FP LP UP L U F UP LP", "oll");
    }
    else
        return false;
    return true;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE CUBE AND SAVES THE ALGORITHM TO THE f2lSolution
   AND THEN CLEARS THE TEMPSOLUTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::applySolution(string_view applySolutionOn)
{
    for (size_t i{0}; i < tempSolution.size(); i++)
    {
        if (tempSolution.at(i) == "F")
            F;
        else if (tempSolution.at(i) == "L")
            L;
        else if (tempSolution.at(i) == "R")
            R;
        else if (tempSolution.at(i) == "U")
            U;
        else if (tempSolution.at(i) == "D")
            D;
        else if (tempSolution.at(i) == "B")
            B;
        else if (tempSolution.at(i) == "FP")
            FP;
        else if (tempSolution.at(i) == "LP")
            LP;
        else if (tempSolution.at(i) == "RP")
            RP;
        else if (tempSolution.at(i) == "UP")
            UP;
        else if (tempSolution.at(i) == "DP")
            DP;
        else if (tempSolution.at(i) == "BP")
            BP;
        else if (tempSolution.at(i) == "F2")
            F2;
        else if (tempSolution.at(i) == "L2")
            L2;
        else if (tempSolution.at(i) == "R2")
            R2;
        else if (tempSolution.at(i) == "U2")
            U2;
        else if (tempSolution.at(i) == "D2")
            D2;
        else if (tempSolution.at(i) == "B2")
            B2;
        else if (tempSolution.at(i) == "M")
            M;
        else if (tempSolution.at(i) == "S")
            S;
        else if (tempSolution.at(i) == "E")
            E;
        else if (tempSolution.at(i) == "MP")
            MP;
        else if (tempSolution.at(i) == "SP")
            SP;
        else if (tempSolution.at(i) == "EP")
            EP;
        else if (tempSolution.at(i) == "M2")
        {
            M;
            M;
        }
        else if (tempSolution.at(i) == "S2")
        {
            S;
            S;
        }
        else if (tempSolution.at(i) == "E2")
        {
            E;
            E;
        }
    }
    if (applySolutionOn == "crs")
        for (size_t i{0}; i < tempSolution.size(); i++)
            crossSolution.push_back(tempSolution.at(i));
    else if (applySolutionOn == "f2l")
        for (size_t i{0}; i < tempSolution.size(); i++)
            f2lSolution.push_back(tempSolution.at(i));
    else if (applySolutionOn == "oll")
        for (size_t i{0}; i < tempSolution.size(); i++)
            ollSolution.push_back(tempSolution.at(i));
    else if (applySolutionOn == "pll")
        for (size_t i{0}; i < tempSolution.size(); i++)
            pllSolution.push_back(tempSolution.at(i));
    tempSolution.clear();
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION OPTIMIZES THE SOLUTION VECTOR PASSED INTO IT AND MAKES IS SHORTER AND SWEET.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solution_optimizer(vector<std::string> &solution)
{
    int checks{1};
    for (int times{0}; times < 4; times++)
    {
        if (checks == 0)
            break;
        checks = 0;
        for (size_t i{0}, j{1}; i < (solution.size() - 1) && solution.size() >= 2; i++, j++)
        {
            if (solution.at(i) == solution.at(j))
            {
                // for the condition when we have U2 and U2 .....
                if (solution.at(i).size() == 2)
                {
                    if (solution.at(i).at(1) == '2')
                    {
                        solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                        checks++;
                    }
                    else
                    {
                        solution.at(i).at(1) = '2';
                        // removing j element....
                        solution.erase(solution.begin() + j);
                        checks++;
                    }
                }
                else
                {
                    solution.at(i) = solution.at(i) + '2';
                    // removing j element....
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
            else if (solution.at(i).size() == 2 && solution.at(j).size() == 1)
            {
                // for the condition when we have up and u so we cancel both....
                if (solution.at(i).at(0) == solution.at(j).at(0))
                {
                    if (solution.at(i).at(1) == 'P')
                    {
                        solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                        checks++;
                    }
                    else
                    {
                        // ex: U2 + U = UP
                        solution.at(i) = solution.at(j) + 'P';
                        solution.erase(solution.begin() + j);
                        checks++;
                    }
                }
            }
            else if (solution.at(i).size() == 1 && solution.at(j).size() == 2)
            {
                // for the condition when we have U and UP so we cancel both....
                if (solution.at(i).at(0) == solution.at(j).at(0))
                {
                    if (solution.at(j).at(1) == 'P')
                    {
                        solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                        checks++;
                    }
                    else
                    {
                        // ex: U + U2 = UP
                        solution.at(i) = solution.at(i) + 'P';
                        solution.erase(solution.begin() + j);
                        checks++;
                    }
                }
            }
            else if (solution.at(i).size() == solution.at(j).size() && solution.at(i).size() == 2)
            {
                if (solution.at(i).at(0) == solution.at(j).at(0))
                {
                    // ex: U2 + UP = U
                    solution.at(i) = solution.at(i).at(0);
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CORRECTS THE ALGORITHM APPLIED AFTER THE ORIENTATION & RE-ORIENTATION OF THE CUBE ON THE BASIS OF SIDE OF ORIENTATOION..
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::algorithmCorrector(const int &side, vector<string> &algorithm)
{
    if (algorithm.size() == 0)
    {
        return;
    }
    else
    {
        if (algorithm.at(0) == "")
        {
            cout << "error";
            return;
        }
    }
    if (side == face)
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
    else if (side == left)
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
    else if (side == right)
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
    else if (side == back)
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
    else if (side == top)
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
   THIS FUNCTION ORIENTS THE CUBE BY MAKING THE GIVEN SIDE TO THE BASE SIDE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::cube_orienter(solver &source, const int &side)
{
    // Orienting the cube on the basis of side value passed....
    switch (side)
    {
    case face:
        source.XP;
        break;
    case left:
        source.ZP;
        break;
    case right:
        source.Z;
        break;
    case back:
        source.X;
        break;
    case top:
        source.X;
        source.X;
        break;
    default:
        break;
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION RE-ORIENTS THE CUBE TO THE PAST CONDIDTION...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::cube_reorienter(solver &source, const int &side)
{
    // Re Orienting the cube on the basis of side value passed....
    switch (side)
    {
    case face:
        source.X;
        break;
    case left:
        source.Z;
        break;
    case right:
        source.ZP;
        break;
    case back:
        source.XP;
        break;
    case top:
        source.X;
        source.X;
        break;
    default:
        break;
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CHECKS IF THE CUBE REQUIRED TO SOLVE THE PLL LAYER...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solver::correct_last_layer()
{
    for (int move{0}; move < 4; move++)
        if (cubeMain[face][0][1] != cubeMain[face][1][1])
            setalgo(face, "U", "pll");
        else
            break;
    solution_optimizer(pllSolution);
}
