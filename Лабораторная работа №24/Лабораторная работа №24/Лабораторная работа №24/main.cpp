#include <iostream>
#include<Windows.h>
#include <conio.h>
#include "func.h"
#include <string>
#include <regex>
using namespace std;

extern regex checknum("[\\-]?[0-9]+");

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // переменная для выбора опции
  string c;
  Stack *mystack = nullptr;
  do {
    cout << "Введите:\n";
    cout << "1 - для добавления элемента в стек\n";
    cout << "2 - для извлечения элемента из стека\n";
    cout << "3 - для записи в файл\n";
    cout << "4 - для чтения из файла\n";
    cout << "5 - для вывода стека с очисткой\n";
    cout << "6 - для удаления элементов стека, которые кратны 3\n";
    cout << "7 - для выхода\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "Некорректный ввод\n";
      getline(cin, c);
    }
    choice = c[0];
    switch (choice) {
    case '1': {
      int n;
      cout << "Введите число, которое хотите добавить в стек\n";
      string b;
      getline(cin, b);
      while (!regex_match(b, checknum)) {
        cout << "Некорректный ввод\n";
        getline(cin, b);
      }
      n = stoi(b);
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
      del_3(mystack);
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