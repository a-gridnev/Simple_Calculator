#define CATCH_CONFIG_MAIN
#include "../ext/catch.hpp"

#include "../src/calculator.hpp"

Calculator calc;


TEST_CASE( "Calculator", "[calc]" )
{
    CHECK       (calc.calculate("-1 + 5 - 3")                                    == Approx(1));
    CHECK       (calc.calculate("-10 + (8 * 2.5) - (3 / 1,5)")                   == Approx(8));
    CHECK       (calc.calculate("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)")   == Approx(11));
    CHECK_THROWS(calc.calculate("1.1 + 2.1 + abc")                               == Approx(2.2));


    CHECK_THROWS(calc.calculate("")       == 0);

    CHECK_THROWS(calc.calculate("-a")     == 1);

    CHECK       (calc.calculate("7")      == Approx(7));
    CHECK       (calc.calculate("-7")     == Approx(-7));

    CHECK       (calc.calculate(".7")     == Approx(0.7));
    CHECK       (calc.calculate("7.")     == Approx(7.0));
    CHECK       (calc.calculate("7.7198") == Approx(7.72));
    CHECK       (calc.calculate("-7,7")   == Approx(-7.7));
    
    CHECK       (calc.calculate("1 +2*3   -  4 + -5   / 6")         == Approx(2.17));

    CHECK       (calc.calculate("1.12 + 2. - 3.123456 * -.4")       == Approx(4.37));

    CHECK       (calc.calculate("(1 +2)*((3   -  4) + -5   / 6)")   == Approx(-5.5));

    // пропущен операнд в начале выражения
    CHECK_THROWS(calc.calculate("* 1.6")  == Approx(1.6));
    // пропущен операнд в конце выражения
    CHECK_THROWS(calc.calculate("1 +2*3   -  4 + -5   / 6 *")       == Approx(2.17));
    // пропущен операнд в середине выражения
    CHECK_THROWS (calc.calculate("1 +2*3  +*  4 + -5   / 6")        == Approx(2.17));

    // лишняя открывающая скобка
    CHECK_THROWS(calc.calculate("(1 +2)*((3   -  4) + (-5   / 6)")  == Approx(-5.5));
    // лишняя закрывающая скобка
    CHECK_THROWS(calc.calculate("(1 +2)*)(3   -  4) + (-5   / 6)") == Approx(-5.5));

// Программа работает некорректно в следующих случаях:
    // пропущен оператор
    CHECK (calc.calculate("1 +2*3      4 + -5   / 6")        == Approx(2.17));
}
