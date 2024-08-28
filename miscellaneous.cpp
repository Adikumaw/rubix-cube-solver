#include "miscellaneous.h"
#include "colors.h"

using namespace std;

// Function to clear a given number of lines from the output
void clearLines(int numLines)
{
    for (int i = 0; i < numLines; i++)
    {
        std::cout << "\x1b[2K"; // Clear current line
        if (i != numLines - 1)
        {
            std::cout << "\x1b[1A"; // Move cursor up one line
        }
    }
}
// Sets font color of passed text to given color named string
void set_font_color(string_view text, string_view color)
{
    if (color == "black")
    {
        cout << BLACK << text << DEFAULT;
    }
    else if (color == "red")
    {
        cout << RED << text << DEFAULT;
    }
    else if (color == "green")
    {
        cout << GREEN << text << DEFAULT;
    }
    else if (color == "yellow")
    {
        cout << YELLOW << text << DEFAULT;
    }
    else if (color == "blue")
    {
        cout << BLUE << text << DEFAULT;
    }
    else if (color == "magenta")
    {
        cout << MAGENTA << text << DEFAULT;
    }
    else if (color == "cyan")
    {
        cout << CYAN << text << DEFAULT;
    }
    else if (color == "white")
    {
        cout << WHITE << text << DEFAULT;
    }
    else if (color == "b_black")
    {
        cout << B_BLACK << text << DEFAULT;
    }
    else if (color == "b_red")
    {
        cout << B_RED << text << DEFAULT;
    }
    else if (color == "b_green")
    {
        cout << B_GREEN << text << DEFAULT;
    }
    else if (color == "b_yellow")
    {
        cout << B_YELLOW << text << DEFAULT;
    }
    else if (color == "b_blue")
    {
        cout << B_BLUE << text << DEFAULT;
    }
    else if (color == "b_magenta")
    {
        cout << B_MAGENTA << text << DEFAULT;
    }
    else if (color == "b_cyan")
    {
        cout << B_CYAN << text << DEFAULT;
    }
    else if (color == "b_white")
    {
        cout << B_WHITE << text << DEFAULT;
    }
}
// Sets fonts backgroud color of passed text to given color named string
void set_bg_clr(string_view ch, string_view bg_color)
{
    if (bg_color == "black")
    {
        cout << BG_BLACK << ch << ch << DEFAULT;
    }
    else if (bg_color == "red")
    {
        cout << BG_RED << ch << ch << DEFAULT;
    }
    else if (bg_color == "green")
    {
        cout << BG_GREEN << ch << ch << DEFAULT;
    }
    else if (bg_color == "yellow")
    {
        cout << BG_YELLOW << ch << ch << DEFAULT;
    }
    else if (bg_color == "blue")
    {
        cout << BG_BLUE << ch << ch << DEFAULT;
    }
    else if (bg_color == "magenta")
    {
        cout << BG_MAGENTA << ch << ch << DEFAULT;
    }
    else if (bg_color == "cyan")
    {
        cout << BG_CYAN << ch << ch << DEFAULT;
    }
    else if (bg_color == "white")
    {
        cout << BG_WHITE << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_black")
    {
        cout << BG_B_BLACK << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_red")
    {
        cout << BG_B_RED << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_green")
    {
        cout << BG_B_GREEN << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_yellow")
    {
        cout << BG_B_YELLOW << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_blue")
    {
        cout << BG_B_BLUE << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_magenta")
    {
        cout << BG_B_MAGENTA << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_cyan")
    {
        cout << BG_B_CYAN << ch << ch << DEFAULT;
    }
    else if (bg_color == "b_white")
    {
        cout << BG_B_WHITE << ch << ch << DEFAULT;
    }
    else
    {
        cout << "**";
    }
}
// converts character to their representative color name as string
std::string ch_to_clr(const char &ch)
{
    switch (ch)
    {
    case 'b':
        return "blue";
        break;
    case 'r':
        return "red";
        break;
    case 'g':
        return "green";
        break;
    case 'y':
        return "b_yellow";
        break;
    case 'p':
        return "b_magenta";
        break;
    case 'w':
        return "white";
        break;
    case 'o':
        return "b_magenta";
        break;

    default:
        return "no color matched";
        break;
    }
}
