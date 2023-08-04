#ifndef _CUBE_H_
#define _CUBE_H_ 1
#pragma once

using namespace std;

#include "rotationAliases.h"
#include <vector>
#include <string>
#include <iostream>

string side_name(const int &colorAsci);

class cube
{
    /* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
    friend ostream &operator<<(ostream &os, const cube &cube);
    friend istream &operator>>(istream &is, cube &cube);

protected:
    vector<vector<vector<char>>> cubeMain{};
    vector<char> sideBar, sideBarBackup;
    short _i, _j, _row, _col;
    vector<vector<char>> tempVec{
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}};
    enum side
    {
        face,
        back,
        left,
        right,
        top,
        bottom,
        mid,
        equator,
        stand,
        axisX,
        axisY,
        axisZ
    };

public:
    static int trials;
    /* ----------------------------------------------------------------------------------------------------------------------------------------
      CONSTRUCTORS FOR CUBE CLASS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
    cube();
    cube(const cube &src);
    /* ----------------------------------------------------------------------------------------------------------------------------------------
       SIDE ROTATION METHOD...
       ----------------------------------------------------------------------------------------------------------------------------------------*/
    void side_rotate(const int &side, string_view direction);
    /* ----------------------------------------------------------------------------------------------------------------------------------------
       SHOWS CUBE'S CURRENT STATUS...
       ----------------------------------------------------------------------------------------------------------------------------------------*/
    void cube_state();
    // CLOCKWISE ROTATIONS....
    void face_rotate_clockwise();
    void right_rotate_clockwise();
    void back_rotate_clockwise();
    void left_rotate_clockwise();
    void top_rotate_clockwise();
    void bottom_rotate_clockwise();
    void mid_rotate_clockwise();
    void equator_rotate_clockwise();
    void stand_rotate_clockwise();
    // COUNTER CLOCKWISE ROTATIONS....
    void face_rotate_counter_clockwise();
    void right_rotate_counter_clockwise();
    void back_rotate_counter_clockwise();
    void left_rotate_counter_clockwise();
    void top_rotate_counter_clockwise();
    void bottom_rotate_counter_clockwise();
    void mid_rotate_counter_clockwise();
    void equator_rotate_counter_clockwise();
    void stand_rotate_counter_clockwise();
    // TWICE MOVES....
    void face_rotate_two_times();
    void right_rotate_two_times();
    void back_rotate_two_times();
    void left_rotate_two_times();
    void top_rotate_two_times();
    void bottom_rotate_two_times();
    // WHOLE CUBE REORIENTATION....
    void x_axis_rotation_clockwise();
    void y_axis_rotation_clockwise();
    void z_axis_rotation_clockwise();
    void x_axis_rotation_counter_clockwise();
    void y_axis_rotation_counter_clockwise();
    void z_axis_rotation_counter_clockwise();
    /* ----------------------------------------------------------------------------------------------------------------------------------------
      THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
    void face_transpose(const int &side, string_view direction);
    void side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection);
    void side_bar_receiver(const int &side, string_view sideBarDirection);
};

#endif //_CUBE_H_