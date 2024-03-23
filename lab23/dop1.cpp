#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

struct list // структура для односвязного списка
{
  int num;
  list* next;
};

regex check("[\\-0-9]+");
list* first = NULL; // указатель на первый элемент
int number; // переменная для хранения числа

void input(list*& first) { // функция для добавления числа в список
  string a;
  cout << "Введите целое число\n";
  getline(cin, a);
  getline(cin, a);
  while (!regex_match(a, check)) {
    cout << "Некорректный ввод\n";
    getline(cin, a);
  }
  number = stoi(a);
  list* newp = new list;
  if (newp != NULL) {
    newp->num = number;
    newp->next = first;
    first = newp;
  }
  else {
    cout << "Произошла ошибка\n";
  }
  cout << '\n';
}



void del(list*& first) { // функция для удаления первого совпадающего элемента с введенным
  if (first == NULL) {
    cout << "Список пуст\n";
  }
  else {
    cout << "Введите число, которое хотите удалить\n";
    string a;
    getline(cin, a);
    getline(cin, a);
    if (a != "") {
      if (a[a.length() - 1] == '\n') {
        a.erase(a.length() - 1);
      }
    }
    while (!regex_match(a, check)) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    number = stoi(a);
    list* prev, * current, * temp;
    if (number == first->num) {
      temp = first;
      first = first->next;
      delete temp;
    }
    else {
      prev = first;
      current = first->next;
      while (current != NULL and number != current->num) {
        prev = current;
        current = current->next;
      }
      if (current != NULL) {
        temp = current;
        prev->next = current->next;
        delete temp;
      }
      else {
        cout << "Число не найдено\n";
      }
    }
  }
  cout << '\n';
}


void search(list* fir) { // функция для поиска суммы положительных элементов 
  int sum = 0;
  while (fir != NULL) {
    if (fir->num > 0) {
      sum += fir->num;
    }
    fir = fir->next;
  }
  if (sum == 0) {
    cout << "В массиве нет положительных чисел\n";
  }
  else {
    cout << "Сумма = " << sum << '\n';
  }
  cout << '\n';
}


void output(list* fir) { // функция для вывода элементов списка
  if (fir == NULL) {
    cout << "Список пуст\n";
  }
  else {
    cout << "Список:\n";
    while (fir != NULL) {
      cout << " --> " << fir->num;
      fir = fir->next;
    }
    cout << " --> NULL\n";
  }
  cout << '\n';
}


void tofile(list* fir) { // функция записи в файл
  list buf;
  ofstream fout("t.txt");
  if (fout.fail()) {
    cout << "Ошибка открытия файла\n";
  }
  else {
    while (fir) {
      buf = *fir;
      fout << buf.num << '\n';
      fir = fir->next;
    }
    fout.close();
  }
}

void fromfile(list*& first) { // функция для считывания списка из файла
  list buf;
  first = NULL;
  ifstream fin("t.txt");
  if (fin.fail()) {
    cout << "Ошибка открытия файла\n";
  }
  else {
    string a;
    getline(fin, a);
    if (a == "") {
      cout << "Файл пуст\n";
      return;
    }
    if (a != "") {
      if (a[a.length() - 1] == '\n') {
        a.erase(a.length() - 1);
      }
    }
    while (!regex_match(a, check)) {
      cout << "Некорректная информация\n";
      cout << "Дальнейшее чтение невозможно\n";
      return;
    }
    buf.num = stoi(a);
    while (!fin.eof()) {
      list* newp = new list;
      if (newp != NULL) {
        newp->num = buf.num;
        newp->next = first;
        first = newp;
        getline(fin, a);
        if (a != "") {
          if (a[a.length() - 1] == '\n') {
            a.erase(a.length() - 1);
          }
        }
        else {
          return;
        }
        while (!regex_match(a, check)) {
          cout << "Некорректная информация\n";
          cout << "Дальнейшее чтение невозможно\n";
          return;
        }
        buf.num = stoi(a);
      }
    }
    fin.close();
  }
}


int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // переменная для выбора опции
  do {
    cout << "Введите:\n";
    cout << "1 - для ввода целого числа с клавиатуры и добавления в начало списка\n";
    cout << "2 - для удаления элемента из списка\n";
    cout << "3 - для поиска суммы положительных элементов\n";
    cout << "4 - для вывода элементов списка в консоль\n";
    cout << "5 - для записи списка в файл\n";
    cout << "6 - для чтения элементов списка из файла\n";
    cout << "7 - для выхода\n";
    cin >> choice;
    switch (choice) {
    case '1': {
      input(first);
      break;
    }
    case '2': {
      del(first);
      break;
    }
    case '3': {
      search(first);
      break;
    }
    case '4': {
      output(first);
      break;
    }
    case '5': {
      tofile(first);
      break;
    }
    case '6': {
      fromfile(first);
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
