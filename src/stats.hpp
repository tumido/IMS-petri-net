/**
 * @file debug.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Debug messages for debug purposes
 */
#ifndef __STATS_HPP__
#define __STATS_HPP__

#define FIRST_COLUMN 40
#define COLUMN_LENGHT 15

#include <iostream>
#include <sstream>
#include <iomanip>

namespace Stats {
    inline unsigned int _PrintRow(int count) {
        std::cout  << "|\n";
        return ++count;
    }

    template <typename H, typename... T>
    inline unsigned int _PrintRow(int count, H p, T... t) {
        std::ostringstream s;
        if (std::is_same<H, double>::value)
            s << "| " << std::fixed << std::setprecision(5) << p;
        else
            s << "| "<< p;
        std::string str = s.str();
        str.resize(COLUMN_LENGHT, ' ');
        std::cout << str;
        return _PrintRow(++count, t...);
    }

    template <typename H, typename... T>
    inline unsigned int PrintRow(H p, T... t) {
        std::ostringstream s;
        s << "| "<< p;
        std::string str = s.str();
        str.resize(FIRST_COLUMN, ' ');
        std::cout << str;
        return _PrintRow(0, t...);
    }

    template <typename H, typename... T>
    inline void PrintHeader(H p, T... t) {
        std::cout << '\n';
        unsigned int cols = PrintRow(p, t...);
        // compute the separator length
        unsigned int sep_length = FIRST_COLUMN + (COLUMN_LENGHT* (cols-1)) + 1;
        for (unsigned int i=0; i < sep_length; i++)
            std::cout << "-";
        std::cout  << "\n";
    }
}

#endif // __STATS_HPP__
