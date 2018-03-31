#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <fstream>
#include <iostream>
#include<locale.h>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
struct Film
{
public:
	int day;
	int month;
	int year;
	string comp;
	string prod;
	string name;
	string scen;
	unsigned long int cash;
	Film &operator=(const Film &c)
	{
		this->comp = c.comp;
		this->prod = c.prod;
		this->name = c.name;
		this->scen = c.scen;
		this->cash = c.cash;
		this->day = c.day;
		this->month = c.month;
		this->year = c.year;
		return *this;
	}
};
ostream &operator<<(ostream &os, const Film &film)
{
	os << "Name:" << film.name << endl;
	os << "Date:" << film.day << '.' << film.month << '.' << film.year << endl;
	os << "Producer:" << film.prod << endl;
	os << "Screenwriter:" << film.scen << endl;
	os << "Composer:" << film.comp << endl;
	os << "Fees:" << film.cash << endl;
	return os;
}
class FilmLibrary
{
private:
	vector <Film> SortLib()
	{
		Film tmp;
		for (int i = 0; i < films.size() - 1; i++)
			for (int j = 0; j < films.size() - i - 1; j++)
				if (films[j].year >= films[j + 1].year)
					if (films[j].year == films[j + 1].year)
						if (films[j].name > films[j + 1].name)
						{
							tmp = films[j];
							films[j] = films[j + 1];
							films[j + 1] = tmp;
						}
						else {}
					else
					{
						tmp = films[j];
						films[j] = films[j + 1];
						films[j + 1] = tmp;
					}
		return films;
	}
	vector <Film> SortFees()
	{
		vector <Film> fees;
		int tmp;
		for (int j = 0; j < films.size(); j++)
		{
			fees[j] = films[j];
		}
		for (int i = 0; i < films.size() - 1; i++)
			for (int j = 0; j < films.size() - i - 1; j++)
			{
				if (fees[j].cash > fees[j + 1].cash)
				{
					tmp = fees[j].cash;
					fees[j].cash = fees[j + 1].cash;
					fees[j + 1].cash = tmp;
				}
			}
		return fees;
	}
public:
	friend ostream &operator<<(ostream &os, const Film &film);
	vector<Film> films;
	vector <Film> g;
	vector <Film> fees;
	//1 Method
	void AddFilm(string _comp, string _prod, string _name, string _scen, int _cash, int _day, int _month, int _year)
	{
		Film f;
		f.comp = _comp;
		f.prod = _prod;
		f.name = _name;
		f.scen = _scen;
		f.cash = _cash;
		f.day = _day;
		f.month = _month;
		f.year = _year;
		films.push_back(f);
		SortLib();
	}
	//2 Method
	void ChangeInfo(int tmp, string _name, int _year, char *_info)
	{
		for (int i = 0; i < films.size(); i++)
		{
			if ((films[i].name == _name) && (films[i].year = _year))
			{
				switch (tmp)
				{
				case 1:
					films[i].day = atoi(_info);
				case 2:
					films[i].month = atoi(_info);
				case 3:
					films[i].year = atoi(_info);
				case 4:
					films[i].name = _info;
				case 5:
					films[i].prod = _info;
				case 6:
					films[i].scen = _info;
				case 7:
					films[i].comp = _info;
				case 8:
					films[i].cash = atoi(_info);
				}
			}
		}
	}
	//3 Method
	Film GetFilm(string _name, int _year)
	{
		for (int j = 0; j < films.size(); j++)
		{
			if ((films[j].name == _name) && (films[j].year = _year))
				return films[j];
		}
	}
	//4 Method
	vector <Film> GetFilmProd(string _prod)
	{
		for (int j = 0; j < films.size(); j++)
		{
			if (films[j].prod == _prod)
				g.push_back(films[j]);
		}
		return g;
	}
	//5 Method
	vector <Film> GetFilmYear(int _year)
	{
		for (int j = 0; j < films.size(); j++)
			if (films[j].year == _year)
				g.push_back(films[j]);
		return g;
	}
	//6 Method
	vector <Film> GetFilmsWithMaxFees(int count)
	{
		for (int i = 0; i < count; i++)
		{
			fees.push_back(SortFees()[i]);
			return fees;
		}
	}
	// 7 Method
	vector <Film> GetFilmsWithMaxFeesInYear(int count, int _year)
	{
		fees = SortFees();
		for (int i = 0; i < fees.size(); i++)
			if (fees[i].year = _year)
				g[i] = fees[i];
		return g;
	}
	//8 Method
	int CountFilms()
	{
		return films.size();
	}
	//9 Method
	void DeleteFilm(int _year, string _name)
	{
		for (int i = 0; i < films.size(); i++)
		{
			if (films[i].year == _year && films[i].name == _name)
				films.erase(films.begin() + i);
		}
	}
	//10 Method
	void SaveInFile()
	{
		setlocale(LC_ALL, "rus");
		ofstream lib;
		lib.open("FilmLibrary.txt");
		lib << films.size() << endl;
		for (int i = 0; i < films.size(); i++)
		{
			lib << "Name:" << films[i].name << endl;
			lib << "Date:" << films[i].day << '.' << films[i].month << '.' << films[i].year << endl;
			lib << "Producer:" << films[i].prod << endl;
			lib << "Screenwriter:" << films[i].scen << endl;
			lib << "Composer:" << films[i].comp << endl;
			lib << "Fees:" << films[i].cash << endl;
		}
		lib.close();
	}
	//11 Method
	void CheckFile(int _count)
	{
		ifstream lib;
		Film f;
		int size;
		char t[300];
		lib.open("FilmLibrary.txt");
		lib.getline(t, 300, '\n');
		size = atoi(t);
		for (int i = 0; i < size; i++)
		{
			lib.getline(t, 100, '\n');
			lib.getline(t, 100, '\n');
			f.name = t;
			lib.getline(t, 100, ':');
			lib.getline(t, 100, '.');
			f.day = atoi(t);
			lib.getline(t, 100, '.');
			f.month = atoi(t);
			lib.getline(t, 100, '\n');
			f.year = atoi(t);
			lib.getline(t, 100, '\n');
			lib.getline(t, 100, '\n');
			f.prod = t;
			lib.getline(t, 100, '\n');
			lib.getline(t, 100, '\n');
			f.scen = t;
			lib.getline(t, 100, '\n');
			lib.getline(t, 100, '\n');
			f.comp = t;
			lib.getline(t, 100, ':');
			lib.getline(t, 100, '\n');
			f.cash = atoi(t);
			films.push_back(f);
		}

	}
	void PrintVector()
	{
		for (int i = 0; i < films.size(); i++)
		{
			cout << films[i] << endl;
		}
	}
};
void main()
{
	FilmLibrary FL;
	vector<Film> _films;
	int tmp, count = 0;
	int t = 1;
	int r;
	char *b[100];
	string name, prod, scen, comp, _name;
	int day, month, year;
	unsigned long int fees;
	setlocale(LC_ALL, "Rus");
	while (t == 1)
	{
		cout << "Select action:\n"
			<< "1 -Set Film\n"
			<< "2 - Change info\n"
			<< "3 - Get film by year and name\n"
			<< "4 - Get film by producer\n"
			<< "5 - Get films for this year\n"
			<< "6 - Issue the specified number of films with the largest fees\n"
			<< "7 - Issue the specified number of films with the largest fees in the selected year\n"
			<< "8 - Get count of films\n"
			<< "9 - Remove film\n"
			<< "10 - Save Library in file\n"
			<< "11 - Check Library\n"
			<< "12 - Exit" << endl;
		cin >> r;
		switch (r)
		{
		case 1:
		{
			system("chcp 1251");
			cout << "Name:";
			getline(cin, name, '.');
			cout << "Day:";
			cin >> day;
			cout << "Month:";
			cin >> month;
			cout << "Year:";
			cin >> year;
			cout << "Producer:";
			getline(cin, prod, '.');
			cout << "Screenwriter:";
			getline(cin, scen, '.');
			cout << "Composer:";
			getline(cin, comp, '.');
			cout << "Box office:";
			cin >> fees;
			cout << endl;
			FL.AddFilm(comp, prod, name, scen, fees, day, month, year);
			FL.PrintVector();
			count++;
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			cout << "Enter name film and year:";
			cin >> name >> year;
			cout << "Enter fact that want:"
				<< "1 - Day\n"
				<< "2 - Month\n"
				<< "3 - Year\n"
				<< "4 - Name\n"
				<< "5 - Producer\n"
				<< "6 - Screenwriter\n"
				<< "7 - Composer\n"
				<< "8 - Fees" << endl;
			cin >> tmp;
			cout << "Enter the fact that you are changing:";
			cin >> r;
			FL.ChangeInfo(tmp, name, year, *b);
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Enter name film and year:";
			cin >> name >> year;
			cout << FL.GetFilm(name, year);
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << "Enter producer:";
			cin >> prod;
			_films = FL.GetFilmProd(prod);;
			for (int i = 0; i < _films.size(); i++)
				cout << _films[i];
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			cout << "Enter year:";
			cin >> year;
			_films = FL.GetFilmYear(year);
			for (int i = 0; i < _films.size(); i++)
				cout << _films[i];
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			cout << "Enter count films:";
			cin >> count;
			FL.GetFilmsWithMaxFees(count);
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			cout << "Enter count films and her year:";
			cin >> count >> year;
			_films = FL.GetFilmsWithMaxFeesInYear(count, year);
			for (int i = 0; i < _films.size(); i++)
				cout << _films[i];
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			cout << "Count films:" << FL.CountFilms() << endl;;
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 9:
		{
			cout << "Enter name and year film that you want remove:";
			cin >> name >> year;
			FL.DeleteFilm(year, name);
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 10:
		{
			FL.SaveInFile();
			system("pause");
			system("cls");
			break;
		}
		case 11:
		{
			FL.CheckFile(count);
			FL.PrintVector();
			system("pause");
			system("cls");
			break;
		}
		case 12:
		{
			t = 0;
		}
		}
	}
}