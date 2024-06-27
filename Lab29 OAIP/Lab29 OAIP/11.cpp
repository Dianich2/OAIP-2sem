#include <iostream>;
#include <Windows.h>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

vector<int> nodes(1000, -1000000);
vector<string> words(1000, "");
regex checknum("([\\-]?)([0-9]+)");
int Maxsize = 0;
int Maxlevel = -1;
struct Node{
	int key;
	string word;
	Node* left, * right;
};

Node* root = NULL;

Node* insert(Node *&t, int key, string word, char prev, int level, int current, vector<int> &nod, vector<string> &wor, int &Maxs, int &Maxl) {
  if (t == NULL) {
    t = new Node;
    t->key = key;
    t->word = word;
    nod[current] = key;
    wor[current] = word;
    if (level > Maxlevel) {
      Maxlevel = level;
      Maxsize += pow(2, level);
    }
    if (level > Maxl) {
      Maxl = level;
      Maxs += pow(2, level);
    }
    t->left = NULL;
    t->right = NULL;
  }
  else if (key < t->key) {
    if (prev == '0') {
      current = 1;
    }
    else {
      current = current * 2 + 1;
    }
    t->left = insert(t->left, key, word, 'l', level + 1, current, nod, wor, Maxs, Maxl);
  }
  else if(key > t->key){
     if (prev == '0') {
      current = 2;
    }
     else {
       current = current * 2 + 2;
     }
    t->right = insert(t->right, key, word, 'r', level + 1, current, nod, wor, Maxs, Maxl);
  }
  return t;
}

void clear(Node* &t) {
  if (t != NULL) {
    clear(t->left);
    clear(t->right);
    delete t;
  }
}

void view() //����� ������ 
{
  if (nodes[0] == -1000000)
  {
    cout << "������ ������\n";
  }
  int i = 0, level = 0;
  while (i < Maxsize) {
    int l = pow(2, level);
    cout << "������� " << level << '\n';
    for (int j = 0; j < l; j++) {
      if (nodes[i] == -1000000) {
        cout << "�����  ";
      }
      else {
        cout << nodes[i] << " -> " << words[i] << ' ';
      }
      i++;
    }
    cout << '\n';
    level++;
  }
  return;
}

void search(int key) {
  for (int i = 0; i < Maxsize; i++) {
    if (nodes[i] == key) {
      cout << "������� ������\n";
      cout << nodes[i] << " -> " << words[i] << '\n';
      return;
    }
  }
  cout << "������� �� ������\n";
}

int view(Node* t, int level) //����� ������ 
{
  if (t)
  {
    view(t->right, level + 1);	//����� ������� ���������
    for (int i = 0; i < level; i++)
      cout << "   ";
    int tm = t->key;
    cout << tm << ' ';
    cout << t->word << '\n';
    view(t->left, level + 1);	//����� ������ ���������
    return 0;
  }
  return 1;
}

void del(Node* t, int key) {
  vector<int> buf(1000, -1000000);
  vector<string> bufw(1000, "");
  int currentmaxsize = 0;
  int currentmaxlevel = -1;
  bool f = false;
  for (int i = 0; i < Maxsize; i++) {
    if (nodes[i] == key) {
      nodes[i] = -1000000;
      words[i] = "";
      f = true;
    }
  }
  if (!f) {
    cout << "������� �� ������\n";
    return;
  }
  Node* temp = NULL;
  for (int i = 0; i < Maxsize; i++) {
    if (nodes[i] != -1000000) {
      insert(temp, nodes[i], words[i], '0', 0, 0, buf, bufw, currentmaxsize, currentmaxlevel);
    }
  }
  root = temp;
  nodes = buf;
  words = bufw;
  Maxsize = currentmaxsize;
  Maxlevel = currentmaxlevel;
}

void countEl(int n) {
  if (n > Maxlevel || n < 0) {
    cout << "������ ������ ���\n";
    return;
  }
  int power = 0;
  int cou = 0;
  for (int i = 0; i <= n; i++) {
    power += pow(2, i);
  }
  int start = pow(2, n) - 1;
  for (int i = start; i < power; i++) {
    if (nodes[i] != -1000000) {
      cout << nodes[i] << " -> " << words[i] << ' ';
      cou++;
    }
  }
  cout << '\n';
  cout << "�� ���� ������ �������� " << cou << " ���������\n";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
  char choice;
  string a;
    do {
    cout << "�������:\n";
    cout << "1 - ��� ���������� ��������\n";
    cout << "2 - ��� �������� ��������\n";
    cout << "3 - ��� ������ ���� ���������\n";
    cout << "4 - ��� ������ �� �����\n";
    cout << "5 - ��� ������� ������\n";
    cout << "6 - ��� �������� ����� ������ n-�� ������\n";
    cout << "7 - ��� ������ \n";
    getline(cin, a);
    while (a.length() != 1) {
      cout << "������������ ����\n";
      getline(cin, a);
    }
    choice = a[0];
    switch (choice) {
    case '1': {
      int n;
      cout << "������� ���� ��� ����������\n";
      getline(cin, a);
      while (!regex_match(a, checknum)) {
        cout << "������������ ����\n";
        getline(cin, a);
      }
      n = stoi(a);
      cout << "������� ������ ��� ����� �����\n";
      getline(cin, a);
      insert(root, n, a, '0', 0, 0, nodes, words, Maxsize, Maxlevel);
      break;
    }

    case '2': {
      int n;
      cout << "������� ���� ��� ��������\n";
      getline(cin, a);
      while (!regex_match(a, checknum)) {
        cout << "������������ ����\n";
        getline(cin, a);
      }
      n = stoi(a);
      del(root, n);
      break;
    }

    case '3': {
      if (!root) {
        cout << "������ ������\n";
      }
      else {
       view(root, 0);
      }
      break;
    }

    case '4': {
      int n;
      cout << "������� ���� ��� ������\n";
      getline(cin, a);
      while (!regex_match(a, checknum)) {
        cout << "������������ ����\n";
        getline(cin, a);
      }
      n = stoi(a);
      search(n);
      break;
    }

    case '5': {
      clear(root);
      Node* rt = NULL;
      root = rt;
      for (int i = 0; i < Maxsize; i++) {
        nodes[i] = -1000000;
      }
      Maxsize = 0;
      Maxlevel = -1;
      break;
    }

    case '6': {
      int n;
      cout << "������� ����� ������\n";
      getline(cin, a);
      while (!regex_match(a, checknum)) {
        cout << "������������ ����\n";
        getline(cin, a);
      }
      n = stoi(a);
      countEl(n);
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