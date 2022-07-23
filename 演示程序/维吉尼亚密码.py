#coding=gbk
from os import system as s
from sys import argv
from sys import exit
Alpha = "abcdefghijklmnopqrstuvwxyz"
Num = "0123456789"
def Vencode(n1, n2):
	r = ""
	text1 = ""
	text2 = ""
	n1 = n1.lower()
	for string in n1:
		if string in Alpha:
			text1  += string
	for string in n2:
		if string in Num:
			text2  += string
	if text1 == "" or text2 == "":
		return r
	print("\n�������ַ�����\n" + text1 + "\n" + text2 + "\n\n��������������")
	for i in range(max(len(text1), len(text2))):
		r  += Alpha[(Alpha.find(text1[i % len(text1)]) + Num.find(text2[i % len(text2)])) % 26]
	return r
def Vdecode(n1, n2):
	r = ""
	text1 = ""
	text2 = ""
	n1 = n1.lower()
	for string in n1:
		if string in Alpha:
			text1  += string
	for string in n2:
		if string in Num:
			text2  += string
	if text1 == "" or text2 == "":
		return r
	print("\n�������ַ�����\n" + text1 + "\n" + text2 + "\n\n��������������")
	for i in range(max(len(text1), len(text2))):
		r += Alpha[(Alpha.find(text1[i % len(text1)]) - Num.find(text2[i % len(text2)])) % 26]
	return r
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a������Ч�������в�������" + str(option) + "����")
	print("������ά������������ܻ���ܡ�\n\n�����б�\n\t[Strings]\tӢ���ַ���\n\t[ + /-]\t\t�����\n\t[Numbers]\t�����ַ���\n")
	print("�����и�ʽ��\n\tά����������.py [Strings] [ + /-] [Numbers]\n")
	print("ʾ����\n\tά����������.py \"I love you for ever\" + 5203344\n\tά����������.py jmpwfzpvgpsfwfs - 1\n")
	if option != "/?" and option != "-?":
		return 0
	else:
		return -1
if __name__  ==  "__main__":
	if ("/?" in argv) or ("-?" in argv):
		exit(help("/?"))
	if len(argv) == 4:
		if argv[2] == "+":
			result = Vencode(argv[1], argv[3])
			if result == "":
				print("\a���Ĳ�����ĸ����Կ�������֡�")
			print(result)
			print(result.upper())
			print("")
		elif argv[2] == "-":
			result = Vdecode(argv[1], argv[3])
			if result == "":
				print("\a���Ĳ�����ĸ����Կ�������֡�")
			print(result)
			print(result.upper())
			print("")
		else:
			exit(help(argv[2]))
		exit(0)
	elif len(argv) != 1:
		exit(help(argv[1:]))
	s("title ά����������&color e")
	while True:
		s("cls")
		print("1  =  ����\t2  =  ����\t0  =  �˳�����\n��ѡ��һ���Լ�����")
		try:
			c = int(input(""))
		except:
			print("\a")
			continue
		s("cls")
		if c == 1:
			s("cls")
			print("���������ģ�", end = '')
			n1 = input("")
			print("�����������ַ�����", end = '')
			n2 = input("")
			result = Vencode(n1, n2)
			if result == "":
				print("\n\a���Ĳ�����ĸ����Կ�������֣��밴��������ء�")
			else:
				print(result + "\n" + result.upper() + "\n\n\n�밴��������ء�")
			s("pause>nul")
		elif c == 2:
			s("cls")
			print("���������ģ�", end = '')
			n1 = input("")
			print("�����������ַ�����", end = '')
			n2 = input("")
			result = Vdecode(n1, n2)
			if result == "":
				print("\n\a���Ĳ�����ĸ����Կ�������֣��밴��������ء�")
			else:
				print(result + "\n" + result.upper() + "\n\n\n�밴��������ء�")
			s("pause>nul")
		elif c == 0:
			break
		else:
			print("\a")
			continue
	s("cls")
	print("��ӭ�ٴ�ʹ�ã��밴������˳�������")
	s("pause>nul&cls")
	exit(0)