#coding=gbk
from os import system as s
from sys import argv
def is_prime(m):
	'''�жϸ�������ֵm�Ƿ�Ϊ����������Ƿ���True�����򷵻�False��
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
				print("���жϣ����⡰ʵ�� " + num + " Ϊ������Ϊ", is_prime(int(num)), "��")
				count += 1
			except:
				print("�������Ϸ�����" + num + "����")
		exit(count)
	s("title �жϸ����������Ƿ�Ϊ����")
	while True:
		while True:
			s("cls")
			try:
				n = int(input("��������жϵ�������"))
				break
			except:
				print("\a������������������������밴������������롣")
				s("pause>nul")
		s("cls")
		print("���жϣ����⡰����", n, "Ϊ������Ϊ", is_prime(n), "��")
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens = input("")
		if Ens.lower() == "exit":
			s("cls")
			quit()