#define _CRT_SECURE_NO_WARNINGS 
#include <fstream> 
#include <iostream> 
#include <cstdlib> 
#include <locale.h>

using namespace std;


class Translator
{
public:
	char ***dict;
	char **rus;
	char **eng;
	int size;
	Translator(int _size = 0)
	{
		size = _size;
		dict = new char**[2];
		for (int i = 0; i < size; i++)
			dict[i] = new char*[2];
	}
	~Translator()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] dict[i];
		}
		delete[] dict;;
	}
	Translator& operator=(const Translator &dict2)
	{
		if (this == &dict2)
			return *this;
		if (size != dict2.size)
		{
			delete[] dict;
			size = dict2.size;
			dict = new char**[2];
			for (int i = 0; i < size; i++)
			{
				dict[i] = new char*[2];
			}
		}
		for (int i = 0; i < size; i++)
		{
			strcpy(dict[i][0], dict2.dict[i][0]);
			strcpy(dict[i][1], dict2.dict[i][1]);
		}
		size = dict2.size;
		return *this;
	}
	Translator(const Translator &c)
	{
		size = c.size;
		dict = new char**[2];
		for (int i = 0; i < size; i++)
		{
			dict[i] = new char*[2];
			dict[i] = c.dict[i];
		}


	}
	void ResizeDict()
	{
		char ***_n;
		_n = new char**[size];

		for (int i = 0; i < size; i++)
		{
			_n[i] = new char*[2];
			_n[i][0] = dict[i][0];
			_n[i][1] = dict[i][1];
		}
		for (int i = 0; i < size; i++)
		{
			delete[] dict[i];
		}
		delete[] dict;

		dict = new char**[size + 1];

		for (int i = 0; i < size + 1; i++)
			dict[i] = new char*[2];

		for (int i = 0; i < size; i++)
		{
			dict[i][0] = _n[i][0];
			dict[i][1] = _n[i][1];
		}
		delete[] _n;
		size++;
	}
	void PrintDict()
	{
		for (int i = 0; i < size; i++)
			cout << dict[i][0] << "   " << dict[i][1] << endl;
	}
	void AddWordAndTranslate(char *_eng, char *_rus)
	{
		ResizeDict();
		dict[size - 1][0] = new char[strlen(_eng) + 1];
		dict[size - 1][1] = new char[strlen(_rus) + 1];
		strcpy(dict[size - 1][0], _eng);
		strcpy(dict[size - 1][1], _rus);
	}


	bool ChangeTranslate(char *word, char *wordrus, char *rus)
	{
		for (int i = 0; i < size; i++)
		{
			if (!strcmp(word, dict[i][0]) && !strcmp(wordrus, dict[i][1]))
			{
				delete dict[i][1];
				dict[i][1] = new char[strlen(rus) + 1];
				strcpy(dict[i][1], rus);
				return true;
			}
		}
		return false;
	}
	char *GetTranslate(char *word)
	{
		for (int i = 0; i < size; i++)
		{
			if (!strcmp(word, dict[i][0]))
				return dict[i][1];
		}
	}
	char CheckWord(char *word)
	{
		bool tmp = true;
		for (int i = 0; i < size; i++)
		{
			if (!strcmp(word, dict[0][i]))
			{
				tmp = true;
			}
			else tmp = false;
			break;
		}
		return tmp;
	}
	int GetCount(int count = 1)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (!strcmp(dict[0][i], dict[0][j]));
				else count++;
				return count;
	}
	void PrintCount()
	{
		cout << GetCount() << endl;
	}
	char SaveInFile()
	{
		setlocale(LC_ALL, "rus");
		ofstream dictionary;
		dictionary.open("dictionary.txt");
		dictionary << size << endl;
		for (int i = 0; i < size; i++)
		{
			dictionary << dict[i][0] << ' ';
			dictionary << dict[i][1] << endl;
		}
		dictionary.close();
		return 0;
	}
	void CheckFile()
	{
		char r[300];
		ifstream dictionary;
		dictionary.open("dictionary.txt");
		dictionary.getline(r, 300, '\n');
		size = atoi(r);
		dict = new char**[size];
		for (int i = 0; i < size; i++)
		{
			dict[i] = new char*[2];
			char t[300];
			dictionary.getline(t, 300, ' ');
			dict[i][0] = new char[strlen(t) + 1];
			strcpy(dict[i][0], t);
			dictionary.getline(t, 300, '\n');
			dict[i][1] = new char[strlen(t) + 1];
			strcpy(dict[i][1], t);
		}
		dictionary.close();
	}
};
void main()
{
	bool tmp = 1;
	int count = 0, b = 1, r;
	char word[100];
	char eng[300];
	char rus[300];
	char _rus[300];
	Translator Tr;
	setlocale(LC_ALL, "Rus");
	while (b == 1)
	{
		cout << "Select action:\n" << "1 - Add Word and translate\n" << "2 - Change translate\n" << "3 - Get translate\n" << "4 - Check word in dictionary\n" << "5 - Get count words\n" << "6 - Save in file\n" << "7 - Read words from file\n" << "8 - Exit\n";
		cin >> r;
		switch (r)
		{
		case 1:
		{
			system("chcp 1251");
			cout << "enter word:" << endl;
			cin >> eng;
			cout << "enter translate:" << endl;
			cin >> rus;
			Tr.AddWordAndTranslate(eng, rus);
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			cout << "Enter the word whose translation you want to change:" << endl;
			cin >> word;
			cout << "Enter the translation you want to change :" << endl;;
			cin >> rus;
			cout << "Enter new translation:" << endl;
			cin >> _rus;
			Tr.ChangeTranslate(word, rus, _rus);
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;

		}
		case 3:
		{
			cout << "Enter the word whose translation you want see:";
			cin >> word;
			cout << Tr.GetTranslate(word) << endl;
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << "Enter the word whose translation you want see:";
			cin >> word;
			if (Tr.CheckWord(word) == true)
			{
				cout << "This word is already in dictionary" << endl;
			}
			else cout << "This word is not in the dictionary" << endl;
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			Tr.PrintCount();
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			Tr.SaveInFile();
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			Tr.CheckFile();
			Tr.PrintDict();
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			b = 0;
		}
		}
	}
	system("pause");
}