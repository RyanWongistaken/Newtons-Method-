#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <mutex>
#include <cmath>

class CNMethod
{
public:
	//Input to newton's method calculations
	float guess_Xc;//in inches
	float guess_Yc;//in inches

	float guess_Xcm;//in cm
	float guess_Ycm;//in cm
	//Coordinate of the Blue spring 
	float blue_Xs;
	float blue_Ys;
	//Coordinate of the Green spring 
	float green_Xs;
	float green_Ys;
	//Coordinate of the Red spring 
	float red_Xs;
	float red_Ys;
	//the spring constant
	float k;
	//
	float Fcs;
	//initial length of the spring in cm
	float Los;



	CNMethod();
	~CNMethod();
	void calculate();
	void input_var();
	void main_menu();
	void test();

};