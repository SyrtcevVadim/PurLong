#include <algorithm>
#include "purlong.h"


PurLong::PurLong(std::string number)
{
    /* 
    Если в числе number в 10-ой СС n знаков, то в СС 10^9 будет [n/9] знаков
    т.к. в 10^9 СС 1 цифра описывает 9 цифр из 10-ой СС
    */ 
   int digitsInNumber = static_cast<int>(number.size()/ZEROS_IN_BASE);
   digits.reserve(digitsInNumber);
   /*
    Чтобы перевести число из 10-ой СС и 10^9 СС, то нужно брать по 9 цифр справа налево.
    Эти 9 цифр будут вместе представлять цифру числа в 10^9 СС
   */
   for(int i{0}; i < digitsInNumber; i++)
   {
       digit newDigit = static_cast<digit>(stoi(number.substr(9*i, ZEROS_IN_BASE)));
       digits.push_back(newDigit);
   }
   /*
   Для удобства выполнения арифметических операций с длинным числом, храним его
   в обратном порядке
   */
   std::reverse(digits.begin(), digits.end());
}

PurLong::PurLong(long long number): PurLong(std::to_string(number))
{}