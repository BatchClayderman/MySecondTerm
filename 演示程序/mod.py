#coding=gbk
if __name__ == "__main__":
	from os import system
	from sys import argv
	if len(argv) == 3:
		try:
			p1 = int(argv[1])
			p2 = int(argv[2])
			print(p1, "��", p2, "=", p1 // p2, "����", p1 % p2)
		except:
			print("\a����������Ĳ������Ϸ���")
			quit(-1)
		quit(0)
	elif len(argv) != 1:
		print("\a���������в�����Ŀ����ȷ��")
		quit(-1)
	system("title ������&color e")
	while True:
		system("cls")
		try:
			print("������p1��", end = "")
			p1 = int(input(""))
			print("������p2��", end = "")
			p2 = int(input(""))
		except:
			continue
		print(p1, "��", p2, "=", p1 // p2, "����", p1 % p2)
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens=input("")
		if Ens.lower()=="exit":
			system("cls")
			quit()