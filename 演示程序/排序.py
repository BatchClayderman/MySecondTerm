#coding=gbk
import os
os.system("title ����&color e&cls")
def bubble_sort(ary):#ð������
	n=len(ary)
	for i in range(n):
		for j in range(1, n-i):
			if ary[j-1]>ary[j]:
				ary[j-1], ary[j]=ary[j], ary[j-1]
	return ary
def select_sort(ary):#ѡ������
	n=len(ary)
	for i in range(n):
		min=i
		for j in range(i+1, n):
			if ary[j]<ary[min]:
				min=j
		ary[min], ary[i]=ary[i], ary[min]
	return ary
def insert_sort(ary):#��������
	n=len(ary)
	for i in range(1, n):
		if ary[i]<ary[i-1]:
			temp=ary[i]
			index=i
			for j in range(i-1, -1, -1):
				if ary[j]>temp:
					ary[j+1]=ary[j]
					index=j
				else:
					break
			ary[index]=temp
	return ary
a=[]
i=1
while True:
	os.system("cls")
	print("�������"+str(i)+"����������������ַ��˳�����")
	try:
		temp=float(input(""))
		a.append(temp)
		i+=1
	except:
		break
os.system("cls")
print("ԭ���ݣ�\n"+str(a)+"\n\nð������\n"+str(bubble_sort(a))+"\nѡ������\n"+str(select_sort(a))+"\n��������\n"+str(insert_sort(a))+"\n\n\n�����ϣ��밴������˳���")
os.system("pause>nul&cls")
quit()