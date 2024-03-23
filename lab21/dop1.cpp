#include <iostream>
#include <math.h>
#include<Windows.h>
#include <conio.h>
#include <string>
#define SIZE 30
using namespace std;

struct student {
  char lastname[20]; // �������
  char firstname[20]; // ���
  char patronimic[20]; // ��������
  int kol_exam; // ���������� ���������
  int* marks; // ������
};

struct student students[SIZE]; // ������� ��������� ��� �������� ���������� � ���������
int currentsize = 0; //������� ���������� �������

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

void input() { // ������� ��� ����� ������
  if (currentsize < SIZE) {
    cout << "������� �������\n";
    gets_s(students[currentsize].lastname);
    while (!checkfio(students[currentsize].lastname)) {
      cout << "������������ ����\n";
      gets_s(students[currentsize].lastname);
    }
    cout << "������� ���\n";
    gets_s(students[currentsize].firstname);
    while (!checkfio(students[currentsize].firstname)) {
      cout << "������������ ����\n";
      gets_s(students[currentsize].firstname);
    }
    cout << "������� ��������\n";
    gets_s(students[currentsize].patronimic);
    while (!checkfio(students[currentsize].patronimic)) {
      cout << "������������ ����\n";
      gets_s(students[currentsize].patronimic);
    }
    cout << "������� ���������� ���������\n";
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
      cout << "������������ ����\n";
      getline(cin, d);
    }
    students[currentsize].kol_exam = stoi(d);
    students[currentsize].marks = new int[students[currentsize].kol_exam]; // ��������� ������ ��� ������ ������
    cout << "������� ������ ��������(�� ����� �� 1 �� 5)\n";
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
          cout << "������������ ����\n";
          cout << "������� ������ �� �����\n";
        }
        else {
          if(stoi(d) < 1 || stoi(d) > 5) {
            cout << "������������ ����\n";
            cout << "������� ������ �� �����\n";
          }
          else {
            break;
          }
        }
        getline(cin, d);
      }
      students[currentsize].marks[i] = stoi(d);
    }
    currentsize++; // ���������� ������� �������
  }
  else {
    cout << "������ ��������� ����������\n";
  }
  cout << '\n';
}


void del() { // ������� ��� �������� ������
  int n; // ���������� ��� �������� ������ ������
  cout << "������� ����� ������, ������� �� ������ �������\n";
  cin >> n; n--;
  if (n >= currentsize or n < 0) {
    cout << "����� ������ ���\n";
  }
  else {
    for (int i = n; i < currentsize - 1; i++) {
      students[i] = students[i + 1];
    }
    currentsize--; // ���������� �������� �������
  }
  cout << '\n';
}

void check() { // ������� ��� �������� ����� ��������� ��������� �� 4 � 5
  int n; // ���������� ��� �������� ������ ������ � ��������, ������� �� ����� ���������
  cout << "������� ����� ������ ��������, ������ �������� �� ������ ���������\n";
  cin >> n; n--;
  if (n >= currentsize or n < 0) {
    cout << "����� ������ ���\n";
  }
  else {
    bool t = true; // ����������-������ ��� �������� �������� �� ���������
    for (int i = 0; i < students[n].kol_exam; i++) {
      if (students[n].marks[i] < 4) { // ���� ������� ������ ������ 4
        cout << "������ ������� �� ��������(� ���� ���� ������ ���� 4)\n";
        t = false;
        break;
      }
    }
    if (t) { // ���� ��� ������ ���� 3
      cout << "���� ������� ��������(� ���� ��� ������ ���� 3)\n";
    }
  }
  cout << '\n';
}

void success() { // ������� ��� �������� ����� ������������
  if (currentsize == 0) {
    cout << "������ ����\n";
    return;
  }
  int kol = 0; // ���������� ��� �������� ���������� ��������� ����������
  bool t = true; // ����������-������ ��� �������� �������� �� ���������
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
  cout << "����� ���������� ��������� " << currentsize << '\n';
  cout << "���������� ���������-���������� " << kol << '\n';
  cout << "������� ������������(��������� ���������� ���������-���������� � ������ ����������) " << ((double)kol / (double)currentsize) * 100 << "%\n";
  cout << '\n';
}

void output() {
  if (currentsize == 0) {
    cout << "������� ���\n";
    return;
  }
  for (int i = 0; i < currentsize; i++) {
    cout << "�������: " << students[i].lastname << '\n';
    cout << "���: " << students[i].firstname << '\n';
    cout << "��������: " << students[i].patronimic << '\n';
    cout << "���������� ������� ���������: " << students[i].kol_exam << '\n';
    cout << "������: ";
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
  char a; // ���������� ��� ���������� ������ �����
  string c;
  do {
    cout << "��������:\n";
    cout << "1-��� ����� ���������� � ����� ��������\n";
    cout << "2-��� �������� ������\n";
    cout << "3-��� �������� ����� ���� ��������� �� 4 � 5\n";
    cout << "4-��� �������� ����� ������������ ���������(������� ���������, ������� ����� ��� �������� �� 4 � 5)\n";
    cout << "5-��� ������ �������\n";
    cout << "6-��� ������\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "������������ ����\n";
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
      cout << "������������ ����\n";
    }
    }
  } while (a != '6');
}
