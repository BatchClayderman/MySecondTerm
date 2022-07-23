from os import system
from sys import argv, exit, stdin
from msvcrt import getch
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
EOF = (-1)
EEOF = (-2)


# 清屏函数
def clearScreen(fakeClear = 120) -> None:
	if stdin.isatty():#在终端
		if PLATFORM == "windows":
			system("cls")
		elif PLATFORM == "linux":
			system("clear")
		else:
			try:
				print("\n" * int(fakeClear))
			except:
				print("\n" * 120)
	else:
		try:
			print("\n" * int(fakeClear))
		except:
			print("\n" * 120)

# 定义 modsq 递归函数
def modsqRec(x, n, m) -> int:
	try:
		if n == 0:
			return 1
		return x * modsqRec(x, n - 1, m) % m
	except:
		return EEOF

# 定义 modsq 递推函数
def modsq(x, n, m) -> int:
	try:
		a = 1
		b = x
		while True:
			temp = n
			if n % 2 == 1:
				a = a * b % m
			b = b * b % m
			n = n // 2
			if temp < 1:
				return a
	except:
		return EEOF

# 处理命令行参数
def dispose(argv) -> int:
	if len(argv) == 4:
		try:
			x = int(argv[1])
			n = int(argv[2])
			m = int(argv[3])
			assert(n >= 0 and m >= 2)
			assert (x != 0 and n != 0)
			print("\nx =", x, "\nn =", n, "\nm =", m)
			result1 = modsqRec(x, n, m)
			result2 = modsqRec(x, n, m)
			if result1 == EEOF:
				print("\a运算出错，可能存在算术溢出。")
			else:
				print("递归实现：", result1)
			if result2 == EEOF:
				print("\a运算出错，可能存在算术溢出。")
			else:
				print("递推实现：", result2)
			print()
			return EXIT_SUCCESS
		except:
			print("\a错误：命令行参数无效。")
			return EOF
	else:
		print("\a错误：命令行参数数目不正确。")
		return EOF

def main() -> int:
	if len(argv) > 1:
		return dispose(argv)
	system("title 模重复平方法&color e&cls")
	while True:
		while True:
			clearScreen()
			try:
				x = int(input("请输入底数x："))
				break
			except:
				print("\a错误：输入的数不是整数，请按任意键重新输入。")
				getch()
		while True:
			clearScreen()
			print("x =", x)
			try:
				n = int(input("请输入指数n："))
				assert(n >= 0)
				assert(x != 0 and n != 0)
				break
			except:
				print("\a错误：指数 n 必须是自然数，或 0 的 0 次方无意义，请按任意键重新输入。")
				getch()
		while True:
			clearScreen()
			print("x =", x)
			print("n =", n)
			try:
				m = int(input("请输入模m："))
				assert(m >= 2)
				break
			except:
				print("\a错误：指数 m 必须是大于 1 的正整数，请按任意键重新输入。")
				getch()
		system("cls")
		print("x =", x, "\nn =", n, "\nm =", m)
		result1 = modsqRec(x, n, m)
		result2 = modsqRec(x, n, m)
		if result1 == EEOF:
			clearScreen()
			print("\a运算出错，可能存在算术溢出。")
		else:
			print("递归实现：", result1)
		if result2 == EEOF:
			clearScreen()
			print("\a运算出错，可能存在算术溢出。")
		else:
			print("递推实现：", result2)
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			clearScreen()
			return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())