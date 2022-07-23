from os import system
from sys import argv, exit, stdin
PLATFORM = __import__("platform").system().lower()
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
EOF = (-1)


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

def lrd(p1, p2):
	if p1 == 0:
		return 0
	count = 0
	for i in range(p2):
		if i ** 2 % p2 == p1 % p2:
			count += 1
	if count == 0:
		return -1
	else:
		return count

def main():
	if len(argv) == 3:
		try:
			p1 = int(argv[1])
			p2 = int(argv[2])
			print(lrd(p1, p2))
		except:
			print("\a错误：所输入的参数不合法。")
			return EOF
		return EXIT_SUCCESS
	elif len(argv) != 1:
		print("\a错误：命令行参数数目不正确。")
		return EOF
	system("title 勒让德符号&color e")
	while True:
		clearScreen()
		while True:
			try:
				p1 = int(input("请输入p1："))
				clearScreen()
				break
			except:
				pass
		while True:
			try:
				print("p1 = {0}".format(p1))
				p2 = int(input("请输入p2："))
				clearScreen()
				break
			except:
				pass
		print("p1 = {0}\np2 = {1}".format(p1, p2))
		result = lrd(p1, p2)
		if result == -1:
			print("\nlrd(", p1, "|", p2, ") = -1")
			print("解数： 0")
		else:
			print("\nlrd(", p1, "|", p2, ") = 1")
			print("解数：", result)
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			clearScreen()
			return EXIT_SUCCESS



if __name__ == "__main__":
	exit(main())