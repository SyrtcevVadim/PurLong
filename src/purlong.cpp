#include <algorithm>
#include <cmath>
#include <iostream>
#include "purlong.h"
using std::cout;
using std::endl;

PurLong::PurLong(std::string number)
{
    // TODO добавить проверку формата числа. Запретить пустые символы и посторонние символы(буквы)
    processSign(number);
    /*  
    Если в числе number в 10-ой СС n знаков, то в СС 10^9 будет [n/9] знаков (округлять вверх)
    т.к. в 10^9 СС 1 цифра описывает 9 цифр из 10-ой СС
    */ 
   int digitsInNumber = static_cast<int>(ceil(number.size()/(double)ZEROS_IN_BASE));
   digits.reserve(digitsInNumber);
   //cout << "initial string:" << number <<endl;
   // Переворачиваем строку, чтобы было удобно записывать разряды в массив
   std::reverse(number.begin(), number.end());
   /*
    Чтобы перевести число из 10-ой СС и 10^9 СС, то нужно брать по 9 цифр справа налево.
    Эти 9 цифр будут вместе представлять цифру числа в 10^9 СС
   */
   for(int i{0}; i < digitsInNumber; i++)
   {
       std::string resultStrDigit = number.substr(9*i, ZEROS_IN_BASE);
       // Переворачиваем эту строку, т.к. изначальная строка тоже была перевёрнута
       std::reverse(resultStrDigit.begin(), resultStrDigit.end());
       digit newDigit = static_cast<digit>(stoi(resultStrDigit));
       digits.push_back(newDigit);
   }


   
   
   /*
   Для удобства выполнения арифметических операций с длинным числом, храним его
   в обратном порядке
   */

//    cout << "got: ";
//    for(digit d: digits)
//    {
//        cout << d<< " ";
//    }
//    cout << endl<<endl;
}

PurLong::PurLong(): PurLong("0") {}

PurLong::PurLong(long long number): PurLong(std::to_string(number)) {}

std::string PurLong::getStringRepr()
{
    std::string result{};
    if(negative)
    {
        result +="-";
    }
    for(auto it{digits.rbegin()}; it != digits.rend(); it++)
    {
        result += std::to_string(*it);
    }
    return result;
}

void PurLong::processSign(std::string &number)
{
    // Изначально мы предполагаем, что на вход подано положительно число
    negative = false;
    // Проверяем, есть ли у поданного числа знак
    if(number[0] == '-')
    {
        negative=true;
        // Удаляем из строки знак '-'
        number = number.substr(1);
    }
    else if(number[0] == '+')
    {
        // Удаляем из строки знак '+'
        number = number.substr(1);
    }
}

std::ostream& operator<<(std::ostream &out, const PurLong &number)
{
    if(number.negative)
    {
        out << "-";
    }
    for(auto it{number.digits.rbegin()}; it != number.digits.rend(); it++)
    {
        out << *it;
    }
    return out;
}



PurLong operator +(const PurLong &lValue, const PurLong &rValue)
{
    // Если оба числа положительны, складываем их
    if(!lValue.negative && !rValue.negative)
    {
        // Находим число с наибольшим количеством разрядов
        bool maxDigitsCondition = (lValue.digits.size()>rValue.digits.size());
        PurLong max=(maxDigitsCondition)?lValue:rValue;
        PurLong min=(maxDigitsCondition)?rValue:lValue;
        //cout << "max: "<< max <<" | min: "<<min<<endl;
        //cout << "min size:"<<min.digits.size()<<endl;
        //cout << "max size: "<<max.digits.size() << endl;
        // Копируем наибольшее число в результат
        PurLong sumResult(max);
        // Если в первом числе n разрядов, а во втором - m, то нужно предоставить max(n,m)+1 разрядов, чтобы можно было
        // записать результат.
        // Предоставляем в результате еще один разряд
        sumResult.digits.push_back(0);
        //cout << "sumResult: " << sumResult<<endl;

        
        
        //cout <<"sumResult size: "<<sumResult.digits.size()<<endl;
        // Складываем числа поразрядно    
        for(int i{0}; i < min.digits.size(); i++)
        {
            
            int sum = sumResult.digits[i]+min.digits[i];
            //cout << "   i:"<<i << "| "<<sumResult.digits[i] <<" + "<< min.digits[i] << " = "<<sum<<endl;
            //cout << "   rest in digit: "<< (sum%BASE) << " carried to next digit: "<< (sum/BASE)<<endl;
            sumResult.digits[i] = sum%BASE;
            sumResult.digits[i+1] += sum/BASE;
            //cout << endl;
        }
        //Удаляем ненужные ведущие нулевые разряды
        while(sumResult.digits.back() == 0)
        {
            //cout << "deleting of trailing zeros"<<endl;
            sumResult.digits.pop_back();
        }
        //cout << "RESULT: "<<min << " + "<<max << " = "<<sumResult<<endl;
        return sumResult;    
    }

}

bool operator==(const PurLong &lValue, const PurLong &rValue)
{
    /*
        Числа считаются равными, если выполняется все условия:
        1. Числа имеют одинаковые знаки
        2. В числах одно и то же число разрядов
        3. Соотвутствующие разряды в числах равны
    */
    if(lValue.negative == rValue.negative && lValue.digits.size() == rValue.digits.size())
    {
        // Поразрядно сравниваем числа
        for(int i{0}; i < lValue.digits.size(); i++)
        {
            if(lValue.digits[i] != rValue.digits[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool operator!=(const PurLong &lValue, const PurLong &rValue)
{
    return !(lValue == rValue);
}

// bool operator >(const PurLong &lValue, const PurLong &rValue)
// {
// }

// bool operator >=(const PurLong &lValue, const PurLong &rValue)
// {

// }

// bool operator <(const PurLong &lValue, const PurLong &rValue)
// {

// }

// bool operator <=(const PurLong &lValue, const PurLong &rValue)
// {

// }