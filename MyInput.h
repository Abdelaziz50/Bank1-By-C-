#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

namespace MyInput
{
	int ReadNumberInt(string Messedg)
	{
		int Number = 0;
		cout << Messedg ;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "invaled Number enter a falid on" << endl;
			cin >> Number;

		}
		return Number;
	}
	float ReadNumberFloat(string Messedg)
	{
		float Number;
		cout << Messedg ;
		cin >> Number;
		cout << endl;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "invaled Number enter a falid on" << endl;
			cin >> Number;

		}



		return Number;
	}
	short ReadNumberinRing(string Messedg, short From, short To)
	{
		short Number = 0;
		

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "invaled Number enter a falid on" << endl;
			cin >> Number;

		}

		do
		{
			cout << Messedg << endl;
			cin >> Number;

		} while (Number < From || Number > To);



		return Number;
	}
	void ReadArrayElement(int Arr[100])
	{
		int Length = 0;
		cout << "Enter Element ?";
		cin >> Length;
		cout << endl;

		for (int i = 0; i < Length; i++)
		{
			cout << "Element [" << i + 1 << "]";
			cin >> Arr[i];
			cout << endl;


		}
	}
	string ReadText(string Meassdge)
	{
		string Text;
		cout << Meassdge ;
		getline(cin >> ws, Text);
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << endl;
		return Text;

	}
	char ReadCharcter(string Meassdge)
	{
		char C;
		cout << Meassdge << endl;
		cin >> C;
		return C;

	}
}