#include "cube.h"
#include "miscellaneous.h"
#include "colors.h"

int cube::trials = 0;

ostream &operator<<(ostream &os, const cube &cube)
{
    cube.cube_state();
    return os;
}
istream &operator>>(istream &is, cube &cube)
{
    bool isColorsCorrect{false};
    int side{}, attempt{1};
    char inputClr{};
    while (1)
    {
        cube.check_colors();
        cube.cube_state();
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
            std::cout << "ENTER THE COLORS OF \"" BOLD + side_name(side) + DEFAULT "\" SIDE OF THE CUBE: \n";
            if (sixTimesLoop < 4)
            {
                for (int row{0}, r{1}; row < 3; row++, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int col{0}, r{0}; col < 3; col++, r++)
                    {
                        cin >> inputClr;
                        cube.cubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                cube.check_colors();
                cube.cube_state();
            }
            else if (sixTimesLoop == 4)
            {
                for (int col{2}, r{1}; col >= 0; col--, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int row{0}; row < 3; row++)
                    {
                        cin >> inputClr;
                        cube.cubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                cube.check_colors();
                cube.cube_state();
            }
            else if (sixTimesLoop == 5)
            {
                for (int col{0}, r{1}; col < 3; col++, r++)
                {
                    cout << "Row_" << r << "-> ";
                    for (int row{2}; row >= 0; row--)
                    {
                        cin >> inputClr;
                        cube.cubeMain[side][row][col] = inputClr;
                    }
                }
                clearLines(15);
                isColorsCorrect = cube.check_colors();
                cube.cube_state();
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
            cube.default_cube();
            attempt++;
        }
        else
            break; // breaking the infinite loop
    }
    return is;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   CONSTRUCTORS FOR cube CLASS
   ----------------------------------------------------------------------------------------------------------------------------------------*/
cube::cube()
{
    for (short l{0}; l < 6; l++)
    {
        cubeMain.push_back(vector<vector<char>>());
        for (short m{0}; m < 3; m++)
        {
            cubeMain[l].push_back(vector<char>());
            for (short n{0}; n < 3; n++)
            {
                cubeMain[l][m].push_back('x');
            }
        }
    }
}
cube::cube(const cube &src)
    : cube{}
{
    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                cubeMain[l][m][n] = src.cubeMain[l][m][n];
            }
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   SHOWS CUBE'S CURRENT STATUS...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void cube::cube_state() const
{
    cout << "\n   FACE        RIGHT       BACK        LEFT        TOP        BOTTOM" << endl;
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // first row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][0][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][0][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][0][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][0][2]));
    cout << "|\n";
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // second row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][1][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][1][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][1][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][1][2]));
    cout << "|\n";
    cout << " __ __ __    __ __ __    __ __ __    __ __ __    __ __ __    __ __ __ \n";
    // third row of all sides...
    cout << "|";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[face][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[right][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[back][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[left][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[top][2][2]));
    cout << "|  |";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][2][0]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][2][1]));
    cout << " ";
    set_bg_clr(" ", ch_to_clr(cubeMain[bottom][2][2]));
    cout << "|\n"
         << endl;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   checks color correctness...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool cube::check_colors()
{
    vector<int> intColorsCount(6, 0);
    vector<char> charColors{'b', 'w', 'o', 'g', 'r', 'y'};
    vector<string> colorAsciis{BLUE, WHITE, BLACK, GREEN, RED, YELLOW};
    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                switch (cubeMain[l][m][n])
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
   making cube to default state
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void cube::default_cube()
{
    for (short l{0}; l < 6; l++)
    {
        for (short m{0}; m < 3; m++)
        {
            for (short n{0}; n < 3; n++)
            {
                cubeMain[l][m][n] = 'x';
            }
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   ROTATION METHODS....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
// CLOCKWISE ROTATIONS....
void cube::face_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][2][_i]);
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "FWD");
    side_bar_receiver(left, "R");
    side_bar_sender(right, "L", "REV");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][_i][0] = sideBarBackup[_i];
}
void cube::right_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][_j][2]);
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(face, "R");
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][_i][0] = sideBarBackup[_i];
}
void cube::back_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][0][_j]);
    side_bar_sender(right, "R", "FWD");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(right, "R");
    side_bar_sender(left, "L", "FWD");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][_i][0] = sideBarBackup[_i];
}
void cube::left_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][_i][0]);
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "REV");
    side_bar_receiver(back, "R");
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[face][_i][0] = sideBarBackup[_i];
}
void cube::top_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][0][_i]);
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(right, "T");
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][0][_i] = sideBarBackup[_i];
}
void cube::bottom_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][2][_i]);
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(left, "BTM");
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][2][_i] = sideBarBackup[_i];
}
void cube::mid_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][_i][1]);
    side_bar_sender(top, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(top, "M");
    side_bar_sender(bottom, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom][_i][1] = sideBarBackup[_i];
}
void cube::equator_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][1][_i]);
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(left, "EQT");
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][1][_i] = sideBarBackup[_i];
}
void cube::stand_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][1][_i]);
    side_bar_sender(left, "M", "REV");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "FWD");
    side_bar_receiver(left, "M");
    side_bar_sender(right, "M", "REV");
    side_bar_receiver(bottom, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][_i][1] = sideBarBackup[_i];
}
// COUNTER CLOCKWISE ROTATIONS....
void cube::face_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][2][_j]);
    side_bar_sender(right, "L", "FWD");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(right, "L");
    side_bar_sender(left, "R", "FWD");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][_i][2] = sideBarBackup[_i];
}
void cube::right_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][_i][2]);
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "REV");
    side_bar_receiver(back, "L");
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[face][_i][2] = sideBarBackup[_i];
}
void cube::back_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][0][_i]);
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "FWD");
    side_bar_receiver(left, "L");
    side_bar_sender(right, "R", "REV");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][_i][2] = sideBarBackup[_i];
}
void cube::left_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][_j][0]);
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(face, "L");
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][_i][2] = sideBarBackup[_i];
}
void cube::top_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][0][_i]);
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(left, "T");
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right][0][_i] = sideBarBackup[_i];
}
void cube::bottom_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][2][_i]);
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][2][_i] = sideBarBackup[_i];
}
void cube::mid_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][_i][1]);
    side_bar_sender(bottom, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(bottom, "M");
    side_bar_sender(top, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        cubeMain[top][_i][1] = sideBarBackup[_i];
}
void cube::equator_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][1][_i]);
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(right, "EQT");
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][1][_i] = sideBarBackup[_i];
}
void cube::stand_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][1][_i]);
    side_bar_sender(right, "M", "FWD");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "REV");
    side_bar_receiver(right, "M");
    side_bar_sender(left, "M", "FWD");
    side_bar_receiver(bottom, "EQT");
    for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
        cubeMain[left][_i][1] = sideBarBackup[_j];
}
// TWICE MOVES.......
void cube::face_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(face, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][2][_j]);
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(top, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom][0][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[right][_j][0]);
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(right, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][_i][2] = sideBarBackup[_i];
}
void cube::right_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(right, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][_i][2]);
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(top, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom][_i][2] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[face][_j][2]);
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(face, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][_i][0] = sideBarBackup[_i];
}
void cube::back_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(back, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top][0][_j]);
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(top, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom][2][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[right][_j][2]);
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(right, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][_i][0] = sideBarBackup[_i];
}
void cube::left_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(left, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top][_i][0]);
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(top, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom][_i][0] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[face][_j][0]);
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(face, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][_i][2] = sideBarBackup[_i];
}
void cube::top_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(top, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][0][_i]);
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(face, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][0][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[right][0][_i]);
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(right, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][0][_i] = sideBarBackup[_i];
}
void cube::bottom_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(bottom, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face][2][_i]);
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back][2][_i] = sideBarBackup[_i];

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[right][2][_i]);
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left][2][_i] = sideBarBackup[_i];
}
// WHOLE CUBE REORIENTATION......
void cube::x_axis_rotation_clockwise()
{
    R;
    MP;
    LP;
}
void cube::y_axis_rotation_clockwise()
{
    U;
    EP;
    DP;
}
void cube::z_axis_rotation_clockwise()
{
    F;
    S;
    BP;
}
void cube::x_axis_rotation_counter_clockwise()
{
    RP;
    M;
    L;
}
void cube::y_axis_rotation_counter_clockwise()
{
    UP;
    E;
    D;
}
void cube::z_axis_rotation_counter_clockwise()
{
    FP;
    SP;
    B;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void cube::face_transpose(const int &side, string_view direction)
{
    if (direction == "CCW")
    {
        _j = 0;
        for (_row = 0; _row < 3; _row++)
        {
            _i = 2;
            for (_col = 0; _col < 3; _col++)
            {
                tempVec[_i][_j] = cubeMain[side][_row][_col];
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
                tempVec[_i][_j] = cubeMain[side][_row][_col];
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
                tempVec[_j][_i] = cubeMain[side][_row][_col];
                _i--;
            }
            _j--;
        }
    }
    cubeMain[side] = tempVec;
}
void cube::side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection)
{
    if (vectorStoringDirection == "FWD")
    {
        if (sideBarDirection == "L")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][_i][0]);
        }
        else if (sideBarDirection == "R")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][_i][2]);
        }
        else if (sideBarDirection == "T")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][0][_i]);
        }
        else if (sideBarDirection == "BTM")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][2][_i]);
        }
        else if (sideBarDirection == "M")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][_i][1]);
        }
        else if (sideBarDirection == "EQT")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side][1][_i]);
        }
    }
    else
    {
        if (sideBarDirection == "L")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][_j][0]);
        }
        else if (sideBarDirection == "R")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][_j][2]);
        }
        else if (sideBarDirection == "T")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][0][_j]);
        }
        else if (sideBarDirection == "BTM")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][2][_j]);
        }
        else if (sideBarDirection == "M")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][_j][1]);
        }
        else if (sideBarDirection == "EQT")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side][1][_j]);
        }
    }
}
void cube::side_bar_receiver(const int &side, string_view sideBarDirection)
{
    if (sideBarDirection == "BTM")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][2][_i] = sideBar[_i];
    }
    else if (sideBarDirection == "L")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][_i][0] = sideBar[_i];
    }
    else if (sideBarDirection == "T")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][0][_i] = sideBar[_i];
    }
    else if (sideBarDirection == "R")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][_i][2] = sideBar[_i];
    }
    else if (sideBarDirection == "M")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][_i][1] = sideBar[_i];
    }
    else if (sideBarDirection == "EQT")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side][1][_i] = sideBar[_i];
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
