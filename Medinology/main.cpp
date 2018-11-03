#include "platform.h"
#include "functions.h"
#include "TwoLayerNet.h"

void Error(LPCSTR errmsg, bool fatal)
{
	MessageBox(0, errmsg, "����", MB_OK | MB_ICONASTERISK);
	if(fatal){
		MessageBox(0,"���α׷��� �����մϴ�.","Medinology - ����",MB_OK); 
		exit(-1);
	}
}

#define INFILE "Input.txt"
/*
Encoding : ANSI / UTF-8
1: ����			M / F
2: ����			����	
3. �ӽſ���		T / F
4: ���� ����	100010101101101001011101011101
5: ���� ����	1101011101010101 
6: �������� ��	1001110101001 
*/ 



enum GENDER gender;
unsigned char age;
bool preg;
char symptom[SYMPTOM_NUM]={0,};
char prevDisease[DISEASE_NUM]={0,};
char MBA[MBA_NUM]={0,};									//Medication Being Administered

string GenStr,AgeStr,PregStr,SymStr,PrevStr,MBAStr;

int main(int argc, char** argv) {
	ifstream input(INFILE);
	if(!input.is_open())
	{
		MessageBox(0,"Input.txt ������ ���� �� �����ϴ�.\n Medinology.exe�� ���� �����ϼ���.","���� �б� ����",0);
		return -1; 
	}
	string line;
	int i=0;
	while(1)
	{
		getline(input,line);
		if(line.empty())
		{
			break;
		}
		switch(i)
		{
			case 0:
				GenStr=line;
				break;
			case 1:
				AgeStr=line;
				break;
			case 2:
				PregStr=line;
				break;
			case 3:
				SymStr=line;
				break;
			case 4:
				PrevStr=line;
				break;
			case 5:
				MBAStr=line;
				break;
		}
		//cout<<line<<endl
		++i;
		line.clear();
	}
	Parse();
	Do();
	Save();
	return 0;
}

void Parse()
{
	if (GenStr[0] == 'M')
	{
		gender = MALE;
	}
	else if (GenStr[0] == 'F')
	{
		gender = FEMALE;
	}
	else {
		Error("������ ���ڵ� �ƴϰ� ���ڵ� �ƴմϴ�!!!!");
	}
	age = strtoul(AgeStr.c_str(), NULL, 10);
	if (PregStr[0] == 'T')
	{
		preg = true;
		if (gender == MALE)
		{
			Error("���ڰ� �ӽ��߽��ϴ�!!!");
		}
	}
	else if (PregStr[0] == 'F')
	{
		preg = false;
	}
	else {
		Error("�ӽ� ���ΰ� �Ҹ��Դϴ�");
	}
	if(SymStr.length()<SYMPTOM_NUM)
	{
		Error("���� �Ľ� ����");
	}
	//if(PrevStr.length()<DISEASE_NUM)
	//{
	//	Error("���� ����  �Ľ� ����");
	//}
	//if(MBAStr.length()<MBA_NUM)
	//{
//		Error("�������� ��  �Ľ� ����");
//	}
	
	for(int i=0;i<SYMPTOM_NUM;++i)
	{
		if(SymStr[i]=='\0')
		{
			Error("���� �Ľ� ����");
		}
		if(SymStr[i]=='1')
		{
			symptom[i]=1;
		}else{
			symptom[i]=0;
		}
	}
	//for(int i=0;i<DISEASE_NUM;++i)
	//{
	//	if(PrevStr[i]=='\0')
//		{
//			Error("���� ���� �Ľ� ����");
//		}
//		if(PrevStr[i]=='1')
//		{
//			prevDisease[i]=1;
//		}else{
//			prevDisease[i]=0;
//		}
//	}
//	for(int i=0;i<MBA_NUM;++i)
//	{
//		if(MBAStr[i]=='\0')
//		{
//			Error("�������� �� �Ľ� ����");
//		}
//		if(MBAStr[i]=='1')
//		{
//			MBA[i]=1;
//		}else{
//			MBA[i]=0;
//		}
//	}
}

TwoLayerNet net(SYMPTOM_NUM,20,DISEASE_NUM);
int disease1,disease2,disease3;
int prob1,prob2,prob3;
void Do()
{
	LoadWeights("Weights.txt");
	MatrixXd x(1,SYMPTOM_NUM);
	for(int i=0;i<SYMPTOM_NUM;++i)
	{
			x(0,i)=symptom[i];
	}
	MatrixXd result=net.Predict(x);
	cout<<result<<endl;
	int i,j;
	prob1=result.maxCoeff(&i,&j)*100;
	result(i,j)=0;
	disease1=j;
	prob2=result.maxCoeff(&i,&j)*100;
	result(i,j)=0;
	disease2=j;
	prob3=result.maxCoeff(&i,&j)*100;
	disease3=j;
	//printf("disease1 : %d disease2 %d disease3 %d prob1 %d prob2 %d prob3 %d ",disease1,disease2,disease3,prob1,prob2,prob3);
}

void Save()
{
	FILE *out=fopen("Output.txt","wt");
	fprintf(out,"%d\n",prob1);
	fprintf(out,"%d\n",disease1);
	fprintf(out,"%d\n",prob2);
	fprintf(out,"%d\n",disease2);
	fprintf(out,"%d\n",prob3);
	fprintf(out,"%d\n",disease3);
	fclose(out);
}

void LoadWeights(const char *filename)

{
	FILE * input=fopen(filename,"rt");
	if(input==NULL)
	{
		Error("Weights.txt ����!!");
		return;
	}
	float data;
	int row,col;
	fscanf(input,"%d %d\n",&row,&col);
	//MessageBox(0,"W1","",0);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			fscanf(input,"%f",&data);
			//printf("%d %d %f\n",i,j,data);
			net.W1(i,j)=data;
		}
	}
	fscanf(input,"%d %d\n",&row,&col);
	
//	printf("W2 %d %d",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			fscanf(input,"%f",&data);
		//	printf("%d %d %f\n",i,j,data);
			net.W2(i,j)=data;
		}
	}
	fscanf(input,"%d %d\n",&row,&col);
	
	//printf("b1 %d %d",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			fscanf(input,"%f",&data);
		//	printf("%d %d %f\n",i,j,data);
			net.b1(i,j)=data;
		}
	}
	fscanf(input,"%d %d",&row,&col);
	
	//printf("b2 %d %d",row,col);
	for(int i= 0; i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			fscanf(input,"%f",&data);
		//	printf("%d %d %f\n",i,j,data);
			net.b2(i,j)=data;
		}
	}
	fclose(input);
}


//void LoadWeights(char *filename)
//
//{
//	FILE * input=fopen(filename,"r");
//	if(input==NULL)
//	{
//		Error("Weights.txt ����!!");
//		return;
//	}
//	char buf[30];
//	int dimx,row
//	fscanf(input,"W1 %d %d",&dimx,&dimy);
//	printf("W1 %d %d",dimx,dimy);
//	float *data=new float[dimx*dimy];
//	fread(data,sizeof(float),dimx*dimy,input);
//	for(int i= 0; i<dimx;++i)
//	{
//		for(int j=0;j<dimy;++j)
//		{
//			printf(" 1-  i:%d j:%d i*dimy+j %d \n",i,j,i*dimy+j);
//			net.W1(i,j)=data[i*dimy+j];
//		}
//	}
//	delete [] data;
//	fscanf(input,"W2 %d %d",&dimx,&dimy);
//	printf("W2 %d %d",dimx,dimy);
//	MessageBox(0,",","",0);
//	data=new float[dimx*dimy];
//	fread(data,sizeof(float),dimx*dimy,input);
//	for(int i= 0; i<dimx;++i)
//	{
//		for(int j=0;j<dimy;++j)
//		{
//			net.W2(i,j)=data[i*dimy+j];
//			printf("2  -  i:%d j:%d i*dimy+j %d \n",i,j,i*dimy+j);
//		}
//	}
//	fscanf(input,"b1 %d %d",&dimx,&dimy);
//	printf("W1 %d %d",dimx,dimy);
//	MessageBox(0,",","",0);
//	data=new float[dimx*dimy];
//	fread(data,sizeof(float),dimx*dimy,input);
//	for(int i= 0; i<dimx;++i)
//	{
//		for(int j=0;j<dimy;++j)
//		{
//			net.b1(i,j)=data[i*dimy+j];
//			printf("3  -  i:%d j:%d i*dimy+j %d \n",i,j,i*dimy+j);
//		}
//	}
//	delete [] data;	
//	fscanf(input,"b2 %d %d",&dimx,&dimy);
//	data=new float[dimx*dimy];
//	fread(data,sizeof(float),dimx*dimy,input);
//	for(int i= 0; i<dimx;++i)
//	{
//		for(int j=0;j<dimy;++j)
//		{
//			net.b2(i,j)=data[i*dimy+j];
//			printf("4  -  i:%d j:%d i*dimy+j %d \n",i,j,i*dimy+j);
//		}
//	}
//	delete [] data;
//	fclose(input);
//}
/*
MatrixXd m1 = MatrixXd(8, 8);
	MatrixXd m2, m3;

	//8*8��� m1�� ���� �־��ݴϴ�.
	double* alpha = new double[8];
	for (int i = 0; i < 8; i++) {
		if (i == 0)
			alpha[i] = 1. / (2.*sqrt(2));
		else {
			alpha[i] = 0.5;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m1(i,j) = alpha[i] * cos((PI*(2.*j + 1)*i) / 16);
		}
	}
	delete alpha;

	m2 = m1.transpose();//m2�� m1�� transpose�� ���� �־��ݴϴ�.
	m3 = m1*m2;//m3�� m1�� m2�� ���� ���� �־��ݴϴ�.
	cout <<"m1"<<endl<< m1 << endl <<"m2"<<endl<< m2 << endl <<"
*/
/*
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
	cout << "m1" << endl << m1 << endl << "m2" << endl << m2 << endl << "m3" << endl << m3 << endl;//���!
	return 0;
}



// 170716
#include <stdio.h>
#include <math.h>
#include <Windows.h>
void Error(LPWSTR desc, bool fatal = false)
{
	MessageBox(0, desc, L"Error", MB_OK);
	int ans = MessageBox(0, L"���α׷��� �����Ͻðڽ��ϱ�?", L"������ �߻��߽��ϴ�!", MB_YESNO);
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
