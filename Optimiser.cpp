#include "Optimiser.h"

using namespace std;

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION OPTIMIZES THE SOLUTION VECTOR PASSED INTO IT AND MAKES IS SHORTER AND SWEET.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Optimiser::optimise(vector<string> &solution)
{

    if (!(solution.size())) // if solution size is 0
    {
        solution.push_back("");
        return;
    }

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
