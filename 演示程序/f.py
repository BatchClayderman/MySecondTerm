#coding=gbk
def f(x):
	try:
		n = int(x)
		if n < 1:
			assert ""
	except:
		return -1
	try:
		y = n ** n
		for i in range(n - 2):
			y = n ** y
		return y
	except:
		return -2
if __name__ == "__main__":
	from sys import argv
	if len(argv) != 1:
		count = 0
		for i in argv[1:]:
			result = f(i)
			if result == -1:
				print("���Ϸ��Ĳ�������" + i + "����")
			elif result == -2:
				print("���� f(" + i + ") ʱ�������������")
			else:
				count += 1
				print("f(" + i + ") =", result)
		quit(count)
	from os import system
	system("title �������׺���&color e")
	while True:
		system("cls")
		print("��������������")
		i = input("")
		system("cls")
		print("���ڳ���ִ�м��㣬���Ժ�\n������ֹ���㣬�밴����ϼ���Ctrl+C����")
		result = f(i)
		system("cls")
		if result == -1:
			print("���Ϸ��Ĳ�������" + i + "����")
		elif result == -2:
			print("���� f(" + i + ") ʱ�������������")
		else:
			print("f(" + i + ") =", result)
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()