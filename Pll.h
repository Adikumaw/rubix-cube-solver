#ifndef _PLL_H_
#define _PLL_H_
#include "Cube.h"
#include <vector>

class Pll : public Cube
{
private:
    /* data */
    vector<string> solution;
    Pll &operator=(const Pll &pll);

public:
    Pll();
    Pll(const Cube &cube);
    void solver(vector<vector<string>> &solutions) override;
    virtual void applySolution(const bool &apply = true) override;
    vector<char> get_equator_colors_orientation();
    string pll_coder(const vector<char> &orientation);
    bool pll_logic(const int &side, string_view PLLcode);
    void correct_last_layer();
};

#endif // _PLL_H_