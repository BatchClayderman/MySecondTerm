#coding=gbk
import platform
from sys import exit#��ֹ��� exe ʱ����
EXIT_SUCCESS = 0#�����ɹ�����
EOF = (-1)#�����в�������ȷ

# ������غ���
def get_gcd(a, b):
	k = a // b
	remainder = a % b
	while remainder != 0:
		a = b
		b = remainder
		k = a // b
		remainder = a % b
	return b
def get_(a, b):
	if b == 0:
		return 1, 0
	else:
		k = a // b
		remainder = a % b
		x1, y1 = get_(b, remainder)
		x, y = y1, x1 - k * y1
		return x, y

# �����������
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a������Ч�������в�������"+str(option)+"����")
	print("��������ģ��Ԫ��\n\n�����б�\n\t/a\t\t����ϵ����ֵ\n\t/m\t\t����ģ����ֵ\n\t[a]\t\tϵ��ֵ\n\t[m]\t\tģ��ֵ\n")
	print("�����и�ʽ��\n\tarcmod.py /a [a] /m [m]\n")
	print("ʾ����\n\tarcmod.py /a 5 /m 203344\n\tarcmod.py /a 5 /m 20\n")
	if option == "/?" or option == "-?":
		return EXIT_SUCCESS
	else:
		return EOF

def dealArgv():# ���������в���
	from sys import argv
	if "/?" in argv or "-?" in argv:
		exit(help("/?"))
	if len(argv) == 5:
		if argv[1].lower() == "/a" or argv[1].lower() == "-a":
			try:
				a = int(argv[2])
				if a <= 0:
					assert ""
			except:
				print("\a�����ṩ��ϵ���Ƿ���\n")
				exit(EOF)
		elif argv[1].lower() == "/m" or argv[1].lower() == "-m":
			try:
				m = int(argv[2])
				if m <= 1:
					assert ""
			except:
				print("\a�����ṩ��ģ���Ƿ���\n")
				exit(EOF)
		if argv[3].lower() == "/a" or argv[3].lower() == "-a":
			try:
				a = int(argv[4])
				if a < 4:
					assert ""
			except:
				print("\a�����ṩ��ϵ��������\n")
				exit(EOF)
		elif argv[3].lower() == "/m" or argv[3].lower() == "-m":
			try:
				m = int(argv[4])
				if m < 1:
					assert ""
			except:
				print("\a�����ṩ��ģ��������\n")
				exit(EOF)
		try:
			print("a =", a)
		except:
			print("\a����δ����ϵ����")
			exit(EOF)
		try:
			print("m =", m)
		except:
			print("\a����δ����ģ����")
			exit(EOF)
		flag = get_gcd(a, m)
		if flag==1:
			x, y = get_(a, m)
			x0 = x % m
			print("x =", x0)
			exit(EXIT_SUCCESS)
		else:
			print("��a��m��=", flag)
			exit(EXIT_SUCCESS)
	elif len(argv) != 1:
		exit(help(argv[1:]))
	del argv

# ������
if __name__ == "__main__":
	dealArgv()
	from os import system
	system("title ��ģ��Ԫ&color e&cls")
	while True:
		system("cls")
		try:
			a = int(input("������ϵ��������������"))
			if a <= 0:
				assert ""
			m = int(input("������ģ�������� 1 ������������"))
			if m <= 1:
				assert ""
		except:
			print("\a���벻�Ϸ����밴������������롣")
			system("pause>nul&cls")
			continue
		flag = get_gcd(a, m)
		if flag == 1:
			x, y = get_(a, m)
			x0 = x % m
			print("������ϣ���ԪΪ" , x0, "��")
		else:
			print("���������أ���Ԫ�����ڣ��������������Ϊ", flag, "��")
		print("\n\n���롰exit���������ִ�Сд���س��˳��������������ַ��س�����ȡ�µ�ģ��Ԫ��")
		ex = input("")
		if ex.lower() == "exit":
			system("cls")
			exit(EXIT_SUCCESS)