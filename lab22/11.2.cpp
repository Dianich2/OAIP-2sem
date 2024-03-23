#include <iostream>
#include <iomanip>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

int days_in_month[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

FILE* t; // файл для записи и чтения данных
regex numcar("([A-Z0-9]+([-]?)([A-Z0-9 ]+))");
regex colo("([A-Za-zа-яА-Я-]+)([A-Za-zа-яА-Я- ]*)");
union automobiles { // текущее объединение
  char car_model[100]; // марка автомобиля
  char color[100]; // цвет
  char number[100]; // номер
  int date; // для даты
  char body_type[100]; // тип кузова
  char lastname[100]; // фамилия владельца
} automobile;



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

bool check_date(string d) {
  for (int i = 0; i < d.length(); i++) {
    if (d[i] < '0' || d[i] > '9') {
      return 0;
    }
  }
  int f = stoi(d);
  int a = f % 10000; f /= 10000;
  int b = f % 100; f /= 100;
  bool t = visokosny(a);
  if (a > 2024) {
    return 0;
  }
  if (a == 2024 && ((b == 3 && f > 20) || (b > 3))) {
    return 0;
  }
  if (b <= 0 || b > 12) {
    return 0;
  }
  else if (b != 2 && f > days_in_month[b - 1] || f <= 0) {
    return 0;
  }
  else if (b == 2) {
    if (t) {
      if (f > days_in_month[b - 1]) {
        return 0;
      }
    }
    else {
      if (f > days_in_month[b - 1] - 1) {
        return 0;
      }
    }
  }
}

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

bool razn(string a, string b) {
  int d = stoi(a);
  int c = stoi(b);
  int d1 = d % 10000; d /= 10000;
  int d2 = d % 100; d /= 100;
  int c1 = c % 10000; c /= 10000;
  int c2 = c % 100; c /= 100;
  if (d1 < c1) {
    return 0;
  }
  else if (d1 > c1) {
    return 1;
  }
  else {
    if (d2 < c2) {
      return 0;
    }
    else if (d2 > c2) {
      return 1;
    }
    else {
      if (d < c) {
        return 0;
      }
      else {
        return 1;
      }
    }
  }
}

void input() {
  if (!fopen_s(&t, "t.txt", "a")) {
    cout << "Введите марку автомобиля\n";
    gets_s(automobile.car_model);
    fputs(automobile.car_model, t);
    fputc('\n', t);
    cout << "Введите цвет автомобиля\n";
    string s;
    getline(cin, s);
    while (!regex_match(s, colo)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    strcpy_s(automobile.color, s.c_str());
    fputs(automobile.color, t);
    fputc('\n', t);
    cout << "Введите номер автомобиля\n";
    getline(cin, s);
    while (!regex_match(s, numcar)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    strcpy_s(automobile.number, s.c_str());
    fputs(automobile.number, t);
    fputc('\n', t);
    cout << "Введите дату выпуска автомобиля\n";
    getline(cin, s);
    while (!check_date(s)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    string v = s;
    automobile.date = stoi(s);
    fputs(s.c_str(), t);
    fputc('\n', t);
    cout << "Введите тип кузова автомобиля\n";
    gets_s(automobile.body_type);
    fputs(automobile.body_type, t);
    fputc('\n', t);
    cout << "Введите дату последнего техосмотра автомобиля\n";
    getline(cin, s);
    while (true) {
      if (!check_date(s)) {
        cout << "Некорректный ввод\n";
        getline(cin, s);
      }
      else if (!razn(s, v)) {
        cout << "Некорректный ввод\n";
        getline(cin, s);
      }
      else {
        break;
      }
    }
    automobile.date = stoi(s);
    fputs(s.c_str(), t);
    fputc('\n', t);
    cout << "Введите фамилию владельца автомобиля\n";
    gets_s(automobile.lastname);
    while (!checkfio(automobile.lastname)) {
      cout << "Некорректный ввод\n";
      gets_s(automobile.lastname);
    }
    fputs(automobile.lastname, t);
    fputc('\n', t);
    fclose(t);
  }
  else {
    cout << "Ошибка открытия файла\n";
  }
  cout << '\n';
}


void saydate(int g) { // функция для красивого вывода даты
  if (g < 10) {
    cout << '0' << g << '.';
  }
  else {
    cout << g << '.';
  }
}

void output() {
  if (!fopen_s(&t, "t.txt", "r")) {
    bool g = true;
    while (!feof(t)) {
      fgets(automobile.car_model, 100, t);
      if (feof(t)) {
        if (g) {
          cout << "Файл пуст\n";
        }
        break;
      }
      g = false;
      cout << "Марка автомобиля: " << automobile.car_model;
      fgets(automobile.color, 100, t);
      string s = automobile.color;
      s.erase(s.length() - 1);
      if(!regex_match(s, colo)) {
        cout << "В файле содержится некорректная информация\n";
        cout << "Дальнейшее чтение файла невозможно\n";
        break;
      }
      cout << "Цвет автомобиля: " << s << '\n';
      fgets(automobile.number, 100, t);
      s = automobile.number;
      s.erase(s.length() - 1);
      if(!regex_match(s, numcar)) {
        cout << "В файле содержится некорректная информация\n";
        cout << "Дальнейшее чтение файла невозможно\n";
        break;
      }
      cout << "Номер автомобиля: " << s << '\n';
      fgets(automobile.color, 100, t);
      s = automobile.color;
      s.erase(s.length() - 1);
      if(!check_date(s)) {
        cout << "В файле содержится некорректная информация\n";
        cout << "Дальнейшее чтение файла невозможно\n";
        break;
      }
      string v = s;
      automobile.date = stoi(s);
      cout << "Дата выпуска автомобиля: ";
      saydate(automobile.date / 1000000);
      saydate(automobile.date / 10000 % 100);
      cout << automobile.date % 10000 << '\n';
      fgets(automobile.body_type, 20, t);
      cout << "Тип кузова автомобиля: " << automobile.body_type;
      fgets(automobile.color, 100, t);
      s = automobile.color;
      s.erase(s.length() - 1);
      if(true) {
        if (!check_date(s)) {
          cout << "В файле содержится некорректная информация\n";
          cout << "Дальнейшее чтение файла невозможно\n";
          break;
        }
        else if (!razn(s, v)) {
          cout << "В файле содержится некорректная информация\n";
          cout << "Дальнейшее чтение файла невозможно\n";
          break;
        }
      }
      automobile.date = stoi(s);
      cout << "Дата последнего техосмотра автомобиля: ";
      saydate(automobile.date / 1000000);
      saydate(automobile.date / 10000 % 100);
      cout << automobile.date % 10000 << '\n';
      fgets(automobile.lastname, 100, t);
      s = automobile.lastname;
      if (s[s.length() - 1] == '\n') {
        s.erase(s.length() - 1);
      }
      if(!checkfio(s)) {
        cout << "В файле содержится некорректная информация\n";
        cout << "Дальнейшее чтение файла невозможно\n";
        break;
      }
      cout << "Фамилия владельца автомобиля: " << automobile.lastname;
      cout << '\n';
    }
    fclose(t);
  }
  else {
    cout << "Ошибка открытия файла\n";
  }
  cout << '\n';
}


void search() { // функция для поиска по фамилии владельца
  string own;
  int i = 0;
  cout << "Введите фамилию владельца, по которой будем искать\n";
  cin >> own;
  bool f = false;
  if (!fopen_s(&t, "t.txt", "r")) {
    while (!feof(t)) {
      i++;
      fgets(automobile.car_model, 100, t);
      if (feof(t)) {
        break;
      }
      fgets(automobile.color, 100, t);
      fgets(automobile.number, 100, t);
      fgets(automobile.number, 100, t);
      fgets(automobile.body_type, 100, t);
      fgets(automobile.number, 100, t);
      fgets(automobile.lastname, 100, t);
      string s = automobile.lastname;
      if (s[s.length() - 1] == '\n') {
        s.erase(s.length() - 1);
      }
      if (own == s) {
        cout << "Запись найдена. Номер записи " << i << '\n';
        f = true;
        cout << '\n';
      }
    }
    if (!f) {
      cout << "Такой записи нет\n";
      cout << '\n';
    }
    fclose(t);
  }
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice;
  string c;
  do {
    cout << "Введите:\n";
    cout << "1- для ввода новой записи с клавиатуры в файл\n";
    cout << "2- для чтения и вывода всех записей из файла в консоль\n";
    cout << "3- для поиска записи по фамилии владельца\n";
    cout << "4- для выхода\n";
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
      search();
      break;
    }
    case '4': {
      break;
    }
    default: {
      cout << "Некорректный ввод\n";
    }
    }
  } while (choice != '4');
}
