/**
 * @file token.hpp
 * @author Albert Uchytil
 * @brief Data structure for Tokens
 */
#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "component.hpp"
#include "place.hpp"

class Token : public Component {
private:
public:
  Place *Location = NULL;
};

#endif // __TOKEN_HPP__
