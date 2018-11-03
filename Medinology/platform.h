#ifndef __PLATFORM_H
#define __PLATFORM_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h>
//#include "csvparser.h"
#ifdef __GNUC__
#include <Eigen/Eigen/Dense>
#elif defined _MSC_VER
#include <Eigen/Dense>
#endif

#define PI 3.14159265359
using namespace Eigen;
using namespace std;

#define SYMPTOM_NUM 51
#define DISEASE_NUM 31
#define MEDICINE_NUM 35
#define MBA_NUM 11
#define HIDDEN_NUM 20

extern char symptom[SYMPTOM_NUM];
enum GENDER
{
	MALE,
	FEMALE
};
#endif
