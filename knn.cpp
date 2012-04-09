#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
using namespace std;
#define M 3000
#define N 100


/*定义一个字符的类*/
class letter
{
public:
	char c;
	int array[16];
	float distance;
};


/*定义训练字符类数组、识别字符类数组*/
letter yletter[M];
letter nletter[N];
letter temp;


/*读取文件函数，将训练样本从磁盘文件yletter.txt读入yletter[M]数组中*/
void Get_from_yletter()
{
	int i,j,n=0;
	ifstream infile("letter.txt",ios::in);
    if(!infile)
	{
	    cerr<<"open error!"<<endl;
		exit(1);
	}
	for(i=0;i<M;i++)
	{
		infile>>yletter[i].c;
		//cout<<yletter[i].c<<" ";
		//n++;
		for(j=0;j<16;j++)
		{
			infile>>yletter[i].array[j];
			//cout<<yletter[i].array[j]<<" ";
			//n++;
		}
		//if(n%17==0)
			//cout<<endl;
	}
	infile.close();
}


/*读取文件函数，将测试样本从磁盘文件nletter.txt读入nletter[N]数组中*/
void Get_from_nletter()
{
	int i,j;
	ifstream infile("sum.txt",ios::in);
    if(!infile)
	{
		cerr<<"open error!"<<endl;
		exit(1);
	}
	for(i=0;i<N;i++)
	{
		infile>>nletter[i].c;
		for(j=0;j<16;j++)
		{
			infile>>nletter[i].array[j];
		}
	}
	infile.close();
}


/*欧氏距离函数，计算一个测试样本与各个训练样本之间的距离*/
void Distance(letter * L)
{
	int i,j;
	float z;
	for(i=0;i<M;i++)
	{
		for(j=0,z=0;j<16;j++)
		{
			z=z+(yletter[i].array[j]-(*L).array[j])*(yletter[i].array[j]-(*L).array[j]);
		}
        yletter[i].distance= (float) sqrt (z);
	}

}


/*排序函数，将距离按从小到大的顺序排列*/
void Sort()
{
	int i,j;
	for(i=0;i<M-1;i++)
		for(j=i+1;j<M;j++)
		{
			if(yletter[i].distance>yletter[j].distance)
			{
				temp=yletter[i];
				yletter[i]=yletter[j];
				yletter[j]=temp;
			}
		}
}


/*分类函数，根据用户输入的k值来确定测试样本属于哪一类*/
char Knn(int q)
{
	int i,j,max;
	int array[26];
	for(i=0;i<26;i++)
	{
		array[i]=0;
	}

	for(i=0;i<q;i++)
	{
		if(yletter[i].c=='A') array[0]++;
		else if(yletter[i].c=='B') array[1]++;
		else if(yletter[i].c=='C') array[2]++;
		else if(yletter[i].c=='D') array[3]++;
		else if(yletter[i].c=='E') array[4]++;
		else if(yletter[i].c=='F') array[5]++;
		else if(yletter[i].c=='G') array[6]++;
		else if(yletter[i].c=='H') array[7]++;
		else if(yletter[i].c=='I') array[8]++;
		else if(yletter[i].c=='J') array[9]++;
		else if(yletter[i].c=='K') array[10]++;
		else if(yletter[i].c=='L') array[11]++;
		else if(yletter[i].c=='M') array[12]++;
		else if(yletter[i].c=='N') array[13]++;
		else if(yletter[i].c=='O') array[14]++;
		else if(yletter[i].c=='P') array[15]++;
		else if(yletter[i].c=='Q') array[16]++;
		else if(yletter[i].c=='R') array[17]++;
		else if(yletter[i].c=='S') array[18]++;
		else if(yletter[i].c=='T') array[19]++;
		else if(yletter[i].c=='U') array[20]++;
		else if(yletter[i].c=='V') array[21]++;
		else if(yletter[i].c=='W') array[22]++;
		else if(yletter[i].c=='X') array[23]++;
		else if(yletter[i].c=='Y') array[24]++;
		else array[25]++;
	}
	max=array[0];
	j=0;
	for(i=1;i<26;i++)
		if(array[i]>max)
		{
			max=array[i];
			j=i;
		}
	return (char)(j+65);
}


int main()
{
	cout<<"训练样本为"<<M<<"个："<<endl;
	Get_from_yletter();
	cout<<endl<<endl;
	cout<<"测试样本为"<<N<<"个："<<endl;
	Get_from_nletter();
	do
	{int i,k;
	int m=0,n=0;
	char c1;
	letter * p;
	cout<<"请输入K值：";
	cin>>k;
    for(i=0;i<N;i++)
	{
		p=&nletter[i];
		Distance(p);
        Sort();
		c1=Knn(k);
        cout<<"该字符属于"<<c1<<"类"<<" ";
		if(c1==nletter[i].c)
		{
			cout<<"识别正确"<<endl;
		    m++;
		}
		else
		{
			cout<<"识别错误"<<endl;
		    n++;
		}
	}
	cout<<"当K取"<<k<<"时 正确个数："<<m<<" "<<"错误个数："<<n<<" 识别率："<<(float)(m)/N<<endl;
	}
	while(1);
	return 0;
}
