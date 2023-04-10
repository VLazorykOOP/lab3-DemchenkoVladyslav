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
		  SetWidth(a);
		 SetHeigth(b);
		  SetColor(c);
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
	cout <<
		"Сеттери (замінити ширину на -5 (значення не зміниться), висоту на 6.5 та колір на \"green\") та виведення за допомогою ґеттерів:" << endl;
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
		count++;
	}   // 	 конструктор без параметрів
	Vec(int c) {
		if (c > 0)
		{
			state = OK;
			size = c;
			vec = new double [c] {0};
			count++;
		}
		else state = BAD_INIT;
	}
	Vec(int c, double n)
	{
		state = OK;
		size = c;
		vec = new double[c];
		for (int i = 0; i < size; i++)
		{
			vec[i] = n;
		}
		count++;
	}
	Vec(int a, double* v);
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
	static int getCount() {
		if (count <= 0) cout << " Немає об'єктів Vec ";
		return count;
	}
	int getState() { return state; }
	int GetAt(int i)
	{
		if (i > -1 && i < size)
			return vec[i];
		else
		{
			state = BAD_INIT;
			return vec[0];
		}
	}
	void SetAt(int i, double value)
	{
		if (i > -1 && i < size)
			vec[i] = value;
		else
		{
			state = BAD_INIT;
		}
	}
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
	Vec& operator=(const Vec&);
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
	count++;
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
	if (d == 0) {
		this->state = BAD_DIV;
		cout << " Error div \n";
		return *this;
	}
	for (int i = 0; i < size; i++)
	{
		this->vec[i] /= d;
	}
	return *this;
}
Vec Vec::Mul(double d) {
	for (int i = 0; i < size; i++)
	{
		this->vec[i] *= d;
	}
	return *this;
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
void Vec::Input()
{
	cout << "Input " << size << " elements of vector" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> vec[i];
	}
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
int Vec::count = 0;
int mainExample2()
{
	cout << "Creating first Vec" << endl;
	Vec vec1 = Vec();
	vec1.Output();
	cout << endl << "Current Vec objects: " << vec1.getCount() << endl;
	cout << endl << "Creating second Vec with size 5 and input from console" << endl;
	Vec vec2 = Vec(5);
	vec2.Input();
	vec2.Output();
	cout << endl << "Current Vec objects: " << vec1.getCount() << endl;
	cout << "Creating third Vec with size 5 and filling it with 1" << endl;
	Vec vec3 = Vec(5, 1);
	vec3.Output();
	cout << endl << "Current Vec objects: " << vec1.getCount() << endl;
	cout << "Creating fourth Vec as copy of vec3" << endl;
	Vec vec4 = Vec(vec3);
	vec4.Output();
	cout << endl << "Current Vec objects: " << vec1.getCount() << endl;
	cout << endl << "Comparing vec3 and vec4" << endl << vec3.Compare(vec4) << endl;
	cout << endl << "Comparing vec1 and vec4" << endl << vec1.Compare(vec4) << endl;
	cout << endl << "Comparing vec3 and vec4 with operator ==" << endl << (vec3 == vec4) << endl;
	cout << endl << "Comparing vec1 and vec4 with operator <" << endl << (vec1 < vec4) << endl;
	cout << "Creating fifth Vec with negative size" << endl;
	Vec vec5 = Vec(-3);
	vec5.Output();
	cout << endl << "Multiplying vec3 on 4" << endl;
	vec3.Mul(4).Output();
	cout << endl << "Dividing vec3 on 4" << endl;
	vec3.Div(4).Output();
	cout << endl << "Dividing vec3 on 0" << endl;
	vec3.Div(0).Output();
	return 0;
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

