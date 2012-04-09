#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M 4000
#define N 100

//定义一个字符的结构体
struct letter
{
    char c;
    int array[16];
    float distance;
};


//定义训练字符结构体数组,共有M个训练样本
letter letters[M];
//识别字符类数组，共有N个对比样本
letter nletters[N];
float t;


//定义读取训练文件函数，将训练样本从磁盘文件letter.txt读入letters[M]数组中
void Get_from_letters()
{
    FILE  *fp;
    int i,j;
    fp=fopen("letter.txt","r");
    for(i=0; i<M; i++)
    {
        fscanf(fp,"%c ",&letters[i].c);
        for(j=0; j<16; j++)
            fscanf(fp,"%d ",&letters[i].array[j]);
    }
    fclose(fp);
}


//定义读取测试文件，将测试样本从磁盘文件素描sum1.txt读入到nletters中
void Get_from_nletters()
{
    int i,j;
    FILE *fp;
    fp=fopen("sum.txt","r");
    for(i=0; i<N; i++)
    {
        fscanf(fp,"%c ",&nletters[i].c);
        for(j=0; j<16; j++)
            fscanf(fp,"%d ",&nletters[i].array[j]);
    }
    fclose(fp);
}

//定义欧式距离函数，计算一个测试样本与各个训练样本之间的距离
void Distance(letter *p)
{
    int i,j;
    float s=0.0;
    for(i=0; i<M; i++)
    {
        for(j=0; j<16; j++)
        {
            s+=((letters[i].array[j]-(*p).array[j])*(letters[i].array[j]-(*p).array[j]));
        }
        letters[i].distance=sqrt(s);
        //恢复到原始值
        s=0.0;
    }


}


//排序函数将letters距离按由小到大排列
void Sort()
{
    int i,j;
    letter t;
    for(i=0; i<M-1; i++)
    {
        for(j=i+1; j<M; j++)
        {
            if(letters[i].distance>letters[j].distance)
            {
                t=letters[i];
                letters[i]=letters[j];
                letters[j]=t;

            }
        }
    }

}



//根据用户输入的k值，确定分类
char Knn(int q)
{
    int i,j,max;
    int array[26];
    for(i=0; i<26; i++)
    {
        array[i]=0;
    }

    for(i=0; i<q; i++)
    {
        switch(letters[i].c)
        {
        case'A':
            array[0]++;
            break;
        case'B':
            array[1]++;
            break;
        case'C':
            array[2]++;
            break;
        case'D':
            array[3]++;
            break;
        case'E':
            array[4]++;
            break;
        case'F':
            array[5]++;
            break;
        case'G':
            array[6]++;
            break;
        case'H':
            array[7]++;
            break;
        case'I':
            array[8]++;
            break;
        case'J':
            array[9]++;
            break;
        case'K':
            array[10]++;
            break;
        case'L':
            array[11]++;
            break;
        case'M':
            array[12]++;
            break;
        case'N':
            array[13]++;
            break;
        case'O':
            array[14]++;
            break;
        case'P':
            array[15]++;
            break;
        case'Q':
            array[16]++;
            break;
        case'R':
            array[17]++;
            break;
        case'S':
            array[18]++;
            break;
        case'T':
            array[19]++;
            break;
        case'U':
            array[20]++;
            break;
        case'V':
            array[21]++;
            break;
        case'W':
            array[22]++;
            break;
        case'X':
            array[23]++;
            break;
        case'Y':
            array[24]++;
            break;
        case'Z':
            array[25]++;
            break;
        }
    }

    max=array[0];
    j=0;
    for(i=0; i<26; i++)
    {
        if(array[i]>max)
        {
            max=array[i];
            j=i;
        }
    }
    return (char)(j+65);
}


//主函数
int main()
{
    int i,j,k=0;
    int m=0,n=0;
    letter * p;
    char c;
    printf("训练样本为%d\n",M);
    Get_from_letters();
    printf("测试样本为%d\n",N);
    Get_from_nletters();
    printf("请输入K值：\n");
    scanf("%d",&k);
    for(i=0; i<N; i++)
    {
        p=&nletters[i];
        Distance(p);
        Sort();
        c=Knn(k);
        if(nletters[i].c==c)
        {
            printf("该字符属于%c类,识别正确\n",nletters[i].c);
            m++;
        }
        else
        {
            printf("该字符属于%c类，识别错误\n",nletters[i].c);
            n++;
        }
        printf("%f",letters[0].distance);
    }
    printf("正确个数为%d",m);
    printf("错误个数为%d",n);
    printf("正确率为%f",(float)(m)/N);
    scanf("%d",&i);
    return 0;
}
