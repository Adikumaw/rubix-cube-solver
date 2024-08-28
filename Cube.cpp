#include "Cube.h"
#include "miscellaneous.h"
#include "colors.h"

vector<vector<char>> Cube::tempVec = {
    {'0', '0', '0'},
    {'0', '0', '0'},
    {'0', '0', '0'}};
int Cube::trials = 0;

Cube &Cube::operator=(const Cube &cube)
{
    if (this != &cube)
        this->CubeMain = cube.CubeMain;
    return *this;
};
ostream &operator<<(ostream &os, const Cube &Cube)
{
    Cube.Cube_state();
    return os;
}
istream &operator>>(istream &is, Cube &Cube)
{
    bool isColorsCorrect{false};
    int side{}, attempt{1};
    char inputClr{};
    while (1)
    {
        Cube.check_colors();
        Cube.Cube_state();
        for (int sixTimesLoop{0}; sixTimesLoop < 6; sixTimesLoop++)
        {
            switch (sixTimesLoop)
            {
            case 0:
                side = 0;
                break;
            case 1:
                side = 3;
                break;
            case 2:
                side = 1;
                break;
            case 3:
                side = 2;
                break;
            case 4:
                side = 4;
                break;
            case 5:
                side = 5;
                break;
            default:
                break;
            }
            std::cout << "ENTER THE COLORS OF \"" BOLD + side_name(side) + DEFAULT "\" SIDE OF THE Cube: \n";
            if (sixTimesLoop < 4)
            {
                for (int row{0}, r{1}; row < 3; row++, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int col{0}, r{0}; col < 3; col++, r++)
                    {
                        cin >> inputClr;
                        Cube.CubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                Cube.check_colors();
                Cube.Cube_state();
            }
            else if (sixTimesLoop == 4)
            {
                for (int col{2}, r{1}; col >= 0; col--, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int row{0}; row < 3; row++)
                    {
                        cin >> inputClr;
                        Cube.CubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                Cube.check_colors();
                Cube.Cube_state();
            }
            else if (sixTimesLoop == 5)
            {
                for (int col{0}, r{1}; col < 3; col++, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int row{2}; row >= 0; row--)
                    {
                        cin >> inputClr;
                        Cube.CubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                isColorsCorrect = Cube.check_colors();
                Cube.Cube_state();
            }
        }
        if (isColorsCorrect == false)
        {
            if (attempt == 1)
            {
                clearLines(11);
                cerr << RED << "Attempt(" << attempt << "): Wrong input! please try again..." << DEFAULT << endl;
            }
            else
            {
                clearLines(12);
                cerr << RED << "Attempt(" << attempt << "): Wrong input! please try again..." << DEFAULT << endl;
            }
            Cube.default_Cube();
            attempt++;
        }
        else
            break; // breaking the infinite loop
    }
    return is;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   CONSTRUCTORS FOR Cube CLASS
   ----------------------------------------------------------------------------------------------------------------------------------------*/
Cube::Cube()
{
    for (short l{0}; l < 6; l++)
    {
        CubeMain.push_back(vector<vector<char>>());
        for (short m{0}; m < 3; m++)
        {
            CubeMain[l].push_back(vector<char>());
            for (short n{0}; n < 3; n++)
            {
                CubeMain[l][m].push_back('x');
            }
        }
    }
}
Cube::Cube(const Cube &src)
    : Cube{}
{
    // for (short l{0}; l < 6; l++)
    // {
    //     for (short m{0}; m < 3; m++)
    //     {
    //         for (short n{0}; n < 3; n++)
    //         {
    //             CubeMain[l][m][n] = src.CubeMain[l][m][n];
    //         }
    //     }
    // }
    this->CubeMain = src.CubeMain;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   SHOWS Cube'S CURRENT STATUS...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cube::Cube_state() const
{
    cout << "\n   FACE        RIGHT       BACK        LEFT        TOP        BOTTOM" << endl;
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // first row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][0][2]));
    cout << "|\n";
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // second row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][1][2]));
    cout << "|\n";
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // third row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[face][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[right][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[back][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[left][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[top][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(CubeMain[bottom][2][2]));
    cout << "|\n"
         << endl;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHANGES THE Cube_SOLVING_ALGORITHEMS TO THE REQUIRED IMPLEMENTAION SIDE ON THE BASIS OF SIDE PROVIDED.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cube::setalgo(const int &side, string str_algo, bool apply)
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
    applySolution(apply);
}
void Cube::setalgo(const int &side, vector<string> algo, bool apply)
{
    if (side == right)
    {
        for (size_t i{0}; i < algo.size(); i++)
        {
            if (algo[i][0] == 'F')
                algo[i][0] = 'R';
            else if (algo[i][0] == 'L')
                algo[i][0] = 'F';
            else if (algo[i][0] == 'R')
                algo[i][0] = 'B';
            else if (algo[i][0] == 'B')
                algo[i][0] = 'L';
            else if (algo[i][0] == 'M')
                algo[i][0] = 'S';
            else if (algo[i] == "S")
                algo[i] = "MP";
            else if (algo[i] == "SP")
                algo[i] = "M";
            else if (algo[i] == "S2")
                algo[i] = "M2";
            // but E will remain E...
        }
    }
    else if (side == back)
    {
        for (size_t i{0}; i < algo.size(); i++)
        {
            if (algo[i][0] == 'F')
                algo[i][0] = 'B';
            else if (algo[i][0] == 'L')
                algo[i][0] = 'R';
            else if (algo[i][0] == 'R')
                algo[i][0] = 'L';
            else if (algo[i][0] == 'B')
                algo[i][0] = 'F';
            else if (algo[i] == "M")
                algo[i] = "MP";
            else if (algo[i] == "MP")
                algo[i] = "M";
            // M2 will remain same..
            else if (algo[i] == "S")
                algo[i] = "SP";
            else if (algo[i] == "SP")
                algo[i] = "S";
        }
    }
    else if (side == left)
    {
        for (size_t i{0}; i < algo.size(); i++)
        {
            if (algo[i][0] == 'F')
                algo[i][0] = 'L';
            else if (algo[i][0] == 'L')
                algo[i][0] = 'B';
            else if (algo[i][0] == 'R')
                algo[i][0] = 'F';
            else if (algo[i][0] == 'B')
                algo[i][0] = 'R';
            else if (algo[i] == "M")
                algo[i] = "SP";
            else if (algo[i] == "M2")
                algo[i] = "S2";
            else if (algo[i] == "MP")
                algo[i] = "S";
            else if (algo[i][0] == 'S')
                algo[i][0] = 'M';
        }
    };
    tempSolution = algo; // copying algo to tempalgo..
    applySolution(apply);
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE Cube
   clear of the tempsolution is not its work you should clear it before using agian
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cube::applyTempSolution()
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
    // if (applySolutionOn == "crs")
    //     for (size_t i{0}; i < tempSolution.size(); i++)
    //         crossSolution.push_back(tempSolution.at(i));
    // else if (applySolutionOn == "f2l")
    //     for (size_t i{0}; i < tempSolution.size(); i++)
    //         f2lSolution.push_back(tempSolution.at(i));
    // else if (applySolutionOn == "oll")
    //     for (size_t i{0}; i < tempSolution.size(); i++)
    //         ollSolution.push_back(tempSolution.at(i));
    // else if (applySolutionOn == "pll")
    //     for (size_t i{0}; i < tempSolution.size(); i++)
    //         pllSolution.push_back(tempSolution.at(i));
    // tempSolution.clear();
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   checks color correctness...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool Cube::check_colors()
{
    vector<int> intColorsCount(6, 0);
    vector<char> charColors{'b', 'w', 'o', 'g', 'r', 'y'};
    vector<string> colorAsciis{BLUE, WHITE, B_MAGENTA, GREEN, RED, B_YELLOW};
    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                switch (CubeMain[l][m][n])
                {
                case 'b':
                    intColorsCount[0]++;
                    break;
                case 'w':
                    intColorsCount[1]++;
                    break;
                case 'o':
                    intColorsCount[2]++;
                    break;
                case 'g':
                    intColorsCount[3]++;
                    break;
                case 'r':
                    intColorsCount[4]++;
                    break;
                case 'y':
                    intColorsCount[5]++;
                    break;
                };
            }
        }
    }
    // printing the Colors count ...
    for (int i{0}; i < intColorsCount.size(); i++)
    {
        cout << "[" << colorAsciis[i] << charColors[i] << ":" << intColorsCount[i] << DEFAULT << "]"
             << "  ";
    }
    cout << endl;
    // checking if the intColorsCount are 9 and assigning 'x' if not...
    if (intColorsCount[0] != 9 || intColorsCount[1] != 9 || intColorsCount[2] != 9 || intColorsCount[3] != 9 || intColorsCount[4] != 9 || intColorsCount[5] != 9)
    {
        return false;
    }
    return true;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   making Cube to default state
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cube::default_Cube()
{
    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                CubeMain[l][m][n] = 'x';
            }
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   ROTATION METHODS....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
// CLOCKWISE ROTATIONS....
void Cube::face_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][2][_i]);
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "FWD");
    side_bar_receiver(left, "R");
    side_bar_sender(right, "L", "REV");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][_i][0] = sideBarBackup[_i];
}
void Cube::right_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][_j][2]);
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(face, "R");
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][_i][0] = sideBarBackup[_i];
}
void Cube::back_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][0][_j]);
    side_bar_sender(right, "R", "FWD");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(right, "R");
    side_bar_sender(left, "L", "FWD");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][_i][0] = sideBarBackup[_i];
}
void Cube::left_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][_i][0]);
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "REV");
    side_bar_receiver(back, "R");
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        CubeMain[face][_i][0] = sideBarBackup[_i];
}
void Cube::top_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][0][_i]);
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(right, "T");
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][0][_i] = sideBarBackup[_i];
}
void Cube::bottom_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][2][_i]);
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(left, "BTM");
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][2][_i] = sideBarBackup[_i];
}
void Cube::mid_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][_i][1]);
    side_bar_sender(top, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(top, "M");
    side_bar_sender(bottom, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        CubeMain[bottom][_i][1] = sideBarBackup[_i];
}
void Cube::equator_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][1][_i]);
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(left, "EQT");
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][1][_i] = sideBarBackup[_i];
}
void Cube::stand_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][1][_i]);
    side_bar_sender(left, "M", "REV");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "FWD");
    side_bar_receiver(left, "M");
    side_bar_sender(right, "M", "REV");
    side_bar_receiver(bottom, "EQT");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][_i][1] = sideBarBackup[_i];
}
// COUNTER CLOCKWISE ROTATIONS....
void Cube::face_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][2][_j]);
    side_bar_sender(right, "L", "FWD");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(right, "L");
    side_bar_sender(left, "R", "FWD");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][_i][2] = sideBarBackup[_i];
}
void Cube::right_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][_i][2]);
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "REV");
    side_bar_receiver(back, "L");
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        CubeMain[face][_i][2] = sideBarBackup[_i];
}
void Cube::back_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][0][_i]);
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "FWD");
    side_bar_receiver(left, "L");
    side_bar_sender(right, "R", "REV");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][_i][2] = sideBarBackup[_i];
}
void Cube::left_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][_j][0]);
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(face, "L");
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][_i][2] = sideBarBackup[_i];
}
void Cube::top_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][0][_i]);
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(left, "T");
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[right][0][_i] = sideBarBackup[_i];
}
void Cube::bottom_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][2][_i]);
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][2][_i] = sideBarBackup[_i];
}
void Cube::mid_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][_i][1]);
    side_bar_sender(bottom, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(bottom, "M");
    side_bar_sender(top, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        CubeMain[top][_i][1] = sideBarBackup[_i];
}
void Cube::equator_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][1][_i]);
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(right, "EQT");
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][1][_i] = sideBarBackup[_i];
}
void Cube::stand_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][1][_i]);
    side_bar_sender(right, "M", "FWD");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "REV");
    side_bar_receiver(right, "M");
    side_bar_sender(left, "M", "FWD");
    side_bar_receiver(bottom, "EQT");
    for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
        CubeMain[left][_i][1] = sideBarBackup[_j];
}
// TWICE MOVES.......
void Cube::face_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(face, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][2][_j]);
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(top, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[bottom][0][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[right][_j][0]);
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(right, "L");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][_i][2] = sideBarBackup[_i];
}
void Cube::right_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(right, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][_i][2]);
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(top, "R");
    for (_i = 0; _i < 3; _i++)
        CubeMain[bottom][_i][2] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[face][_j][2]);
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(face, "R");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][_i][0] = sideBarBackup[_i];
}
void Cube::back_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(back, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[top][0][_j]);
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(top, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[bottom][2][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[right][_j][2]);
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(right, "R");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][_i][0] = sideBarBackup[_i];
}
void Cube::left_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(left, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[top][_i][0]);
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(top, "L");
    for (_i = 0; _i < 3; _i++)
        CubeMain[bottom][_i][0] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(CubeMain[face][_j][0]);
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(face, "L");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][_i][2] = sideBarBackup[_i];
}
void Cube::top_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(top, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][0][_i]);
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(face, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][0][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[right][0][_i]);
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(right, "T");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][0][_i] = sideBarBackup[_i];
}
void Cube::bottom_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(bottom, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[face][2][_i]);
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[back][2][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(CubeMain[right][2][_i]);
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    for (_i = 0; _i < 3; _i++)
        CubeMain[left][2][_i] = sideBarBackup[_i];
}
// WHOLE Cube REORIENTATION......
void Cube::x_axis_rotation_clockwise()
{
    R;
    MP;
    LP;
}
void Cube::y_axis_rotation_clockwise()
{
    U;
    EP;
    DP;
}
void Cube::z_axis_rotation_clockwise()
{
    F;
    S;
    BP;
}
void Cube::x_axis_rotation_counter_clockwise()
{
    RP;
    M;
    L;
}
void Cube::y_axis_rotation_counter_clockwise()
{
    UP;
    E;
    D;
}
void Cube::z_axis_rotation_counter_clockwise()
{
    FP;
    SP;
    B;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE Cube...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void Cube::face_transpose(const int &side, string_view direction)
{
    if (direction == "CCW")
    {
        _j = 0;
        for (_row = 0; _row < 3; _row++)
        {
            _i = 2;
            for (_col = 0; _col < 3; _col++)
            {
                tempVec[_i][_j] = CubeMain[side][_row][_col];
                _i--;
            }
            _j++;
        }
    }
    else if (direction == "CW")
    {
        _j = 2;
        for (_row = 0; _row < 3; _row++)
        {
            _i = 0;
            for (_col = 0; _col < 3; _col++)
            {
                tempVec[_i][_j] = CubeMain[side][_row][_col];
                _i++;
            }
            _j--;
        }
    }
    else if (direction == "2CW")
    {
        _j = 2;
        for (_row = 0; _row < 3; _row++)
        {
            _i = 2;
            for (_col = 0; _col < 3; _col++)
            {
                tempVec[_j][_i] = CubeMain[side][_row][_col];
                _i--;
            }
            _j--;
        }
    }
    CubeMain[side] = tempVec;
}
void Cube::side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection)
{
    if (vectorStoringDirection == "FWD")
    {
        if (sideBarDirection == "L")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][_i][0]);
        }
        else if (sideBarDirection == "R")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][_i][2]);
        }
        else if (sideBarDirection == "T")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][0][_i]);
        }
        else if (sideBarDirection == "BTM")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][2][_i]);
        }
        else if (sideBarDirection == "M")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][_i][1]);
        }
        else if (sideBarDirection == "EQT")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(CubeMain[side][1][_i]);
        }
    }
    else
    {
        if (sideBarDirection == "L")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][_j][0]);
        }
        else if (sideBarDirection == "R")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][_j][2]);
        }
        else if (sideBarDirection == "T")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][0][_j]);
        }
        else if (sideBarDirection == "BTM")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][2][_j]);
        }
        else if (sideBarDirection == "M")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][_j][1]);
        }
        else if (sideBarDirection == "EQT")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(CubeMain[side][1][_j]);
        }
    }
}
void Cube::side_bar_receiver(const int &side, string_view sideBarDirection)
{
    if (sideBarDirection == "BTM")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][2][_i] = sideBar[_i];
    }
    else if (sideBarDirection == "L")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][_i][0] = sideBar[_i];
    }
    else if (sideBarDirection == "T")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][0][_i] = sideBar[_i];
    }
    else if (sideBarDirection == "R")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][_i][2] = sideBar[_i];
    }
    else if (sideBarDirection == "M")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][_i][1] = sideBar[_i];
    }
    else if (sideBarDirection == "EQT")
    {
        for (_i = 0; _i < 3; _i++)
            CubeMain[side][1][_i] = sideBar[_i];
    }
    sideBar.clear();
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THSI FUNCITON PROVIDES COLOR NAME STRING IN EXCHANGE OF INTEGER VALUE OF THE COLOR
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string side_name(const int &colorAscii)
{
    switch (colorAscii)
    {
    case 0:
        return "FACE";
        break;
    case 1:
        return "BACK";
        break;
    case 2:
        return "LEFT";
        break;
    case 3:
        return "RIGHT";
        break;
    case 4:
        return "TOP";
        break;
    case 5:
        return "BOTTOM";
        break;
    default:
        return "ERROR FINDING COLOR NAME";
        break;
    }
}
