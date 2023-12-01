#include "Cross.h"
#include <algorithm>
#include "Optimiser.h"

Cross::Cross() : Cube() {}
Cross::Cross(const Cube &cube) : Cube(cube) {}

Cross &Cross::operator=(const Cross &cross)
{
    Cube::operator=(cross);

    if (this != &cross)
        this->solution = cross.solution;
    return *this;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE BOTTOM CROSS OF THE RUBIX Cube...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cross::solver(vector<vector<string>> &solutions)
{
    int block{0}, side{0}, crossColorCount{0}, count{0}, twocorrect{0}, limit{0};
    bool solve{false}, tenTimeSolve{false};
    const char bottomColor{CubeMain[bottom][1][1]};
    char edgeColor{};
    vector<char> mainOrientation{}, currentOrientation{};
    vector<int> crsEdges{};
    mainOrientation = move(get_equator_colors_orientation());
    currentOrientation = move(get_cross_colors_orientation());
    crossColorCount = count_bottom_lyr_edge();

    if (crossColorCount == 4)
    {
        // for the condition when crosscolor count == 4....
        currentOrientation = move(get_cross_colors_orientation());
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
            setalgo(face, "D");
        }
        if (count == 4) // if cross is compelete
        {
            // Optimising f2lSolution....
            Optimiser::optimise(solution);
            solutions.push_back(solution);
            return;
        }
        else // if edges are in bottom but not currect
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
                    setalgo(side, "FP DP F D FP");
                    break;
                case 1:
                    setalgo(side, "F D FP DP F");
                    break;
                case 2:
                    setalgo(side, "F D2 FP D2 F");
                    break;
                default:
                    break;
                }
                // Verifying the current orientation...
                currentOrientation = move(get_cross_colors_orientation());
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
                // reverting the previous solution....
                switch (checkside)
                {
                case 0:
                    setalgo(side, "F DP FP D F", false);
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    break;
                case 1:
                    setalgo(side, "FP D F DP FP", false);
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    break;
                case 2:
                    setalgo(side, "FP D2 F D2 FP", false);
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    solution.pop_back();
                    break;
                default:
                    break;
                }
            }
        }
    }

    // first f2l corner...
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

    Cross sourceBackup, sourceCpy;
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
        crossColorCount = count_bottom_lyr_edge();
        if (crossColorCount != 4)
        {
            if (side >= face && side <= right)
            {
                switch (block)
                {
                // this case is for checking the top side edge....
                case 1:
                    if (CubeMain[side][0][1] == bottomColor)
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
                                    setalgo(side, "F RP");
                                    break;
                                case 1:
                                    setalgo(side, "FP L");
                                    break;
                                default:
                                    break;
                                }
                                sourceCpy = *this;
                                *this = sourceBackup;
                                sourceCpy.solver(solutions);
                            }
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                        setalgo(side, "F RP");
                                    else
                                        setalgo(side, "FP L");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (limit == 3 && crossColorCount == 2)
                                    {
                                        if (twotimes == 0)
                                            setalgo(side, "FP");
                                        else
                                            setalgo(side, "F");
                                        // using twoCorrect as a singnal.....
                                        twocorrect = -1;
                                    }
                                    else
                                        twocorrect = 0;
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount >= limit)
                                    {
                                        // Verifying the current Orientation......
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                            setalgo(side, "F", false);
                                        else
                                            setalgo(side, "FP", false);
                                        solution.pop_back();
                                    }
                                    if (twotimes == 0)
                                        setalgo(side, "R FP", false);
                                    else
                                        setalgo(side, "LP F", false);
                                    solution.pop_back();
                                    solution.pop_back();
                                    setalgo(side, "D");
                                }
                                // this is for breaking the two times loop .....
                                if (count >= limit)
                                    break;
                            }
                            break;
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                            setalgo(side, "F RP FP");
                                        else
                                            setalgo(side, "FP L F");
                                        crossColorCount = count_bottom_lyr_edge();
                                        if (crossColorCount == 4)
                                        {
                                            if (checkside == 2)
                                            {
                                                // reverting to get even shorter solution....
                                                setalgo(side, "F R FP", false);
                                                solution.pop_back();
                                                solution.pop_back();
                                                solution.pop_back();
                                                // for removing last two D operatrions...
                                                setalgo(side, "D2", false);
                                                solution.pop_back();
                                                solution.pop_back();
                                                break;
                                            }
                                            // using count as a signal to what to do next....
                                            count = -1;
                                            break;
                                        }
                                        // reverting the previour solution....
                                        if (twotimes == 0)
                                            setalgo(side, "F R FP", false);
                                        else
                                            setalgo(side, "FP LP F", false);
                                        solution.pop_back();
                                        solution.pop_back();
                                        solution.pop_back();
                                        setalgo(side, "D");
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
                                            setalgo(side, "F RP");
                                        else
                                            setalgo(side, "FP L");
                                        crossColorCount = count_bottom_lyr_edge();
                                        if (crossColorCount == 2)
                                        {
                                            if (twotimes == 0)
                                                setalgo(side, "FP");
                                            else
                                                setalgo(side, "F");
                                            // using twoCorrect as a singnal.....
                                            twocorrect = -1;
                                        }
                                        else
                                            twocorrect = 0;
                                        crossColorCount = count_bottom_lyr_edge();
                                        if (crossColorCount == 3)
                                        {
                                            // Verifying the current orientation...
                                            currentOrientation = move(get_cross_colors_orientation());
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
                                                setalgo(side, "F", false);
                                            else
                                                setalgo(side, "FP", false);
                                            solution.pop_back();
                                        }
                                        if (twotimes == 0)
                                            setalgo(side, "R FP", false);
                                        else
                                            setalgo(side, "LP F", false);
                                        solution.pop_back();
                                        solution.pop_back();
                                        setalgo(side, "D");
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
                                            setalgo(side, "F RP");
                                        else
                                            setalgo(side, "FP L");
                                        crossColorCount = count_bottom_lyr_edge();
                                        if (crossColorCount <= 3)
                                        {
                                            // Verifying the current orientation...
                                            currentOrientation = move(get_cross_colors_orientation());
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
                                            setalgo(side, "R FP", false);
                                        else
                                            setalgo(side, "LP F", false);
                                        solution.pop_back();
                                        solution.pop_back();
                                        setalgo(side, "D");
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
                    if (CubeMain[side][1][2] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                        case 0:
                            setalgo(side, "RP");
                            break;
                        // one or two edges on the bottom
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side, "RP");
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side, "R", false);
                                solution.pop_back();
                                setalgo(side, "D");
                            }
                            break;
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "RP");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount == 4)
                                    {
                                        break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "R", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
                                }
                            }
                            // When two edges are correct...
                            else if (twocorrect == 2)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "RP");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "R", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
                                }
                            }
                            // When one edge is correct...
                            else
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "RP");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount <= 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "R", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
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
                    if (CubeMain[side][2][1] == bottomColor)
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
                                    setalgo(side, "FP RP");
                                    break;
                                case 1:
                                    setalgo(side, "F L");
                                    break;
                                default:
                                    break;
                                }
                                sourceCpy = *this;
                                *this = sourceBackup;
                                sourceCpy.solver(solutions);
                            }
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "FP D RP");
                                    break;
                                case 1:
                                    setalgo(side, "FP RP");
                                    break;
                                case 2:
                                    setalgo(side, "F D L");
                                    break;
                                case 3:
                                    setalgo(side, "F L");
                                    break;
                                default:
                                    break;
                                }
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "R DP F", false);
                                    solution.pop_back();
                                    solution.pop_back();
                                    solution.pop_back();
                                    break;
                                case 1:
                                    setalgo(side, "R F", false);
                                    solution.pop_back();
                                    solution.pop_back();
                                    break;
                                case 2:
                                    setalgo(side, "LP DP FP", false);
                                    solution.pop_back();
                                    solution.pop_back();
                                    solution.pop_back();
                                    break;
                                case 3:
                                    setalgo(side, "LP FP", false);
                                    solution.pop_back();
                                    solution.pop_back();
                                    break;
                                default:
                                    break;
                                }
                            }
                            break;
                            // three edges on the bottom...
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                        setalgo(side, "FP D RP");
                                        break;
                                    case 1:
                                        setalgo(side, "F DP L");
                                        break;
                                    default:
                                        break;
                                    }
                                    sourceCpy = *this;
                                    *this = sourceBackup;
                                    sourceCpy.solver(solutions);
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
                                        setalgo(side, "FP RP");
                                        break;
                                    case 1:
                                        setalgo(side, "F D L");
                                        break;
                                    case 2:
                                        setalgo(side, "F L");
                                        break;
                                    default:
                                        break;
                                    }
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                        setalgo(side, "R F", false);
                                        solution.pop_back();
                                        solution.pop_back();
                                        break;
                                    case 1:
                                        setalgo(side, "LP DP FP", false);
                                        solution.pop_back();
                                        solution.pop_back();
                                        solution.pop_back();
                                        break;
                                    case 2:
                                        setalgo(side, "LP FP", false);
                                        solution.pop_back();
                                        solution.pop_back();
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
                                        setalgo(side, "F L");
                                        break;
                                    case 1:
                                        setalgo(side, "FP RP");
                                        break;
                                    default:
                                        break;
                                    }
                                    sourceCpy = *this;
                                    *this = sourceBackup;
                                    sourceCpy.solver(solutions);
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
                    if (CubeMain[side][1][0] == bottomColor)
                    {
                        switch (crossColorCount)
                        {
                            // no edges on the bottom...
                        case 0:
                            setalgo(side, "L");
                            break;
                        // one or two edges on the bottom...
                        case 1:
                        case 2:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side, "L");
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount >= limit)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side, "LP", false);
                                solution.pop_back();
                                setalgo(side, "D");
                            }
                            break;
                            // When three edges on the bottom...
                        case 3:
                            currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "L");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount == 4)
                                    {
                                        break;
                                    }
                                    // reverting the previour solution....
                                    setalgo(side, "LP", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
                                }
                            }
                            // two correct edges...
                            else if (twocorrect == 2)
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "L");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount == 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "LP", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
                                }
                            }
                            // one edge correct...
                            else
                            {
                                for (int checkside{0}; checkside < 4; checkside++)
                                {
                                    setalgo(side, "L");
                                    crossColorCount = count_bottom_lyr_edge();
                                    if (crossColorCount <= 3)
                                    {
                                        // Verifying the current orientation...
                                        currentOrientation = move(get_cross_colors_orientation());
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
                                    setalgo(side, "LP", false);
                                    solution.pop_back();
                                    setalgo(side, "D");
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
                    if (CubeMain[side][2][1] == bottomColor)
                        side_2 = face;
                    break;
                case 2:
                    // this is for checking the right side edge....
                    if (CubeMain[side][1][2] == bottomColor)
                        side_2 = right;
                    break;
                case 3:
                    // this is for checking the back side edge....
                    if (CubeMain[side][0][1] == bottomColor)
                        side_2 = back;
                    break;
                case 4:
                    // this is for checking the left side edge....
                    if (CubeMain[side][1][0] == bottomColor)
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
                        setalgo(side_2, "F2");
                        break;
                        // one or two edges on the bottom...
                    case 1:
                    case 2:
                        currentOrientation = move(get_cross_colors_orientation());
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
                            setalgo(side_2, "F2");
                            crossColorCount = count_bottom_lyr_edge();
                            if (crossColorCount >= limit)
                            {
                                // Verifying the current orientation...
                                currentOrientation = move(get_cross_colors_orientation());
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
                            setalgo(side_2, "F2", false);
                            solution.pop_back();
                            setalgo(side_2, "D");
                        }
                        break;
                        // three edges on the bottom...
                    case 3:
                        currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side_2, "F2");
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount == 4)
                                {
                                    break;
                                }
                                // reverting the previour solution....
                                setalgo(side_2, "F2", false);
                                solution.pop_back();
                                setalgo(side_2, "D");
                            }
                        }
                        // When two edges are correct...
                        else if (twocorrect == 2)
                        {
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side_2, "F2");
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount == 3)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side_2, "F2", false);
                                solution.pop_back();
                                setalgo(side_2, "D");
                            }
                        }
                        // one correct edge on the bottom...
                        else
                        {
                            for (int checkside{0}; checkside < 4; checkside++)
                            {
                                setalgo(side_2, "F2");
                                crossColorCount = count_bottom_lyr_edge();
                                if (crossColorCount <= 3)
                                {
                                    // Verifying the current orientation...
                                    currentOrientation = move(get_cross_colors_orientation());
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
                                setalgo(side_2, "F2", false);
                                solution.pop_back();
                                setalgo(side_2, "D");
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
                sourceCpy.solver(solutions);
            }
        }
    }
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION COUNTS THE NUMBER OF BASE EDGES CURENTLY LOCATED AT THE BOTTOM...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
int Cross::count_bottom_lyr_edge()
{
    int colorCount{0};
    if (CubeMain[bottom][0][1] == CubeMain[bottom][1][1])
        colorCount++;
    if (CubeMain[bottom][1][0] == CubeMain[bottom][1][1])
        colorCount++;
    if (CubeMain[bottom][1][2] == CubeMain[bottom][1][1])
        colorCount++;
    if (CubeMain[bottom][2][1] == CubeMain[bottom][1][1])
        colorCount++;
    return colorCount;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION THIS FUNCTION RETURNS THE MAIN ORIENTATION OF THE CROSS COLORS.....
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<char> Cross::get_equator_colors_orientation()
{
    vector<char> crossColorOrientation{};
    crossColorOrientation.push_back(CubeMain[face][1][1]);
    crossColorOrientation.push_back(CubeMain[right][1][1]);
    crossColorOrientation.push_back(CubeMain[back][1][1]);
    crossColorOrientation.push_back(CubeMain[left][1][1]);
    return std::move(crossColorOrientation);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION THIS FUNCTION RETURNS THE CURRENT ORIENTATION OF THE CROSS EDGES ON THE BOTTOM...
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<char> Cross::get_cross_colors_orientation()
{
    vector<char> baseCross{};
    if (CubeMain[bottom][0][1] == CubeMain[bottom][1][1])
        baseCross.push_back(CubeMain[face][2][1]);
    else
        baseCross.push_back('\0');
    if (CubeMain[bottom][1][2] == CubeMain[bottom][1][1])
        baseCross.push_back(CubeMain[right][2][1]);
    else
        baseCross.push_back('\0');
    if (CubeMain[bottom][2][1] == CubeMain[bottom][1][1])
        baseCross.push_back(CubeMain[back][2][1]);
    else
        baseCross.push_back('\0');
    if (CubeMain[bottom][1][0] == CubeMain[bottom][1][1])
        baseCross.push_back(CubeMain[left][2][1]);
    else
        baseCross.push_back('\0');
    return move(baseCross);
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE LOCATION OF THE BOTTOM COLOR EDGE ON THE BASIS OF THE CORESPONDING COLOR PROVIDED...
   IT SAVES THE SIDE AND BLOCK OF THE EDGE..
   AND RETURNS TRUE IF IT FINDS THE EDGE..
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool Cross::get_edge_location(const char &color_1, int &side, int &block)
{
    int count{0};
    vector<char> colors{color_1, CubeMain[bottom][1][1]};
    // BELLOW FOUR ARE TOP SIDE EDGES....
    count = 0;
    for (int i{0}; i < 2; i++)
    {
        if (CubeMain[top][2][1] == colors[i] || CubeMain[face][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[top][2][1] == colors[i])
            {
                side = top;
                block = 1;
            }
            else if (CubeMain[face][0][1] == colors[i])
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
        if (CubeMain[top][1][2] == colors[i] || CubeMain[right][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[top][1][2] == colors[i])
            {
                side = top;
                block = 2;
            }
            else if (CubeMain[right][0][1] == colors[i])
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
        if (CubeMain[top][0][1] == colors[i] || CubeMain[back][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[top][0][1] == colors[i])
            {
                side = top;
                block = 3;
            }
            else if (CubeMain[back][0][1] == colors[i])
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
        if (CubeMain[top][1][0] == colors[i] || CubeMain[left][0][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[top][1][0] == colors[i])
            {
                side = top;
                block = 4;
            }
            else if (CubeMain[left][0][1] == colors[i])
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
        if (CubeMain[bottom][0][1] == colors[i] || CubeMain[face][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[face][2][1] == colors[i])
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
        if (CubeMain[bottom][1][2] == colors[i] || CubeMain[right][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[right][2][1] == colors[i])
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
        if (CubeMain[bottom][2][1] == colors[i] || CubeMain[back][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[back][2][1] == colors[i])
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
        if (CubeMain[bottom][1][0] == colors[i] || CubeMain[left][2][1] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[left][2][1] == colors[i])
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
        if (CubeMain[face][1][2] == colors[i] || CubeMain[right][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[face][1][2] == colors[i])
            {
                side = face;
                block = 2;
            }
            else if (CubeMain[right][1][0] == colors[i])
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
        if (CubeMain[right][1][2] == colors[i] || CubeMain[back][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[right][1][2] == colors[i])
            {
                side = right;
                block = 2;
            }
            else if (CubeMain[back][1][0] == colors[i])
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
        if (CubeMain[back][1][2] == colors[i] || CubeMain[left][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[back][1][2] == colors[i])
            {
                side = back;
                block = 2;
            }
            else if (CubeMain[left][1][0] == colors[i])
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
        if (CubeMain[left][1][2] == colors[i] || CubeMain[face][1][0] == colors[i])
            count++;
        if (count == 2)
        {
            if (CubeMain[left][1][2] == colors[i])
            {
                side = left;
                block = 2;
            }
            else if (CubeMain[face][1][0] == colors[i])
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
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE Cube AND SAVES THE ALGORITHM TO THE f2lSolution
   AND THEN CLEARS THE TEMPSOLUTION.
   ---------------------------------------------------------------------------------------------------------------------------------------- */
void Cross::applySolution(const bool &apply) // overriden function...
{
    Cube::applyTempSolution();
    if (apply)
    {
        for (size_t i{0}; i < tempSolution.size(); i++)
            solution.push_back(tempSolution.at(i));
    }
    tempSolution.clear(); // clear the tempsolutoin to avoid additional application..
}