#include <iostream>
#include <time.h>
#include <fstream>
#include <ctime>
#include <Windows.h>
using namespace std;
int const n = 10;
typedef struct Matrix
{
	int size;
	double** mx;
	void input()
	{
		size = 1 + rand() % 10;
		cout << "size = " << size << endl;
		input(size);
	}
	void input(int x)
	{
		size = x;
		memory();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cin >> mx[i][j];
			}
		}
	}
	void generateRandom(int x)
	{
		size = x;
		memory();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				mx[i][j] = 1 + rand() % 9;
			}
		}
	}
	void output()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << mx[i][j] << " ";
			}
			cout << endl;
		}
	}
	void output(string FileName, Matrix* x)
	{
		ofstream file;
		file.open(FileName);
		for (int kol = 0; kol < n; kol++)
		{
			for (int i = 0; i < x[kol].size; i++)
			{
				for (int j = 0; j < x[kol].size; j++)
					file << x[kol].mx[i][j] << " ";
				file << endl;
			}
			file << endl;
		}
		file.close();
	}
	void determinant(int i, int j)
	{  
		double ratio;

		if (mx[i][j] == 0)
			goto end;

		ratio = mx[i][j] / mx[j][j];
		mx[i][j] = 0;

		for (int k = j + 1; k < size; k++)
		{
		mx[i][k] -= ratio * mx[i-1][k];
		}
		end:
		cout << "";
	}
	void outDet()
		{
		long long det = 1;
		for (int i = 0; i < size; i++)
			det *= mx[i][i];

		cout << fixed;
		cout.precision(0);
		cout << "Determinant: " << det << endl;
		}
	void memory()
	{
		mx = new double* [size];
		for (int i = 0; i < size; i++)
			mx[i] = new double[size];
	}
	void deletememory()
	{
		for (int i = 0; i < size; i++)
			delete mx[i];
		delete mx;
	}
};
class Timer
{
private:
	double _start;
	double _end;
	double res;
	int sec;
	int min;
	void res_ans()
	{
		_end = clock();
		res = (_end - _start) / CLOCKS_PER_SEC;
	}
public:
	void start()
	{
		_start = clock();
	}
	void stop()
	{
		res_ans();
		cout << "time ="<< res * 1000 << "ms";
	}
	void stop(string s)
	{
		res_ans();
		int x;
		x = (int)res;
		if (s == "s")
		{
			sec = x;
			cout << "time =" << sec << " s";
		}
		if (s == "m")
		{
			min = sec / 60;
			cout << "time =" << min << " min";
		}
		if (s == "full")
		{
			cout << "time = " << (x / 60) << " min " << (x % 60) << " s " << (res - x) << "ms";
		}
	}
};
int main()
{
	srand(time(0));
	Timer timer;
	timer.start();
	Matrix* matr = new Matrix[n];
	for (int i = 0; i < n; i++)
	{
		matr[i].generateRandom(3);
		matr[i].output();
		cout << endl;
		for (int j = 0; j < matr[i].size-1; j++)
			for (int k = j+1; k < matr[i].size; k++)
				matr[i].determinant(k,j);
		matr[i].output();
		matr[i].outDet();
		cout << endl;
	}
	for (int i = 0; i < n; i++)
	{
		delete matr[i].mx;
	}
	Sleep(2000);
	timer.stop();
}