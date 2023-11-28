#include "Pll.h"
#include <vector>
#include "Optimiser.h"
#include <algorithm>

Pll::Pll() : Cube() {}
Pll::Pll(const Cube &cube) : Cube(cube) {}

Pll &Pll::operator=(const Pll &pll)
{
    Cube::operator=(pll);
    if (this != &pll)
        this->solution = pll.solution;
    return *this;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE PLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE PLL CONDITIONS WILL MATCHES AND SOLVES THE PLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Pll::solver(vector<vector<string>> &solutions)
{
    solution.clear();
    bool solve{false};
    string PLLcode{};
    vector<char> orientation = get_equator_colors_orientation();
    for (int ornt_chng{0}; ornt_chng < 4; ornt_chng++)
    {
        PLLcode = pll_coder(orientation);
        for (int rotate{0}; rotate < 4; rotate++)
        {
            switch (rotate)
            {
            case 0:
                solve = pll_logic(face, PLLcode);
                if (!solve)
                    U;
                break;
            case 1:
                UP;
                solve = pll_logic(right, PLLcode);
                if (!solve)
                    U2;
                break;
            case 2:
                U2;
                solve = pll_logic(back, PLLcode);
                if (!solve)
                    UP;
                break;
            case 3:
                U;
                solve = pll_logic(left, PLLcode);
                break;
            default:
                break;
            }
            if (solve)
            {
                // solution_optimizer(pllSolution);
                correct_last_layer();
                Optimiser::optimise(solution);
                solutions.push_back(solution);
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
   THIS FUNCTION THIS FUNCTION RETURNS THE MAIN ORIENTATION OF THE CROSS COLORS.....
   AND A TEMPRORY solver CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<char> Pll::get_equator_colors_orientation()
{
    vector<char> crossColorOrientation{};
    crossColorOrientation.push_back(CubeMain[face][1][1]);
    crossColorOrientation.push_back(CubeMain[right][1][1]);
    crossColorOrientation.push_back(CubeMain[back][1][1]);
    crossColorOrientation.push_back(CubeMain[left][1][1]);
    return std::move(crossColorOrientation);
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CODES THE PLL LAYER IN 0, 1, 2, 3 IN RESPECT TO THEIR COLOR ORIENTATION CHARACTER.
   THE FIRST THREE CHAR IS FOR FIRST ROW OF FACE AND
   THE OTHER THREE CHAR IS FOR FIRST ROW OF RIGHT AND
   THE OTHER THREE CHAR IS FOR FIRST ROW OF BACK AND
   THE LAST THREE CHARACHTER IS FOR FIRST ROW OF LEFT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string Pll::pll_coder(const vector<char> &orientation)
{
    string PLLcode{};
    // CODING FIRST ROW OF FACE SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[face][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF RIGHT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[right][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF BACK SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[back][0])
        for (int i{0}; i < orientation.size(); i++)
            if (orientation.at(i) == vecOfchar)
                PLLcode += to_string(i);
    // CODING FIRST ROW OF LEFT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[left][0])
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
bool Pll::pll_logic(const int &side, string_view PLLcode)
{
    if (PLLcode == "000111222333")
        return true;
    // A-PERMS..
    else if (PLLcode == "001212320133")
        setalgo(side, "R2 B2 R F RP B2 R FP R");
    else if (PLLcode == "300113021232")
        setalgo(side, "L2 B2 LP FP L B2 LP F LP");
    // U-PERMS.
    else if (PLLcode == "030101222313")
        setalgo(side, "R2 U R U RP UP RP UP RP U RP");
    else if (PLLcode == "010131222303")
        setalgo(side, "R UP R U R U R UP RP UP R2");
    // H-PERM..
    else if (PLLcode == "020131202313")
        setalgo(side, "M2 U M2 U2 M2 U M2");
    // T-PERM..
    else if (PLLcode == "001230122313")
        setalgo(side, "R U RP UP RP F R2 UP RP UP R U RP FP");
    // J-PERMS..
    else if (PLLcode == "000112331223")
        setalgo(side, "RP U LP U2 R UP RP U2 R L UP");
    else if (PLLcode == "011200122333")
        setalgo(side, "R U RP FP R U RP UP RP F R2 UP RP UP");
    // R-PERMS...
    else if (PLLcode == "030112321203")
        setalgo(side, "L U2 LP U2 L FP LP UP L U L F L2 U");
    else if (PLLcode == "010102321233")
        setalgo(side, "RP U2 R U2 RP F R U RP UP RP FP R2 UP");
    // V-PERM...
    else if (PLLcode == "002321210133")
        setalgo(side, "RP U RP UP BP RP B2 UP BP U BP R B R");
    // G-PERMS...
    else if (PLLcode == "300123031212")
        setalgo(side, "R2 D BP U BP UP B DP R2 FP U F");
    else if (PLLcode == "132311203020")
        setalgo(side, "RP UP R B2 D LP U L UP L DP B2");
    else if (PLLcode == "132301223010")
        setalgo(side, "R2 DP F UP F U FP D R2 B UP BP");
    else if (PLLcode == "320113031202")
        setalgo(side, "R U RP F2 DP L UP LP U LP D F2");
    // F-PERM...
    else if (PLLcode == "103031222310")
        setalgo(side, "RP U2 RP UP BP RP B2 UP BP U BP R B UP R");
    // Z-PERM...
    else if (PLLcode == "010101232323")
        setalgo(side, "M2 U M2 U MP U2 M2 U2 MP U2");
    // Y-PERM...
    else if (PLLcode == "002311230123")
        setalgo(side, "F R UP RP UP R U RP FP R U RP UP RP F R FP");
    // N-PERMS...
    else if (PLLcode == "022311200133")
        setalgo(side, "L UP R U2 LP U RP L UP R U2 LP U RP U");
    else if (PLLcode == "220113002331")
        setalgo(side, "RP U LP U2 R UP L RP U LP U2 R UP L UP");
    // E-PERM...
    else if (PLLcode == "301210123032")
        setalgo(side, "R BP RP F R B RP F2 LP B L F LP BP L");
    else
        return false;
    return true;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE Cube AND SAVES THE ALGORITHM TO THE f2lSolution
   AND THEN CLEARS THE TEMPSOLUTION.
   ---------------------------------------------------------------------------------------------------------------------------------------- */
void Pll::applySolution(bool apply) // overriden function...
{
    Cube::applyTempSolution();
    if (apply)
    {
        for (size_t i{0}; i < tempSolution.size(); i++)
            solution.push_back(tempSolution.at(i));
    }
    tempSolution.clear(); // clear the tempsolutoin to avoid additional application..
}

void Pll::correct_last_layer()
{
    for (int move{0}; move < 4; move++)
        if (CubeMain[face][0][1] != CubeMain[face][1][1])
            setalgo(face, "U");
        else
            break;
}
