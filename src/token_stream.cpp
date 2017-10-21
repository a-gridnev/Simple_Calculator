#include "token_stream.hpp"

Token_stream::Token_stream(std::istream& _iss): iss(_iss)
{}

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;
    full   = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    if(!iss.rdbuf()->in_avail())
    {
        return Token('e');
    }

    char ch;
    iss >> ch;

    switch(ch)
    {
        case '(':
        case ')':
        case '-':
        case '+':
        case '*':
        case '/':
            return Token(ch);

        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            {
                iss.putback(ch);
                double val;
                iss >> val;
                return Token('d',val);
            }

        default:
            {
                iss.putback(ch);
                std::string s;
                iss >> s;
                error("некорректный ввод, строка содержит недопустимое выражение  " + s);
            }
    }
}

void Token_stream::clear_buffer()
{
    full = false;
}

void Token_stream::error(std::string str)
{
    throw std::runtime_error(str);
}