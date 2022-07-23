#coding=gbk
def lfs(a, m, flag):
	try:
		p1 = int(a)
		p2 = int(m)
	except:
		return []
	if p2 == 0:
		return ["NULL"]
	a = []
	xp = []
	xq = []
	i = 0
	try:
		while True:
			a.append(p1 // p2)
			xp.append(p1 % p2)
			xq.append(p2)
			if i == 0:
				if flag:
					print("a0 = [", p1, "/", p2, "] =", a[0], "��x0", "= x - a0 =", xp[i], "/", xq[i])
			else:
				if xp[i] == 0:
					if flag:
						print("a" + str(i), "= [", p1, "/", p2, "] =", a[i], "��x" + str(i), "= 1 / x" + str(i - 1), "- a" + str(i), "= 0")
					return a
				else:
					if flag:
						print("a" + str(i), "= [", p1, "/", p2, "] =", a[i], "��x" + str(i), "= 1 / x" + str(i - 1), "- a" + str(i), "=", xp[i], "/", xq[i])
			p1 = xq[i]
			p2 = xp[i]
			i += 1
	except:
		return ["break"]
	return 0
# �����������
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a������Ч�������в�������" + str(option) + "����")
	print("����������������\n\n�����б�\n\t/true\t\t��ӡ����\n\t/false\t\t����ӡ����ֵ\n\t[p1]\t\t����\n\t[p2]\t\t��ĸ\n")
	print("�����и�ʽ��\n\tlfs.py [/true|/false] [p1] [p2]")
	print("ʾ����\n\tlfs.py /true 7700 2145\n\tlfs.py /false -97 73\n\tlfs.py /true 5391 3976\n")
	if option == "/?" or option == "-?":
		return 0
	else:
		return -1
if __name__ == "__main__":
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
		result = lfs(argv[2], argv[3], flag)
		if result == []:
			exit(help(argv[2:4]))
		elif result == ["NULL"]:
			print("\a���󣺷�ĸ����Ϊ 0��")
		elif result == ["break"]:
			print("\n��ʾ������ֹ�����㡣\n")
			quit()
		else:
			print(result, end = "\t")
			result[len(result) - 1] -= 1
			result.append(1)
			print(result, "\n")
		exit(0)
	elif len(argv) != 1:
		exit(help(argv[1:]))
	from os import system
	system("title ������������ϼ���Ctrl+C�����жϼ��㣩&color e")
	while True:
		system("cls")
		try:
			print("��������ӣ�", end = '')
			p1 = input("")
			print("�������ĸ��", end = '')
			p2 = input("")
		except:
			system("cls")
			break
		system("cls")
		result = lfs(p1, p2, True)
		if result == []:
			print("\a�������������޷����м��㡣")
		elif result == ["NULL"]:
			print("\a���󣺷�ĸ����Ϊ 0��")
		elif result == ["break"]:
			print("\n��ʾ������ֹ�����㡣")
		else:
			print("\n������ϣ�x = [", p1, "/", p2, "]����������ʽ���£�")
			print(result, end = "\t")
			result[len(result) - 1] -= 1
			result.append(1)
			print(result)
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()