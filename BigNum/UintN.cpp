#include "UintN.h"
UintN::UintN()
{	
	for (int i = 0; i < N; i++) 
		BigNum[i] = 0;
}

UintN::UintN(string num)
{
	
	for (int i = 0; i < N; i++) {
		BigNum[i] = 0;
	}
	int index = 0;
	// chia lien tiep de bat tat cac bits dung lai khi chuoi rong
	while (!(num.length() == 0)) 
	{
		if (convertCharToInt(num[num.length() - 1]) % 2 == 1)
		{

			onBit(index);
		}
		num = divStrFor2(num);
		index++;
	}
}

UintN::UintN(const UintN&Num)
{
	for (int i = 0; i < N; i++) {
		BigNum[i] = Num.BigNum[i];
	}
}

int UintN::convertCharToInt(char c)
{
	return c - '0';
}

char UintN::convertIntToChar(int x)
{
	switch (x)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	default:
		return '0';
	}
}

string UintN::divStrFor2(string strSource)
{
	string strDes = "";
	int num = 0;

	for (int i = 0; i < (int)strSource.length(); i++)
	{
		num = num * 10 + convertCharToInt(strSource[i]);
		strDes += convertIntToChar(num / 2);
		if (num >= 2)
		{
			num = num % 2;
		}
	}
	// ta can xoa di ki tu '0' de chuoi rong va thoat chuong trinh 
	while (true)
	{
		// kiem tra chuoi rong 
		if (strDes.length() != 0)
		{
			// kiem tra phan tu '0'
			if (strDes[0] == '0')
			{
				strDes.erase(0, 1);
				continue;
			}
		}
		break;
	}
	return strDes;
}
string UintN::mulStrFor2(string strSource)
{
	int memory = 0; // nho
	for (int i = strSource.length() - 1; i >= 0; i--) 
	{
		int temp = convertCharToInt(strSource[i]) * 2 + memory;
		strSource[i] = convertIntToChar(temp % 10);
		memory = temp / 10;
	}
	if (memory != 0) {
		strSource = convertIntToChar(memory) + strSource;
	}
	return strSource;
}

void UintN::onBit( int locate)
{
	int indexInt = locate / 32;
	int indexBit = locate % 32;

	unsigned int temp = 1;
	temp = temp <<  indexBit;
	BigNum[indexInt] = BigNum[indexInt] | temp;
}

void UintN::offBit(int locate)
{
	int indexInt = locate / 32;
	int indexBit = locate % 32;

	unsigned int temp = 1;
	temp = ~(temp <<  indexBit);
	BigNum[indexInt] = BigNum[indexInt] & temp;
}
bool UintN::getBit(int index) const
{
	int indexInt = index / 32;
	int indexBit = index % 32;

	return ((BigNum[indexInt] >> indexBit) & 1);
}
string UintN::addStrWith1(string strSource)
{
	int memory = 1;  
	int index = strSource.length() - 1;
	do {
		int temp = convertCharToInt(strSource[index]) + memory;
		strSource[index] = convertIntToChar(temp % 10);
		memory = temp / 10;
		index--;
	} while ((memory != 0) && index >= 0);

	if (memory != 0) {
		strSource = '1' + strSource;
	}
	return strSource;
}
string UintN::output(const UintN& num)
{
	string result = "0";
	for (int indexInt = N - 1; indexInt >= 0; indexInt--) 
	{
		
		if (num.BigNum[indexInt] == 0 && result[0] == '0') {
			continue;
		}
		
		for (int indexBit = 31; indexBit >= 0; indexBit--)  // nhan 2^[vi tri (i*32+j)]
		{
			result = mulStrFor2(result); 
			if (num.getBit( indexInt * 32 + indexBit)) // lay bit (1) tai vi tri thu (i*32+j)
			{
				result = addStrWith1(result);
			}
		}
	}

	return result;
}

UintN& UintN::operator = (const UintN&num)
{
	if (this == &num)
		return *this;

	for (int i = 0; i < N; i++) {
		this->BigNum[i] = num.BigNum[i];
	}

	return *this;
}

UintN& UintN::operator+=(const UintN&num)
{
	return *this = *this + num;
}

UintN& UintN::operator-=(const UintN&num)
{
	return *this = *this - num;
}

UintN& UintN::operator*=(const UintN&num)
{
	return *this = *this * num;
}

UintN& UintN::operator/=(const UintN&num)
{
	return *this = *this / num;
}

UintN& UintN::operator%=(const UintN&num)
{
	return *this = *this / num;
}

UintN UintN::operator<<(const int x) const
{
	UintN result = *this;
	for (int i = 0; i < x; i++) {
		bool startBit = 0;
		bool finalBit = 0;
		for (int IndexInt = 0; IndexInt < N; IndexInt++) {
			finalBit = result.getBit((IndexInt * 32) + (32 - 1));
			result.BigNum[IndexInt] = result.BigNum[IndexInt] << 1;
			if (startBit) {
				result.onBit(IndexInt * 32);
			}
			startBit = finalBit;

		}
	}

	return result;
}

UintN UintN::operator>>(const int x) const
{
	UintN result = *this;
	for (int i = 0; i < x; i++) {
		for (int indexInt = 0; indexInt < N; indexInt++) {
			bool bit = result.getBit((indexInt + 1) * 32);
			result.BigNum[indexInt] = result.BigNum[indexInt] >> 1;
			if (indexInt < (N - 1)) 
			{
				if (bit) 
				{
					result.onBit(((indexInt + 1) * 32) - 1);
				}
			}
		}
	}

	return result;
}

UintN UintN::operator~() const
{
	UintN result;
	for (int IndexInt = 0; IndexInt < N; IndexInt++) {
		result.BigNum[IndexInt] = ~this->BigNum[IndexInt];
	}
	return result;
}

ostream& operator<<(ostream& out, const UintN&num)
{
	string result = UintN::output(num);
	out << result;
	return out;
}

istream& operator>>(istream& in, UintN& num)
{
	string numStr;
	in >> numStr;
	num = UintN(numStr);
	return in;
}

bool operator==(const UintN&num1, const UintN&num2)
{
	for (int IndexInt = 0; IndexInt < N; IndexInt++) {
		if (num1.BigNum[IndexInt] != num2.BigNum[IndexInt])
			return false;
	}
	return true;
}

bool operator!=(const UintN&num1, const UintN&num2)
{
	for (int IndexInt = 0; IndexInt < N; IndexInt++) {
		if (num1.BigNum[IndexInt] == num2.BigNum[IndexInt])
			return false;
	}
	return true;
}

bool operator>(const UintN&num1, const UintN&num2)
{
	for (int IndexInt = N - 1; IndexInt >= 0; IndexInt--) {
		if (num1.BigNum[IndexInt] > num2.BigNum[IndexInt])
			return true;
	}
	return false;
}

bool operator<(const UintN&num1, const UintN&num2)
{
	for (int IndexInt = N - 1; IndexInt >= 0; IndexInt--) {
		if (num1.BigNum[IndexInt] < num2.BigNum[IndexInt])
			return true;
	}
	return false;
}

bool operator>=(const UintN&num1, const UintN&num2)
{
	for (int indexInt = N - 1; indexInt >= 0; indexInt--) {
		if (num1.BigNum[indexInt] < num2.BigNum[indexInt])
			return false;
		if (num1.BigNum[indexInt] > num2.BigNum[indexInt])
			return true;
	}
	return true;
	
}

bool operator<=(const UintN& num1, const UintN& num2)
{
	for (int indexInt = N - 1; indexInt >= 0; indexInt--) {
		if (num1.BigNum[indexInt] > num2.BigNum[indexInt])
			return false;
		if (num1.BigNum[indexInt] < num2.BigNum[indexInt])
			return true;
	}
	return true;
}

UintN operator^(const UintN&num1, const UintN&num2)
{
	UintN result;
	for (int indexInt = 0; indexInt < N; indexInt++) {
		result.BigNum[indexInt] = num1.BigNum[indexInt] ^ num2.BigNum[indexInt];
	}
	return result;
}

UintN operator&(const UintN&num1, const UintN&num2)
{
	UintN result;
	for (int IndexInt = 0; IndexInt < N; IndexInt++) {
		result.BigNum[IndexInt] = num1.BigNum[IndexInt] & num2.BigNum[IndexInt];
	}
	return result;
}

UintN operator+(const UintN&num1, const UintN&num2)
{
	UintN result = num1 ^ num2;
	UintN memory = num1 & num2;

	if (memory == UintN()) {
		return result;
	}
	else {
		memory = memory << 1;
		return result + memory;
	}
}

UintN operator-(const UintN&num1, const UintN&num2) 
{
	UintN compensation2 = ~num2 + UintN("1");
	return num1 + compensation2;
}

UintN operator*(const UintN&num1, const UintN&num2)
{
	UintN result;
	
		for (int indexInt = 0; indexInt < N; indexInt++) {
			if (num1.BigNum[indexInt] == 0) {
				continue;
			}
			else {
				for (int indexBit = 0; indexBit < 32; indexBit++) {
					int index = indexInt * 32 + indexBit;
					if (num2.getBit(index)) {
						result = result + (num1 << index);
					}
				}
			}
		}
	

	return result;
}

UintN operator/(const UintN& num1, const UintN& num2)
{
	UintN dividend = num1;
	UintN divisor = num2;
	UintN result = UintN();

	while ((divisor << 1) <= dividend) 
	{
		divisor = (divisor << 1);
	}

	while (divisor >= num2)
	{
		result = (result << 1);
		if (divisor <= dividend) 
		{
			dividend = dividend - divisor;
			result.onBit(0);
		}
		divisor = (divisor >> 1);
	}

	return result;
}

UintN operator%(const UintN&num1, const UintN&num2)
{
	UintN dividend = num1;
	UintN divisor = num2;

	while ((divisor << 1) <= dividend) {
		divisor = (divisor << 1);
	}

	while (divisor >= num2) {

		if (divisor <= dividend) {
			dividend = dividend - divisor;
		}
		divisor = (divisor >> 1);
	}

	return dividend;
}
bool UintN::isPrime(UintN& num)
{

	UintN zero = UintN("0");
	UintN two = UintN("2");
	if (num < two) {
		return false;
	}

	if (num == two) {
		return true;
	}

	if ((num % two) == zero) {
		return false;
	}

	for (UintN i = UintN("3"); (i * i) <= num; i = (i + two)) {
		if ((num % i) == zero) {
			return false;
		}
	}

	return true;
}

UintN UintN::nextPrime(UintN& num)
{
	UintN one("1");
	UintN prime = num;
	bool found = false;
	while (!found)
	{
		prime = prime + one;
		if (isPrime(prime))
		{
			found = true;
		}

	}
	return prime;
}
