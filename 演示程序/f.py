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
				print("不合法的参数：“" + i + "”。")
			elif result == -2:
				print("计算 f(" + i + ") 时发生算术溢出。")
			else:
				count += 1
				print("f(" + i + ") =", result)
		quit(count)
	from os import system
	system("title 计算层二阶函数&color e")
	while True:
		system("cls")
		print("请输入正整数：")
		i = input("")
		system("cls")
		print("正在尝试执行计算，请稍候。\n如需中止计算，请按下组合键“Ctrl+C”。")
		result = f(i)
		system("cls")
		if result == -1:
			print("不合法的参数：“" + i + "”。")
		elif result == -2:
			print("计算 f(" + i + ") 时发生算术溢出。")
		else:
			print("f(" + i + ") =", result)
		print("\n\n输入“exit”（不区分大小写）回车退出程序，输入其它或直接回车运行新运算。")
		Ens = input("")
		if Ens.lower() == "exit":
			system("cls")
			quit()