#ifndef BIGINT_H
#define BIGINT_H
using namespace std;

//俱计
class BigInt
{
	// () default: ㏕﹚(100) 俱计
	// () ヴ種俱计


public:
	static int bigIntCounter;
	BigInt(); // default constructor, value = 0, capacity = 100, numDigits = 0
	BigInt(int value, int size = 100); // assign an integer value and capacity = size
	BigInt(const char*, int size = 100); // assign a string 
	BigInt(const BigInt&); // copy constructor
	~BigInt(); // destructor
	static int getCount()
	{
		return bigIntCounter;
	}

	void Zero();
	void Add(const BigInt&);
	void Add(int);
	void Add(const char*);
	void PrintValue();
	friend ostream& operator<<(ostream& out, BigInt a);
	friend BigInt operator+=(BigInt& a, BigInt b);
	BigInt operator=(BigInt b);
	friend BigInt operator-(BigInt a, BigInt b);
	friend BigInt operator*(BigInt a, BigInt times);
	friend BigInt operator/(BigInt a, BigInt b);
private:
	char* _digits; // Array: array–俱计计 俱计筁ㄓ璸衡ゑ耕よ獽(array材计 array材计 ...)
	int _capacity; // Array  癘拘砰甧秖 
	int _numDigits; // 俱计Τ碭计
	int sign;
	// 耎Θす砛タ璽计ㄏノ
};



ostream& operator<<(ostream& out, BigInt a)
{
	a.PrintValue();
	return out;
}

BigInt BigInt::operator=(BigInt bi)
{
	sign = bi.sign;
	_capacity = bi._capacity;
	_digits = new char [_capacity ]; // Array: 纗俱计
	Zero();
	_numDigits = bi._numDigits;

	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = bi._digits[i];
	}
	return *this;
}

BigInt operator+=(BigInt& a, BigInt b)
{
	a.Add(b);
	return a;
}

BigInt operator-=(BigInt& a, BigInt b)
{
	a = a - b;
	return a;
}


BigInt operator++(BigInt& a)
{
	a.Add(1);
	return a;
}

BigInt operator++(BigInt& a, int b)
{
	BigInt temp(a);
	a.Add(1);
	return temp;
}

BigInt operator+(BigInt a, BigInt b)
{
	a.Add(b);
	return a;
}

BigInt operator-(BigInt a, BigInt b)
{
	b.sign = b.sign * -1;
	a.Add(b);
	return a;
}

BigInt operator--(BigInt& a, int b)
{
	BigInt temp(a);
	a.Add(-1);
	return temp;
}

BigInt& operator--(BigInt& a)
{
	a.Add(-1);
	return a;
}





BigInt operator*(BigInt a, BigInt times)
{
	BigInt temp(a);
	/*if(times._numDigits==1||times._digits[0]==0)
	{
        return 0;
	}*/
	int isNegative = 0;
	if (times.sign == -1)
	{
		isNegative = 1;
		times.sign = 1;
	}
	while (times.sign == 1)
	{
		//cout << "times: " << times << "a: " << a << endl;
		a.Add(temp);
		times = times - 1;
	}
	temp.sign = temp.sign * -1;
	a.Add(temp);
	a.Add(temp);
	if (isNegative == 1)
	{
		a.sign = a.sign * -1;
	}

	//cout << "a final: " << a<<endl;
	return a;
}

BigInt operator*=(BigInt& a, BigInt times)
{
	a = a * times;
	return a;
}

BigInt operator/(BigInt a, BigInt b)
{
	int isNegative = 0;
	if (a.sign != b.sign)
	{
		isNegative = 1;
	}
	b.sign = a.sign * -1;
	BigInt temp(a);

	int counter=0;
	while (temp.sign == a.sign)
	{
		temp.Add(b);
		counter++;
	}
	counter--;
	if (isNegative == 0)
	{
		b.sign = b.sign * -1;
	}
	BigInt result(counter);
	result.sign = a.sign * b.sign;
	return result;
}

BigInt operator/=(BigInt& a, BigInt b)
{
	a = a / b;
	return a;
}

#endif
