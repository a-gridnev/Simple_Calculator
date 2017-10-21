#include "token.hpp"

Token::Token()
{

}

Token::Token(char k)
{
    kind = k;
}

Token::Token(char k, double v)
{
    kind = k;
    value = v;
}