#include "calculator.hpp"

#include <iostream>
#include <stdexcept>


int main(int argc, char** argv)
{
    Calculator calc;

    // Если входное выражение передается программе через аргументы командной строки:
    // вычисляем выражение, выводим результат в консоль, завершаем работу программы. 
    if (argc >= 2)
    {
        try
        {
            std::cout << calc.calculate(argv[1]);
        }

        catch(std::runtime_error&  e)
        {
            std::cerr << "runtime  error :  " << e.what() << std::endl;
            return  1;
        }        
    }

    // Иначе программа переходит в интерактивный режим:
    // Программа ожидает ввода выражения, вычисляет его,
    // выводит результат в консоль и ожидает следующего ввода.
    // Для завершения работы программы, на вход следует подать
    // символ 'q'
    else
    {
        std::string str;

        while(true)
        {
            std::getline(std::cin, str);

            if(str.length() == 1 && str[0] == 'q') break;

            try
            {
                std::cout << calc.calculate(str) << std::endl;
            }

            catch(std::runtime_error&  e)
            {
                std::cout << e.what() << std::endl;

                std::cout.clear();

                std::cout << std::endl;
            } 
        }
    }

    return 0;
}
