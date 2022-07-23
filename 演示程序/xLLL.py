#coding=gbk
from fractions import Fraction
from typing import Iterator, List, Sequence
class Vector(list):
	def __init__(self, x):
		super().__init__(map(Fraction, x))
	def sdot(self) -> Fraction:
		return self.dot(self)
	def dot(self, rhs: "Vector") -> Fraction:
		rhs = Vector(rhs)
		assert len(self) == len(rhs)
		return sum(map(lambda x: x[0] * x[1], zip(self, rhs)))
	def proj_coff(self, rhs: "Vector") -> Fraction:
		rhs = Vector(rhs)
		assert len(self) == len(rhs)
		return self.dot(rhs) / self.sdot()
	def proj(self, rhs: "Vector") -> "Vector":
		rhs = Vector(rhs)
		assert len(self) == len(rhs)
		return self.proj_coff(rhs) * self
	def __sub__(self, rhs: "Vector") -> "Vector":
		rhs = Vector(rhs)
		assert len(self) == len(rhs)
		return Vector(x - y for x, y in zip(self, rhs))
	def __mul__(self, rhs: Fraction) -> "Vector":
		return Vector(x * rhs for x in self)
	def __rmul__(self, lhs: Fraction) -> "Vector":
		return Vector(x * lhs for x in self)
	def __repr__(self) -> str:
		return "[{}]".format(", ".join(str(x) for x in self))
def gramschmidt(v: Sequence[Vector]) -> Sequence[Vector]:
	u: List[Vector] = []
	for vi in v:
		ui = Vector(vi)
		for uj in u:
			ui -= uj.proj(vi)
		if any(ui):
			u.append(ui)
	return u
def reduction(basis: Sequence[Sequence[int]], delta: float) -> Sequence[Sequence[int]]:
	n = len(basis)
	basis = list(map(Vector, basis))
	ortho = gramschmidt(basis)
	def mu(i: int, j: int) -> Fraction:
		return ortho[j].proj_coff(basis[i])
	k = 1
	while k < n:
		for j in range(k - 1, -1, -1):
			mu_kj = mu(k, j)
			if abs(mu_kj) > 0.5:
				basis[k] = basis[k] - basis[j] * round(mu_kj)
				ortho = gramschmidt(basis)
		if ortho[k].sdot() >= (delta - mu(k, k - 1) ** 2) * ortho[k - 1].sdot():
			k += 1
		else:
			basis[k], basis[k - 1] = basis[k - 1], basis[k]
			ortho = gramschmidt(basis)
			k = max(k - 1, 1)
	return [list(map(int, b)) for b in basis]
def deal(ori):
	sq = int(len(ori) ** 0.5)
	if len(ori) ** 0.5 == sq:
		tmp = []
		for i in range(sq):
			tmp.append([])
		for i in range(len(ori)):
			tmp[i // sq].append(ori[i])
		return tmp
	else:
		return []
def prVector(V):
	for i in V:
		m = 0
		for j in i:
			print("\t", j, end = '')
			m += j ** 2
		print("\t\t\t", m)
def help(option):
	print("")
	if option!="/?" and option!="-?":
		print(option)
	print("������LLL ��Լ���㷨��\n\n�����б�\n\t[delta]\t\tdelta ֵ\n\t[int]\t\t������������\n")
	print("�����и�ʽ��\n\txLLL.py [delta] [int 1] [int 2] [int 3] ...\n")
	print("ʾ����\n\txLLL.py 1 11 17 29 21 17 19 71 37 -8\n")
	print("ע�����\n\tdelta ��ֵ������� 0.25 �� 1 ֮��\n\tint ������Ŀ��������ȫƽ����\n\t������ϼ���Ctrl + C������ֹ����\n")
if __name__ == "__main__":
	from os import system
	from sys import argv
	if "/?" in argv or "-?" in argv:
		help("-?")
		quit(0)
	if len(argv) != 1:
		if (len(argv) - 2) ** 0.5 == int((len(argv) - 2) ** 0.5):
			try:
				_argv = []
				_argv.append(float(argv[1]))
				if _argv[0] > 1 or _argv[0] < 0.25:
					assert ""
			except:
				help("\a����delta ֵӦ���� 0.25 �� 1 ֮�䡣")
				quit(-1)
			try:
				for i in argv[2:]:
					_argv.append(int(i))
			except:
				help("\a���󣺲�������ȷ��")
				quit(-1)
			try:
				print("\n���뷽��", int((len(argv) - 2) ** 0.5), "ά����")
				prVector(deal(_argv[1:]))
				print("\n������� delta =", _argv[0], "����")
				prVector(reduction(deal(_argv[1:]), _argv[0]))
				print("")
			except:
				print("\a������������г��ִ���\n")
				quit(1)
			quit(0)
		else:
			help("\a���󣺴���ľ����Ƿ���")
			quit(-1)
	system("title LLL ��Լ���㷨&color e")
	while True:
		system("cls")
		print("������ delta���� 0.25 �� 1 ֮�䣩��")
		while True:
			try:
				delta = float(input(""))
				if delta < 0.25 or delta > 1:
					assert ""
				break
			except:
				print("\adelta ��ֵӦ���� 0.25 �� 1 ֮�䣬���������룺")
		print("\n�����뷽�����롰#���س���������")
		ordinary = []
		while True:
			a = input("")
			if a == "#":
				break
			try:
				ordinary.append(int(a))
			except:
				print("\a����������Ĳ������������������������")
		#ordinary = [[11, 17, 29], [21, 17, 19], [71, 37, -8]]
		#result = [[-11, 3 -6], [10, 0, -10], [-1, 23, 7]]
		system("cls")
		if len(ordinary) ** 0.5 == int(len(ordinary) ** 0.5):
			try:
				print("���뷽��", int(len(ordinary) ** 0.5), "ά����")
				prVector(deal(ordinary))
				print("\n������� delta =", delta, "����")
				prVector(reduction(deal(ordinary), delta))
			except:
				system("cls")
				print("���뷽��", int(len(ordinary) ** 0.5), "ά����")
				prVector(deal(ordinary))
				print("\n\a������������г��ִ���")
		else:
			print("\a��������Ĳ��Ƿ���")
		print("\n\n���롰exit���������ִ�Сд���س��˳���������������ֱ�ӻس����������㡣")
		Ens=input("")
		if Ens.lower()=="exit":
			system("cls")
			quit()