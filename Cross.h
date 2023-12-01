#ifndef _CROSS_H_
#define _CROSS_H_

#include "Cube.h"

using namespace std;

class Cross : public Cube
{
private:
    /* data */
    vector<string> solution;
    // vector<vector<string>> solutions;
    Cross &operator=(const Cross &cross);
    int count_bottom_lyr_edge();
    vector<char> get_equator_colors_orientation();
    vector<char> get_cross_colors_orientation();
    bool get_edge_location(const char &color_1, int &side, int &block);

public:
    Cross(const Cube &cube);
    Cross();
    void solver(vector<vector<string>> &solutions) override;
    virtual void applySolution(const bool &apply) override;
};

#endif //_CROSS_H_