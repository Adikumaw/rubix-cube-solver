#ifndef _SOLVER_H_
#define _SOLVER_H_ 1
#pragma once

#include "Cube.h"
#include <algorithm>
#include <string_view>
#include "miscellaneous.h"

using namespace std;

class CubeSolver
{
   int bestSide{0}, trials{0};

private:
   Cube cube;
   vector<string> bestInCubeCross, bestInCubeF2l, bestInCubeOll, bestInCubePll;

public:
   friend istream &operator>>(istream &is, CubeSolver &solver)
   {
      std::cin >> solver.cube;
      return is;
   };
   friend ostream &operator<<(ostream &os, CubeSolver &solver)
   {
      std::cout << solver.cube;
      return os;
   };
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CONSTRUCTORS FOR Cube CLASS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   /* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
   // solver &operator=(const solver &source);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      SETTERS AND GETTERS METHODS
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void print(const int &duration);
   int printSolutionSteps(int currentStep);
   int printDirectSteps(const vector<string> &solution, const int &currentStep);
   vector<string> allInOneSolution();
   // void applySolution();
   void solve();
   int getSize(const vector<string> &solution);
   int getTotalSolutionSize();
   void Cube_orienter(Cube &src, const int &side);
   void Cube_reorienter(Cube &src, const int &side);
   void algorithmCorrector(const int &side, vector<string> &algorithm);
};

#endif //_SOLVER_H_