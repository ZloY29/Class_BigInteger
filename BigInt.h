#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <sstream>

using namespace std;

class BigInt
{
private:

    short pos_minus_numb = 1;
    string value;
    bool is_minus;

public:

    // конструктор по умолчанию
    BigInt() {
        this->value = "0";
        this->is_minus = false;
    }

    // конструктор из числа
    BigInt(int value) {
        // проверка отрицательное ли число
        if (value < 0) {
            this->is_minus = true;
        }
        else {
            this->is_minus = false;
        }
        // установка значения числа в виде строки
        this->value = to_string(this->is_minus ? -value : value);
    }

    // ф-ция удаления ведущих нулей
    void clear_lead_zeroes() {
        int position = 0;
        while (this->value[position] == '0' && value.size() - position > 1) {
            position++;
        }
        // очистили ведущие нули
        this->value = this->value.substr(position);
    }

    // конструктор из строки
    BigInt(const string &value) {
        if (value.size() == 0) {
            this->value = "0";
            this->is_minus = false;
            return;
        }
        this->is_minus = value[0] == '-';
        this->value = value.substr(this->is_minus);
        this->clear_lead_zeroes();
        erase(this->value, '\0');
    }

    // сеттеры-геттеры
    void set_value(string s) {
        value = s;
    }
    void set_is_minus(bool flag) {
        is_minus = flag;
    }
    string get_value() const {
        return value;
    }
    bool get_is_minus() const {
        return is_minus;
    }

    // конструктор копирования
    BigInt(const BigInt &other) {
        this->value = other.value;
        this->is_minus = other.is_minus;
    }

    string toString() const
    {
        string ans = this->is_minus ? "-" + this->value : this->value;
        return ans;
    }

    // оператор сравнения ==
    const bool operator == (const BigInt& other) const {
        if ((this->value == other.get_value()) && (this->is_minus == other.get_is_minus())) {
            return true;
        }
        else {
            return false;
        }
    }

    // оператор сравнения !=
    const bool operator != (const BigInt& other) const {
        return !(*this == other);
    }

    // оператор сравнения <
    const bool operator < (const BigInt& other) const {
        // значение второго числа
        string value2 = other.get_value();
        // длина первого числа
        size_t len1 = value.length();
        // длина второго числа
        size_t len2 = value2.length();
        // если знаки одинаковые, то проверяем значения
        if (is_minus == other.get_is_minus()) {
            if (len1 != len2) {
                if (this->is_minus) {
                    if (len1 < len2) {
                        return false;
                    }
                    else {
                        return true;
                    }
                }
                else {
                    if (len1 < len2) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
            size_t i = 0;
            // ищем разряд, в котором значения отличаются
            while (i < len1 && value[i] == value2[i])
                i++;
            // если разряд найден, то меньше число с меньшей цифрой для положительных и с большей цифрой для отрицательных, иначе числа равны
            if (i < len1) {
                if (this->is_minus) {
                    return value[i] > value2[i];
                }
                else {
                    return value[i] < value2[i];
                }
            }
            else {
                return false;
            }
        }
        // знаки разные, если число отрицательное, то оно меньше, если положительное, то больше
        return is_minus;
    }

    // оператор сравнения >
    const bool operator > (const BigInt& other) const {
        return !(*this < other || *this == other);
    }

    // оператор сравнения <=
    const bool operator <= (const BigInt& other) const {
        return *this < other || *this == other;
    }

    // оператор сравнения >=
    const bool operator >= (const BigInt& other) const {
        return *this > other || *this == other;
    }

    // оператор присвоения
    BigInt operator = (const BigInt& other) {
        this->value = other.value;
        this->is_minus = other.is_minus;
        return *this;
    }

    // унарный минус, если было отрицательным, возвращаем положительное, иначе отрицательное
    BigInt operator - () const&& {
        string copy = this->is_minus ? this->value : string("-") + this->value;
        BigInt curr(copy);
        return curr;
    }

    // постфиксная запись инкремента
    BigInt operator++(int) {
        BigInt res = *this;
        *this = *this + BigInt(1);
        return res;
    }

    // префиксная запись инкремента
    BigInt operator++() {
        return *this = *this + 1;
    }

    // постфиксная запись декремента
    BigInt operator--(int) {
        BigInt res = *this;
        *this = *this - BigInt(1);
        return res;
    }

    // префиксная запись декремента
    BigInt operator--() {
        return *this = *this - 1;
    }

    // оператор сложения
    BigInt operator+(const BigInt& other) const {
        // если знаки одинаковые, то выполняем сложение
        bool flag = other.get_is_minus() == this->is_minus;
        if (flag) {
            // значение второго числа
            string num2 = other.get_value();
            // длина первого числа
            size_t len1 = this->value.size();
            // длина второго числа
            size_t len2 = num2.size();
            // длина суммы + 1 из-за возможного переноса разряда
            size_t length = 1 + max(len1, len2);
            // строковый массив для выполнения операции сложения
            string res = "0";
            res.resize(length + 1);
            res[length - 1] = res[length] = '\0';
            for (size_t i = 0; i < length - 1; i++) {
                int j = length - 1 - i;
                // выполняем сложение разрядов
                res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (value[len1 - 1 - i] - '0') : 0);
                // выполняем перенос в следующий разряд, если он был
                res[j - 1] = res[j] / 10;
                // оставляем только единицы от возможного переноса и превращаем символ в цифру
                res[j] = res[j] % 10 + '0';
            }
            erase(res, '\0');
            this->is_minus ? res = string("-") + res :res = res;
            // возвращаем результат, в зависимости от знака
            return BigInt(res);
        }
        else
            // одно из чисел отрицательное, а другое положительное, отправляем на вычитание, меняя знак
            return this->is_minus ? (other - (-BigInt(*this))) : (*this - (-BigInt(other)));
    }

    // переводит вектор int в строку
    string createStr(vector<int>& v) const{
        string s = "";
        for (size_t i = 0; i < v.size(); i++)
        {
            s.push_back((char)v[i]);
        }
        erase(s, '\0');
        return s;
    }

    // оператор вычитания
    BigInt operator-(const BigInt &other) const {
        // случай равенства чисел
        if (*this == other) {
            return 0;
        }
        if (!this->is_minus && !other.is_minus) {
            // значения второго числа
            string value2 = other.value;
            // длинны первого и второго числа
            size_t len1 = this->value.size();
            size_t len2 = value2.size();
            // длинна результата
            size_t lenght = max(len1, len2);
            // знак результата
            bool is_minus_res = other > *this;
            // переведем строковое представление чисел в числа
            vector<int> A(lenght), B(lenght);
            vector<int> Result(lenght + 1);
            A[0] = B[0] = 0;
            Result[lenght] = Result[lenght - 1] = '\0';
            // знак результата
            int sign = (2 * is_minus_res) - 1;
            for (size_t i = 0; i < lenght - 1; i++) {
                A[i] += (i < len1) ? (value[len1 - 1 - i] - '0') : 0; // формируем разряды
                B[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0; // из строк аргументов

                B[i + 1] = -is_minus_res; // в зависимости от знака занимаем или не занимаем
                A[i + 1] = is_minus_res - 1; // 10 у следующего разряда

                Result[lenght - 1 - i] += 10 + sign * (B[i] - A[i]);
                Result[lenght - 1 - i - 1] = Result[lenght - 1 - i] / 10;
                Result[lenght - 1 - i] = Result[lenght - 1 - i] % 10 + '0';
            }
            // выполняем операцию с последним разрядом
            A[lenght - 1] += (lenght - 1 < len1) * (value[0] - '0');
            B[lenght - 1] += (lenght - 1 < len2) * (value2[0] - '0');
            // записываем в строку последний разряд
            Result[0] += sign * (B[lenght - 1] - A[lenght - 1]) + '0';
            string answer = is_minus_res ? string("-") + createStr(Result) : createStr(Result);
            return BigInt(answer);
        }
        else
            return this->is_minus && other.is_minus ? (-BigInt(other) - (-BigInt(*this))) : (*this + -BigInt(other));
    }

    // операция деления двух чисел
    BigInt operator/(const BigInt& other) const {
        string value1 = value;
        string value2 = other.value; // запоминаем значение второго числа
        if (value2[0] == '0')
            throw string("На ноль делить нельзя!"); // нельзя делить на ноль, этому ещё в школе учат
        if (value[0] == '0')
            return 0;
        if (value2 == "1")
            return BigInt(other.is_minus ? -BigInt(*this) : *this);
        size_t zeroes = 0;
        while (value2[value2.length() - 1 - zeroes] == '0')
            zeroes++;
        if (zeroes >= value.length())
            return 0;
        // избавляемся от круглых чисел
        if (zeroes) {
            value1 = value1.substr(0, value1.length() - zeroes);
            value2 = value2.substr(0, value2.length() - zeroes);
        }
        bool is_minus_res = this->is_minus ^ other.is_minus; // считаем знак числа
        BigInt tmp(value2);
        size_t divider_length = value2.length(); // запоминаем длину делителя
        long divider_v = divider_length > 8 ? 0 : atol(value2.c_str()); // если длина больше 8, то обнуляем long'овый делитель, иначе переводим строку в long
        size_t length = value1.length(); // получаем длину делимого
        size_t index = 0; // стартуем с нулевого индекса
        string div; // строка результата деления
        string tmp_num; // строка подчисла (которое делится на делитель в столбик)
        // формируем начальное число для деления
        while (BigInt(tmp_num) < tmp && index < length)
            tmp_num += value1[index++];
        do {
            int count = 0; // результат деления подчисла на делитель
            // если можем разделить, то делим
            if (BigInt(tmp_num) >= tmp) {
                if (divider_length > 8) { // если не входит в long, то делим с помощью вычитания
                    BigInt mod = tmp_num;
                    while (mod >= tmp) {
                        mod -= tmp;
                        count++;
                    }
                    tmp_num = mod.value;
                }
                else {
                    long mod = stol(tmp_num);
                    count = mod / divider_v;
                    tmp_num = to_string(mod % divider_v);
                }
            }
            div += count + '0'; // если не делили, то добавили ноль к результату, иначе добавили результат деления
            if (index <= length)
                tmp_num += value1[index++]; // формируем новое значение для подчисла
        } while (index <= length);
        return BigInt(is_minus_res && div != "0" ? string("-") + div : div); // возвращаем результат учитывая знак и возможное равенство нулю
    }

    // операция взятия остатка от деления
    BigInt operator%(const BigInt& other) const {
        string value2 = other.value;
        string value = this->value;

        if (value2[0] == '0')
            throw string("На ноль делить нельзя!");

        if (value[0] == '0' || value2 == "1")
            return 0;

        if (value.length() < 9 && value2.length() < 9) {
            long res = stol(value) % stol(value2);
            return this->is_minus ? -res + stol(value2) : res;
        }
        BigInt tmp(value2);
        size_t divider_length = value2.length(); // запоминаем длину делителя
        long divider_v = divider_length >= 9 ? 0 : atol(value2.c_str()); // если длина больше 8, то обнуляем long'овый делитель, иначе переводим строку в long
        size_t length = value.length();
        size_t index = 0;
        BigInt mod2 = value;
        string tmp_num;
        while (BigInt(tmp_num) < tmp && index < length)
            tmp_num += value[index++];
        do {
            if (BigInt(tmp_num) >= tmp) {
                if (divider_v)
                    tmp_num = to_string(stol(tmp_num) % divider_v);
                else {
                    BigInt mod = tmp_num;
                    while (mod >= tmp)
                        mod -= tmp;
                    tmp_num = mod.value;
                }
            }
            if (index <= length) {
                mod2 = tmp_num;
                tmp_num += value[index++];
            }
        } while (index <= length);
        if (mod2.value == "0")
            return 0;
        return this->is_minus ? -BigInt(mod2) : mod2;
    }

    BigInt operator * (const BigInt& other) const
    {
        if (value == "0" || other.value == "0")
            return 0; // если один из множителей равен нулю, то результат равен нулю
        string value2 = other.value; // запоминаем значение второго числа
        size_t len1 = value.length(); // запоминаем длину первого числа
        size_t len2 = value2.length(); // запоминаем длину второго числа
        size_t length = len1 + len2 + 1; // резульат влезет в сумму длин + 1 из-за возможного переноса
        bool is_minus_res = this->is_minus ^ other.is_minus; // флаг отрицательности результата - отрицательный, если числа разных знаков
        vector<int> A(length), B(length); // массивы аргументов и результата
        string res = ""; // строковый массив для результата
        res.resize(length + 1);
        res[length] = '\0'; // устанавливаем символ окончания строки
        // заполняем массивы инверсной записью чисел (с ведущими нулями)
        for (size_t i = 0; i < length; i++) {
            A[i] = (i < len1) ? (value[len1 - 1 - i] - '0') : 0;
            B[i] = (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
            res[i] = 0;
        }
        // выполняем умножение "в столбик""
        for (size_t i = 0; i < len1; i++) {
            for (size_t j = 0; j < len2; j++) {
                res[length - 1 - (i + j)] += A[i] * B[j];
                res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
                res[length - 1 - (i + j)] %= 10;
            }
        }
        // переписываем результат в строку
        for (size_t i = 0; i < length; i++)
            res[length - 1 - i] += '0';
        return BigInt(is_minus_res ? string("-") + string(res) : string(res)); // возвращаем результат, учитывая его знак
    }

    // краткая запись сложения
    BigInt operator+=(const BigInt& other) {
        return *this = *this + other;
    }

    // краткая запись вычитания
    BigInt operator-=(const BigInt& other) {
        return *this = *this - other;
    }

    // краткая запись умножения
    BigInt operator*=(const BigInt& other) {
        return *this = *this * other;
    }

    // краткая запись деления на целое
    BigInt operator/=(const BigInt& other) {
        return *this = *this / other;
    }

    // краткая запись деления с остатком
    BigInt operator%=(const BigInt& other) {
        return *this = *this % other;
    }
};

// вывод числа в выходной поток
ostream& operator<<(ostream& stream, const BigInt& other) {
    if (other.get_is_minus())
        stream << "-";
    return stream << other.get_value();
}

// ввод числа из входного потока
istream& operator>>(istream& stream, BigInt& other) {
    string value;
    stream >> value;
    other = BigInt(value);
    return stream;
}
