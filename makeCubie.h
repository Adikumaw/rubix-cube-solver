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
private:
   vector<vector<vector<char>>> cubeMain{};
   vector<char> sideBar, sideBarBackup, cornerColors;
   char topSideColor;
   short edgeSide;
   vector<string> CrossSolution, F2LSolution, OLLSolution, PLLSolution, tempSolution;

   // DECLARATION FOR SPEED OPOTIMIZATION....
   short i, j;
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
   void speedtester();
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
   void setcube();
   void getcube();
   void getCrossSolution();
   void getF2LSolution();
   void getOLLSolution();
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      SIDE ROTATION METHOD...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void sideRotate(const int &side, string_view direction);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CUBE SOLVING METHODS...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   int crossSolver();
   void f2lSolver(makeCubie &temp_cube);
   void shortestF2LSolver(const int &crossSide);
   void OLLSolver();
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void faceTranspose(const int &side, string_view direction);
   void sideBarSender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection);
   void sideBarReceiver(const int &side, string_view sideBarDirection);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      HELPER METHODS FOR CUBE SOLVING METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   bool fullCrossChecker(const makeCubie &temp_cube, const int &side);
   bool cornerColorsFinder(const char &bottom_color, const int &side, const int &row, const int &col);
   int sideEdgeFinder(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   bool edgeSetterOnTop(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter);
   void f2LHelper(makeCubie &temp_cube, const int &side, const int &colorBlock);
   void cornerSetterOnTop(makeCubie &temp_cube, const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper);
   string OLLCoder();
   bool OLLLogic(const int &side, string_view OLLcode);
   bool PLLChecker(const makeCubie &source);
   int crossChecker(const makeCubie &source);
   vector<char> crossColorOrientation(const makeCubie &source);
   vector<char> currentorientation(const makeCubie &source);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      ALGORITHEM IMPLEMENTATION METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void setalgo(const int &side, string str_algo, string_view applySolutionOn);
   void applySolution(string_view applySolutionOn);
   void algorithmCorrector(const int &side, vector<string> &algorithm);
};

#endif //_MAKECUBIE_H_