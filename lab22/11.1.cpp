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

struct lambard { // ��������� �������� ���������� � ��������
  char lastname[100];
  char productname[100];
  double cost;
  double zalogsum;
  date_of_delivery currentdate;
  int shelf_life;
};


struct lambard currentlambard[SIZE]; // ������� ��������� �������� ���������� � ��������
int currentsize = 0; // ���������� ������� � ���������


bool checkfio(string f) {
  bool t = false;
  for (int i = 0; i < f.length(); i++) {
    if (i == 0) {
      if ((f[0] >= 'A' && f[0] <= 'Z') || (f[0] >= '�' && f[0] <= '�')) {
        t = true;
        continue;
      }
      else {
        return 0;
      }
    }
    else if ((f[i] >= 'A' && f[i] <= 'Z') || (f[i] >= '�' && f[i] <= '�') && t) {
      if (f[i - 1] == '-') {
        continue;
      }
      else {
        return 0;
      }
    }
    else if ((f[i] >= 'a' && f[i] <= 'z') || (f[i] >= '�' && f[i] <= '�')) {
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

bool visokosny(int y) { // ������� ��� ����������� ������������ ����
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

void input() { // ������� ��� ����� ���������� � ����� ������
  if (currentsize < SIZE) {
    cout << "������� ������� �������\n";
    gets_s(currentlambard[currentsize].lastname);
    while (!checkfio(currentlambard[currentsize].lastname)) {
      cout << "������������ ����\n";
      gets_s(currentlambard[currentsize].lastname);
    }
    cout << "������� ������������ ������\n";
    gets_s(currentlambard[currentsize].productname);
    cout << "������� ��������� ���������\n";
    string s;
    getline(cin, s);
    while(!regex_match(s.c_str(), costs)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    currentlambard[currentsize].cost = stof(s);
    cout << "������� �����, �������� ��� �����\n";
    getline(cin, s);
    while (!regex_match(s.c_str(), costs)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    currentlambard[currentsize].zalogsum = stof(s);
    cout << "������� ���� ����� � �������(��������)\n";
    getline(cin, s);
    while (!check_date(s, currentlambard[currentsize])) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    cout << "������� ���� ��������(���������� ����)\n";
    getline(cin, s);
    while (!regex_match(s.c_str(), da)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    currentlambard[currentsize].shelf_life = stoi(s);
    currentsize++;
  }
  else {
    cout << "���������� ������� ����� ������. ������� ����� �������.\n";
  }
  cout << '\n';
}


void saydate(int j) { // ������� ��� ��������� ������ ����
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

void output() { // ������� ��� ������ ���������� � ��������
  if (currentsize > 0) {
    for (int i = 0; i < currentsize; i++) {
      cout << "������� �������: " << currentlambard[i].lastname << '\n';
      cout << "������������ ������: " << currentlambard[i].productname << '\n';
      cout << "��������� ���������: " << currentlambard[i].cost << '\n';
      cout << "�����, �������� ��� �����: " << currentlambard[i].zalogsum << '\n';
      cout << "���� �����: ";
      saydate(i);
      cout << "���� ��������: " << currentlambard[i].shelf_life << '\n';
      cout << '\n';
    }
  }
  else {
    cout << "������� ���\n";
    cout << '\n';
  }
}


void del() { // ������� ��� �������� ������
  int n; // ���������� ��� ������ ������ 
  cout << "������� ����� ������, ������� ������ �������\n";
  cin >> n; n--;
  if (n < 0 or n >= currentsize) {
    cout << "����� ������ ���\n";
  }
  else {
    for (int i = n; i < currentsize; i++) {
      currentlambard[i] = currentlambard[i + 1];
    }
    currentsize--;
  }
  cout << '\n';
}


void search() { // ������� ������ �� ����� ��������
  int n; // ���������� ��� �������� ����� ��������
  cout << "������� ���� ��������, �� �������� ����� ������ ����(� ����)\n";
  string s;
  getline(cin, s);
  while (!regex_match(s.c_str(), da)) {
    cout << "������������ ����\n";
    getline(cin, s);
  }
  n = stoi(s);
  bool t = false; // ����������-������ ��� ������������ ���������� ������ ������
  for (int i = 0; i < currentsize; i++) {
    if (currentlambard[i].shelf_life == n) {
      cout << "������� �������: " << currentlambard[i].lastname << '\n';
      cout << "������������ ������: " << currentlambard[i].productname << '\n';
      cout << "��������� ���������: " << currentlambard[i].cost << '\n';
      cout << "�����, �������� ��� �����: " << currentlambard[i].zalogsum << '\n';
      cout << "���� �����: ";
      saydate(i);
      cout << "���� ��������: " << currentlambard[i].shelf_life << '\n';
      cout << '\n';
      t = true;
    }
  }
  if (!t) {
    cout << "���������� �� �������\n";
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
    cout << "�������:\n";
    cout << "1- ��� ����� ����� ������\n";
    cout << "2- ��� ������ ���� �������\n";
    cout << "3- ��� �������� ������\n";
    cout << "4- ��� ������ �� ����� ��������\n";
    cout << "5- ��� ������\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "������������ ����\n";
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
