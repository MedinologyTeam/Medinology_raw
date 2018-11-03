//Desc: Functions.cpp

#include "platform.h"
#include "functions.h"

double identity_function(double x)
{
	return x;
}

double step_function(double x)
{
	if(x>0)
		return 1;
	return 0;
}

double sigmoid(double x)
{
	return 1.0/(1.0+exp(-x));
}

double sigmoid_grad(double x)
{
	double s=sigmoid(x);
	return (1.0-s)*s;
}

double relu(double x)
{
	if(x>0)return x;
	return 0.0;
}

//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!
double relu_grad(double x)
{
	return relu(x);
}

double expfunc(double x)
{
	return exp(x);
}


MatrixXd identityFunction(MatrixXd x)
{
	return x;
}

MatrixXd stepFunction(MatrixXd x)
{
	MatrixXd m=x;
	m.unaryExpr(&step_function);
	return m;
}

MatrixXd Sigmoid(MatrixXd x)
{
	MatrixXd m=x;
	m.unaryExpr(&sigmoid);
	return m;
}

MatrixXd Sigmoid_Grad(MatrixXd x)
{
	MatrixXd m=x;
	m.unaryExpr(&sigmoid_grad);
	return m;
}

MatrixXd Relu(MatrixXd x)
{
	MatrixXd m=x;
	m.unaryExpr(&relu);
	return m;
}
/*
MatrixXd Relu_grad()
{
	MatrixXd m=MatrixXd::Zero();
	m.unaryExpr(&relu);
	return m;
	
}
*/
MatrixXd Softmax(MatrixXd x)
{
	MatrixXd y=x.array()-x.maxCoeff();
	y.unaryExpr(&expfunc);
	double s=y.sum();
	return y/s;
}

//data set 구조
//증상id=72row 
//질병id=29 
float dataset[SYMPTOM_NUM][DISEASE_NUM];

void LoadDataSet()
{
	CsvParser *csvparser = CsvParser_new("symdis.csv", ",", 0);
    CsvRow *row;
	int i,r=0;
    while ((row = CsvParser_getRow(csvparser)) ) {
        const char **rowFields = CsvParser_getFields(row);
        for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
        	int data=strtoul(rowFields[i],NULL,10);
            printf("%d",data);//�;� 그 char 값
            dataset[r][i]=data;
        }
		printf("\n");
		r++;
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);
}

#include "TwoLayerNet.h"
TwoLayerNet net(SYMPTOM_NUM,HIDDEN_NUM,DISEASE_NUM);
#define learning_rate 0.01
void Train_sub(int i)//i번째 질병을 학습시킨다. 
{
	MatrixXd x(1,SYMPTOM_NUM);
	for(int it=0;it<SYMPTOM_NUM;++it)
	{
		x(0,it)=dataset[it][i];
	}
	MatrixXd t=MatrixXd::Zero(1,DISEASE_NUM);
	t(0,i)=1;
	net.CalcGrad(x,t);
	MatrixXd gradW1=net.getGradW1();
	MatrixXd gradW2=net.getGradW2();
	MatrixXd gradb1=net.getGradb1();
	MatrixXd gradb2=net.getGradb2();
	net.W1-=(learning_rate*gradW1);
	net.W2-=(learning_rate*gradW2);
	net.b1-=(learning_rate*gradb1);
	net.b2-=(learning_rate*gradb2);
}


void Train()
{
	for(int j=0;j<200;++j)
	{
		for(int i=0;i<DISEASE_NUM;++i)
		{
			Train_sub(i);
		}
	}
}

 void WriteWeights()
 {
 	int row,col;
 	FILE *fp=fopen("Weights.txt","w");
 	float data;
 	row=SYMPTOM_NUM,col=HIDDEN_NUM;
 	fprintf(fp,"%d %d\n",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			data=net.W1(i,j);
			fprintf(fp,"%lf\n",data);
		}
	}
	row=HIDDEN_NUM,col=DISEASE_NUM;
 	fprintf(fp,"%d %d\n",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{	
			data=net.W2(i,j);
			fprintf(fp,"%lf\n",data);
		}
	}
	row=1,col=HIDDEN_NUM;
 	fprintf(fp,"%d %d\n",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			data=net.b1(i,j);
			fprintf(fp,"%lf\n",data);
		}
	}
	row=1,col=DISEASE_NUM;
 	fprintf(fp,"%d %d\n",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			data=net.b2(i,j);
			fprintf(fp,"%lf\n",data);
		}
	}
 	fclose(fp);
 }
