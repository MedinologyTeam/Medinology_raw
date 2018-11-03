#include <iostream>
#include <Eigen/Dense>
#define PI 3.141592653589793238
using namespace Eigen;
using namespace std;

class DeepConvNet
{
	MatrixXf gradient()
	{


	}
	MatrixXf conv_params1, conv_params2, conv_params3, conv_params4, conv_params5, conv_params6;
	MatrixXf pre_node_nums, wight_init_scales,params,pre_channel_num,layers,last_layer;


};









/*#include <iostream>
#include <Eigen/Dense>
#define PI 3.141592653589793238
using namespace Eigen;
using namespace std;

int main()
{
	MatrixXf m1 = MatrixXf(8, 8);
	MatrixXf m2, m3;
	double *alpha = new double[8];
	for (int i = 0; i < 8; ++i)
	{
		alpha[i] = (float)(rand() % 255)/200.0f;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m1(i, j) = alpha[i] * cos((PI*(2.*j + 1)*i) / 16);
		}
	}
	delete alpha;

	m2 = m1.transpose();
	m3 = m1*m2;
	cout << "m1" << endl << m1 << endl << "m2" << endl << m2 << endl << "m3" << endl << m3 << endl;//출력!
	return 0;
}



// 170716
#include <stdio.h>
#include <math.h>
#include <Windows.h>
void Error(LPWSTR desc, bool fatal = false)
{
	MessageBox(0, desc, L"Error", MB_OK);
	int ans = MessageBox(0, L"프로그램을 종료하시겠습니까?", L"에러가 발생했습니다!", MB_YESNO);
	if (ans == MB_OK)
		exit(-1);
}


#define Batch(out,in,size,func)\
	for(int ___i=size-1;___i>=0;--___i)\
	{\
		out[___i]=func(in[___i]);\
	}

inline float step_functionS(float x)
{
	if (x > 0)
		return 1;
	else
		return 0;
}

float sigmoidS(float x)
{
	return 1.0 / (1 + exp(-x));
}

float reluS(float x)
{
	if (x > 0)return x;
	return 0;
}


#define sigmoid(out,in,size)\
	Batch(out,in,size,sigmoidS)
#define step_function(out,in,size)\
	Batch(out,in,size,step_functionS)
#define relu(out,in,size)\
	Batch(out,in,size,reluS)

	*/