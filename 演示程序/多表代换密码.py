#coding=gbk
from os import system as s
from sys import argv
Alpha="abcdefghijklmnopqrstuvwxyz"
def doubleencode(n1, n2):
	r=""
	text1=""
	text2=""
	n1=n1.lower()
	n2=n2.lower()
	for str in n1:
		if str in Alpha:
			text1+=str
	for str in n2:
		if str in Alpha:
			text2+=str
	if text1=="" or text2=="":
		return r
	print("\n�������ַ�����\n"+text1+"\n"+text2+"\n\n��������������")
	for i in range(max(len(text1), len(text2))):
		r+=Alpha[(Alpha.find(text1[i%len(text1)])+Alpha.find(text2[i%len(text2)]))%26]
	return r
def doubledecode(n1, n2):
	r=""
	text1=""
	text2=""
	n1=n1.lower()
	n2=n2.lower()
	for str in n1:
		if str in Alpha:
			text1+=str
	for str in n2:
		if str in Alpha:
			text2+=str
	if text1=="" or text2=="":
		return r
	print("\n�������ַ�����\n"+text1+"\n"+text2+"\n\n��������������")
	for i in range(max(len(text1), len(text2))):
		r+=Alpha[(Alpha.find(text1[i%len(text1)])-Alpha.find(text2[i%len(text2)]))%26]
	return r
def help(option):
	print("")
	if option!="/?" and option!="-?":
		print("\a������Ч�������в�������"+str(option)+"����")
	print("������������������ܻ���ܡ�\n\n�����б�\n\t[strings1]\t��һ���ַ���\n\t[+/-]\t\t�����\n\t[strings2]\t�ڶ����ַ���\n")
	print("�����и�ʽ��\n\t����������.py [strings1] [+/-] [strings2]\n")
	print("ʾ����\n\t����������.py \"I love you for ever\" + \"you love me\"\n\t����������.py jmpwfxtzgpsfwfs - b\n")
	if option!="/?" and option!="-?":
		return 0
	else:
		return -1
if ("/?" in argv) or ("-?" in argv):
	exit(help("/?"))
if len(argv)==4:
	if argv[2]=="+":
		result=doubleencode(argv[1], argv[3])
		print(result)
		print(result.upper())
		print("")
	elif argv[2]=="-":
		result=doubledecode(argv[1], argv[3])
		print(result)
		print(result.upper())
		print("")
	else:
		exit(help(argv[2]))
	exit(0)
elif len(argv)!=1:
	exit(help(argv[1:]))
if __name__ == "__main__":
	s("title ����������&color e")
	while True:
		s("cls")
		print("1 = ����\t2 = ����\t0 = �˳�����\n��ѡ��һ���Լ�����")
		try:
			c=int(input(""))
		except:
			print("\a")
			continue
		s("cls")
		if c==1:
			s("cls")
			print("�������һ���ַ�����", end='')
			n1=input("")
			print("������ڶ����ַ�����", end='')
			n2=input("")
			result=doubleencode(n1, n2)
			if result=="":
				print("\n\a���Ļ���Կ������ĸ���밴��������ء�")
			else:
				print(result+"\n"+result.upper()+"\n\n�밴��������ء�")
			s("pause>nul")
		elif c==2:
			s("cls")
			print("�������һ���ַ�����", end='')
			n1=input("")
			print("������ڶ����ַ�����", end='')
			n2=input("")
			result=doubledecode(n1, n2)
			if result=="":
				print("\n\a���Ļ���Կ������ĸ���밴��������ء�")
			else:
				print(result+"\n"+result.upper()+"\n\n\n�밴��������ء�")
			s("pause>nul")
		elif c==0:
			break
		else:
			print("\a")
			continue
	s("cls")
	print("��ӭ�ٴ�ʹ�ã��밴������˳�������")
	s("pause>nul&cls")
	quit()