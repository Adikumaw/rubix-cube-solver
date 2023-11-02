#ifndef _PLL_H_
#define _PLL_H_
#include "Cube.h"
#include <vector>

class Pll : public Cube
{
private:
    /* data */
    vector<string> solution;

public:
    virtual void applySolution(bool apply = true) override;
    vector<string> solver();
    vector<char> get_equator_colors_orientation();
    string pll_coder(const vector<char> &orientation);
    bool pll_logic(const int &side, string_view PLLcode);
};

#endif // _PLL_H_