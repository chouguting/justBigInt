#ifndef BIGINT_H
#define BIGINT_H
#include <string>
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
	if(temp.isZero()==1||times.isZero()==1)
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
	int finalSign = sign * b.sign;
	BigInt temp(*this);
	temp.sign = 1;
	b.sign = 1;

	//main idea:盽埃猭
	
	int currentIndex = _numDigits - b._numDigits; //ヘ玡埃猭ヘ夹竚
	int currentUpperCap = _numDigits - 1; //ヘ玡计程竚

	
	string answer = ""; //硂﹃氮
	
	BigInt currentRemainder; //–近緇计

	
	while (true)
	{
		
		if(currentIndex==-1)//狦ヘ夹竚琌0竒场埃Ч
		{
			break;
		}


		//т硂近璶砆埃计眖ヘ玡程秨﹍ъъヘ夹竚ゎ
		string theNum = "";
		int i;
		for (i = currentUpperCap; i >= currentIndex; i--)
		{
			theNum += to_string(temp._digits[i]);
		}
		const char* buffer = theNum.c_str(); //﹃锣char夹
		BigInt theNumThisRound(buffer);


		//眔硂近坝㎝緇计
		int resultThisRound = theNumThisRound.division(b, currentRemainder);


		//clear Zero
		while (currentRemainder._digits[currentRemainder._numDigits - 1] == 0)
		{
			currentRemainder._numDigits = currentRemainder._numDigits - 1;
		}

		if (resultThisRound == 0)//狦近坝琌0
		{
			answer += to_string(0); //р0秈氮
			currentIndex--;
		}
		else //狦近坝ぃ琌0
		{
			answer += to_string(resultThisRound); //р坝秈氮
			int j = 0;

			//р緇计钡セ计碞秈︽近埃猭
			while(j<currentRemainder._numDigits)
			{
				temp._digits[currentIndex+j]=currentRemainder._digits[j];
				j++;
			}
			temp._numDigits = currentIndex + j;
			currentUpperCap = temp._numDigits - 1; //р程砞Θ钡近緇计眔
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
