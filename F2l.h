#ifndef _F2L_H_
#define _F2L_H_

#include "Cube.h"
#include <vector>
#include <string_view>

class F2l : public Cube
{
private:
    vector<string> solution;
    // vector<vector<string>> solutions;
    F2l &operator=(const F2l &f2l);
    vector<char> cornerColors;
    char topSideColor;
    short edgeSide;

public:
    F2l(const Cube &cube);
    F2l();
    void solver(vector<vector<string>> &solutions) override;
    virtual void applySolution(const bool &apply = true) override;
    bool get_corner_location(const char &color_1, const char &color_2, int &side, int &block);
    bool find_corner_colors(const char &bottomColor, const int &side, const int &row, const int &col);
    bool find_edge_in_top_lyr(const char &color_1, const char &color_2, const bool &edgeSetter);
    int find_edge_in_mid_lyr(const char &color_1, const char &color_2, const bool &edgeSetter);
    void set_corner_on_top(const char &color_1, const char &color_2, const char &color_3, const bool &F2LHelper);
    void f2LHelper(const int &side, const int &colorBlock);
};

#endif //_F2L_H_