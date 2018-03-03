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

	//Know Size Array//
	void SizeArray()
	{
		cout << "Size array:" << GetSize() << "\n";
	}

	//Set element by index//
	void SetElem(int index, double elem)
	{
		arr[index - 1] = elem;
	}

	//Know element by index//
	void KnowElem(int i)
	{
		cout << arr[i] << "\n";
	}

	//Find Minimal Element in array//
	void MinimalElem()
	{
		double min = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}
		cout << min << "\n";
	}

	//Validation of the array in order//
	void CheckArray()
	{
		int tmp = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] <= arr[i + 1])
				tmp = 0;
			else
			{
				tmp = 1;
				break;
			}
		}
		if (tmp == 0)
			cout << "Array is ordered\n";
		else cout << "Array is disordered\n";
	}

	//Array with odd index//
	void OddArray()
	{
		double *oddarr = new double[(size / 2) + 1];
		float p = size / 2;
		cout << "Subarray with odd index of the source:";
		for (int i = 0; i < size; i++)
			for (int j = 0; j < p - 1; j++)
			{
				if (i % 2 == 0)
				{
					oddarr[j] = arr[i];
					cout << oddarr[j] << " ";
				}

			}
		cout << "\n";
	}

	//Destructor//
	~DynamicArray()
	{
		delete[] arr;
	}
};

void main()
{
	int size = 1;
	int r = 1;
	int b;
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
			A.SizeArray();
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Set index:\n";
			cin >> size;
			cout << "Set value:\n";
			cin >> elem;
			A.SetElem(size, elem);
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << "Set index:\n";
			cin >> size;
			A.KnowElem(size);
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			A.MinimalElem();
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			A.CheckArray();
			A.PrintArray();
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			A.OddArray();
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