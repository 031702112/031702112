#include"pch.h"
#include <fstream>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
using namespace std;

int m, n, ans[9][9];//m-宫格阶级（3~9的整数);n-待解答盘面数目;ans-存放解的数组
bool solved[10];//标记是否得到解
int B = 0;//第几盘
fstream fr, fw;//定义输入输出对象

/*标记当前格子可填数字*/
void mark_avai(int x, int y, int(*arr)[9], int *q)
{
	int i(0);
	while (i < m + 1)q[i++] = 1;//q数组初始化为1，表示1~m为可填数字
	for (i = 0; i < m; ++i)
	{
		q[arr[x][i]] = 0;//遍历当前格子所在列，并标记q[列的值]=0，表示当前格子无法填该值
		q[arr[i][y]] = 0;//遍历当前格子所在行，并标记q[行的值]=0，表示当前格子无法填该值
	}
}

/*输出函数，方便处理时输出*/
void fileout(int(*arr)[9], int u)
{
	for (int i = 0; i < u; ++i)
	{
		for (int j = 0; j < u; ++j)
			fw << arr[i][j] << " ";//输出一行的值并用空格隔开
		fw << endl;//换行
	}
	fw << endl;//输出完一个盘面的解后换行
}

/*通过递归，求解数独函数*/
void deal(int(*arr)[9], int u, int x, int y)
{
	if (y == u)
	{
		y = 0;
		++x;
	}//如果列号等于阶数则处理下一行
	if (arr[x][y] != 0) //如果当前格子数值不为0
	{
		if (x != u - 1 && y != u - 1) //非最后一个格子
		{
			deal(arr, u, x, y + 1);
			return;
		}//处理完后便退出
		else
		{
			fileout(arr, m);
			return;
		} //是最后一个格子并且值不为0，所以输出并退出函数
	}
	int mark[10]; //存放函数mark_avai中q数组的值
	int record = arr[x][y]; //记录传入数组的值
	mark_avai(x, y, arr, mark); //调用函数，获取当前格子（x，y）可填数字
	for (int k = 1; k <= u; ++k)
	{
		if (mark[k] == 0)continue; //如果当前值k不可填则进行k+1判断
		arr[x][y] = k; //mark[k]=1,说明当前格子（x，y）可以为k
		if (x == u - 1 && y == u - 1) //为最后一个格子
			fileout(arr, m), solved[B] = true;//将解输出到文件
		else deal(arr, u, x, y + 1); //非最后一个格子则继续处理下一个格子
		if (solved[B])return; //如果获得解则退出函数
	}
	arr[x][y] = record;//还原传入数组的值
}
int main(int argc,char *argv[])
{
	//m = atoi(argv[2]); 
	//n = atoi(argv[4]); 
	int i, j, k;
	fr.open("E:\\input.txt", ios::in); //读入输入文件
	fw.open("output.txt", ios::out); //打印输出文件
	if (!fr)
	{
		printf("The input file is empty!");
		exit(0);
	}//如果输入文件为空则退出
	for (i = 0; i < n; ++i) //i为第几盘-1
	{
		for (j = 0; j < m; ++j)
			for (k = 0; k < m; ++k)
			{
				fr >> ans[j][k];//读入输入文件数据
			}
		B = i;
		solved[B] = false; //初始化solve数组为false
		deal(ans, m, 0, 0); //调用求解函数
	}
	printf("结果已写入输出文件\n");
	return 0;
}