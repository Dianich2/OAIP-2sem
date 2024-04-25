#pragma once

struct Stack {
	int data;
	Stack* next;
};

void push(Stack*&, int&);
void pop(Stack*&);
void tofile(Stack*);
void fromfile(Stack*&);
void output_clean(Stack*&);
void del_min(Stack*&);