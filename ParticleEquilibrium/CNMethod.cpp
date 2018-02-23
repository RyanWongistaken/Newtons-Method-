#include "stdafx.h"
#include "CNMethod.h"

/** @This function sets the default value for all relevant varriables
*
* @param no input parameter
* @return returns nothing
*/
CNMethod::CNMethod()
{
	//Sets the default values for the inputs
	red_Xs = 14;//inches
	red_Ys = 3;//inches
	green_Xs = 1;//inches
	green_Ys = 0;//inches
	blue_Xs = 0;//inches
	blue_Ys = 21;//inches
	guess_Xc = 5;//iniches
	guess_Yc = 9;//inches

	blue_k = 0.152;//US customary
	blue_Fcs = 0.1466;//US customary
	blue_Los = 15.2 / 2.54;//feet

	red_k = 0.152;//US customary
	red_Fcs = 0.1466;//US customary
	red_Los = 15.2 / 2.54;//feet
	
	green_k = 0.152;//US customary
	green_Fcs = 0.1466;//US customar
	green_Los = 15.2 / 2.54;//feet
}

CNMethod::~CNMethod()
{

}

/** @This function performs all calculations in Imperial units
*
* @param no input parameter
* @return returns nothing
*/
void CNMethod::calculate()
{
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

	//convert from inches to ft
	blue_Xs = blue_Xs / 12;
	blue_Ys = blue_Ys / 12;

	red_Xs = red_Xs / 12;
	red_Ys = red_Ys / 12;

	green_Xs = green_Xs / 12;
	green_Ys = green_Ys / 12;

	


	blue_lambda = blue_Fcs - (blue_k * blue_Los);
	red_lambda = red_Fcs - (red_k * red_Los);
	green_lambda = green_Fcs - (green_k * green_Los);

	//performs Newton's Method calculations 4 times inorder to determine the center 
	for (int index = 0; index < 4; index++)
	{
		Blue_Ls = sqrt(pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2));
		Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
		Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

		PhiX = ((blue_k * (blue_Xs - guess_Xc)) + (blue_lambda * ((blue_Xs - guess_Xc) / Blue_Ls))) +
			((red_k * (red_Xs - guess_Xc)) + (red_lambda * ((red_Xs - guess_Xc) / Red_Ls))) +
			((green_k * (green_Xs - guess_Xc)) + (green_lambda * ((green_Xs - guess_Xc) / Green_Ls)));

		PhiY = ((blue_k * (blue_Ys - guess_Yc)) + (blue_lambda * ((blue_Ys - guess_Yc) / Blue_Ls))) +
			((red_k * (red_Ys - guess_Yc)) + (red_lambda * ((red_Ys - guess_Yc) / Red_Ls))) +
			((green_k * (green_Ys - guess_Yc)) + (green_lambda * ((green_Ys - guess_Yc) / Green_Ls)));

		dxdx = ((blue_lambda * pow(((blue_Xs - guess_Xc) / Blue_Ls), 2) - (blue_Fcs * blue_k * Blue_Ls - blue_Los)) / Blue_Ls) +
			((red_lambda * pow(((red_Xs - guess_Xc) / Red_Ls), 2) - (red_Fcs * red_k * Red_Ls - red_Los)) / Red_Ls) +
			((green_lambda * pow(((green_Xs - guess_Xc) / Green_Ls), 2) - (green_Fcs * green_k * Green_Ls - green_Los)) / Green_Ls);

		dydy = ((blue_lambda * pow(((blue_Ys - guess_Yc) / Blue_Ls), 2) - (blue_Fcs * blue_k * Blue_Ls - blue_Los)) / Blue_Ls) +
			((red_lambda * pow(((red_Ys - guess_Yc) / Red_Ls), 2) - (red_Fcs * red_k * Red_Ls - red_Los)) / Red_Ls) +
			((green_lambda * pow(((green_Ys - guess_Yc) / Green_Ls), 2) - (green_Fcs * green_k * Green_Ls - green_Los)) / Green_Ls);

		dxdy = (((blue_Xs - guess_Xc) * blue_lambda * (blue_Ys - guess_Yc)) / (pow((pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2)), 1.5))) +
			(((red_Xs - guess_Xc) * red_lambda * (red_Ys - guess_Yc)) / (pow((pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2)), 1.5))) +
			(((green_Xs - guess_Xc) * green_lambda * (green_Ys - guess_Yc)) / (pow((pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2)), 1.5)));

		dydx = (((blue_Xs - guess_Xc) * blue_lambda * (blue_Ys - guess_Yc)) / (pow((pow((blue_Xs - guess_Xc), 2) + pow((blue_Ys - guess_Yc), 2)), 1.5))) +
			(((red_Xs - guess_Xc) * red_lambda * (red_Ys - guess_Yc)) / (pow((pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2)), 1.5))) +
			(((green_Xs - guess_Xc) * green_lambda * (green_Ys - guess_Yc)) / (pow((pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2)), 1.5)));

		secondguess_Xc = guess_Xc - (((PhiX * dydy) - (PhiY * dxdy)) / ((dxdx * dydy) - (dydx * dxdy)));
		secondguess_Yc = guess_Yc - (((-1 * PhiX * dydx) + (PhiY * dxdx)) / ((dxdx * dydy) - (dydx * dxdy)));

		guess_Xc = ((1 - 0.5) * guess_Xc) + (0.5 * secondguess_Xc);
		guess_Yc = ((1 - 0.5) * guess_Yc) + (0.5 * secondguess_Yc);
	}

	//The force in the springs (lbf)
	blue_Ts = (blue_Fcs + (blue_k * (Blue_Ls - blue_Los)));
	red_Ts = (red_Fcs + (red_k * (Red_Ls - red_Los)));
	green_Ts = (green_Fcs + (green_k * (Green_Ls - green_Los)));

	//The angle created by the spring in degrees
	blue_angle = acos((blue_Xs - guess_Xc) / Blue_Ls) * 180.0 / PI;
	red_angle = acos((red_Xs - guess_Xc) / Red_Ls) * 180.0 / PI;
	green_angle = acos((green_Xs - guess_Xc) / Green_Ls) * 180.0 / PI;

	//convert from ft to inches
	blue_Xs = blue_Xs * 12;
	blue_Ys = blue_Ys * 12;

	red_Xs = red_Xs * 12;
	red_Ys = red_Ys * 12;

	green_Xs = green_Xs * 12;
	green_Ys = green_Ys * 12;

	std::cout << "\nThe center is located at: " << "(" << guess_Xc << ", " << guess_Yc << ")" << std::endl; //prints the answer to the screen
	std::cout << "      Force[lbf] Length[in] Angle[Degrees]" << std::endl;
	std::cout << "Blue  " << blue_Ts << std::setw(11) << Blue_Ls << std::setw(11) << blue_angle << std::endl;
	std::cout << "Green " << green_Ts << std::setw(11) << Green_Ls << std::setw(11) << green_angle << std::endl;
	std::cout << "Red   " << red_Ts << std::setw(11) << Red_Ls << std::setw(11) << red_angle << std::endl;
	CNMethod::main_menu();
}

/** @This function lets the user alter the input values
*
* @param no input parameter
* @return returns nothing
*/
void CNMethod::input_var()
{
	using namespace std;
	string choice;
	float Blue_Ls;
	float Red_Ls;
	float Green_Ls;

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
		cout << "Enter the K value for the Red spring in imperial units: ";
		cin >> red_k;
		cout << "Enter the Fcs value for the Red spring in imperial units: ";
		cin >> red_Fcs;
		cout << "Enter the Los value for the Red Spring in ft: ";
		cin >> red_Los;
	}
	else if (choice[0] == 'G' || choice[0] == 'g')
	{
		cout << "Enter the x position of the Green spring in inches: ";
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
		cout << "Enter the K value for the Green spring in imperial units: ";
		cin >> green_k;
		cout << "Enter the Fcs value for the Green spring in imperial units: ";
		cin >> green_Fcs;
		cout << "Enter the Los value for the Green Spring in ft: ";
		cin >> green_Los;
	}
	else if (choice[0] == 'b' || choice[0] == 'B')
	{
		cout << "Enter the x position of the Blue spring in inches: ";
		cin >> blue_Xs;
		while (blue_Xs > 24 || blue_Xs < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> blue_Xs;
		}
		cout << "Enter the y position of the Blue spring in inches: ";
		cin >> blue_Ys;
		while (blue_Ys > 24 || blue_Ys < 0)//Error checking ensures that the value entered cannot be smaller than 0 or bigger than 24
		{
			cout << "Please enter a value between 0 and 24 inches: ";
			cin >> blue_Ys;
		}
		cout << "Enter the K value for the Blue spring in imperial units: ";
		cin >> blue_k;
		cout << "Enter the Fcs value for the Blue spring in imperial units: ";
		cin >> blue_Fcs;
		cout << "Enter the Los value for the Blue Spring in ft: ";
		cin >> blue_Los;
	}
	else if (choice[0] == 'I' || choice[0] == 'i')
	{
		//convert from inches to ft
		blue_Xs = blue_Xs / 12;
		blue_Ys = blue_Ys / 12;

		red_Xs = red_Xs / 12;
		red_Ys = red_Ys / 12;

		green_Xs = green_Xs / 12;
		green_Ys = green_Ys / 12;

		Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
		Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
		Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));

		cout << "Enter the guess for the X co-ordinate in inches: ";
		cin >> guess_Xc;
		cout << "Enter the guess for the Y co-ordinate in inches: ";
		cin >> guess_Yc;
		while (Blue_Ls < blue_Los || Green_Ls < green_Los || Red_Ls < red_Los)//Checks to make sure Ls for each spring is not larger than Los
		{
			if (Blue_Ls < blue_Los)
			{
				cout << "The guess must have a Blue Ls larger than the Blue Los " << Blue_Ls << " < " << blue_Los << endl;
			}
			else if (Green_Ls < green_Los)
			{
				cout << "The guess must have a Green Ls larger than the Green Los " << Green_Ls << " < " << green_Los << endl;
			}
			else if (Red_Ls < red_Los)
			{
				cout << "The guess must have a Red Ls larger than the Red Los " << Red_Ls << " < " << red_Los << endl;
			}
			cout << "Re-nter the guess for the X co-ordinate in inches: ";
			cin >> guess_Xc;
			cout << "Re-nter the guess for the Y co-ordinate in inches: ";
			cin >> guess_Yc;

			Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
			Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
			Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));
		}
		//convert from ft to inches
		blue_Xs = blue_Xs * 12;
		blue_Ys = blue_Ys * 12;

		red_Xs = red_Xs * 12;
		red_Ys = red_Ys * 12;

		green_Xs = green_Xs * 12;
		green_Ys = green_Ys * 12;
	}
	CNMethod::main_menu();
}

/** @Prints the main menu to the screen
*
* @param no input parameter
* @return returns nothing
*/
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


/** @A test function used to help in the creation
*
* @param no input parameter
* @return returns nothing
*/
void CNMethod::test()
{
	using namespace std;
	float ez;
	float lmao;
	
	//convert from inches to ft
	blue_Xs = blue_Xs / 12;
	blue_Ys = blue_Ys / 12;

	red_Xs = red_Xs / 12;
	red_Ys = red_Ys / 12;

	green_Xs = green_Xs / 12;
	green_Ys = green_Ys / 12;


	float Blue_Ls;
	float Red_Ls;
	float Green_Ls;
	Blue_Ls = sqrt(pow((blue_Ys - guess_Yc), 2) + pow((blue_Xs - guess_Xc), 2));
	Red_Ls = sqrt(pow((red_Xs - guess_Xc), 2) + pow((red_Ys - guess_Yc), 2));
	Green_Ls = sqrt(pow((green_Xs - guess_Xc), 2) + pow((green_Ys - guess_Yc), 2));


	cout << "Enter the x position of the Red spring in inches: ";
	cin >> guess_Xc;
	cout << "Enter the y position of the Green spring in inches: ";
	cin >> guess_Yc;
	while (Blue_Ls < blue_Los )
	{
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
	}
	cout << "it works!!";
	while(1);
}