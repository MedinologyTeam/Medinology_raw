//Desc: Functions.h
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
#ifndef __PLATFORM_H
#error "Platform.h Must be included Before this header File" 
#endif
void Error(LPCSTR errmsg, bool fatal=true);
void Do();
void Parse();
void Save();
void Train();
void LoadDataSet();
void WriteWeights();


double identity_function(double x);
double step_function(double x);
double sigmoid(double x);
double sigmoid_grad(double x);
double relu(double x);
double expfunc(double x);
//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!
double relu_grad(double x);
MatrixXd identityFunction(MatrixXd x);
MatrixXd stepFunction(MatrixXd x);
MatrixXd Sigmoid(MatrixXd x);
MatrixXd Sigmoid_Grad(MatrixXd x);
MatrixXd Softmax(MatrixXd x);

#endif
