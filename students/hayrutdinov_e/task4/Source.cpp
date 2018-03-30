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
class FilmLibrary
{
public:
	vector<Film> films;
	void SortLib()
	{
		string tmp;
		for (int i = 0; i < films.size() - 1; i++)
			for (int j = 0; j < films.size() - i - 1; j++)

				if (films[i].year <= films[j].year)
					if (films[i].year == films[j].year)
						if (films[i].name < films[j].name)
						{
							tmp = films[i].name;


						}
	}
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
	vector <Film> GetFilm(string _name, int _year)
	{
		vector <Film> f;
		for (int j = 0; j < films.size(); j++)
		{
			if ((films[j].name == _name) && (films[j].year = _year))
				f.push_back(films[j]);
		}
		return f;
	}
	//4 Method
	vector <Film> GetFilmProd(string _prod)
	{
		vector <Film> g;
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
		vector <Film> h;
		for (int j = 0; j < films.size(); j++)
			if (films[j].year == _year)
				h.push_back(films[j]);
		return h;
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
				if (fees[j].cash > fees[j].cash)
				{
					tmp = fees[j].cash;
					fees[i].cash = fees[j + 1].cash;
					fees[j + 1].cash = tmp;
				}
			}
		return fees;
	}
	//6 Method
	vector <Film> GetFilmsWithMaxFees(int count)
	{
		vector <Film> fees;
		fees = SortFees();
		while (fees.size() != count)
			fees.pop_back();
		return fees;
	}
	// 7 Method
	vector <Film> GetFilmsWithMaxFeesInYear(int count, int _year)
	{
		vector <Film> feesinyear;
		vector <Film> tmp;
		feesinyear = SortFees();
		for (int i = 0; i < feesinyear.size(); i++)
			if (feesinyear[i].year = _year)
				tmp[i] = feesinyear[i];
		while (tmp.size() != count)
			tmp.pop_back();
		return tmp;
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
				films.erase(films.begin + i);
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
		lib.close;
	}
	//11 Method
	void CheckFile()
	{
		ifstream lib;
		int size;
		char t[300];
		lib.open("FilmLibrary.txt");
		lib.getline(t, 300, '\n');
		size = atoi(t);
		for (int i = 0; i < size; i++)
		{
			lib.getline(t, 100, '\n');
			films[i].name = t;
			lib.getline(t, 100, '.');
			films[i].day = atoi(t);
			lib.getline(t, 100, '.');
			films[i].month = atoi(t);
			lib.getline(t, 100, '\n');
			films[i].year = atoi(t);
			lib.getline(t, 100, '\n');
			films[i].prod = t;
			lib.getline(t, 100, '\n');
			films[i].scen = t;
			lib.getline(t, 100, '\n');
			films[i].comp = t;
			lib.getline(t, 100, '\n');
			films[i].cash = atoi(t);
		}
	}

};
void main()
{
	FilmLibrary FL;
	int tmp, tmp1;
	int t = 1;
	int r;
	char *b[100];
	string name, prod, scen, comp;
	int day, month, year, count;
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
			<< "11 - Check Library"
			<< "12 - Exit" << endl;
		cin >> r;
		switch (r)
		{
		case 1:
		{
			cout << "Name:";
			getline(cin, name);
			cout << "Day:";
			cin >> day;
			cout << "Month:";
			cin >> month;
			cout << "Year";
			cin >> year;
			cout << "Producer:";
			getline(cin, prod);
			cout << "Screenwriter";
			getline(cin, scen);
			cout << "Composer";
			getline(cin, comp);
			cout << "Box office:";
			cin >> fees;
			FL.AddFilm(comp, prod, name, scen, fees, day, month, year);
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			cout << "Enter name film and year:";
			cin >> name >> year;
			cout << "Enter fact that want:"
				<< "1 - Day"
				<< "2 - Month"
				<< "3 - Year"
				<< "4 - Name"
				<< "5 - Producer"
				<< "6 - Screenwriter"
				<< "7 - Composer"
				<< "8 - Fees" << endl;
			cin >> tmp;
			cout << "Enter the fact that you are changing:";
			cin >> r;
			FL.ChangeInfo(tmp, name, year, *b);
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Enter name film and year:";
			cin >> name >> year;
			FL.GetFilm(name, year);
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << "Enter producer";
			cin >> prod;
			FL.GetFilmProd(prod);
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			cout << "Enter year";
			cin >> year;
			FL.GetFilmYear(year);
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			cout << "Enter count films";
			cin >> count;
			FL.GetFilmsWithMaxFees(count);
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			cout << "Enter count films and her year";
			cin >> count >> year;
			FL.GetFilmsWithMaxFeesInYear(count, year);
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			cout << "Count films:" << FL.CountFilms();
			system("pause");
			system("cls");
			break;
		}
		case 9:
		{
			cout << "Enter name and year film that you want remove:";
			cin >> name >> year;
			FL.DeleteFilm(year, name);
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
			FL.CheckFile();
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