#coding=gbk
if __name__ == "__main__":
	from os import system
	from sys import argv
	if len(argv) == 3:
		try:
			p1 = int(argv[1])
			p2 = int(argv[2])
			print(p1, "÷", p2, "=", p1 // p2, "……", p1 % p2)
		except:
			print("\a错误：所输入的参数不合法。")
			quit(-1)
		quit(0)
	elif len(argv) != 1:
		print("\a错误：命令行参数数目不正确。")
		quit(-1)
	system("title 求余数&color e")
	while True:
		system("cls")
		try:
			print("请输入p1：", end = "")
			p1 = int(input(""))
			print("请输入p2：", end = "")
			p2 = int(input(""))
		except:
			continue
		print(p1, "÷", p2, "=", p1 // p2, "……", p1 % p2)
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens=input("")
		if Ens.lower()=="exit":
			system("cls")
			quit()