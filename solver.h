#ifndef _SOLVER_H_
#define _SOLVER_H_ 1
#pragma once

#include "cube.h"
#include <algorithm>
#include <random>
#include <string_view>

using namespace std;

class solver : public cube
{
private:
   vector<char> cornerColors;
   char topSideColor;
   short edgeSide;
   vector<string> CrossSolution, F2LSolution, OLLSolution, PLLSolution, tempSolution;
   vector<vector<string>> crossSolutions, f2lSolutions, ollSolutions, pllSolutions;

public:
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CONSTRUCTORS FOR cube CLASS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   solver();
   solver(const solver &src);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
   solver &operator=(const solver &source);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      SETTERS AND GETTERS METHODS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void get_cross_solution();
   void get_f2l_solution();
   void get_oll_solution();
   void get_pll_solution();
   int get_solution_size(string_view solutionName);

   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CUBE SOLVING METHODS...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void cross_solver(solver &storeSolution);
   void f2l_solver(solver &temp_cube);
   string shortest_cube_solution();
   void oll_solver();
   void pll_solver();
   void correct_last_layer();

   /* ----------------------------------------------------------------------------------------------------------------------------------------
      HELPER METHODS FOR CUBE SOLVING METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   bool get_edge_location(const char &color_1, int &side, int &block);
   bool get_corner_location(const char &color_1, const char &color_2, int &side, int &block);
   bool find_corner_colors(const char &bottom_color, const int &side, const int &row, const int &col);
   int find_edge_in_mid_lyr(solver &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   bool find_edge_in_top_lyr(solver &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   void f2LHelper(solver &temp_cube, const int &side, const int &colorBlock);
   void set_corner_on_top(solver &temp_cube, const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper);
   string oll_coder();
   string pll_coder(const vector<char> &orientation);
   bool pll_logic(const int &side, string_view PLLcode);
   bool oll_logic(const int &side, string_view OLLcode);
   int count_bottom_lyr_edge(const solver &src);
   vector<char> get_equator_colors_orientation(const solver &source);
   vector<char> get_cross_colors_orientation(const solver &source);
   void cube_orienter(solver &source, const int &side);
   void cube_reorienter(solver &source, const int &side);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      ALGORITHEM IMPLEMENTATION METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void setalgo(const int &side, string str_algo, string_view applySolutionOn);
   void applySolution(string_view applySolutionOn);
   void algorithmCorrector(const int &side, vector<string> &algorithm);
};

#endif //_SOLVER_H_