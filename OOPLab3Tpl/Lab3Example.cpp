#if !defined(_MSC_VER)
#define CODING_VS_CODE
#endif
#include <iostream>
#include <math.h>
#if !defined(CODING_VS_CODE)
#include <clocale>
#endif
using namespace std;
enum STATE {
	OK, BAD_INIT, BAD_DIV
};
class Rectangle
{
private: double width;
	   double heigth;
	   string color;
public: Rectangle()
{
	width = 1;
	heigth = 1;
	color = "red";
}
	  Rectangle(double a, double b, string c)
	  {
		  width = a;
		  heigth = b;
		  color = c;
	  }
	  void SetWidth(double a)
	  {
		  if (a > 0)width = a;
	  }
	  void SetHeigth(double a)
	  {
		  if (a > 0)heigth = a;
	  }
	  void SetColor(string c)
	  {
		  color = c;
	  }
	  double GetWidth()
	  {
		  return width;
	  }
	  double GetHeigth()
	  {
		  return heigth;
	  }
	  string GetColor()
	  {
		  return color;
	  }
	  void Show()
	  {
		  cout << "Width: " << width << endl;
		  cout << "Heigth: " << heigth << endl;
		  cout << "Color: " << color << endl;
	  }
};

int mainExample1()
{
	cout << "Тестування класу \"прямокутник\":" << endl;
	cout << "Конструктор без параметрів:" << endl;
	Rectangle a = Rectangle();
	a.Show();
	cout << "Конструктор з параметрами (5, 5, blue):" << endl;
	a = Rectangle(5, 5, "blue");
	a.Show();
	cout << "Сеттери (замінити ширину на -5 (значення не зміниться), висоту на 6.5 та колір на \"green\") та виведення за допомогою ґеттерів:" << endl;
	a.SetWidth(-5);
	a.SetHeigth(6.5);
	a.SetColor("green");
	cout << "Width: " << a.GetWidth() << endl;
	cout << "Heigth: " << a.GetHeigth() << endl;
	cout << "Color: " << a.GetColor() << endl;
	return 1;
}
class Vec
{
	double* vec;
	int state;
	int size;
	static int count;
public:
	Vec() {
		state = OK;
		size = 1;
		vec = new double[1] {0};
	}   // 	 конструктор без параметрів
	Vec(int c) {
		state = OK;
		size = c;
		vec = new double [c] {0};
	}
	Vec(int c, double n)
	{
		state = OK;
		size = c;
		vec = new double [c] {n};
	}
	Vec(double ix, double iy);
	Vec(double* v);
	~Vec() {
		count--;
		if (vec != NULL)
			delete[]vec;
		cout << " state Vec " << state;
		cout << " Vec delete \n";
	}
	Vec(const Vec&);
	Vec Add(Vec& d);
	Vec Sub(Vec& d);
	Vec Mul(double d);
	Vec Div(double d);
	void Input();   //  !!! Без первантаження операцій    
	void Output();  //  !!! Без первантаження операцій
	bool CompLessAll(Vec& s);
	static int getCount() {
		if (count <= 0) cout << " Немає об'єктів Vec ";
		return count;
	}
	int getState() { return state; }

	bool Equals(const Vec& s)
	{
		if (size != s.size)return false;
		for (int i = 0; i < size; i++)
		{
			if (vec[i] != s.vec[i])return false;
		}
		return true;
	}
	int Compare(const Vec& s)
	{
		if (size != s.size)
		{
			if (size > s.size)return 1;
			return -1;
		}
		double abs1 = 0, abs2 = 0;
		for (int i = 0; i < size; i++)
		{
			abs1 += (vec[i] * vec[i]);
			abs2 += (s.vec[i] * s.vec[i]);
		}
		if (abs1 == abs2)return 0;
		if (abs1 > abs2)return 1;
		if (abs1 < abs2)return -1;
	}
};
Vec::Vec(const Vec& s) {
	//if (this == &s) return; //  // the expression is used in the old standard
	state = OK;
	size = s.size;
	vec = new double[size];
	for (int i = 0; i < size; i++)
	{
		vec[i] = s.vec[i];
	}
};
void Vec::Output() {
	for (int i = 0; i < size; i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl << "State: " << state;
}

Vec Vec::Add(Vec& s) {
	if (s.size == size)
	{
		Vec tmp = Vec(size);
		for (int i = 0; i < size; i++)
		{
			tmp.vec[i] = vec[i] + s.vec[i];
		}
		return tmp;
	}
}

Vec Vec::Sub(Vec& s) {
	if (s.size == size)
	{
		Vec tmp = Vec(size);
		for (int i = 0; i < size; i++)
		{
			tmp.vec[i] = vec[i] - s.vec[i];
		}
		return tmp;
	}
}
Vec Vec::Div(double d) {
	Vec tmp;
	if (fabs(d) < 1.e-25) {
		tmp.state = BAD_DIV;
		cout << " Error div \n";
		return *this;
	}
	for (int i = 0; i < size; i++)
	{
		tmp.vec[i] = vec[i] / d;
	}
	return tmp;
}
Vec Vec::Mul(double d) {
	Vec tmp = Vec(*this);
	for (int i = 0; i < size; i++)
	{
		tmp.vec[i] = vec[i] * d;
	}
	return tmp;
}
Vec& Vec::operator=(const Vec& s) {

	if (size != s.size)
	{
		if (vec) delete[] vec;
		size = s.size;
		vec = new double[size];
		state = 0;
	}
	for (int i = 0; i < size; i++)
		vec[i] = s.vec[i];
	return *this;
}
bool operator==(Vec& s1, Vec& s2) {

	return s1.Equals(s2);
}
bool operator>(Vec& s1, Vec& s2) {

	return s1.Compare(s2) == 1;
}
bool operator<(Vec& s1, Vec& s2) {

	return s1.Compare(s2) == -1;
}
bool operator>=(Vec& s1, Vec& s2) {

	return s1.Compare(s2) > -1;
}
bool operator<=(Vec& s1, Vec& s2) {

	return s1.Compare(s2) < 1;
}
int mainExample3()
{
#if !defined(CODING_VS_CODE)
	cout << "Тестування створенного класу \n";
	cout << "Тестування конструкторiв \n";
#else 
	cout << "Testing create class  \n";
	cout << "Testing crot's  \n";
#endif
	Vec ObjCDef;
	ObjCDef.Output();
	Vec ObjP1(10.0);
	ObjP1.Output();
	double  a = 1.0, b = 2.0;
	Vec  ObjP2(a, b);
	ObjP2.Output();
	Vec ObjCopy(ObjP2);
	double* v = nullptr, v2[] = { 1.2, 3.3 };
	Vec  ObjP3(v2);
	if (ObjP3.getState() != OK) cout << " ObjP3  x= 0  y= 0  \n";
	Vec  ObjP4(v2);
	if (ObjP4.getState() != OK) cout << " ObjP4 x= 0  y= 0  \n";
#if !defined(CODING_VS_CODE)
	cout << " Кiлькiсть створених об'єктiв Vec " << Vec::getCount() << endl;
	cout << "Тестування введення \n";
	ObjCDef.Input();
	cout << "Тестування функцiй \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n Кiлькiсть створених об'єктiв Vec до Sub " << Vec::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n Кiлькiсть створених об'єктiв Vec пiсля Sub " << Vec::getCount() << endl;
#else 
	cout << "Testing input \n";
	ObjCDef.Input();
	cout << "Testing gunction \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n sizes create objects Vec before  Sub " << Vec::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n  sizes create objects Vec after Sub  " << Vec::getCount() << endl;
#endif

	ObjCDef.Output();
	ObjCDef = ObjCDef.Mul(5);
	ObjCDef.Output();
	ObjCDef = ObjCDef.Div(1.3);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();

	ObjCDef = ObjCDef.Div(0.0);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();
	cout << "ObjCopy state " << ObjCopy.getState() << endl;
	if (ObjCopy.CompLessAll(ObjCDef))  cout << "ObjCopy less ObjDef  " << endl;


#if !defined(CODING_VS_CODE)
	cout << "Завершення  тестування  \n";
#else 
	cout << "Completion of testing  \n";
#endif
	return 1;

}
/*example  4
Створити тип даних - клас вектор, який має вказівник на ComplexDouble, число елементів і змінну стану. У класі визначити
o	 конструктор без параметрів( виділяє місце для одного елемента та інінціалізує його в нуль);
o	конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує масив значенням нуль);
o	конструктор із двома параметрами - розмір вектора та значення ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує значенням другого аргументу).
o	конструктор копій та операцію присвоєння; // !!!
o	деструктор звільняє пам'ять;
o	визначити функції друку, додавання;
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі масиву. Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/

#include<complex>
using namespace std;
typedef complex<double> ComplexDouble;
#define _RE 0
#define _IM 1

class ComplexVector
{
	ComplexDouble* v;
	int num;   // default num=2
	int state = 0;
public:
	ComplexVector() : ComplexVector(2) {}
	ComplexVector(int n);
	ComplexVector(int n, ComplexDouble&);
	ComplexVector(int n, ComplexDouble*);
	ComplexVector(const ComplexVector& s);
	ComplexVector& operator=(const ComplexVector& s);
	~ComplexVector() {
		std::cout << " del vec";
		if (v) delete[] v;
	}
	void Output();
	void Input();
	ComplexVector Add(ComplexVector& b);

};

ComplexVector::ComplexVector(int n) {
	if (n <= 0)    n = 2;  // default num =2;
	num = n;
	v = new ComplexDouble[n];
	for (int i = 0; i < n; i++) {
		v[i] = 0.0;
		//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
	}

}
ComplexVector::ComplexVector(int n, ComplexDouble& b) : ComplexVector(n) {
	for (int i = 0; i < num; i++) {
		v[i] = b;
		//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
	}
}

ComplexVector::ComplexVector(int n, ComplexDouble* p) : ComplexVector(n) {
	if (p != nullptr)
		for (int i = 0; i < num; i++)
			v[i] = p[i];

}

ComplexVector::ComplexVector(const ComplexVector& s) {
	// if (this == &s) return;  // the expression is used in the old standard
	num = s.num;
	v = new ComplexDouble[num];
	state = 0;
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
}

ComplexVector& ComplexVector::operator=(const ComplexVector& s) {

	if (num != s.num)
	{
		if (v) delete[] v;
		num = s.num;
		v = new ComplexDouble[num];
		state = 0;
	}
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
	return *this;
}
void ComplexVector::Input() {
	int in_num = 0;
	do {
		cout << "Input size Vec\n";
		cin >> in_num;
	} while (in_num <= 0);
	if (num != in_num) {
		num = in_num;
		if (v) delete[] v;
		v = new ComplexDouble[num];
	}
	for (int i = 0; i < num; i++) {

#if defined(_MSC_VER)
		cout << " v [ " << i << " ] real img  "; cin >> v[i] >> v[i]._Val[_IM];
#else 
		double re, im;
		cout << " v [ " << i << " ] real img  "; cin >> re >> im;
		v[i].real(re);
		v[i].imag(im);
#endif		


	}
}

void ComplexVector::Output() {
	if (num != 0) {
		for (int i = 0; i < num; i++) {
			cout << " v [ " << i << " ]   " << v[i] << '\t';
			cout << endl;
		}
	}
}

ComplexVector ComplexVector::Add(ComplexVector& b) {
	int tnum;
	tnum = num < b.num ? num : b.num;
	if (tnum >= 0) {
		ComplexVector tmp(tnum);
		for (int i = 0; i < tnum; i++) tmp.v[i] = v[i] + b.v[i];
		return tmp;
	}
	return ComplexVector(1);
}


int mainExample4()
{
	ComplexDouble a(1.0, 2), b, c;
	cout << a << endl;
#if defined(_MSC_VER)
	b._Val[_RE] = 21.3;
	b._Val[_IM] = 22.3;
#else 
	b.real(21.3);
	b.imag(22.3);
#endif	

	cout << b << endl;
	c = a + b;
	cout << c << endl;
	cout << " Test  " << endl;
	ComplexVector VecObj, VecObj1(10);
	cout << "VecObj \n";
	VecObj.Output();
	cout << "VecObj1 \n";
	VecObj1.Output();
	cout << " Input a " << endl;

#if defined(_MSC_VER)
	cin >> a >> a._Val[_IM];
#else 
	double re, im;
	cin >> re >> im;
	a.real(re);
	a.imag(im);
#endif		
	cout << a << endl;
	ComplexVector VecObj2(10, a);
	VecObj2.Output();

	VecObj.Input();
	cout << endl;
	VecObj.Output();
	VecObj1 = VecObj.Add(VecObj2);
	VecObj1.Output();

	return 1;
}

/// 

