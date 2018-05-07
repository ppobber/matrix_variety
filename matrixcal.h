#pragma once

#include <iostream>
#include <string>
#include <stdio.h>

typedef int m_type;
//待用
#define err -3//错误类型

#define init -2//初始化类型

#define def 1//默认类型
#define zero 0//零矩阵
#define square 200//方阵
#define notsquare 300//非方阵

#define einheit 10//单位矩阵
#define elementary 20//初等矩阵
#define els 30//其他矩阵
#define roweChelonForm 40//行阶梯形矩阵
#define simplest 50//行最简形
//新增矩阵类型时修改settype，print_type，有必要增加judgeType。

#define ifzero(x) x % 10
#define iffeature(x) x / 10 * 10
#define ifsquare(x) x / 100 * 100

#define ERR_multiplication_type_unavailable 2
#define ERR_different_matrix 4
#define ERR_not_square_matrix 5
#define ERR_matrix_too_small 6
//待用
#define ERR_print_failed 3
#define ERR_unknown_false 0

template<typename T>
class a_Matrix {
	template<typename T>
	friend a_Matrix<T> transposition(a_Matrix<T>);
	template<typename T>
	friend T det(a_Matrix<T>);
	template<typename T>
	friend T a_Matrix<T>::LCM(T, T);
	template<typename T>
	friend T dett(T **a, int n);

	template<typename T>
	friend a_Matrix<T> operator* (const T &, const a_Matrix<T> &);

public:
	a_Matrix();
	//	a_Matriax() {};
	a_Matrix(int z);
	a_Matrix(int r, int c);
	a_Matrix(const a_Matrix<T> &);
	~a_Matrix();

	int input_Mat();//输入一些数以构成一个矩阵
	int print_Mat();//打印矩阵
	int print_type();//打印矩阵类型
	int print_error(int);//打印错误

	a_Matrix<T> &operator= (const a_Matrix<T> &);//赋值
	a_Matrix<T> operator+ (const a_Matrix<T> &) const;//矩阵之间的加法
	a_Matrix<T> operator- (const a_Matrix<T> &) const;//矩阵之间的减法
	a_Matrix<T> operator* (const a_Matrix<T> &) const;//矩阵之间的乘法
	a_Matrix<T> operator* (const T &) const;//矩阵的数乘

	a_Matrix<T> &transposition();//矩阵转置
	a_Matrix<T> &simplification();//矩阵化简
	a_Matrix<T> &inverse();//求逆矩阵
//	a_Matrix<T> &inverse_definition();//通过伴随矩阵求逆矩阵
//	a_Matrix<T> adjoint();//伴随矩阵
//	T cofactor(int, int);//代数余子式
	T determinant();//通过矩阵的化简求行列式
	T determinant_confactor();//通过代数余子式的递归求行列式

private:
	T **Mat;  //矩阵的头指针

	int row;//行数
	int column;//列数
	m_type M_type;

	void swap(T &, T &);
	void swapi(int &, int &);

	void set();//给对象内数组分配空间
	void del();
	//	void setcopy();
	//	void delcopy();

	void settype(m_type);//设置矩阵类型
						 //	void reset();
	m_type judgeType();//判断矩阵的类型，为零矩阵，单位矩阵，初等矩阵……
					   //并设置
};

template<typename T>
inline a_Matrix<T>::a_Matrix() {
	//默认构造一个一行一列的零矩阵
		row = 1;
		column = 1;
		//		M_type = init;
		set();
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				Mat[turn1][turn2] = 0;
		}
		settype(zero);
		settype(square);
}

template<typename T>
inline a_Matrix<T>::a_Matrix(int z) {
	//输入为0时，判定为初始化一个零矩阵
	//不为零时，判定为初始化一个z行z列的方阵
	if (z != 0) {
		row = z;
		column = z;
		//		M_type = init;
		set();
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				Mat[turn1][turn2] = 0;
		}
		settype(zero);
		settype(square);
	}
	else {
		row = 1;
		column = 1;
		//		M_type = init;
		set();
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				Mat[turn1][turn2] = 0;
		}
		settype(zero);
		settype(square);
	}
}

template<typename T>
inline a_Matrix<T>::a_Matrix(int r, int c) {
	//输入一个行数，一个列数。但不能初始化一个零行零列的矩阵
	if (r != 0 && c != 0) {
		row = r;
		column = c;
		//		M_type = init;
		set();
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				Mat[turn1][turn2] = 0;
		}
		settype(zero);
	}
	if (r == c)
		settype(square);
	else
		settype(notsquare);
}

template<typename T>
inline a_Matrix<T>::a_Matrix(const a_Matrix<T> &a) {
	row = a.row;
	column = a.column;
	M_type = a.M_type;

	set();
	for (int turn1 = 0; turn1 < a.row; ++turn1) {
		for (int turn2 = 0; turn2 < a.column; ++turn2)
			Mat[turn1][turn2] = a.Mat[turn1][turn2];
	}
}

template<typename T>
inline a_Matrix<T>::~a_Matrix() {
	//	del();
	for (int turn = 0; turn < row; ++turn)
		delete[] Mat[turn];
	delete[] Mat;
}

template<typename T>
inline int a_Matrix<T>::input_Mat() {
	std::cout << "input a matrix with " << row << " rows and " << column << " columns." << std::endl;
	for (int turn1 = 0; turn1 < row; ++turn1) {
		for (int turn2 = 0; turn2 < column; ++turn2)
			std::cin >> Mat[turn1][turn2];
	}
	judgeType();
	return 0;
}

template<typename T>
inline int a_Matrix<T>::print_Mat() {
	T max = 0;
	for (int turn1 = 0; turn1 < row; ++turn1) {
		for (int turn2 = 0; turn2 < column; ++turn2) {
			if (max < Mat[turn1][turn2])
				max = Mat[turn1][turn2];
		}
	}

	for (int turn1 = 0; turn1 < row; ++turn1) {
		for (int turn2 = 0; turn2 < column; ++turn2) {
			std::cout << Mat[turn1][turn2] << "   ";
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

template<typename T>
inline int a_Matrix<T>::print_type() {
	std::string ty, tz;
	if (ifzero(M_type) == zero)
		ty = "null";
	else if (iffeature(M_type) == elementary)
		ty = "elementary";
	else if (iffeature(M_type) == einheit)
		ty = "einheit";
	else if (iffeature(M_type) == roweChelonForm)
		ty = "row chelon";
	else if (iffeature(M_type) == simplest)
		ty = "row standard simplest";
	else
		ty = "default";

	if (ifsquare(M_type) == square)
		tz = "square";
	else if (ifsquare(M_type) == notsquare)
		tz = "not a square";
	std::cout << "the type of this matrix is " << ty << " and " << tz << " matrix" << std::endl;
	return 0;
}

template<typename T>
inline int a_Matrix<T>::print_error(int x) {

	if (x == ERR_multiplication_type_unavailable) {
		std::cout << "Unavailable type to multiply." << std::endl;
	}
	if (x == ERR_print_failed) {
		std::cout << "Can not print out." << std::endl;
	}
	if (x == ERR_unknown_false) {
		std::cout << "Unknown false." << std::endl;
	}
	if (x == ERR_different_matrix) {
		std::cout << "You can't add or subtract two different matrix." << std::endl;
	}
	if (x == ERR_not_square_matrix) {
		std::cout << "This is not a square matrix." << std::endl;
	}
	if (x == ERR_matrix_too_small) {
		std::cout << "The matrix is too small that can't do such operate." << std::endl;
	}
	//add more error type to complete this function.
	return x;
}

template<typename T>
inline a_Matrix<T> &a_Matrix<T>::transposition() {
	if (row == column) {
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2) {
				if (turn1 < turn2)
					swap(Mat[turn1][turn2], Mat[turn2][turn1]);
			}
		}
	}
	else {

		swapi(row, column);
		//创建一个备份
		T **backup = new T*[row];
		for (int turn = 0; turn < row; ++turn)
			backup[turn] = new T[column];

		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2) {
				backup[turn1][turn2] = Mat[turn2][turn1];
			}
		}
		//释放Mat
		for (int turn = 0; turn < column; ++turn)
			delete[] Mat[turn];
		delete[] Mat;
		Mat = backup;
	}

	return *this;
}

template<typename T>
inline a_Matrix<T> &a_Matrix<T>::simplification() {
	//分数类支持，否则会有较大误差
	
	//第一步，化为行阶梯形
	int lim1, lim2;
	if (column >= row) {
		lim1 = row - 1;//t1的限制条件
		lim2 = row - 1;//t2的限制条件
	}
	else {
		lim1 = row - 1;
		lim2 = column;
	}
	for (int t2 = 0; t2 < lim2; ++t2) {//行推移
		bool ifallzero = false;
		if (Mat[t2][t2] == 0) {//如果判断行为0，则与非零行交换
			ifallzero = true;
			for (int t1 = lim1; t1 > t2; --t1) {
				if (Mat[t1][t2] != 0) {
					for (int turn = 0; turn < column; ++turn)
						swap(Mat[t2][turn], Mat[t1][turn]);
					ifallzero = false;
					break;
				}
			}
		}
		if (ifallzero == true)//如果全为零，直接进入下一行
			continue;

		for (int t1 = lim1; t1 > t2; --t1) {//列推移
			if (Mat[t1][t2] != 0) {
//				T lcm = LCM(Mat[t2][t2], Mat[t1][t2]);
//				T ch1 = lcm / Mat[t2][t2];
//				T ch2 = lcm / Mat[t1][t2];
				T ch = Mat[t1][t2] / Mat[t2][t2]; //------------------//
				for (int turn = 0; turn < column; ++turn) {//一整行赋值
//					Mat[t2][turn] = Mat[t2][turn] * ch1;
//					Mat[t1][turn] = Mat[t1][turn] * ch2;
//					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn];
					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn] * ch; //------------------//
				}
			}
		}
	}
	return *this;
}

template<typename T>
inline a_Matrix<T> &a_Matrix<T>::inverse() {

	if (ifsquare(M_type) != square) {
		print_error(ERR_not_square_matrix);
		return *this;
	}

	a_Matrix<T> ivs(row, column);
	for (int turn = 0; turn < row; ++turn)
		ivs.Mat[turn][turn] = 1;
	ivs.settype(elementary);
	
	//第一步，化下半三角为零
	int lim1, lim2;
	
	if (column >= row) {
		lim1 = row - 1;//t1的限制条件
		lim2 = row - 1;//t2的限制条件
	}
	else {
		lim1 = row - 1;
		lim2 = column;
	}
	for (int t2 = 0; t2 < lim2; ++t2) {//行推移
		bool ifallzero = false;
		if (Mat[t2][t2] == 0) {//如果判断行为0，则与非零行交换
			ifallzero = true;
			for (int t1 = lim1; t1 > t2; --t1) {
				if (Mat[t1][t2] != 0) {
					for (int turn = 0; turn < column; ++turn) {
						swap(Mat[t2][turn], Mat[t1][turn]);
						swap(ivs.Mat[t2][turn], ivs.Mat[t1][turn]);
					}
					ifallzero = false;
					break;
				}
			}
		}
		if (ifallzero == true)//如果全为零，直接进入下一行
			continue;

		for (int t1 = lim1; t1 > t2; --t1) {//列推移
			if (Mat[t1][t2] != 0) {
				//				T lcm = LCM(Mat[t2][t2], Mat[t1][t2]);
				//				T ch1 = lcm / Mat[t2][t2];
				//				T ch2 = lcm / Mat[t1][t2];
				T ch = Mat[t1][t2] / Mat[t2][t2]; //------------------//
				for (int turn = 0; turn < column; ++turn) {//一整行赋值
//					Mat[t2][turn] = Mat[t2][turn] * ch1;
//					Mat[t1][turn] = Mat[t1][turn] * ch2;
//					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn];
					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn] * ch; //------------------//
					ivs.Mat[t1][turn] = ivs.Mat[t1][turn] - ivs.Mat[t2][turn] * ch;
				}
			}
		}

	}
	
	//第二步，化上半三角为零
	if (column >= row) {
		lim1 = 0;
		lim2 = 0;
	}
	else {
		lim1 = 0;
		lim2 = row - column;
	}
	for (int t2 = row - 1; t2 > lim2; --t2) {
		
		bool ifallzero = false;
		if (Mat[t2][column - row + t2] == 0) {
			ifallzero = true;
			for (int t1 = 0; t1 < t2; ++t1) {
				if (Mat[t1][t2] != 0) {
					for (int turn = 0; turn < column; ++turn) {
						swap(Mat[t2][turn], Mat[t1][turn]);
						swap(ivs.Mat[t2][turn], ivs.Mat[t1][turn]);
					}
					ifallzero = false;
					break;
				}
			}
		}
		if (ifallzero == true)
			continue;
		
		for (int t1 = 0; t1 < t2; ++t1) {
			if (Mat[t1][t2] != 0) {
				//				T lcm = LCM(Mat[t2][t2], Mat[t1][t2]);
				//				T ch1 = lcm / Mat[t2][t2];
				//				T ch2 = lcm / Mat[t1][t2];
				T ch = Mat[t1][t2] / Mat[t2][t2]; //------------------//
				for (int turn = 0; turn < column; ++turn) {
					//					Mat[t2][turn] = Mat[t2][turn] * ch1;
					//					Mat[t1][turn] = Mat[t1][turn] * ch2;
					//					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn];
					Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn] * ch; //------------------//
					ivs.Mat[t1][turn] = ivs.Mat[t1][turn] - ivs.Mat[t2][turn] * ch;
				}
			}
		}
	}
	//消除最后的对角矩阵
	for (int t1 = 0; t1 < row; ++t1) {
		for (int turn = 0; turn < column; ++turn) {
			ivs.Mat[t1][turn] = ivs.Mat[t1][turn] / Mat[t1][t1];
//			Mat[t1][turn] = Mat[t1][turn] / Mat[t1][turn];
		}
		Mat[t1][t1] = Mat[t1][t1] / Mat[t1][t1];
	}

	*this = ivs;
	return *this;
}

template<typename T>
inline T a_Matrix<T>::determinant() {

	if (ifsquare(M_type) == square) {

		bool ifpositive = true;
//		T outs = 1;

		int lim1, lim2;
		if (column >= row) {
			lim1 = row - 1;//t1的限制条件
			lim2 = row - 1;//t2的限制条件
		}
		else {
			lim1 = row - 1;
			lim2 = column;
		}
		for (int t2 = 0; t2 < lim2; ++t2) {//行推移
			bool ifallzero = false;
			if (Mat[t2][t2] == 0) {//如果判断行为0，则与非零行交换
				ifallzero = true;
				for (int t1 = lim1; t1 > t2; --t1) {
					if (Mat[t1][t2] != 0) {
						for (int turn = 0; turn < column; ++turn)
							swap(Mat[t2][turn], Mat[t1][turn]);
						ifallzero = false;
						ifpositive = !ifpositive;
						break;
					}
				}
			}
			if (ifallzero == true)//如果全为零，直接进入下一行
				continue;

			for (int t1 = lim1; t1 > t2; --t1) {//列推移
				if (Mat[t1][t2] != 0) {
//					T lcm = LCM(Mat[t2][t2], Mat[t1][t2]);
//					T ch1 = lcm / Mat[t2][t2];
//					T ch2 = lcm / Mat[t1][t2];
					T ch = Mat[t1][t2] / Mat[t2][t2]; //------------------//
					for (int turn = 0; turn < column; ++turn) {//一整行赋值
//						Mat[t2][turn] = Mat[t2][turn] * ch1;
//						Mat[t1][turn] = Mat[t1][turn] * ch2;
//						Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn];
						Mat[t1][turn] = Mat[t1][turn] - Mat[t2][turn] * ch; //------------------//
					}
//					outs = outs * lcm;
				}

				this->print_Mat();
			}
		}
		T sum = 1;
		for (int turn = 0; turn < row; ++turn)
			sum = sum * Mat[turn][turn];

//		std::cout << sum << "   " << outs << std::endl;
//		std::cout << sum << std::endl; //------------------//

		if (ifpositive == true) {
			return sum; //------------------//
//			return sum / outs;
		}
		else {
			return sum; //------------------//
//			return -sum / outs;
		}

	}
	else {
		print_error(ERR_not_square_matrix);
		return 0;
	}
}

template<typename T>
inline T a_Matrix<T>::determinant_confactor() {
	return dett(Mat, row);
}

template<typename T>
inline a_Matrix<T> a_Matrix<T>::operator+(const a_Matrix<T> &x) const {
	a_Matrix<T> cop = *this;
	if (x.row == cop.row && x.column == cop.column) {
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				cop.Mat[turn1][turn2] = cop.Mat[turn1][turn2] + x.Mat[turn1][turn2];
		}
	}
	else
		cop.print_error(ERR_different_matrix);
	cop.judgeType();
	return cop;
}

template<typename T>
inline a_Matrix<T> a_Matrix<T>::operator-(const a_Matrix<T> &x) const {
	a_Matrix<T> cop = *this;
	if (x.row == cop.row && x.column == cop.column) {
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				cop.Mat[turn1][turn2] = cop.Mat[turn1][turn2] - x.Mat[turn1][turn2];
		}
	}
	else
		cop.print_error(ERR_different_matrix);
	cop.judgeType();
	return cop;
}

template<typename T>
inline a_Matrix<T> a_Matrix<T>::operator*(const a_Matrix<T> &x) const {
	a_Matrix<T> cop = *this;

	if (x.row == cop.row && x.column == cop.column) {
		//方阵之间的乘法
		for (int turn1 = 0; turn1 < cop.row; ++turn1) {
			for (int turn2 = 0; turn2 < cop.column; ++turn2) {
				T tem = 0;
				for (int turn3 = 0; turn3 < cop.column; ++turn3) {
					//因为左矩阵的列和右矩阵的行相等时有意义，所以应使用左值的column
					tem = tem + cop.Mat[turn1][turn3] * x.Mat[turn3][turn2];
				}
				cop.Mat[turn1][turn2] = tem;
			}
		}
	}
	else {
		//普通矩阵之间的乘法
		if (cop.column == x.row) {

			//创建一个备份
			T **backup = new T*[cop.row];
			for (int turn = 0; turn < cop.row; ++turn)
				backup[turn] = new T[x.column];

			for (int turn1 = 0; turn1 < cop.row; ++turn1) {
				for (int turn2 = 0; turn2 < x.column; ++turn2) {
					T tem = 0;
					for (int turn3 = 0; turn3 < cop.column; ++turn3) {
						tem = tem + cop.Mat[turn1][turn3] * x.Mat[turn3][turn2];
					}
					backup[turn1][turn2] = tem;
				}
			}
			//释放Mat
			for (int turn = 0; turn < row; ++turn)
				delete[] cop.Mat[turn];
			delete[] cop.Mat;
			cop.Mat = backup;

			cop.column = x.column;
		}
		else {
			//非法的类型
			cop.print_error(ERR_multiplication_type_unavailable);
		}
	}

	cop.judgeType();
	return cop;
}

template<typename T>
inline a_Matrix<T> a_Matrix<T>::operator*(const T &x) const {
	a_Matrix<T> cop = *this;

	for (int turn1 = 0; turn1 < cop.row; ++turn1) {
		for (int turn2 = 0; turn2 < cop.column; ++turn2)
			cop.Mat[turn1][turn2] = cop.Mat[turn1][turn2] * x;
	}
	return cop;
}

template<typename T>
inline a_Matrix<T> operator*(const T &y, const a_Matrix<T> &x) {
	a_Matrix<T> cop = x;

	for (int turn1 = 0; turn1 < cop.row; ++turn1) {
		for (int turn2 = 0; turn2 < cop.column; ++turn2)
			cop.Mat[turn1][turn2] = cop.Mat[turn1][turn2] * y;
	}
	return cop;
}

template<typename T>
inline a_Matrix<T>& a_Matrix<T>::operator=(const a_Matrix<T> &x) {
	if (x.row == this->row && x.column == this->column) {
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2)
				this->Mat[turn1][turn2] = x.Mat[turn1][turn2];
		}
	}
	else {



		//创建一个备份
		T **backup = new T*[x.row];
		for (int turn = 0; turn < x.row; ++turn)
			backup[turn] = new T[x.column];

		for (int turn1 = 0; turn1 < x.row; ++turn1) {
			for (int turn2 = 0; turn2 < x.column; ++turn2)
				backup[turn1][turn2] = x.Mat[turn1][turn2];
		}
		//释放Mat
		for (int turn = 0; turn < row; ++turn)
			delete[] Mat[turn];
		delete[] Mat;
		Mat = backup;

		column = x.column;
		row = x.row;
		M_type = x.M_type;
	}
	return *this;
}

template<typename T>
inline void a_Matrix<T>::swap(T &x, T &y) {
	T z = x;
	x = y;
	y = z;
}

template<typename T>
inline void a_Matrix<T>::swapi(int &x, int &y) {
	int z = x;
	x = y;
	y = z;
}

template<typename T>
inline void a_Matrix<T>::set() {
	Mat = new T*[row];
	for (int turn = 0; turn < row; ++turn)
		Mat[turn] = new T[column];
}

template<typename T>
inline void a_Matrix<T>::del() {
	for (int turn = 0; turn < row; ++turn)
		delete[] Mat[turn];
	delete[] Mat;
}

template<typename T>
inline void a_Matrix<T>::settype(m_type x) {
	if (x == err)
		M_type = err;
	else if (x == init)
		M_type = init;
	else if (x == zero)
		M_type = M_type / 10 + zero;
	else if (x == square)
		M_type = M_type % 100 + square;
	else if (x == notsquare)
		M_type = M_type % 100 + notsquare;
	else if (x == elementary)
		M_type = elementary + square + def;
	else if (x == einheit)
		M_type = einheit + square + def;
	else if (x == roweChelonForm)
		M_type = M_type / 100 * 100 + roweChelonForm + def;
	else if (x == els)
		M_type = M_type / 100 * 100 + els + def;
}

template<typename T>
inline m_type a_Matrix<T>::judgeType() {
	bool special = false;

	bool ifz = true;
	for (int turn1 = 0; turn1 < row; ++turn1) {
		for (int turn2 = 0; turn2 < column; ++turn2) {
			if (Mat[turn1][turn2] != 0)
				ifz = false;
		}
	}
	if (ifz == true) {
		settype(zero);
		special = true;
		return zero;
	}


	//方阵情况下才满足
	if (row == column) {
		settype(square);
		bool ife = true;
		for (int turn1 = 0; turn1 < row; ++turn1) {
			for (int turn2 = 0; turn2 < column; ++turn2) {
				if (turn1 == turn2 && Mat[turn1][turn2] != 1)
					ife = false;
				if (turn1 != turn2 && Mat[turn1][turn2] != 0)
					ife = false;
			}
		}
		if (ife == true) {
			settype(einheit);
			special = true;
			return einheit;
		}
		//fix 应增加判断elementary等矩阵的方法
	}
	else
		settype(notsquare);

	if (special == false) {
		settype(els);
		return els;
	}
}

template<typename T> class a_Matrix;
template<typename T>
inline a_Matrix<T> transposition(a_Matrix<T> x) {

	if (x.row == x.column) {
		for (int turn1 = 0; turn1 < x.row; ++turn1) {
			for (int turn2 = 0; turn2 < x.column; ++turn2) {
				if (turn1 < turn2)
					x.swap(x.Mat[turn1][turn2], x.Mat[turn2][turn1]);
			}
		}
	}
	else {

		x.swapi(x.row, x.column);
		//创建一个备份
		T **backup = new T*[x.row];
		for (int turn = 0; turn < x.row; ++turn)
			backup[turn] = new T[x.column];

		for (int turn1 = 0; turn1 < x.row; ++turn1) {
			for (int turn2 = 0; turn2 < x.column; ++turn2) {
				backup[turn1][turn2] = x.Mat[turn2][turn1];
				//				printf("M %d\n", Mat[turn2][turn1]);
				//				printf("b %d\n", backup[turn1][turn2]);
			}
		}
		//释放Mat
		for (int turn = 0; turn < x.column; ++turn)
			delete[] x.Mat[turn];
		delete[] x.Mat;
		x.Mat = backup;
	}

	return x;
}

template<typename T> class a_Matrix;
template<typename T>
inline T dett(a_Matrix<T> x) {
	if (x.row == x.column) {
		//fix 化简矩阵函数


	}
	else {
		x.print_error(ERR_not_square_matrix);
		return 0;
	}
}

template<typename T> class a_Matrix;
template<typename T>
inline T LCM(T a, T b) {
	T num1 = 0, num2 = 0, c = 0;
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	if (a >= b)
	{
		num1 = a;
		num2 = b;
	}
	else
	{
		num1 = b;
		num2 = a;
	}
	while (num2 > 0)
	{
		c = num1 % num2;
		num1 = num2;
		num2 = c;
	}
	return a * b / num1;
}

template<typename T> class a_Matrix;
template<typename T>
T dett(T **a, int n) {
	T **b = new T*[n];
	for (int turn = 0; turn < n; ++turn)
		b[turn] = new T[n];

	T sum = 0;
	int p = 0, m = 0;
	if (n == 1)
		return a[0][0];
	else
		for (int i = 0; i <n; ++i) {
			for (int j = 1; j <n; ++j) {
				for (int c = 0; c <n; ++c) {
					if (c == i) {
						continue;
					}
					b[p][m] = a[j][c];
					m++;
				}
				m = 0;
				p++;
			}
			sum = sum + a[0][i] * dett(b, n - 1) * (T)pow(-1, i + 1 + 1);
			p = 0;
		}

	for (int turn = 0; turn < n; ++turn)
		delete[] b[turn];
	delete[] b;

	return sum;
}