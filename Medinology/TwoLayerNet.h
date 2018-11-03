#ifndef __TWOLAYERNET
#define __TWOLAYERNET


#include "platform.h"
#include "functions.h"

class TwoLayerNet
{
	public:
		TwoLayerNet(int inputsiz,int hiddensiz,int outputsiz);
		MatrixXd Predict(MatrixXd x);
		MatrixXd W1,W2,b1,b2;
		void CalcGrad(MatrixXd x,MatrixXd t);
		MatrixXd getGradW1();
		MatrixXd getGradW2();
		MatrixXd getGradb1();
		MatrixXd getGradb2();
	private:
		MatrixXd gradW1;
		MatrixXd gradW2;
		MatrixXd gradb1;
		MatrixXd gradb2;
		
};

#endif
