#ifndef MYCALLINES_H
#define MYCALLINES_H


#include <iostream>
#include <glad\glad.h>


using namespace std;

int myAbs(int a, int b) {
	if (a > b) return a - b;
	return b - a;
}

void mySwap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void line(int x0, int x1, int y0, int y1, int& count, int (&points)[12000]) {
	bool steep = myAbs(y1, y0) > myAbs(x1, x0);
	if (steep) {
		mySwap(x0, y0);
		mySwap(x1, y1);
	}
	if (x0 > x1) {
		mySwap(x0, x1);
		mySwap(y0, y1);
	}
	int deltax = x1 - x0;
	int deltay = myAbs(y1, y0);
	int error = deltax / 2;
	int ystep = (y0 < y1) ? 1 : -1;
	int y = y0;
	for (int x = x0; x < x1; x++) {
		if (steep) {
			points[count] = y;
			points[count + 1] = x;
		}
		else {
			points[count] = x;
			points[count + 1] = y;
		}
		count += 2;
		error = error - deltay;
		if (error < 0) {
			y += ystep;
			error += deltax;
		}
	}
}



void myCalLines(int* A, int* B, int* C, int& count, int (&points)[12000]) {
	//int count = 0;
	line(A[0], B[0], A[1], B[1], count, points);
	line(A[0], C[0], A[1], C[1], count, points);
	line(B[0], C[0], B[1], C[1], count, points);
}


#endif // !MYCALLINES_H
