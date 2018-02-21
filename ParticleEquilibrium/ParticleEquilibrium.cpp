// ParticleEquilibrium.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CNMethod.h"

int main()
{
	using namespace std;
	CNMethod Newton;
	Newton.main_menu();
	char option;
	int end = 0;
	//Newton.test();
	while (end == 0)
	{

		cin >> option;
		if (option == 'E' || option == 'e')
		{
			Newton.input_var();
			option = '0';//prevents the programing from looping after 1 input
		}
		else if (option == 's' || option == 'S')
		{
			Newton.calculate();
			option = '0';//prevents the programing from looping after 1 input
		}
		else if (option == 'q' || option == 'Q')
		{
			end = 1;
			option = '0';//prevents the programing from looping after 1 input
		}
	}
	return 0;
}
