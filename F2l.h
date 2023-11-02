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
    vector<char> cornerColors;
    char topSideColor;
    short edgeSide;

public:
    virtual void applySolution(bool apply = true) override;
    void solver(vector<vector<string>> &solutions);
    bool get_corner_location(const char &color_1, const char &color_2, int &side, int &block);
    bool find_corner_colors(const char &bottomColor, const int &side, const int &row, const int &col);
    bool find_edge_in_top_lyr(const char &color_1, const char &color_2, string_view edgeSetter);
    int find_edge_in_mid_lyr(const char &color_1, const char &color_2, string_view edgeSetter);
    void set_corner_on_top(const char &color_1, const char &color_2, const char &color_3, string_view F2LHelper);
    void f2LHelper(const int &side, const int &colorBlock);
};

#endif //_F2L_H_