#ifndef _Cube_H_
#define _Cube_H_ 1
#pragma once

using namespace std;

#include "rotationAliases.h"
#include <vector>
#include <string>
#include <iostream>

string side_name(const int &colorAsci);

class Cube
{
private:
    /* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
    friend ostream &operator<<(ostream &os, const Cube &Cube);
    friend istream &operator>>(istream &is, Cube &Cube);
    friend class CubeSolver;

    vector<char> sideBar, sideBarBackup;
    short _i, _j, _row, _col;
    static vector<vector<char>> tempVec;

public:
    Cube &operator=(const Cube &cube);
    virtual void solver(vector<vector<string>> &solutions){};
    /* ----------------------------------------------------------------------------------------------------------------------------------------
      CONSTRUCTORS FOR Cube CLASS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
    Cube();
    Cube(const Cube &src);
    /* ----------------------------------------------------------------------------------------------------------------------------------------
       SHOWS Cube'S CURRENT STATUS...
       ----------------------------------------------------------------------------------------------------------------------------------------*/
    void Cube_state() const;

protected:
    // MEMBERS
    vector<vector<vector<char>>> CubeMain{};
    vector<string> tempSolution;
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

    // MEMBER FUNCTIONS....
    virtual void applySolution(const bool &apply = true)
    {
        applyTempSolution();
        tempSolution.clear();
    };
    // virtual vector<vector<string>> getSolutions();
    void setalgo(const int &side, string str_algo, const bool &apply = true);
    void setalgo(const int &side, vector<string> algo, const bool &apply = true);
    void applyTempSolution();
    /* ----------------------------------------------------------------------------------------------------------------------------------------
   checks color correctness
   ----------------------------------------------------------------------------------------------------------------------------------------*/
    bool check_colors();
    /* ----------------------------------------------------------------------------------------------------------------------------------------
   making Cube to default state
   ----------------------------------------------------------------------------------------------------------------------------------------*/
    void default_Cube();
    /* ----------------------------------------------------------------------------------------------------------------------------------------
   ROTATION METHODS....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
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
    // WHOLE Cube REORIENTATION....
    void x_axis_rotation_clockwise();
    void y_axis_rotation_clockwise();
    void z_axis_rotation_clockwise();
    void x_axis_rotation_counter_clockwise();
    void y_axis_rotation_counter_clockwise();
    void z_axis_rotation_counter_clockwise();
    /* ----------------------------------------------------------------------------------------------------------------------------------------
      THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE Cube.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
    void face_transpose(const int &side, string_view direction);
    void side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection);
    void side_bar_receiver(const int &side, string_view sideBarDirection);
};

#endif //_Cube_H_