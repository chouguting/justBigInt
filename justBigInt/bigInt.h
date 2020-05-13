#ifndef BIGINT_H
#define BIGINT_H
#include <string>
using namespace std;

//大整數
class BigInt
{
	// (一) default: 固定位(100) 的整數
	// (二) 任意位的整數


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
	int isZero();
	int division(BigInt, BigInt&);
	void PrintValue();
	friend ostream& operator<<(ostream& out, BigInt a);
	friend BigInt operator+=(BigInt& a, BigInt b);
	BigInt operator=(BigInt b);
	friend BigInt operator-(BigInt a, BigInt b);
	friend BigInt operator*(BigInt a, BigInt times);
	BigInt operator/(BigInt b);
	BigInt& operator++();
	BigInt operator++(int b);
	BigInt& operator--();
	BigInt operator--(int b);
private:
	char* _digits; // Array: array每一個整數存一位數 存整數可以倒過來存計算比較方便(array第一個存個位數 array第二個存十位數 ...)
	int _capacity; // Array  記憶體容量 
	int _numDigits; // 整數有幾位數
	int sign;
	// 擴充成允許正負數使用
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
	_digits = new char [_capacity ]; // Array: 儲存整數
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


BigInt& BigInt::operator++()
{
	Add(1);
	return *this;
}

BigInt BigInt::operator++(int b)
{
	BigInt temp(*this);
	Add(1);
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

BigInt BigInt::operator--(int b)
{
	BigInt temp(*this);
	Add(-1);
	return temp;
}

BigInt& BigInt::operator--()
{
	Add(-1);
	return *this;
}


BigInt operator*(BigInt a, BigInt times)
{
	BigInt temp(a);
	if(times._numDigits==1||times._digits[0]==0)
	{
        return 0;
	}
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

BigInt BigInt::operator/(BigInt b)
{
	/*效率不夠
	 */
	int finalSign = sign * b.sign;
	
	BigInt temp(*this);
	temp.sign = 1;
	b.sign = 1;
	int currentIndex = _numDigits - b._numDigits;
	int currentUpperCap = _numDigits - 1;

	
	string answer = "";
	
	BigInt currentRemainder;

	
	while (true)
	{
		
		if(currentIndex==-1)
		{
			break;
		}
		
		string theNum = "";
		int i;
		for (i = currentUpperCap; i >= currentIndex; i--)
		{
			theNum += to_string(temp._digits[i]);
		}
		const char* buffer = theNum.c_str();

	
		BigInt theNumThisRound(buffer);
		//cout <<"temp:"<<temp<< "\ttheNum: " << theNumThisRound << "\t";

		
		int resultThisRound = theNumThisRound.division(b, currentRemainder);

		//cout << "result this round:" << resultThisRound  <<"\tcurrentRemainder: "<<currentRemainder << endl;

		while (currentRemainder._digits[currentRemainder._numDigits - 1] == 0)
		{
			currentRemainder._numDigits = currentRemainder._numDigits - 1;
		}

		if (resultThisRound == 0)
		{
			answer += to_string(0);
			currentIndex--;
		}
		else
		{
			answer += to_string(resultThisRound);
			int j = 0;
			while(j<currentRemainder._numDigits)
			{
				temp._digits[currentIndex+j]=currentRemainder._digits[j];
				j++;
			}
			temp._numDigits = currentIndex + j;
			currentUpperCap = temp._numDigits - 1;
			currentIndex --;
		}
	}
	const char* buffer = answer.c_str();;
	BigInt lastAns(buffer);
	lastAns.sign = finalSign;
	return lastAns;
	
}

BigInt operator/=(BigInt& a, BigInt b)
{
	a = a / b;
	return a;
}

#endif
