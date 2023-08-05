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
    int color{}, side{};
    string buff{};
    char ch{};
    cube.cube_state();
    for (int six_times{0}; six_times < 6; six_times++)
    {
        switch (six_times)
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
        buff = "ENTER THE COLORS OF \"" BOLD + side_name(side) + DEFAULT "\" SIDE OF THE CUBE: \n";
        std::cout << buff;
        if (six_times < 4)
        {
            for (int row{0}, r{1}; row < 3; row++, r++)
            {
                cout << "Row_" << r << "-> ";
                // buff += "Row" + row + ' ';
                for (int col{0}, r{0}; col < 3; col++, r++)
                {
                    cin >> ch;
                    cube.cubeMain.at(side).at(row).at(col) = ch;
                    // temp_side.at(row).at(col) = ch;
                }
                buff += '\n';
            }
            clearLines(14);
            cube.cube_state();
        }
        else if (six_times == 4)
        {
            for (int col{2}, r{1}; col >= 0; col--, r++)
            {
                cout << "Row_" << r << "-> ";
                for (int row{0}; row < 3; row++)
                {
                    cin >> ch;
                    buff += ch + ' ';
                    cube.cubeMain.at(side).at(row).at(col) = ch;
                }
                buff += '\n';
            }
            clearLines(14);
            cube.cube_state();
        }
        else if (six_times == 5)
        {
            for (int col{0}, r{1}; col < 3; col++, r++)
            {
                cout << "Row_" << r << "-> ";
                for (int row{2}; row >= 0; row--)
                {
                    cin >> ch;
                    buff += ch + ' ';
                    cube.cubeMain.at(side).at(row).at(col) = ch;
                }
                buff += '\n';
            }
            clearLines(14);
            cube.cube_state();
        }
    }
    cout << endl;
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
            cubeMain.at(l).push_back(vector<char>());
            for (short n{0}; n < 3; n++)
            {
                cubeMain.at(l).at(m).push_back('x');
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
                cubeMain.at(l).at(m).at(n) = src.cubeMain.at(l).at(m).at(n);
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
   ROTATION METHODS....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
// CLOCKWISE ROTATIONS....
void cube::face_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(2).at(_i));
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "FWD");
    side_bar_receiver(left, "R");
    side_bar_sender(right, "L", "REV");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::right_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(_j).at(2));
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(face, "R");
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::back_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(0).at(_j));
    side_bar_sender(right, "R", "FWD");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(right, "R");
    side_bar_sender(left, "L", "FWD");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::left_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(_i).at(0));
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "REV");
    side_bar_receiver(back, "R");
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[face].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::top_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(0).at(_i));
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(right, "T");
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(0).at(_i) = sideBarBackup.at(_i);
}
void cube::bottom_rotate_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(2).at(_i));
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(left, "BTM");
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(2).at(_i) = sideBarBackup.at(_i);
}
void cube::mid_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(_i).at(1));
    side_bar_sender(top, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(top, "M");
    side_bar_sender(bottom, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom].at(_i).at(1) = sideBarBackup.at(_i);
}
void cube::equator_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(1).at(_i));
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(left, "EQT");
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(1).at(_i) = sideBarBackup.at(_i);
}
void cube::stand_rotate_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(1).at(_i));
    side_bar_sender(left, "M", "REV");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "FWD");
    side_bar_receiver(left, "M");
    side_bar_sender(right, "M", "REV");
    side_bar_receiver(bottom, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(_i).at(1) = sideBarBackup.at(_i);
}
// COUNTER CLOCKWISE ROTATIONS....
void cube::face_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(face, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(2).at(_j));
    side_bar_sender(right, "L", "FWD");
    side_bar_receiver(top, "BTM");
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(right, "L");
    side_bar_sender(left, "R", "FWD");
    side_bar_receiver(bottom, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::right_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(right, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(_i).at(2));
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(top, "R");
    side_bar_sender(bottom, "R", "REV");
    side_bar_receiver(back, "L");
    side_bar_sender(face, "R", "FWD");
    side_bar_receiver(bottom, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[face].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::back_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(back, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(0).at(_i));
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(top, "T");
    side_bar_sender(bottom, "BTM", "FWD");
    side_bar_receiver(left, "L");
    side_bar_sender(right, "R", "REV");
    side_bar_receiver(bottom, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::left_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(left, "CCW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(_j).at(0));
    side_bar_sender(face, "L", "FWD");
    side_bar_receiver(top, "L");
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(face, "L");
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(bottom, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::top_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(top, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(0).at(_i));
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(face, "T");
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(left, "T");
    side_bar_sender(right, "T", "FWD");
    side_bar_receiver(back, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[right].at(0).at(_i) = sideBarBackup.at(_i);
}
void cube::bottom_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    face_transpose(bottom, "CCW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(2).at(_i));
    side_bar_sender(right, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(back, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(2).at(_i) = sideBarBackup.at(_i);
}
void cube::mid_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(_i).at(1));
    side_bar_sender(bottom, "M", "FWD");
    side_bar_receiver(face, "M");
    side_bar_sender(back, "M", "REV");
    side_bar_receiver(bottom, "M");
    side_bar_sender(top, "M", "REV");
    side_bar_receiver(back, "M");
    for (_i = 0; _i < 3; _i++)
        cubeMain[top].at(_i).at(1) = sideBarBackup.at(_i);
}
void cube::equator_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(1).at(_i));
    side_bar_sender(right, "EQT", "FWD");
    side_bar_receiver(face, "EQT");
    side_bar_sender(back, "EQT", "FWD");
    side_bar_receiver(right, "EQT");
    side_bar_sender(left, "EQT", "FWD");
    side_bar_receiver(back, "EQT");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(1).at(_i) = sideBarBackup.at(_i);
}
void cube::stand_rotate_counter_clockwise()
{
    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(1).at(_i));
    side_bar_sender(right, "M", "FWD");
    side_bar_receiver(top, "EQT");
    side_bar_sender(bottom, "EQT", "REV");
    side_bar_receiver(right, "M");
    side_bar_sender(left, "M", "FWD");
    side_bar_receiver(bottom, "EQT");
    for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
        cubeMain[left].at(_i).at(1) = sideBarBackup.at(_j);
}
// TWICE MOVES.......
void cube::face_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(face, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(2).at(_j));
    side_bar_sender(bottom, "T", "REV");
    side_bar_receiver(top, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom].at(0).at(_i) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[right].at(_j).at(0));
    side_bar_sender(left, "R", "REV");
    side_bar_receiver(right, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::right_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(right, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(_i).at(2));
    side_bar_sender(bottom, "R", "FWD");
    side_bar_receiver(top, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom].at(_i).at(2) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[face].at(_j).at(2));
    side_bar_sender(back, "L", "REV");
    side_bar_receiver(face, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::back_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(back, "2CW");
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[top].at(0).at(_j));
    side_bar_sender(bottom, "BTM", "REV");
    side_bar_receiver(top, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom].at(2).at(_i) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[right].at(_j).at(2));
    side_bar_sender(left, "L", "REV");
    side_bar_receiver(right, "R");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(_i).at(0) = sideBarBackup.at(_i);
}
void cube::left_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(left, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[top].at(_i).at(0));
    side_bar_sender(bottom, "L", "FWD");
    side_bar_receiver(top, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[bottom].at(_i).at(0) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_j = 2; _j >= 0; _j--)
        sideBarBackup.push_back(cubeMain[face].at(_j).at(0));
    side_bar_sender(back, "R", "REV");
    side_bar_receiver(face, "L");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(_i).at(2) = sideBarBackup.at(_i);
}
void cube::top_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(top, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(0).at(_i));
    side_bar_sender(back, "T", "FWD");
    side_bar_receiver(face, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(0).at(_i) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[right].at(0).at(_i));
    side_bar_sender(left, "T", "FWD");
    side_bar_receiver(right, "T");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(0).at(_i) = sideBarBackup.at(_i);
}
void cube::bottom_rotate_two_times()
{
    sideBarBackup.clear();
    face_transpose(bottom, "2CW");
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[face].at(2).at(_i));
    side_bar_sender(back, "BTM", "FWD");
    side_bar_receiver(face, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[back].at(2).at(_i) = sideBarBackup.at(_i);

    sideBarBackup.clear();
    for (_i = 0; _i < 3; _i++)
        sideBarBackup.push_back(cubeMain[right].at(2).at(_i));
    side_bar_sender(left, "BTM", "FWD");
    side_bar_receiver(right, "BTM");
    for (_i = 0; _i < 3; _i++)
        cubeMain[left].at(2).at(_i) = sideBarBackup.at(_i);
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

void cube::side_rotate(const int &side, string_view direction)
{
    if (direction == "2CW")
    {
        face_transpose(side, direction);
        if (side == face)
        {
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[top].at(2).at(_j));
            side_bar_sender(bottom, "T", "REV");
            side_bar_receiver(top, "BTM");
            for (_i = 0; _i < 3; _i++)
                cubeMain[bottom].at(0).at(_i) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[right].at(_j).at(0));
            side_bar_sender(left, "R", "REV");
            side_bar_receiver(right, "L");
            for (_i = 0; _i < 3; _i++)
                cubeMain[left].at(_i).at(2) = sideBarBackup.at(_i);
        }
        else if (side == back)
        {
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[top].at(0).at(_j));
            side_bar_sender(bottom, "BTM", "REV");
            side_bar_receiver(top, "T");
            for (_i = 0; _i < 3; _i++)
                cubeMain[bottom].at(2).at(_i) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[right].at(_j).at(2));
            side_bar_sender(left, "L", "REV");
            side_bar_receiver(right, "R");
            for (_i = 0; _i < 3; _i++)
                cubeMain[left].at(_i).at(0) = sideBarBackup.at(_i);
        }
        else if (side == left)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(_i).at(0));
            side_bar_sender(bottom, "L", "FWD");
            side_bar_receiver(top, "L");
            for (_i = 0; _i < 3; _i++)
                cubeMain[bottom].at(_i).at(0) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[face].at(_j).at(0));
            side_bar_sender(back, "R", "REV");
            side_bar_receiver(face, "L");
            for (_i = 0; _i < 3; _i++)
                cubeMain[back].at(_i).at(2) = sideBarBackup.at(_i);
        }
        else if (side == right)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(_i).at(2));
            side_bar_sender(bottom, "R", "FWD");
            side_bar_receiver(top, "R");
            for (_i = 0; _i < 3; _i++)
                cubeMain[bottom].at(_i).at(2) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_j = 2; _j >= 0; _j--)
                sideBarBackup.push_back(cubeMain[face].at(_j).at(2));
            side_bar_sender(back, "L", "REV");
            side_bar_receiver(face, "R");
            for (_i = 0; _i < 3; _i++)
                cubeMain[back].at(_i).at(0) = sideBarBackup.at(_i);
        }
        else if (side == top)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[face].at(0).at(_i));
            side_bar_sender(back, "T", "FWD");
            side_bar_receiver(face, "T");
            for (_i = 0; _i < 3; _i++)
                cubeMain[back].at(0).at(_i) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[right].at(0).at(_i));
            side_bar_sender(left, "T", "FWD");
            side_bar_receiver(right, "T");
            for (_i = 0; _i < 3; _i++)
                cubeMain[left].at(0).at(_i) = sideBarBackup.at(_i);
        }
        else if (side == bottom)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[face].at(2).at(_i));
            side_bar_sender(back, "BTM", "FWD");
            side_bar_receiver(face, "BTM");
            for (_i = 0; _i < 3; _i++)
                cubeMain[back].at(2).at(_i) = sideBarBackup.at(_i);

            sideBarBackup.clear();
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[right].at(2).at(_i));
            side_bar_sender(left, "BTM", "FWD");
            side_bar_receiver(right, "BTM");
            for (_i = 0; _i < 3; _i++)
                cubeMain[left].at(2).at(_i) = sideBarBackup.at(_i);
        }
    }
    else if (side >= face && side <= bottom)
    {
        face_transpose(side, direction);
        if (side == face)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(2).at(_i));
            if (direction == "CW")
            {
                side_bar_sender(left, "R", "REV");
                side_bar_receiver(top, "BTM");
                side_bar_sender(bottom, "T", "FWD");
                side_bar_receiver(left, "R");
                side_bar_sender(right, "L", "REV");
                side_bar_receiver(bottom, "T");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[right].at(_i).at(0) = sideBarBackup.at(_i);
            }
            else
            {
                side_bar_sender(right, "L", "FWD");
                side_bar_receiver(top, "BTM");
                side_bar_sender(bottom, "T", "REV");
                side_bar_receiver(right, "L");
                side_bar_sender(left, "R", "FWD");
                side_bar_receiver(bottom, "T");
                for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
                    cubeMain[left].at(_i).at(2) = sideBarBackup.at(_j);
                // side_bar_receiver(left, "R");
            }
        }
        else if (side == back)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(0).at(_i));
            if (direction == "CW")
            {
                side_bar_sender(right, "R", "FWD");
                side_bar_receiver(top, "T");
                side_bar_sender(bottom, "BTM", "REV");
                side_bar_receiver(right, "R");
                side_bar_sender(left, "L", "FWD");
                side_bar_receiver(bottom, "BTM");
                for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
                    cubeMain[left].at(_i).at(0) = sideBarBackup.at(_j);
                // side_bar_receiver(left, "L");
            }
            else
            {
                side_bar_sender(left, "L", "REV");
                side_bar_receiver(top, "T");
                side_bar_sender(bottom, "BTM", "FWD");
                side_bar_receiver(left, "L");
                side_bar_sender(right, "R", "REV");
                side_bar_receiver(bottom, "BTM");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[right].at(_i).at(2) = sideBarBackup.at(_i);
            }
        }
        else if (side == left)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(_i).at(0));
            if (direction == "CW")
            {
                side_bar_sender(back, "R", "REV");
                side_bar_receiver(top, "L");
                side_bar_sender(bottom, "L", "REV");
                side_bar_receiver(back, "R");
                side_bar_sender(face, "L", "FWD");
                side_bar_receiver(bottom, "L");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[face].at(_i).at(0) = sideBarBackup.at(_i);
            }
            else
            {
                side_bar_sender(face, "L", "FWD");
                side_bar_receiver(top, "L");
                side_bar_sender(bottom, "L", "FWD");
                side_bar_receiver(face, "L");
                side_bar_sender(back, "R", "REV");
                side_bar_receiver(bottom, "L");
                for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
                    cubeMain[back].at(_i).at(2) = sideBarBackup.at(_j);
                // side_bar_receiver(back, "R");
            }
        }
        else if (side == right)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[top].at(_i).at(2));
            if (direction == "CW")
            {
                side_bar_sender(face, "R", "FWD");
                side_bar_receiver(top, "R");
                side_bar_sender(bottom, "R", "FWD");
                side_bar_receiver(face, "R");
                side_bar_sender(back, "L", "REV");
                side_bar_receiver(bottom, "R");
                for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
                    cubeMain[back].at(_i).at(0) = sideBarBackup.at(_j);
                // side_bar_receiver(back, "L");
            }
            else
            {
                side_bar_sender(back, "L", "REV");
                side_bar_receiver(top, "R");
                side_bar_sender(bottom, "R", "REV");
                side_bar_receiver(back, "L");
                side_bar_sender(face, "R", "FWD");
                side_bar_receiver(bottom, "R");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[face].at(_i).at(2) = sideBarBackup.at(_i);
            }
        }
        else if (side == top)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[face].at(0).at(_i));
            if (direction == "CW")
            {
                side_bar_sender(right, "T", "FWD");
                side_bar_receiver(face, "T");
                side_bar_sender(back, "T", "FWD");
                side_bar_receiver(right, "T");
                side_bar_sender(left, "T", "FWD");
                side_bar_receiver(back, "T");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[left].at(0).at(_i) = sideBarBackup.at(_i);
            }
            else
            {
                side_bar_sender(left, "T", "FWD");
                side_bar_receiver(face, "T");
                side_bar_sender(back, "T", "FWD");
                side_bar_receiver(left, "T");
                side_bar_sender(right, "T", "FWD");
                side_bar_receiver(back, "T");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[right].at(0).at(_i) = sideBarBackup.at(_i);
            }
        }
        else if (side == bottom)
        {
            for (_i = 0; _i < 3; _i++)
                sideBarBackup.push_back(cubeMain[face].at(2).at(_i));
            if (direction == "CW")
            {
                side_bar_sender(left, "BTM", "FWD");
                side_bar_receiver(face, "BTM");
                side_bar_sender(back, "BTM", "FWD");
                side_bar_receiver(left, "BTM");
                side_bar_sender(right, "BTM", "FWD");
                side_bar_receiver(back, "BTM");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[right].at(2).at(_i) = sideBarBackup.at(_i);
            }
            else
            {
                side_bar_sender(right, "BTM", "FWD");
                side_bar_receiver(face, "BTM");
                side_bar_sender(back, "BTM", "FWD");
                side_bar_receiver(right, "BTM");
                side_bar_sender(left, "BTM", "FWD");
                side_bar_receiver(back, "BTM");
                for (_i = 0; _i < 3; _i++)
                    cubeMain[left].at(2).at(_i) = sideBarBackup.at(_i);
            }
        }
    }
    else if (side == mid)
    {
        for (_i = 0; _i < 3; _i++)
            sideBarBackup.push_back(cubeMain[face].at(_i).at(1));
        if (direction == "CW")
        {
            side_bar_sender(top, "M", "FWD");
            side_bar_receiver(face, "M");
            side_bar_sender(back, "M", "REV");
            side_bar_receiver(top, "M");
            side_bar_sender(bottom, "M", "REV");
            side_bar_receiver(back, "M");
            for (_i = 0; _i < 3; _i++)
                cubeMain[bottom].at(_i).at(1) = sideBarBackup.at(_i);
        }
        else
        {
            side_bar_sender(bottom, "M", "FWD");
            side_bar_receiver(face, "M");
            side_bar_sender(back, "M", "REV");
            side_bar_receiver(bottom, "M");
            side_bar_sender(top, "M", "REV");
            side_bar_receiver(back, "M");
            for (_i = 0; _i < 3; _i++)
                cubeMain[top].at(_i).at(1) = sideBarBackup.at(_i);
        }
    }
    else if (side == equator)
    {
        for (_i = 0; _i < 3; _i++)
            sideBarBackup.push_back(cubeMain[face].at(1).at(_i));
        if (direction == "CW")
        {
            side_bar_sender(left, "EQT", "FWD");
            side_bar_receiver(face, "EQT");
            side_bar_sender(back, "EQT", "FWD");
            side_bar_receiver(left, "EQT");
            side_bar_sender(right, "EQT", "FWD");
            side_bar_receiver(back, "EQT");
            for (_i = 0; _i < 3; _i++)
                cubeMain[right].at(1).at(_i) = sideBarBackup.at(_i);
        }
        else
        {
            side_bar_sender(right, "EQT", "FWD");
            side_bar_receiver(face, "EQT");
            side_bar_sender(back, "EQT", "FWD");
            side_bar_receiver(right, "EQT");
            side_bar_sender(left, "EQT", "FWD");
            side_bar_receiver(back, "EQT");
            for (_i = 0; _i < 3; _i++)
                cubeMain[left].at(1).at(_i) = sideBarBackup.at(_i);
        }
    }
    else if (side == stand)
    {
        for (_i = 0; _i < 3; _i++)
            sideBarBackup.push_back(cubeMain[top].at(1).at(_i));
        if (direction == "CW")
        {
            side_bar_sender(left, "M", "REV");
            side_bar_receiver(top, "EQT");
            side_bar_sender(bottom, "EQT", "FWD");
            side_bar_receiver(left, "M");
            side_bar_sender(right, "M", "REV");
            side_bar_receiver(bottom, "EQT");
            for (_i = 0; _i < 3; _i++)
                cubeMain[right].at(_i).at(1) = sideBarBackup.at(_i);
        }
        else
        {
            side_bar_sender(right, "M", "FWD");
            side_bar_receiver(top, "EQT");
            side_bar_sender(bottom, "EQT", "REV");
            side_bar_receiver(right, "M");
            side_bar_sender(left, "M", "FWD");
            side_bar_receiver(bottom, "EQT");
            for (_j = 2, _i = 0; _j >= 0, _i < 3; _j--, _i++)
                cubeMain[left].at(_i).at(1) = sideBarBackup.at(_j);
            // side_bar_receiver(left, "M");
        }
    }
    // RECURSION WILL OCCUR FOR THE BELLOW THREE CONDITIONS......
    else if (side == axisX)
    {
        if (direction == "CW")
        {
            R;
            MP;
            LP;
        }
        else
        {
            RP;
            M;
            L;
        }
    }
    else if (side == axisY)
    {
        if (direction == "CW")
        {
            U;
            EP;
            DP;
        }
        else
        {
            UP;
            E;
            D;
        }
    }
    else if (side == axisZ)
    {
        if (direction == "CW")
        {
            F;
            S;
            BP;
        }
        else
        {
            FP;
            SP;
            B;
        }
    }
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
                tempVec[_i][_j] = cubeMain[side].at(_row).at(_col);
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
                tempVec[_i][_j] = cubeMain[side].at(_row).at(_col);
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
                tempVec[_j][_i] = cubeMain[side].at(_row).at(_col);
                _i--;
            }
            _j--;
        }
    }
    (cubeMain)[side] = tempVec;
}
void cube::side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection)
{
    if (vectorStoringDirection == "FWD")
    {
        if (sideBarDirection == "L")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(_i).at(0));
        }
        else if (sideBarDirection == "R")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(_i).at(2));
        }
        else if (sideBarDirection == "T")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(0).at(_i));
        }
        else if (sideBarDirection == "BTM")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(2).at(_i));
        }
        else if (sideBarDirection == "M")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(_i).at(1));
        }
        else if (sideBarDirection == "EQT")
        {
            for (_i = 0; _i < 3; _i++)
                sideBar.push_back(cubeMain[side].at(1).at(_i));
        }
    }
    else
    {
        if (sideBarDirection == "L")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(_j).at(0));
        }
        else if (sideBarDirection == "R")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(_j).at(2));
        }
        else if (sideBarDirection == "T")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(0).at(_j));
        }
        else if (sideBarDirection == "BTM")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(2).at(_j));
        }
        else if (sideBarDirection == "M")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(_j).at(1));
        }
        else if (sideBarDirection == "EQT")
        {
            for (int _j{2}; _j >= 0; _j--)
                sideBar.push_back(cubeMain[side].at(1).at(_j));
        }
    }
}
void cube::side_bar_receiver(const int &side, string_view sideBarDirection)
{
    if (sideBarDirection == "BTM")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(2).at(_i) = sideBar.at(_i);
    }
    else if (sideBarDirection == "L")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(_i).at(0) = sideBar.at(_i);
    }
    else if (sideBarDirection == "T")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(0).at(_i) = sideBar.at(_i);
    }
    else if (sideBarDirection == "R")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(_i).at(2) = sideBar.at(_i);
    }
    else if (sideBarDirection == "M")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(_i).at(1) = sideBar.at(_i);
    }
    else if (sideBarDirection == "EQT")
    {
        for (_i = 0; _i < 3; _i++)
            cubeMain[side].at(1).at(_i) = sideBar.at(_i);
    }
    sideBar.clear();
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THSI FUNCITON PROVIDES COLOR NAME STRING IN EXCHANGE OF INTEGER VALUE OF THE COLOR
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string side_name(const int &colorAsci)
{
    switch (colorAsci)
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
        return "ERROR FINDING COLOR NAME...";
        break;
    }
}
