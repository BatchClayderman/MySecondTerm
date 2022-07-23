#coding=gbk
def _ESq(p, flag):
	try:
		p = int(p)
		if p % 8 != 5 or p < 0  or p % 5 == 0:
			assert ""
	except:
		return 0, 0
	x = []
	y = []
	m = []
	u = []
	v = []
	i = 0
	if flag:
		print("[i, x, y, m, u, v]")
	try:
		while True:
			if i == 0:
				x.append((2 ** int(((p - 1) / 4))) % p)
				if x[i] * 2 > p:
					x[i] -= p
				y.append(1)
			else:
				x.append(int((u[i - 1] * x[i - 1] + v[i - 1] * y[i - 1]) / m[i - 1]))
				y.append(int((u[i - 1] * y[i - 1] - v[i - 1] * x[i - 1]) / m[i - 1]))
			m.append(int((x[i] ** 2 + y[i] ** 2) / p))
			u.append(x[i] % m[i])
			if abs(u[i] * 2) > abs(m[i]):
				u[i] -= m[i]
			v.append(y[i] % m[i])
			if abs(v[i] * 2) > abs(m[i]):
				v[i] -= m[i]
			if flag:
				print([i, x[i], y[i], m[i], u[i], v[i]])
			if m[i] == 1:
				break
			i += 1
	except:
		return -1, -1
	return abs(x[i]), abs(y[i])
def help(option):
	print("")
	if option!="/?" and option!="-?":
		print("\a错误：无效的命令行参数—“"+str(option)+"”。")
	print("描述：求 x 和 y 使其平方和为 p。\n\n参数列表：\n\t/true\t\t显示过程\n\t/false\t\t不显示过程\n\t[p]\t\tp\n")
	print("命令行格式：\n\tESqP.py [/true|/false] p1 p2 p3 ...\n")
	print("示例：\n\tESqP.py /true 100069\n")
	if option!="/?" and option!="-?":
		return 0
	else:
		return -1
if __name__ == "__main__":
	from sys import argv
	if len(argv) == 2:
		quit(help(argv[1]))
	if len(argv) > 2:
		if argv[1].lower() == "/true" or argv[1].lower() == "/false":
			count = 1
			if argv[1].lower() == "/true":
				for p in argv[2:]:
					x, y = _ESq(p, True)
					if (x != 0 or y != 0) and (x != -1 or y != -1):
						count += 1
						print("")
						print([p, "result", "±" + str(x), "±" + str(y)])
					else:
						print([p, "error"])
					print("\n")
			else:
				for p in argv[2:]:
					x, y = _ESq(p, False)
					if (x != 0 or y != 0) and (x != -1 or y != -1):
						count += 1
						print([p, "result", "±" + str(x), "±" + str(y)])
					else:
						print([p, "error"])
			quit(count)
		else:
			quit(help(argv[1]))
	from os import system
	system("title 求 x 和 y 使其平方和为 p&color e")
	while True:
		system("cls")
		print("请输入p：", end = '')
		p = input("")
		system("cls")
		x, y = _ESq(p, True)
		print("计算完毕，| x | =", x, "，| y | =", y, "。")
		if x == 0 and y == 0:
			system("cls")
			print("\a错误：输入的不是模 8 余 5 的正素数。")
		elif x == -1 and y == -1:
			system("cls")
			print("\a错误：算术溢出，或不存在 x 和 y 使得等式成立。")
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens=input("")
		if Ens.lower()=="exit":
			system("cls")
			quit()