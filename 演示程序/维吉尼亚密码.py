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
	print("\n处理后的字符串：\n" + text1 + "\n" + text2 + "\n\n处理后的运算结果：")
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
	print("\n处理后的字符串：\n" + text1 + "\n" + text2 + "\n\n处理后的运算结果：")
	for i in range(max(len(text1), len(text2))):
		r += Alpha[(Alpha.find(text1[i % len(text1)]) - Num.find(text2[i % len(text2)])) % 26]
	return r
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a错误：无效的命令行参数—“" + str(option) + "”。")
	print("描述：维吉尼亚密码加密或解密。\n\n参数列表：\n\t[Strings]\t英文字符串\n\t[ + /-]\t\t运算符\n\t[Numbers]\t数字字符串\n")
	print("命令行格式：\n\t维吉尼亚密码.py [Strings] [ + /-] [Numbers]\n")
	print("示例：\n\t维吉尼亚密码.py \"I love you for ever\" + 5203344\n\t维吉尼亚密码.py jmpwfzpvgpsfwfs - 1\n")
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
				print("\a明文不含字母或密钥不含数字。")
			print(result)
			print(result.upper())
			print("")
		elif argv[2] == "-":
			result = Vdecode(argv[1], argv[3])
			if result == "":
				print("\a密文不含字母或密钥不含数字。")
			print(result)
			print(result.upper())
			print("")
		else:
			exit(help(argv[2]))
		exit(0)
	elif len(argv) != 1:
		exit(help(argv[1:]))
	s("title 维吉尼亚密码&color e")
	while True:
		s("cls")
		print("1  =  加密\t2  =  解密\t0  =  退出程序\n请选择一项以继续：")
		try:
			c = int(input(""))
		except:
			print("\a")
			continue
		s("cls")
		if c == 1:
			s("cls")
			print("请输入明文：", end = '')
			n1 = input("")
			print("请输入数字字符串：", end = '')
			n2 = input("")
			result = Vencode(n1, n2)
			if result == "":
				print("\n\a明文不含字母或密钥不含数字，请按任意键返回。")
			else:
				print(result + "\n" + result.upper() + "\n\n\n请按任意键返回。")
			s("pause>nul")
		elif c == 2:
			s("cls")
			print("请输入密文：", end = '')
			n1 = input("")
			print("请输入数字字符串：", end = '')
			n2 = input("")
			result = Vdecode(n1, n2)
			if result == "":
				print("\n\a密文不含字母或密钥不含数字，请按任意键返回。")
			else:
				print(result + "\n" + result.upper() + "\n\n\n请按任意键返回。")
			s("pause>nul")
		elif c == 0:
			break
		else:
			print("\a")
			continue
	s("cls")
	print("欢迎再次使用，请按任意键退出本程序。")
	s("pause>nul&cls")
	exit(0)