#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <cstdlib> 
#include <cmath>

using namespace std;
class DynamicArray
{
	int size;
	double *arr;

public:

	//Constructor//
	DynamicArray(int _ind = 1)
	{
		size = _ind;
		arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = 0;
		}
	}

	//Assignment operator//
	DynamicArray& operator=(DynamicArray &arr2)
	{
		delete[] arr;
		size = arr2.size;
		arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = arr2.arr[i];
		}
		return *this;
	}
	double GetSize()
	{
		return size;
	}
	void PrintArray()
	{
		for (int i = 0; i < size; i++)
			cout << arr[i] << "  ";
	}
	//Change Size//
	void SetSize(int _size)
	{
		delete[] arr;
		size = _size;
		arr = new double[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = 0;
		}
	}
	//Set element by index//
	void SetElem(int index, double elem)
	{
		arr[index] = elem;
	}

	//Know element by index//
	double GetElem(int i)
	{
		return arr[i];
	}

	//Find Minimal Element in array//
	double MinimalElem()
	{
		double min = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}
		return min;
	}
	void PrintMinElem()
	{
		cout << "Minimal element of array:" << MinimalElem() << "\n";
	}

	//Validation of the array in order//
	double CheckArray()
	{
		bool tmp;
		int t;
		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] <= arr[i + 1])
				tmp = true;
			else
			{
				tmp = 1;
				break;
			}
		}
		return tmp;
	}

	//Array with odd index//
	double OddArray(int j)
	{
		double *oddarr = new double[(size / 2)];
		float p = size / 2;
		for (int i = 0; i < p; i++)
			oddarr[i] = arr[2 * i + 1];
		return oddarr[j];
	}
	//Destructor//
	~DynamicArray()
	{
		delete[] arr;
	}
};

void main()
{
	int index;
	double min = 0;
	int size = 1;
	int r = 1;
	int b;
	bool tmp = 0;
	double elem;
	double *array = new double[size];

	DynamicArray A;
	while (r == 1)
	{
		cout << "Select action:" << "\n" << "1 - Set size of array\n" << "2 - Know size of array\n" << "3 - Set element by index\n" << "4 - Know element by index\n" << "5 - Find minimal element\n" << "6 - Check for orderliness\n" << "7 - Allocate the subarray\n" << "8 - EXIT\n";
		cin >> b;
		switch (b)
		{
		case 1:
		{
			cout << "Set size:" << "\n";
			cin >> size;
			A.SetSize(size);
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			A.GetSize();
			cout << "Size array:" << size << "\n";
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Set index:\n";
			cin >> index;
			cout << "Set value:\n";
			cin >> elem;
			A.SetElem(index, elem);
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << "Set index:\n";
			cin >> index;
			cout << A.GetElem(index) << "\n";
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			A.PrintMinElem();
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			A.CheckArray();
			if (tmp)
				cout << "Array is ordered\n";
			else cout << "Array is disordered\n";
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			float p = size / 2;
			for (int i = 0; i < p; i++)
				cout << A.OddArray(i) << " ";
			cout << "\n";
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 8:
			r = 0;

		}
	}
	system("pause");
}