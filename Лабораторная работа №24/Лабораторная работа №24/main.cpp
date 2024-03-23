#include <iostream>
#include<Windows.h>
#include <conio.h>
#include "func.h"
#include <string>
#include <regex>
using namespace std;

extern regex checknum("[\\-]?[0-9]+");

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // ���������� ��� ������ �����
  string c;
  Stack *mystack = nullptr;
  do {
    cout << "�������:\n";
    cout << "1 - ��� ���������� �������� � ����\n";
    cout << "2 - ��� ���������� �������� �� �����\n";
    cout << "3 - ��� ������ � ����\n";
    cout << "4 - ��� ������ �� �����\n";
    cout << "5 - ��� ������ ����� � ��������\n";
    cout << "6 - ��� �������� ��������� �����, ������� ������ 3\n";
    cout << "7 - ��� ������\n";
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
      int n;
      cout << "������� �����, ������� ������ �������� � ����\n";
      string b;
      getline(cin, b);
      while (!regex_match(b, checknum)) {
        cout << "������������ ����\n";
        getline(cin, b);
      }
      n = stoi(b);
      push(mystack, n);
      break;
    }
    case '2': {
      pop(mystack);
      break;
    }
    case '3': {
      tofile(mystack);
      break;
    }
    case '4': {
      fromfile(mystack);
      break;
    }
    case '5': {
      output_clean(mystack);
      break;
    }
    case '6': {
      del_3(mystack);
      break;
    }
    case '7': {
      break;
    }
    default: {
      cout << "������������ ����\n";
      break;
    }
    }
  } while (choice != '7');
}