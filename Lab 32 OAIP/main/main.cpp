#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <vector>
#include <regex>
using namespace std;
regex checknum("([1-9]+)([0-9]*)");
regex checknum2("[\\-]?[0-9]+");
void quick_sort(vector<int>& e, int first, int last) { // быстрая сортировка
  int middle;
  int l = first, r = last;
  middle = e[(l + r) / 2];
  while (l < r) {
    while (e[l] < middle) l++;
    while (e[r] > middle) r--;
    if (l <= r) {
      swap(e[l], e[r]);
      l++;
      r--;
    }
  }
  if (first < r) quick_sort(e, first, r);
  if (l < last) quick_sort(e, l, last);
}

void merge(vector<int>& a, int left, int middle, int right) { // сортировка слиянием
  int lefts = middle - left + 1;
  int rights = right - middle;

  int* lefta = new int[lefts];
  int* righta = new int[rights];

  for (int i = 0; i < lefts; i++) {
    lefta[i] = a[left + i];
  }
  for (int i = 0; i < rights; i++) {
    righta[i] = a[middle + 1 + i];
  }
  int i = 0, j = 0, k = left;
  while (i < lefts && j < rights) {
    if (lefta[i] <= righta[j]) {
      a[k] = lefta[i];
      i++;
    }
    else {
      a[k] = righta[j];
      j++;
    }
    k++;
  }

  while (i < lefts) {
    a[k] = lefta[i];
    i++;
    k++;
  }
  while (j < rights) {
    a[k] = righta[j];
    j++;
    k++;
  }
}

void mergesort(vector<int>& a, int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;

    mergesort(a, left, middle);
    mergesort(a, middle + 1, right);

    merge(a, left, middle, right);
  }
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  srand(time(NULL));
  int n;
  string t;
  cout << "Введите количество элементов в массивах\n";
  getline(cin, t);
  while (!regex_match(t, checknum)) {
    cout << "Некорректный ввод\n";
    getline(cin, t);
  }
  n = stoi(t);
  vector<int> a(n);
  vector<int> b(n);
  vector<int> c1;
  vector<int> c2;
  cout << "Введите элементы массива А\n";
  for (int i = 0; i < n; i++) {
    getline(cin, t);
    while (!regex_match(t, checknum2)) {
      cout << "Некорректный ввод\n";
      getline(cin, t);
    }
    a[i] = stoi(t);
  }
  cout << "Введите элементы массива B\n";
  for (int i = 0; i < n; i++) {
    getline(cin, t);
    while (!regex_match(t, checknum2)) {
      cout << "Некорректный ввод\n";
      getline(cin, t);
    }
    b[i] = stoi(t);
  }
    for (int i = 0; i < n; i++) {
      if (a[i] % 2 != 0) {
        c1.push_back(a[i]);
        c2.push_back(a[i]);
      }
    }
    for (int i = 0; i < n; i++) {
      if (b[i] % 2 == 0) {
        c1.push_back(b[i]);
        c2.push_back(b[i]);
      }
    }
    cout << "Элементы массива C\n";
    for (int i = 0; i < c1.size(); i++) {
      cout << c1[i] << ' ';
    }
    cout << '\n';
    auto start = chrono::high_resolution_clock::now();
    quick_sort(c1, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Быстрая сортировка время: " << time.count() << '\n';
    cout << "Массива С после сортировки Хоара\n";
    for (int i = 0; i < c1.size(); i++) {
      cout << c1[i] << ' ';
    }
    cout << '\n';
    start = chrono::high_resolution_clock::now();
    mergesort(c2, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Сортировка слиянием время: " << time.count() << '\n';
    cout << "Массива С после сортировки слиянием\n";
    for (int i = 0; i < c2.size(); i++) {
      cout << c2[i] << ' ';
    }
    cout << '\n';
}