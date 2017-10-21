#include "calculator.hpp"

Calculator::Calculator():ts(iss)
{}

double Calculator::calculate(std::string str)
{
    std::replace(str.begin(),str.end(),',','.');

    iss.clear();
    iss.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    iss.seekg(0);

    ts.clear_buffer();

    iss.str(str);

    return round(expression()*100.0)/100.0;
}

double Calculator::expression()
{
    double left = term();

    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
            case '+':
                left += term();
                t = ts.get();
                break;

            case '-':
                left -= term();
                t = ts.get();
                break;

            default:
                ts.putback(t);
                return left;
        }
    }
}

double Calculator::term()
{
    double left = primary();

    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;

            case '/':
            {
                double d = primary();
                if(d == 0)
                {
                    error("некорректный ввод, деление на ноль");
                }
                left /= d;
                t = ts.get();
                break;
            }

            default:
                ts.putback(t);
                return left;
        }
    }
}


double Calculator::primary()
{
    Token t = ts.get();

    int sign {1};

    switch(t.kind)
    {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
            {
                error("некорректный ввод, ошибка в расстановке скобок в выражении (отсутствует знак ')')");
            }
            return d;
        }

        case ')':
            error("некорректный ввод, ошибка в расстановке скобок в выражении (отсутствует знак '(')");

        case '-':
            t = ts.get();
            sign = -1;

        case 'd':
            return t.value * sign;

        default:
            error("некорректный ввод, в выражении пропущен операнд");
    }
}

void Calculator::error(std::string str)
{
    throw std::runtime_error(str);
}
