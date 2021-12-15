#include<cstdint>
#include<iostream>
#include<vector>
#include<string>
// Примечание: СС - Система Счисления

typedef int32_t digit;

// Для удобства преобразования числа в/из 10 СС будем использовать 10^9 СС
#define BASE 1'000'000'000
// Количество нулей в основании СС
#define ZEROS_IN_BASE 9



/*
    Класс неограниченно больших целых чисел
*/
class PurLong
{
public:
    /// Создаёт объёкт неограниченного большого числа, который изначально будет равняться нулю
    PurLong();
    /// На основе строкового представления числа в десятичной СС строит объект
    /// неограниченно большого числа. У числа можно указать знак: как -, так и +
    PurLong(std::string number);
    /// На основе числа в десятичной СС строит объект 
    /// неограниченно большого числа. У числа можно указать знак: как -, так и +
    PurLong(long long number);
    /// Возвращает строкове представление неограниченно длинного числа
    std::string getStringRepr();


    friend std::ostream& operator<<(std::ostream &out, const PurLong &number);

    
    // Меняет знак числа
    friend PurLong operator -(const PurLong &rValue);
    // Возвращает число в неизменном виде
    friend PurLong operator +(const PurLong &rValue);

    friend PurLong operator +(const PurLong &lValue, const PurLong &rValue);
    friend PurLong operator -(const PurLong &lValue, const PurLong &rValue);

    friend bool operator ==(const PurLong &lValue, const PurLong &rValue);
    friend bool operator !=(const PurLong &lValue, const PurLong &rValue);
    //friend bool operator >(const PurLong &lValue, const PurLong &rValue);
    // friend bool operator >=(const PurLong &lValue, const PurLong &rValue);
    // friend bool operator <(const PurLong &lValue, const PurLong &rValue);
    // friend bool operator <=(const PurLong &lValue, const PurLong &rValue);
private:
    /// Показывает, является ли число отрицательным
    bool negative;
    /// Динамический массив цифр числа. Все цифры числа хранятся в системе счисления,
    /// определяемым макросом BASE
    std::vector<digit> digits;
    /// Выясняет, есть ли у числа знак. Если у числа есть знак, он извлекается
    /// из строки и устанавливается соответственный флаг знака числа
    void processSign(std::string &number);
    /// Удаляют из числа ведущие(незначащие нули)
    void deleteLeadingZeros();
};