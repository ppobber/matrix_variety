#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

typedef int typey;//返回分数类型
#define ZERO 0//分子分母同为零
#define DEFA 1//默认分数形式
#define ERRO -1//错误的分数类型，分母为零，分子不为零

template<typename T>
class numf {
public:
	numf() : up(0), down(0), unk(ZERO) {};
	numf(int x, int y) : up(x), down(y), unk(DEFA) {};
	numf(int x, int y, int z) : up(x), down(y), unk(DEFA) {};
	numf(const numf<T> &);
	numf(const T &);
	~numf() {};

	template<typename T>
	friend std::ostream& operator<<(std::ostream&, numf<T>&);
	template<typename T>
	friend std::istream& operator>>(std::istream&, numf<T>&);

	template<typename T>
	friend numf<T> operator+ (const numf<T>&, const numf<T>&);//类之间相加
	template<typename T>
	friend numf<T> operator- (const numf<T>&, const numf<T>&);//类之间相减
	template<typename T>
	friend numf<T> operator* (const numf<T>&, const numf<T>&);
	template<typename T>
	friend numf<T> operator/ (const numf<T>&, const numf<T>&);
	template<typename T>
	friend numf<T> operator% (const numf<T>&, const numf<T>&);//只是为了兼容矩阵类，没有实际意义。
	template<typename T>
	friend T operator< (const numf<T>&, const numf<T>&);
	template<typename T>
	friend T operator> (const numf<T>&, const numf<T>&);
	template<typename T>
	friend T operator>= (const numf<T>&, const numf<T>&);
	template<typename T>
	friend T operator!= (const numf<T>&, const numf<T>&);
	template<typename T>
	friend T operator== (const numf<T>&, const numf<T>&);
	
	template<typename T>
	friend numf<T> operator+ (const T&, const numf<T>&);
	template<typename T>
	friend numf<T> operator- (const T&, const numf<T>&);
	template<typename T>
	friend numf<T> operator* (const T&, const numf<T>&);
	template<typename T>
	friend numf<T> operator/ (const T&, const numf<T>&);
	template<typename T>
	friend T operator< (const T&, const numf<T>&);
	template<typename T>
	friend T operator> (const T&, const numf<T>&);
	template<typename T>
	friend T operator!= (const T&, const numf<T>&);
	template<typename T>
	friend T operator== (const T&, const numf<T>&);

	numf<T> &operator= (const T&);
	numf<T> &operator= (const numf<T>&);//赋值
	numf<T> operator+ (const T&);//与数字的加法
	numf<T> operator- (const T&);//与数字的减法
	numf<T> operator* (const T&);//与数字的乘法
	numf<T> operator/ (const T&);//与数字的除法

	numf<T> operator- (void);
	
	T operator< (const T&);
	T operator> (const T&);
	T operator!= (const T&);
	T operator== (const T&);

	bool print_num();//打印分数
	numf<T> &write_num(const T&, const T&);//读入一个分数
	void reduct();//约分

private:
	void swap(T &, T &);
	typey iferr();//判断分数类型
	bool chaop();

	T up;//分子
	T down;//分母
	int unk;//该分数是否错误
};

template<typename T>
bool numf<T>::print_num() {
	if (unk == ERRO)
		std::cout << "A wrong contianer." << std::endl;
	if (unk == ZERO)
		std::cout << up << std::endl;
	if (down == 1)
		std::cout << up << std::endl;
	if (unk != ERRO && unk != ZERO && down != 1)
		std::cout << up << "/" << down << std::endl;

	return true;
}

template<typename T>
numf<T> &numf<T>::write_num(const T &x, const T &y) {
	if (y == 0 && x != 0)
		std::cout << "wrong input" << std::endl;

	up = x;
	down = y;
	reduct();
	iferr();

	return *this;
}

template<typename T>
void numf<T>::reduct() {
	T con = down, ron = up, cnm;
	if (ron == 0) {
		down = 0;
		return;
	}
	if (con == 0 && ron != 0) {
		unk = ERRO;
		return;
	}
	if (ron >= con) {
		//		swap(ron, con);
		while (1) {
			cnm = ron % con;
			ron = con;
			con = cnm;
			if (con == 0)
				break;
		}
		down = down / ron;
		up = up / ron;
	}
	else {
		while (1) {
			cnm = con % ron;
			con = ron;
			ron = cnm;
			if (ron == 0)
				break;
		}
		down = down / con;
		up = up / con;
	}

	if (up > 0 && down < 0) {
		up = -up;
		down = -down;
	}
}

template<typename T>
inline std::ostream &operator<<(std::ostream &out, numf<T> &x) {
	if (x.unk == ERRO)
		out << "$$$";
	else if (x.unk == ZERO)
		out << x.up;
	else if (x.down == 1)
		out << x.up;
	else if (x.unk != ERRO && x.unk != ZERO && x.down != 1)
		out << x.up << "/" << x.down;

	return out;
}

template<typename T>
inline std::istream &operator>>(std::istream &in, numf<T> &x) {
	in >> x.up;
	x.down = 1;
	if (x.down == 0 && x.up != 0)
		std::cout << "wrong input" << std::endl;
	x.reduct();
	x.iferr();

	return in;
}

template<typename T>
numf<T> operator+ (const numf<T> &x, const numf<T> &y) {
	numf<T> sum = x;
	numf<T> st = y;
	if (st.iferr() == DEFA) {
		if (sum.iferr() == DEFA) {
			sum.down = x.down * y.down;
			sum.up = x.up * y.down + x.down * y.up;
			sum.reduct();
			if (sum.down == 0 && sum.up == 0)
				sum.unk = ZERO;
		}
		else if (sum.iferr() == ZERO) {
			sum.down = y.down;
			sum.up = y.up;
			sum.unk = y.unk;
		}
	}
	else if (st.iferr() == ZERO) {
		sum.down = x.down;
		sum.up = x.up;
		sum.unk = x.unk;
	}

	return sum;
}

template<typename T>
numf<T> operator- (const numf<T> &x, const numf<T> &y) {
	numf<T> sum = x;
	numf<T> st = y;
	if (st.iferr() == DEFA) {
		if (sum.iferr() == DEFA) {
			sum.down = x.down * y.down;
			sum.up = x.up * y.down - x.down * y.up;
			sum.reduct();
			if (sum.down == 0 && sum.up == 0)
				sum.unk = ZERO;
		}
		else if (sum.iferr() == ZERO) {
			sum.down = y.down;
			sum.up = -y.up;
			sum.unk = y.unk;
		}
	}
	else if(st.iferr() == ZERO) {
		sum.down = x.down;
		sum.up = x.up;
		sum.unk = x.unk;
	}

	return sum;
}

template<typename T>
inline numf<T> operator*(const numf<T> &x, const numf<T> &y) {
	numf<T> sum = x;
	if (sum.iferr() == DEFA) {
		sum.down = x.down * y.down;
		sum.up = x.up * y.up;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.down = 0;
		sum.up = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> operator/(const numf<T> &x, const numf<T> &y) {
	numf<T> sum = x;

	if (sum.iferr() == DEFA) {
		sum.down = x.down * y.up;
		sum.up = x.up * y.down;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.down = 0;
		sum.up = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> operator%(const numf<T> &x, const numf<T> &y) {
	numf<T> sum = x;

	if (sum.iferr() == DEFA) {
		sum.down = 1;
		sum.up = x.up % y.up;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.down = 0;
		sum.up = 0;
	}

	return sum;
}

template<typename T>
inline T operator<(const numf<T> &x, const numf<T> &y) {
	T a, b;
	a = x.up * y.down - x.down * y.up;
	b = y.down * x.down;
	if (a * b < 0)
		return 1;
	else
		return 0;
}

template<typename T>
inline T operator>(const numf<T> &x, const numf<T> &y) {
	T a, b;
	a = x.up * y.down - x.down * y.up;
	b = y.down * x.down;
	if (a * b > 0)
		return 1;
	else
		return 0;
}

template<typename T>
inline T operator>=(const numf<T> &x, const numf<T> &y) {
	T a, b;
	a = x.up * y.down - x.down * y.up;
	b = y.down * x.down;
	if (a * b < 0)
		return 0;
	else
		return 1;
}

template<typename T>
inline T operator!=(const numf<T> &x, const numf<T> &y) {
	if (x.unk != y.unk)
		return 1;
	if (x.up == y.up && x.down == y.down)
		return 0;
	else
		return 1;
}

template<typename T>
inline T operator==(const numf<T> &x, const numf<T> &y) {
	if (x.unk != y.unk)
		return 0;
	if (x.unk == ZERO && y.unk == ZERO)
		return 1;
	if (x.up == y.up && x.down == y.down)
		return 1;
	else
		return 0;
}

template<typename T>
inline numf<T> operator+(const T &x, const numf<T> &y) {
	numf<T> sum = y;
	if (sum.iferr() == DEFA) {
		sum.up = sum.up + sum.down * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	else if (sum.iferr() == ZERO) {
		sum.up = x;
		sum.down = 1;
		sum.unk = DEFA;
	}

	return sum;
}

template<typename T>
inline numf<T> operator-(const T &x, const numf<T> &y) {
	numf<T> sum = y;
	if (sum.iferr() == DEFA) {
		sum.up = sum.down * x - sum.up;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	else if (sum.iferr() == ZERO) {
		sum.up = -x;
		sum.down = 1;
		sum.unk = DEFA;
	}

	return sum;
}

template<typename T>
inline numf<T> operator*(const T &x, const numf<T> &y) {
	numf<T> sum = y;
	if (x == 0) {
		sum.up = 0;
		sum.down = 0;
	}
	if (sum.iferr() == DEFA) {
		sum.up = sum.up * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> operator/(const T &x, const numf<T> &y) {
	numf<T> sum = y;
	if (x == 0) {
		sum.up = 0;
		sum.down = 0;
	}
	if (sum.iferr() == DEFA) {
		sum.down = sum.down * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
inline T operator<(const T &x, const numf<T> &y) {
	T a, b;
	a = y.up - y.down * x;
	b = y.down;
	if (a * b > 0)
		return 1;
	else
		return 0;
}

template<typename T>
inline T operator>(const T &x, const numf<T> &y) {
	T a, b;
	a = y.up - y.down * x;
	b = y.down;
	if (a * b < 0)
		return 1;
	else
		return 0;
}

template<typename T>
inline T operator!=(const T &x, const numf<T> &y) {
	if (x == 0 && y.unk == ZERO)
		return 0;
	else if (x == 0 && y.unk != ZERO)
		return 1;

	if (y.down == 1 && x == y.up)
		return 0;
	else
		return 1;
}

template<typename T>
inline T operator==(const T &, const numf<T>&) {
	if (x == 0 && y.unk == ZERO)
		return 1;
	else if (x == 0 && y.unk != ZERO)
		return 0;

	if (y.down == 1 && x == y.up)
		return 1;
	else
		return 0;
}

template<typename T>
inline numf<T>::numf(const numf<T> &x) {
	up = x.up;
	down = x.down;
	unk = x.unk;
}

template<typename T>
inline numf<T>::numf(const T &x) {
	if (x == 0) {
		up = 0;
		down = 0;
		unk = ZERO;
	}
	else {
		up = x;
		down = 1;
		unk = DEFA;
	}
}

template<typename T>
inline numf<T> &numf<T>::operator=(const T &x) {
	if (x == 0) {
		down = 0;
		up = 0;
		unk = ZERO;
	}
	else {
		down = 1;
		up = x;
		unk = DEFA;
	}

	return *this;
}

template<typename T>
numf<T> &numf<T>::operator=(const numf<T> &x) {
	this->iferr();
	down = x.down;
	up = x.up;
	unk = x.unk;

	return *this;
}

template<typename T>
numf<T> numf<T>::operator+(const T &x) {
	numf<T> sum = *this;
	if (sum.iferr() == DEFA) {
		sum.up = sum.up + sum.down * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
numf<T> numf<T>::operator-(const T &x) {
	numf<T> sum = *this;
	if (sum.iferr() == DEFA) {
		sum.up = sum.up - sum.down * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> numf<T>::operator*(const T &x) {
	numf<T> sum = *this;
	if (x == 0) {
		sum.up = 0;
		sum.down = 0;
	}
	if (sum.iferr() == DEFA) {
		sum.up = sum.up * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> numf<T>::operator/(const T &x) {
	numf<T> sum = *this;
	if (sum.iferr() == DEFA) {
		sum.down = sum.down * x;
		sum.reduct();
		if (sum.down == 0 && sum.up == 0)
			sum.unk = ZERO;
	}
	if (sum.iferr() == ZERO) {
		sum.up = 0;
		sum.down = 0;
	}

	return sum;
}

template<typename T>
inline numf<T> numf<T>::operator-(void) {
	numf<T> sum = *this;
	if (sum.unk != ZERO)
		sum.up = -sum.up;
	return sum;
}

template<typename T>
inline T numf<T>::operator!=(const T &x) {
	if (x == 0 && this->unk == ZERO)
		return 0;
	else if (x == 0 && this->unk != ZERO)
		return 1;

	if (this->down == 1 && x == this->up)
		return 0;
	else
		return 1;
}

template<typename T>
inline T numf<T>::operator==(const T &x) {
	if (x == 0 && this->unk == ZERO)
		return 1;
	else if (x == 0 && this->unk != ZERO)
		return 0;

	if (this->down == 1 && x == this->up)
		return 1;
	else
		return 0;
}

template<typename T>
inline T numf<T>::operator<(const T &y) {
	T a, b;
	a = this->up - this->down * y;
	b = this->down;
	if (a * b < 0)
		return 1;
	else
		return 0;
}

template<typename T>
inline T numf<T>::operator>(const T &y) {
	T a, b;
	a = this->up - this->down * y;
	b = this->down;
	if (a * b > 0)
		return 1;
	else
		return 0;
}

template<typename T>
void numf<T>::swap(T &x, T &y) {
	T z = x;
	x = y;
	y = z;
}

template<typename T>
typey numf<T>::iferr() {
	if (down == 0 && up != 0) {
		unk = ERRO;
		return false;
	}
	if (down == 0 && up == 0) {
		unk = ZERO;
		return ZERO;
	}
	else {
		unk = DEFA;
		return true;
	}
	std::cout << "unknow error!" << std::endl;
}

template<typename T>
bool numf<T>::chaop() {
	if (down < 0 && up < 0) {
		down = abs(down);
		up = abs(up);
	}
	if (down < 0 && up > 0) {
		up = -up;
		down = abs(down);
	}
	if (iferr() == DEFA || iferr() == ZERO)
		return true;
	else
		return false;
}