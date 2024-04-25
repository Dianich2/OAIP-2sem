#include <iostream>
#include<Windows.h>
#include <conio.h>
#include "func.h"
#include <string>
using namespace std;

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // переменная для выбора опции
  Stack* mystack = nullptr;
  do {
    cout << "Введите:\n";
    cout << "1 - для добавления элемента в стек\n";
    cout << "2 - для извлечения элемента из стека\n";
    cout << "3 - для записи в файл\n";
    cout << "4 - для чтения из файла\n";
    cout << "5 - для вывода стека с очисткой\n";
    cout << "6 - для удаления первого положительного элемента\n";
    cout << "7 - для выхода\n";
    cin >> choice;
    switch (choice) {
    case '1': {
      int n;
      cout << "Введите число, которое хотите добавить в стек\n";
      cin >> n;
      push(mystack, n);
      break;
    }
    case '2': {
      pop(mystack);
      break;
    }
    case '3': {
      tofile(mystack);
      break;
    }
    case '4': {
      fromfile(mystack);
      break;
    }
    case '5': {
      output_clean(mystack);
      break;
    }
    case '6': {
      del_plus(mystack);
      break;
    }
    case '7': {
      break;
    }
    default: {
      cout << "Некорректный ввод\n";
      break;
    }
    }
  } while (choice != '7');
}