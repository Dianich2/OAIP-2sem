#include <iostream>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <string>
#define SIZE 30
using namespace std;

struct student {
  char lastname[20]; // фамилия
  char firstname[20]; // имя
  char patronimic[20]; // отчество
  int kol_exam; // количество экзаменов
  int* marks; // оценки
};

struct student students[SIZE]; // текущая структура для хранения информации о студентах
int currentsize = 0; //текущее количество записей

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

void input() { // функция для ввода записи
  if (currentsize < SIZE) {
    cout << "Введите фамилию\n";
    gets_s(students[currentsize].lastname);
    while (!checkfio(students[currentsize].lastname)) {
      cout << "Некорректный ввод\n";
      gets_s(students[currentsize].lastname);
    }
    cout << "Введите имя\n";
    gets_s(students[currentsize].firstname);
    while (!checkfio(students[currentsize].firstname)) {
      cout << "Некорректный ввод\n";
      gets_s(students[currentsize].firstname);
    }
    cout << "Введите отчество\n";
    gets_s(students[currentsize].patronimic);
    while (!checkfio(students[currentsize].patronimic)) {
      cout << "Некорректный ввод\n";
      gets_s(students[currentsize].patronimic);
    }
    cout << "Введите количество экзаменов\n";
    string d;
    getline(cin, d);
    while (true) {
      bool t = true;
      for (int j = 0; j < d.length(); j++) {
        if (d[j] < '0' || d[j] > '9') {
          t = false;
          break;
        }
      }
      if (t && stoi(d) != 0 ) {
        break;
      }
      cout << "Некорректный ввод\n";
      getline(cin, d);
    }
    students[currentsize].kol_exam = stoi(d);
    students[currentsize].marks = new int[students[currentsize].kol_exam]; // выделение памяти под массив оценок
    cout << "Введите оценки студента(по шкале от 1 до 5)\n";
    for (int i = 0; i < students[currentsize].kol_exam; i++) {
      getline(cin, d);
      while (true) {
        bool t = true;
        for (int j = 0; j < d.length(); j++) {
          if (d[j] < '1' || d[j] > '5') {
            t = false;
            break;
          }
        }
        if (!t || d == "") {
          cout << "Некорректный ввод\n";
          cout << "Вводите оценки по одной\n";
        }
        else {
          if(stoi(d) < 1 || stoi(d) > 5) {
            cout << "Некорректный ввод\n";
            cout << "Вводите оценки по одной\n";
          }
          else {
            break;
          }
        }
        getline(cin, d);
      }
      students[currentsize].marks[i] = stoi(d);
    }
    currentsize++; // увеличение счетика записей
  }
  else {
    cout << "Список студентов переполнен\n";
  }
  cout << '\n';
}


void del() { // функция для удаления записи
  int n; // переменная для хранения номера записи
  cout << "Введите номер записи, которую вы хотите удалить\n";
  cin >> n; n--;
  if (n >= currentsize or n < 0) {
    cout << "Такой записи нет\n";
  }
  else {
    for (int i = n; i < currentsize - 1; i++) {
      students[i] = students[i + 1];
    }
    currentsize--; // уменьшение счетчика записей
  }
  cout << '\n';
}

void check() { // функция для проверки сдачи экзаменов студентом на 4 и 5
  int n; // переменная для хранения номера записи о студенте, которую мы хотим проверить
  cout << "Введите номер записи студента, оценки которого Вы хотите проверить\n";
  cin >> n; n--;
  if (n >= currentsize or n < 0) {
    cout << "Такой записи нет\n";
  }
  else {
    bool t = true; // переменная-флажок для проверки студента на отличника
    for (int i = 0; i < students[n].kol_exam; i++) {
      if (students[n].marks[i] < 4) { // если нашлась оценка меньше 4
        cout << "Данный студент не отличник(у него есть оценки ниже 4)\n";
        t = false;
        break;
      }
    }
    if (t) { // если все оценки выше 3
      cout << "Этот студент отличник(у него все оценки выше 3)\n";
    }
  }
  cout << '\n';
}

void success() { // функция для подсчета общей успеваемости
  if (currentsize == 0) {
    cout << "Список пуст\n";
    return;
  }
  int kol = 0; // переменная для хранения количества студентов отличников
  bool t = true; // переменная-флажок для проверки студента на отличника
  for (int i = 0; i < currentsize; i++) {
    for (int j = 0; j < students[i].kol_exam; j++) {
      if (students[i].marks[j] < 4) {
        t = false;
        break;
      }
    }
    if (t) {
      kol++;
    }
    t = true;
  }
  cout << "Общее количество студентов " << currentsize << '\n';
  cout << "Количество студентов-отличников " << kol << '\n';
  cout << "Процент успеваемости(отношения количества студентов-отличников к общему количеству) " << ((double)kol / (double)currentsize) * 100 << "%\n";
  cout << '\n';
}

void output() {
  if (currentsize == 0) {
    cout << "Записей нет\n";
    return;
  }
  for (int i = 0; i < currentsize; i++) {
    cout << "Фамилия: " << students[i].lastname << '\n';
    cout << "Имя: " << students[i].firstname << '\n';
    cout << "Отчество: " << students[i].patronimic << '\n';
    cout << "Количество сданных экзаменов: " << students[i].kol_exam << '\n';
    cout << "Оценки: ";
    for (int j = 0; j < students[i].kol_exam; j++) {
      cout << students[i].marks[j] << ' ';
    }
    cout << '\n';
    cout << '\n';
  }
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char a; // переменная для считывания выбора опции
  string c;
  do {
    cout << "Выберите:\n";
    cout << "1-для ввода информации о новом студенте\n";
    cout << "2-для удаления записи\n";
    cout << "3-для проверки сдачи всех экзаменов на 4 и 5\n";
    cout << "4-для подсчета общей успеваемости студентов(процент студентов, которые сдали все экзамены на 4 и 5)\n";
    cout << "5-для вывода записей\n";
    cout << "6-для выхода\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "Некорректный ввод\n";
      getline(cin, c);
    }
    a = c[0];
    switch (a) {
    case '1': {
      input();
      break;
    }
    case '2': {
      del();
      break;
    }
    case '3': {
      check();
      break;
    }
    case '4': {
      success();
      break;
    }
    case '5': {
      output();
      break;
    }
    case '6': {
      break;
    }
    default: {
      cout << "Некорректный ввод\n";
    }
    }
  } while (a != '6');
}
