#include <iostream>
#include <Windows.h>
#include <string>
#include <stack>
using namespace std;
stack<char>opt;//操作符栈
stack<double>val;//操作数栈

enum class State//状态码
{
	Numb_IN,//数字内
	Numb_OUT,//数字外
};

int level(char theOpt)//为每一个操作符返回一个数，数越大优先级越高
{
	char operators[10] = "+-*/()=";//操作符
	for (int i = 0; i < 7; i++)
		if (theOpt == operators[i])
			return i;
	return -1;//如果不是上述操作符就返回-1
}

bool in_set(char theChar)//判断输入的操作符是否合法
{
	char operators[10] = "+-*/()=";//操作符
	for (int i = 0; i < 7; i++)
		if (theChar == operators[i])
			return true;
	return false;
}

bool del_space(string& theString)//用于去除空格并检查是否有非法字符
{
	string res;
	if (theString.length() == 0)
	{
		return false;
	}
	for (unsigned int i = 0; i < theString.length(); i++)
	{
		if (in_set(theString[i]) || isdigit(theString[i]))
			res += theString[i];
		else if (theString[i] == ' ');
		else
		{
			cout << "\a表达式含有错误字符！" << endl;
			return false;
		}
	}
	theString = res;
	return true;
}

string to_string(int theInt)//把数字转换成字符串
{
	if (theInt == 0)
		return string("0");
	bool neg = false;
	if (theInt < 0)
	{
		neg = true;
		theInt = -theInt;
	}
	string res;
	while (theInt != 0)
	{
		char c = (theInt % 10) + '0';
		res = c + res;
		theInt /= 10;
	}
	if (neg)
		res = '-' + res;
	return res;
}

/* 将中缀表达式转换成后缀表达式 */
bool change(string& from, string& to)
{
	int theInt = 0;//暂存数字
	State state = State::Numb_OUT;//初始状态：在数字外
	char c;
	if(from[from.length() - 1] != '=')
	{
		cout << "\a等号位置有误或遗漏等号，请注意，本程序不支持方程求解！" << endl;
		return false;
	}
	for (unsigned int i = 0; i < from.length(); i++)
	{
		c = from[i];
		if (isdigit(c))
		{
			theInt *= 10;
			theInt += c - '0';
			state = State::Numb_IN;
		}
		else
		{
			if (state == State::Numb_IN)//刚刚处理了数字
			{
				to += std::to_string(theInt) + ' ';
				theInt = 0;
			}
			if (c == '=')
			{
				if(i != from.length() - 1){
					cout << "\a等于号语法有误，本程序不支持方程求解！" << endl;
					return false;
				}
				break;
			}
			else if (c == '(')
				opt.push(c);
			else if (c == ')')
			{
				while (!opt.empty() && opt.top() != '(')
				{
					to += opt.top();
					to += ' ';
					opt.pop();
				}
				if(opt.empty())
				{
					cout << "\a括号匹配有误！" << endl;
					return false;
				}
				else
					opt.pop();
			}
			else
			{
				while (true)
				{
					if (opt.empty() || opt.top() == '(')
						opt.push(c);
					else if (level(c) > level(opt.top()))
						opt.push(c);
					else
					{
						to += opt.top();
						to += ' ';
						opt.pop();
						continue;
					}
					break;
				}
			}
			state = State::Numb_OUT;//在数字外
		}
	}
	while (!opt.empty())
	{
		if(opt.top() == '(')
		{
			cout << "\a括号匹配有误！" << endl;
			return false;
		}
		to += opt.top();
		to += ' ';
		opt.pop();
	}
	return true;
}

/* 计算后缀表达式 */
bool compute(string& theExp)
{
	int theInt = 0;
	State state = State::Numb_OUT;
	char c;
	for (unsigned int i = 0; i < theExp.length(); i++)
	{
		c = theExp[i];
		if (isdigit(c))
		{
			theInt *= 10;
			theInt += c - '0';
			state = State::Numb_IN;//保存状态
		}
		else
		{
			if (state == State::Numb_IN)//刚刚处理了数字
			{
				val.push(theInt);
				theInt = 0;
			}
			double x, y;
			if (c != ' ')
			{
				if(val.empty())
				{
					cout << "\a操作数存在语法错误！" << endl;
					return false;
				}
				x = val.top();
				val.pop();
				if(val.empty())
				{
					cout << "\a操作数存在语法错误！" << endl;
					return false;
				}
				y = val.top();
				val.pop();
				switch (c)
				{
				case '+':
					val.push(x + y);
					break;
				case '-':
					val.push(y - x);
					break;
				case '*':
					val.push(x * y);
					break;
				case '/':
					val.push(y / x);
					break;
				default:
					cout << "\a发生了未指定的错误！" << endl;
				}
			}
			state = State::Numb_OUT;
		}
	}
	if(val.size() != 1)
	{
		cout << "\a缺少操作符！" << endl;
		return false;
	}
	return true;
}

/* 主函数 */
int main()
{
	system("chcp 936&title 算术表达式运算&color e&cls");
	if (MessageBox(NULL, TEXT("程序说明：\n请保证所有的操作数均为自然数，且不要出现(-x)的形式。\n若输出为小数，本程序按照四舍五入规则最多保留小数点后四位。\n表达式必须为英文字符，并以等号结尾，按下回车键执行计算。"), TEXT("算术表达式运算"), MB_OKCANCEL | MB_ICONWARNING | MB_TOPMOST) == 2)
		return 1;
	while (true)
	{
		cin.clear();
		cin.sync();
		cin.sync();
		while (!opt.empty())//初始化两个栈
			opt.pop();
		while (!val.empty())
			val.pop();
		string init_exp;//输入算术表达式
		cout << "请输入算术表达式：";
		getline(cin, init_exp);
		if (!del_space(init_exp))//去除空格并检查是否有非法字符
		{
			cout << endl;
			continue;
		}
		string deal_exp;
		deal_exp.clear();
		if (!change(init_exp, deal_exp))//转换为后缀表达式
		{
			cout << endl;
			continue;
		}
		if (!compute(deal_exp))//计算后缀表达式
		{
			cout << endl;
			continue;
		}
		double stdans = val.top();
		cout << "经计算，该表达式的运算结果为：" << stdans << "。" << endl;
		if (MessageBox(NULL, TEXT("继续运算吗？"), TEXT("算术表达式运算"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST) == 6)
			cout << endl;
		else
			break;
	}
	MessageBox(NULL, TEXT("欢迎再次使用，请点击“确定”退出本程序。"), TEXT("算术表达式运算"), MB_OK | MB_TOPMOST);
	system("cls");
	return 0;
}