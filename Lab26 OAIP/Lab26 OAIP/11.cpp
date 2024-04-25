#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int currentsize = 0; // текущий размер списка
regex checknum("[0-9]+");
regex checkcity("(([A-ZА-Я]{1}[a-zа-я]+[ ]?)+||([A-ZА-Я]{1}[a-zа-я]+([\\-]{1})[A-ZА-Я]{1}[a-zа-я]+))");

struct Address {
  char name[100];
  char city[100];
  Address* next;
  Address* prev;
};

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

void insert(Address* cur, Address** first, Address** last) { // вставить новый элемент
  Address* p = *last;
  if (*last == NULL) {
    cur->next = NULL;
    cur->prev = NULL;
    *last = cur;
    *first = cur;
  }
  else {
    p->next = cur;
    cur->prev = p;
    cur->next = NULL;
    *last = cur;
  }
  currentsize++;
}

Address* set() { // функция для создания элемента
  string a;
  Address* temp = new Address;
  cout << "Введите имя:\n";
  getline(cin, a);
  while (!checkfio(a)) {
    cout << "Некорректный ввод\n";
    getline(cin, a);
  }
  strcpy_s(temp->name, a.c_str());
  cout << "Введите город:\n";
  getline(cin, a);
  while (!regex_match(a, checkcity)) {
    cout << "Некорректный ввод\n";
    getline(cin, a);
  }
  strcpy_s(temp->city, a.c_str());
  temp->next = NULL;
  temp->prev = NULL;
  return temp;
}


void del(Address** first, Address** last) { // функция для удаления
  char currentname[100];
  string a;
  Address* t = *first;
  if (t == NULL) {
    cout << "Список пуст\n";
  }
  else {
    cout << "Введите имя, по которому будем удалять запись\n";
    getline(cin, a);
    while (!checkfio(a)) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    strcpy_s(currentname, a.c_str());
    while (t) {
      if (!strcmp(currentname, t->name)) {
        break;
      }
      t = t->next;
    }
    if (!t) {
      cout << "Запись не найдена\n";
    }
    else {
      if (*first == t) {
        *first = t->next;
        if (*first) {
          (*first)->prev = NULL;
        }
        else {
          (*last) = NULL;
        }
      }
      else {
        t->prev->next = t->next;
        if (t != *last) {
          t->next->prev = t->prev;
        }
        else {
          *last = t->prev;
        }
      }
      delete t;
      currentsize--;
    }
  }
}


void output(Address** first) { // функция для вывода всех записей
  Address* t = *first;
  if (t == NULL) {
    cout << "Список пуст\n";
  }
  else {
    while (t) {
      cout << t->name << '\n' << t->city << '\n';
      cout << '\n';
      t = t->next;
    }
  }
}

void search(Address** first) { // функция для поиска
  char currentname[100];
  string a;
  cout << "Введите имя для поиска\n";
  getline(cin, a);
  while (!checkfio(a)) {
    cout << "Некорректный ввод\n";
    getline(cin, a);
  }
  strcpy_s(currentname, a.c_str());
  Address* t = *first;
  while (t) {
    if (!strcmp(currentname, t->name)) {
      break;
    }
    t = t->next;
  }
  if (t) {
    cout << t->name << '\n' << t->city << '\n';
  }
  else {
    cout << "Запись не найдена\n";
  }
}

void changeX(Address* first) { // функция замены
  int num;
  string a;
  cout << "Введите номер элемента, который хотите изменить\n";
    getline(cin, a);
  while (!regex_match(a, checknum)) {
    cout << "Некорректный ввод\n";
    getline(cin, a);
  }
  num = stoi(a); num--;
  if (num >= currentsize or num < 0) {
    cout << "Такого элемента нет\n";
  }
  else {
    for (int i = 0; i < num; i++) {
      first = first->next;
    }
    cout << "Введите новое имя\n";
    getline(cin, a);
    while (!checkfio(a)) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    strcpy_s(first->name, a.c_str());
    cout << "Введите новый город\n";
    getline(cin, a);
    while (!regex_match(a, checkcity)) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    strcpy_s(first->city, a.c_str());
  }
}

void tofile(Address* first) { // функция записи в файл
  ofstream fout("t.txt");
  while (first) {
    fout << first->name << '\n';
    fout << first->city << '\n';
    first = first->next;
  }
  fout.close();
}

void fromfile(Address** first, Address** last) { // функция чтения из файла
  currentsize = 0;
  string a;
  ifstream fin("t.txt");
  *first = NULL;
  *last = NULL;
  while (!fin.eof()) {
    Address* cur = new Address;
    getline(fin, a);
   if(!checkfio(a)) {
     cout << "В файле содержится некорректная информация\n";
     cout << "Дальнейшее чтение невозможно\n";
     break;
    }
    strcpy_s(cur->name, a.c_str());
    if (fin.eof()) {
      break;
    }
    getline(fin, a);
    if(!regex_match(a, checkcity)) {
      cout << "В файле содержится некорректная информация\n";
      cout << "Дальнейшее чтение невозможно\n";
      break;
    }
    strcpy_s(cur->city, a.c_str());
    insert(cur, first, last);
  }
  fin.close();
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice;
  string a;
  Address* first = NULL;
  Address* last = NULL;
  do {
    cout << "Введите:\n";
    cout << "1 - для ввода новой записи\n";
    cout << "2 - для удаления первой записи с именем, введенным с клавиатуры\n";
    cout << "3 - для вывода всех записей\n";
    cout << "4 - для поиска первого элемента с именем, введенным с клавиатуры\n";
    cout << "5 - для замены элемента с введенным номером\n";
    cout << "6 - для записи списка в файл\n";
    cout << "7 - для чтения списка из файла\n";
    cout << "8 - для выхода\n";
    getline(cin, a);
    while (a.length() != 1) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    choice = a[0];
    switch (choice) {
    case '1': {
      insert(set(), &first, &last);
      cout << '\n';
      break;
    }
    case '2': {
      del(&first, &last);
      cout << '\n';
      break;
    }
    case '3': {
      output(&first);
      cout << '\n';
      break;
    }
    case '4': {
      search(&first);
      cout << '\n';
      break;
    }
    case '5': {
      changeX(first);
      cout << '\n';
      break;
    }
    case '6': {
      tofile(first);
      cout << '\n';
      break;
    }
    case '7': {
      fromfile(&first, &last);
      cout << '\n';
      break;
    }
    case '8': {
      break;
    }
    }
  } while (choice != '8');
}



