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
		print("\a错误：无效的命令行参数—“"+str(option)+"”。")
	print("描述：单表代换密码加密或解密。\n\n参数列表：\n\tencode\t\t加密\n\tdecode\t\t解密\n\t[strings]\t待加密或解密的密文\n\t[k]\t\t位移值（0为遍历）\n")
	print("命令行格式：\n\t单表代换密码.py encode [strings] [k]\n\t单表代换密码.py decode [strings] [k]\n")
	print("示例：\n\t单表代换密码.py encode \"I love wsy\" 5203344\n\t单表代换密码.py decode \"Y belu mio\" 5203344\n")
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
	s("title 单表代换密码&color e")
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
			while True:
				s("cls")
				print("请输入位移值（输入负数可返回主面板，输入0将会遍历）：", end='')
				try:
					k=int(input(""))
					if k<0:
						break
				except:
					print("\a")
					continue
				text=input("请输入待加密字符串：")
				if k==0:
					print("\n\n循环执行如下：")
					for i in range(26):
						print([i, encode(text, i)])
				else:
					print("\n\n"+encode(text, k))
				s("pause>nul")
		elif c==2:
			while True:
				s("cls")
				print("请输入位移值（输入负数可返回主面板，输入0将会遍历）：", end='')
				try:
					k=int(input(""))
					if k<0:
						break
				except:
					print("\a")
					continue
				text=input("请输入待解密字符串：")
				if k==0:
					print("\n\n循环执行如下：")
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
	print("欢迎再次使用，请按任意键退出本程序。")
	s("pause>nul&cls")
	quit()