#pragma once


#include "token.hpp"
#include "token_stream.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>


class Calculator
{
public:
    Calculator();

    double calculate(std::string str);

private:
    std::istringstream iss;
    Token_stream       ts;

    Token  get_token();

    double expression();
    double term();
    double primary();

    void error(std::string str);
};

