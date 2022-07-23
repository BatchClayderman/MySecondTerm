#coding=gbk
import os
from sys import argv
from math import sqrt
def isPrime(q):
	if q<=1:
		return False
	elif q==2 or q==3:
		return True
	else:
		c=0
		for k in range(2, int(sqrt(q)) + 1):
			if q%k==0:
				c=1
				break
		if c==0:
			return True
		else:
			return False
def dePrime(q):
	strings=str(q)+" = "
	for k in range(2, q+1):
		if isPrime(k):
			d=0
			while q%k==0:
				d+=1
				q/=k
			if d==0:
				continue
			elif d==1:
				strings=strings+str(k)+" * "
			else:
				strings=strings+str(k)+"^"+str(d)+" * "
	return strings[0:-3]
if __name__=="__main__":
	if len(argv)!=1:
		count=0
		for num in argv[1:]:
			try:
				print(dePrime(int(num)))
				count+=1
			except:
				print("�������Ϸ�����"+num+"����")
		exit(count)
	os.system("title �ֽ�������&color e&cls")
	while True:
		os.system("cls")
		try:
			n=int(input("��������� 1 ����������"))
			if n<2:
				assert ""
		except:
			print("\a")
			continue
		os.system("cls")
		print("����ִ�зֽ⣬���Ժ�")
		print(dePrime(n))
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens=input("")
		if Ens.lower()=="exit":
			os.system("cls")
			quit()