from os import system
from sys import argv, exit, stdin
from msvcrt import getch
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
pars = []


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

def gcd(m, n, ll = None):# 定义 gcd 函数
	if ll is None:
		l = len(str(max(abs(m), abs(n))))
		global pars
		pars = []
	else:
		l = ll
	try:
		if m == 0 or n == 0:
			return 0
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if l != 0: # 为输出而设立
				print("\t", " " * (l - len(str(p))), p, "=", q, "×", p // q, "＋", p % q)
				pars.append([p, q, p // q, p % q])
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q, l)
	except:
		return -2

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
	o = c // d
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
		o = c // d
		r = c % d
	if abs(p) >= abs(q):
		return int(i * p / abs(p)), int(j * q / abs(q))
	else:
		return int(j * p / abs(p)), int(i * q / abs(q))

def printProcess():
	if len(pars) == 1:
		print("\t", pars[0][1], "=", pars[0][1], "×", 1, "－", pars[0][0], "×", 0)
		return
	elif len(pars) < 1:
		return
	length = len(str(pars[-1][1]))
	a = pars[-2][0]; aa = None
	b = 1
	c = pars[-2][1]; cc = None
	d = pars[-2][2]
	print("\t", pars[-1][1], "=", a, "×", b, "－", c, "×", d)
	for line in range(len(pars) - 3, -1, -1):
		if cc is None:
			aa = None # Swap
			cc = [pars[line][0], 1, pars[line][1], pars[line][2]]
			print("\t", " " * length, "=", a, "×", b, "－", "({0} × {1} － {2} × {3})".format(*cc), "×", d)
			c = cc[0]
			b += cc[3] * d
			d *= cc[1]
			print("\t", " " * length, "=", a, "×", b, "－", c, "×", d)
		else:
			cc = None # Swap
			aa = [pars[line][0], 1, pars[line][1], pars[line][2]]
			print("\t", " " * length, "=", "({0} × {1} － {2} × {3})".format(*aa), "×", b, "－", c, "×", d)
			a = aa[0]
			d += aa[3] * b
			b *= aa[1]
			print("\t", " " * length, "=", a, "×", b, "－", c, "×", d)			
	print()
	
def main():
	if 3 == len(argv):
		try:
			a = int(argv[1])
			b = int(argv[2])
			print(gcd(a, b, 0))
			print(exgcd(a, b))
			return EXIT_SUCCESS
		except:
			print("命令行参数不正确，请确保两个给定的数是正整数！")
			return EXIT_FAILURE
	else:
		system("title 广义欧几里得除法&color e")
		clearScreen()
		while True:
			while True:
				system("cls")
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
			print("正在使用欧几里得除法运行计算（" + str(a) + "，" + str(b) + "），运算过程如下：")
			result = gcd(a, b)
			if result == -2:
				clearScreen()
				print("\a运算出错，可能存在算术溢出。")
			if result == 0:
				clearScreen()
				print(a, "和", b, "的最大公因数为", max(abs(a), abs(b)), "。")
			else:
				print("\n经运算，", a, " 和 ", b, " 的最大公因数为", result, "。")
			s, t = exgcd(a, b)
			if type(s) == int and type(t) == int:
				print("正在使用拓展欧几里得除法求 s、t，运算过程如下：")
				printProcess()
			print("\n拓展欧几里得除法得 s = " + str(s) + "，t = " + str(t) + "。")
			print("\n\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
			if "exit" == input("").lower():
				clearScreen()
				break
		return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())