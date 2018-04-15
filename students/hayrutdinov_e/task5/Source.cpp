#define _CRT_SECURE_NO_WARNINGS 
#include <cstdlib> 
#include <fstream> 
#include <iostream> 
#include<locale.h> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;
struct Goods
{
	string name;
	int barcode;
	int price;
	int sale;
	int count = 1;
	Goods &operator=(const Goods &c)
	{
		this->name = c.name;
		this->price = c.price;
		this->barcode = c.barcode;
		this->sale = c.sale;
		return *this;
	}
	friend ostream &operator<<(ostream &os, const Goods &ch);
};
ostream &operator<<(ostream &os, const Goods &ch)
{
	os << "Barcode:" << ch.barcode << endl;
	os << "Name:" << ch.name << endl;
	os << "price" << ch.price << endl;
	os << "Sale" << ch.sale << endl;
	return os;
}

struct Voucher : public Goods
{
	vector<Goods> goods;
	int value; // price za ves tovar
	int total; // summa k oplate
	int totsale; //general skidka
	void GetValue()
	{
		for (int i = 0; i < goods.size(); i++)
			value += goods[i].price*goods[i].count;
	}
	void GetTotalSale()
	{
		for (int i = 0; i < goods.size(); i++)
			totsale += goods[i].sale;
	}
	//5 Method
	int GetTotal()
	{
		total = value*totsale;
		return total;
	}
};
ostream &operator<<(ostream &os, const Voucher &ch)
{
	os << "Voucher" << endl;
	for (int i = 0; i < ch.goods.size(); i++)
	{
		os << setfill('.') << setw(10) << left << ch.goods[i].name << ch.goods[i].price << 'x' << ch.goods[i].count << endl;
		os << "Value:" << setfill('.') << setw(12) << ch.value << endl;
	}
	os << "Sale all goods:" << ch.totsale << endl;
	os << "TOTAL:" << ch.total;
}

class Storage
{
protected:
	vector <Goods> inv;
public:
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
class Till :public Storage
{
private:
	Voucher v;
public:
	//1 Method
	bool GetGoods(int code)
	{
		for (int i = 0; i < inv.size(); i++)
		{
			if (code == inv[i].barcode)
			{
				v.goods.push_back(inv[i]);
				return 1;
			}
			return 0;
		}
		for (int i = 0; i < v.goods.size(); i++)
			if (code == v.goods[i].barcode)
			{
				v.goods[i].count++;
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

	//4 Method
	Voucher SetVoucher()
	{
		return v;
	}
	//5 Method
	int GetTotal()
	{
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
	Storage storage;
	setlocale(LC_ALL, "rus");
	while (b == 0)
	{
		cout << "Select action:\n"
			<< "1 - Set Goods in storage\n"
			<< "2 -Set Barcode\n"
			<< "3 - Get Description\n"
			<< "4 - \n"
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
			getline(cin, name);
			cout << "Enter price" << endl;
			cin >> price;
			cout << "Enter sale:" << endl;
			cin >> sale;
			storage.SetGoods(code, name, price, sale);
		}
		case 2:
		{
			system("chcp 1251");
			cout << "Enter barcode:" << endl;
			cin >> code;
			till.GetGoods(code);
			if (till.GetGoods(code) == 0)
			{
				cout << "This product is not in stock.Add it to the database:" << endl;
				cout << "Enter name" << endl;
				getline(cin, name);
				cout << "Enter price" << endl;
				cin >> price;
				cout << "Enter sale:" << endl;
				cin >> sale;
				storage.SetGoods(code, name, price, sale);
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