#include "makeCubie.h"

#define F sideRotate(side::face, "clk")
#define L sideRotate(side::left, "clk")
#define R sideRotate(side::right, "clk")
#define U sideRotate(side::top, "clk")
#define D sideRotate(side::bottom, "clk")
#define B sideRotate(side::back, "clk")
#define FP sideRotate(side::face, "antclk")
#define LP sideRotate(side::left, "antclk")
#define RP sideRotate(side::right, "antclk")
#define UP sideRotate(side::top, "antclk")
#define DP sideRotate(side::bottom, "antclk")
#define BP sideRotate(side::back, "antclk")
#define M sideRotate(side::mid, "clk")
#define E sideRotate(side::equator, "clk")
#define S sideRotate(side::stand, "clk")
#define MP sideRotate(side::mid, "antclk")
#define EP sideRotate(side::equator, "antclk")
#define SP sideRotate(side::stand, "antclk")

void solutionOptimizer(vector<std::string> &solution);
string sideColor(const int &colorAsci);

void makeCubie::speedtester()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rang1to12(1, 12);
    long int trials{0};
    int moves{0};
    bool solve{false};
    makeCubie temp_cube(*this);
    while (!solve)
    {
        moves = rang1to12(rng);

        switch (moves)
        {
        case 1:
            CrossSolution.push_back("F");
            temp_cube.F;
            break;
        case 2:
            CrossSolution.push_back("L");
            temp_cube.L;
            break;
        case 3:
            CrossSolution.push_back("R");
            temp_cube.R;
            break;
        case 4:
            CrossSolution.push_back("U");
            temp_cube.U;
            break;
        case 5:
            CrossSolution.push_back("D");
            temp_cube.D;
            break;
        case 6:
            CrossSolution.push_back("B");
            temp_cube.B;
            break;
        case 7:
            CrossSolution.push_back("FP");
            temp_cube.FP;
            break;
        case 8:
            CrossSolution.push_back("LP");
            temp_cube.LP;
            break;
        case 9:
            CrossSolution.push_back("RP");
            temp_cube.RP;
            break;
        case 10:
            CrossSolution.push_back("UP");
            temp_cube.UP;
            break;
        case 11:
            CrossSolution.push_back("DP");
            temp_cube.DP;
            break;
        case 12:
            CrossSolution.push_back("BP");
            temp_cube.BP;
            break;
        default:
            break;
        }

        trials++;
        std::cout << "\r" << trials << " combinations tried!";
        if (trials > 10000000)
            break;
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   CONSTRUCTORS FOR MAKECUBIE CLASS
   ----------------------------------------------------------------------------------------------------------------------------------------*/
makeCubie::makeCubie()
{
    for (int l{0}; l < 6; l++)
    {
        cubeMain.push_back(vector<vector<char>>());
        for (int m{0}; m < 3; m++)
        {
            cubeMain.at(l).push_back(vector<char>());
            for (int n{0}; n < 3; n++)
            {
                cubeMain.at(l).at(m).push_back('x');
            }
        }
    }
}
makeCubie::makeCubie(const makeCubie &source)
    : makeCubie{}
{
    for (int l{0}; l < 6; l++)
    {
        for (int m{0}; m < 3; m++)
        {
            for (int n{0}; n < 3; n++)
            {
                cubeMain.at(l).at(m).at(n) = source.cubeMain.at(l).at(m).at(n);
            }
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLOADING
----------------------------------------------------------------------------------------------------------------------------------------*/
makeCubie &makeCubie::operator=(const makeCubie &source)
{
    // FOR THE CONDITION WHEN SAME CLASS ARE ASSIGNED;
    if (this == &source)
        return *this;

    for (int l{0}; l < 6; l++)
    {
        for (int m{0}; m < 3; m++)
        {
            for (int n{0}; n < 3; n++)
            {
                this->cubeMain.at(l).at(m).at(n) = source.cubeMain.at(l).at(m).at(n);
            }
        }
    }
    return *this;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------
   SETTER AND GETTER FOR THE RUBIX CUBE
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::setcube()
{
    char ch{};
    for (int l{0}; l < 6; l++)
    {
        std::cout << "ENTER THE COLOR OF \"" << sideColor(l) << "\" SIDE OF THE CUBE: " << endl;
        for (int m{0}; m < 3; m++)
        {
            for (int n{0}; n < 3; n++)
            {
                cin >> ch;
                cubeMain.at(l).at(m).at(n) = ch;
            }
        }
    }
}
void makeCubie::getcube()
{
    for (size_t i{0}; i < cubeMain.size(); i++)
    {
        std::cout << "\nTHE ELEMENTS OF \"" << sideColor(i) << "\" SIDE ARE:" << endl;
        for (size_t j{0}; j < cubeMain.at(i).size(); j++)
        {
            for (size_t k{0}; k < cubeMain.at(i).at(j).size(); k++)
            {
                std::cout << cubeMain.at(i).at(j).at(k) << " ";
            }
            std::cout << endl;
        }
    }
};
void makeCubie::getCrossSolution()
{
    for (size_t i{0}; i < CrossSolution.size(); i++)
    {
        std::cout << CrossSolution.at(i) << " ";
    }
}
void makeCubie::getF2LSolution()
{
    for (size_t i{0}; i < F2LSolution.size(); i++)
    {
        std::cout << F2LSolution.at(i) << " ";
    }
}
void makeCubie::getOLLSolution()
{
    for (size_t i{0}; i < OLLSolution.size(); i++)
    {
        std::cout << OLLSolution.at(i) << " ";
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE SIDE ROTATION LOGIC FUNCTION ON THE BASIS OF SIDE AND DIRECTION PROVIDED
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::sideRotate(const int &side, string_view direction)
{
    sideBarBackup.clear();
    if (side >= face && side <= bottom)
    {
        faceTranspose(side, direction);
        if (side == face)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[top].at(2).at(i));
            if (direction == "clk")
            {
                sideBarSender(left, "right", "rev.");
                sideBarReceiver(top, "bottom");
                sideBarSender(bottom, "top", "forward");
                sideBarReceiver(left, "right");
                sideBarSender(right, "left", "rev.");
                sideBarReceiver(bottom, "top");
                for (int i{0}; i < 3; i++)
                    cubeMain[right].at(i).at(0) = sideBarBackup.at(i);
            }
            else
            {
                sideBarSender(right, "left", "forward");
                sideBarReceiver(top, "bottom");
                sideBarSender(bottom, "top", "rev.");
                sideBarReceiver(right, "left");
                sideBarSender(left, "right", "forward");
                sideBarReceiver(bottom, "top");
                for (int j{2}, i{0}; j >= 0, i < 3; j--, i++)
                    cubeMain[left].at(i).at(2) = sideBarBackup.at(j);
                // sideBarReceiver(left, "right");
            }
        }
        else if (side == back)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[top].at(0).at(i));
            if (direction == "clk")
            {
                sideBarSender(right, "right", "forward");
                sideBarReceiver(top, "top");
                sideBarSender(bottom, "bottom", "rev.");
                sideBarReceiver(right, "right");
                sideBarSender(left, "left", "forward");
                sideBarReceiver(bottom, "bottom");
                for (int j{2}, i{0}; j >= 0, i < 3; j--, i++)
                    cubeMain[left].at(i).at(0) = sideBarBackup.at(j);
                // sideBarReceiver(left, "left");
            }
            else
            {
                sideBarSender(left, "left", "rev.");
                sideBarReceiver(top, "top");
                sideBarSender(bottom, "bottom", "forward");
                sideBarReceiver(left, "left");
                sideBarSender(right, "right", "rev.");
                sideBarReceiver(bottom, "bottom");
                for (int i{0}; i < 3; i++)
                    cubeMain[right].at(i).at(2) = sideBarBackup.at(i);
            }
        }
        else if (side == left)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[top].at(i).at(0));
            if (direction == "clk")
            {
                sideBarSender(back, "right", "rev.");
                sideBarReceiver(top, "left");
                sideBarSender(bottom, "left", "rev.");
                sideBarReceiver(back, "right");
                sideBarSender(face, "left", "forward");
                sideBarReceiver(bottom, "left");
                for (int i{0}; i < 3; i++)
                    cubeMain[face].at(i).at(0) = sideBarBackup.at(i);
            }
            else
            {
                sideBarSender(face, "left", "forward");
                sideBarReceiver(top, "left");
                sideBarSender(bottom, "left", "forward");
                sideBarReceiver(face, "left");
                sideBarSender(back, "right", "rev.");
                sideBarReceiver(bottom, "left");
                for (int j{2}, i{0}; j >= 0, i < 3; j--, i++)
                    cubeMain[back].at(i).at(2) = sideBarBackup.at(j);
                // sideBarReceiver(back, "right");
            }
        }
        else if (side == right)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[top].at(i).at(2));
            if (direction == "clk")
            {
                sideBarSender(face, "right", "forward");
                sideBarReceiver(top, "right");
                sideBarSender(bottom, "right", "forward");
                sideBarReceiver(face, "right");
                sideBarSender(back, "left", "rev.");
                sideBarReceiver(bottom, "right");
                for (int j{2}, i{0}; j >= 0, i < 3; j--, i++)
                    cubeMain[back].at(i).at(0) = sideBarBackup.at(j);
                // sideBarReceiver(back, "left");
            }
            else
            {
                sideBarSender(back, "left", "rev.");
                sideBarReceiver(top, "right");
                sideBarSender(bottom, "right", "rev.");
                sideBarReceiver(back, "left");
                sideBarSender(face, "right", "forward");
                sideBarReceiver(bottom, "right");
                for (int i{0}; i < 3; i++)
                    cubeMain[face].at(i).at(2) = sideBarBackup.at(i);
            }
        }
        else if (side == top)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[face].at(0).at(i));
            if (direction == "clk")
            {
                sideBarSender(right, "top", "forward");
                sideBarReceiver(face, "top");
                sideBarSender(back, "top", "forward");
                sideBarReceiver(right, "top");
                sideBarSender(left, "top", "forward");
                sideBarReceiver(back, "top");
                for (int i{0}; i < 3; i++)
                    cubeMain[left].at(0).at(i) = sideBarBackup.at(i);
            }
            else
            {
                sideBarSender(left, "top", "forward");
                sideBarReceiver(face, "top");
                sideBarSender(back, "top", "forward");
                sideBarReceiver(left, "top");
                sideBarSender(right, "top", "forward");
                sideBarReceiver(back, "top");
                for (int i{0}; i < 3; i++)
                    cubeMain[right].at(0).at(i) = sideBarBackup.at(i);
            }
        }
        else if (side == bottom)
        {
            for (int i{0}; i < 3; i++)
                sideBarBackup.push_back(cubeMain[face].at(2).at(i));
            if (direction == "clk")
            {
                sideBarSender(left, "bottom", "forward");
                sideBarReceiver(face, "bottom");
                sideBarSender(back, "bottom", "forward");
                sideBarReceiver(left, "bottom");
                sideBarSender(right, "bottom", "forward");
                sideBarReceiver(back, "bottom");
                for (int i{0}; i < 3; i++)
                    cubeMain[right].at(2).at(i) = sideBarBackup.at(i);
            }
            else
            {
                sideBarSender(right, "bottom", "forward");
                sideBarReceiver(face, "bottom");
                sideBarSender(back, "bottom", "forward");
                sideBarReceiver(right, "bottom");
                sideBarSender(left, "bottom", "forward");
                sideBarReceiver(back, "bottom");
                for (int i{0}; i < 3; i++)
                    cubeMain[left].at(2).at(i) = sideBarBackup.at(i);
            }
        }
    }
    else if (side == mid)
    {
        for (int i{0}; i < 3; i++)
            sideBarBackup.push_back(cubeMain[face].at(i).at(1));
        if (direction == "clk")
        {
            sideBarSender(top, "mid", "forward");
            sideBarReceiver(face, "mid");
            sideBarSender(back, "mid", "rev.");
            sideBarReceiver(top, "mid");
            sideBarSender(bottom, "mid", "rev.");
            sideBarReceiver(back, "mid");
            for (int i{0}; i < 3; i++)
                cubeMain[bottom].at(i).at(1) = sideBarBackup.at(i);
        }
        else
        {
            sideBarSender(bottom, "mid", "forward");
            sideBarReceiver(face, "mid");
            sideBarSender(back, "mid", "rev.");
            sideBarReceiver(bottom, "mid");
            sideBarSender(top, "mid", "rev.");
            sideBarReceiver(back, "mid");
            for (int i{0}; i < 3; i++)
                cubeMain[top].at(i).at(1) = sideBarBackup.at(i);
        }
    }
    else if (side == equator)
    {
        for (int i{0}; i < 3; i++)
            sideBarBackup.push_back(cubeMain[face].at(1).at(i));
        if (direction == "clk")
        {
            sideBarSender(left, "equator", "forward");
            sideBarReceiver(face, "equator");
            sideBarSender(back, "equator", "forward");
            sideBarReceiver(left, "equator");
            sideBarSender(right, "equator", "forward");
            sideBarReceiver(back, "equator");
            for (int i{0}; i < 3; i++)
                cubeMain[right].at(1).at(i) = sideBarBackup.at(i);
        }
        else
        {
            sideBarSender(right, "equator", "forward");
            sideBarReceiver(face, "equator");
            sideBarSender(back, "equator", "forward");
            sideBarReceiver(right, "equator");
            sideBarSender(left, "equator", "forward");
            sideBarReceiver(back, "equator");
            for (int i{0}; i < 3; i++)
                cubeMain[left].at(1).at(i) = sideBarBackup.at(i);
        }
    }
    else if (side == stand)
    {
        for (int i{0}; i < 3; i++)
            sideBarBackup.push_back(cubeMain[top].at(1).at(i));
        if (direction == "clk")
        {
            sideBarSender(left, "mid", "rev.");
            sideBarReceiver(top, "equator");
            sideBarSender(bottom, "equator", "forward");
            sideBarReceiver(left, "mid");
            sideBarSender(right, "mid", "rev.");
            sideBarReceiver(bottom, "equator");
            for (int i{0}; i < 3; i++)
                cubeMain[right].at(i).at(1) = sideBarBackup.at(i);
        }
        else
        {
            sideBarSender(right, "mid", "forward");
            sideBarReceiver(top, "equator");
            sideBarSender(bottom, "equator", "rev.");
            sideBarReceiver(right, "mid");
            sideBarSender(left, "mid", "forward");
            sideBarReceiver(bottom, "equator");
            for (int j{2}, i{0}; j >= 0, i < 3; j--, i++)
                cubeMain[left].at(i).at(1) = sideBarBackup.at(j);
            // sideBarReceiver(left, "mid");
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THE THREE BELLOW FUNCITON ARE FOR SIDE ROTATION LOGICS OF THE CUBE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::faceTranspose(const int &side, string_view direction)
{
    int i{0}, j{0};
    if (direction == "antclk")
    {
        j = 0;
        for (size_t l{0}; l < cubeMain[side].size(); l++)
        {
            i = 2;
            for (size_t m{0}; m < cubeMain[side].at(l).size(); m++)
            {
                tempVec[i][j] = cubeMain[side].at(l).at(m);
                i--;
            }
            j++;
        }
    }
    else if (direction == "clk")
    {
        j = 2;
        for (size_t l{0}; l < cubeMain[side].size(); l++)
        {
            i = 0;
            for (size_t m{0}; m < cubeMain[side].at(l).size(); m++)
            {
                tempVec[i][j] = cubeMain[side].at(l).at(m);
                ;
                i++;
            }
            j--;
        }
    }
    (cubeMain)[side] = tempVec;
}
void makeCubie::sideBarSender(const int &side, string_view sideBarDirection, string_view vectorStoringDirection)
{
    if (vectorStoringDirection == "forward")
    {
        if (sideBarDirection == "left")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(i).at(0));
        }
        else if (sideBarDirection == "right")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(i).at(2));
        }
        else if (sideBarDirection == "top")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(0).at(i));
        }
        else if (sideBarDirection == "bottom")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(2).at(i));
        }
        else if (sideBarDirection == "mid")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(i).at(1));
        }
        else if (sideBarDirection == "equator")
        {
            for (int i{0}; i < 3; i++)
                sideBar.push_back(cubeMain[side].at(1).at(i));
        }
    }
    else
    {
        if (sideBarDirection == "left")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(i).at(0));
        }
        else if (sideBarDirection == "right")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(i).at(2));
        }
        else if (sideBarDirection == "top")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(0).at(i));
        }
        else if (sideBarDirection == "bottom")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(2).at(i));
        }
        else if (sideBarDirection == "mid")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(i).at(1));
        }
        else if (sideBarDirection == "equator")
        {
            for (int i{2}; i >= 0; i--)
                sideBar.push_back(cubeMain[side].at(1).at(i));
        }
    }
}
void makeCubie::sideBarReceiver(const int &side, string_view sideBarDirection)
{
    if (sideBarDirection == "bottom")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(2).at(i) = sideBar.at(i);
    }
    else if (sideBarDirection == "left")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(i).at(0) = sideBar.at(i);
    }
    else if (sideBarDirection == "top")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(0).at(i) = sideBar.at(i);
    }
    else if (sideBarDirection == "right")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(i).at(2) = sideBar.at(i);
    }
    else if (sideBarDirection == "mid")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(i).at(1) = sideBar.at(i);
    }
    else if (sideBarDirection == "equator")
    {
        for (int i{0}; i < 3; i++)
            cubeMain[side].at(1).at(i) = sideBar.at(i);
    }
    sideBar.clear();
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE BOTTOM CROSS OF TEH RUBIX CUBE...
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::crossSolver()
{
    // srand(time(NULL));
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rang1to12(1, 12);
    long int trials{0};
    int moves{0};
    bool solve{false};
    makeCubie temp_cube(*this);
    std::cout << endl;
    while (!solve)
    {
        temp_cube = *this;
        while (temp_cube.cubeMain[bottom].at(0).at(1) != 'w' || temp_cube.cubeMain[bottom].at(1).at(0) != 'w' || temp_cube.cubeMain[bottom].at(1).at(2) != 'w' || temp_cube.cubeMain[bottom].at(2).at(1) != 'w' || temp_cube.cubeMain[face].at(2).at(1) != 'b' || temp_cube.cubeMain[right].at(2).at(1) != 'r' || temp_cube.cubeMain[back].at(2).at(1) != 'g' || temp_cube.cubeMain[left].at(2).at(1) != 'o')
        {
            moves = rang1to12(rng);

            switch (moves)
            {
            case 1:
                CrossSolution.push_back("F");
                temp_cube.F;
                break;
            case 2:
                CrossSolution.push_back("L");
                temp_cube.L;
                break;
            case 3:
                CrossSolution.push_back("R");
                temp_cube.R;
                break;
            case 4:
                CrossSolution.push_back("U");
                temp_cube.U;
                break;
            case 5:
                CrossSolution.push_back("D");
                temp_cube.D;
                break;
            case 6:
                CrossSolution.push_back("B");
                temp_cube.B;
                break;
            case 7:
                CrossSolution.push_back("FP");
                temp_cube.FP;
                break;
            case 8:
                CrossSolution.push_back("LP");
                temp_cube.LP;
                break;
            case 9:
                CrossSolution.push_back("RP");
                temp_cube.RP;
                break;
            case 10:
                CrossSolution.push_back("UP");
                temp_cube.UP;
                break;
            case 11:
                CrossSolution.push_back("DP");
                temp_cube.DP;
                break;
            case 12:
                CrossSolution.push_back("BP");
                temp_cube.BP;
                break;
            default:
                break;
            }

            trials++;
            std::cout << "\r" << trials << " combinations tried!";
            if ((CrossSolution.size() % 10) == 0)
            {
                solutionOptimizer(CrossSolution);
            }
            if ((CrossSolution.size() % 10) == 0)
            {
                CrossSolution.clear();
                solve = false;
                break;
            }
            solve = true;
        }
        if (moves == 0)
            return;
    }

    solutionOptimizer(CrossSolution);
    // copy the temp cube to the source cube....
    *this = temp_cube;
    std::cout << "\nCross Solved...." << endl;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SOLVES THE F2L_LAYER OF THE RUBIX CUBE....
   AND A TEMPRORY MAKECUBIE CLASS SHOULD BE PROVIDED TO THE FUNCTION FOR BETTER PERFORMANCE....
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::f2lSolver(makeCubie &temp_cube)
{
    // srand(time(NULL));
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> rang0to5(0, 5);
    std::uniform_int_distribution<int> rang0to1(0, 1);
    std::uniform_int_distribution<int> rang1to4(1, 4);
    int temp{}, side{}, sentinal{}, block{};
    bool cornerLocMatch{false}, boolEdgeSetter{false};
    // bool cornerFound{false};
    // while (!cornerFound)
    while (
        cubeMain.at(bottom).at(1).at(1) != cubeMain.at(bottom).at(0).at(0) || cubeMain.at(bottom).at(1).at(1) != cubeMain.at(bottom).at(0).at(2) || cubeMain.at(bottom).at(1).at(1) != cubeMain.at(bottom).at(2).at(0) || cubeMain.at(bottom).at(1).at(1) != cubeMain.at(bottom).at(2).at(2) || cubeMain.at(face).at(1).at(1) != cubeMain.at(face).at(1).at(0) || cubeMain.at(face).at(1).at(1) != cubeMain.at(face).at(2).at(0) || cubeMain.at(face).at(1).at(1) != cubeMain.at(face).at(1).at(2) || cubeMain.at(face).at(1).at(1) != cubeMain.at(face).at(2).at(2) || cubeMain.at(right).at(1).at(1) != cubeMain.at(right).at(1).at(0) || cubeMain.at(right).at(1).at(1) != cubeMain.at(right).at(2).at(0) || cubeMain.at(right).at(1).at(1) != cubeMain.at(right).at(1).at(2) || cubeMain.at(right).at(1).at(1) != cubeMain.at(right).at(2).at(2) || cubeMain.at(back).at(1).at(1) != cubeMain.at(back).at(1).at(0) || cubeMain.at(back).at(1).at(1) != cubeMain.at(back).at(2).at(0) || cubeMain.at(back).at(1).at(1) != cubeMain.at(back).at(1).at(2) || cubeMain.at(back).at(1).at(1) != cubeMain.at(back).at(2).at(2) || cubeMain.at(left).at(1).at(1) != cubeMain.at(left).at(1).at(0) || cubeMain.at(left).at(1).at(1) != cubeMain.at(left).at(2).at(0) || cubeMain.at(left).at(1).at(1) != cubeMain.at(left).at(1).at(2) || cubeMain.at(left).at(1).at(1) != cubeMain.at(left).at(2).at(2))
    {
        // side = ((rand() % (5 - 0 + 1)) + 0);
        side = rang0to5(rng);
        block = rang1to4(rng);
        // -------------------------------------------------- BOTTOM SIDE ---------------------------------------------------------------
        if (side == bottom)
        {
            switch (block)
            {
            case 1:
                if (cubeMain[side].at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    if (cornerLocMatch)
                    {
                        // for optimization purposes....
                        boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        sentinal = -1;
                        if (!boolEdgeSetter)
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (sentinal == -1)
                        {
                            if (edgeSide == left)
                            {
                                setalgo(left, "U R UP RP UP FP U F", "f2l");
                            }
                            else if (edgeSide == face)
                            {
                                setalgo(left, "UP FP U F U R UP RP", "f2l");
                            }
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(left, "R UP R R U U R UP FP U F", "f2l");
                        };
                    }
                    else
                    {
                        temp = rang0to1(rng);
                        switch (temp)
                        {
                        case 0:
                            setalgo(left, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(left, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                };
                break;
            case 2:
                if (cubeMain[side].at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    if (cornerLocMatch)
                    {
                        boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        sentinal = -1;
                        if (!boolEdgeSetter)
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (sentinal == -1)
                        {
                            if (edgeSide == face)
                            {
                                setalgo(face, "U R UP RP UP FP U F", "f2l");
                            }
                            else if (edgeSide == right)
                            {
                                setalgo(face, "UP FP U F U R UP RP", "f2l");
                            }
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(face, "R UP R R U U R UP FP U F", "f2l");
                        };
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(face, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(face, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 3:
                if (cubeMain[side].at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    if (cornerLocMatch)
                    {
                        boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        sentinal = -1;
                        if (!boolEdgeSetter)
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (sentinal == -1)
                        {
                            if (edgeSide == back)
                            {
                                setalgo(back, "U R UP RP UP FP U F", "f2l");
                            }
                            else if (edgeSide == left)
                            {
                                setalgo(back, "UP FP U F U R UP RP", "f2l");
                            }
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(back, "R UP R R U U R UP FP U F", "f2l");
                        };
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(back, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(back, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (cubeMain[side].at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    if (cornerLocMatch)
                    {
                        boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        sentinal = -1;
                        if (!boolEdgeSetter)
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                        if (sentinal == -1)
                        {
                            if (edgeSide == right)
                            {
                                setalgo(right, "U R UP RP UP FP U F", "f2l");
                            }
                            else if (edgeSide == back)
                            {
                                setalgo(right, "UP FP U F U R UP RP", "f2l");
                            }
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(right, "R UP R R U U R UP FP U F", "f2l");
                        };
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(right, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(right, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        // -------------------------------------------------- FACE SIDE ---------------------------------------------------------------
        else if (side == face)
        {
            switch (block)
            {
            case 1:
                if (cubeMain.at(side).at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(left, "U FP U F U FP U U F", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(left, "U FP UP F UP R U RP", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "R UP RP U U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(left, "UP R UP RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "U FP U U F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(left, "R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "U FP UP F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(left, "UP R U RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "F RP FP R", "f2l");
                            }
                            else
                            {
                                setalgo(left, "U FP U U F UP R U RP", "f2l");
                            }
                        }
                    } // this else is for the condition when the corner or edge is not on the right location....
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 2:
                if (cubeMain.at(side).at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(face, "UP R UP RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(face, "UP R U RP U FP UP F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "FP U F U U R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(face, "U FP U F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(face, "UP R U U RP U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "UP R U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(face, "U FP UP F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "UP R U U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(face, "FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 3:
                if (cubeMain.at(side).at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(left, "R UP RP U R U U RP U R UP RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(left, "R U RP UP R UP RP U U FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == face)
                        {
                            setalgo(left, "R U RP UP R U RP", "f2l");
                        }
                        else if (edgeSide == left)
                        {
                            setalgo(left, "FP U F UP FP U F", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(left, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(left, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (cubeMain.at(side).at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(face, "R UP RP UP R U RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(face, "R UP RP U FP UP F UP FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == face)
                        {
                            setalgo(face, "FP UP F U FP UP F", "f2l");
                        }
                        else if (edgeSide == right)
                        {
                            setalgo(face, "R UP RP U R UP RP", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(face, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(face, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        // -------------------------------------------------- RIGHT SIDE ---------------------------------------------------------------
        else if (side == right)
        {
            switch (block)
            {
            case 1:
                if (cubeMain.at(side).at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(face, "U FP U F U FP U U F", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(face, "U FP UP F UP R U RP", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "R UP RP U U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "UP R UP RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "U FP U U F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "U FP UP F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "UP R U RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "F RP FP R", "f2l");
                            }
                            else
                            {
                                setalgo(face, "U FP U U F UP R U RP", "f2l");
                            }
                        }
                    } // this else is for the condition when the corner or edge is not on the right location....
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 2:
                if (cubeMain.at(side).at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(right, "UP R UP RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(right, "UP R U RP U FP UP F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "FP U F U U R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "U FP U F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "UP R U U RP U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "UP R U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "U FP UP F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "UP R U U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 3:
                if (cubeMain.at(side).at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(face, "R UP RP U R U U RP U R UP RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(face, "R U RP UP R UP RP U U FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == right)
                        {
                            setalgo(face, "R U RP UP R U RP", "f2l");
                        }
                        else if (edgeSide == face)
                        {
                            setalgo(face, "FP U F UP FP U F", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(face, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(face, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (cubeMain.at(side).at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(right, "R UP RP UP R U RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(right, "R UP RP U FP UP F UP FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == right)
                        {
                            setalgo(right, "FP UP F U FP UP F", "f2l");
                        }
                        else if (edgeSide == back)
                        {
                            setalgo(right, "R UP RP U R UP RP", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(right, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(right, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        // -------------------------------------------------- BACK SIDE ---------------------------------------------------------------
        else if (side == back)
        {
            switch (block)
            {
            case 1:
                if (cubeMain.at(side).at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(right, "U FP U F U FP U U F", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(right, "U FP UP F UP R U RP", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "R UP RP U U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(right, "UP R UP RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "U FP U U F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(right, "R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "U FP UP F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(right, "UP R U RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "F RP FP R", "f2l");
                            }
                            else
                            {
                                setalgo(right, "U FP U U F UP R U RP", "f2l");
                            }
                        }
                    } // this else is for the condition when the corner or edge is not on the right location....
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 2:
                if (cubeMain.at(side).at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(back, "UP R UP RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(back, "UP R U RP U FP UP F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "FP U F U U R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(back, "U FP U F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(back, "UP R U U RP U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "UP R U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(back, "U FP UP F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "UP R U U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(back, "FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 3:
                if (cubeMain.at(side).at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(right, "R UP RP U R U U RP U R UP RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(right, "R U RP UP R UP RP U U FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == back)
                        {
                            setalgo(right, "R U RP UP R U RP", "f2l");
                        }
                        else if (edgeSide == right)
                        {
                            setalgo(right, "FP U F UP FP U F", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(right, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(right, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (cubeMain.at(side).at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(back, "R UP RP UP R U RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(back, "R UP RP U FP UP F UP FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == back)
                        {
                            setalgo(back, "FP UP F U FP UP F", "f2l");
                        }
                        else if (edgeSide == left)
                        {
                            setalgo(back, "R UP RP U R UP RP", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(back, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(back, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        // -------------------------------------------------- LEFT SIDE ---------------------------------------------------------------
        else if (side == left)
        {
            switch (block)
            {
            case 1:
                if (cubeMain.at(side).at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(back, "U FP U F U FP U U F", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(back, "U FP UP F UP R U RP", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "R UP RP U U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "UP R UP RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "U FP U U F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "U FP UP F U FP U U F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "UP R U RP U R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "F RP FP R", "f2l");
                            }
                            else
                            {
                                setalgo(back, "U FP U U F UP R U RP", "f2l");
                            }
                        }
                    } // this else is for the condition when the corner or edge is not on the right location....
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 2:
                if (cubeMain.at(side).at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(left, "UP R UP RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(left, "UP R U RP U FP UP F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // the corner setter will set the corner and will pass the control back to this function.....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "FP U F U U R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "U FP U F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "UP R U U RP U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "UP R U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "U FP UP F UP FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "UP R U U RP UP R U U RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 3:
                if (cubeMain.at(side).at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(back, "R UP RP U R U U RP U R UP RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(back, "R U RP UP R UP RP U U FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == left)
                        {
                            setalgo(back, "R U RP UP R U RP", "f2l");
                        }
                        else if (edgeSide == back)
                        {
                            setalgo(back, "FP U F UP FP U F", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(back, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(back, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (cubeMain.at(side).at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                    if (cornerLocMatch)
                    {
                        // for the condition when corner is on the correct location but side edge is not on the top......
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_EDGE_SETTER");
                            if (sentinal == 1)
                            {
                                setalgo(left, "R UP RP UP R U RP UP R U U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(left, "R UP RP U FP UP F UP FP UP F", "f2l");
                            }
                            // IN THIS CASE WE DO NOT NEED TO WORK ON -1 CONDITION CAUSE IN THAT CASE THE BELLOW CODE WILL WORK FINE.....
                        }
                        if (edgeSide == left)
                        {
                            setalgo(left, "FP UP F U FP UP F", "f2l");
                        }
                        else if (edgeSide == face)
                        {
                            setalgo(left, "R UP RP U R UP RP", "f2l");
                        }
                    }
                    else
                    {
                        int temp{};
                        temp = rang0to1(rng);

                        switch (temp)
                        {
                        case 0:
                            setalgo(left, "R U RP", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        case 1:
                            setalgo(left, "FP UP F", "f2l");
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                            break;
                        default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        // -------------------------------------------------- TOP SIDE ---------------------------------------------------------------
        else if (side == top)
        {
            switch (block)
            {
            case 1:
                if (cubeMain.at(side).at(0).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(back, "R U RP UP R U RP UP R U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(back, "R UP RP U FP U F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // this is for the condition when the side elements are not in the correct location....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "U U FP UP F UP FP U F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "U R U U RP U R UP RP", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "UP FP U U F UP FP U F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "U U R U RP U R UP RP", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "FP U U F U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "R U RP U U R U RP UP R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(back, "FP UP F U U FP UP F U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(back, "R U U RP UP R U RP", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 2:
                if (cubeMain.at(side).at(0).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 0, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(right, "R U RP UP R U RP UP R U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(right, "R UP RP U FP U F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // this is for the condition when the side elements are not in the correct location....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "U R U U RP U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "U U FP UP F UP FP U F", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "U U R U RP U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "UP FP U U F UP FP U F", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "R U RP U U R U RP UP R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "FP U U F U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(right, "R U U RP UP R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(right, "FP UP F U U FP UP F U FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 3:
                if (cubeMain.at(side).at(2).at(0) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 0);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(left, "R U RP UP R U RP UP R U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(left, "R UP RP U FP U F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // this is for the condition when the side elements are not in the correct location....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "U R U U RP U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "U U FP UP F UP FP U F", "f2l");
                            }
                        }
                        else if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "U U R U RP U R UP RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "UP FP U U F UP FP U F", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "R U RP U U R U RP UP R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "FP U U F U FP UP F", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(left, "R U U RP UP R U RP", "f2l");
                            }
                            else
                            {
                                setalgo(left, "FP UP F U U FP UP F U FP UP F", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            case 4:
                if (cubeMain.at(side).at(2).at(2) == 'w')
                {
                    cornerLocMatch = cornerColorsFinder(side, 2, 2);
                    boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                    if (cornerLocMatch)
                    {
                        if (!boolEdgeSetter)
                        {
                            sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            if (sentinal == 1)
                            {
                                setalgo(face, "R U RP UP R U RP UP R U RP", "f2l");
                            }
                            else if (sentinal == 0)
                            {
                                setalgo(face, "R UP RP U FP U F", "f2l");
                            }
                            else if (sentinal == -1)
                            {
                                // this is for the condition when the side elements are not in the correct location....
                                cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                                edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            }
                        }
                        if (edgeSide == back)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "U U FP UP F UP FP U F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "U R U U RP U R UP RP", "f2l");
                            }
                        }
                        else if (edgeSide == left)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "UP FP U U F UP FP U F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "U U R U RP U R UP RP", "f2l");
                            }
                        }
                        else if (edgeSide == face)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "FP U U F U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "R U RP U U R U RP UP R U RP", "f2l");
                            }
                        }
                        else if (edgeSide == right)
                        {
                            if (topSideColor == cornerColors.at(0))
                            {
                                setalgo(face, "FP UP F U U FP UP F U FP UP F", "f2l");
                            }
                            else
                            {
                                setalgo(face, "R U U RP UP R U RP", "f2l");
                            }
                        }
                    }
                    else
                    {
                        cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "CALL_F2LHELPER");
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    // optimising f2lsolution....
    solutionOptimizer(F2LSolution);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE OLL LOGIC FUNCTION AND CHECKS IT ON WHICH SIDE THE OLL CONDITIONS WILL MATCHES AND SOLVES THE OLL LAYER.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::OLLSolver()
{
    bool solve{false};
    string OLLcode{};
    OLLcode = OLLCoder();
    for (int i{0}; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            solve = OLLLogic(face, OLLcode);
            if (solve == false)
            {
                U;
            }
            break;
        case 1:
            UP;
            solve = OLLLogic(right, OLLcode);
            if (solve == false)
            {
                U;
                U;
            }
            break;
        case 2:
            U;
            U;
            solve = OLLLogic(back, OLLcode);
            if (solve == false)
            {
                UP;
            }
            break;
        case 3:
            U;
            solve = OLLLogic(left, OLLcode);
            break;
        default:
            break;
        }
        if (solve == true)
        {
            solutionOptimizer(OLLSolution);
            return;
        }
        OLLcode = OLLCoder();
    }
    cout << "error solving Oll layer...." << endl;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION SAVES THE PARTNER SIDE OF THE WHITE CORNER TO THE CORNERCOLORS VECTOR AND CHECKS IF IT IS ON THE RIGHT LOCATION.
   IF IT SI THAN IT RETURNS TRUE ELSE RETURNS FALSE.
      -> PRIORITIES FOR SAVING THE CORNER COLORS ARE -:
        * TOP AND BOTTOM
        * FACE BACK
        * LEFT AND RIGHT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool makeCubie::cornerColorsFinder(const int &side, const int &row, const int &col)
{
    cornerColors.clear();
    vector<int> sideloc;
    if ((side == face && row == 0 && col == 2) ||
        (side == top && row == 2 && col == 2) ||
        (side == right && row == 0 && col == 0))
    {
        sideloc.push_back(face);
        sideloc.push_back(top);
        sideloc.push_back(right);
        if (cubeMain[top].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[top].at(2).at(2));
        ;
        if (cubeMain[face].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[face].at(0).at(2));
        ;
        if (cubeMain[right].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[right].at(0).at(0));
        ;
    }
    else if ((side == face && row == 0 && col == 0) ||
             (side == top && row == 2 && col == 0) ||
             (side == left && row == 0 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (cubeMain[top].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[top].at(2).at(0));
        ;
        if (cubeMain[face].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[face].at(0).at(0));
        ;
        if (cubeMain[left].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[left].at(0).at(2));
        ;
    }
    else if ((side == left && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 0) ||
             (side == back && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(left);
        if (cubeMain[top].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[top].at(0).at(0));
        ;
        if (cubeMain[back].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[back].at(0).at(2));
        ;
        if (cubeMain[left].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[left].at(0).at(0));
        ;
    }
    else if ((side == back && row == 0 && col == 0) ||
             (side == top && row == 0 && col == 2) ||
             (side == right && row == 0 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(top);
        sideloc.push_back(right);
        if (cubeMain[top].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[top].at(0).at(2));
        ;
        if (cubeMain[back].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[back].at(0).at(0));
        ;
        if (cubeMain[right].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[right].at(0).at(2));
        ;
    }
    // bottom corners...
    else if ((side == face && row == 2 && col == 2) ||
             (side == bottom && row == 0 && col == 2) ||
             (side == right && row == 2 && col == 0))
    {
        sideloc.push_back(face);
        sideloc.push_back(bottom);
        sideloc.push_back(right);
        if (cubeMain[bottom].at(0).at(2) != 'w')
            cornerColors.push_back(cubeMain[bottom].at(0).at(2));
        ;
        if (cubeMain[face].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[face].at(2).at(2));
        ;
        if (cubeMain[right].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[right].at(2).at(0));
        ;
    }
    else if ((side == face && row == 2 && col == 0) ||
             (side == bottom && row == 0 && col == 0) ||
             (side == left && row == 2 && col == 2))
    {
        sideloc.push_back(face);
        sideloc.push_back(bottom);
        sideloc.push_back(left);
        if (cubeMain[bottom].at(0).at(0) != 'w')
            cornerColors.push_back(cubeMain[bottom].at(0).at(0));
        ;
        if (cubeMain[face].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[face].at(2).at(0));
        ;
        if (cubeMain[left].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[left].at(2).at(2));
        ;
    }
    else if ((side == left && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 0) ||
             (side == back && row == 2 && col == 2))
    {
        sideloc.push_back(left);
        sideloc.push_back(bottom);
        sideloc.push_back(back);
        if (cubeMain[bottom].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[bottom].at(2).at(0));
        ;
        if (cubeMain[back].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[back].at(2).at(2));
        ;
        if (cubeMain[left].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[left].at(2).at(0));
        ;
    }
    else if ((side == back && row == 2 && col == 0) ||
             (side == bottom && row == 2 && col == 2) ||
             (side == right && row == 2 && col == 2))
    {
        sideloc.push_back(back);
        sideloc.push_back(bottom);
        sideloc.push_back(right);
        if (cubeMain[bottom].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[bottom].at(2).at(2));
        ;
        if (cubeMain[back].at(2).at(0) != 'w')
            cornerColors.push_back(cubeMain[back].at(2).at(0));
        ;
        if (cubeMain[right].at(2).at(2) != 'w')
            cornerColors.push_back(cubeMain[right].at(2).at(2));
        ;
    }
    // the bellow code checks the corner is on the right location or not......
    int x{0};
    for (int i{0}; i < 3; i++)
    {
        if (cubeMain.at(sideloc.at(i)).at(1).at(1) == cornerColors.at(0) || cubeMain.at(sideloc.at(i)).at(1).at(1) == cornerColors.at(1))
            x++;
    }
    if (x == 2)
        return true;
    else
        return false;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CHECKS IF THE SIDE ELEMENT IS ON THE TOP OF THE CUBE IF IT IS IT RERURNS "TRUE" ELSE IT RETURNS "FALSE".
   IF THE EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT MOVES THE SIDE EDGE TO THE CORRECT LOCATION, ELSE LET IT STAY ON THE SAME LOCATION
   AND MAKES TOPSIDECOLOR === "THE COLOR IN THE TOP OF SIDE ELEMENT"
   AND EDGESIDE === "TO THE SIDE OF TEH EDGE ELEMENT ON THE CUBE"
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool makeCubie::edgeSetterOnTop(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter)
{
    if (edgeSetter == "CALL_EDGE_SETTER")
        temp_cube = *this;
    bool pos{false};
    int moveCount{0};
    // the bellow two assignment is for the precaution of removing past assignments....
    edgeSide = -1;
    topSideColor = 'x';
    while (!pos)
    {
        if (temp_cube.cubeMain[face].at(0).at(1) == color_1 && temp_cube.cubeMain[top].at(2).at(1) == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[face].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = face;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top].at(1).at(2) == color_2 && temp_cube.cubeMain[right].at(0).at(1) == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[right].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = right;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top].at(1).at(0) == color_2 && temp_cube.cubeMain[left].at(0).at(1) == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[left].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = left;
            topSideColor = color_2;
        }
        else if (temp_cube.cubeMain[top].at(0).at(1) == color_2 && temp_cube.cubeMain[back].at(0).at(1) == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_1 == temp_cube.cubeMain[back].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = back;
            topSideColor = color_2;
        }
        // if second color is not on the face.....
        else if (temp_cube.cubeMain[face].at(0).at(1) == color_2 && temp_cube.cubeMain[top].at(2).at(1) == color_1)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[face].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = face;
            topSideColor = color_1;
        }
        else if (temp_cube.cubeMain[top].at(1).at(2) == color_1 && temp_cube.cubeMain[right].at(0).at(1) == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[right].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = right;
            topSideColor = color_1;
        }
        else if (temp_cube.cubeMain[top].at(1).at(0) == color_1 && temp_cube.cubeMain[left].at(0).at(1) == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[left].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = left;
            topSideColor = color_1;
        }
        // back side edges
        else if (temp_cube.cubeMain[top].at(0).at(1) == color_1 && temp_cube.cubeMain[back].at(0).at(1) == color_2)
        {
            if (edgeSetter == "CALL_EDGE_SETTER")
            {
                if (color_2 == temp_cube.cubeMain[back].at(1).at(1))
                    pos = true;
                else
                {
                    temp_cube.U;
                    moveCount++;
                }
            }
            edgeSide = back;
            topSideColor = color_1;
        };
        // this block is for stoping the loop from running infinite times...
        if (moveCount == 0)
        {
            pos = true;
        }
    }
    // IF MOVECOUNT IS 3 IT IS GOING TO APPLY U-PRIME ELSE IN OTHER TWO CONDITIONS (2,1) IT IS GOING TO APPLY SIMPLE U OPERATIONS.....
    switch (moveCount)
    {
    case 3:
        this->tempSolution.push_back("UP");
        break;
    case 2:
        this->tempSolution.push_back("U");
        this->tempSolution.push_back("U");
        break;
    case 1:
        this->tempSolution.push_back("U");
        break;
    default:
        break;
    }
    applySolution("f2l");
    if (edgeSide == -1)
    {
        return false;
    }
    return true;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
THIS FUNCTION SIMPLY MOVES THE CORNER ELEMENT TO THE CORRECT LOCATION, IF IT IS ON THE TOP SIDE OF THE CUBE
   AND IF F2LHELPER === "CALL_F2LHELPER" THAN IT WILL CALL THE REQUIRED SIDE OF F2LHELPER FUNCTION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::cornerSetterOnTop(makeCubie &temp_cube, const char &color_2, const char &color_3, string_view F2LHelper)
{
    temp_cube = *this;
    vector<char> colors{color_2, color_3};
    int colorCount{0}, moveCount{0}, side{-1}, colorBlock{-1};
    bool pos{false};
    while (!pos)
    {
        colorCount = 0;
        //--------------------- ifs for TOP , FACE AND RIGHT ANGLED CORNER ---------------------
        if (temp_cube.cubeMain[top].at(2).at(2) == 'w' && temp_cube.cubeMain[face].at(0).at(2) == color_2 && temp_cube.cubeMain[right].at(0).at(0) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 4;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(2) == color_3 && temp_cube.cubeMain[face].at(0).at(2) == 'w' && temp_cube.cubeMain[right].at(0).at(0) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(2) == color_2 && temp_cube.cubeMain[face].at(0).at(2) == color_3 && temp_cube.cubeMain[right].at(0).at(0) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(2) == color_3 && temp_cube.cubeMain[face].at(0).at(2) == color_2 && temp_cube.cubeMain[right].at(0).at(0) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(2) == 'w' && temp_cube.cubeMain[face].at(0).at(2) == color_3 && temp_cube.cubeMain[right].at(0).at(0) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 4;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(2) == color_2 && temp_cube.cubeMain[face].at(0).at(2) == 'w' && temp_cube.cubeMain[right].at(0).at(0) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , BACK AND RIGHT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top].at(0).at(2) == 'w' && temp_cube.cubeMain[back].at(0).at(0) == color_2 && temp_cube.cubeMain[right].at(0).at(2) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(2) == color_3 && temp_cube.cubeMain[back].at(0).at(0) == 'w' && temp_cube.cubeMain[right].at(0).at(2) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(2) == color_2 && temp_cube.cubeMain[back].at(0).at(0) == color_3 && temp_cube.cubeMain[right].at(0).at(2) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(2) == color_3 && temp_cube.cubeMain[back].at(0).at(0) == color_2 && temp_cube.cubeMain[right].at(0).at(2) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = right;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(2) == 'w' && temp_cube.cubeMain[back].at(0).at(0) == color_3 && temp_cube.cubeMain[right].at(0).at(2) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(2) == color_2 && temp_cube.cubeMain[back].at(0).at(0) == 'w' && temp_cube.cubeMain[right].at(0).at(2) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[right].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , BACK AND LEFT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top].at(0).at(0) == 'w' && temp_cube.cubeMain[back].at(0).at(2) == color_2 && temp_cube.cubeMain[left].at(0).at(0) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(0) == color_3 && temp_cube.cubeMain[back].at(0).at(2) == 'w' && temp_cube.cubeMain[left].at(0).at(0) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(0) == color_2 && temp_cube.cubeMain[back].at(0).at(2) == color_3 && temp_cube.cubeMain[left].at(0).at(0) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(0) == color_3 && temp_cube.cubeMain[back].at(0).at(2) == color_2 && temp_cube.cubeMain[left].at(0).at(0) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(0) == 'w' && temp_cube.cubeMain[back].at(0).at(2) == color_3 && temp_cube.cubeMain[left].at(0).at(0) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(0).at(0) == color_2 && temp_cube.cubeMain[back].at(0).at(2) == 'w' && temp_cube.cubeMain[left].at(0).at(0) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[back].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = back;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        //--------------------- ifs for TOP , FACE AND LEFT ANGLED CORNER ----------------------
        else if (temp_cube.cubeMain[top].at(2).at(0) == 'w' && temp_cube.cubeMain[face].at(0).at(0) == color_2 && temp_cube.cubeMain[left].at(0).at(2) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 3;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(0) == color_3 && temp_cube.cubeMain[face].at(0).at(0) == 'w' && temp_cube.cubeMain[left].at(0).at(2) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(0) == color_2 && temp_cube.cubeMain[face].at(0).at(0) == color_3 && temp_cube.cubeMain[left].at(0).at(2) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(0) == color_3 && temp_cube.cubeMain[face].at(0).at(0) == color_2 && temp_cube.cubeMain[left].at(0).at(2) == 'w')
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = left;
                    colorBlock = 2;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(0) == 'w' && temp_cube.cubeMain[face].at(0).at(0) == color_3 && temp_cube.cubeMain[left].at(0).at(2) == color_2)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = top;
                    colorBlock = 3;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        else if (temp_cube.cubeMain[top].at(2).at(0) == color_2 && temp_cube.cubeMain[face].at(0).at(0) == 'w' && temp_cube.cubeMain[left].at(0).at(2) == color_3)
        {
            for (int i{0}; i < 2; i++)
            {
                if (temp_cube.cubeMain[face].at(1).at(1) == colors.at(i) || temp_cube.cubeMain[left].at(1).at(1) == colors.at(i))
                    colorCount++;
            }
            if (colorCount == 2)
            {
                pos = true;
                if (F2LHelper == "CALL_F2LHELPER")
                {
                    side = face;
                    colorBlock = 1;
                }
            }
            else
            {
                temp_cube.U;
                moveCount++;
            }
        }
        if (moveCount == 0)
        {
            pos = true;
        }
    }

    switch (moveCount)
    {
    case 3:
        this->tempSolution.push_back("UP");
        break;
    case 2:
        this->tempSolution.push_back("U");
        this->tempSolution.push_back("U");
        break;
    case 1:
        this->tempSolution.push_back("U");
        break;
    default:
        break;
    }
    applySolution("f2l");
    f2LHelper(temp_cube, side, colorBlock);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHECKS FOR THE EDGE ELEMENTS IN THE MID LAYER OF THE CUBE.
   AND IF THE EDGE IN ON THE CORRECT LOCATION THAN IT RETURNS "1"
   ELSE IF THE EDGE IN ON THE CORRECT LOCATION BUT IN REVER DIRECTION THAN IT RETURN "0"
   ELSE IF EDGE IS IN NEAR LOCATION THAN IT WILL RETURN "-1" AND WILL MOVE THE EDGE OUT OF THE MID LAYER.
   AND IF EDGESETTER IS === "CALL_EDGE_SETTER" THAN IT WILL CALL THE EDGESETTER_ON_TOP FUNCTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
int makeCubie::sideEdgeFinder(makeCubie &temp_cube, const char &color_1, const char &color_2, string_view edgeSetter)
{
    // temp_cube = *this;
    // FRONT SIDE-EDGES
    if (cubeMain[face].at(1).at(2) == color_1 && cubeMain[right].at(1).at(0) == color_2)
    {
        if (color_1 == cubeMain[face].at(1).at(1) && color_2 == cubeMain[right].at(1).at(1))
        {
            return 1;
        }
        else if (color_2 == cubeMain[face].at(1).at(1) && color_1 == cubeMain[right].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) || color_2 == cubeMain[face].at(1).at(1))
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == cubeMain[right].at(1).at(1) || color_2 == cubeMain[right].at(1).at(1))
        {
            tempSolution.push_back("FP");
            tempSolution.push_back("UP");
            tempSolution.push_back("F");
        }
        else
        {
            tempSolution.push_back("R");
            tempSolution.push_back("UP");
            tempSolution.push_back("RP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face].at(1).at(2) == color_2 && cubeMain[right].at(1).at(0) == color_1)
    {
        if (color_2 == cubeMain[face].at(1).at(1) && color_1 == cubeMain[right].at(1).at(1))
        {
            return 1;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) && color_2 == cubeMain[right].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) || color_2 == cubeMain[face].at(1).at(1))
        {
            tempSolution.push_back("R");
            tempSolution.push_back("U");
            tempSolution.push_back("RP");
        }
        else if (color_1 == cubeMain[right].at(1).at(1) || color_2 == cubeMain[right].at(1).at(1))
        {
            tempSolution.push_back("FP");
            tempSolution.push_back("UP");
            tempSolution.push_back("F");
        }
        else
        {
            tempSolution.push_back("R");
            tempSolution.push_back("UP");
            tempSolution.push_back("RP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face].at(1).at(0) == color_1 && cubeMain[left].at(1).at(2) == color_2)
    {
        if (color_1 == cubeMain[face].at(1).at(1) && color_2 == cubeMain[left].at(1).at(1))
        {
            return 1;
        }
        else if (color_2 == cubeMain[face].at(1).at(1) && color_1 == cubeMain[left].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) || color_2 == cubeMain[face].at(1).at(1))
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == cubeMain[left].at(1).at(1) || color_2 == cubeMain[left].at(1).at(1))
        {
            tempSolution.push_back("F");
            tempSolution.push_back("U");
            tempSolution.push_back("FP");
        }
        else
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("U");
            tempSolution.push_back("L");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[face].at(1).at(0) == color_2 && cubeMain[left].at(1).at(2) == color_1)
    {
        if (color_2 == cubeMain[face].at(1).at(1) && color_1 == cubeMain[left].at(1).at(1))
        {
            return 1;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) && color_2 == cubeMain[left].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[face].at(1).at(1) || color_2 == cubeMain[face].at(1).at(1))
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("UP");
            tempSolution.push_back("L");
        }
        else if (color_1 == cubeMain[left].at(1).at(1) || color_2 == cubeMain[left].at(1).at(1))
        {
            tempSolution.push_back("F");
            tempSolution.push_back("U");
            tempSolution.push_back("FP");
        }
        else
        {
            tempSolution.push_back("LP");
            tempSolution.push_back("U");
            tempSolution.push_back("L");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    // BACK SIDE-EDGES
    else if (cubeMain[right].at(1).at(2) == color_1 && cubeMain[back].at(1).at(0) == color_2)
    {
        if (color_1 == cubeMain[right].at(1).at(1) && color_2 == cubeMain[back].at(1).at(1))
        {
            return 1;
        }
        else if (color_2 == cubeMain[right].at(1).at(1) && color_1 == cubeMain[back].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[right].at(1).at(1) || color_2 == cubeMain[right].at(1).at(1))
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == cubeMain[back].at(1).at(1) || color_2 == cubeMain[back].at(1).at(1))
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("UP");
            tempSolution.push_back("R");
        }
        else
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("U");
            tempSolution.push_back("R");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[right].at(1).at(2) == color_2 && cubeMain[back].at(1).at(0) == color_1)
    {
        if (color_2 == cubeMain[right].at(1).at(1) && color_1 == cubeMain[back].at(1).at(1))
        {
            return 1;
        }
        else if (color_1 == cubeMain[right].at(1).at(1) && color_2 == cubeMain[back].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[right].at(1).at(1) || color_2 == cubeMain[right].at(1).at(1))
        {
            tempSolution.push_back("B");
            tempSolution.push_back("U");
            tempSolution.push_back("BP");
        }
        else if (color_1 == cubeMain[back].at(1).at(1) || color_2 == cubeMain[back].at(1).at(1))
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("UP");
            tempSolution.push_back("R");
        }
        else
        {
            tempSolution.push_back("RP");
            tempSolution.push_back("U");
            tempSolution.push_back("R");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[left].at(1).at(0) == color_1 && cubeMain[back].at(1).at(2) == color_2)
    {
        if (color_1 == cubeMain[left].at(1).at(1) && color_2 == cubeMain[back].at(1).at(1))
        {
            return 1;
        }
        else if (color_2 == cubeMain[left].at(1).at(1) && color_1 == cubeMain[back].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[left].at(1).at(1) || color_2 == cubeMain[left].at(1).at(1))
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == cubeMain[back].at(1).at(1) || color_2 == cubeMain[back].at(1).at(1))
        {
            tempSolution.push_back("L");
            tempSolution.push_back("U");
            tempSolution.push_back("LP");
        }
        else
        {
            tempSolution.push_back("L");
            tempSolution.push_back("UP");
            tempSolution.push_back("LP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    else if (cubeMain[left].at(1).at(0) == color_2 && cubeMain[back].at(1).at(2) == color_1)
    {
        if (color_2 == cubeMain[left].at(1).at(1) && color_1 == cubeMain[back].at(1).at(1))
        {
            return 1;
        }
        else if (color_1 == cubeMain[left].at(1).at(1) && color_2 == cubeMain[back].at(1).at(1))
        {
            return 0;
        }
        else if (color_1 == cubeMain[left].at(1).at(1) || color_2 == cubeMain[left].at(1).at(1))
        {
            tempSolution.push_back("BP");
            tempSolution.push_back("U");
            tempSolution.push_back("B");
        }
        else if (color_1 == cubeMain[back].at(1).at(1) || color_2 == cubeMain[back].at(1).at(1))
        {
            tempSolution.push_back("L");
            tempSolution.push_back("U");
            tempSolution.push_back("LP");
        }
        else
        {
            tempSolution.push_back("L");
            tempSolution.push_back("UP");
            tempSolution.push_back("LP");
        }
        applySolution("f2l");
        if (edgeSetter == "CALL_EDGE_SETTER")
            edgeSetterOnTop(temp_cube, color_1, color_2, edgeSetter);
        return -1;
    }
    return -1;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON EXECUTES THE ELGORITHEMS OF F2L_LAYER ON THE BASIS OF THE SIDE AND COLORBLOCK VALUE PROVIDED
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::f2LHelper(makeCubie &temp_cube, const int &side, const int &colorBlock)
{
    temp_cube = *this;
    int sentinal;
    bool cornerLocMatch{false}, boolEdgeSetter{false};

    // -------------------------------------------------- FACE SIDE ---------------------------------------------------------------
    if (side == face)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain.at(side).at(0).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(left, "U FP U F U FP U U F", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(left, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R UP RP U U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP U U F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U FP UP F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP U U F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain.at(side).at(0).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(face, "UP R UP RP UP R U U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(face, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U F U U R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R U U RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP R U U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(face, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- RIGHT SIDE ---------------------------------------------------------------
    else if (side == right)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain.at(side).at(0).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(face, "U FP U F U FP U U F", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(face, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "R UP RP U U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP U U F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U FP UP F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U FP U U F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain.at(side).at(0).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(right, "UP R UP RP UP R U U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(right, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "FP U F U U R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R U U RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "UP R U U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- BACK SIDE ---------------------------------------------------------------
    else if (side == back)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain.at(side).at(0).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(right, "U FP U F U FP U U F", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(right, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R UP RP U U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP U U F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U FP UP F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U FP U U F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain.at(side).at(0).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(back, "UP R UP RP UP R U U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(back, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U F U U R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R U U RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP R U U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(back, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- LEFT SIDE ---------------------------------------------------------------
    else if (side == left)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain.at(side).at(0).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(back, "U FP U F U FP U U F", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(back, "U FP UP F UP R U RP", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "R UP RP U U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R UP RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP U U F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U FP UP F U FP U U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "UP R U RP U R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "F RP FP R", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U FP U U F UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain.at(side).at(0).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    // for the condition when corner is on the correct location but side edge is not on the top......
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(left, "UP R UP RP UP R U U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(left, "UP R U RP U FP UP F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // the corner setter will set the corner and will pass the control back to this function.....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "FP U F U U R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP U F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP R U U RP U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U FP UP F UP FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "UP R U U RP UP R U U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    // -------------------------------------------------- TOP SIDE ---------------------------------------------------------------
    else if (side == top)
    {
        switch (colorBlock)
        {
        case 1:
            if (cubeMain.at(side).at(0).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(back, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(back, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "U U FP UP F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U R U U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "UP FP U U F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "U U R U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP U U F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U RP U U R U RP UP R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(back, "FP UP F U U FP UP F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(back, "R U U RP UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        case 2:
            if (cubeMain.at(side).at(0).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 0, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(right, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(right, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U R U U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "U U FP UP F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "U U R U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "UP FP U U F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U RP U U R U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP U U F U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(right, "R U U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(right, "FP UP F U U FP UP F U FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        case 3:
            if (cubeMain.at(side).at(2).at(0) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 2, 0);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(left, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(left, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U R U U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "U U FP UP F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "U U R U RP U R UP RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "UP FP U U F UP FP U F", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U RP U U R U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP U U F U FP UP F", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(left, "R U U RP UP R U RP", "f2l");
                        }
                        else
                        {
                            setalgo(left, "FP UP F U U FP UP F U FP UP F", "f2l");
                        }
                    }
                }
            }
            break;
        case 4:
            if (cubeMain.at(side).at(2).at(2) == 'w')
            {
                cornerLocMatch = cornerColorsFinder(side, 2, 2);
                boolEdgeSetter = edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                if (cornerLocMatch)
                {
                    if (!boolEdgeSetter)
                    {
                        sentinal = sideEdgeFinder(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        if (sentinal == 1)
                        {
                            setalgo(face, "R U RP UP R U RP UP R U RP", "f2l");
                        }
                        else if (sentinal == 0)
                        {
                            setalgo(face, "R UP RP U FP U F", "f2l");
                        }
                        else if (sentinal == -1)
                        {
                            // this is for the condition when the side elements are not in the correct location....
                            cornerSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                            edgeSetterOnTop(temp_cube, cornerColors.at(0), cornerColors.at(1), "DO_NOT_CALL");
                        }
                    }
                    if (edgeSide == back)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "U U FP UP F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U R U U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == left)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "UP FP U U F UP FP U F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "U U R U RP U R UP RP", "f2l");
                        }
                    }
                    else if (edgeSide == face)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP U U F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U RP U U R U RP UP R U RP", "f2l");
                        }
                    }
                    else if (edgeSide == right)
                    {
                        if (topSideColor == cornerColors.at(0))
                        {
                            setalgo(face, "FP UP F U U FP UP F U FP UP F", "f2l");
                        }
                        else
                        {
                            setalgo(face, "R U U RP UP R U RP", "f2l");
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCITON CHANGES THE CUBE_SOLVING_ALGORITHEMS TO THE REQUIRED IMPLEMENTAION SIDE ON THE BASIS OF SIDE PROVIDED.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::setalgo(const int &side, string str_algo, string_view applySolutionOn)
{
    string move{};
    if (side == right)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'M')
                str_algo[i] = 'S';
            else if (str_algo[i] == 'S')
            {
                // S will become MP
                if (str_algo[i + 1] != 'P')
                {
                    str_algo.erase(i, 1);
                    str_algo.insert(i, "MP");
                }
                else
                {
                    // SP will become M
                    str_algo[i] = 'M';
                    str_algo.erase(i + 1, 1);
                }
            }
            // but E will remain E...
        }
    }
    else if (side == back)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'M')
            {
                // M will become MP
                if (str_algo[i + 1] != 'P')
                {
                    str_algo.insert(i + 1, 1, 'P');
                }
                else
                {
                    // MP will become M
                    str_algo.erase(i + 1, 1);
                }
            }
            else if (str_algo[i] == 'S')
            {
                // S will become SP
                if (str_algo[i + 1] != 'P')
                {
                    str_algo.insert(i + 1, 1, 'P');
                }
                else
                {
                    // SP will become S
                    str_algo.erase(i + 1, 1);
                }
            }
        }
    }
    else if (side == left)
    {
        for (size_t i{0}; i < str_algo.length(); i++)
        {
            if (str_algo[i] == 'F')
                str_algo[i] = 'L';
            else if (str_algo[i] == 'L')
                str_algo[i] = 'B';
            else if (str_algo[i] == 'R')
                str_algo[i] = 'F';
            else if (str_algo[i] == 'B')
                str_algo[i] = 'R';
            else if (str_algo[i] == 'S')
            {
                // M will become SP
                if (str_algo[i + 1] != 'P')
                {
                    str_algo.erase(i, 1);
                    str_algo.insert(i, "SP");
                }
                else
                {
                    // MP will become S
                    str_algo[i] = 'S';
                    str_algo.erase(i + 1, 1);
                }
            }
            else if (str_algo[i] == 'S')
                str_algo[i] = 'M';
        }
    };
    // this loop extracts the operations from the string (str_algo) and pushbacks it to the arr_algo vector....
    for (size_t i{0}; i < str_algo.length(); i++)
    {
        if (str_algo[i] != ' ')
        {
            move += str_algo[i];
        }
        else if (str_algo[i] == ' ')
        {
            tempSolution.push_back(move);
            move.clear();
        }
    }
    tempSolution.push_back(move);
    // this loop applies the operations stored in the arr_algo vector and pushback the opereation to the slution vector....
    // for (size_t i{0}; i < arr_algo.size(); i++)
    // {
    //     if (arr_algo.at(i) == "F")
    //     {
    //         tempSolution.push_back("F");
    //     }
    //     else if (arr_algo.at(i) == "L")
    //     {
    //         tempSolution.push_back("L");
    //     }
    //     else if (arr_algo.at(i) == "R")
    //     {
    //         tempSolution.push_back("R");
    //     }
    //     else if (arr_algo.at(i) == "U")
    //     {
    //         tempSolution.push_back("U");
    //     }
    //     else if (arr_algo.at(i) == "D")
    //     {
    //         tempSolution.push_back("D");
    //     }
    //     else if (arr_algo.at(i) == "B")
    //     {
    //         tempSolution.push_back("B");
    //     }
    //     else if (arr_algo.at(i) == "FP")
    //     {
    //         tempSolution.push_back("FP");
    //     }
    //     else if (arr_algo.at(i) == "LP")
    //     {
    //         tempSolution.push_back("LP");
    //     }
    //     else if (arr_algo.at(i) == "RP")
    //     {
    //         tempSolution.push_back("RP");
    //     }
    //     else if (arr_algo.at(i) == "UP")
    //     {
    //         tempSolution.push_back("UP");
    //     }
    //     else if (arr_algo.at(i) == "DP")
    //     {
    //         tempSolution.push_back("DP");
    //     }
    //     else if (arr_algo.at(i) == "BP")
    //     {
    //         tempSolution.push_back("BP");
    //     }
    //     else if (arr_algo.at(i) == "M")
    //     {
    //         tempSolution.push_back("M");
    //     }
    //     else if (arr_algo.at(i) == "S")
    //     {
    //         tempSolution.push_back("S");
    //     }
    //     else if (arr_algo.at(i) == "E")
    //     {
    //         tempSolution.push_back("E");
    //     }
    //     else if (arr_algo.at(i) == "MP")
    //     {
    //         tempSolution.push_back("MP");
    //     }
    //     else if (arr_algo.at(i) == "SP")
    //     {
    //         tempSolution.push_back("SP");
    //     }
    //     else if (arr_algo.at(i) == "EP")
    //     {
    //         tempSolution.push_back("EP");
    //     }
    // }
    applySolution(applySolutionOn);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CALLS THE F2LSOLVER ON TEMPRORY CUBE UNTIL IT FINDES THE SHORTEST POSSIBLE F2L SOLUTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::shortestF2LSolver()
{
    unsigned int trials{0};
    bool solve{false};
    makeCubie solveF2L(*this);
    makeCubie temp_cube(*this);
    while (!solve)
    {
        ++trials;
        cout << "\r " << trials << " tried....";
        solveF2L = temp_cube = *this;
        solveF2L.f2lSolver(temp_cube);
        if (trials < 1500)
        {
            if (solveF2L.F2LSolution.size() > 26)
            {
                solveF2L.F2LSolution.clear();
                continue;
            }
        }
        else if (trials < 3000)
        {
            if (solveF2L.F2LSolution.size() > 29)
            {
                solveF2L.F2LSolution.clear();
                continue;
            }
        }
        else if (trials < 5000)
        {
            if (solveF2L.F2LSolution.size() > 32)
            {
                solveF2L.F2LSolution.clear();
                continue;
            }
        }
        else
        {
            if (solveF2L.F2LSolution.size() > 35)
            {
                solveF2L.F2LSolution.clear();
                continue;
            }
        }
        solve = true;
    }
    *this = solveF2L;
    this->F2LSolution = solveF2L.F2LSolution;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION CODES THE OLL LAYER IN '1' AND '0' CHARACTER.
   THE VERY FIRST 9 CHARACTERS ARE FOR TOP SIDE
   THE OTHER THREE FOR FIRST ROW OF FACE AND
   THE OTHER THREE FOR FIRST ROW OF RIGHT AND
   THE OTHER THREE FOR FIRST ROW OF BACK AND
   THE LAST THREE CHARACHTER IS FOR FIRST ROW OF LEFT
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string makeCubie::OLLCoder()
{
    string OLLCode{};
    // CODING TOP SIDE OF THE CUBE.....
    for (auto vecOfvec : cubeMain[top])
        for (auto vecOfchar : vecOfvec)
            if (vecOfchar == 'y')
                OLLCode += '1';
            else
                OLLCode += '0';
    // CODING FIRST ROW OF FACE SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[face].at(0))
        if (vecOfchar == 'y')
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF RIGHT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[right].at(0))
        if (vecOfchar == 'y')
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF BACK SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[back].at(0))
        if (vecOfchar == 'y')
            OLLCode += '1';
        else
            OLLCode += '0';
    // CODING FIRST ROW OF LEFT SIDE OF THE CUBE.....
    for (auto vecOfchar : cubeMain[left].at(0))
        if (vecOfchar == 'y')
            OLLCode += '1';
        else
            OLLCode += '0';
    // RETURNING THE FULLY CODED STRING.....
    return OLLCode;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION HAVE SOLUTION FOR ALL THE CONDITIONS POSSIBLE IN OLL
   LAYER AND IT DIRECTLY CALLS THE SETALGO TO APPLY THE CONDITION.
   IT RETURNS TRUE IF THE CONDITION MATCHES THE CODE AND FALSE WHEN OLLCODE DOSEN'T MATCHES ANY CONDITION
   ----------------------------------------------------------------------------------------------------------------------------------------*/
bool makeCubie::OLLLogic(const int &side, string_view OLLcode)
{
    // DOT CONDITIONS...
    if (OLLcode == "000010000010111010111")
    {
        setalgo(side, "R U BP R B R R UP RP F R FP", "oll");
    }
    else if (OLLcode == "000010000111011010110")
    {
        setalgo(side, "RP F R FP U U RP F R F F U U F", "oll");
    }
    else if (OLLcode == "000010001010011011011")
    {
        setalgo(side, "B U L UP LP BP U B L U LP UP BP", "oll");
    }
    else if (OLLcode == "001010000110110010110")
    {
        setalgo(side, "RP U U RP F R FP UP FP UP F UP R", "oll");
    }
    else if (OLLcode == "100010001010010110011")
    {
        setalgo(side, "R U RP U RP F R FP U U RP F R FP", "oll");
    }
    else if (OLLcode == "101010101010010010010")
    {
        setalgo(side, "MP U U M U U MP U M U U MP U U M", "oll");
    }
    else if (OLLcode == "101010000010110010011")
    {
        setalgo(side, "RP U U F R U RP UP F F U U F R", "oll");
    }
    else if (OLLcode == "000010101010010111010")
    {
        setalgo(side, "F R U RP U FP U U FP L F LP", "oll");
    }
    // LINE CONDITIONS...
    else if (OLLcode == "010010010100111001010")
    {
        setalgo(side, "RP UP FP U FP L F LP F R", "oll");
    }
    else if (OLLcode == "010010010000111000111")
    {
        setalgo(side, "R UP B B D BP U U B DP B B U RP", "oll");
    }
    else if (OLLcode == "000111000110101011000")
    {
        setalgo(side, "F U R UP RP U R UP RP FP", "oll");
    }
    else if (OLLcode == "000111000010101010101")
    {
        setalgo(side, "LP BP L UP RP U R UP RP U R LP B L", "oll");
    }
    // CROSS CONDITION....
    else if (OLLcode == "010111010100101001000")
    {
        setalgo(side, "L UP RP U LP U R U RP U R", "oll");
    }
    else if (OLLcode == "010111010000101000101")
    {
        setalgo(side, "R U RP U R UP RP U R U U RP", "oll");
    }
    else if (OLLcode == "010111011100000100100")
    {
        setalgo(side, "LP U R UP L U RP", "oll");
    }
    else if (OLLcode == "010111011000001001001")
    {
        setalgo(side, "RP U U R U RP U R", "oll");
    }
    else if (OLLcode == "110111110001000100000")
    {
        setalgo(side, "RP FP L F R FP LP F", "oll");
    }
    else if (OLLcode == "111111010101000000000")
    {
        setalgo(side, "R R D RP U U R DP RP U U RP", "oll");
    }
    else if (OLLcode == "110111011000000100001")
    {
        setalgo(side, "RP FP LP F R FP L F", "oll");
    }
    // 4 CORNERS....
    else if (OLLcode == "101110111000010010000")
    {
        setalgo(side, "MP UP M U U MP UP M", "oll");
    }
    else if (OLLcode == "101111101010000010000")
    {
        setalgo(side, "LP R U RP UP L RP F R FP", "oll");
    }
    // SHAPE _| .......
    else if (OLLcode == "010110100011011001000")
    {
        setalgo(side, "L F RP F R F F LP", "oll");
    }
    else if (OLLcode == "110110001110011000000")
    {
        setalgo(side, "F RP FP R U R UP RP", "oll");
    }
    else if (OLLcode == "010110001110010100100")
    {
        setalgo(side, "RP UP R F RP FP U F R FP", "oll");
    }
    else if (OLLcode == "010110101010010101000")
    {
        setalgo(side, "UP R U U RP UP R UP R R FP UP F U R", "oll");
    }
    else if (OLLcode == "010110000011010100101")
    {
        setalgo(side, "F R U RP UP R U RP UP FP", "oll");
    }
    else if (OLLcode == "010110000111010101000")
    {
        setalgo(side, "L FP LP F U U L L B L BP L", "oll");
    }
    // SHAPE \_ .....
    else if (OLLcode == "010011101010000101010")
    {
        setalgo(side, "UP RP U U R U RP U R R B U BP UP RP", "oll");
    }
    else if (OLLcode == "011011000110100000110")
    {
        setalgo(side, "L F F RP FP R FP LP", "oll");
    }
    else if (OLLcode == "010011000110101001010")
    {
        setalgo(side, "FP LP UP L U LP UP L U F", "oll");
    }
    else if (OLLcode == "011011100010100001010")
    {
        setalgo(side, "RP U U R R BP RP B RP U U R", "oll");
    }
    else if (OLLcode == "010011000111000101010")
    {
        setalgo(side, "RP F R FP U U R R BP RP B RP", "oll");
    }
    else if (OLLcode == "010011000011000100111")
    {
        setalgo(side, "RP F RP FP R R U U BP R B RP", "oll");
    }
    // SHAPE -\ .....
    else if (OLLcode == "001110010001010011001")
    {
        setalgo(side, "R U RP BP R B UP BP RP B", "oll");
    }
    else if (OLLcode == "100110010100110110000")
    {
        setalgo(side, "LP BP L UP RP U R LP B L", "oll");
    }
    else if (OLLcode == "000110011100010110100")
    {
        setalgo(side, "M LP UP L UP LP U U L UP MP", "oll");
    }
    else if (OLLcode == "101110010000110010001")
    {
        setalgo(side, "BP R BP R R U R U RP UP R B B", "oll");
    }
    // SHAPE \- ....
    else if (OLLcode == "000011010001000110111")
    {
        setalgo(side, "LP B L L FP L L BP L L F LP", "oll");
    }
    else if (OLLcode == "000011110001001011010")
    {
        setalgo(side, "M R U RP U R U U RP U MP", "oll");
    }
    else if (OLLcode == "000011011000001011011")
    {
        setalgo(side, "LP B B R B RP B L", "oll");
    }
    else if (OLLcode == "101011010000100010011")
    {
        setalgo(side, "R R U RP BP R UP R R U R B RP", "oll");
    }
    // SHAPE C ....
    else if (OLLcode == "110010110000111000010")
    {
        setalgo(side, "R U R BP RP B UP RP", "oll");
    }
    else if (OLLcode == "000111101010001010100")
    {
        setalgo(side, "R U RP UP BP RP F R FP B", "oll");
    }
    // SHAPE L ....
    else if (OLLcode == "000111001110000110100")
    {
        setalgo(side, "RP F R U RP FP R F UP FP", "oll");
    }
    else if (OLLcode == "000111100011001011000")
    {
        setalgo(side, "L FP LP UP L F LP FP U F", "oll");
    }
    else if (OLLcode == "000111001010001011001")
    {
        setalgo(side, "LP BP L RP UP R U LP B L", "oll");
    }
    else if (OLLcode == "000111100010100110100")
    {
        setalgo(side, "R B RP L U LP UP R BP RP", "oll");
    }
    // SHAPE P .....
    else if (OLLcode == "110110100010111000000")
    {
        setalgo(side, "F U R UP RP FP", "oll");
    }
    else if (OLLcode == "011011001110000001010")
    {
        setalgo(side, "RP UP F U R UP RP FP R", "oll");
    }
    else if (OLLcode == "110110100011010100000")
    {
        setalgo(side, "L U FP UP LP U L F LP", "oll");
    }
    else if (OLLcode == "011011001010000000111")
    {
        setalgo(side, "FP UP LP U L F", "oll");
    }
    // SHAPE T .....
    else if (OLLcode == "001111001010000010101")
    {
        setalgo(side, "F R U RP UP FP", "oll");
    }
    else if (OLLcode == "001111001110000011000")
    {
        setalgo(side, "R U RP UP RP F R FP", "oll");
    }
    // SHAPE W ....
    else if (OLLcode == "001011110001000010110")
    {
        setalgo(side, "L U LP U L UP LP UP LP B L BP", "oll");
    }
    else if (OLLcode == "100110011100011010000")
    {
        setalgo(side, "RP UP R UP RP U R U R BP RP B", "oll");
    }
    // SHAPE Z ....
    else if (OLLcode == "100111001010000110001")
    {
        setalgo(side, "RP F R U RP UP FP U R", "oll");
    }
    else if (OLLcode == "001111100010100011000")
    {
        setalgo(side, "L FP LP UP L U F UP LP", "oll");
    }
    else
        return false;
    return true;
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION APPLIES TEMPSOLUTION TO THE CUBE AND SAVES THE ALGORITHM TO THE F2LSOLUTION
   AND THEN CLEARS THE TEMPSOLUTION.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void makeCubie::applySolution(string_view applySolutionOn)
{
    for (size_t i{0}; i < tempSolution.size(); i++)
    {
        if (tempSolution.at(i) == "F")
            F;
        else if (tempSolution.at(i) == "L")
            L;
        else if (tempSolution.at(i) == "R")
            R;
        else if (tempSolution.at(i) == "U")
            U;
        else if (tempSolution.at(i) == "D")
            D;
        else if (tempSolution.at(i) == "B")
            B;
        else if (tempSolution.at(i) == "FP")
            FP;
        else if (tempSolution.at(i) == "LP")
            LP;
        else if (tempSolution.at(i) == "RP")
            RP;
        else if (tempSolution.at(i) == "UP")
            UP;
        else if (tempSolution.at(i) == "DP")
            DP;
        else if (tempSolution.at(i) == "BP")
            BP;
        else if (tempSolution.at(i) == "M")
            M;
        else if (tempSolution.at(i) == "S")
            S;
        else if (tempSolution.at(i) == "E")
            E;
        else if (tempSolution.at(i) == "MP")
            MP;
        else if (tempSolution.at(i) == "SP")
            SP;
        else if (tempSolution.at(i) == "EP")
            EP;
    }
    if (applySolutionOn == "f2l")
        for (size_t i{0}; i < tempSolution.size(); i++)
        {
            F2LSolution.push_back(tempSolution.at(i));
        }
    else if (applySolutionOn == "oll")
        for (size_t i{0}; i < tempSolution.size(); i++)
        {
            OLLSolution.push_back(tempSolution.at(i));
        }
    else if (applySolutionOn == "pll")
        for (size_t i{0}; i < tempSolution.size(); i++)
        {
            PLLSolution.push_back(tempSolution.at(i));
        }
    tempSolution.clear();
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THSI FUNCITON IS ONLY USED BY THE CUBE_SETTER TO PROVIDE COLOR NAME STRING IN EXCHANGE OF INTEGER VALUE OF THE COLOR
   ----------------------------------------------------------------------------------------------------------------------------------------*/
string sideColor(const int &colorAsci)
{
    switch (colorAsci)
    {
    case 0:
        return "BLUE";
        break;
    case 1:
        return "GREEN";
        break;
    case 2:
        return "ORANGE";
        break;
    case 3:
        return "RED";
        break;
    case 4:
        return "YELLOW";
        break;
    case 5:
        return "WHITE";
        break;
    default:
        return "ERROR FINDING COLOR NAME...";
        break;
    }
}
/* ----------------------------------------------------------------------------------------------------------------------------------------
   THIS FUNCTION OPTIMIZES THE SOLUTION VECTOR PASSED INTO IT AND MAKES IS SHORTER AND SWEET.
   ----------------------------------------------------------------------------------------------------------------------------------------*/
void solutionOptimizer(vector<std::string> &solution)
{
    int checks{1};
    for (int times{0}; times < 4; times++)
    {
        if (checks == 0)
            break;
        checks = 0;
        for (size_t i{0}, j{1}; i < (solution.size() - 1) && solution.size() > 2; i++, j++)
        {
            if (solution.at(i) == solution.at(j))
            {
                // for the condition when we have 2u and 2u .....
                if (solution.at(i).at(0) == '2')
                {
                    solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                    checks++;
                }
                else
                {
                    solution.at(i) = '2' + solution.at(i);
                    // poping the "p" from step....
                    if (solution.at(i).size() == 3)
                    {
                        solution.at(i).pop_back();
                    }
                    // removing j element....
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
            else if (solution.at(i).size() == 2 && solution.at(j).size() == 1)
            {
                // for the condition when we have up and u so we cancel both....
                if (solution.at(i).at(0) == solution.at(j).at(0))
                {
                    solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                    checks++;
                }
                // ex: 2U + U = UP
                else if (solution.at(i).at(1) == solution.at(j).at(0))
                {
                    solution.at(i) = solution.at(j) + 'P';
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
            else if (solution.at(i).size() == 1 && solution.at(j).size() == 2)
            {
                // for the condition when we have U and UP so we cancel both....
                if (solution.at(i).at(0) == solution.at(j).at(0))
                {
                    solution.erase(solution.begin() + i, solution.begin() + (j + 1));
                    checks++;
                }
                // ex: U + 2U = UP
                else if (solution.at(j).at(1) == solution.at(i).at(0))
                {
                    solution.at(i) = solution.at(i) + 'P';
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
            else if (solution.at(i).size() == solution.at(j).size() && solution.at(i).size() == 2)
            {
                if (solution.at(i).at(1) == solution.at(j).at(0))
                {
                    // ex: 2U + UP = U
                    solution.at(i) = solution.at(j).at(0);
                    solution.erase(solution.begin() + j);
                    checks++;
                }
                else if (solution.at(i).at(0) == solution.at(j).at(1))
                {
                    // ex: UP + 2U = U
                    solution.at(i) = solution.at(i).at(0);
                    solution.erase(solution.begin() + j);
                    checks++;
                }
            }
        }
    }
}
