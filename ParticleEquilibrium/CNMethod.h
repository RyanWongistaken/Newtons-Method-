////////////////////////////////////////////////////////////////
// 
// Author: Ryan Wong 
// Date Modified: 1-13-2020
// Desc: Using Newton's Method to determine force on one point
//		 utilizing US Customary Units converting to metric
//
////////////////////////////////////////////////////////////////
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
#define PI 3.14159265

class CNMethod///< This class contains all variables and methods related to calculating the equilibrium equations
{				  
public:
	//Input to newton's method calculations
	float guess_Xc;//in inches
	float guess_Yc;//in inches

	//Coordinate of the Blue spring 
	float blue_Xs;
	float blue_Ys;
	//Coordinate of the Green spring 
	float green_Xs;
	float green_Ys;
	//Coordinate of the Red spring 
	float red_Xs;
	float red_Ys;

	//Blue Spring Constants
	float blue_Fcs;
	float blue_Los;
	float blue_k;
	float blue_lambda;
	float blue_Ts;
	float blue_angle;

	//Red Spring Constants
	float red_Fcs;
	float red_Los;
	float red_k;
	float red_lambda;
	float red_Ts;
	float red_angle;

	//Green Spring Constants
	float green_Fcs;
	float green_Los;
	float green_k;
	float green_lambda;
	float green_Ts;
	float green_angle;


	CNMethod();
	~CNMethod();
	void calculate();
	void input_var();
	void main_menu();
	void test();

};