#coding=gbk
# ȡ���Լ��
def gcd(p1, p2):
	try:
		m = int(p1)
		n = int(p2)
		if m == 0 or n == 0:
			return 0
		else:
			p = max(abs(m), abs(n))
			q = min(abs(m), abs(n))
			if p % q == 0:
				return q
			else:	
				return gcd(q, p % q)
	except:
		return -2
# ������
def _zm(a, m, flag):
	try:
		p1 = int(a)
		p2 = int(m)
	except:
		return -1
	if p1 < 2 or p2 < 2:
		return 0
	i = 1
	try:
		while True:
			if p1 ** i % p2 == 1:
				print(p1, "^", i, "��", p1 ** i % p2, "(mod " + str(p2) + ")")
				return i
			else:
				if flag:
					print(p1, "^", i, "��", p1 ** i % p2, "(mod " + str(p2) + ")")
				i += 1
	except:
		return -2
	return 0
# �����������
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a������Ч�������в�������" + str(option) + "����")
	print("��������ģָ����\n\n�����б�\n\t/true\t\t��ӡ����\n\t/false\t\t����ӡ����ֵ\n\t[p1]\t\t���� a ��ֵ������ 1 ����Ȼ����\n\t[p2]\t\tģ m ��ֵ������ 1 ����Ȼ����\n")
	print("�����и�ʽ��\n\tzm.py [/true|/false] [p1] [p2]")
	print("ʾ����\n\tzm.py /true 2 13\n\tzm.py /false 5 13\n")
	print("�ر�˵����\n\t������ģ����Ӧ���Ǵ��� 1 ����Ȼ������������\n")
	if option == "/?" or option == "-?":
		return 0
	else:
		return -1
if __name__ == "__main__":
	from os import system
	from sys import argv
	if "/?" in argv or "-?" in argv:
		exit(help("/?"))
	if len(argv) == 4:
		if argv[1].lower() == "/true" or argv[1].lower() == "-true":
			flag = True
		elif argv[1].lower() == "/false" or argv[1].lower() == "-false":
			flag = False
		else:
			exit(help(argv[1]))
		try:
			p1 = int(argv[2])
			p2 = int(argv[3])
			if p1 < 2:
				help(argv[2])
				assert ""
			if p2 < 2:
				help(argv[3])
				assert ""
			if gcd(p1, p2) != 1:
				help(argv[2:4])
				assert ""
			_zm(p1, p2, flag)
		except:
			exit(-1)
		exit(0)
	elif len(argv) != 1:
		help(argv[1:])
		exit(-1)
	system("title ��ģָ������ϼ���Ctrl+C�����жϼ��㣩&color e")
	while True:
		system("cls")
		print("��������� a��")
		p1 = input("")
		print("������ģ�� m��")
		p2 = input("")
		system("cls")
		if gcd(p1, p2) == 1:
			result = _zm(p1, p2, True)
			if result == -2:
				print("��ʾ�����ж������С�")
			elif result == -1:
				print("\a������������Ƿ���")
			elif result == 0:
				print("\a����������Ĳ��Ǵ��� 1 ����Ȼ����")
		else:
			print("\a��������������������ء�")
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()