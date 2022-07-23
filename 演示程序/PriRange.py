#coding=gbk
import os
from math import sqrt
def primes_in_range(k):
	'''
	���С�ڵ�����Ȼ�� k ��������������������б��С�
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
			print("\n��������С�ڵ���", n, "�������б����£�")
			print(primes_in_range(n))
		print("")
		exit(count)
	os.system("title ö��ĳ��Χ�ڵ���������&color e")
	while True:
		os.system("cls")
		try:
			n = int(input("������һ����Ȼ����"))
			if n < 0:
				assert ""
		except:
			print("\a")
			continue
		os.system("cls")
		print("��������С�ڵ���", n, "�������б����£�")
		print(primes_in_range(n))
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens=input("")
		if Ens.lower()=="exit":
			os.system("cls")
			quit()