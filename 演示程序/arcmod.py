#coding=gbk
import platform
from sys import exit#防止打包 exe 时出错
EXIT_SUCCESS = 0#操作成功结束
EOF = (-1)#命令行参数不正确

# 定义相关函数
def get_gcd(a, b):
	k = a // b
	remainder = a % b
	while remainder != 0:
		a = b
		b = remainder
		k = a // b
		remainder = a % b
	return b
def get_(a, b):
	if b == 0:
		return 1, 0
	else:
		k = a // b
		remainder = a % b
		x1, y1 = get_(b, remainder)
		x, y = y1, x1 - k * y1
		return x, y

# 定义帮助函数
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a错误：无效的命令行参数—“"+str(option)+"”。")
	print("描述：求模逆元。\n\n参数列表：\n\t/a\t\t设置系数的值\n\t/m\t\t设置模数的值\n\t[a]\t\t系数值\n\t[m]\t\t模数值\n")
	print("命令行格式：\n\tarcmod.py /a [a] /m [m]\n")
	print("示例：\n\tarcmod.py /a 5 /m 203344\n\tarcmod.py /a 5 /m 20\n")
	if option == "/?" or option == "-?":
		return EXIT_SUCCESS
	else:
		return EOF

def dealArgv():# 处理命令行参数
	from sys import argv
	if "/?" in argv or "-?" in argv:
		exit(help("/?"))
	if len(argv) == 5:
		if argv[1].lower() == "/a" or argv[1].lower() == "-a":
			try:
				a = int(argv[2])
				if a <= 0:
					assert ""
			except:
				print("\a错误：提供的系数非法。\n")
				exit(EOF)
		elif argv[1].lower() == "/m" or argv[1].lower() == "-m":
			try:
				m = int(argv[2])
				if m <= 1:
					assert ""
			except:
				print("\a错误：提供的模数非法。\n")
				exit(EOF)
		if argv[3].lower() == "/a" or argv[3].lower() == "-a":
			try:
				a = int(argv[4])
				if a < 4:
					assert ""
			except:
				print("\a错误：提供的系数不合理。\n")
				exit(EOF)
		elif argv[3].lower() == "/m" or argv[3].lower() == "-m":
			try:
				m = int(argv[4])
				if m < 1:
					assert ""
			except:
				print("\a错误：提供的模数不合理。\n")
				exit(EOF)
		try:
			print("a =", a)
		except:
			print("\a错误：未定义系数。")
			exit(EOF)
		try:
			print("m =", m)
		except:
			print("\a错误：未定义模数。")
			exit(EOF)
		flag = get_gcd(a, m)
		if flag==1:
			x, y = get_(a, m)
			x0 = x % m
			print("x =", x0)
			exit(EXIT_SUCCESS)
		else:
			print("（a，m）=", flag)
			exit(EXIT_SUCCESS)
	elif len(argv) != 1:
		exit(help(argv[1:]))
	del argv

# 主程序
if __name__ == "__main__":
	dealArgv()
	from os import system
	system("title 求模逆元&color e&cls")
	while True:
		system("cls")
		try:
			a = int(input("请输入系数（正整数）："))
			if a <= 0:
				assert ""
			m = int(input("请输入模数（大于 1 的正整数）："))
			if m <= 1:
				assert ""
		except:
			print("\a输入不合法，请按任意键重新输入。")
			system("pause>nul&cls")
			continue
		flag = get_gcd(a, m)
		if flag == 1:
			x, y = get_(a, m)
			x0 = x % m
			print("计算完毕，逆元为" , x0, "。")
		else:
			print("两数不互素，逆元不存在！两数的最大公因数为", flag, "。")
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它字符回车以求取新的模逆元。")
		ex = input("")
		if ex.lower() == "exit":
			system("cls")
			exit(EXIT_SUCCESS)