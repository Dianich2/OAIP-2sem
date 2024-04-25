#include <iostream>
#include<Windows.h>
#include <conio.h>
#include "func.h"
#include <string>
using namespace std;

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // ���������� ��� ������ �����
  Stack* mystack = nullptr;
  do {
    cout << "�������:\n";
    cout << "1 - ��� ���������� �������� � ����\n";
    cout << "2 - ��� ���������� �������� �� �����\n";
    cout << "3 - ��� ������ � ����\n";
    cout << "4 - ��� ������ �� �����\n";
    cout << "5 - ��� ������ ����� � ��������\n";
    cout << "6 - ��� �������� ������� �������������� ��������\n";
    cout << "7 - ��� ������\n";
    cin >> choice;
    switch (choice) {
    case '1': {
      int n;
      cout << "������� �����, ������� ������ �������� � ����\n";
      cin >> n;
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
      del_plus(mystack);
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