#ifndef _MAKECUBIE_H_
#define _MAKECUBIE_H_

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <utility>

using namespace std;

class makeCubie
{
private:
   vector<vector<vector<char>>> cubeMain{};
   vector<char> sideBar, sideBarBackup, cornerColors;
   char topSideColor;
   unsigned short edgeSide;
   vector<string> CrossSolution, F2LSolution, OLLSolution, PLLSolution, tempSolution;

   // DECLARATION FOR SPEED OPOTIMIZATION....
   vector<vector<char>> tempVec{
       {'0', '0', '0'},
       {'0', '0', '0'},
       {'0', '0', '0'}};
   //  enumerator for cube sides ......
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
      stand
   };

public:
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
   void sideRotate(int side, string direction);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      CUBE SOLVING METHODS...
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void crossSolver();
   void f2lSolver(makeCubie &temp_cube);
   void shortestF2LSolver();
   void OLLSolver();
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void faceTranspose(int side, string direction);
   void sideBarSender(int side, string sideBarDirection, string vectorStoringDirection);
   void sideBarReceiver(int side, string sideBarDirection);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      HELPER METHODS FOR CUBE SOLVING METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   bool cornerColorsFinder(int side, int row, int col);
   int sideEdgeFinder(makeCubie &temp_cube, char color_1, char color_2, string edgeSetter);
   bool edgeSetterOnTop(makeCubie &temp_cube, char color_1, char color_2, string edgeSetter);
   void f2LHelper(makeCubie &temp_cube, int side, int colorBlock);
   void cornerSetterOnTop(makeCubie &temp_cube, char color_2, char color_3, string F2LHelper);
   string OLLCoder();
   bool OLLLogic(int side, string OLLcode);
   /* ----------------------------------------------------------------------------------------------------------------------------------------
      ALGORITHEM IMPLEMENTATION METHODS.
      ----------------------------------------------------------------------------------------------------------------------------------------*/
   void setalgo(int side, string str_algo, string applySolutionOn);
   void applySolution(string applySolutionOn);
};

#endif //_MAKECUBIE_H_