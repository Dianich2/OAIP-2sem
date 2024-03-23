#include <iostream>
#include <iomanip>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <regex>
#define SIZE 30
using namespace std;

regex costs("([0-9]+)((\\.){1}([0-9]+)|(\\.){0})");
regex da("([1-9]{1}[0-9]*)");
unsigned days_in_month[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

struct date_of_delivery {
  unsigned day : 6; 
  unsigned month : 5;
  unsigned year : 12; 
};

enum month {
  January = 1, February, March,
  April, May, June, July, August, September,
  October, November, December
} months;

struct lambard { // структура хранения информации о ломбарде
  char lastname[100];
  char productname[100];
  double cost;
  double zalogsum;
  date_of_delivery currentdate;
  int shelf_life;
};


struct lambard currentlambard[SIZE]; // текущая структура хранения информации о ломбарде
int currentsize = 0; // количество записей в структуре


bool checkfio(string f) {
  bool t = false;
  for (int i = 0; i < f.length(); i++) {
    if (i == 0) {
      if ((f[0] >= 'A' && f[0] <= 'Z') || (f[0] >= 'А' && f[0] <= 'Я')) {
        t = true;
        continue;
      }
      else {
        return 0;
      }
    }
    else if ((f[i] >= 'A' && f[i] <= 'Z') || (f[i] >= 'А' && f[i] <= 'Я') && t) {
      if (f[i - 1] == '-') {
        continue;
      }
      else {
        return 0;
      }
    }
    else if ((f[i] >= 'a' && f[i] <= 'z') || (f[i] >= 'а' && f[i] <= 'я')) {
      if (f[i - 1] == '-') {
        return 0;
      }
      continue;
    }
    else if (f[i] == '-') {
      continue;
    }
    else {
      return 0;
    }
  }
  return 1;
}

bool visokosny(int y) { // функция для определения високосности года
  if (y % 4 != 0) {
    return 0;
  }
  if (y % 100 != 0) {
    return 1;
  }
  if (y % 400 == 0) {
    return 1;
  }
  return 0;
}

bool check_date(string d, lambard& lamb) {
  for (int i = 0; i < d.length(); i++) {
    if (d[i] < '0' || d[i] > '9') {
      return 0;
    }
  }
  int f = stoi(d);
  lamb.currentdate.year = f % 10000; f /= 10000;
  lamb.currentdate.month = f % 100; f /= 100;
  lamb.currentdate.day = f;
  bool t = visokosny(lamb.currentdate.year);
  if (lamb.currentdate.year == 2024 && ((lamb.currentdate.month == 3 && lamb.currentdate.day > 20) ||(lamb.currentdate.month > 3))) {
    return 0;
  }
  if (lamb.currentdate.month <= 0 || lamb.currentdate.month > 12) {
    return 0;
  }
  else if (lamb.currentdate.month != 2 && lamb.currentdate.day > days_in_month[lamb.currentdate.month - 1] || lamb.currentdate.day <= 0) {
    return 0;
  }
  else if (lamb.currentdate.month == 2) {
    if (t) {
      if (lamb.currentdate.day > days_in_month[lamb.currentdate.month - 1]) {
        return 0;
      }
    }
    else {
      if (lamb.currentdate.day > days_in_month[lamb.currentdate.month - 1] - 1) {
        return 0;
      }
    }
  }
}

void input() { // функция для ввода информации о новой записи
  if (currentsize < SIZE) {
    cout << "Введите фамилию клиента\n";
    gets_s(currentlambard[currentsize].lastname);
    while (!checkfio(currentlambard[currentsize].lastname)) {
      cout << "Некорректный ввод\n";
      gets_s(currentlambard[currentsize].lastname);
    }
    cout << "Введите наименование товара\n";
    gets_s(currentlambard[currentsize].productname);
    cout << "Введите оценочную стоимость\n";
    string s;
    getline(cin, s);
    while(!regex_match(s.c_str(), costs)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    currentlambard[currentsize].cost = stof(s);
    cout << "Введите сумму, выданную под залог\n";
    getline(cin, s);
    while (!regex_match(s.c_str(), costs)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    currentlambard[currentsize].zalogsum = stof(s);
    cout << "Введите дату сдачи в формате(ДДММГГГГ)\n";
    getline(cin, s);
    while (!check_date(s, currentlambard[currentsize])) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    cout << "Введите срок хранения(количество дней)\n";
    getline(cin, s);
    while (!regex_match(s.c_str(), da)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    currentlambard[currentsize].shelf_life = stoi(s);
    currentsize++;
  }
  else {
    cout << "Невозможно сделать новую запись. Слишком много записей.\n";
  }
  cout << '\n';
}


void saydate(int j) { // функция для красивого вывода даты
  if (currentlambard[j].currentdate.day < 10) {
    cout << '0' << currentlambard[j].currentdate.day << '.';
  }
  else {
    cout << currentlambard[j].currentdate.day << '.';
  }
  if (currentlambard[j].currentdate.month < 10) {
    cout << '0' << currentlambard[j].currentdate.month << '.';
  }
  else {
    cout << currentlambard[j].currentdate.month << '.';
  }
  cout << currentlambard[j].currentdate.year << '\n';
}

void output() { // функция для вывода информации о ломбарде
  if (currentsize > 0) {
    for (int i = 0; i < currentsize; i++) {
      cout << "Фамилия клиента: " << currentlambard[i].lastname << '\n';
      cout << "Наименование товара: " << currentlambard[i].productname << '\n';
      cout << "Оценочная стоимость: " << currentlambard[i].cost << '\n';
      cout << "Сумма, выданная под залог: " << currentlambard[i].zalogsum << '\n';
      cout << "Дата сдачи: ";
      saydate(i);
      cout << "Срок хранения: " << currentlambard[i].shelf_life << '\n';
      cout << '\n';
    }
  }
  else {
    cout << "Записей нет\n";
    cout << '\n';
  }
}


void del() { // функция для удаления записи
  int n; // переменная для номера записи 
  cout << "Введите номер записи, которую хотите удалить\n";
  cin >> n; n--;
  if (n < 0 or n >= currentsize) {
    cout << "Такой записи нет\n";
  }
  else {
    for (int i = n; i < currentsize; i++) {
      currentlambard[i] = currentlambard[i + 1];
    }
    currentsize--;
  }
  cout << '\n';
}


void search() { // функция поиска по сроку хранения
  int n; // переменная для хранения срока хранения
  cout << "Введите срок хранения, по которому будем искать вещи(в днях)\n";
  string s;
  getline(cin, s);
  while (!regex_match(s.c_str(), da)) {
    cout << "Некорректный ввод\n";
    getline(cin, s);
  }
  n = stoi(s);
  bool t = false; // переменная-флажок для отслеживания нахождения нужной записи
  for (int i = 0; i < currentsize; i++) {
    if (currentlambard[i].shelf_life == n) {
      cout << "Фамилия клиента: " << currentlambard[i].lastname << '\n';
      cout << "Наименование товара: " << currentlambard[i].productname << '\n';
      cout << "Оценочная стоимость: " << currentlambard[i].cost << '\n';
      cout << "Сумма, выданная под залог: " << currentlambard[i].zalogsum << '\n';
      cout << "Дата сдачи: ";
      saydate(i);
      cout << "Срок хранения: " << currentlambard[i].shelf_life << '\n';
      cout << '\n';
      t = true;
    }
  }
  if (!t) {
    cout << "Информация не найдена\n";
  }
  cout << '\n';
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice;
  string c;
  do {
    cout << "Введите:\n";
    cout << "1- для ввода новой записи\n";
    cout << "2- для вывода всех записей\n";
    cout << "3- для удаления записи\n";
    cout << "4- для поиска по сроку хранения\n";
    cout << "5- для выхода\n";
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
      input();
      break;
    }
    case '2': {
      output();
      break;
    }
    case '3': {
      del();
      break;
    }
    case '4': {
      search();
      break;
    }
    case '5': {
      break;
    }
    }
  } while (choice != '5');
}
