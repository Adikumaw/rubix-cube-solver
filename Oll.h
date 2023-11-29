#ifndef _OLL_H_
#define _OLL_H_

#include "Cube.h"
#include <vector>

class Oll : public Cube
{
private:
    /* data */
    vector<string> solution;
    // vector<vector<string>> solutions;
    Oll &operator=(const Oll &oll);

public:
    Oll();
    Oll(const Cube &cube);
    void solver(vector<vector<string>> &solutions) override;
    virtual void applySolution(bool apply = true) override;
    long int oll_coder();
    bool oll_logic(const int &side, long int ollCode);
};

#endif // _OLL_H_