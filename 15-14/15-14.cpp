// 15-7,сортировки.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <ctime>             
#include <stdlib.h>
#include <iostream>
using namespace std;
void dubbleSort1(int A[], int size)//Перестановка элементов в шейкерной сортировке выполняется аналогично пузырьковой, т. е. два соседних элемента при необходимости меняются местами.  
{
	int i, j, count, key;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - 1; j++)
		{
			key = j + 1;
			count = A[key];
			if (A[j] > A[key])
			{
				A[key] = A[j];
				A[j] = count;
			}
		}
	}

}

void insertSort(int *A, int size)
{
	int t, i, j;
	for (i = 1; i < size; i++)
	{
		t = A[i];
		for (j = i - 1; j >= 0 && A[j] > t; j--)
			A[j + 1] = A[j];
		A[j + 1] = t;
	}
}

//------------------------------

int getHoarBorder(int A[], int sm, int em)//разбиваем массив
										  //Здесь A[] – исходный массив чисел, sm –  индекс первого элемента массива, em –  индекс последнего (последний элемент правой части).
{
	int i = sm - 1, j = em + 1;
	int brd = A[sm];
	int buf;
	while (i < j)
	{
		while (A[--j]> brd);
		while (A[++i]< brd);
		if (i < j)
		{
			buf = A[j];
			A[j] = A[i];
			A[i] = buf;
		};
	}
	return j;
}
int* sortHoar(int A[], int sm, int em)//ну а тут уже сама сортировка
{
	if (sm < em)
	{
		int hb = getHoarBorder(A, sm, em);
		sortHoar(A, sm, hb);
		sortHoar(A, hb + 1, em);
	}
	return A;
};

//------------------------------
int getRandKey(int reg = 0)     // генерация случайных ключей
{
	if (reg > 0)
		srand((unsigned)time(NULL));
	int rmin = 0;
	int rmax = 100000;
	return (int)(((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin);
}
//------------------------------
int main()
{
	setlocale(LC_CTYPE, "Russian");
	const int N = 50001;
	int k[N], f[N];
	clock_t  t1, t2;
	getRandKey(1);
	for (int i = 0; i < N; i++)
		f[i] = getRandKey(0);
	for (int n = 10000; n <= N; n += 10000)
	{
		cout << "n = " << n << endl;
		cout << "SortPuzirek(пузырек) ";
		memcpy(k, f, n * sizeof(int));//копирует байты блока памяти,во второй блок
		t1 = clock();//clock-возвращает количество тактов,прошедших с начала запуска
		insertSort(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "insertSort(вставка)   ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		dubbleSort1(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl << endl;
		cout << "SortHoar(Хоар)   ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		sortHoar(k, 0, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl << endl;
	}
	return 0;
}




