#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int maxlength(string s1, string s2, string s3)
{
	return max((size_t)max(s1.length(), s2.length()), s3.length());
}

bool check(string s1, string s2, string s3)
{
	//проверка результата
	int *a, *b, *c, *d, m, i, key;
	char ch;
	m = maxlength(s1, s2, s3)+2;
	a = new int[m];
	b = new int[m];
	c = new int[m];
	d = new int[m];
	key = 0;
	for (i = 0; i < m; i++)
	{
		if (i < s1.length())
		{
			ch = s1[s1.length() - i - 1];
			a[i] = atoi(&ch);
		}
		else
			a[i] = 0;

		if (i < s2.length())
		{
			ch = s2[s2.length() - i - 1];
			b[i] = atoi(&ch);
		}
		else
			b[i] = 0;

		if (i < s3.length())
		{
			ch = s3[s3.length() - i - 1];
			c[i] = atoi(&ch);
		}
		else
			c[i] = 0;

		if (a[i] + b[i] + key < 10)
		{
			d[i] = a[i] + b[i] + key;
			key = 0;
		}
		else
		{
			d[i] = a[i] + b[i] + key - 10;
			key = 1;
		}
	}
	for (i = 0; i < m; i++)
	{
		//cout << c[i] << ' ' << d[i] << '\n';
		if (c[i] != d[i]) return 0;
	}
	return 1;
}

void symbolchar(string s1, int& a, int pos)
{
	char ch;

	if (s1.length() >= pos)
	{
		ch = s1[s1.length() - pos];
		if (ch != '?')
			a = atoi(&ch);
		else
			a = -1;
	}
	else
		a = 0;
}

void symbol(string s1, string s2, string s3, int& a, int& b, int& c, int pos)
//записываем в a, b, c символы, стоящие на месте pos  (pos отсчитывается с 1, начиная с конца строки)
{
	symbolchar(s1, a, pos);
	symbolchar(s2, b, pos);
	symbolchar(s3, c, pos);
}

bool previous(string s1, string s2, string s3, int a, int b, int c, int pos)
{
	if ((a != -1) && (b != -1) && (c != -1) && (a + b == c - 1))
	{
		return 1;
	}
	else
	{
		if ((c == 9) && (pos != maxlength(s1, s2, s3)))
		{
			symbol(s1, s2, s3, a, b, c, pos + 1);
			if (previous(s1, s2, s3, a, b, c, pos + 1)) return 1;
		}
		else
			return 0;
	}
}

void work(int& a, int& b, int& c, bool following, bool key)
//заменяем "?" на числа в текущем разряде, 
{
	//один вопрос 
	if ((a == -1) && (b != -1) && (c != -1))
	{
		if (c >= b)
			a = c - b;
		else
			a = 10 + c - b;
		if (key)
		{
			if (a>0) 
				a--;
			else
				a = 9;
		}
	}
	if ((b == -1) && (a != -1) && (c != -1))
	{
		if (c >= a)
			b = c - a;
		else
			b = 10 + c - a;
		if (key)
		{
			if (b>0)
				b--;
			else
				b = 9;
		}
	}
	if ((c == -1) && (b != -1) && (a != -1))
	{
		if (a + b < 10)
			c = a + b;
		else
			c = a + b - 10;
		if (key)
		{
			if (c<9)
				c++;
			else
				c = 0;
		}
	}
	//два вопроса
	if ((a == -1) && (b == -1) && (c != -1))
	{
		if (following)
		{
			a = 9;
			if (c<9)
				b = c + 1;
			else
				b = 0;
			if (key)
			{
				a = 9;
				b = c;
			}			
		}
		else
		{
			b = 0;
			a = c;
			if (key)
			{
				if (a > 0)
					a--;
				else
					a = 9;
			}
		}
	}
	if ((a == -1) && (c == -1) && (b != -1))
	{
		if (following)
		{
			a = 9;
			if (key) a--;
			c = b - 1;
		}
		else
		{
			a = 0;
			c = b;
			if (key) {
				if (c < 9)
					c++;
				else
					c = 0;
			}
		}
	}
	if ((b == -1) && (c == -1) && (a != -1))
	{
		if (following)
		{
			c = a - 1;
			b = 9;
			if (key) b--;
		}
		else
		{
			c = a;
			b = 0;
			if (key) {
				if (c < 9)
					c++;
				else
					c = 0;
			}
		}
	}
	//три вопроса
	if ((b == -1) && (c == -1) && (a == -1))
	{
		if (following)
		{
			if (key)
			{
				a = 8; b = 1; c = 1;
			}
			a = 9; b = 1; c = 0;
		}
		else
		{
			if (key)
			{
				a = 0; b = 0; c = 1;
			}
			a = 0; b = 0; c = 0;
		}
	}
}

void main()
{
	string s, s1, s2, s3;
	int a=0, b=0, c=0;
	int pos; 
	bool following, key;
	int *key1;

	cin >> s;
	s1 = s.substr(0, s.find('+'));
	s2 = s.substr(s.find('+') + 1, s.find('=')- s.find('+')-1);
	s3 = s.substr(s.find('=') + 1, s.length() - s.find('=') - 1);

	key1 = new int[maxlength(s1, s2, s3)];

	for (pos = 1; pos <= maxlength(s1, s2, s3); pos++)
	{
		following = 0; //младший разряд требует переноса 1 в старший разряд
		if (pos != maxlength(s1, s2, s3))
		{
			symbol(s1, s2, s3, a, b, c, pos + 1);
			if (previous(s1, s2, s3, a, b, c, pos + 1)) following = 1;
		}

		key = 0; //старший разряд требует переноса 1 из младшего разряда
		key1[pos - 1] = 0;

		if (pos != 1)
		{
			symbol(s1, s2, s3, a, b, c, pos-1);
			if ((a + b == c + 10) && (key1[pos-2] != 1) || (a + b == c + 10 - 1) && (key1[pos - 2] == 1))
			{
				key = 1;
				key1[pos-1] = 1;
			}
		}
		//cout << "\n" << key1[pos-1] << '\n';
		
		symbol(s1, s2, s3, a, b, c, pos);
		
		work(a, b, c, following, key);
		
		if (s1.length() >= pos) s1[s1.length() - pos] = a + '0';
		if (s2.length() >= pos) s2[s2.length() - pos] = b + '0';
		if (s3.length() >= pos) s3[s3.length() - pos] = c + '0';
	}

	if (check(s1, s2, s3))	
		cout << s1 << '+' << s2 << '=' << s3 << '\n';
	else
	{
		//cout << s1 << '+' << s2 << '=' << s3 << '\n';
		cout << "impossible";
	}
	getchar();
	getchar();
}



