#include <iostream>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <algorithm>
#define SIZE 8
using namespace std;


struct time_s { // ��������� ��� ������� ������������
  int hour; // ��������� ��� ���������� �����
  int min; // ���������� ��� ���������� �����
  int sec; // ���������� ��� ���������� ������
};


struct TRAIN { // ��������� �������
  char place_name[20]; // �������� ������ ����������
  char train_num[20]; // ����� ������
  time_s train_time; // ������� ��������� ������� ����������� �������� ������
};


struct TRAIN trains[SIZE]; // ���� ������� ��������� �������


void saytime(int i) { // ������� ��� ��������� ������ �������
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
  cout << "������� ���������� � ������ ������\n";
  for (int i = 0; i < SIZE; i++) { // ���� ��� ���������� ���������� ��� ���� �������
    cout << "������� �������� ������ ���������� " << i + 1 << " ������\n";
    cin >> trains[i].place_name;
    cout << "������� ����� " << i + 1 << " ������\n";
    cin >> trains[i].train_num;
    while (true) { // �������� ������������ ����� �������
      cout << "������� ����� ����������� � �������(����(������)������(������)�������)" << i + 1 << " ������\n";
      cin >> trains[i].train_time.hour >> trains[i].train_time.min >> trains[i].train_time.sec;
      if (trains[i].train_time.hour < 0 or trains[i].train_time.hour > 23 or trains[i].train_time.min > 59 or trains[i].train_time.min < 0 or trains[i].train_time.sec > 59 or trains[i].train_time.sec < 0) {
        cout << "������������ ����\n";
      }
      else {
        break;
      }
    }
  }
  time_s currenttime; // ��������� ��� �������� �������-���������
  while (true) { // �������� ������������ ����� �������
    cout << "\n������� �����, ��� ���������� �������, ������� ������������ ����� ����\n";
    cin >> currenttime.hour;
    cin >> currenttime.min;
    cin >> currenttime.sec;
    if (currenttime.hour < 0 or currenttime.hour > 23 or currenttime.min > 59 or currenttime.min < 0 or currenttime.sec > 59 or currenttime.sec < 0) {
      cout << "������������ ����\n";
    }
    else {
      break;
    }
  }

  // ���������� ���������
  int len = SIZE; // ���������� ����� ���������
  bool t = false; // ���������� ��� �������� ������� ������� ������� ���������
  while (len--) { // ���� ����� �� 0
    t = false;
    for (int i = 0; i < SIZE; i++) {
      if (strcmp(trains[i].place_name, trains[i + 1].place_name) > 0) { // ���� ������� �������� ����������������� ������, �� ������ �������
        swap(trains[i], trains[i + 1]);
        t = true;
      }
    }
    if (!t) {
      break;
    }
  }

  t = false; // ���������� ��� ������ ���������� �������
  for (int i = 0; i < SIZE; i++) {
    if ((trains[i].train_time.hour > currenttime.hour)
      or (trains[i].train_time.hour == currenttime.hour and trains[i].train_time.min > currenttime.min)
      or (trains[i].train_time.hour == currenttime.hour and trains[i].train_time.min == currenttime.min and trains[i].train_time.sec > currenttime.sec)) {
      cout << "����� � ������� " << trains[i].train_num << " ������������ � " << trains[i].place_name << " � ";
      saytime(i);
      t = true;
    }
  }
  if (!t) { // ���� ������ �� �������
    cout << "����� ������� ���\n";
  }
}
