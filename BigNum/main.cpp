#include"UintN.h"
UintN primeBignum();

bool CheckPrime2N(UintN& num1,UintN& num2) 
{
	if (UintN::isPrime(num1) == true && UintN::isPrime(num2) == true)
	{
		cout << num1 << " & " << num2 << " are prime number \n";
		return true;
	}
	else if (UintN::isPrime(num1) == true && UintN::isPrime(num2) == false)
	{
		cout << num2 << " is not prime number \n";
		cout << num1 << " is a prime number\n";
		return true;
	}
	else if (UintN::isPrime(num1) == false && UintN::isPrime(num2) == true)
	{
		cout << num1 << " is not prime number \n";
		cout << num2 << " is a prime number\n";
		return true;
	}
	else
	{
		cout <<"they aren't prime number\n";
		return false;
	}

}
void findthenextprime(UintN& num1, UintN& num2)
{
	if (CheckPrime2N(num1, num2))
	{
		if (UintN::isPrime(num1) == true && UintN::isPrime(num2) == true)
		{
			if (num1 > num2)
			{
				cout << "the next prime number bigger than " << num1 << " & " << num2 << " is " << UintN::nextPrime(num1) << endl;
			}
			else
			{
				cout << "the next prime number bigger than " << num1 << " & " << num2 << " is " << UintN::nextPrime(num2) << endl;
			}
		}
		else if (UintN::isPrime(num1) == true && UintN::isPrime(num2) == false)
		{
			
			cout << "the next prime number bigger than " << num1 << " is " << UintN::nextPrime(num1) << endl;
		}
		else if (UintN::isPrime(num1) == false && UintN::isPrime(num2) == true)
		{
			
			cout << "the next prime number bigger than " << num2 << " is " << UintN::nextPrime(num2) << endl;
		}
	}
}
int main() {
	
	UintN a, b, c;

	cin >> a >> b;
	//-------test tim so nguyen to -------
	findthenextprime(a, b);
	//-------test toan tu -------
	/*cout << a << " + " << b << a + b << endl;
	cout << a << " - " << b << a - b << endl;
	cout << a << " * " << b << a * b << endl;
	cout << a << " / " << b << a / b << endl;
	cout << a << " % " << b << a % b << endl;*/
	
	/*
	//-------test phep gan-------
	c = a + b;
	cout << a << " + " << b << c << endl;
	c = a - b;
	cout << a << " - " << b << c << endl;
	c = a * b;
	cout << a << " * " << b << c << endl;
	c = a / b;
	cout << a << " / " << b << c << endl;
	c = a % b;
	cout << a << " % " << b << c << endl;
	//-------test phep gan toan tu-------
	UintN d;
	cin >> d;
	cout << d << " + " << a;
	d += a;
	cout << d << endl;
	cout << d << " - " << a;
	d -= a;
	cout << d << endl;
	cout << d << " * " << a;
	d *= a;
	cout << d << endl;
	cout << d << " / " << a;
	d /= a;
	cout << d << endl;
	cout << d << " % " << a;
	d %= a;
	cout << d << endl; */
}
