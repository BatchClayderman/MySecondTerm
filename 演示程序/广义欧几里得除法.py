from os import system
from sys import argv, exit, stdin
from msvcrt import getch
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
EOF = (-1)
EEOF = (-2)


def clearScreen(fakeClear = 120):
	if stdin.isatty():#在终端
		if "windows" == PLATFORM:
			system("cls")
		elif "linux" == PLATFORM:
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

def gcd(m, n, l) -> int:# 定义 gcd 函数
	try:
		if m == 0 or n == 0:
			return EOF
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if l != 0:
				print("\t", " " * (l - len(str(p))), p, "=", p // q, "×", q, "＋", p % q)
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q, l)
	except:
		return EEOF

def exgcd(p, q):# 定义exgcd 函数
	if p == 0 and q != 0:
		return "任意整数", 1
	elif q == 0 and p != 0:
		return 1, "任意整数"
	elif p == 0 and q == 0:
		return "任意整数", "任意整数"
	m = max(abs(p), abs(q))
	n = min(abs(p), abs(q))
	x = j = 1
	y = i = 0
	c = m
	d = n
	o = int(c / d)
	r = c % d
	while r:
		c = d
		d = r
		z = x
		x = i
		i = z - o * i
		z = y
		y = j
		j = z - o * j
		o = int(c / d)
		print("\t", {"s":i, "t":j, "r":r})
		r = c % d
	if abs(p) >= abs(q):
		return int(i * p / abs(p)), int(j * q / abs(q))
	else:
		return int(j * p / abs(p)), int(i * q / abs(q))

def addBrackets(num) -> str:
	return ("({0})" if num < 0 else "{0}").format(num)

def main():
	if 3 == len(argv):
		try:
			a = int(argv[1])
			b = int(argv[2])
			print(gcd(a, b, 0))
			print(exgcd(a, b))
			return EXIT_SUCCESS
		except:
			print("命令行参数不正确，请确保两个给定的数是整数！")
			return EXIT_FAILURE
	else:
		system("title 广义欧几里得除法&color e")
		clearScreen()
		while True:
			while True:
				clearScreen()
				try:
					a = int(input("请输入整数 a："))
					break
				except:
					print("\a错误：输入的数不是整数，请按任意键重新输入。")
					getch()
			while True:
				clearScreen()
				try:
					print("a =", a)
					b = int(input("请输入整数 b："))
					break
				except:
					print("\a错误：输入的数不是整数，请按任意键重新输入。")
					getch()
			clearScreen()
			print("正在使用欧几里得除法运行计算（{0}，{1}）。".format(a, b))
			result = gcd(a, b, len(str(max(abs(a), abs(b)))))
			if EOF == result:
				result = max(abs(a), abs(b))
			if EEOF == result:
				print("\a运算出错，可能存在算术溢出。")
			else:
				print("\n经运算，{0} 和 {1} 的最大公因数为 {2}。".format(a, b, result))
			s, t = exgcd(a, b)
			if str in (type(s), type(t)):#存在任意整数需要更换表达
				print("\n广义欧几里得除法得 sa ＋ tb = {0}，其中 s 为 {1}，t 为 {2}。".format(result, s, t))
			else:
				print("\n广义欧几里得除法得 {0} × {1} ＋ {2} × {3} = {4}，即 s = {5}，t = {6}。".format(
					addBrackets(s), addBrackets(a), addBrackets(t), addBrackets(b), addBrackets(result), s, t
				))
			print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
			if "exit" == input("").lower():
				clearScreen()
				break
		return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())