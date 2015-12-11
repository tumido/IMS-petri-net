/**
 * @file debug.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Debug messages for debug purposes
 */
#ifndef __STATS_HPP__
#define __STATS_HPP__

#define COLUMN_LENGHT 30

#include <iostream>
#include <sstream>

namespace Stats {
    inline void PrintRow() {
        std::cout  << " |\n";
    }

    template <typename H, typename... T>
    inline void PrintRow(H p, T... t) {
        std::ostringstream s;
        s << "| "<< p;
        std::string str = s.str();
        str.resize(COLUMN_LENGHT, ' ');
        std::cout << str;
        PrintRow(t...);
    }

    template <typename H, typename... T>
    inline void PrintHeader(H p, T... t) {
        std::cout << '\n';
        PrintRow(p, t...);
        for (unsigned int i=0; i < COLUMN_LENGHT * 4; i++)
            std::cout << "-";
        std::cout  << "\n";
    }
}

#endif // __STATS_HPP__
