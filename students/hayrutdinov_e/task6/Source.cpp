#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <windows.h>
using namespace std;
class Computer
{
protected:
	vector <int> comp;
	int n;
public:
	Computer()
	{
		n = 0;
	}
	vector<int> RandomNumber(int n)
	{
		vector<int> a(10);
		for (int i = 0; i < 10; i++)
			a[i] = i;
		random_shuffle(a.begin(), a.end());
		for (int i = 0; i <= n; i++)
			comp.push_back(a[i]);
		return comp;
	}
};
class Game :public Computer
{
	int n;
	int cows;
	int bulls;
	int Record;
	int steps;
	vector <int> player;
public:
	Game()
	{
		n = 0;
		cows = 0;
		bulls = 0;
	}
	void SetSize(int _n)
	{
		n = _n;
	}
	bool GetNumber(string _player)
	{
		if (_player.size() == n)
		{
			for (int i = 0; i < _player.size(); i++)
			{
				char tmp[2];
				tmp[0] = _player[i];
				tmp[1] = '\0';
				player.push_back(atoi(tmp));
			}
			return true;
		}
		else return false;
	}
	int CheckCows()
	{
		cows = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if ((comp[i] == player[j]) && (i != j))
					cows++;
			}
		}
		return cows;
	}
	int CheckBulls()
	{
		bulls = 0;
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
	string num;
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	cout << "Приветствую тебя в игре Быки и Коровы" << endl;
	while (b == 0)
	{
		cout << "     МЕНЮ \n"
			<< "1 - Начать играть\n"
			<< "2 - Узнать лучший счет\n"
			<< "3 - Узнать правила игры\n"
			<< "4 - Выход\n" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			steps = 0;
			cout << "Введите длину числа:" << endl;;
			cin >> n;
			game.SetSize(n);
		m1:	cout << "Введите число:" << endl;;
			cin >> num;
			for (int i = 0; i < n; i++)
				cout << game.RandomNumber(n)[i];
			cout << endl;
			if (game.GetNumber(num) == 0)
			{
				cout << "Неправильный ввод. Повторите попытку" << endl;
				goto m1;
			}
			else
				if (game.GetNumber(num) == 1)
				{
					steps++;
					cout << "Быков:" << game.CheckBulls() << endl;
					cout << "Коров:" << game.CheckCows() << endl;
					if (game.CheckBulls() == n)
					{
						cout << "Поздравляю, Игрок, ты выиграл!" << endl;
						cout << "Твой счет:" << steps;
						cout << "Лучший счет:" << game.ShowBest();
						system("pause");
						system("cls");
						break;
					}
					else goto m1;
				}

		}

		system("pause");
	}
}
