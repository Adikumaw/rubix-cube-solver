#ifndef _MISCE_H_
#define _MISCE_H_
#pragma once

#include <string>
#include <iostream>
#include <string_view>
using namespace std;

// Function to clear a given number of lines from the output
void clearLines(int numLines);
// Sets font color of passed text to given color named string
void set_font_color(string_view text, string_view color);
// Sets fonts backgroud color of passed text to given color named string
void set_bg_clr(string_view ch, string_view bg_color);
// converts character to their representative color name as string
std::string ch_to_clr(const char &ch);

#endif //_MISCE_H_