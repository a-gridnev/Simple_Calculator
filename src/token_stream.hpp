#pragma once


#include "token.hpp"

#include <sstream>
#include <string>


class Token_stream
{
public:
    Token_stream(std::istream&);

    Token get();
    void  putback(Token t);

    void clear_buffer();

private:
    bool  full{false};
    Token buffer;

    std::istream& iss;

    void error(std::string str);
};