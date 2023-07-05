#pragma once
#include "BigInt.h"

int main()
{
    BigInt number_first("1233639496673963964563639636394673");
    BigInt number_second("321334856252390534023643697396736");
    bool flag = number_first < number_second;
    cout << "Тест 1 '<' ожидается 0 = " << flag << '\n';

    number_first = BigInt("-12312312312312312312335207602360");
    number_second = BigInt("12312312312312312312335207602360");
    flag = number_second < number_first;
    cout << "Тест 2 '<' ожидается 0 = " << flag << '\n';

    number_first = BigInt("-10010000000000000000000000000000000000");
    number_second = BigInt("-11000000000000000001000000000000000000");
    flag = number_second > number_first;
    cout << "Тест 3 '>' ожидается 0 = " << flag << '\n';

    number_first = BigInt("-1");
    number_second = BigInt("0");
    flag = number_second > number_first;
    cout << "Тест 4 '>' ожидается 1 = " << flag << '\n';

    number_first = BigInt("10000000000000000001000000000000000000");
    number_second = BigInt("11000000000000000001000000000000000000");
    flag = number_second > number_first;
    cout << "Тест 5 '>' ожидается 1 = " << flag << '\n';

    number_first = BigInt("10000000000000000001000000000000000000");
    number_second = BigInt("11000000000000000001000000000000000000");
    BigInt test_ans = number_first + number_second;
    cout << "Тест 6 '+' ожидается 21000000000000000002000000000000000000 = " << test_ans << '\n';

    number_first = BigInt("-10000100000000000001000000000000000000");
    number_second = BigInt("32131200000000000001000000000000000000");
    test_ans = number_first + number_second;
    cout << "Тест 7 '+' ожидается 22131100000000000000000000000000000000 = " << test_ans << '\n';

    number_first = BigInt("123456990000000000001000000000000000000");
    number_second = BigInt("-32131200000000000001000000000000000000");
    test_ans = number_first + number_second;
    cout << "Тест 8 '+' ожидается 91325790000000000000000000000000000000 = " << test_ans << '\n';

    number_first = BigInt("123456990000000000001000000000000000000");
    number_second = BigInt("-32131200000000000001000000000000000000");
    test_ans = number_first * number_second;
    cout << "Тест 9 '*' ожидается -3966821237088000000155588190000000000001000000000000000000000000000000000000 = " << test_ans << '\n';

    number_first = BigInt("123456990000000000001000000000000000000");
    number_second = BigInt("0");
    test_ans = number_first * number_second;
    cout << "Тест 10 '*' ожидается 0 = " << test_ans << '\n';

    number_first = BigInt("1111111111111111111111111111111111111111111111111111111111111");
    number_second = BigInt("99999999999999999999999999999999991111111111111111111111119999999999999999999999");
    test_ans = number_first * number_second;
    cout << "Тест 11 '*' ожидается 111111111111111111111111111111111101234567901234567901234577766666666666666666665555555555555556543209876543209876543208888888888888888888889 = " << test_ans << endl;

    number_second = BigInt("0");
    ++number_second;
    test_ans = number_second;
    cout << "Тест 12 '++number' ожидается 1 = " << test_ans << '\n';

    number_second = BigInt("0");
    number_second++;
    test_ans = number_second;
    cout << "Тест 13 'number++' ожидается 1 = " << test_ans << '\n';

    number_second = BigInt("0");
    --number_second;
    test_ans = number_second;
    cout << "Тест 14 '--number' ожидается -1 = " << test_ans << '\n';

    number_second = BigInt("0");
    number_second--;
    test_ans = number_second;
    cout << "Тест 15 'number--' ожидается -1 = " << test_ans << '\n';


    BigInt testInt("123123123123123123123123123123123");
    BigInt testInt2("12312312312312312312312312312312311111");
    bool ans = testInt != testInt2;
    cout << "Тест 16 '!=' ожидается 1 = " << ans << '\n';

    testInt = BigInt("123123123123123123123123123123123");
    testInt2 = BigInt("123123123123123123123123123123123");
    ans = testInt == testInt2;
    cout << "Тест 17 '==' ожидается 1 = " << ans << '\n';

    testInt = BigInt("123123123123123123123123123123123");
    testInt2 = BigInt("123123123123123123123123123123124");
    ans = testInt >= testInt2;
    cout << "Тест 18 '>=' ожидается 0 = " << ans << '\n';

    testInt = BigInt("123123123123123123123123123123123");
    testInt2 = BigInt("123123123123123123123123123123124");
    ans = testInt <= testInt2;
    cout << "Тест 19 '<=' ожидается 1 = " << ans << '\n';

    testInt = BigInt("123123123123123123123123123123123");
    testInt2 = BigInt("123123123123123123123123123123124");
    BigInt ansTestInt = testInt - testInt2;
    cout << "Тест 20 '-' ожидается -1 = " << ansTestInt << '\n';

    testInt = BigInt("-3");
    testInt2 = BigInt("100");
    ansTestInt = testInt2 / testInt;
    cout << "Тест 21 '/' ожидается 2780747285213848753531 = " << ansTestInt << '\n';

    testInt = BigInt("10");
    testInt2 = BigInt("-99");
    ansTestInt = testInt2 % testInt;
    cout << "Тест 22 '%' ожидается 426032 = " << ansTestInt << '\n';

    BigInt cinInteger;
    cout << "Введите число типа BigInt = ";
    cin >> cinInteger;
    cout << " Тест 23 '<<' && '>>' ваше введенное число типа BigInt это = " << cinInteger << '\n';

    return 0;
}