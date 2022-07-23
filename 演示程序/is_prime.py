#coding=gbk
from os import system as s
from sys import argv
def is_prime(m):
	'''判断给定的数值m是否为质数。如果是返回True，否则返回False。
	>>> is_prime(2)
	True
	>>> is_prime(53)
	True
	>>> is_prime(9)
	False
	>>> is_prime(1)
	False
	'''
	try:
		n = abs(int(m))
		if n == 0 or n == 1:
			assert ""
	except:
		return False
	for i in range(2, n):
		if n % i == 0:
			break
	else:
		return True
	return False
if __name__ == "__main__":
	if len(argv)!=1:
		count = 0
		for num in argv[1:]:
			try:
				print("经判断，命题“实数 " + num + " 为质数”为", is_prime(int(num)), "。")
				count += 1
			except:
				print("参数不合法：“" + num + "”。")
		exit(count)
	s("title 判断给定的整数是否为质数")
	while True:
		while True:
			s("cls")
			try:
				n = int(input("请输入待判断的整数："))
				break
			except:
				print("\a错误：所输入的数不是整数，请按任意键重新输入。")
				s("pause>nul")
		s("cls")
		print("经判断，命题“整数", n, "为质数”为", is_prime(n), "。")
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			s("cls")
			quit()