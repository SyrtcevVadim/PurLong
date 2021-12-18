#include <algorithm>
#include <cmath>
#include <iostream>
#include "purlong.h"
using std::cout;
using std::endl;
using std::string;

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
   //std::reverse(number.begin(), number.end());
  
  
   /*
    Чтобы перевести число из 10-ой СС и 10^9 СС, то нужно брать по 9 цифр справа налево.
    Эти 9 цифр будут вместе представлять цифру числа в 10^9 СС
   */
   for(int i{0}; i < digitsInNumber; i++)
   {
       // Берём 9 цифр с конца и делаем из них цифру нового числа
       string newDigit{""};
       for(int j{0}; j < ZEROS_IN_BASE; j++)
       {
           int oldDigitIndex = (number.size()-1-9*i)-j;
           // Проверяем, не вышел ли индекс за рамки числа
           if(oldDigitIndex < 0)
           {
               break;
           }
           newDigit = number[oldDigitIndex] + newDigit;
       }
       //cout << "i: " << i<<" digit: "<<newDigit << endl;
       // Добавляем полученную цифру в наше число
       digits.push_back(static_cast<digit>(stoi(newDigit)));
   }

//    for(int i{0}; i < digitsInNumber; i++)
//    {
//        std::string resultStrDigit = number.substr(9*i, ZEROS_IN_BASE);
//        // Переворачиваем эту строку, т.к. изначальная строка тоже была перевёрнута
//        std::reverse(resultStrDigit.begin(), resultStrDigit.end());
//        digit newDigit = static_cast<digit>(stoi(resultStrDigit));
//        digits.push_back(newDigit);
//    }

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
    // Число 0 - особое и не имеет знака
    if(number == "0")
    {
        return;
    }
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

void PurLong::deleteLeadingZeros()
{
    /*
    Учитываем, что все цифры числа могут оказаться нулевыми. Это может произойти, например, после
    вычитания одинаковых чисел друг из друга. В результате должен остаться единственный ноль
    */
    while(digits.back()==0 && digits.size() > 1)
    {
        digits.pop_back();
    }
}

PurLong PurLong::getAbs()const
{
    if(negative)
    {
        return -(*this);
    }
    return *this;
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


PurLong operator -(const PurLong &rValue)
{
    PurLong result{rValue};
    // Ноль не имеет знака
    if(rValue == PurLong(0))
    {
        return rValue;
    }
    result.negative = !result.negative;
    return result;
}

PurLong operator +(const PurLong &rValue)
{
    return rValue;
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
        sumResult.deleteLeadingZeros();
        // while(sumResult.digits.back() == 0)
        // {
        //     //cout << "deleting of trailing zeros"<<endl;
        //     sumResult.digits.pop_back();
        // }
        //cout << "RESULT: "<<min << " + "<<max << " = "<<sumResult<<endl;
        return sumResult;    
    }
    // Пусть, a > 0 && b > 0
    // (-a)+(-b) = -(a+b)
    else if(lValue.negative && rValue.negative)
    {
        return -(lValue.getAbs()+rValue.getAbs());
    }
    // (-a)+b = b-a
    else if(lValue.negative && !rValue.negative)
    {
        return (rValue - lValue.getAbs());
    }
    // a+(-b) = a-b
    else if(!lValue.negative && rValue.negative)
    {
        return (lValue - rValue.getAbs());
    }
}

PurLong operator -(const PurLong &lValue, const PurLong &rValue)
{
    // Если оба числа положительны, производим поразрядное вычитание
    if(!lValue.negative && !rValue.negative)
    {
        bool resultIsNegative;
        PurLong min, max;
        // Копируем наибольшее число в результат
        if(lValue >= rValue)
        {
            max = lValue;
            min = rValue;
            // Уменьшаемое больше вычитаемого, результат положительный
            resultIsNegative = false;
        }
        else
        {
            max = rValue;
            min = lValue;
            // Уменьшаемое меньше вычитаемого, результат отрицательный
            resultIsNegative = true;
        }
        // Копируем максимальное число в результат
        PurLong differenceResult{max};
        // Поразрядно вычитаем из большего числа меньшее
        for(int i{0}; i < min.digits.size(); i++)
        {
            int difference = differenceResult.digits[i]-min.digits[i];
            if(difference < 0)
            {
                // Занимаем единицу из ближайшего ненулевого старшего разряда
                int j = i+1;
                // Ищем такой разряд. Он обязательно должен быть, т.к. это число больше вычитаемого
                while(differenceResult.digits[j]==0)
                {
                    // В каждый нулевой разряд, который мы прошли, должно перенестись значение BASE-1
                    differenceResult.digits[j]=BASE-1;
                    j++;
                }
                differenceResult.digits[j]--;
                difference += BASE;
            }
            // Запоминаем результат вычитания значений в текущем разрядеы
            differenceResult.digits[i] = difference;
        }
        // Удаляем из результата незначащие нули
        differenceResult.deleteLeadingZeros();
        // Учитываем знак результата
        if(resultIsNegative)
        {
            return -differenceResult;
        }
        return differenceResult;
    }
    // Пусть, a > 0 && b > 0
    // (-a)-(-b) = -a+b = b-a
    else if(lValue.negative && rValue.negative)
    {
        return rValue.getAbs() - lValue.getAbs();
    }
    // a-(-b) = a+b
    else if(!lValue.negative && rValue.negative)
    {
        return lValue.getAbs() + rValue.getAbs();
    }
    // (-a)-b = -(a+b)
    else if(lValue.negative && !rValue.negative)
    {
        return -(lValue.getAbs() + rValue.getAbs());
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

PurLong PurLong::operator++()
{
    *this = *this + 1;
    return *this;
}

PurLong PurLong::operator++(int)
{
    PurLong oldValue(*this);
    ++(*this);
    return oldValue;
}

bool operator >(const PurLong &lValue, const PurLong &rValue)
{
    /*
    Мы считаем левое число больше правого, если выполняется хотя бы одно из следующих условий:
    1. Левое число положительное, правое - отрицательное
    2. Оба числа положительные и в левом числе больше разрядов, чем в правом
    3. Оба числа положительные, в обоих числах одинаковое число разрядов и
    старший разряд левого числа больше старшего разряда правого числа
    4. Оба числа отрицательные, тогда большее из них то, которое меньше по абсолютному значению
    */
    if(!lValue.negative && rValue.negative)
    {
        return true;
    }
    if(!lValue.negative && !rValue.negative)
    {
        if(lValue.digits.size() > rValue.digits.size())
        {
            return true;
        }
        else if(lValue.digits.size()==rValue.digits.size())
        {
            int lastDigitIndex = lValue.digits.size()-1;
            return (lValue.digits[lastDigitIndex] > rValue.digits[lastDigitIndex]);
        } 
    }
    if(lValue.negative && rValue.negative)
    {
        /*
        Вместо реализации функции взятия абсолютного значения добавляем к числам '-;, делая их положительными
        */
        return (PurLong(-rValue)>PurLong(-lValue));
    }
    // В противном случае, правое число больше
    return false;
}

bool operator >=(const PurLong &lValue, const PurLong &rValue)
{
    return (lValue == rValue || lValue > rValue);
}

bool operator <(const PurLong &lValue, const PurLong &rValue)
{
    return (rValue > lValue);
}

bool operator <=(const PurLong &lValue, const PurLong &rValue)
{
    return (lValue == rValue || lValue < rValue);
}