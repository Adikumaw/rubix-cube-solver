#ifndef _MAKECUBIE_H_
#define _MAKECUBIE_H_

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <utility>
#include <string_view>

using namespace std;

class makeCubie
{
   friend ostream &operator<<(ostream &os, const makeCubie &cube);
   friend istream &operator>>(istream &is, makeCubie &cube);

private:
   vector<vector<vector<char>>> cubeMain{};
   vector<char> sideBar, sideBarBackup, cornerColors;
   char topSideColor;
   short edgeSide;
   vector<string> CrossSolution, F2LSolution, OLLSolution, PLLSolution, tempSolution;
   vector<vector<string>> crossSolutions, f2lSolutions, ollSolutions, pllSolutions;
   // DECLARATION FOR SPEED OPOTIMIZATION....
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
      CONSTRUCTORS FOR MAKECUBIE CLASS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   makeCubie();
   makeCubie(const makeCubie &source);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
   OPERATOR OVERLOADING
   ----------------------------------------------------------------------------------------------------------------------------------------*/
   makeCubie &operator=(const makeCubie &source);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      SETTERS AND GETTERS METHODS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void set_cube();
   void get_cube();
   void get_cross_solution();
   void get_f2l_solution();
   void get_oll_solution();
   void get_pll_solution();
   int get_solution_size(string_view solutionName);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      SIDE ROTATION METHOD...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void side_rotate(const int &side, string_view direction);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CUBE SOLVING METHODS...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void cross_solver(makeCubie &storeSolution);
   void f2l_solver(makeCubie &temp_cube);
   string shortest_cube_solution();
   void oll_solver();
   void pll_solver();
   void correct_last_layer();
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void face_transpose(const int &side, string_view direction);
   void side_bar_sender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection);
   void side_bar_receiver(const int &side, string_view sideBarDirection);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      HELPER METHODS FOR CUBE SOLVING METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   bool get_edge_location(const char &color_1, int &side, int &block);
   bool get_corner_location(const char &color_1, const char &color_2, int &side, int &block);
   bool find_corner_colors(const char &bottom_color, const int &side, const int &row, const int &col);
   int find_edge_in_mid_lyr(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   bool find_edge_in_top_lyr(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   void f2LHelper(makeCubie &temp_cube, const int &side, const int &colorBlock);
   void set_corner_on_top(makeCubie &temp_cube, const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper);
   string oll_coder();
   string pll_coder(const vector<char> &orientation);
   bool pll_logic(const int &side, string_view PLLcode);
   bool oll_logic(const int &side, string_view OLLcode);
   int count_bottom_lyr_edge(const makeCubie &source);
   vector<char> get_equator_colors_orientation(const makeCubie &source);
   vector<char> get_cross_colors_orientation(const makeCubie &source);
   void cube_orienter(makeCubie &source, const int &side);
   void cube_reorienter(makeCubie &source, const int &side);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      ALGORITHEM IMPLEMENTATION METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void setalgo(const int &side, string str_algo, string_view applySolutionOn);
   void applySolution(string_view applySolutionOn);
   void algorithmCorrector(const int &side, vector<string> &algorithm);
};

#endif //_MAKECUBIE_H_