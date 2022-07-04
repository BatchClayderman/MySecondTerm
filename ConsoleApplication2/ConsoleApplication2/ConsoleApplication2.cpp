#include <stdio.h>
#include <stdlib.h>
#include <time.h>//时间库，用于判断运行速度

int main(void)
{
	system("chcp 936&title C语言用蒙托卡罗方法求pi&color e&cls");//设置标题，调整字体颜色
	time_t start_time, end_time;//声明计时变量
	double elapsed_time;
	double x, y, pi;//声明双精度变量
	long total = 0;
	printf("初始化完成，按下任意键，开始奔跑。\n");
	system("pause>nul&cls");
	srand((unsigned)time(0));//初始化时间种子
	time(&start_time);//开始计时
	for (int i = 0; i < 1e8; i++)//for循环
	{
		x = rand() / (double)(RAND_MAX);
		y = rand() / (double)(RAND_MAX);
		if (x * x + y * y < 1)
			total++;
	}
	pi = 4.0 * total / 1e8;
	time(&end_time);//计时结束
	elapsed_time = difftime(end_time, start_time);//计算运行耗时
	printf("count=%d\t\ttotal=100000000\t\tpi=%f\t\ttime=%f\n\n\n", total, pi, elapsed_time);
	printf("运行完成，返回信息如上，请按任意键退出本程序。\n");
	system("pause>nul&cls");
	return 0;
}