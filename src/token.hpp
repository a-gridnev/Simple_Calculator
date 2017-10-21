#pragma once


class Token
{
public:
    Token();
    Token(char k);
    Token(char k, double v);

    char kind;
    double value;
};