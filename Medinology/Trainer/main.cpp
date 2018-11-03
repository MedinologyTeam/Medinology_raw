#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "platform.h"
#include "functions.h"
/* run this program using the console pauser or add your own getch, system("pause") or col loop */


int main(int argc, char** argv) {
	srand(time(NULL));
	LoadDataSet();
	Train(); 
	WriteWeights();
	return 0;
}

