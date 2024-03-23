#include <iostream>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <algorithm>
#define SIZE 8
using namespace std;


struct time_s { // структура для времени отправления¬
  int hour; // переменая для количества часов
  int min; // переменная для количества минут
  int sec; // переменная для количества секунд
};


struct TRAIN { // структура поездов
  char place_name[20]; // название пункта назначения
  char train_num[20]; // номер поезда
  time_s train_time; // текущая структура времени отправления текущего поезда
};


struct TRAIN trains[SIZE]; // наша текущая структура поездов


void saytime(int i) { // функция для красивого вывода времени
  if (trains[i].train_time.hour < 10) {
    cout << '0' << trains[i].train_time.hour << ':';
  }
  else {
    cout << trains[i].train_time.hour << ':';
  }
  if (trains[i].train_time.min < 10) {
    cout << '0' << trains[i].train_time.min << ':';
  }
  else {
    cout << trains[i].train_time.min << ':';
  }
  if (trains[i].train_time.sec < 10) {
    cout << '0' << trains[i].train_time.sec;
  }
  else {
    cout << trains[i].train_time.sec;
  }
  cout << '\n' << '\n';
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  cout << "Введите информацию о каждом поезде\n";
  for (int i = 0; i < SIZE; i++) { // цикл для считывания информации обо всех поездах
    cout << "Введите название пункта назначения " << i + 1 << " поезда\n";
    cin >> trains[i].place_name;
    cout << "Введите номер " << i + 1 << " поезда\n";
    cin >> trains[i].train_num;
    while (true) { // проверка корректности ввода времени
      cout << "Введите время отправления в формате(часы(пробел)минуты(пробел)секунды)" << i + 1 << " поезда\n";
      cin >> trains[i].train_time.hour >> trains[i].train_time.min >> trains[i].train_time.sec;
      if (trains[i].train_time.hour < 0 or trains[i].train_time.hour > 23 or trains[i].train_time.min > 59 or trains[i].train_time.min < 0 or trains[i].train_time.sec > 59 or trains[i].train_time.sec < 0) {
        cout << "Некорректный ввод\n";
      }
      else {
        break;
      }
    }
  }
  time_s currenttime; // структура для текущего времени-ориентира
  while (true) { // проверка корректности ввода времени
    cout << "\nВведите время, для вычисления поездов, которые отправляются после него\n";
    cin >> currenttime.hour;
    cin >> currenttime.min;
    cin >> currenttime.sec;
    if (currenttime.hour < 0 or currenttime.hour > 23 or currenttime.min > 59 or currenttime.min < 0 or currenttime.sec > 59 or currenttime.sec < 0) {
      cout << "Некорректный ввод\n";
    }
    else {
      break;
    }
  }

  // сортировка структуры
  int len = SIZE; // переменная длины структуры
  bool t = false; // переменная для проверки наличия неверно стоящих элементов
  while (len--) { // пока длина не 0
    t = false;
    for (int i = 0; i < SIZE; i++) {
      if (strcmp(trains[i].place_name, trains[i + 1].place_name) > 0) { // если текущее название лексикографически больше, то меняем местами
        swap(trains[i], trains[i + 1]);
        t = true;
      }
    }
    if (!t) {
      break;
    }
  }

  t = false; // переменная для поиска подходящих поездов
  for (int i = 0; i < SIZE; i++) {
    if ((trains[i].train_time.hour > currenttime.hour)
      or (trains[i].train_time.hour == currenttime.hour and trains[i].train_time.min > currenttime.min)
      or (trains[i].train_time.hour == currenttime.hour and trains[i].train_time.min == currenttime.min and trains[i].train_time.sec > currenttime.sec)) {
      cout << "Поезд с номером " << trains[i].train_num << " отправляется в " << trains[i].place_name << " в ";
      saytime(i);
      t = true;
    }
  }
  if (!t) { // если поезда не найдены
    cout << "Таких поездов нет\n";
  }
}
