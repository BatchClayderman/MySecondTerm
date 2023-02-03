from os import system
from sys import argv, exit, stdin
from msvcrt import getch
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
pars = []


def clearScreen(fakeClear = 120) -> None:
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

def getMulMode(x, mul_mode = None) -> str:
	if mul_mode is None:
		return str(x)
	elif type(mul_mode) == int and mul_mode > 0:
		return str(x) + " " * (mul_mode - 1) + "×"
	elif type(mul_mode) == int and mul_mode < 0:
		return "×" + " " * (-mul_mode - 1) + str(x)
	else:
		return ""

def getX(n, mul_mode = None) -> str: # None = 默认，0 = 隐藏，1 = 右输出" × "，-1 = 左输出" × "
	if type(n) in (tuple, list, set):
		return [getX(item) for item in n]
	elif type(n) == dict:
		return {item:getX(item) for item in list(n.keys())}
	if type(n) != int:
		return ""
	elif n < 0:
		return "-" + getX(-n)
	in_list = bin(n)[2:]
	out_list = []
	for i, ele in enumerate(in_list[:-2]):
		if ele == "1":
			out_list.append("x^{0}".format(len(in_list) - i - 1))
	else:
		if len(in_list) > 1 and in_list[-2] == "1":
			out_list.append("x")
		if in_list[-1] == "1":
			out_list.append("1")
	if out_list:
		if len(out_list) == 1:
			if out_list == ["1"]:
				return getMulMode("1", mul_mode)
			else:
				return out_list[0]
		else:
			return "(" + " + ".join(out_list) + ")"
	else:
		return getMulMode("0", mul_mode)

def getDHX(n) -> str: # 连等号输出
	if type(n) in (tuple, list, set):
		return [getDHX(item) for item in n]
	elif type(n) == dict:
		return {item:getDHX(item) for item in list(n.keys())}
	elif type(n) == int:
		return " = ".join([str(n), hex(n), getX(n)])
	else:
		return ""

def gcd(m, n, ll = None) -> int:# 定义 gcd 函数
	if ll is None:
		l = max(len(getX(m)), len(getX(n))) # l = len(str(max(abs(m), abs(n))))
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
				print("\t", " " * (l - len(getX(p))), getX(p), "=", (getX(q, 1) + getX(p // q, -1)).replace("×  ×", "×") , "＋", getX(p % q))
				pars.append([p, q, p // q, p % q])
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q, l)
	except Exception as e:
		print(e)
		input()
		return -2

def exgcd(p, q) -> tuple:# 定义exgcd 函数
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

def printProcess() -> None:
	if len(pars) == 1:
		print("\t", pars[0][1], "=", pars[0][1], "×", 1, "－", pars[0][0], "×", 0)
		return
	elif len(pars) < 1:
		return
	length = len(getX(pars[-1][1])) # length = len(str(pars[-1][1]))
	a = pars[-2][0]; aa = None
	b = 1
	c = pars[-2][1]; cc = None
	d = pars[-2][2]
	print("\t", " " * (length - len(str(pars[-1][1])) - 1), pars[-1][1], "=", a, "×", b, "－", c, "×", d)
	print("\t", " " * (length - len(getX(pars[-1][1])) - 1), getX(pars[-1][1]), "=", (getX(a, 1) + getX(b, -1)).replace("×  ×", "×"), "－", (getX(c, 1) + getX(d, -1)).replace("×  ×", "×"))
	for line in range(len(pars) - 3, -1, -1):
		if cc is None:
			aa = None # Swap
			cc = [pars[line][0], 1, pars[line][1], pars[line][2]]
			print("\t", " " * length, "=", a, "×", b, "－", "({0} × {1} － {2} × {3})".format(*cc), "×", d)
			print("\t", " " * length, "=", (getX(a, 1) + getX(b, -1)).replace("×  ×", "×"), "－", "({0}{1} － {2}{3})".format(*getX(cc)).replace("×  ×", "×") + getX(d, -1))
			c = cc[0]
			b += cc[3] * d
			d *= cc[1]
		else:
			cc = None # Swap
			aa = [pars[line][0], 1, pars[line][1], pars[line][2]]
			print("\t", " " * length, "=", "({0} × {1} － {2} × {3})".format(*aa), "×", b, "－", c, "×", d)
			print("\t", " " * length, "=", "({0}{1} － {2}{3})".format(*getX(aa)).replace("×  ×", "×") + getX(b, -1), "－", (getX(c, 1) + getX(d, -1)).replace("×  ×", "×"))
			a = aa[0]
			d += aa[3] * b
			b *= aa[1]
		print("\t", " " * length, "=", a, "×", b, "－", c, "×", d)
		print("\t", " " * length, "=", (getX(a, 1) + getX(b, -1)).replace("×  ×", "×"), "－", (getX(c, 1) + getX(d, -1)).replace("×  ×", "×"))			
	print()
	
def main() -> int:
	if 3 == len(argv):
		try:
			a = int(argv[1])
			b = int(argv[2])
			print("gcd({0}，{1}) = {2}".format(getDHX(a), getDHX(b), getDHX(gcd(a, b, 0))))
			print("({0}，{1})".format(*getDHX(exgcd(a, b))))
			return EXIT_SUCCESS
		except:
			print("命令行参数不正确，请确保两个给定的数是正整数！")
			return EXIT_FAILURE
	else:
		if stdin.isatty():
			system("title 拓展欧几里得除法&color e")
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
				print("gcd(a = {0}，b = {1})".format(a, b))
				print("\a运算出错，可能存在算术溢出。")
			else:
				if result == 0:
					clearScreen()
					print("a = {0} 和 b = {1} 的最大公因数为 {2}。".format(getDHX(a), getDHX(b), getDHX(max(abs(a), abs(b)))))
				else:
					print("\n经运算，a = {0} 和 b = {1} 的最大公因数为 {2}。".format(getDHX(a), getDHX(b), getDHX(result)))
				s, t = exgcd(a, b)
				if type(s) == int and type(t) == int:
					print("正在使用拓展欧几里得除法求 s、t，运算过程如下：")
					printProcess()
				print("\n拓展欧几里得除法得 s = {0}，t = {1}。".format(getDHX(s), getDHX(t)))
			print("\n\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
			if "exit" == input("").lower():
				clearScreen()
				break
		return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())