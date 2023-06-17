#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

#define ITEMS 4
#define MAX 8

using namespace std;
using namespace std::chrono;

// algorytm silowy

void decToBin(int y, int arr[], int size)
{
	int x = y;
	for (int i = 0; i < size; i++)
	{
		arr[i] = x % 2;
		x /= 2;
	}
}

int current(int encrypted[], int val[], int size)
{
	int w = 0;
	for (int i = 0; i < size; i++)
	{
		w += encrypted[i] * val[i];
	}
	return w;
}

vector<int> bruteForce(int w[], int p[], int total, int n)
{
	int max = 0, solution = 0;
	vector<int> sol;
	int* encrypt = new int[n];
	int* best_binary = new int[n];
	if (n == 0 || total == 0)
		return sol;
	for (int x = 1; x < (int)pow(2, n); x++)
	{
		decToBin(x, encrypt, n);
		if (current(encrypt, w, n) <= total)
		{
			if (current(encrypt, p, n) > max)
			{
				max = current(encrypt, p, n);
				std::copy(encrypt, encrypt + n, best_binary);
				solution = x;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (best_binary[i] == 1)
			sol.push_back(i + 1);
	}
	delete[] best_binary;
	delete[] encrypt;
	return sol;
}

// algorytm zachlanny

void heapify(int arr[], double coef[], int n, int i)
{
	int min = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && coef[left] < coef[min])
		min = left;
	if (right < n && coef[right] < coef[min])
		min = right;
	if (min != i)
	{
		swap(coef[i], coef[min]);
		swap(arr[i], arr[min]);
		heapify(arr, coef, n, min);
	}
}

void heapsort(int arr[], double coef[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, coef, n, i);
	}
	for (int i = 1; i < n; i++)
	{
		swap(coef[0], coef[n - i]);
		swap(arr[0], arr[n - i]);
		heapify(arr, coef, n - i, 0);
	}
}

int greedy(int w[], int p[], int total, int n)
{
	double* coef = new double[n];
	for (int i = 0; i < n; i++)
	{
		coef[i] = (double)p[i] / w[i];
	}
	double* coef_copy = new double[n];
	std::copy(coef, coef + n, coef_copy);
	heapsort(w, coef_copy, n);
	heapsort(p, coef, n);
	int i = 0;
	int full = 0;
	do {
		total -= w[i];
		full += p[i];
		i++;
	} while (i < n && total >= w[i]);
	delete[] coef;
	delete[] coef_copy;
	return full;
}

//algorytm programowania dynamicznego

void fill(int** m, int w[], int p[])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (i == 0 || j == 0)
				m[i][j] = 0;
			else if (w[i - 1] > j)
				m[i][j] = m[i - 1][j];
			else
				m[i][j] = std::max(m[i - 1][j], m[i - 1][j - w[i - 1]] + p[i - 1]);
		}
	}
}

vector<int> dpSolution(int** m, int w[], int j, int i)
{
	vector<int> sub;
	while (i != 0)
	{
		if (m[i][j] > m[i - 1][j]) 
		{
			sub.push_back(i);
			j -= w[i - 1];
		}
		i--;
	}
	return sub;
}

int main()
{
	int w[ITEMS] = { 2, 1, 4, 4 };
	int p[ITEMS] = { 4, 3, 6, 8 };
	// macierz programowania dynamicznego
	int** m = new int*[ITEMS + 1];
	for (int i = 0; i < 5; i++)
	{
		m[i] = new int[MAX + 1];
	}
	fill(m, w, p);
	vector<int> s = dpSolution(m, w, MAX, ITEMS);
	for (int i = 0; i < s.size(); i++)
	{
		cout << "x" << s[i] << " ";
	}
}