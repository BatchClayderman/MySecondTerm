#coding=gbk
from os import system as s
from sys import argv
Alpha="abcdefghijklmnopqrstuvwxyz"
def encode(text, k):
	r=""
	for i in range(len(text)):
		if Alpha.find(text[i])==-1:
			if Alpha.find(text[i].lower())==-1:
				r+=text[i]
			else:
				r+=Alpha[(Alpha.find(text[i].lower())+k)%26].upper()
		else:
			r+=Alpha[(Alpha.find(text[i])+k)%26]
	return r
def decode(text, k):
	r=""
	for i in range(len(text)):
		if Alpha.find(text[i])==-1:
			if Alpha.find(text[i].lower())==-1:
				r+=text[i]
			else:
				r+=Alpha[(Alpha.find(text[i].lower())-k)%26].upper()
		else:
			r+=Alpha[(Alpha.find(text[i])-k)%26]
	return r
def help(option):
	print("")
	if option!="/?" and option!="-?":
		print("\a������Ч�������в�������"+str(option)+"����")
	print("�������������������ܻ���ܡ�\n\n�����б�\n\tencode\t\t����\n\tdecode\t\t����\n\t[strings]\t�����ܻ���ܵ�����\n\t[k]\t\tλ��ֵ��0Ϊ������\n")
	print("�����и�ʽ��\n\t�����������.py encode [strings] [k]\n\t�����������.py decode [strings] [k]\n")
	print("ʾ����\n\t�����������.py encode \"I love wsy\" 5203344\n\t�����������.py decode \"Y belu mio\" 5203344\n")
	if option!="/?" and option!="-?":
		return 0
	else:
		return -1
if ("/?" in argv) or ("-?" in argv):
	exit(help("/?"))
elif len(argv)==4:
	try:
		k=int(argv[3])
	except:
		exit(help(argv[3]))
	if argv[1].lower()=="encode":
		print("")
		if k==0:
			for i in range(26):
				print([i, encode(argv[2], i)])
		else:
			print(encode(argv[2], k))
		print("")
	elif argv[1].lower()=="decode":
		print("")
		if k==0:
			for i in range(26):
				print([i, decode(argv[2], i)])
		else:
			print(decode(argv[2], k))
		print("")
	else:
		exit(help(argv[1]))
	exit(0)
elif len(argv)!=1:
	exit(help(argv[1:]))
if __name__ == "__main__":
	s("title �����������&color e")
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
			while True:
				s("cls")
				print("������λ��ֵ�����븺���ɷ�������壬����0�����������", end='')
				try:
					k=int(input(""))
					if k<0:
						break
				except:
					print("\a")
					continue
				text=input("������������ַ�����")
				if k==0:
					print("\n\nѭ��ִ�����£�")
					for i in range(26):
						print([i, encode(text, i)])
				else:
					print("\n\n"+encode(text, k))
				s("pause>nul")
		elif c==2:
			while True:
				s("cls")
				print("������λ��ֵ�����븺���ɷ�������壬����0�����������", end='')
				try:
					k=int(input(""))
					if k<0:
						break
				except:
					print("\a")
					continue
				text=input("������������ַ�����")
				if k==0:
					print("\n\nѭ��ִ�����£�")
					for i in range(26):
						print([i, decode(text, i)])
				else:
					print("\n\n"+decode(text, k))
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