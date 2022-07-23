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
					print("a0 = [", p1, "/", p2, "] =", a[0], "，x0", "= x - a0 =", xp[i], "/", xq[i])
			else:
				if xp[i] == 0:
					if flag:
						print("a" + str(i), "= [", p1, "/", p2, "] =", a[i], "，x" + str(i), "= 1 / x" + str(i - 1), "- a" + str(i), "= 0")
					return a
				else:
					if flag:
						print("a" + str(i), "= [", p1, "/", p2, "] =", a[i], "，x" + str(i), "= 1 / x" + str(i - 1), "- a" + str(i), "=", xp[i], "/", xq[i])
			p1 = xq[i]
			p2 = xp[i]
			i += 1
	except:
		return ["break"]
	return 0
# 定义帮助函数
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a错误：无效的命令行参数—“" + str(option) + "”。")
	print("描述：求连分数。\n\n参数列表：\n\t/true\t\t打印过程\n\t/false\t\t仅打印最终值\n\t[p1]\t\t分子\n\t[p2]\t\t分母\n")
	print("命令行格式：\n\tlfs.py [/true|/false] [p1] [p2]")
	print("示例：\n\tlfs.py /true 7700 2145\n\tlfs.py /false -97 73\n\tlfs.py /true 5391 3976\n")
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
			print("\a错误：分母不能为 0。")
		elif result == ["break"]:
			print("\n提示：您中止了运算。\n")
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
	system("title 求连分数（组合键“Ctrl+C”可中断计算）&color e")
	while True:
		system("cls")
		try:
			print("请输入分子：", end = '')
			p1 = input("")
			print("请输入分母：", end = '')
			p2 = input("")
		except:
			system("cls")
			break
		system("cls")
		result = lfs(p1, p2, True)
		if result == []:
			print("\a您的输入有误，无法运行计算。")
		elif result == ["NULL"]:
			print("\a错误：分母不能为 0。")
		elif result == ["break"]:
			print("\n提示：您中止了运算。")
		else:
			print("\n计算完毕，x = [", p1, "/", p2, "]的连分数形式如下：")
			print(result, end = "\t")
			result[len(result) - 1] -= 1
			result.append(1)
			print(result)
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()