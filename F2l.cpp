#include "F2l.h"
#include <algorithm>
#include <random>
#include "Optimiser.h"

F2l::F2l() : Cube() {}
F2l::F2l(const Cube &cube) : Cube(cube) {}

F2l &F2l::operator=(const F2l &f2l)
{
    Cube::operator=(f2l);
    if (this != &f2l)
        this->solution = f2l.solution;
    return *this;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE F2L_LAYER OF THE RUBIX Cube....
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void F2l::solver(vector<vector<string>> &solutions)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rang0to1(0, 1);
    int side{}, sentinel{}, block{};
    const char bottomColor{CubeMain[bottom][1][1]};
    vector<int> incorrectF2lCorners{};
    bool cornerLocMatch{false}, boolEdgeSetter{false};

    // first f2l corner...
    if (CubeMain[bottom][1][1] != CubeMain[bottom][0][0] || CubeMain[face][1][1] != CubeMain[face][1][0] || CubeMain[face][1][1] != CubeMain[face][2][0] || CubeMain[left][1][1] != CubeMain[left][1][2] || CubeMain[left][1][1] != CubeMain[left][2][2])
        incorrectF2lCorners.push_back(1);
    // second f2l corner...
    if (CubeMain[bottom][1][1] != CubeMain[bottom][0][2] || CubeMain[face][1][1] != CubeMain[face][1][2] || CubeMain[face][1][1] != CubeMain[face][2][2] || CubeMain[right][1][1] != CubeMain[right][1][0] || CubeMain[right][1][1] != CubeMain[right][2][0])
        incorrectF2lCorners.push_back(2);
    // third f2l corner...
    if (CubeMain[bottom][1][1] != CubeMain[bottom][2][0] || CubeMain[back][1][1] != CubeMain[back][1][2] || CubeMain[back][1][1] != CubeMain[back][2][2] || CubeMain[left][1][1] != CubeMain[left][1][0] || CubeMain[left][1][1] != CubeMain[left][2][0])
        incorrectF2lCorners.push_back(3);
    // fourth f2l corner...
    if (CubeMain[bottom][1][1] != CubeMain[bottom][2][2] || CubeMain[back][1][1] != CubeMain[back][1][0] || CubeMain[back][1][1] != CubeMain[back][2][0] || CubeMain[right][1][1] != CubeMain[right][1][2] || CubeMain[right][1][1] != CubeMain[right][2][2])
        incorrectF2lCorners.push_back(4);

    if (incorrectF2lCorners.size() == 0) // IT WILL WORK IF THE Cube IS SOLVED....
    {
        // solution_optimizer(f2lSolution);
        Optimiser::optimise(solution); // Optimising f2lSolution....
        // oll_solver();
        // pll_solver();
        // correct_last_layer();
        solutions.push_back(solution);
        // temp_Cube.ollSolutions.push_back(ollSolution);
        // temp_Cube.pllSolutions.push_back(pllSolution);
        // trials++;
        // std::cout << "\r" << RED << trials << DEFAULT << " TIMES Cube SOLVED...";
    }
    else
    {
        F2l sourceBackup, sourceCpy;
        for (size_t i{0}; i < incorrectF2lCorners.size(); i++)
        {
            cornerColors.clear();
            switch (incorrectF2lCorners.at(i))
            {
            case 1:
                cornerColors.push_back(CubeMain[face][1][1]);
                cornerColors.push_back(CubeMain[left][1][1]);
                break;
            case 2:
                cornerColors.push_back(CubeMain[face][1][1]);
                cornerColors.push_back(CubeMain[right][1][1]);
                break;
            case 3:
                cornerColors.push_back(CubeMain[back][1][1]);
                cornerColors.push_back(CubeMain[left][1][1]);
                break;
            case 4:
                cornerColors.push_back(CubeMain[back][1][1]);
                cornerColors.push_back(CubeMain[right][1][1]);
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        if (cornerLocMatch)
                        {
                            // for optimization purposes....
                            boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == left)
                                {
                                    setalgo(left, "U R UP RP UP FP U F");
                                }
                                else if (edgeSide == face)
                                {
                                    setalgo(left, "UP FP U F U R UP RP");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(left, "R UP R2 U2 R UP FP U F");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    };
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == face)
                                {
                                    setalgo(face, "U R UP RP UP FP U F");
                                }
                                else if (edgeSide == right)
                                {
                                    setalgo(face, "UP FP U F U R UP RP");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(face, "R UP R2 U2 R UP FP U F");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == back)
                                {
                                    setalgo(back, "U R UP RP UP FP U F");
                                }
                                else if (edgeSide == left)
                                {
                                    setalgo(back, "UP FP U F U R UP RP");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(back, "R UP R2 U2 R UP FP U F");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        if (cornerLocMatch)
                        {
                            boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            sentinel = -1;
                            if (!boolEdgeSetter)
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinel == -1)
                            {
                                if (edgeSide == right)
                                {
                                    setalgo(right, "U R UP RP UP FP U F");
                                }
                                else if (edgeSide == back)
                                {
                                    setalgo(right, "UP FP U F U R UP RP");
                                }
                            }
                            else if (sentinel == 0)
                            {
                                setalgo(right, "R UP R2 U2 R UP FP U F");
                            };
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "U FP U F U FP U2 F");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "U FP UP F UP R U RP");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R UP RP U2 FP UP F");
                                }
                                else
                                {
                                    setalgo(left, "UP R UP RP U R U RP");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U FP U2 F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(left, "R U RP");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U FP UP F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(left, "UP R U RP U R U RP");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "F RP FP R");
                                }
                                else
                                {
                                    setalgo(left, "U FP U2 F UP R U RP");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "UP R UP RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "UP R U RP U FP UP F");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP U F U2 R U RP");
                                }
                                else
                                {
                                    setalgo(face, "U FP U F UP FP UP F");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U R UP RP");
                                }
                                else
                                {
                                    setalgo(face, "UP R U2 RP U FP UP F");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP R U RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(face, "U FP UP F UP FP UP F");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP R U2 RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(face, "FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R UP RP U R U2 RP U R UP RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R U RP UP R UP RP U2 FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == face)
                            {
                                setalgo(left, "R U RP UP R U RP");
                            }
                            else if (edgeSide == left)
                            {
                                setalgo(left, "FP U F UP FP U F");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R UP RP UP R U RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R UP RP U FP UP F UP FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == face)
                            {
                                setalgo(face, "FP UP F U FP UP F");
                            }
                            else if (edgeSide == right)
                            {
                                setalgo(face, "R UP RP U R UP RP");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "U FP U F U FP U2 F");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "U FP UP F UP R U RP");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "R UP RP U2 FP UP F");
                                }
                                else
                                {
                                    setalgo(face, "UP R UP RP U R U RP");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U FP U2 F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(face, "R U RP");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U FP UP F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(face, "UP R U RP U R U RP");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "F RP FP R");
                                }
                                else
                                {
                                    setalgo(face, "U FP U2 F UP R U RP");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "UP R UP RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "UP R U RP U FP UP F");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "FP U F U2 R U RP");
                                }
                                else
                                {
                                    setalgo(right, "U FP U F UP FP UP F");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U R UP RP");
                                }
                                else
                                {
                                    setalgo(right, "UP R U2 RP U FP UP F");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "UP R U RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(right, "U FP UP F UP FP UP F");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "UP R U2 RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(right, "FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R UP RP U R U2 RP U R UP RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R U RP UP R UP RP U2 FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == right)
                            {
                                setalgo(face, "R U RP UP R U RP");
                            }
                            else if (edgeSide == face)
                            {
                                setalgo(face, "FP U F UP FP U F");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(face, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(face, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R UP RP UP R U RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R UP RP U FP UP F UP FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == right)
                            {
                                setalgo(right, "FP UP F U FP UP F");
                            }
                            else if (edgeSide == back)
                            {
                                setalgo(right, "R UP RP U R UP RP");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "U FP U F U FP U2 F");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "U FP UP F UP R U RP");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R UP RP U2 FP UP F");
                                }
                                else
                                {
                                    setalgo(right, "UP R UP RP U R U RP");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U FP U2 F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(right, "R U RP");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U FP UP F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(right, "UP R U RP U R U RP");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "F RP FP R");
                                }
                                else
                                {
                                    setalgo(right, "U FP U2 F UP R U RP");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "UP R UP RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "UP R U RP U FP UP F");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP U F U2 R U RP");
                                }
                                else
                                {
                                    setalgo(back, "U FP U F UP FP UP F");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U R UP RP");
                                }
                                else
                                {
                                    setalgo(back, "UP R U2 RP U FP UP F");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP R U RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(back, "U FP UP F UP FP UP F");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP R U2 RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(back, "FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R UP RP U R U2 RP U R UP RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R U RP UP R UP RP U2 FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == back)
                            {
                                setalgo(right, "R U RP UP R U RP");
                            }
                            else if (edgeSide == right)
                            {
                                setalgo(right, "FP U F UP FP U F");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(right, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(right, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R UP RP UP R U RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R UP RP U FP UP F UP FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == back)
                            {
                                setalgo(back, "FP UP F U FP UP F");
                            }
                            else if (edgeSide == left)
                            {
                                setalgo(back, "R UP RP U R UP RP");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "U FP U F U FP U2 F");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "U FP UP F UP R U RP");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "R UP RP U2 FP UP F");
                                }
                                else
                                {
                                    setalgo(back, "UP R UP RP U R U RP");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U FP U2 F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(back, "R U RP");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U FP UP F U FP U2 F");
                                }
                                else
                                {
                                    setalgo(back, "UP R U RP U R U RP");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "F RP FP R");
                                }
                                else
                                {
                                    setalgo(back, "U FP U2 F UP R U RP");
                                }
                            }
                        } // this else is for the condition when the corner or edge is not on the right location....
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "UP R UP RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "UP R U RP U FP UP F");
                                }
                                else if (sentinel == -1)
                                {
                                    // the corner setter will set the corner and will pass the control back to this function.....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "FP U F U2 R U RP");
                                }
                                else
                                {
                                    setalgo(left, "U FP U F UP FP UP F");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U R UP RP");
                                }
                                else
                                {
                                    setalgo(left, "UP R U2 RP U FP UP F");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "UP R U RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(left, "U FP UP F UP FP UP F");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "UP R U2 RP UP R U2 RP");
                                }
                                else
                                {
                                    setalgo(left, "FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R UP RP U R U2 RP U R UP RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R U RP UP R UP RP U2 FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == left)
                            {
                                setalgo(back, "R U RP UP R U RP");
                            }
                            else if (edgeSide == back)
                            {
                                setalgo(back, "FP U F UP FP U F");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(back, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(back, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (cornerLocMatch)
                        {
                            // for the condition when corner is on the correct location but side edge is not on the top......
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R UP RP UP R U RP UP R U2 RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R UP RP U FP UP F UP FP UP F");
                                }
                                // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                            }
                            if (edgeSide == left)
                            {
                                setalgo(left, "FP UP F U FP UP F");
                            }
                            else if (edgeSide == face)
                            {
                                setalgo(left, "R UP RP U R UP RP");
                            }
                        }
                        else
                        {
                            switch (rang0to1(rng))
                            {
                            case 0:
                                setalgo(left, "R U RP");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                                break;
                            case 1:
                                setalgo(left, "FP UP F");
                                set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
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
                    if (CubeMain[side][0][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(back, "R U RP UP R U RP UP R U RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(back, "R UP RP U FP U F");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "U2 FP UP F UP FP U F");
                                }
                                else
                                {
                                    setalgo(back, "U R U2 RP U R UP RP");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "UP FP U2 F UP FP U F");
                                }
                                else
                                {
                                    setalgo(back, "U2 R U RP U R UP RP");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP U2 F U FP UP F");
                                }
                                else
                                {
                                    setalgo(back, "R U RP U2 R U RP UP R U RP");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(back, "FP UP F U2 FP UP F U FP UP F");
                                }
                                else
                                {
                                    setalgo(back, "R U2 RP UP R U RP");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 2:
                    if (CubeMain[side][0][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(right, "R U RP UP R U RP UP R U RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(right, "R UP RP U FP U F");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U R U2 RP U R UP RP");
                                }
                                else
                                {
                                    setalgo(right, "U2 FP UP F UP FP U F");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "U2 R U RP U R UP RP");
                                }
                                else
                                {
                                    setalgo(right, "UP FP U2 F UP FP U F");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R U RP U2 R U RP UP R U RP");
                                }
                                else
                                {
                                    setalgo(right, "FP U2 F U FP UP F");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(right, "R U2 RP UP R U RP");
                                }
                                else
                                {
                                    setalgo(right, "FP UP F U2 FP UP F U FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 3:
                    if (CubeMain[side][2][0] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(left, "R U RP UP R U RP UP R U RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(left, "R UP RP U FP U F");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U R U2 RP U R UP RP");
                                }
                                else
                                {
                                    setalgo(left, "U2 FP UP F UP FP U F");
                                }
                            }
                            else if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "U2 R U RP U R UP RP");
                                }
                                else
                                {
                                    setalgo(left, "UP FP U2 F UP FP U F");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R U RP U2 R U RP UP R U RP");
                                }
                                else
                                {
                                    setalgo(left, "FP U2 F U FP UP F");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(left, "R U2 RP UP R U RP");
                                }
                                else
                                {
                                    setalgo(left, "FP UP F U2 FP UP F U FP UP F");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                case 4:
                    if (CubeMain[side][2][2] == bottomColor)
                    {
                        cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                        boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (cornerLocMatch)
                        {
                            if (!boolEdgeSetter)
                            {
                                sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                if (sentinel == 1)
                                {
                                    setalgo(face, "R U RP UP R U RP UP R U RP");
                                }
                                else if (sentinel == 0)
                                {
                                    setalgo(face, "R UP RP U FP U F");
                                }
                                else if (sentinel == -1)
                                {
                                    // this is for the condition when the side elements are not in the correct location....
                                    set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                    find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                }
                            }
                            if (edgeSide == back)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "U2 FP UP F UP FP U F");
                                }
                                else
                                {
                                    setalgo(face, "U R U2 RP U R UP RP");
                                }
                            }
                            else if (edgeSide == left)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "UP FP U2 F UP FP U F");
                                }
                                else
                                {
                                    setalgo(face, "U2 R U RP U R UP RP");
                                }
                            }
                            else if (edgeSide == face)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP U2 F U FP UP F");
                                }
                                else
                                {
                                    setalgo(face, "R U RP U2 R U RP UP R U RP");
                                }
                            }
                            else if (edgeSide == right)
                            {
                                if (topSideColor == cornerColors.at(0))
                                {
                                    setalgo(face, "FP UP F U2 FP UP F U FP UP F");
                                }
                                else
                                {
                                    setalgo(face, "R U2 RP UP R U RP");
                                }
                            }
                        }
                        else
                        {
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            sourceCpy = *this;
            *this = sourceBackup;
            sourceCpy.solver(solutions);
        }
    }
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE LOCATION OF THE BOTTOM COLOR CORNER ON THE BASIS OF THE CORESPONDING COLORS PROVIDED...
   IT SAVES THE SIDE AND BLOCK OF THE CORNER..
   AND RETURNS TRUE IF IT FINDS THE CORNER..
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool F2l::get_corner_location(const char &color_1, const char &color_2, int &side, int &block)
{
    vector<char> colors{color_1, color_2, CubeMain[bottom][1][1]};
    int count{0};
    // first corner..
    count = 0;
    for (int i{0}; i < 3; i++)
    {
        if (CubeMain[face][0][2] == colors[i] ||
            CubeMain[top][2][2] == colors[i] ||
            CubeMain[right][0][0] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[face][0][2] == colors[i])
            {
                side = face;
                block = 2;
            }
            else if (CubeMain[top][2][2] == colors[i])
            {
                side = top;
                block = 4;
            }
            else if (CubeMain[right][0][0] == colors[i])
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
        if (CubeMain[face][0][0] == colors[i] ||
            CubeMain[top][2][0] == colors[i] ||
            CubeMain[left][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[face][0][0] == colors[i])
            {
                side = face;
                block = 1;
            }
            else if (CubeMain[top][2][0] == colors[i])
            {
                side = top;
                block = 3;
            }
            else if (CubeMain[left][0][2] == colors[i])
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
        if (CubeMain[left][0][0] == colors[i] ||
            CubeMain[top][0][0] == colors[i] ||
            CubeMain[back][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[left][0][0] == colors[i])
            {
                side = left;
                block = 1;
            }
            else if (CubeMain[top][0][0] == colors[i])
            {
                side = top;
                block = 1;
            }
            else if (CubeMain[back][0][2] == colors[i])
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
        if (CubeMain[back][0][0] == colors[i] ||
            CubeMain[top][0][2] == colors[i] ||
            CubeMain[right][0][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[back][0][0] == colors[i])
            {
                side = back;
                block = 1;
            }
            else if (CubeMain[top][0][2] == colors[i])
            {
                side = top;
                block = 2;
            }
            else if (CubeMain[right][0][2] == colors[i])
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
        if (CubeMain[face][2][2] == colors[i] ||
            CubeMain[bottom][0][2] == colors[i] ||
            CubeMain[right][2][0] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[face][2][2] == colors[i])
            {
                side = face;
                block = 4;
            }
            else if (CubeMain[bottom][0][2] == colors[i])
            {
                side = bottom;
                block = 2;
            }
            else if (CubeMain[right][2][0] == colors[i])
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
        if (CubeMain[face][2][0] == colors[i] ||
            CubeMain[bottom][0][0] == colors[i] ||
            CubeMain[left][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[face][2][0] == colors[i])
            {
                side = face;
                block = 3;
            }
            else if (CubeMain[bottom][0][0] == colors[i])
            {
                side = bottom;
                block = 1;
            }
            else if (CubeMain[left][2][2] == colors[i])
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
        if (CubeMain[left][2][0] == colors[i] ||
            CubeMain[bottom][2][0] == colors[i] ||
            CubeMain[back][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[left][2][0] == colors[i])
            {
                side = left;
                block = 3;
            }
            else if (CubeMain[bottom][2][0] == colors[i])
            {
                side = bottom;
                block = 3;
            }
            else if (CubeMain[back][2][2] == colors[i])
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
        if (CubeMain[back][2][0] == colors[i] ||
            CubeMain[bottom][2][2] == colors[i] ||
            CubeMain[right][2][2] == colors[i])
            count++;
        if (count == 3)
        {
            if (CubeMain[back][2][0] == colors[i])
            {
                side = back;
                block = 3;
            }
            else if (CubeMain[bottom][2][2] == colors[i])
            {
                side = bottom;
                block = 4;
            }
            else if (CubeMain[right][2][2] == colors[i])
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
   THIS FUNCTION SAVES THE PARTNER SIDE OF THE WHITE CORNER TO THE CORNERCOLORS VECTOR AND CHECKS IF IT IS ON THE RIGHT LOCATION.
   IF IT SI THAN IT RETURNS TRUE ELSE RETURNS FALSE.
      -> PRIORITIES FOR SAVING THE CORNER COLORS ARE -:
        * TOP AND BOTTOM
        * FACE BACK
        * LEFT AND RIGHT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool F2l::find_corner_colors(const char &bottomColor, const int &side, const int &row, const int &col)
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
        if (CubeMain[top][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[top][2][2]);
        ;
        if (CubeMain[face][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[face][0][2]);
        ;
        if (CubeMain[right][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[right][0][0]);
        ;
    }
    else if ((side == face && row == 0 && col == 0) ||
             (side == top && row == 2 && col == 0) ||
             (side == left && row == 0 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (CubeMain[top][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[top][2][0]);
        ;
        if (CubeMain[face][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[face][0][0]);
        ;
        if (CubeMain[left][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[left][0][2]);
        ;
    }
    else if ((side == left && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 0) ||
             (side == back && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (CubeMain[top][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[top][0][0]);
        ;
        if (CubeMain[back][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[back][0][2]);
        ;
        if (CubeMain[left][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[left][0][0]);
        ;
    }
    else if ((side == back && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 2) ||
             (side == right && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(right);
        if (CubeMain[top][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[top][0][2]);
        ;
        if (CubeMain[back][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[back][0][0]);
        ;
        if (CubeMain[right][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[right][0][2]);
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
        if (CubeMain[bottom][0][2] != bottomColor)
            cornerColors.push_back(CubeMain[bottom][0][2]);
        ;
        if (CubeMain[face][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[face][2][2]);
        ;
        if (CubeMain[right][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[right][2][0]);
        ;
    }
    else if ((side == face && row == 2 && col == 0) ||
             (side == bottom && row == 0 && col == 0) ||
             (side == left && row == 2 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(bottom);
        sideloc.push_back(left);
        if (CubeMain[bottom][0][0] != bottomColor)
            cornerColors.push_back(CubeMain[bottom][0][0]);
        ;
        if (CubeMain[face][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[face][2][0]);
        ;
        if (CubeMain[left][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[left][2][2]);
        ;
    }
    else if ((side == left && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 0) ||
             (side == back && row == 2 && col == 2))
    {
        sideloc.push_back(left);
        sideloc.push_back(bottom);
        sideloc.push_back(back);
        if (CubeMain[bottom][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[bottom][2][0]);
        ;
        if (CubeMain[back][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[back][2][2]);
        ;
        if (CubeMain[left][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[left][2][0]);
        ;
    }
    else if ((side == back && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 2) ||
             (side == right && row == 2 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(bottom);
        sideloc.push_back(right);
        if (CubeMain[bottom][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[bottom][2][2]);
        ;
        if (CubeMain[back][2][0] != bottomColor)
            cornerColors.push_back(CubeMain[back][2][0]);
        ;
        if (CubeMain[right][2][2] != bottomColor)
            cornerColors.push_back(CubeMain[right][2][2]);
        ;
    }
    // the bellow code checks the corner is on the right location or not......
    int x{0};
    for (int i{0}; i < 3; i++)
    {
        if (CubeMain[sideloc.at(i)][1][1] == cornerColors.at(0) || CubeMain[sideloc.at(i)][1][1] == cornerColors.at(1))
            x++;
    }
    if (x == 2)
        return true;
    else
        return false;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CHECKS IF THE SIDE ELEMENT IS ON THE TOP OF THE Cube IF IT IS IT RERURNS "TRUE" ELSE IT RETURNS "FALSE".
   IF THE EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT MOVES THE SIDE EDGE TO THE CORRECT LOCATION, ELSE LET IT STAY ON THE SAME LOCATION
   AND MAKES TOPSIDECOLOR === "THE COLOR IN THE TOP OF SIDE ELEMENT"
   AND EDGESIDE === "TO THE SIDE OF TEH EDGE ELEMENT ON THE Cube"
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool F2l::find_edge_in_top_lyr(const char &color_1, const char &color_2, string_view edgeSetter)
{
    bool pos{false};
    // the bellow two assignment is for the precaution of removing past assignments....
    edgeSide = -1;
    topSideColor = 'x';
    while (!pos)
    {
        if (CubeMain[face][0][1] == color_1 && CubeMain[top][2][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == CubeMain[face][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = face;
            topSideColor = color_2;
        }
        else if (CubeMain[top][1][2] == color_2 && CubeMain[right][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == CubeMain[right][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = right;
            topSideColor = color_2;
        }
        else if (CubeMain[top][1][0] == color_2 && CubeMain[left][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == CubeMain[left][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = left;
            topSideColor = color_2;
        }
        else if (CubeMain[top][0][1] == color_2 && CubeMain[back][0][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == CubeMain[back][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = back;
            topSideColor = color_2;
        }
        // if second color is not on the face.....
        else if (CubeMain[face][0][1] == color_2 && CubeMain[top][2][1] == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == CubeMain[face][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = face;
            topSideColor = color_1;
        }
        else if (CubeMain[top][1][2] == color_1 && CubeMain[right][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == CubeMain[right][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = right;
            topSideColor = color_1;
        }
        else if (CubeMain[top][1][0] == color_1 && CubeMain[left][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == CubeMain[left][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = left;
            topSideColor = color_1;
        }
        // back side edges
        else if (CubeMain[top][0][1] == color_1 && CubeMain[back][0][1] == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == CubeMain[back][1][1])
                    pos = true;
                else
                {
                    setalgo(face, "U");
                }
            }
            edgeSide = back;
            topSideColor = color_1;
        }
        else // this block is for stoping the loop from running infinite times...
        {
            break;
        }
        if (edgeSetter != "CALL_EDGE_SETTER")
        { // exit loop if edgeSetter is DO_NOT_CALL to avoid infinite looping
            break;
        }
    }
    // IF MOVECOUNT IS 3 IT IS GOING TO APPLY U-PRIME ELSE IN OTHER TWO CONDITIONS (2,1) IT IS GOING TO APPLY SIMPLE U OPERATIONS.....
    // switch (moveCount)
    // {
    // case 3:
    //     this->tempSolution.push_back("UP");
    //     break;
    // case 2:
    //     this->tempSolution.push_back("U");
    //     this->tempSolution.push_back("U");
    //     break;
    // case 1:
    //     this->tempSolution.push_back("U");
    //     break;
    // default:
    //     break;
    // }
    // applySolution();
    if (edgeSide == -1)
    {
        return false;
    }
    return true;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHECKS FOR THE EDGE ELEMENTS IN THE MID LAYER OF THE Cube.
   AND IF THE EDGE IN ON THE CORRECT LOCATION THAN IT RETURNS "1"
   ELSE IF THE EDGE IN ON THE CORRECT LOCATION BUT IN REVER DIRECTION THAN IT RETURN "0"
   ELSE IF EDGE IS IN NEAR LOCATION THAN IT WILL RETURN "-1" AND WILL MOVE THE EDGE OUT OF THE MID LAYER.
   AND IF EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT WILL CALL THE EDGESETTER_ON_TOP FUNCTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
int F2l::find_edge_in_mid_lyr(const char &color_1, const char &color_2, string_view edgeSetter)
{
    if (CubeMain[face][1][2] == color_1 && CubeMain[right][1][0] == color_2)
    {
        if (color_1 == CubeMain[face][1][1] && color_2 == CubeMain[right][1][1])
        {
            return 1;
        }
        else if (color_2 == CubeMain[face][1][1] && color_1 == CubeMain[right][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[face][1][1] || color_2 == CubeMain[face][1][1])
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == CubeMain[right][1][1] || color_2 == CubeMain[right][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[face][1][2] == color_2 && CubeMain[right][1][0] == color_1)
    {
        if (color_2 == CubeMain[face][1][1] && color_1 == CubeMain[right][1][1])
        {
            return 1;
        }
        else if (color_1 == CubeMain[face][1][1] && color_2 == CubeMain[right][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[face][1][1] || color_2 == CubeMain[face][1][1])
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == CubeMain[right][1][1] || color_2 == CubeMain[right][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[face][1][0] == color_1 && CubeMain[left][1][2] == color_2)
    {
        if (color_1 == CubeMain[face][1][1] && color_2 == CubeMain[left][1][1])
        {
            return 1;
        }
        else if (color_2 == CubeMain[face][1][1] && color_1 == CubeMain[left][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[face][1][1] || color_2 == CubeMain[face][1][1])
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == CubeMain[left][1][1] || color_2 == CubeMain[left][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[face][1][0] == color_2 && CubeMain[left][1][2] == color_1)
    {
        if (color_2 == CubeMain[face][1][1] && color_1 == CubeMain[left][1][1])
        {
            return 1;
        }
        else if (color_1 == CubeMain[face][1][1] && color_2 == CubeMain[left][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[face][1][1] || color_2 == CubeMain[face][1][1])
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == CubeMain[left][1][1] || color_2 == CubeMain[left][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    // BACK SIDE-EDGES
    else if (CubeMain[right][1][2] == color_1 && CubeMain[back][1][0] == color_2)
    {
        if (color_1 == CubeMain[right][1][1] && color_2 == CubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_2 == CubeMain[right][1][1] && color_1 == CubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[right][1][1] || color_2 == CubeMain[right][1][1])
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == CubeMain[back][1][1] || color_2 == CubeMain[back][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[right][1][2] == color_2 && CubeMain[back][1][0] == color_1)
    {
        if (color_2 == CubeMain[right][1][1] && color_1 == CubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_1 == CubeMain[right][1][1] && color_2 == CubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[right][1][1] || color_2 == CubeMain[right][1][1])
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == CubeMain[back][1][1] || color_2 == CubeMain[back][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[left][1][0] == color_1 && CubeMain[back][1][2] == color_2)
    {
        if (color_1 == CubeMain[left][1][1] && color_2 == CubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_2 == CubeMain[left][1][1] && color_1 == CubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[left][1][1] || color_2 == CubeMain[left][1][1])
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == CubeMain[back][1][1] || color_2 == CubeMain[back][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    else if (CubeMain[left][1][0] == color_2 && CubeMain[back][1][2] == color_1)
    {
        if (color_2 == CubeMain[left][1][1] && color_1 == CubeMain[back][1][1])
        {
            return 1;
        }
        else if (color_1 == CubeMain[left][1][1] && color_2 == CubeMain[back][1][1])
        {
            return 0;
        }
        else if (color_1 == CubeMain[left][1][1] || color_2 == CubeMain[left][1][1])
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == CubeMain[back][1][1] || color_2 == CubeMain[back][1][1])
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
            find_edge_in_top_lyr(color_1, color_2, edgeSetter);
        return -1;
    }
    return -1;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
THIS FUNCTION SIMPLY MOVES THE CORNER ELEMENT TO THE CORRECT LOCATION, IF IT IS ON THE TOP SIDE OF THE Cube
   AND IF F2LHELPER === "CALL_F2LHELPER" THAN IT WILL CALL THE REQUIRED SIDE OF F2LHELPER FUNCTION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void F2l::set_corner_on_top(const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper)
{
    // temp_Cube = *this;
    vector<char> colors{color_2, color_3};
    int colorCount{0}, side{-1}, colorBlock{-1};
    bool pos{false};
    while (!pos)
    {
        colorCount = 0;
        //--------------------- ifs for TOP , FACE AND RIGHT ANGLED CORNER ---------------------
        if (CubeMain[top][2][2] == color_1 && CubeMain[face][0][2] == color_2 && CubeMain[right][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][2] == color_3 && CubeMain[face][0][2] == color_1 && CubeMain[right][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][2] == color_2 && CubeMain[face][0][2] == color_3 && CubeMain[right][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][2] == color_3 && CubeMain[face][0][2] == color_2 && CubeMain[right][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][2] == color_1 && CubeMain[face][0][2] == color_3 && CubeMain[right][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][2] == color_2 && CubeMain[face][0][2] == color_1 && CubeMain[right][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        //--------------------- ifs for TOP , BACK AND RIGHT ANGLED CORNER ----------------------
        else if (CubeMain[top][0][2] == color_1 && CubeMain[back][0][0] == color_2 && CubeMain[right][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][2] == color_3 && CubeMain[back][0][0] == color_1 && CubeMain[right][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][2] == color_2 && CubeMain[back][0][0] == color_3 && CubeMain[right][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][2] == color_3 && CubeMain[back][0][0] == color_2 && CubeMain[right][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][2] == color_1 && CubeMain[back][0][0] == color_3 && CubeMain[right][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][2] == color_2 && CubeMain[back][0][0] == color_1 && CubeMain[right][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[right][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        //--------------------- ifs for TOP , BACK AND LEFT ANGLED CORNER ----------------------
        else if (CubeMain[top][0][0] == color_1 && CubeMain[back][0][2] == color_2 && CubeMain[left][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][0] == color_3 && CubeMain[back][0][2] == color_1 && CubeMain[left][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][0] == color_2 && CubeMain[back][0][2] == color_3 && CubeMain[left][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][0] == color_3 && CubeMain[back][0][2] == color_2 && CubeMain[left][0][0] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][0] == color_1 && CubeMain[back][0][2] == color_3 && CubeMain[left][0][0] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][0][0] == color_2 && CubeMain[back][0][2] == color_1 && CubeMain[left][0][0] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[back][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        //--------------------- ifs for TOP , FACE AND LEFT ANGLED CORNER ----------------------
        else if (CubeMain[top][2][0] == color_1 && CubeMain[face][0][0] == color_2 && CubeMain[left][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][0] == color_3 && CubeMain[face][0][0] == color_1 && CubeMain[left][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][0] == color_2 && CubeMain[face][0][0] == color_3 && CubeMain[left][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][0] == color_3 && CubeMain[face][0][0] == color_2 && CubeMain[left][0][2] == color_1)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][0] == color_1 && CubeMain[face][0][0] == color_3 && CubeMain[left][0][2] == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else if (CubeMain[top][2][0] == color_2 && CubeMain[face][0][0] == color_1 && CubeMain[left][0][2] == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (CubeMain[face][1][1] == colors[i] || CubeMain[left][1][1] == colors[i])
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
                setalgo(face, "U");
            }
        }
        else
        {
            pos = true;
        }
        // if (moveCount == 0)
        // {
        //     pos = true;
        // }
    }

    // switch (moveCount)
    // {
    // case 3:
    //     this->tempSolution.push_back("UP");
    //     break;
    // case 2:
    //     this->tempSolution.push_back("U");
    //     this->tempSolution.push_back("U");
    //     break;
    // case 1:
    //     this->tempSolution.push_back("U");
    //     break;
    // default:
    //     break;
    // }
    // applySolution("f2l");
    if (F2LHelper == "CALL_F2LHELPER")
        f2LHelper(side, colorBlock);
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON EXECUTES THE ELGORITHEMS OF F2L_LAYER ON THE BASIS OF THE SIDE AND COLORBLOCK VALUE PROVIDED
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void F2l::f2LHelper(const int &side, const int &colorBlock)
{
    // temp_Cube = *this;
    int sentinel;
    const char bottomColor{CubeMain[bottom][1][1]};
    bool cornerLocMatch{false}, boolEdgeSetter{false};

    // -------------------------------------------------- FACE SIDE ---------------------------------------------------------------
    if (side == face)
    {
        switch (colorBlock)
        {
        case 1:
            if (CubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "U FP U F U FP U2 F");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "U FP UP F UP R U RP");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R UP RP U2 FP UP F");
                        }
                        else
                        {
                            setalgo(left, "UP R UP RP U R U RP");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP U2 F U FP U2 F");
                        }
                        else
                        {
                            setalgo(left, "R U RP");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP UP F U FP U2 F");
                        }
                        else
                        {
                            setalgo(left, "UP R U RP U R U RP");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "F RP FP R");
                        }
                        else
                        {
                            setalgo(left, "U FP U2 F UP R U RP");
                        }
                    }
                }
            }
            break;
        case 2:
            if (CubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "UP R UP RP UP R U2 RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "UP R U RP U FP UP F");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U F U2 R U RP");
                        }
                        else
                        {
                            setalgo(face, "U FP U F UP FP UP F");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U R UP RP");
                        }
                        else
                        {
                            setalgo(face, "UP R U2 RP U FP UP F");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(face, "U FP UP F UP FP UP F");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U2 RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(face, "FP UP F");
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
            if (CubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "U FP U F U FP U2 F");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "U FP UP F UP R U RP");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "R UP RP U2 FP UP F");
                        }
                        else
                        {
                            setalgo(face, "UP R UP RP U R U RP");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP U2 F U FP U2 F");
                        }
                        else
                        {
                            setalgo(face, "R U RP");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP UP F U FP U2 F");
                        }
                        else
                        {
                            setalgo(face, "UP R U RP U R U RP");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "F RP FP R");
                        }
                        else
                        {
                            setalgo(face, "U FP U2 F UP R U RP");
                        }
                    }
                }
            }
            break;
        case 2:
            if (CubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "UP R UP RP UP R U2 RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "UP R U RP U FP UP F");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "FP U F U2 R U RP");
                        }
                        else
                        {
                            setalgo(right, "U FP U F UP FP UP F");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R UP RP");
                        }
                        else
                        {
                            setalgo(right, "UP R U2 RP U FP UP F");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(right, "U FP UP F UP FP UP F");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U2 RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(right, "FP UP F");
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
            if (CubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "U FP U F U FP U2 F");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "U FP UP F UP R U RP");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R UP RP U2 FP UP F");
                        }
                        else
                        {
                            setalgo(right, "UP R UP RP U R U RP");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP U2 F U FP U2 F");
                        }
                        else
                        {
                            setalgo(right, "R U RP");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP UP F U FP U2 F");
                        }
                        else
                        {
                            setalgo(right, "UP R U RP U R U RP");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "F RP FP R");
                        }
                        else
                        {
                            setalgo(right, "U FP U2 F UP R U RP");
                        }
                    }
                }
            }
            break;
        case 2:
            if (CubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "UP R UP RP UP R U2 RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "UP R U RP U FP UP F");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U F U2 R U RP");
                        }
                        else
                        {
                            setalgo(back, "U FP U F UP FP UP F");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U R UP RP");
                        }
                        else
                        {
                            setalgo(back, "UP R U2 RP U FP UP F");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(back, "U FP UP F UP FP UP F");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U2 RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(back, "FP UP F");
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
            if (CubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "U FP U F U FP U2 F");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "U FP UP F UP R U RP");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "R UP RP U2 FP UP F");
                        }
                        else
                        {
                            setalgo(back, "UP R UP RP U R U RP");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP U2 F U FP U2 F");
                        }
                        else
                        {
                            setalgo(back, "R U RP");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP UP F U FP U2 F");
                        }
                        else
                        {
                            setalgo(back, "UP R U RP U R U RP");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "F RP FP R");
                        }
                        else
                        {
                            setalgo(back, "U FP U2 F UP R U RP");
                        }
                    }
                }
            }
            break;
        case 2:
            if (CubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "UP R UP RP UP R U2 RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "UP R U RP U FP UP F");
                        }
                        else if (sentinel == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "FP U F U2 R U RP");
                        }
                        else
                        {
                            setalgo(left, "U FP U F UP FP UP F");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R UP RP");
                        }
                        else
                        {
                            setalgo(left, "UP R U2 RP U FP UP F");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(left, "U FP UP F UP FP UP F");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U2 RP UP R U2 RP");
                        }
                        else
                        {
                            setalgo(left, "FP UP F");
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
            if (CubeMain[side][0][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(back, "R U RP UP R U RP UP R U RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(back, "R UP RP U FP U F");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U2 FP UP F UP FP U F");
                        }
                        else
                        {
                            setalgo(back, "U R U2 RP U R UP RP");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP FP U2 F UP FP U F");
                        }
                        else
                        {
                            setalgo(back, "U2 R U RP U R UP RP");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U2 F U FP UP F");
                        }
                        else
                        {
                            setalgo(back, "R U RP U2 R U RP UP R U RP");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP UP F U2 FP UP F U FP UP F");
                        }
                        else
                        {
                            setalgo(back, "R U2 RP UP R U RP");
                        }
                    }
                }
            }
            break;
        case 2:
            if (CubeMain[side][0][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 0, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(right, "R U RP UP R U RP UP R U RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(right, "R UP RP U FP U F");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R U2 RP U R UP RP");
                        }
                        else
                        {
                            setalgo(right, "U2 FP UP F UP FP U F");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U2 R U RP U R UP RP");
                        }
                        else
                        {
                            setalgo(right, "UP FP U2 F UP FP U F");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U RP U2 R U RP UP R U RP");
                        }
                        else
                        {
                            setalgo(right, "FP U2 F U FP UP F");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U2 RP UP R U RP");
                        }
                        else
                        {
                            setalgo(right, "FP UP F U2 FP UP F U FP UP F");
                        }
                    }
                }
            }
            break;
        case 3:
            if (CubeMain[side][2][0] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 2, 0);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(left, "R U RP UP R U RP UP R U RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(left, "R UP RP U FP U F");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R U2 RP U R UP RP");
                        }
                        else
                        {
                            setalgo(left, "U2 FP UP F UP FP U F");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U2 R U RP U R UP RP");
                        }
                        else
                        {
                            setalgo(left, "UP FP U2 F UP FP U F");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U RP U2 R U RP UP R U RP");
                        }
                        else
                        {
                            setalgo(left, "FP U2 F U FP UP F");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U2 RP UP R U RP");
                        }
                        else
                        {
                            setalgo(left, "FP UP F U2 FP UP F U FP UP F");
                        }
                    }
                }
            }
            break;
        case 4:
            if (CubeMain[side][2][2] == bottomColor)
            {
                cornerLocMatch = find_corner_colors(bottomColor, side, 2, 2);
                boolEdgeSetter = find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinel = find_edge_in_mid_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinel == 1)
                        {
                            setalgo(face, "R U RP UP R U RP UP R U RP");
                        }
                        else if (sentinel == 0)
                        {
                            setalgo(face, "R UP RP U FP U F");
                        }
                        else if (sentinel == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            set_corner_on_top(bottomColor, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            find_edge_in_top_lyr(cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U2 FP UP F UP FP U F");
                        }
                        else
                        {
                            setalgo(face, "U R U2 RP U R UP RP");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP FP U2 F UP FP U F");
                        }
                        else
                        {
                            setalgo(face, "U2 R U RP U R UP RP");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U2 F U FP UP F");
                        }
                        else
                        {
                            setalgo(face, "R U RP U2 R U RP UP R U RP");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP UP F U2 FP UP F U FP UP F");
                        }
                        else
                        {
                            setalgo(face, "R U2 RP UP R U RP");
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
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE Cube AND SAVES THE ALGORITHM TO THE f2lSolution
   AND THEN CLEARS THE TEMPSOLUTION.
   ---------------------------------------------------------------------------------------------------------------------------------------- */
void F2l::applySolution(bool apply) // overriden function...
{
    Cube::applyTempSolution();
    if (apply)
    {
        for (size_t i{0}; i < tempSolution.size(); i++)
            solution.push_back(tempSolution.at(i));
    }
    tempSolution.clear(); // clear the tempsolutoin to avoid additional application..
}