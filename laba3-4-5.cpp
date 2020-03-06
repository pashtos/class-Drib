#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template<class T>
class drib
{
protected:
	T ch;
	T zn;
public:
	drib();
	drib(T ch, T zn);
	drib(const drib<T>& other);
	~drib();
	void show();
	T getZN();
	T getCH();
	drib& operator = (const drib<T>& other);
	drib operator +(const drib<T>& other);
	friend ostream& operator << (ostream& s, const drib<int>& a);
	friend istream& operator >> (istream& s, drib<int>& a);
};


template <class T>
class int_drib :
	public drib<T>
{
	T int_part;
public:
	int_drib(T int_part, T ch, T zn);
	int_drib();
	int_drib& operator = (const int_drib<T>& other);
	int_drib operator +(const int_drib<T>& other);

	friend ostream& operator << (ostream& s, int_drib<int>& a);
	friend istream& operator >> (istream& s, int_drib<int>& a);

};


template <class T> T NSK(T a, T b);
template <class T> string Plus(drib<T>& a, drib<T>& b);
template <class T> string Minus(drib<T>& a, drib<T>& b);
template <class T> string Multiplication(drib<T>& a, drib<T>& b);

ostream& operator << (ostream& s, const drib<int>& a);
istream& operator >> (istream& s, drib<int>& a);

ostream& operator << (ostream& s, int_drib<int>& a);
istream& operator >> (istream& s, int_drib<int>& a);


int main()
{
	system("chcp 1251");
	drib<int> a(2, 3);
	//cin >> a;
	drib<int> b(2, 3);
	drib<int>c = a + b;
	cout << c;
	return 0;
}
/////////////////////////DRIB////////////////////////////////////////////////////////
template <class T> drib<T>::drib()
{
	//cout << "\nВикликався конструктор за замовчуванням\n";
	ch = 1;
	zn = 1;
}
template <class T> drib<T>::drib(T ch, T zn)
{
	//cout << "\nВикликався конструктор з параметрами\n";
	this->ch = ch;
	this->zn = zn;
	if (zn == 0 || ch == 0 || zn < ch)
	{
		cout << "\nВведіть коректні дані\n";
		exit(1);
	}
}
template <class T> drib<T>::drib(const drib<T>& other)
{
	//	cout << "\nВикликався конструктор копіювання\n";
	this->ch = other.ch;
	this->zn = other.zn;
}
template <class T> drib<T>::~drib()
{
	//cout << "\nВикликався деструктор\n";
}
template <class T> void drib<T>::show()
{
	for (int i = min(zn, ch); i > 1; i--)
	{
		if (zn % i == 0 && ch % i == 0)
		{
			zn /= i;
			ch /= i;
		}
	}
	cout << ch << "/" << zn;
}
template <class T> T drib<T>::getZN()
{
	return zn;
}
template <class T> T drib<T>::getCH()
{
	return ch;
}
template <class T> drib<T>& drib<T>::operator = (const drib<T>& other)
{
	this->ch = other.ch;
	this->zn = other.ch;
	return *this;
}
template <class T> drib<T> drib<T>::operator+(const drib<T>& other)
{
	drib New;
	if (this->zn == other.zn)
	{
		New.zn = this->zn;
		New.ch = this->ch + other.ch;
	}
	else
	{
		//НСК
		int c = max(this->zn, other.zn);
		while (c % this->zn != 0 || c % other.zn != 0)
		{
			c++;
		}
		New.zn = c;
		New.ch = this->ch * (New.zn / this->zn) + other.ch * (New.zn / other.zn);
	}
	return New;
}
ostream& operator<< (ostream& s, const drib<int>& a)
{
	s << a.ch << "/" << a.zn;
	return s;
}
istream& operator >> (istream& s, drib<int>& a)
{
	cout << "Введіть чисельник: ";
	s >> a.ch;
	while (!a.ch)
	{
		cout << "Введіть чисельник правильно: ";
		s >> a.ch;
	}
	cout << "Введіть знаменник: ";
	s >> a.zn;
	while (!a.zn || a.zn <= a.ch)
	{
		cout << "Введіть знаменник правильно: ";
		s >> a.zn;
	}
	return s;
}

//////////////////////////////INT_DRIB///////////////////////////////////////////////////////////

template <class T> int_drib<T>::int_drib(T int_part, T ch, T zn) :drib<T>(ch, zn)
{
	this->int_part = int_part;

	if (int_part) {
		this->ch += this->zn * this->int_part;
		this->int_part = 0;
	}
}
template <class T> int_drib<T>::int_drib()
{
	this->int_part = 0;
	this->ch = 1;
	this->zn = 1;
}
template <class T> int_drib<T>& int_drib<T>::operator=(const int_drib<T>& other)
{
	this->int_part = other.int_part;
	this->ch = other.ch;
	this->zn = other.ch;
	return *this;
}
template <class T> int_drib<T> int_drib<T>::operator+(const int_drib<T>& other)
{
	int_drib<T> New;
	if (this->zn == other.zn)
	{
		New.zn = this->zn;
		New.ch = this->ch + other.ch;
	}
	else
	{
		//НСК
		int c = max(this->zn, other.zn);
		while (c % this->zn != 0 || c % other.zn != 0)
		{
			c++;
		}
		New.zn = c;
		New.ch = this->ch * (New.zn / this->zn) + other.ch * (New.zn / other.zn);
	}
	return New;
}
ostream& operator<<(ostream& s, int_drib<int>& a)
{
	if (a.ch > a.zn)
	{
		a.int_part = a.ch / a.zn;
		a.ch -= a.int_part * a.zn;
	}
	s << a.int_part << " " << a.ch << "/" << a.zn;
	return s;
}
istream& operator >> (istream& s, int_drib<int>& a)
{
	cout << "Введіть цілу частину дробу: ";
	s >> a.int_part;
	cout << "Введіть чисельник:";
	s >> a.ch;
	while (!a.ch)
	{
		cout << "Введіть коректне значення чисельника:";
		s >> a.ch;
	}
	cout << "Введіть знаменник:";
	s >> a.zn;
	while (!a.zn || a.zn <= a.ch)
	{
		cout << "Введіть коректне значення знаменника:";
		s >> a.zn;
	}
	return s;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T> T NSK(T a, T b)
{
	if (a == b)return a;
	else {
		int c = max(a, b);
		while (c % a != 0 || c % b != 0)
		{
			c++;
		}
		return c;
	}
}
template <class T> string Plus(drib<T>& a, drib<T>& b)
{
	int zn = NSK(a.getZN(), b.getZN());
	int ch = a.getCH() * (zn / a.getZN()) + b.getCH() * (zn / b.getZN());
	for (int i = 2; i <= min(zn, ch); i++)
	{
		if (zn % i == 0 && ch % i == 0)
		{
			zn /= i;
			ch /= i;
		}
	}
	return to_string(ch) + "/" + to_string(zn);
}
template <class T> string Minus(drib<T>& a, drib<T>& b)
{
	int zn = NSK(a.getZN(), b.getZN());
	int ch = a.getCH() * (zn / a.getZN()) - b.getCH() * (zn / b.getZN());
	for (int i = 2; i <= min(zn, ch); i++)
	{
		if (zn % i == 0 && ch % i == 0)
		{
			zn /= i;
			ch /= i;
		}
	}
	return to_string(ch) + "/" + to_string(zn);
}
template <class T> string Multiplication(drib<T>& a, drib<T>& b)
{
	int ch = a.getCH() * b.getCH();
	int zn = a.getZN() * b.getZN();
	return to_string(ch) + "/" + to_string(zn);
}