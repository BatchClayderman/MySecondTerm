#coding=gbk
import os
from sys import argv

# ����⴦����
def fixlib(cb, command):
	print("δ����ȷ����װ"+cb+"�⣬���ڳ���ִ�а�װ����ȷ��������������������")
	os.system("py -m pip install "+cb)
	try:
		exec(command)
	except:
		os.system("cls")
		if os.popen("ver").read().upper().find("XP")==-1:
			print("��װ"+cb+"��ʧ�ܣ����ڳ����Թ���ԱȨ��ִ�а�װ����ȷ��������������������")
			os.system("mshta vbscript:createobject(\"shell.application\").shellexecute(\"py\",\"-m pip install "+cb+"\",\"\",\"runas\",\"1\")(window.close)")
			print("�ѵ����´��ڣ�ȷ����Ȩ����װ��ɺ��밴�����������")
			os.system("pause>nul")
			try:
				exec(command)
			except:
				print("�޷���ȷ��װ"+cb+"�⣬�밴������˳��������Ժ���������������")
				os.system("pause>nul&cls")
				exit()
		else:
			print("�޷���ȷ��װ"+cb+"�⣬�밴������˳��������Ժ���������������")

# �����㷨����
def egcd(a, b):
	if a==0:
		return b, 0, 1
	else:
		g, y, x = egcd(b % a, a)
		return g, x - (b // a) * y, y
def modinv(a, m):
	g, x, y = egcd(a, m)
	if g != 1:
		return -1
	else:
		return x % m
def ne(n, e):
	f = FactorDB(n)
	f.connect()
	result = f.get_factor_list()
	if len(result)!=2:
		return -1
	# print(result)
	p, q = result[0], result[1]
	print("p =", p)
	# p = 14001864863580621636769
	print("q =", q)
	# q = 14901278358136141983377
	d = modinv(e, (p-1)*(q-1))
	return d

# �����������
def help(option):
	print("")
	if option != "/?" and option != "-?":
		print("\a������Ч�������в�������"+str(option)+"����")
	print("����������n��e��RSA�������㡣\n\n�����б�\n\t/n\t\t����n��ֵ\n\t/e\t\t����e��ֵ\n\t[n]\t\tn��ֵ\n\t[e]\t\te��ֵ\n")
	print("�����и�ʽ��\n\tenRSA.py /n [n] /e [e]\n")
	print("ʾ����\n\tenRSA.py /n 208645685865220781237677030108874331729988913 /e 10111111111\n")
	if option == "/?" or option == "-?":
		return 0
	else:
		return -1

# ���������в���
if "/?" in argv or "-?" in argv:
	exit(help("/?"))
if len(argv) == 5:
	if argv[1].lower() == "/n" or argv[1].lower() == "-n":
		try:
			n = int(argv[2])
			if n < 4:
				assert ""
		except:
			print("\a�����ṩ�� n ֵ����ȷ��\n")
			exit(-1)
	elif argv[1].lower() == "/e" or argv[1].lower() == "-e":
		try:
			e = int(argv[2])
			if e < 1:
				assert ""
		except:
			print("\a�����ṩ�� e ֵ����ȷ��\n")
			exit(-1)
	if argv[3].lower() == "/n" or argv[3].lower() == "-n":
		try:
			n = int(argv[4])
			if n < 4:
				assert ""
		except:
			print("\a�����ṩ�� n ֵ����ȷ��\n")
			exit(-1)
	elif argv[3].lower() == "/e" or argv[3].lower() == "-e":
		try:
			e = int(argv[4])
			if e < 1:
				assert ""
		except:
			print("\a�����ṩ�� e ֵ����ȷ��\n")
			exit(-1)
	try:
		print("n =", n)
	except:
		print("\a����δ���� n��")
		exit(-1)
	try:
		print("e =", e)
	except:
		print("\a����δ���� e��")
		exit(-1)
	try:
		from factordb.factordb import FactorDB
	except:
		fixlib("factordb-pycli", "from factordb.factordb import FactorDB")
		from factordb.factordb import FactorDB
	d = int(ne(n, e))
	if d == -1:
		print("\a���������n��eֵ��Ч������Կ�������Եġ�")
		exit(-1)
	else:
		print("d =", d, "\n")
		exit(0)
elif len(argv) != 1:
	exit(help(argv[1:]))

# ������
os.system("title ����n��e��RSA��������&color e&cls")
try:
	from factordb.factordb import FactorDB
except:
	fixlib("factordb-pycli", "from factordb.factordb import FactorDB")
	from factordb.factordb import FactorDB
while True:
	os.system("cls")
	while True:
		try:
			os.system("cls")
			print("������n��")
			n = int(input(""))
			if n < 4:
				assert ""
			break
		except:
			os.system("cls")
			print("\a�����n���Ϸ����밴������������롣")
			os.system("pause>nul")
	while True:
		try:
			os.system("cls")
			print("������e��")
			e = int(input(""))
			if e < 1:
				assert ""
			break
		except:
			os.system("cls")
			print("\a�����e���Ϸ����밴������������롣")
			os.system("pause>nul")
	os.system("cls")
	print("n =", n)
	print("e =", e)
	# n = 208645685865220781237677030108874331729988913
	# e = 10111111111
	try:
		d = int(ne(n, e))
		# d = 197944482226238981644771241465020009358173687
		if d == -1:
			print("\a���������n��eֵ��Ч������Կ�������Եġ�")
		else:
			print("d =", d)
	except:
		print("\a������������ʧ�ܣ��޷���ȡ������Դ��")
	print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
	Ens = input("")
	if Ens.lower() == "exit":
		os.system("cls")
		quit()