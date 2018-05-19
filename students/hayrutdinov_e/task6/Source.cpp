#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

class Game
{
	int n;
	int cows;
	int bulls;
	int Record;
	int steps;
	vector <int> player;
	vector <int> comp;
public:
	Game()
	{
		n = 0;
		cows = 0;
		bulls = 0;
	}
	vector<int> RandomNumber(int n)
	{
		vector<int> a(10);
		srand(time(NULL));
		for (int i = 0; i < 10; i++)
			a[i] = i;
		random_shuffle(a.begin(), a.end());
		for (int i = 0; i <= n; i++)
			comp.push_back(a[i]);
		return comp;
	}
	void SetSize(int _n)
	{
		n = _n;
	}
	bool GetNumber(int _player)
	{
		int tmp = _player;
		int count = 0;
		while (tmp != 0)
		{
			count++;
			tmp / 10;
		}
		if (count == n)
		{
			for (int i = 0; i < n; i++)
			{
				int y;
				y = _player % 10;
				player.push_back(y);
				_player = _player / 10;
			}
			return true;
		}
		else return false;
	}
	int CheckCows()
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (comp[i] == player[j])
					cows++;
			}
		}
		return cows;
	}
	int CheckBulls()
	{
		for (int i = 0; i < n; i++)
		{
			if (comp[i] == player[i])
				bulls++;
		}
		return bulls;
	}
	int Steps(int _steps)
	{
		steps = _steps;
	}
	void SaveRecords()
	{
		ofstream rec("Records.txt");
		if (steps < ShowBest())
		{
			rec.open("Records.txt", ios_base::trunc);
			rec << steps;
		}
		rec.close();
	}
	int ShowBest()
	{
		ifstream rec("Records.txt");
		rec >> Record;
		rec.close();
		return Record;
	}
};

void main()
{
	Game game;
	int n, b = 0, a, steps;
	int num;
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	cout << "����������� ���� � ���� ���� � ������" << endl;
	while (b == 0)
	{
		cout << "     ���� \n"
			<< "1 - ������ ������\n"
			<< "2 - ������ ������ ����\n"
			<< "3 - ������ ������� ����\n"
			<< "4 - �����\n" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			steps = 0;
			cout << "������� ����� �����:" << endl;;
			cin >> n;
			game.SetSize(n);
		m1:	cout << "������� �����:" << endl;;
			cin >> num;
			for (int i = 0; i < n; i++)
				cout << game.RandomNumber(n)[i];
			cout << endl;
			if (game.GetNumber(num) == 0)
			{
				cout << "������������ ����. ��������� �������" << endl;
				goto m1;
			}
			else
				if (game.GetNumber(num) == 1)
				{
					steps++;
					cout << "�����:" << game.CheckBulls() << endl;
					cout << "�����:" << game.CheckCows() << endl;
					if (game.CheckBulls() == n)
					{
						cout << "����������, �����, �� �������!" << endl;
						cout << "���� ����:" << steps;
						cout << "������ ����:" << game.ShowBest();
						system("pause");
						system("cls");
						break;
					}
					else goto m1;
				}
		case 2:
		{
			cout << game.ShowBest() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "����������(�������)." << endl;
			cout << "������ ��� ������(������� � ���������)." << endl;
			cout << "����� �������� ����� ������������� ����� � n." << endl;
			cout << "��������� ����������� n - ������� ����� � ���������������� �������." << endl;
			cout << " ������ ������� �������� ����� � ������ n - ������� ����� � ���������������� �������." << endl;
			cout << " ��������, ������� ���� ������� ��� ���������� � �� ��������� � ���������� �����(�� ���� ���������� �����) � ������� ������� ������ �� ������� � ���������� �����(�� ���� ���������� �����)." << endl;
			cout << " ������ �������, ���� �� �������� ��� ������������������." << endl;
			cout << "������." << endl;
			cout << "����� n = 4." << endl;
			cout << "����� �������� ������ ����� �3219�." << endl;
			cout << "����� ���� ����� �2310�." << endl;
			cout << "���������: ��� ��������(��� ����� : �2� � �3� � ������� �� �������� ��������) � ���� ����(���� ����� �1� ������� ������ �� �������)." << endl;
		}
		case 4:
		{
			b = 1;
		}
		}

		system("pause");
	}
}
