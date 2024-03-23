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

FILE* t; // ���� ��� ������ � ������ ������
regex numcar("([A-Z0-9]+([-]?)([A-Z0-9 ]+))");
regex colo("([A-Za-z�-��-�-]+)([A-Za-z�-��-�- ]*)");
union automobiles { // ������� �����������
  char car_model[100]; // ����� ����������
  char color[100]; // ����
  char number[100]; // �����
  int date; // ��� ����
  char body_type[100]; // ��� ������
  char lastname[100]; // ������� ���������
} automobile;



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
    cout << "������� ����� ����������\n";
    gets_s(automobile.car_model);
    fputs(automobile.car_model, t);
    fputc('\n', t);
    cout << "������� ���� ����������\n";
    string s;
    getline(cin, s);
    while (!regex_match(s, colo)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    strcpy_s(automobile.color, s.c_str());
    fputs(automobile.color, t);
    fputc('\n', t);
    cout << "������� ����� ����������\n";
    getline(cin, s);
    while (!regex_match(s, numcar)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    strcpy_s(automobile.number, s.c_str());
    fputs(automobile.number, t);
    fputc('\n', t);
    cout << "������� ���� ������� ����������\n";
    getline(cin, s);
    while (!check_date(s)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    string v = s;
    automobile.date = stoi(s);
    fputs(s.c_str(), t);
    fputc('\n', t);
    cout << "������� ��� ������ ����������\n";
    gets_s(automobile.body_type);
    fputs(automobile.body_type, t);
    fputc('\n', t);
    cout << "������� ���� ���������� ���������� ����������\n";
    getline(cin, s);
    while (true) {
      if (!check_date(s)) {
        cout << "������������ ����\n";
        getline(cin, s);
      }
      else if (!razn(s, v)) {
        cout << "������������ ����\n";
        getline(cin, s);
      }
      else {
        break;
      }
    }
    automobile.date = stoi(s);
    fputs(s.c_str(), t);
    fputc('\n', t);
    cout << "������� ������� ��������� ����������\n";
    gets_s(automobile.lastname);
    while (!checkfio(automobile.lastname)) {
      cout << "������������ ����\n";
      gets_s(automobile.lastname);
    }
    fputs(automobile.lastname, t);
    fputc('\n', t);
    fclose(t);
  }
  else {
    cout << "������ �������� �����\n";
  }
  cout << '\n';
}


void saydate(int g) { // ������� ��� ��������� ������ ����
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
          cout << "���� ����\n";
        }
        break;
      }
      g = false;
      cout << "����� ����������: " << automobile.car_model;
      fgets(automobile.color, 100, t);
      string s = automobile.color;
      s.erase(s.length() - 1);
      if(!regex_match(s, colo)) {
        cout << "� ����� ���������� ������������ ����������\n";
        cout << "���������� ������ ����� ����������\n";
        break;
      }
      cout << "���� ����������: " << s << '\n';
      fgets(automobile.number, 100, t);
      s = automobile.number;
      s.erase(s.length() - 1);
      if(!regex_match(s, numcar)) {
        cout << "� ����� ���������� ������������ ����������\n";
        cout << "���������� ������ ����� ����������\n";
        break;
      }
      cout << "����� ����������: " << s << '\n';
      fgets(automobile.color, 100, t);
      s = automobile.color;
      s.erase(s.length() - 1);
      if(!check_date(s)) {
        cout << "� ����� ���������� ������������ ����������\n";
        cout << "���������� ������ ����� ����������\n";
        break;
      }
      string v = s;
      automobile.date = stoi(s);
      cout << "���� ������� ����������: ";
      saydate(automobile.date / 1000000);
      saydate(automobile.date / 10000 % 100);
      cout << automobile.date % 10000 << '\n';
      fgets(automobile.body_type, 20, t);
      cout << "��� ������ ����������: " << automobile.body_type;
      fgets(automobile.color, 100, t);
      s = automobile.color;
      s.erase(s.length() - 1);
      if(true) {
        if (!check_date(s)) {
          cout << "� ����� ���������� ������������ ����������\n";
          cout << "���������� ������ ����� ����������\n";
          break;
        }
        else if (!razn(s, v)) {
          cout << "� ����� ���������� ������������ ����������\n";
          cout << "���������� ������ ����� ����������\n";
          break;
        }
      }
      automobile.date = stoi(s);
      cout << "���� ���������� ���������� ����������: ";
      saydate(automobile.date / 1000000);
      saydate(automobile.date / 10000 % 100);
      cout << automobile.date % 10000 << '\n';
      fgets(automobile.lastname, 100, t);
      s = automobile.lastname;
      if (s[s.length() - 1] == '\n') {
        s.erase(s.length() - 1);
      }
      if(!checkfio(s)) {
        cout << "� ����� ���������� ������������ ����������\n";
        cout << "���������� ������ ����� ����������\n";
        break;
      }
      cout << "������� ��������� ����������: " << automobile.lastname;
      cout << '\n';
    }
    fclose(t);
  }
  else {
    cout << "������ �������� �����\n";
  }
  cout << '\n';
}


void search() { // ������� ��� ������ �� ������� ���������
  string own;
  int i = 0;
  cout << "������� ������� ���������, �� ������� ����� ������\n";
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
        cout << "������ �������. ����� ������ " << i << '\n';
        f = true;
        cout << '\n';
      }
    }
    if (!f) {
      cout << "����� ������ ���\n";
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
    cout << "�������:\n";
    cout << "1- ��� ����� ����� ������ � ���������� � ����\n";
    cout << "2- ��� ������ � ������ ���� ������� �� ����� � �������\n";
    cout << "3- ��� ������ ������ �� ������� ���������\n";
    cout << "4- ��� ������\n";
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
      search();
      break;
    }
    case '4': {
      break;
    }
    default: {
      cout << "������������ ����\n";
    }
    }
  } while (choice != '4');
}
