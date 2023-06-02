#include <iostream>
#include <cmath>
using namespace std;

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

int bruteForce(int w[], int p[], int total, int n)
{
	int max = 0, solution = 0;
	int* encrypt = new int[n];
	if (n == 0 || total == 0)
		return 0;
	for (int x = 1; x < (int)pow(2, n); x++)
	{
		decToBin(x, encrypt, n);
		if (current(encrypt, w, n) <= total)
		{
			if (current(encrypt, p, n) > max)
			{
				max = current(encrypt, p, n);
				solution = x;
			}
		}
	}
	delete[] encrypt;
	return max;
}

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

int main()
{
	int w[4] = { 2, 2, 4, 4 };
	int p[4] = { 5, 3, 6, 12 };
	int max = 8;
	cout << "Wartosc brute force: " << greedy(w, p, max, sizeof(w) / sizeof(int)) << "\n";
	cout << "Wartosc zachlanny: " << bruteForce(w, p, max, sizeof(w) / sizeof(int));
}