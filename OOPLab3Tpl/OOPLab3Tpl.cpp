﻿// OOPLab3Tpl.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №3. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//

#include <iostream>

// Ваші файли загловки 
//
#include "Lab3Example.h"
int main()
{
    setlocale(LC_CTYPE, "ukr");
    std::cout << " Lab #3  !\n";
//  Код виконання завдань
//  Головне меню завдань
//  Функції та класи можуть знаходитись в інших файлах проекту

    int conv = 2;
    if (conv == 1) conv = mainExample1();
    if (conv == 2) conv = mainExample2(); 
  //  if (conv == 3) conv = mainExample3();

}

