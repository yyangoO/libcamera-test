#ifndef _UTILS_H
#define _UTILS_H


#include <string>
#include <iostream>


std::string color_str(std::string str, std::string color = "black", bool bold = false, bool underline = false)
{
    std::string ret = "";

    switch (color)
    {
        case "black":
            ret += "\033[30m";
            break;
        case "red":
            ret += "\033[31m";
            break;
        case "green":
            ret += "\033[32m";
            break;
        case "yellow":
            ret += "\033[33m";
            break;
        case "blue":
            ret += "\033[34m";
            break;
        case "magents":
            ret += "\033[35m";
            break;
        case "cyan":
            ret += "\033[36m";
            break;
        case "white":
            ret += "\033[37m";
            break;
    }
    if (bold)
    {
        ret += "\033[1m";
    }
    if (underline)
    {
        ret += "\033[4m";
    }
    ret += str;
    ret += "\033[0m";

    return ret;
}


#endif // _UTILS_H