#include "Oll.h"
#include "Optimiser.h"

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE OLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE OLL CONDITIONS WILL MATCHES AND SOLVES THE OLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
vector<string> Oll::solver()
{
    solution.clear();
    bool solve{false};
    string OLLcode{};
    OLLcode = oll_coder();
    for (int i{0}; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            solve = oll_logic(face, OLLcode);
            if (!solve)
            {
                U;
            }
            break;
        case 1:
            UP;
            solve = oll_logic(right, OLLcode);
            if (!solve)
            {
                U;
                U;
            }
            break;
        case 2:
            U;
            U;
            solve = oll_logic(back, OLLcode);
            if (!solve)
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
        if (solve)
        {
            Optimiser::optimise(solution);
            return solution;
        }
        OLLcode = oll_coder();
    }
    cerr << "error solving Oll layer...." << endl;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CODES THE OLL LAYER IN '1' AND '0' CHARACTER.
   THE VERY FIRST 9 CHARACTERS ARE FOR TOP SIDE
   THE OTHER THREE FOR FIRST ROW OF FACE AND
   THE OTHER THREE FOR FIRST ROW OF RIGHT AND
   THE OTHER THREE FOR FIRST ROW OF BACK AND
   THE LAST THREE CHARACHTER IS FOR FIRST ROW OF LEFT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string Oll::oll_coder()
{
    const char top_color{CubeMain[top][1][1]};
    string OLLCode{};
    // CODING TOP SIDE OF THE Cube.....
    for (auto vecOfvec : CubeMain[top])
        for (auto vecOfchar : vecOfvec)
            if (vecOfchar == top_color)
                OLLCode += '1';
            else
                OLLCode += '0';
    // CODING FIRST ROW OF FACE SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[face][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF RIGHT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[right][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF BACK SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[back][0])
        if (vecOfchar == top_color)
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF LEFT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[left][0])
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
bool Oll::oll_logic(const int &side, string_view OLLcode)
{
    if (OLLcode == "111111111000000000000")
    {
        return true;
    }
    // DOT CONDITIONS...
    else if (OLLcode == "000010000010111010111")
    {
        setalgo(side, "R U BP R B R2 UP RP F R FP");
    }
    else if (OLLcode == "000010000111011010110")
    {
        setalgo(side, "RP F R FP U2 RP F R F2 U2 F");
    }
    else if (OLLcode == "000010001010011011011")
    {
        setalgo(side, "B U L UP LP BP U B L U LP UP BP");
    }
    else if (OLLcode == "001010000110110010110")
    {
        setalgo(side, "RP U2 RP F R FP UP FP UP F UP R");
    }
    else if (OLLcode == "100010001010010110011")
    {
        setalgo(side, "R U RP U RP F R FP U2 RP F R FP");
    }
    else if (OLLcode == "101010101010010010010")
    {
        setalgo(side, "MP U2 M U2 MP U M U2 MP U2 M");
    }
    else if (OLLcode == "101010000010110010011")
    {
        setalgo(side, "RP U2 F R U RP UP F2 U2 F R");
    }
    else if (OLLcode == "000010101010010111010")
    {
        setalgo(side, "F R U RP U FP U2 FP L F LP");
    }
    // LINE CONDITIONS...
    else if (OLLcode == "010010010100111001010")
    {
        setalgo(side, "RP UP FP U FP L F LP F R");
    }
    else if (OLLcode == "010010010000111000111")
    {
        setalgo(side, "R UP B2 D BP U2 B DP B2 U RP");
    }
    else if (OLLcode == "000111000110101011000")
    {
        setalgo(side, "F U R UP RP U R UP RP FP");
    }
    else if (OLLcode == "000111000010101010101")
    {
        setalgo(side, "LP BP L UP RP U R UP RP U R LP B L");
    }
    // CROSS CONDITION....
    else if (OLLcode == "010111010100101001000")
    {
        setalgo(side, "L UP RP U LP U R U RP U R");
    }
    else if (OLLcode == "010111010000101000101")
    {
        setalgo(side, "R U RP U R UP RP U R U2 RP");
    }
    else if (OLLcode == "010111011100000100100")
    {
        setalgo(side, "LP U R UP L U RP");
    }
    else if (OLLcode == "010111011000001001001")
    {
        setalgo(side, "RP U2 R U RP U R");
    }
    else if (OLLcode == "110111110001000100000")
    {
        setalgo(side, "RP FP L F R FP LP F");
    }
    else if (OLLcode == "111111010101000000000")
    {
        setalgo(side, "R2 D RP U2 R DP RP U2 RP");
    }
    else if (OLLcode == "110111011000000100001")
    {
        setalgo(side, "RP FP LP F R FP L F");
    }
    // 4 CORNERS....
    else if (OLLcode == "101110111000010010000")
    {
        setalgo(side, "MP UP M U2 MP UP M");
    }
    else if (OLLcode == "101111101010000010000")
    {
        setalgo(side, "LP R U RP UP L RP F R FP");
    }
    // SHAPE _| .......
    else if (OLLcode == "010110100011011001000")
    {
        setalgo(side, "L F RP F R F2 LP");
    }
    else if (OLLcode == "110110001110011000000")
    {
        setalgo(side, "F RP FP R U R UP RP");
    }
    else if (OLLcode == "010110001110010100100")
    {
        setalgo(side, "RP UP R F RP FP U F R FP");
    }
    else if (OLLcode == "010110101010010101000")
    {
        setalgo(side, "UP R U2 RP UP R UP R2 FP UP F U R");
    }
    else if (OLLcode == "010110000011010100101")
    {
        setalgo(side, "F R U RP UP R U RP UP FP");
    }
    else if (OLLcode == "010110000111010101000")
    {
        setalgo(side, "L FP LP F U2 L2 B L BP L");
    }
    // SHAPE \_ .....
    else if (OLLcode == "010011101010000101010")
    {
        setalgo(side, "UP RP U2 R U RP U R2 B U BP UP RP");
    }
    else if (OLLcode == "011011000110100000110")
    {
        setalgo(side, "L F2 RP FP R FP LP");
    }
    else if (OLLcode == "010011000110101001010")
    {
        setalgo(side, "FP LP UP L U LP UP L U F");
    }
    else if (OLLcode == "011011100010100001010")
    {
        setalgo(side, "RP U2 R2 BP RP B RP U2 R");
    }
    else if (OLLcode == "010011000111000101010")
    {
        setalgo(side, "RP F R FP U2 R2 BP RP B RP");
    }
    else if (OLLcode == "010011000011000100111")
    {
        setalgo(side, "RP F RP FP R2 U2 BP R B RP");
    }
    // SHAPE -\ .....
    else if (OLLcode == "001110010001010011001")
    {
        setalgo(side, "R U RP BP R B UP BP RP B");
    }
    else if (OLLcode == "100110010100110110000")
    {
        setalgo(side, "LP BP L UP RP U R LP B L");
    }
    else if (OLLcode == "000110011100010110100")
    {
        setalgo(side, "M LP UP L UP LP U2 L UP MP");
    }
    else if (OLLcode == "101110010000110010001")
    {
        setalgo(side, "BP R BP R2 U R U RP UP R B2");
    }
    // SHAPE \- ....
    else if (OLLcode == "000011010001000110111")
    {
        setalgo(side, "LP B L2 FP L2 BP L2 F LP");
    }
    else if (OLLcode == "000011110001001011010")
    {
        setalgo(side, "M R U RP U R U2 RP U MP");
    }
    else if (OLLcode == "000011011000001011011")
    {
        setalgo(side, "LP B2 R B RP B L");
    }
    else if (OLLcode == "101011010000100010011")
    {
        setalgo(side, "R2 U RP BP R UP R2 U R B RP");
    }
    // SHAPE C ....
    else if (OLLcode == "110010110000111000010")
    {
        setalgo(side, "R U R BP RP B UP RP");
    }
    else if (OLLcode == "000111101010001010100")
    {
        setalgo(side, "R U RP UP BP RP F R FP B");
    }
    // SHAPE L ....
    else if (OLLcode == "000111001110000110100")
    {
        setalgo(side, "RP F R U RP FP R F UP FP");
    }
    else if (OLLcode == "000111100011001011000")
    {
        setalgo(side, "L FP LP UP L F LP FP U F");
    }
    else if (OLLcode == "000111001010001011001")
    {
        setalgo(side, "LP BP L RP UP R U LP B L");
    }
    else if (OLLcode == "000111100010100110100")
    {
        setalgo(side, "R B RP L U LP UP R BP RP");
    }
    // SHAPE P .....
    else if (OLLcode == "110110100010111000000")
    {
        setalgo(side, "F U R UP RP FP");
    }
    else if (OLLcode == "011011001110000001010")
    {
        setalgo(side, "RP UP F U R UP RP FP R");
    }
    else if (OLLcode == "110110100011010100000")
    {
        setalgo(side, "L U FP UP LP U L F LP");
    }
    else if (OLLcode == "011011001010000000111")
    {
        setalgo(side, "FP UP LP U L F");
    }
    // SHAPE T .....
    else if (OLLcode == "001111001010000010101")
    {
        setalgo(side, "F R U RP UP FP");
    }
    else if (OLLcode == "001111001110000011000")
    {
        setalgo(side, "R U RP UP RP F R FP");
    }
    // SHAPE W ....
    else if (OLLcode == "001011110001000010110")
    {
        setalgo(side, "L U LP U L UP LP UP LP B L BP");
    }
    else if (OLLcode == "100110011100011010000")
    {
        setalgo(side, "RP UP R UP RP U R U R BP RP B");
    }
    // SHAPE Z ....
    else if (OLLcode == "100111001010000110001")
    {
        setalgo(side, "RP F R U RP UP FP U R");
    }
    else if (OLLcode == "001111100010100011000")
    {
        setalgo(side, "L FP LP UP L U F UP LP");
    }
    else
        return false;
    return true;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE Cube AND SAVES THE ALGORITHM TO THE f2lSolution
   AND THEN CLEARS THE TEMPSOLUTION.
   ---------------------------------------------------------------------------------------------------------------------------------------- */
void Oll::applySolution(bool apply) // overriden function...
{
    Cube::applyTempSolution();
    if (apply)
    {
        for (size_t i{0}; i < tempSolution.size(); i++)
            solution.push_back(tempSolution.at(i));
    }
    tempSolution.clear(); // clear the tempsolutoin to avoid additional application..
}
