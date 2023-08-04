
#pragma once

#include <iostream>
#include <string>
#include "miscellaneous.h"
#include "colors.h"
using namespace std;

// Print title named "RUBIX CUBE SOLVER"..
void printTitle()
{
    std::string title = R"(
----------------------------------------------------------------
`-  ____          _      _          ____          _           `-
`- |  _ \        | |    (_) _  _   /  _ \        | |          `-
`- | |_) | _   _ | |__   _ \ \/ / |  / \_| _   _ | |__   ___  `-
`- | ___/ | | | ||  _ \ | | \  /  |  |    | | | ||  _ \ / _ \ `-
`- | |\ \ | \_/ || |_) || | /  \  |  \_/-|| \_/ || |_) || __/ `-
`- |_| \_\ \___/ |____/ |_|/_/\_\  \____/  \___/ |____/ \___| `-
`-   ____          _                                          `-
`-  / ___|        | |                                         `-
`- | (___    ___  | |   _   _  ___  _ __                      `-
`-  \___ \  / _ \ | |  \ \ / // _ \| '__|                     `-
`-  ____) |( (_) )| |__ \ - / | __/| |                        `-
`- |_____/  \___/ |____| \_/  \___||_|                        `-
`-------------------------------------------------------------`- 
    )";
    std::cout << B_GREEN << BOLD << title << std::endl;
    std::cout << "\033[0m"; // Set text color back to default
}

// Print Banner ...
void printBanner(const std::string &name)
{
    std::string banner = "-----------------------------------------------------------------\n"
                         "        WELCOME TO RUBIK'S CUBE SOLVER BY " B_WHITE ITALIC +
                         name + DEFAULT "      \n"
                                        "-----------------------------------------------------------------\n";
    std::cout << banner << std::endl;
}