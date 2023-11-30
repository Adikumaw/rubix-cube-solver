#include "Oll.h"
#include "Optimiser.h"

Oll::Oll() : Cube() {}
Oll::Oll(const Cube &cube) : Cube(cube) {}

Oll &Oll::operator=(const Oll &oll)
{
    Cube::operator=(oll);
    if (this != &oll)
        this->solution = oll.solution;
    return *this;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE OLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE OLL CONDITIONS WILL MATCHES AND SOLVES THE OLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Oll::solver(vector<vector<string>> &solutions)
{
    solution.clear();
    bool solve{false};
    // string OLLcode{};
    long int ollCode;
    ollCode = oll_coder();
    for (int i{0}; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            solve = oll_logic(face, ollCode);
            if (!solve)
            {
                U;
            }
            break;
        case 1:
            UP;
            solve = oll_logic(right, ollCode);
            if (!solve)
            {
                U;
                U;
            }
            break;
        case 2:
            U;
            U;
            solve = oll_logic(back, ollCode);
            if (!solve)
            {
                UP;
            }
            break;
        case 3:
            U;
            solve = oll_logic(left, ollCode);
            break;
        default:
            break;
        }
        if (solve)
        {
            Optimiser::optimise(solution);
            solutions.push_back(solution);
            return;
        }
        ollCode = oll_coder();
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
long int Oll::oll_coder()
{
    const char top_color{CubeMain[top][1][1]};
    // string OLLCode{};
    long int ollCode{0};
    // CODING TOP SIDE OF THE Cube.....
    for (auto vecOfvec : CubeMain[top])
        for (auto vecOfchar : vecOfvec)
            if (vecOfchar == top_color)
                ollCode = (ollCode << 1 | 1);
            else
                ollCode = ollCode << 1;

    // CODING FIRST ROW OF FACE SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[face][0])
        if (vecOfchar == top_color)
            ollCode = (ollCode << 1 | 1);
        else
            ollCode = ollCode << 1;

    // CODING FIRST ROW OF RIGHT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[right][0])
        if (vecOfchar == top_color)
            ollCode = (ollCode << 1 | 1);
        else
            ollCode = ollCode << 1;

    // CODING FIRST ROW OF BACK SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[back][0])
        if (vecOfchar == top_color)
            ollCode = (ollCode << 1 | 1);
        else
            ollCode = ollCode << 1;

    // CODING FIRST ROW OF LEFT SIDE OF THE Cube.....
    for (auto vecOfchar : CubeMain[left][0])
        if (vecOfchar == top_color)
            ollCode = (ollCode << 1 | 1);
        else
            ollCode = ollCode << 1;

    return ollCode; // RETURNING THE FULLY CODED STRING.....
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION HAVE SOLUTION FOR ALL THE CONDITIONS POSSIBLE IN OLL
   LAYER AND IT DIRECTLY CALLS THE SETALGO TO APPLY THE CONDITION.
   IT RETURNS TRUE IF THE CONDITION MATCHES THE CODE AND FALSE WHEN OLLCODE DOSEN'T MATCHES ANY CONDITION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool Oll::oll_logic(const int &side, long int ollCode)
{
    if (ollCode == 0b111111111000000000000L)
    {
        return true;
    }
    // DOT CONDITIONS...
    else if (ollCode == 0b000010000010111010111L)
    {
        setalgo(side, "R U BP R B R2 UP RP F R FP");
    }
    else if (ollCode == 0b000010000111011010110L)
    {
        setalgo(side, "RP F R FP U2 RP F R F2 U2 F");
    }
    else if (ollCode == 0b000010001010011011011L)
    {
        setalgo(side, "B U L UP LP BP U B L U LP UP BP");
    }
    else if (ollCode == 0b001010000110110010110L)
    {
        setalgo(side, "RP U2 RP F R FP UP FP UP F UP R");
    }
    else if (ollCode == 0b100010001010010110011L)
    {
        setalgo(side, "R U RP U RP F R FP U2 RP F R FP");
    }
    else if (ollCode == 0b101010101010010010010L)
    {
        setalgo(side, "MP U2 M U2 MP U M U2 MP U2 M");
    }
    else if (ollCode == 0b101010000010110010011L)
    {
        setalgo(side, "RP U2 F R U RP UP F2 U2 F R");
    }
    else if (ollCode == 0b000010101010010111010L)
    {
        setalgo(side, "F R U RP U FP U2 FP L F LP");
    }
    // LINE CONDITIONS...
    else if (ollCode == 0b010010010100111001010L)
    {
        setalgo(side, "RP UP FP U FP L F LP F R");
    }
    else if (ollCode == 0b010010010000111000111L)
    {
        setalgo(side, "R UP B2 D BP U2 B DP B2 U RP");
    }
    else if (ollCode == 0b000111000110101011000L)
    {
        setalgo(side, "F U R UP RP U R UP RP FP");
    }
    else if (ollCode == 0b000111000010101010101L)
    {
        setalgo(side, "LP BP L UP RP U R UP RP U R LP B L");
    }
    // CROSS CONDITION....
    else if (ollCode == 0b010111010100101001000L)
    {
        setalgo(side, "L UP RP U LP U R U RP U R");
    }
    else if (ollCode == 0b010111010000101000101L)
    {
        setalgo(side, "R U RP U R UP RP U R U2 RP");
    }
    else if (ollCode == 0b010111011100000100100L)
    {
        setalgo(side, "LP U R UP L U RP");
    }
    else if (ollCode == 0b010111011000001001001L)
    {
        setalgo(side, "RP U2 R U RP U R");
    }
    else if (ollCode == 0b110111110001000100000L)
    {
        setalgo(side, "RP FP L F R FP LP F");
    }
    else if (ollCode == 0b111111010101000000000L)
    {
        setalgo(side, "R2 D RP U2 R DP RP U2 RP");
    }
    else if (ollCode == 0b110111011000000100001L)
    {
        setalgo(side, "RP FP LP F R FP L F");
    }
    // 4 CORNERS....
    else if (ollCode == 0b101110111000010010000L)
    {
        setalgo(side, "MP UP M U2 MP UP M");
    }
    else if (ollCode == 0b101111101010000010000L)
    {
        setalgo(side, "LP R U RP UP L RP F R FP");
    }
    // SHAPE _| .......
    else if (ollCode == 0b010110100011011001000L)
    {
        setalgo(side, "L F RP F R F2 LP");
    }
    else if (ollCode == 0b110110001110011000000L)
    {
        setalgo(side, "F RP FP R U R UP RP");
    }
    else if (ollCode == 0b010110001110010100100L)
    {
        setalgo(side, "RP UP R F RP FP U F R FP");
    }
    else if (ollCode == 0b010110101010010101000L)
    {
        setalgo(side, "UP R U2 RP UP R UP R2 FP UP F U R");
    }
    else if (ollCode == 0b010110000011010100101L)
    {
        setalgo(side, "F R U RP UP R U RP UP FP");
    }
    else if (ollCode == 0b010110000111010101000L)
    {
        setalgo(side, "L FP LP F U2 L2 B L BP L");
    }
    // SHAPE \_ .....
    else if (ollCode == 0b010011101010000101010L)
    {
        setalgo(side, "UP RP U2 R U RP U R2 B U BP UP RP");
    }
    else if (ollCode == 0b011011000110100000110L)
    {
        setalgo(side, "L F2 RP FP R FP LP");
    }
    else if (ollCode == 0b010011000110101001010L)
    {
        setalgo(side, "FP LP UP L U LP UP L U F");
    }
    else if (ollCode == 0b011011100010100001010L)
    {
        setalgo(side, "RP U2 R2 BP RP B RP U2 R");
    }
    else if (ollCode == 0b010011000111000101010L)
    {
        setalgo(side, "RP F R FP U2 R2 BP RP B RP");
    }
    else if (ollCode == 0b010011000011000100111L)
    {
        setalgo(side, "RP F RP FP R2 U2 BP R B RP");
    }
    // SHAPE -\ .....
    else if (ollCode == 0b001110010001010011001L)
    {
        setalgo(side, "R U RP BP R B UP BP RP B");
    }
    else if (ollCode == 0b100110010100110110000L)
    {
        setalgo(side, "LP BP L UP RP U R LP B L");
    }
    else if (ollCode == 0b000110011100010110100L)
    {
        setalgo(side, "M LP UP L UP LP U2 L UP MP");
    }
    else if (ollCode == 0b101110010000110010001L)
    {
        setalgo(side, "BP R BP R2 U R U RP UP R B2");
    }
    // SHAPE \- ....
    else if (ollCode == 0b000011010001000110111L)
    {
        setalgo(side, "LP B L2 FP L2 BP L2 F LP");
    }
    else if (ollCode == 0b000011110001001011010L)
    {
        setalgo(side, "M R U RP U R U2 RP U MP");
    }
    else if (ollCode == 0b000011011000001011011L)
    {
        setalgo(side, "LP B2 R B RP B L");
    }
    else if (ollCode == 0b101011010000100010011L)
    {
        setalgo(side, "R2 U RP BP R UP R2 U R B RP");
    }
    // SHAPE C ....
    else if (ollCode == 0b110010110000111000010L)
    {
        setalgo(side, "R U R BP RP B UP RP");
    }
    else if (ollCode == 0b000111101010001010100L)
    {
        setalgo(side, "R U RP UP BP RP F R FP B");
    }
    // SHAPE L ....
    else if (ollCode == 0b000111001110000110100L)
    {
        setalgo(side, "RP F R U RP FP R F UP FP");
    }
    else if (ollCode == 0b000111100011001011000L)
    {
        setalgo(side, "L FP LP UP L F LP FP U F");
    }
    else if (ollCode == 0b000111001010001011001L)
    {
        setalgo(side, "LP BP L RP UP R U LP B L");
    }
    else if (ollCode == 0b000111100010100110100L)
    {
        setalgo(side, "R B RP L U LP UP R BP RP");
    }
    // SHAPE P .....
    else if (ollCode == 0b110110100010111000000L)
    {
        setalgo(side, "F U R UP RP FP");
    }
    else if (ollCode == 0b011011001110000001010L)
    {
        setalgo(side, "RP UP F U R UP RP FP R");
    }
    else if (ollCode == 0b110110100011010100000L)
    {
        setalgo(side, "L U FP UP LP U L F LP");
    }
    else if (ollCode == 0b011011001010000000111L)
    {
        setalgo(side, "FP UP LP U L F");
    }
    // SHAPE T .....
    else if (ollCode == 0b001111001010000010101L)
    {
        setalgo(side, "F R U RP UP FP");
    }
    else if (ollCode == 0b001111001110000011000L)
    {
        setalgo(side, "R U RP UP RP F R FP");
    }
    // SHAPE W ....
    else if (ollCode == 0b001011110001000010110L)
    {
        setalgo(side, "L U LP U L UP LP UP LP B L BP");
    }
    else if (ollCode == 0b100110011100011010000L)
    {
        setalgo(side, "RP UP R UP RP U R U R BP RP B");
    }
    // SHAPE Z ....
    else if (ollCode == 0b100111001010000110001L)
    {
        setalgo(side, "RP F R U RP UP FP U R");
    }
    else if (ollCode == 0b001111100010100011000L)
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
