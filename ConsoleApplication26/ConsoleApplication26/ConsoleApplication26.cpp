#include <iostream>
#include <Windows.h>
#include <string.h>
using namespace std;
#define maxStack 2//最多元素个数
#define MAXSIZE 500//最长路径
#define money 0.1//每分钟单价
#define CarLen 20//车牌的最大长度
char strings[4][CarLen] = { 0 };

enum class Error_code//栈错误代码
{
	success,
	underflow,
	overflow,
};

template <class Stack_entry>
class Stack//栈
{
private:
	unsigned int count;//记录栈内元素个数
	Stack_entry entry[maxStack];//数组实现
public:
	Stack()
	{
		count = 0;
	}
	bool empty() const
	{
		if (count == 0)
			return true;
		else
			return false;
	}
	bool full() const
	{
		if (count == maxStack)
			return true;
		else
			return false;
	}
	int CarNumb()
	{
		return count;
	}
	Error_code pop()
	{
		if (count == 0)
			return Error_code::underflow;
		else
		{
			count--;
			return Error_code::success;
		}
	}
	Error_code top(Stack_entry& item) const//取栈顶元素
	{
		if (count == 0)
			return Error_code::underflow;
		else
		{
			item = entry[count - 1];
			return Error_code::success;
		}
	}
	Error_code push(Stack_entry& item)
	{
		if (count >= maxStack)
			return Error_code::overflow;
		else
		{
			entry[count++] = item;
			item.position = count;//返回停车位置，从1开始记
			return Error_code::success;
		}
	}
};

/*以上是栈的部分，以下是链队列部分*/

template<class Node_entry>//链队列结点定义（单链表）
struct Node
{
	//数据成员
	Node_entry entry;
	Node<Node_entry>* next;
	//构造函数
	Node() {}
	Node(Node_entry new_entry, Node<Node_entry>* new_next = NULL) :entry(new_entry), next(new_next) {}
};

template<class Queue_entry>
class Queue
{
public:
	unsigned int count;//结点个数
	Node<Queue_entry>* front, * rear;//队列头、尾结点
	Queue()//构造函数
	{
		count = 0;
		front = rear = NULL;
	}
	bool empty() const
	{
		if (count == 0)
			return true;
		else
			return false;
	}
	Error_code serve()
	{
		if (count == 0)
			return Error_code::underflow;
		else
		{
			Node<Queue_entry>* out = front;
			front = front->next;
			if (front == NULL) rear = NULL;
			delete out;
			count--;
			return Error_code::success;
		}
	}
	Error_code retrieve(Queue_entry& item) const//取队列头元素
	{
		if (count == 0)
			return Error_code::underflow;
		else
		{
			item = front->entry;//解引用
			return Error_code::success;
		}
	}
	Error_code append(const Queue_entry& item)//添加车辆
	{
		Node<Queue_entry>* in = new Node<Queue_entry>(item);
		if (in == NULL)
			return Error_code::overflow;
		if (count == 0)
			front = rear = in;
		else
		{
			rear->next = in;
			rear = in;;
		}
		count++;
		return Error_code::success;
	}
};

/*以上是链队列部分，以下是时间类部分*/

class Time//时间类
{
private:
	unsigned short hour;
	unsigned short minute;
public:
	Time() { hour = 0; minute = 0; }//默认构造函数
	Time(unsigned short h, unsigned short m) :hour(h), minute(m){}//构造函数
	int HowManyMinutes(const Time& time)//计算时间间隔
	{
		return time - *this;
	}
	Time& operator=(const Time& t)
	{
		hour = t.hour;
		minute = t.minute;
		return *this;
	}
	friend int operator-(const Time& t1, const Time& t2);//重载相减运算符
	friend istream& operator>>(istream& is, Time& t);
	friend ostream& operator<<(ostream& os, Time& t);
};

int operator-(const Time& t1, const Time& t2)//重载相减运算符
{
	int dur = 0;
	if (t1.minute < t2.minute)
	{
		dur = t1.minute + 60 - t2.minute;
		dur += 60 * (t1.hour - 1 - t2.hour);
	}
	else
	{
		dur = t1.minute - t2.minute;
		dur += 60 * (t1.hour - t2.hour);
	}
	return dur < 0 ? dur + 1440 : dur;
}

istream& operator>>(istream& is, Time& t)
{
	char sem;
	is >> t.hour >> sem >> t.minute;
	return is;
}

ostream& operator<<(ostream& os, Time& t)
{
	t.minute >= 10 ? os << t.hour << ':' << t.minute : os << t.hour << ":0" << t.minute;
	return os;
}

short int ctoh(char* _time)
{
	unsigned int i;
	short int h = 0;
	char time[3] = { 0 };
	for (i = 0; i < strlen(_time); i++)
		if (_time[i] == ':')
		{
			if (i == 1)
				h = short int(_time[0] - '0');
			else if (i == 2)
				h = short int(_time[1] - '0') + 10 * short int(_time[0] - '0');
			else
				return h;
			if (h < 0 || h > 23)
				return 0;
			else
				return h;
		}
	return h;
}

short int ctom(char* _time)
{
	unsigned int i;
	short int m = 0;
	char time[3] = { 0 };
	for (i = 0; i < strlen(_time); i++)
		if (_time[i] == ':')
		{
			if (strlen(_time) - i == 2)
				m = short int(_time[i + 1] - '0');
			else if (strlen(_time) - i == 3)
				m = short int(_time[i + 2] - '0') + 10 * short int(_time[i + 1] - '0');
			else
				return m;
			if (m < 0 || m > 59)
				return 0;
			else
				return m;
		}
	if (strlen(_time) == 2)
		m = short int(_time[1] - '0') + 10 * short int(_time[0] - '0');
	else if (strlen(_time) == 1)
		m = short int(_time[0] - '0');
	else
		return m;
	return m;
}

/*以上是时间类部分，以下是停车场部分*/

struct Car//车辆信息
{
	string num;//车牌号
	Time arrTime;//到达时间（未必立即停入车位）
	Time inTime;//停入车位的时间
	short int position = -1;//停入的车位，-1为初始化值，0为便道，栈底为1
	Time depTime;//离开时间
	//构造函数
	Car() {};
	Car(string n, Time a) :num(n), arrTime(a) {}
	void CheckOut()//离开时结算
	{
		cout << "车牌号：" << num << endl;
		cout << "到达时间：" << arrTime << endl;
		cout << "停入时间：" << inTime << endl;
		cout << "离开时间：" << depTime << endl;
		cout << "有效停留时间：" << depTime - inTime << " 分钟" << endl;//停留时间
		cout << "应交纳停车费：" << int((depTime - inTime) * money) << " 元" << endl;
	}
	void CheckIn()//进入停车场信息
	{
		cout << "车牌号：" << num << endl;
		cout << "到达时间：" << arrTime << endl;
		cout << "进入停车场时间：" << inTime << endl;
		cout << "停入的位置：#" << position << endl;
	}
};

enum class Status//停车场错误代码
{
	success,
	fail,
};

class Parking//停车场
{
private:
	Stack<Car> parkStack;//停车栈
	Stack<Car> tempStack;//临时栈
	Queue<Car> waitingQueue;//便道
public:
	Status park(string num, Time arr)
	{
		if (!waitingQueue.empty())//遍历队列以确认是否有重复的车
		{
			Node<Car>* q = waitingQueue.front;
			while (q != NULL)
			{
				if (q->entry.num == num)
				{
					cout << "车牌号为 " << num << " 的车已在便道中排队，请勿重复进入。" << endl;
					return Status::fail;
				}
				q = q->next;
			}
		}
		Car* currentCar = new Car();
		parkStack.top(*currentCar);
		Status second = Status::success;
		int posi = parkStack.CarNumb() + 1;
		while (!parkStack.empty())//遍历栈以确认是否有重复的车
		{
			posi--;
			if (currentCar->num == num)//找到了
			{
				second = Status::fail;
				cout << "车牌号为 " << num << " 的车已在停车场中，位于 #" << posi << "，请勿重复进入。" << endl;
				break;
			}
			tempStack.push(*currentCar);//假装让前面的车退出到临时栈
			parkStack.pop();
			parkStack.top(*currentCar);
		}//没找到
		while (!tempStack.empty())//假装让车移回去
		{
			tempStack.top(*currentCar);
			parkStack.push(*currentCar);
			tempStack.pop();
		}
		if (second == Status::fail)
			return Status::fail;
		Car* new_car = new Car(num, arr);
		if (parkStack.full())//栈满，入便道
		{
			waitingQueue.append(*new_car);
			new_car->position = 0;
			cout << "停车场已满，将车牌号为 " << num << " 的车放入便道。" << endl;
		}
		else//栈未满，入栈
		{
			new_car->inTime = arr;//到达即入栈
			parkStack.push(*new_car);
			new_car->CheckIn();
		}
		return Status::success;
	}
	Status leave(string num, Time dep)
	{
		Status out = Status::success;
		Car* currentCar = new Car();
		parkStack.top(*currentCar);
		while (currentCar->num != num)//遍历栈以找到要离开的车
		{
			tempStack.push(*currentCar);//前面的车退出到临时栈
			parkStack.pop();
			parkStack.top(*currentCar);
			if (parkStack.empty())//没找到
			{
				out = Status::fail;
				break;
			}
		}//找到了要离开的那辆车
		if (!parkStack.empty())
		{
			currentCar->depTime = dep;//登记离开时间
			currentCar->CheckOut();//结账，打印账单
			parkStack.pop();//该车出栈
		}
		while (!tempStack.empty())//临时栈中的车依次放回停车栈
		{
			tempStack.top(*currentCar);
			parkStack.push(*currentCar);
			tempStack.pop();
		}
		if (out == Status::fail)
			return Status::fail;
		if (!waitingQueue.empty())//便道不空，队头入栈
		{
			waitingQueue.retrieve(*currentCar);
			waitingQueue.serve();
			parkStack.push(*currentCar);
			currentCar->inTime = dep;//上一辆车离开的时间就是这一辆的入栈时间
			cout << endl << "车牌号为 " << currentCar->num << " 的车已从便道驶入停车场。" << endl;
			currentCar->CheckIn();
		}
		return Status::success;
	}
};

/*以上是停车场部分，以下是停车场控制台部分*/

void InputBox(char* _0)//文本输入框
{
	if (strings == NULL)
	{
		MessageBox(NULL, TEXT("内存空间不足，程序意外中止。"), TEXT("停车场控制台"), MB_OK | MB_ICONERROR | MB_TOPMOST);
		exit(9009);
	}
	int i, j;
	char cmd[MAXSIZE] = { 0 }, runvbs[2 * MAXSIZE] = "(if exist \"";
	for (i = strlen(_0) - 1; i >= 0; i--)
		if (_0[i] == '\\')
			break;
	for (j = 0; j <= i; j++)
		cmd[j] = _0[j];
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "InputBox.txt\" (del /a /f /q \\\\?\\\"");
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "InputBox.txt\"))&start /realtime /wait \"\" \"");
	strcat_s(cmd, "InputBox.vbs");
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "\"");
	FILE* fp;
	fopen_s(&fp, cmd, "r");
	if (!fp)
	{
		fopen_s(&fp, cmd, "w+");
		if (fp)
		{
			fwrite("strings = inputbox(\"输入示例：\"&vbCrLf&\">> 到达：（A 粤RG9957 11:40）或（A 1 5）\"&vbCrLf&\">> 离开：（粤RYH068 17:35）或（D 1 15）\"&vbCrLf&\">> 结束：E 0 0（或点击“取消”）\"&vbCrLf&\"\"&vbCrLf&\"请输入事件：\",\"停车场控制台\",\"A 粤RG9957 11:40\")\nif (not strings<>false) Then\nstrings = \"E 0 0\"\nEnd if\nSet fso = CreateObject(\"Scripting.FileSystemObject\")\nSet f = fso.CreateTextFile(\"", 375, 1, fp);
			fwrite(cmd, strlen(cmd) - 3, 1, fp);
			fwrite("txt\",True)\nf.write strings\nf.close", 34, 1, fp);
			fclose(fp);
		}
		else
		{
			MessageBox(NULL, TEXT("生成脚本文件失败，请确保程序所在目录可写。"), TEXT("停车场控制台"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			return;
		}
	}
	system(runvbs);
	cmd[strlen(cmd) - 3] = 't';
	cmd[strlen(cmd) - 2] = 'x';
	cmd[strlen(cmd) - 1] = 't';
	fopen_s(&fp, cmd, "r");
	if (fp)
	{
		char str[MAXSIZE] = { 0 };
		fgets(str, MAXSIZE, fp);
		fclose(fp);
		unsigned int i, j = 0, k = 1, count = 0;
		for (i = 0; i < strlen(str); i++)
			if (str[i] == ' ')
				count++;
		if (count == 2)
		{
			i = 0;
			k = 0;
			while (str[i] != ' ')
			{
				i++;
				j++;
			}
			i++;
			j++;
			k += j;
			while (str[i] != ' ')
			{
				i++;
				k++;
			}
			char tmp1[2] = { 0 }, tmp2[CarLen] = { 0 }, tmp3[6] = { 0 };
			for (i = 0; i < j - 1 && i < 2; i++)
				strings[0][i] = str[i];
			for (i = j; i < k && i - j < CarLen; i++)
				strings[1][i - j] = str[i];
			k += 1;
			for (i = k; i < strlen(str) && i - k < 6; i++)
				strings[2][i - k] = str[i];
			strings[2][strlen(str)] = '\0';
		}
		else
			return InputBox(_0);//如果输入有误，递归
	}
	else
	{
		MessageBox(NULL, TEXT("从脚本读取数据失败，请确保程序所在目录可读。"), TEXT("InputBox"), MB_OK | MB_ICONERROR | MB_TOPMOST);
		strings[0][0] = 'E';
	}
	return;
}

int main(int argc, char* argv[])
{
	system("chcp 936&title 停车场状态输出&color e&cls");
	Parking parking;
	cout << "初始化栈式停车场成功，停车场的容量为 " << maxStack << "。" << endl << endl << endl;
	while (true)
	{
		string num;
		Time timing;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < CarLen; j++)
				strings[i][j] = '\0';
		InputBox(argv[0]);
		num = string(strings[1]);
		timing = Time(ctoh(strings[2]), ctom(strings[2]));
		if (strcmp(strings[0], "A") == 0 || strcmp(strings[0], "a") == 0)
			parking.park(num, timing);
		else if (strcmp(strings[0], "D") == 0 || strcmp(strings[0], "d") == 0)
		{
			if (parking.leave(num, timing) == Status::fail)
				cout << "车牌号为 " << num << " 的车不在停车场中，无需离场。" << endl;
		}
		else if (strcmp(strings[0], "E") == 0 || strcmp(strings[0], "e") == 0)
			break;
		else
			continue;
		cout << endl;
	}
	printf("\n\n欢迎再次使用，请点击“确定”退出本程序，期待您的再次使用。\n");
	MessageBox(NULL, TEXT("欢迎再次使用，请点击“确定”退出本程序，期待您的再次使用。"), TEXT("停车场控制台"), MB_OK | MB_TOPMOST);
	system("cls");
	return 0;
}