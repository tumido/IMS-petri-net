/**
 * @file debug.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Debug messages for debug purposes
 */
#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#ifdef DEBUG
#define debug(caller, msg) { std::cout << "[" << (caller) << "]\t" << (msg) << std::endl;}
#else
#define debug(caller, msg)
#endif

#endif // __DEBUG_HPP__
