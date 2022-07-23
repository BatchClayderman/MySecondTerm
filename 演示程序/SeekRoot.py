#coding=gbk
import os
from sys import argv
from math import sqrt
# 定义gcd函数
def gcd(m, n, l):
	try:
		if m == 0 or n == 0:
			return 0
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if l!=0:
				print("\t", " "*(l-len(str(p))), p, "=", p // q, "·", q, "＋", p % q)
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q, l)
	except:
		return -2
# 定义欧拉函数
def euler(x):
	try:
		a = int(x)
	except:
		return 0
	count = 0
	for i in range(1, a):
		if gcd(a, i, 0) == 1:
			count += 1
	return count
# 定义order函数
def order(a, n, b):
	try:
		a = int(a)
		n = int(n)
		b = int(b)
	except:
		return -1
	p = 1
	while (p <= n and (b ** p % a != 1)):
		p += 1
	if p <= n:
		return p
	else:
		return -1
# 定义原根函数
def SeekRoot(a):
	try:
		if int(a) < 1:
			assert ""
	except:
		return []
	n = euler(a)
	prim = []
	for b in range(2, a):
		if order(a, n, b) == n:
			prim.append(b)
	return prim
# 命令行与面向用户处理
if __name__=="__main__":
	if len(argv) != 1:
		count=0
		for num in argv[1:]:
			try:
				print(int(num), SeekRoot(int(num)))
				count += 1
			except:
				print("参数不合法：“" + num + "”，或是运算过程中用户取消了操作。")
		exit(count)
	os.system("title 求原根&color e&cls")
	while True:
		os.system("cls")
		try:
			n = int(input("请输入的正整数："))
			if n < 1:
				assert ""
		except:
			print("\a")
			continue
		os.system("cls")
		print("正在执行计算，请稍候。")
		print(SeekRoot(n))
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens=input("")
		if Ens.lower()=="exit":
			os.system("cls")
			quit()