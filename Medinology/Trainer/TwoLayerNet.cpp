#include "TwoLayerNet.h"

TwoLayerNet::TwoLayerNet(int inputsiz,int hiddensiz,int outputsiz)
{
	W1=MatrixXd::Random(inputsiz,hiddensiz);
	W2=MatrixXd::Random(hiddensiz,outputsiz);
	b1=MatrixXd::Random(1,hiddensiz);
	b2=MatrixXd::Random(1,outputsiz);
	result=MatrixXd(1,31);
}
MatrixXd TwoLayerNet::getGradW1(){return gradW1;}
MatrixXd TwoLayerNet::getGradW2(){return gradW2;}
MatrixXd TwoLayerNet::getGradb1(){return gradb1;}
MatrixXd TwoLayerNet::getGradb2(){return gradb2;}

MatrixXd TwoLayerNet::Predict(MatrixXd x)
{
	printf("x=%d X %d  W1=%d X %d W2=%d X %d b1=%d X %d b2=%d X %d",x.rows(),x.cols(),W1.rows(),W1.cols(),W2.rows(),W2.cols(),b1.rows(),b1.cols(),b2.rows(),b2.cols());
	MatrixXd a=(x*W1)+b1;
	a=Sigmoid(a);
	printf("a row=%d col=%d\n",a.rows(),a.cols());

	MatrixXd b=a*W2+b2;
	b=Softmax(b);
	printf("b row=%d col=%d\n",b.rows(),b.cols());
	result=b;
	return b;
}

void TwoLayerNet::CalcGrad(MatrixXd x,MatrixXd t)
{
	//MatrixXd result(1,31);
	//result=Predict(x);
	//printf("result %d X %d  t %d  X  %d",result.rows(),result.cols(),t.rows(),t.cols());
	MatrixXd delta=result-t;
	delta*=0.1;
	double d=delta.sum();
	gradW1=W1*d;
	gradW2=W2*d;
	gradb1=b1*d;
	gradb2=b2*d;
	/*
	//forward
	MatrixXd a1=x*W1+b1;
	MatrixXd z1=Sigmoid(a1);
	MatrixXd a2=z1*W2+b2;
	MatrixXd y=Softmax(a2);
	//Backward
	MatrixXd dy=(y-t);
	gradW2=(z1.transpose())*dy;
	gradb2=dy;
	MatrixXd da1t=dy*(W2.transpose());
	double da1=da1t.sum();
	MatrixXd dz1=Sigmoid_Grad(a1)*da1;
	gradW1=(x.transpose())*dz1;
	gradb1=dz1;
	*/
}
