#include"stdio.h"
#include"stdlib.h"
#include<iostream>
using namespace std;

#define N 11
#define k 3

typedef struct {
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float l;
	float m;
	float p;
}Point;

Point point[N] = {
		{ 723.55 ,10050.21,663.03 ,4697.23 ,5556.32 ,500.67 ,1233.88 ,7507.09 ,1.88 ,287.95 ,1.50 },
        { 586.57 ,8003.61 ,509.50 ,3349.63 ,4506.58 ,713.73 ,1006.41 ,5302.84 ,1.81 ,284.68 ,0.88 },
        { 349.48 ,3517.81 ,328.91 ,1494.57 ,2513.82 ,229.27 ,350.35  ,2949.24 ,1.70 ,139.09 ,0.83 },
        { 263.71 ,2084.26 ,184.48 ,963.92  ,1402.64 ,88.55  ,191.31  ,1548.15 ,1.73 ,122.60 ,0.92 },
        { 443.11 ,4465.97 ,346.80 ,1621.06 ,2582.84 ,271.42 ,362.89  ,3113.03 ,1.82 ,198.94 ,0.89 },
		{ 97.36  ,1092.85 ,74.50  ,415.52  ,1134.76 ,61.85  ,112.72  ,661.61  ,1.73 ,111.01 ,1.18 },
        { 811.21 ,4618.08 ,573.98 ,2674.38 ,3456.39 ,171.15 ,403.07  ,4487.04 ,2.07 ,129.57 ,1.22 },
        { 478.09 ,3402.34 ,346.01 ,1783.10 ,1836.16 ,476.73 ,309.69  ,3509.21 ,2.13 ,141.03 ,1.11 },
        { 256.38 ,1146.13 ,130.58 ,550.98  ,882.04  ,32.92  ,94.02   ,893.16  ,1.97 ,84.46  ,0.99 },
        { 597.49 ,3553.85 ,407.32 ,1826.68 ,1996.03 ,188.29 ,298.02  ,3145.48 ,2.04 ,229.75 ,1.12 },
        { 266.38 ,1103.29 ,141.15 ,519.28  ,751.52  ,31.44  ,94.51   ,1028.39 ,2.19 ,91.36  ,1.01 }
};

int center[N];//聚类中心
Point mean[k];//均值

float getdistance(Point point1, Point point2);//计算两点的11维欧式距离
void cluster();
float gete();
void getmean(int center[N]);

int main()
{
	//初始化k个中心点,这里选择给定中心点，而不是随机生成，需要更多的先验知识
	//若没有相关先验知识，可选择随机生成初始中心点
	mean[0].a = point[0].a;
	mean[0].b = point[0].b;
	mean[0].c = point[0].c;
	mean[0].d = point[0].d;
	mean[0].e = point[0].e;
	mean[0].f = point[0].f;
	mean[0].g = point[0].g;
	mean[0].h = point[0].h;
	mean[0].l = point[0].l;
	mean[0].m = point[0].m;
	mean[0].p = point[0].p;

	mean[1].a = point[3].a;
	mean[1].b = point[3].b;
	mean[1].c = point[3].c;
	mean[1].d = point[3].d;
	mean[1].e = point[3].e;
	mean[1].f = point[3].f;
	mean[1].g = point[3].g;
	mean[1].h = point[3].h;
	mean[1].l = point[3].l;
	mean[1].m = point[3].m;
	mean[1].p = point[3].p;

	mean[2].a = point[6].a;
	mean[2].b = point[6].b;
	mean[2].c = point[6].c;
	mean[2].d = point[6].d;
	mean[2].e = point[6].e;
	mean[2].f = point[6].f;
	mean[2].g = point[6].g;
	mean[2].h = point[6].h;
	mean[2].l = point[6].l;
	mean[2].m = point[6].m;
	mean[2].p = point[6].p;

	float temp1, temp2;

	//第一次聚类
	cluster();
	int number=1;//number统计进行了几次聚类

	//对第一次聚类的结果进行误差平方和的计算   
	temp1 = gete();
	printf("the error1 is:%f\n", temp1);

	//针对第一次聚类的结果，重新计算聚类中心
	getmean(center);

	//第二次聚类
	cluster();
	number++;
	temp2 = gete();
	printf("the error2 is:%f\n", temp2);

	//迭代循环，直到两次迭代误差的差值在一定阈值范围内，则迭代停止
	while (fabs(temp1 - temp2) > 0.005)
	{
		temp1 = temp2;
		getmean(center);
		cluster();
		temp2 = gete();
		number++;
		printf("the error%d is:%f\n", number, temp2);
	}
	printf("The total clustering time is:%d\n", number);

	system("pause");
	return 0;

}

//计算距离函数，欧式距离
float getdistance(Point point1, Point point2)
{
	float d;
	d = sqrt((point1.a - point2.a)*(point1.a - point2.a) + (point1.b - point2.b)*(point1.b - point2.b) 
		+ (point1.c - point2.c)*(point1.c - point2.c) + (point1.d - point2.d)*(point1.d - point2.d) 
		+ (point1.e - point2.e)*(point1.e - point2.e) + (point1.f - point2.f)*(point1.f - point2.f)
		+ (point1.g - point2.g)*(point1.g - point2.g) + (point1.h - point2.h)*(point1.h - point2.h)
		+ (point1.l - point2.l)*(point1.l - point2.l) + (point1.m - point2.m)*(point1.m - point2.m)
		+ (point1.p - point2.p)*(point1.p - point2.p));
	return d;
}
//聚类函数
void cluster()
{
	float distance[N][k];//计算点与聚类中心点之间的距离
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < k; j++)
		{
			distance[i][j] = getdistance(point[i], mean[j]);
		}
		float min = 9999.0;
		for (int j = 0; j < k; j++)
		{
			if (distance[i][j] < min)
			{
				min = distance[i][j];
				center[i] = j;
			}
		}
		printf("No.(%d)\t in cluster-%d\n", 
			i+1, center[i] + 1);
	}
}
//聚类后误差计算函数
float gete()
{
	float cnt = 0, sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (center[i] == j)
			{
				cnt = getdistance(point[i], mean[j]);
			}
		}
		sum += cnt;
	}
	return sum;
}

//重新计算聚类中心
void getmean(int center[N])
{
	Point sum;
	int count;
	for (int i = 0; i < k; i++)
	{
		sum.a = 0.0;
		sum.b = 0.0;
		sum.c = 0.0;
		sum.d = 0.0;
		sum.e = 0.0;
		sum.f = 0.0;
		sum.g = 0.0;
		sum.h = 0.0;
		sum.l = 0.0;
		sum.m = 0.0;
		sum.p = 0.0;

		count = 0;
		for (int j = 0; j < N; j++)
		{
			if (center[j] == i)
			{
				sum.a += point[j].a;
				sum.b += point[j].b;
				sum.c += point[j].c;
				sum.d += point[j].d;
				sum.e += point[j].e;
				sum.f += point[j].f;
				sum.g += point[j].g;
				sum.h += point[j].h;
				sum.l += point[j].l;
				sum.m += point[j].m;
				sum.p += point[j].p;
				
				count++;
			}
		}
		mean[i].a = sum.a / count;
		mean[i].b = sum.b / count;
		mean[i].c = sum.c / count;
		mean[i].d = sum.d / count;
		mean[i].e = sum.e / count;
		mean[i].f = sum.f / count; 
		mean[i].g = sum.g / count;
		mean[i].h = sum.h / count; 
		mean[i].l = sum.l / count;
		mean[i].m = sum.m / count;
		mean[i].p = sum.p / count;
	}
	for (int i = 0; i < k; i++)
	{
		printf("The New Center of cluster%d is:\n(%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f)\n", i + 1, 
			mean[i].a, mean[i].b, mean[i].c, mean[i].d, mean[i].e, mean[i].f, 
			mean[i].g, mean[i].h, mean[i].l, mean[i].m, mean[i].p );
	}
}