from os import system
from sys import argv, exit, stdin
from msvcrt import getch
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1


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

def gcd(m, n, l):# 定义 gcd 函数
	try:
		if m == 0 or n == 0:
			return 0
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if l != 0:
				print("\t", " "*(l - len(str(p))), p, "=", p // q, "·", q, "＋", p % q)
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
		o = int(c/ d)
		r = c % d
		print({"c":c, "d":d, "i":i, "j":j, "x":x, "y":y, "z":z})
	if abs(p) >= abs(q):
		return int(i * p / abs(p)), int(j * q / abs(q))
	else:
		return int(j * p / abs(p)), int(i * q / abs(q))

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
			print("正在使用广义欧几里得除法运行计算（" + str(a) + "，" + str(b) + "），运算过程如下：")
			result = gcd(a, b, len(str(max(abs(a), abs(b)))))
			if result == -2:
				clearScreen()
				print("\a运算出错，可能存在算术溢出。")
			if result == 0:
				clearScreen()
				print(a, "和", b, "的最大公因数为", max(abs(a), abs(b)), "。")
			else:
				print("\n经运算，", a, " 和 ", b, " 的最大公因数为", result, "。")
			s, t = exgcd(a, b)
			print("拓展欧几里得除法得 s = " + str(s) + "，t = " + str(t) + "。")
			print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
			if "exit" == input("").lower():
				clearScreen()
				break
		return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())