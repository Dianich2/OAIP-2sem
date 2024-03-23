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
struct sanatorium_vouchers { // ��������� ���������� �������
  char sanatorium_name[100]; // �������� ���������
  char place_name[100]; // ����� ������������
  char healing_profile[100]; // �������� �������
  int kol_vouchers; // ���������� �������
};


struct sanatorium_vouchers vouchers[SIZE]; // ������� ���������
int currentsize = 0; // ������� ���������� �������
vector<string> healingprofiles; // ������ ��� �������� ���� �������� ��������

void input() { // ������� ��� ����� ���������� � �������
  if (currentsize < SIZE) { // ���� ������ �� ����������
    cout << "������� �������� ���������\n";
    gets_s(vouchers[currentsize].sanatorium_name);
    cout << "������� ����� ������������ ���������\n";
    gets_s(vouchers[currentsize].place_name);
    cout << "������� �������� �������\n";
    gets_s(vouchers[currentsize].healing_profile);
    if (find(healingprofiles.begin(), healingprofiles.end(), vouchers[currentsize].healing_profile) == healingprofiles.end()) {
      healingprofiles.push_back(vouchers[currentsize].healing_profile);
    }
    cout << "������� ���������� ��������� �������\n";
    string s;
    getline(cin, s);
    while (!regex_match(s, kol)) {
      cout << "������������ ����\n";
      getline(cin, s);
    }
    vouchers[currentsize].kol_vouchers = stoi(s);
    currentsize++;
  }
  else { // ���� ����������
    cout << "���������� �������� ����������. ������� ����� �������!\n";
  }
  cout << '\n';
}


void output() { // ������� ��� ������ ���������� � ��������
  if (currentsize > 0) {
    bool t = false;
    cout << setw(20) << "�������� �������" << ' ' << setw(20) << "�������� ���������" << ' ' << setw(20) << "����� ������������" << ' ' << setw(20) << "���������� �������\n" << '\n';
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
    cout << "��� ���������� � ��������\n";
  }
}


void structsort() { // ������� ��� ���������� ��������� �� ��������� ����������
  int size = currentsize; // ���������� ��� ������� ���������
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


void search() { // ������� ������ ��������� �� ��������
  char current_sanatorium[20]; // ���������� ��� �������� �������� �������� ���������
  cout << "������� �������� ���������, ������� � ������� �� ������ �����\n";
  cin >> current_sanatorium;
  bool t = false; // ���������� ������ ��� ������������ ���������� ������� ���������
  for (int i = 0; i < currentsize; i++) {
    if (strcmp(vouchers[i].sanatorium_name, current_sanatorium) == 0) {
      cout << "���������� �� ���� ���������\n";
      cout << "��������: " << vouchers[i].sanatorium_name << '\n';
      cout << "����� ������������: " << vouchers[i].place_name << '\n';
      cout << "�������� �������: " << vouchers[i].healing_profile << '\n';
      cout << "���������� ��������� �������: " << vouchers[i].kol_vouchers << '\n';
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
  char choice; // ���������� ������ �����
  string c;
  do {
    cout << "�������:\n";
    cout << "1- ��� ����� ������ � �������\n";
    cout << "2- ��� ������ ���������� ��� ���� ��������\n";
    cout << "3- ��� ������ ������� �� �������� ���������\n";
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
      cout << "������������ ����\n";
    }
    }
  } while (choice != '4');
}
