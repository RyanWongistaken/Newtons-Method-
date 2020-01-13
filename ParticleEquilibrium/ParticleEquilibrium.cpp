////////////////////////////////////////////////////////////////
// 
// Author: Ryan Wong 
// Date Modified: 1-13-2020
// Desc: Using Newton's Method to determine force on one point
//		 utilizing US Customary Units converting to metric
//
////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CNMethod.h"

int main()
{
	using namespace std;
	CNMethod Newton;// Create Object
	Newton.main_menu(); // Launch the main menu
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
