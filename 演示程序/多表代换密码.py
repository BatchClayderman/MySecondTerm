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
	print("\n处理后的字符串：\n"+text1+"\n"+text2+"\n\n处理后的运算结果：")
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
	print("\n处理后的字符串：\n"+text1+"\n"+text2+"\n\n处理后的运算结果：")
	for i in range(max(len(text1), len(text2))):
		r+=Alpha[(Alpha.find(text1[i%len(text1)])-Alpha.find(text2[i%len(text2)]))%26]
	return r
def help(option):
	print("")
	if option!="/?" and option!="-?":
		print("\a错误：无效的命令行参数—“"+str(option)+"”。")
	print("描述：多表代换密码加密或解密。\n\n参数列表：\n\t[strings1]\t第一个字符串\n\t[+/-]\t\t运算符\n\t[strings2]\t第二个字符串\n")
	print("命令行格式：\n\t多表代换密码.py [strings1] [+/-] [strings2]\n")
	print("示例：\n\t多表代换密码.py \"I love you for ever\" + \"you love me\"\n\t多表代换密码.py jmpwfxtzgpsfwfs - b\n")
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
	s("title 多表代换密码&color e")
	while True:
		s("cls")
		print("1 = 加密\t2 = 解密\t0 = 退出程序\n请选择一项以继续：")
		try:
			c=int(input(""))
		except:
			print("\a")
			continue
		s("cls")
		if c==1:
			s("cls")
			print("请输入第一个字符串：", end='')
			n1=input("")
			print("请输入第二个字符串：", end='')
			n2=input("")
			result=doubleencode(n1, n2)
			if result=="":
				print("\n\a明文或密钥不含字母，请按任意键返回。")
			else:
				print(result+"\n"+result.upper()+"\n\n请按任意键返回。")
			s("pause>nul")
		elif c==2:
			s("cls")
			print("请输入第一个字符串：", end='')
			n1=input("")
			print("请输入第二个字符串：", end='')
			n2=input("")
			result=doubledecode(n1, n2)
			if result=="":
				print("\n\a明文或密钥不含字母，请按任意键返回。")
			else:
				print(result+"\n"+result.upper()+"\n\n\n请按任意键返回。")
			s("pause>nul")
		elif c==0:
			break
		else:
			print("\a")
			continue
	s("cls")
	print("欢迎再次使用，请按任意键退出本程序。")
	s("pause>nul&cls")
	quit()