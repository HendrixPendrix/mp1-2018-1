#define _CRT_SECURE_NO_WARNINGS 
#include <cstdlib> 
#include <fstream> 
#include <iostream> 
#include<locale.h> 
#include <string> 
#include <vector> 
using namespace std;
struct Goods
{
	string name;
	int barcode;
	int price;
	double sale;
	int count = 1;
	Goods &operator=(const Goods &c)
	{
		this->name = c.name;
		this->price = c.price;
		this->barcode = c.barcode;
		this->sale = c.sale;
		this->count = c.count;
		return *this;
	}
	friend ostream &operator<<(ostream &os, const Goods &ch);
};
ostream &operator<<(ostream &os, const Goods &ch)
{
	os << "Barcode:" << ch.barcode << endl;
	os << "Name:" << ch.name << endl;
	os << "Price" << ch.price << endl;
	os << "Sale" << ch.sale << endl;
	return os;
}
struct Voucher
{
	vector<Goods> goods;
	int value = 0; // price za ves tovar
	float total = 0; // summa k oplate
	float totsale = 0; //general skidka
	Voucher &operator=(const Voucher &c)
	{
		this->value = c.value;
		this->total = c.total;
		this->totsale = c.totsale;;
		return *this;
	}
	int GetValue()
	{
		for (int i = 0; i < goods.size(); i++)
			value += (goods[i].price*goods[i].count);
		return value;
	}
	float GetTotalSale()
	{
		for (int i = 0; i < goods.size(); i++)
			totsale += (goods[i].price  * (goods[i].sale / 100))*goods[i].count;
		return totsale;
	}
	float GetTotal()
	{
		total = GetValue() - GetTotalSale();
		return total;
	}
};
ostream &operator<<(ostream &os, const Voucher &ch)
{
	os << "Voucher" << endl;
	for (int i = 0; i < ch.goods.size(); i++)
	{
		os << "Name: " << ch.goods[i].name << endl;
		os << "Price: " << ch.goods[i].price << endl;
		os << "Count: " << ch.goods[i].count << endl;
		os << "Sale: " << ch.goods[i].sale << "%" << endl;
	}
	os << "Value:" << ch.value << endl;
	os << "Sale all goods:" << ch.totsale << endl;
	os << "TOTAL:" << ch.total;
	return os;
}
class Storage
{
public:
	vector <Goods> inv;
	void SetGoods(int _code, string _name, int _price, int _sale)
	{
		Goods tmp;
		tmp.name = _name;
		tmp.barcode = _code;
		tmp.price = _price;
		tmp.sale = _sale;
		inv.push_back(tmp);
	}
};
class Till : public Storage
{
private:
	Voucher v;
	Goods g;
public:
	//1 Method
	bool GetGoods(int code)
	{
		if (code == g.barcode)
		{
			g.count++;
		}
		for (int i = 0; i < inv.size(); i++)
		{
			if (code == inv[i].barcode)
			{
				g = inv[i];
				return 1;
			}
			return 0;
		}
	}
	//2 Method
	Goods GetDescription(int _code)
	{
		for (int i = 0; i < inv.size(); i++)
			if (_code == inv[i].barcode)
				return inv[i];
	}
	//3 Method
	void SetDescription()
	{
		v.goods.push_back(g);
	}
	//4 Method
	Voucher SetVoucher()
	{
		return v;
	}
	//5 Method
	double GetTotal()
	{
		v.GetValue();
		v.GetTotalSale();
		return v.GetTotal();
	}
	//6 Method
	void DeleteGoods(int _code)
	{
		for (int i = 0; i < v.goods.size(); i++)
			if (_code == v.goods[i].barcode)
			{
				v.goods.erase(v.goods.begin() + i);
			}
	}
};
void main()
{
	int b = 0, r, code;
	string name;
	int price, sale;
	Till till;
	setlocale(LC_ALL, "rus");
	while (b == 0)
	{
		cout << "Select action:\n"
			<< "1 - Set Goods in storage\n"
			<< "2 - Set Barcode\n"
			<< "3 - Get Description\n"
			<< "4 - Set Description\n"
			<< "5 - To form a check\n"
			<< "6 - To calculate the final cost\n"
			<< "7 - To remove the selected goods\n"
			<< "0 - Exit" << endl;
		cin >> r;
		switch (r)
		{
		case 1:
		{
			cout << "Enter barcode" << endl;
			cin >> code;
			cout << "Enter name" << endl;
			cin.ignore();
			getline(cin, name);
			cout << "Enter price" << endl;
			cin >> price;
			cout << "Enter sale:" << endl;
			cin >> sale;
			till.SetGoods(code, name, price, sale);
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			system("chcp 1251");
			cout << "Enter barcode:" << endl;
			cin >> code;
			if (till.GetGoods(code) == 0)
			{
				cout << "This product is not in stock." << endl;
			}
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Enter barcode:" << endl;
			cin >> code;
			cout << till.GetDescription(code) << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			till.SetDescription();
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			cout << till.SetVoucher() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			cout << till.GetTotal() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			cout << "Enter barcode:" << endl;
			cin >> code;
			till.DeleteGoods(code);
			system("pause");
			system("cls");
			break;
		}
		case 0:
		{
			b = 1;
		}
		}
	}
}