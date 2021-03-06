﻿#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
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
	void RandomNumber(int n)
	{
		vector<int> a(10);
		srand(time(NULL));
		for (int i = 0; i < 10; i++)
			a[i] = i;
		random_shuffle(a.begin(), a.end());
		for (int i = 0; i <= n; i++)
			comp.push_back(a[i]);
	}
	vector<int> GetRandNumber()
	{
		return comp;
	}
};
class Game :public Computer
{
	int cows;
	int bulls;
	int steps;
	vector <int> player;
public:
	Game()
	{
		cows = 0;
		bulls = 0;
	}
	void SetSize(int _n)
	{
		n = _n;
	}
	bool GetNumber(string _player)
	{
		if (n == _player.size())
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
		else
			return false;
	}
	int CountCows()
	{
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
	int CountBulls()
	{
		for (int i = 0; i < n; i++)
		{
			if (comp[i] == player[i])
				bulls++;
		}
		return bulls;
	}
	bool WinOrLose()
	{
		if (bulls == n)
			return true;
		return false;
	}
	void Steps(int _steps)
	{
		steps = _steps;
	}
	void ClearCowsBulls()
	{
		cows = 0;
		bulls = 0;
		player.clear();
	}
	void SaveRecords(int _steps)
	{
		int tmp;
		ifstream read("Records.txt");
		read >> tmp;
		read.close();
		ofstream rec;
		if (_steps < tmp)
		{
			rec.open("Records.txt", ios_base::trunc);
			rec << _steps;
		}
		rec.close();
	}
	int ShowBest()
	{
		int Record;
		char t[300];
		ifstream rec;
		rec.open("Records.txt");
		rec.getline(t, 300, '\n');
		Record = atoi(t);
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
		{
			steps = 0;
			cout << "Введите длину числа:" << endl;;
			cin >> n;
			game.SetSize(n);
			game.RandomNumber(n);
		m1:	cout << "Введите число:" << endl;;
			cin >> num;
			for (int i = 0; i < n; i++)
				cout << game.GetRandNumber()[i];
			cout << endl;
			if (game.GetNumber(num) == 0)
			{
				cout << "Неправильный ввод. Повторите попытку" << endl;
				goto m1;
			}
			if (game.GetNumber(num) == 1)
			{
				steps++;
				cout << "Быков:" << game.CountBulls() << endl;
				cout << "Коров:" << game.CountCows() << endl;
				if (game.WinOrLose() == true)
				{
					cout << "Поздравляю, Игрок, ты выиграл!" << endl;
					cout << "Твой счет:" << steps << endl;
					game.SaveRecords(steps);
					system("pause");
					system("cls");
					break;
				}
				if (game.WinOrLose() == false)
				{
					cout << "У всех бывают неудачи. Попробуй еще раз!. Я в тебя верю!!" << endl;
					game.ClearCowsBulls();
					goto m1;
				}
			}
		}
		case 2:
		{
			cout << "Лучший результат:" << game.ShowBest() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Требования(правила)." << endl;
			cout << "Играют два игрока(человек и компьютер)." << endl;
			cout << "Игрок выбирает длину загадываемого числа – n." << endl;
			cout << "Компьютер «задумывает» n - значное число с неповторяющимися цифрами." << endl;
			cout << " делает попытку отгадать число – вводит n - значное число с неповторяющимися цифрами." << endl;
			cout << " сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе(то есть количество коров) и сколько угадано вплоть до позиции в загаданном числе(то есть количество быков)." << endl;
			cout << " делает попытки, пока не отгадает всю последовательность." << endl;
			cout << "Пример." << endl;
			cout << "Пусть n = 4." << endl;
			cout << "Пусть задумано тайное число «3219»." << endl;
			cout << "Игрок ввел число «2310»." << endl;
			cout << "Результат: две «коровы»(две цифры : «2» и «3» — угаданы на неверных позициях) и один «бык»(одна цифра «1» угадана вплоть до позиции)." << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			b = 1;
		}
		}
	}
}
