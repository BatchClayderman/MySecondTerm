#coding=gbk
import os
os.system("title 排序&color e&cls")
def bubble_sort(ary):#冒泡排序
	n=len(ary)
	for i in range(n):
		for j in range(1, n-i):
			if ary[j-1]>ary[j]:
				ary[j-1], ary[j]=ary[j], ary[j-1]
	return ary
def select_sort(ary):#选择排序
	n=len(ary)
	for i in range(n):
		min=i
		for j in range(i+1, n):
			if ary[j]<ary[min]:
				min=j
		ary[min], ary[i]=ary[i], ary[min]
	return ary
def insert_sort(ary):#插入排序
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
	print("请输入第"+str(i)+"个数（输入非数字字符退出）：")
	try:
		temp=float(input(""))
		a.append(temp)
		i+=1
	except:
		break
os.system("cls")
print("原数据：\n"+str(a)+"\n\n冒泡排序：\n"+str(bubble_sort(a))+"\n选择排序：\n"+str(select_sort(a))+"\n插入排序：\n"+str(insert_sort(a))+"\n\n\n输出完毕，请按任意键退出。")
os.system("pause>nul&cls")
quit()