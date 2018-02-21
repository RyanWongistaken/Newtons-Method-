#include "stdafx.h"
#include "CNMethod.h"

//This function is called automatically at the start and inputs the default values used for the calculations
CNMethod::CNMethod()
{
	//Sets the default values for the inputs
	red_Xs = 14;
	red_Ys = 3;
	green_Xs = 1;
	green_Ys = 0;
	blue_Xs = 0;
	blue_Ys = 21;
	guess_Xc = 5;
	guess_Yc = 9;

	k = 0.152;
	Fcs = 0.1466;
	Los = 15.2 / 2.54;//Los was measured in cm so we had to convert it to inches
}

CNMethod::~CNMethod()
{

}

//Newton's method is executed here 
void CNMethod::calculate()
{

	float lambda;
	float PhiX;
	float PhiY;
	float dxdx;
	float dydy;
	float dxdy;
	float dydx;
	float Blue_Ls;
	float Red_Ls;
	float Green_Ls;

	float secondguess_Xc = 0;
	float secondguess_Yc = 0;

	lambda = Fcs - (k * Los);

	//performs Newton's Method calculations 4 times
	for (int index = 0; index < 4; index++)
	{
		Blue_Ls = sqrt(pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2));
		Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
		Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

		PhiX = ((k * (blue_Xs - guess_Xc)) + (lambda * ((blue_Xs - guess_Xc) / Blue_Ls))) +
			((k * (red_Xs - guess_Xc)) + (lambda * ((red_Xs - guess_Xc) / Red_Ls))) +
			((k * (green_Xs - guess_Xc)) + (lambda * ((green_Xs - guess_Xc) / Green_Ls)));

		PhiY = ((k * (blue_Ys - guess_Yc)) + (lambda * ((blue_Ys - guess_Yc) / Blue_Ls))) +
			((k * (red_Ys - guess_Yc)) + (lambda * ((red_Ys - guess_Yc) / Red_Ls))) +
			((k * (green_Ys - guess_Yc)) + (lambda * ((green_Ys - guess_Yc) / Green_Ls)));

		dxdx = ((lambda * pow(((blue_Xs - guess_Xc) / Blue_Ls), 2) - (Fcs * k * Blue_Ls - Los)) / Blue_Ls) +
			((lambda * pow(((red_Xs - guess_Xc) / Red_Ls), 2) - (Fcs * k * Red_Ls - Los)) / Red_Ls) +
			((lambda * pow(((green_Xs - guess_Xc) / Green_Ls), 2) - (Fcs * k * Green_Ls - Los)) / Green_Ls);

		dydy = ((lambda * pow(((blue_Ys - guess_Yc) / Blue_Ls), 2) - (Fcs * k * Blue_Ls - Los)) / Blue_Ls) +
			((lambda * pow(((red_Ys - guess_Yc) / Red_Ls), 2) - (Fcs * k * Red_Ls - Los)) / Red_Ls) +
			((lambda * pow(((green_Ys - guess_Yc) / Green_Ls), 2) - (Fcs * k * Green_Ls - Los)) / Green_Ls);

		dxdy = (((blue_Xs - guess_Xc) * lambda * (blue_Ys - guess_Yc)) / (pow((pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2)), 1.5))) +
			(((red_Xs - guess_Xc) * lambda * (red_Ys - guess_Yc)) / (pow((pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2)), 1.5))) +
			(((green_Xs - guess_Xc) * lambda * (green_Ys - guess_Yc)) / (pow((pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2)), 1.5)));

		dydx = (((blue_Xs - guess_Xc) * lambda * (blue_Ys - guess_Yc)) / (pow((pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2)), 1.5))) +
			(((red_Xs - guess_Xc) * lambda * (red_Ys - guess_Yc)) / (pow((pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2)), 1.5))) +
			(((green_Xs - guess_Xc) * lambda * (green_Ys - guess_Yc)) / (pow((pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2)), 1.5)));

		secondguess_Xc = guess_Xc - (((PhiX * dydy) - (PhiY * dxdy)) / ((dxdx * dydy) - (dydx * dxdy)));
		secondguess_Yc = guess_Yc - (((-1 * PhiX * dydx) + (PhiY * dxdx)) / ((dxdx * dydy) - (dydx * dxdy)));

		guess_Xc = ((1 - 0.5) * guess_Xc) + (0.5 * secondguess_Xc);
		guess_Yc = ((1 - 0.5) * guess_Yc) + (0.5 * secondguess_Yc);
	}

	/*
	nothing but failure here
	guess_Xcm = guess_Xc;
	guess_Ycm = guess_Yc;
	float guess_Xcm1;
	float guess_Ycm1;
	for (int index = 0; index < 4; index++)
	{
		PhiX = (k * (blue_Xs - guess_Xcm) + (lambda * ((blue_Xs - guess_Xcm) / (sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2)))))) +
			(k * (green_Xs - guess_Xcm) + (lambda * ((green_Xs - guess_Xcm) / (sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2)))))) +
			(k * (red_Xs - guess_Xcm) + (lambda * ((red_Xs - guess_Xcm) / (sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2))))));

		PhiY = (k * (blue_Ys - guess_Ycm) + (lambda * ((blue_Ys - guess_Ycm) / (sqrt(pow((blue_Ys - guess_Ycm), 2) + pow((blue_Xs - guess_Xcm), 2)))))) +
			(k * (green_Ys - guess_Ycm) + (lambda * ((green_Ys - guess_Ycm) / (sqrt(pow((green_Ys - guess_Ycm), 2) + pow((green_Xs - guess_Xcm), 2)))))) +
			(k * (red_Ys - guess_Ycm) + (lambda * ((red_Xs - guess_Ycm) / (sqrt(pow((red_Ys - guess_Ycm), 2) + pow((red_Xs - guess_Xc), 2))))));
		
		dxdx = (((lambda * pow(((blue_Xs - guess_Xcm) / (sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))))) +
			(((lambda * pow(((green_Xs - guess_Xcm) / (sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))))) +
			(((lambda * pow(((red_Xs - guess_Xcm) / (sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2)))));
	
		dydy = (((lambda * pow(((blue_Ys - guess_Ycm) / (sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))))) +
			(((lambda * pow(((green_Ys - guess_Ycm) / (sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))))) +
			(((lambda * pow(((red_Ys - guess_Ycm) / (sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2)))), 0.5)) - (Fcs - k * ((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2))) - Los))) / ((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2)))));
		
		dxdy = (((blue_Xs - guess_Xcm) * lambda * (blue_Ys - guess_Ycm)) / pow((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))), 1.5)) +
			(((green_Xs - guess_Xcm) * lambda * (green_Ys - guess_Ycm)) / pow((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))), 1.5)) +
			(((red_Xs - guess_Xcm) * lambda * (red_Ys - guess_Ycm)) / pow((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2))), 1.5));
		
		dydx = (((blue_Ys - guess_Ycm) * lambda * (blue_Xs - guess_Xcm)) / pow((sqrt(pow((blue_Xs - guess_Xcm), 2) + pow((blue_Ys - guess_Ycm), 2))), 1.5)) +
			(((green_Ys - guess_Ycm) * lambda * (green_Xs - guess_Xcm)) / pow((sqrt(pow((green_Xs - guess_Xcm), 2) + pow((green_Ys - guess_Ycm), 2))), 1.5)) +
			(((red_Ys - guess_Ycm) * lambda * (red_Xs - guess_Xcm)) / pow((sqrt(pow((red_Xs - guess_Xcm), 2) + pow((red_Ys - guess_Ycm), 2))), 1.5));
	
		guess_Xcm1 = guess_Xcm - (((PhiX * dydy) - (PhiY * dxdy)) / ((dxdx * dydy) - (dydx * dxdy)));
		guess_Ycm1 = guess_Ycm - (((-1 * PhiX * dydx) + (PhiY * dxdx)) / ((dxdx * dydy) - (dydx * dxdy)));

		guess_Xcm = guess_Xcm1;
		guess_Ycm = guess_Ycm1;
	
	}
	guess_Xc = guess_Xcm;
	guess_Yc = guess_Ycm;
	*/

	std::cout << "The center is located at: " << "(" << guess_Xc << ", " << guess_Yc << ")" << std::endl; //prints the answer to the screen
	CNMethod::main_menu();
}

//this function enalbes the user to change the parameters set by the programing in the begining
void CNMethod::input_var()
{
	using namespace std;
	string choice;
	float Blue_Ls;
	float Red_Ls;
	float Green_Ls;
	Blue_Ls = sqrt(pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2));
	Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
	Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

	cout << "\nWhat value would you like to edit?" << endl;
	cout << "(I)nital guess values" << endl;
	cout << "(R)ed Spring values" << endl;
	cout << "(G)reen Spring values" << endl;
	cout << "(B)lue Spring values" << endl;
	cin >> choice;
	while (choice[0] != 'R' && choice[0] != 'r' && choice[0] != 'I' && choice[0] != 'i' && choice[0] != 'G' && choice[0] != 'g' && choice[0] != 'b' && choice[0] != 'B')
	{
		cout << "Please enter an option listed above : ";
		cin >> choice;
	}

	if (choice[0] == 'R' || choice[0] == 'r')
	{
		cout << "Enter the x position of the Red spring in inches: ";
		cin >> red_Xs;
		while (red_Xs > 24 || red_Xs < 0) //Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> red_Xs;
		}
		cout << "Enter the y position of the Red spring in inches: ";
		cin >> red_Ys;
		while (red_Ys > 24 || red_Ys < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> red_Ys;
		}
	}
	else if (choice[0] == 'G' || choice[0] == 'g')
	{
		cout << "Enter the x position of the Red spring in inches: ";
		cin >> green_Xs;
		while (green_Xs > 24 || green_Xs < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> green_Xs;
		}
		cout << "Enter the y position of the Green spring in inches: ";
		cin >> green_Ys;
		while (green_Ys > 24 || green_Ys < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> green_Ys;
		}
	}
	else if (choice[0] == 'b' || choice[0] == 'B')
	{
		cout << "Enter the x position of the Red spring in inches: ";
		cin >> blue_Xs;
		while (blue_Xs > 24 || blue_Xs < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> blue_Xs;
		}
		cout << "Enter the y position of the Green spring in inches: ";
		cin >> blue_Ys;
		while (blue_Ys > 24 || blue_Ys < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> blue_Ys;
		}

	}
	else if (choice[0] == 'I' || choice[0] == 'i')
	{
		cout << "Enter the guess for the X co-ordinate in inches: ";
		cin >> guess_Xc;
		cout << "Enter the guess for the Y co-ordinate in inches: ";
		cin >> guess_Yc;
		while (Blue_Ls < Los || Green_Ls < Los || Red_Ls < Los)//Checks to make sure Ls for each spring is not larger than Los
		{
			if (Blue_Ls < Los)
			{
				cout << "The guess must have a Blue Ls larger than Los " << Blue_Ls << " < " << Los << endl;
			}
			else if (Green_Ls < Los)
			{
				cout << "The guess must have a Green Ls larger than Los " << Green_Ls << " < " << Los << endl;
			}
			else if (Red_Ls < Los)
			{
				cout << "The guess must have a Red Ls larger than Los " << Red_Ls << " < " << Los << endl;
			}
			cout << "Re-nter the guess for the X co-ordinate in inches: ";
			cin >> guess_Xc;
			cout << "Re-nter the guess for the Y co-ordinate in inches: ";
			cin >> guess_Yc;

			Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
			Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
			Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

		}

	}
	CNMethod::main_menu();
}

//this function prints the main menu to the screen
void CNMethod::main_menu()
{
	using namespace std; 
	cout << "\n***********************************************************" << endl;
	cout << "System Modeling using Newtons Method by Ryan, Ian and Mark" << endl;
	cout << "***********************************************************" << endl;
	cout << "Current values used in the simulation are as follows... " << endl;
	cout << "Guess for Xc: " << setw(3) << guess_Xc << " Guess for Yc: " << setw(3) << guess_Yc << endl;
	cout << "Coordinates of the Red spring: " << "(" << red_Xs << ", " << red_Ys << ")" << endl;
	cout << "Coordinates of the Green spring: " << "(" << green_Xs << ", " << green_Ys << ")" << endl;
	cout << "Coordinates of the Blue spring: " << "(" << blue_Xs << ", " << blue_Ys << ")" << endl;
	cout << "(E)dit Inputs" << endl;
	cout << "(S)tart the calculations" << endl;
	cout << "(Q)uit" << endl;
}

//this function was used to simply help me test things quickly without having to rewrite significant porptions of code
void CNMethod::test()
{
	using namespace std;
	float ez;
	float lmao;
	float lambda;
	float Blue_Ls;
	float Red_Ls;
	float Green_Ls;
	guess_Xcm = guess_Xc;
	guess_Ycm = guess_Yc;
	Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
	Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
	Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));
	lambda = Fcs - (k * Los);

	cout << "Enter the x position of the Red spring in inches: ";
	cin >> guess_Xc;
	cout << "Enter the y position of the Green spring in inches: ";
	cin >> guess_Yc;
	while (Blue_Ls < Los || Green_Ls < Los || Red_Ls < Los)
	{
		Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
		Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
		Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

		if (Blue_Ls < Los)
		{
			cout << "The guess must have a Blue Ls larger than Los " << Blue_Ls << " < " << Los << endl;
		}
		else if (Green_Ls < Los)
		{
			cout << "The guess must have a Green Ls larger than Los " << Green_Ls << " < " << Los << endl;
		}
		else if (Red_Ls < Los)
		{
			cout << "The guess must have a Red Ls larger than Los " << Red_Ls << " < " << Los << endl;
		}
		cout << "Re-enter the x position of the Red spring in inches: ";
		cin >> guess_Xc;
		cout << "Re-enter the y position of the Green spring in inches: ";
		cin >> guess_Yc;
	}
	cout << "it works!!";
	while(1);
}