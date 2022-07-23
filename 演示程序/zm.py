#coding=gbk
# 取最大公约数
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
# 主函数
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
				print(p1, "^", i, "≡", p1 ** i % p2, "(mod " + str(p2) + ")")
				return i
			else:
				if flag:
					print(p1, "^", i, "≡", p1 ** i % p2, "(mod " + str(p2) + ")")
				i += 1
	except:
		return -2
	return 0
# 定义帮助函数
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a错误：无效的命令行参数—“" + str(option) + "”。")
	print("描述：求模指数。\n\n参数列表：\n\t/true\t\t打印过程\n\t/false\t\t仅打印最终值\n\t[p1]\t\t底数 a 的值（大于 1 的自然数）\n\t[p2]\t\t模 m 的值（大于 1 的自然数）\n")
	print("命令行格式：\n\tzm.py [/true|/false] [p1] [p2]")
	print("示例：\n\tzm.py /true 2 13\n\tzm.py /false 5 13\n")
	print("特别说明：\n\t底数和模数都应该是大于 1 的自然数且两数互素\n")
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
	system("title 求模指数（组合键“Ctrl+C”可中断计算）&color e")
	while True:
		system("cls")
		print("请输入底数 a：")
		p1 = input("")
		print("请输入模数 m：")
		p2 = input("")
		system("cls")
		if gcd(p1, p2) == 1:
			result = _zm(p1, p2, True)
			if result == -2:
				print("提示：您中断了运行。")
			elif result == -1:
				print("\a错误：您的输入非法。")
			elif result == 0:
				print("\a错误：您输入的不是大于 1 的自然数。")
		else:
			print("\a错误：您输入的两数不互素。")
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()