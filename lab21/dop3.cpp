#include <iostream>
#include <iomanip>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <regex>
#define SIZE 30
using namespace std;

regex kol("[1-9]{1}[0-9]*");
struct sanatorium_vouchers { // структура санаторных путевок
  char sanatorium_name[100]; // название санатория
  char place_name[100]; // место расположения
  char healing_profile[100]; // лечебный профиль
  int kol_vouchers; // количество путевок
};


struct sanatorium_vouchers vouchers[SIZE]; // текущая структура
int currentsize = 0; // текущее количество путевок
vector<string> healingprofiles; // вектор для хранения всех лечебных профилей

void input() { // функция для ввода информации о путевке
  if (currentsize < SIZE) { // если массив не переполнен
    cout << "Введите название санатория\n";
    gets_s(vouchers[currentsize].sanatorium_name);
    cout << "Введите место расположения санатория\n";
    gets_s(vouchers[currentsize].place_name);
    cout << "Введите лечебный профиль\n";
    gets_s(vouchers[currentsize].healing_profile);
    if (find(healingprofiles.begin(), healingprofiles.end(), vouchers[currentsize].healing_profile) == healingprofiles.end()) {
      healingprofiles.push_back(vouchers[currentsize].healing_profile);
    }
    cout << "Введите количество доступных путевок\n";
    string s;
    getline(cin, s);
    while (!regex_match(s, kol)) {
      cout << "Некорректный ввод\n";
      getline(cin, s);
    }
    vouchers[currentsize].kol_vouchers = stoi(s);
    currentsize++;
  }
  else { // если переполнен
    cout << "Невозможно добавить информацию. Слишком много путевок!\n";
  }
  cout << '\n';
}


void output() { // функция для вывода информации о путевках
  if (currentsize > 0) {
    bool t = false;
    cout << setw(20) << "Лечебный профиль" << ' ' << setw(20) << "Название санатория" << ' ' << setw(20) << "Место расположения" << ' ' << setw(20) << "Количество путевок\n" << '\n';
    for (int i = 0; i < healingprofiles.size(); i++) {
      cout << setw(20) << healingprofiles[i] << ' ';
      t = false;
      for (int j = 0; j < currentsize; j++) {
        if (vouchers[j].healing_profile == healingprofiles[i]) {
          if (t) {
            cout << setw(21) << setfill(' ') << ' ';
          }
          cout << setw(20) << vouchers[j].sanatorium_name << ' ' << setw(20) << vouchers[j].place_name << ' ' << setw(10) << vouchers[j].kol_vouchers << '\n';
          t = true;
        }
      }
    }
  }
  else {
    cout << "Нет информации о путевках\n";
  }
}


void structsort() { // функция для сортировки структуры по названиям санаториев
  int size = currentsize; // переменная для размера структуры
  if (size > 1) {
    bool t = false;
    while (size--) {
      t = false;
      for (int i = 0; i < size; i++) {
        if (strcmp(vouchers[i].sanatorium_name, vouchers[i + 1].sanatorium_name) > 0) {
          swap(vouchers[i], vouchers[i + 1]);
          t = true;
        }
      }
      if (!t) {
        break;
      }
    }
  }
}


void search() { // функция поиска санатория по названию
  char current_sanatorium[20]; // переменная для хранения названия искомого санатория
  cout << "Введите название санатория, путевки в который вы хотите найти\n";
  cin >> current_sanatorium;
  bool t = false; // переменная флажок для отслеживания нахождения нужного санатория
  for (int i = 0; i < currentsize; i++) {
    if (strcmp(vouchers[i].sanatorium_name, current_sanatorium) == 0) {
      cout << "Информация об этом санатории\n";
      cout << "Название: " << vouchers[i].sanatorium_name << '\n';
      cout << "Место расположения: " << vouchers[i].place_name << '\n';
      cout << "Лечебный профиль: " << vouchers[i].healing_profile << '\n';
      cout << "Количество доступных путевок: " << vouchers[i].kol_vouchers << '\n';
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
  char choice; // переменная выбора опции
  string c;
  do {
    cout << "Введите:\n";
    cout << "1- для ввода данных о путевке\n";
    cout << "2- для вывода информации обо всех путевках\n";
    cout << "3- для поиска путевки по названию санатория\n";
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
      structsort();
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
