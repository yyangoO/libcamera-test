/**
 * @file                    utils.h
 * @author                  yyang yyangoO@outlook.com & sjtu_yangyang@sjtu.edu.cn
 * @version                 1.0.0
 * @date                    5-APR-2022
 * @section                 description
 *                          utils of project
 * @section                 logs
 * <table>
 * <tr><th>date             <th>version     <th>author      <th>description     </tr>
 * <tr><td>2022.04.5        <td>1.0.0       <td>yyang       <td>initial version </tr>
 * </tr>
 */


#ifndef _UTILS_H
#define _UTILS_H


#include <string>
#include <iostream>


/**
 * @brief color string
 * This function colors a string in terminal.
 * @param str       the origin string
 * @param color     the color
 * @param bold      is bold or not
 * @param underline is underline or not
 */
std::string colored_str(std::string str, std::string color = "black", bool bold = false, bool underline = false)
{
    std::string ret = "";

    if (color == "black")
    {
        ret += "\033[30m";
    }
    else if (color == "red")
    {
        ret += "\033[31m";
    }
    else if (color == "green")
    {
        ret += "\033[32m";
    }
    else if (color == "yellow")
    {
        ret += "\033[33m";
    }
    else if (color == "blue")
    {
        ret += "\033[34m";
    }
    else if (color == "magents")
    {
        ret += "\033[35m";
    }
    else if (color == "cyan")
    {
        ret += "\033[36m";
    }
    else if (color == "white")
    {
        ret += "\033[37m";
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