
#pragma once

#include <iostream>
#include <string>
#include "miscellaneous.h"
#include "colors.h"
using namespace std;

// Print title named "RUBIX CUBE SOLVER"..
void printTitle()
{
    std::string titleANSISHADOW = R"(
-------------------------------------------------------------------------
██████╗ ██╗   ██╗██████╗ ██╗██╗  ██╗     ██████╗██╗   ██╗██████╗ ███████╗
██╔══██╗██║   ██║██╔══██╗██║╚██╗██╔╝    ██╔════╝██║   ██║██╔══██╗██╔════╝
██████╔╝██║   ██║██████╔╝██║ ╚███╔╝     ██║     ██║   ██║██████╔╝█████╗
██╔══██╗██║   ██║██╔══██╗██║ ██╔██╗     ██║     ██║   ██║██╔══██╗██╔══╝
██║  ██║╚██████╔╝██████╔╝██║██╔╝ ██╗    ╚██████╗╚██████╔╝██████╔╝███████╗
╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝╚═╝  ╚═╝     ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝

███████╗ ██████╗ ██╗    ██╗   ██╗███████╗██████╗
██╔════╝██╔═══██╗██║    ██║   ██║██╔════╝██╔══██╗
███████╗██║   ██║██║    ██║   ██║█████╗  ██████╔╝
╚════██║██║   ██║██║    ╚██╗ ██╔╝██╔══╝  ██╔══██╗
███████║╚██████╔╝███████╗╚████╔╝ ███████╗██║  ██║
╚══════╝ ╚═════╝ ╚══════╝ ╚═══╝  ╚══════╝╚═╝  ╚═╝
-------------------------------------------------------------------------
        )";
    std::string titleBANNER3D = R"(
-----------------------------------------------------------------------------------------------
'########::'##::::'##:'########::'####:'##::::'##:::::'######::'##::::'##:'########::'########:
 ##.... ##: ##:::: ##: ##.... ##:. ##::. ##::'##:::::'##... ##: ##:::: ##: ##.... ##: ##.....::
 ##:::: ##: ##:::: ##: ##:::: ##:: ##:::. ##'##:::::: ##:::..:: ##:::: ##: ##:::: ##: ##:::::::
 ########:: ##:::: ##: ########::: ##::::. ###::::::: ##::::::: ##:::: ##: ########:: ######:::
 ##.. ##::: ##:::: ##: ##.... ##:: ##:::: ## ##:::::: ##::::::: ##:::: ##: ##.... ##: ##...::::
 ##::. ##:: ##:::: ##: ##:::: ##:: ##::: ##:. ##::::: ##::: ##: ##:::: ##: ##:::: ##: ##:::::::
 ##:::. ##:. #######:: ########::'####: ##:::. ##::::. ######::. #######:: ########:: ########:
..:::::..:::.......:::........:::....::..:::::..::::::......::::.......:::........:::........::
:'######:::'#######::'##:::::::'##::::'##:'########:'########:::::::::::::::::::::::::::::::::: 
'##... ##:'##.... ##: ##::::::: ##:::: ##: ##.....:: ##.... ##:::::::::::::::::::::::::::::::::
 ##:::..:: ##:::: ##: ##::::::: ##:::: ##: ##::::::: ##:::: ##:::::::::::::::::::::::::::::::::
. ######:: ##:::: ##: ##::::::: ##:::: ##: ######::: ########::::::::::::::::::::::::::::::::::
:..... ##: ##:::: ##: ##:::::::. ##:: ##:: ##...:::: ##.. ##:::::::::::::::::::::::::::::::::::
'##::: ##: ##:::: ##: ##::::::::. ## ##::: ##::::::: ##::. ##::::::::::::::::::::::::::::::::::
. ######::. #######:: ########:::. ###:::: ########: ##:::. ##:::::::::::::::::::::::::::::::::
:......::::.......:::........:::::...:::::........::..:::::..::::::::::::::::::::::::::::::::::
`----------------------------------------------------------------------------------------------
    )";
    std::string titlePOISON = R"(
--------------------------------------------------------------------------------------
@@@@@@@   @@@  @@@  @@@@@@@   @@@  @@@  @@@      @@@@@@@  @@@  @@@  @@@@@@@   @@@@@@@@  
@@@@@@@@  @@@  @@@  @@@@@@@@  @@@  @@@  @@@     @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@  
@@!  @@@  @@!  @@@  @@!  @@@  @@!  @@!  !@@     !@@       @@!  @@@  @@!  @@@  @@!       
!@!  @!@  !@!  @!@  !@   @!@  !@!  !@!  @!!     !@!       !@!  @!@  !@   @!@  !@!       
@!@!!@!   @!@  !@!  @!@!@!@   !!@   !@@!@!      !@!       @!@  !@!  @!@!@!@   @!!!:!    
!!@!@!    !@!  !!!  !!!@!!!!  !!!    @!!!       !!!       !@!  !!!  !!!@!!!!  !!!!!:    
!!: :!!   !!:  !!!  !!:  !!!  !!:   !: :!!      :!!       !!:  !!!  !!:  !!!  !!:       
:!:  !:!  :!:  !:!  :!:  !:!  :!:  :!:  !:!     :!:       :!:  !:!  :!:  !:!  :!:       
::   :::  ::::: ::   :: ::::   ::   ::  :::      ::: :::  ::::: ::   :: ::::   :: ::::  
 :   : :   : :  :   :: : ::   :     :   ::       :: :: :   : :  :   :: : ::   : :: ::   
                                                                                        
 @@@@@@    @@@@@@   @@@       @@@  @@@  @@@@@@@@  @@@@@@@                               
@@@@@@@   @@@@@@@@  @@@       @@@  @@@  @@@@@@@@  @@@@@@@@                              
!@@       @@!  @@@  @@!       @@!  @@@  @@!       @@!  @@@                              
!@!       !@!  @!@  !@!       !@!  @!@  !@!       !@!  @!@                              
!!@@!!    @!@  !@!  @!!       @!@  !@!  @!!!:!    @!@!!@!                               
 !!@!!!   !@!  !!!  !!!       !@!  !!!  !!!!!:    !!@!@!                                
     !:!  !!:  !!!  !!:       :!:  !!:  !!:       !!: :!!                               
    !:!   :!:  !:!   :!:       ::!!:!   :!:       :!:  !:!                              
:::: ::   ::::: ::   :: ::::    ::::     :: ::::  ::   :::                              
:: : :     : :  :   : :: : :     :      : :: ::    :   : :                              
--------------------------------------------------------------------------------------
    )";
    std::string titleBOXED = R"(
-------------------------------------------------------------------------------------------------
 ______     __  __     ______     __     __  __        ______     __  __     ______     ______    
/\  == \   /\ \/\ \   /\  == \   /\ \   /\_\_\_\      /\  ___\   /\ \/\ \   /\  == \   /\  ___\   
\ \  __<   \ \ \_\ \  \ \  __<   \ \ \  \/_/\_\/_     \ \ \____  \ \ \_\ \  \ \  __<   \ \  __\   
 \ \_\ \_\  \ \_____\  \ \_____\  \ \_\   /\_\/\_\     \ \_____\  \ \_____\  \ \_____\  \ \_____\ 
  \/_/ /_/   \/_____/   \/_____/   \/_/   \/_/\/_/      \/_____/   \/_____/   \/_____/   \/_____/ 
                                                                                                  
 ______     ______     __         __   __   ______     ______                                     
/\  ___\   /\  __ \   /\ \       /\ \ / /  /\  ___\   /\  == \                                    
\ \___  \  \ \ \/\ \  \ \ \____  \ \ \'/   \ \  __\   \ \  __<                                    
 \/\_____\  \ \_____\  \ \_____\  \ \__|    \ \_____\  \ \_\ \_\                                  
  \/_____/   \/_____/   \/_____/   \/_/      \/_____/   \/_/ /_/                                  

--------------------------------------------------------------------------------------------------
    )";
    std::cout << B_GREEN << BOLD << titleANSISHADOW << std::endl;
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