#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

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
void insert_sort(vector<int>& c, int n) { // сортировка вставками
  for (int i = 1; i < n; i++) {
    int sort = i - 1;
    while (sort > -1 and c[sort] > c[sort + 1]) {
      swap(c[sort], c[sort + 1]);
      sort--;
    }
  }
}

void choice_sort(vector<int>& d, int n) { // сортировка выбором
  for (int i = 0; i < n - 1; i++) {
    int min_poz = i;
    for (int j = i + 1; j < n; j++) {
      if (d[j] < d[min_poz]) {
        min_poz = j;
      }
    }
    if (min_poz != i) {
      swap(d[i], d[min_poz]);
    }
  }
}

void Shell_sorting(vector<int>& a, int n) { // сортировка Шелла
  for (int i = n / 2; i > 0; i /= 2) {
    for (int j = i; j < n; j++) {
      for (int k = j - i; k >= 0 && a[k] > a[k + i]; k -= i) {
        swap(a[k], a[k + i]);
      }
    }
  }
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  srand(time(NULL));
  int n = 1000;
  for (int i = 0; i < 5; i++) {
    vector<int> a(n);
    vector<int> b(n);
    vector<int> c(n);
    vector<int> d(n);
    vector<int> e(n);
    cout << "Время на " << n << " числах\n";
    for (int i = 0; i < n; i++) {
      a[i] = b[i] = c[i] = d[i] = e[i] = rand() % 50000 + 1;
    }
    auto start = chrono::high_resolution_clock::now();
    quick_sort(a, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Быстрая сортировка: " << time.count() << '\n';

    start = chrono::high_resolution_clock::now();
    mergesort(b, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Сортировка слиянием: " << time.count() << '\n';

    start = chrono::high_resolution_clock::now();
    insert_sort(c, n);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Сортировка вставками: " << time.count() << '\n';

    start = chrono::high_resolution_clock::now();
    choice_sort(d, n);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Сортировка выбором: " << time.count() << '\n';

    start = chrono::high_resolution_clock::now();
    Shell_sorting(e, n);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Сортировка Шелла: " << time.count() << '\n';

    cout << '\n';
    n += 1000;
  }
}