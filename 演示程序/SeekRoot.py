#coding=gbk
import os
from sys import argv
from math import sqrt
# ����gcd����
def gcd(m, n, l):
	try:
		if m == 0 or n == 0:
			return 0
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if l!=0:
				print("\t", " "*(l-len(str(p))), p, "=", p // q, "��", q, "��", p % q)
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q, l)
	except:
		return -2
# ����ŷ������
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
# ����order����
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
# ����ԭ������
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
# �������������û�����
if __name__=="__main__":
	if len(argv) != 1:
		count=0
		for num in argv[1:]:
			try:
				print(int(num), SeekRoot(int(num)))
				count += 1
			except:
				print("�������Ϸ�����" + num + "������������������û�ȡ���˲�����")
		exit(count)
	os.system("title ��ԭ��&color e&cls")
	while True:
		os.system("cls")
		try:
			n = int(input("���������������"))
			if n < 1:
				assert ""
		except:
			print("\a")
			continue
		os.system("cls")
		print("����ִ�м��㣬���Ժ�")
		print(SeekRoot(n))
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens=input("")
		if Ens.lower()=="exit":
			os.system("cls")
			quit()