#coding=gbk
import os
from math import sqrt
def primes_in_range(k):
	'''
	求出小于等于自然数 k 的所有质数，结果放在列表中。
	>>> primes_in_range(-10)
	[]
	>>> primes_in_range(0)
	[]
	>>> primes_in_range(2)
	[2]
	>>> primes_in_range(10)
	[2, 3, 5, 7]
	>>> primes_in_range(20)
	[2, 3, 5, 7, 11, 13, 17, 19]
	'''
	try:
		n = int(k)
		if n <= 1:
			assert ""
	except:
		return []
	lists = []
	for i in range(2, n+1):
		for j in range(2, i):
			if i % j == 0:
				break
		else:
			lists.append(i)
	return(lists)
if __name__=="__main__":
	from sys import argv
	if len(argv) != 1:
		count = 0
		for i in argv[1:]:
			try:
				n = int(i)
				if n < 0:
					assert ""
			except:
				continue
			print("\n经分析，小于等于", n, "的质数列表如下：")
			print(primes_in_range(n))
		print("")
		exit(count)
	os.system("title 枚举某范围内的所有质数&color e")
	while True:
		os.system("cls")
		try:
			n = int(input("请输入一个自然数："))
			if n < 0:
				assert ""
		except:
			print("\a")
			continue
		os.system("cls")
		print("经分析，小于等于", n, "的质数列表如下：")
		print(primes_in_range(n))
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens=input("")
		if Ens.lower()=="exit":
			os.system("cls")
			quit()