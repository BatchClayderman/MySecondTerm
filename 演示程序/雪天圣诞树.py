#coding=gbk
import os
from turtle import *
from random import random, randint
os.system("title ʥ������ף��ʥ���ڿ��֣�Merry Christmas!&cls&mshta vbscript:msgbox(\"�װ������ˣ���������Ϊ������һ��ʥ������\",64,\"ʥ���ڿ��֣�Ҫ�������Ӵ��\")(window.close)")
title("May this festive season sparkle and shine, may all of your wishes and dreams come true!")
bgcolor("mistyrose")
n = 100.0
delay(0)
tracer(0)
Turtle().screen.delay(0)
speed("fastest")
left(90)
forward(3 * n)
color("orange", "gold")
begin_fill()
left(126)
for i in range(5):
	forward(n / 5)
	right(144)
	forward(n / 5)
	left(72)
end_fill()
right(126)
color("green")
backward(n * 4.8)
def tree(d, s):
	if d <= 0:
		return
	forward(s)
	tree(d - 1, s * 0.8)
	right(120)
	tree(d - 3, s * 0.5)
	right(120)
	tree(d - 3, s * 0.5)
	right(120)
	backward(s)
tree(15, n)
backward(n / 2)
for i in range(200):
	a = 200 - 400 * random()
	b = 10 - 20 * random()
	up()
	forward(b)
	left(90)
	forward(a)
	down()
	if randint(0,1) == 0:
		color("white")
	else:
		color("honeydew")
	circle(2)
	up()
	backward(a)
	right(90)
	backward(b)



def drawsnow():
	ht()  #���ر�ͷ��ht=hideturtle
	pensize(2)  #�����ͷ��С
	for i in range(200): #������ѩ��
		pencolor("white") #���廭����ɫΪ��ɫ����ʵ����ѩ��Ϊ��ɫ
		pu() #���
		setx(randint(-350, 350)) #����x���꣬�����-350��350֮��ѡ��
		sety(randint(-100, 350)) #����y���꣬ע��ѩ��һ���ڵ��ϲ������£����Բ����̫С�������Ὺʼ
		pd() #���
		dens = 6 #ѩ��������Ϊ6
		snowsize = randint(1,10) #����ѩ����С
		for j in range(dens): #����6���Ǿ��ǻ�5�Σ�Ҳ����һ��ѩ�������
			#forward(int(snowsize))  #int����ȡ����
			fd(int(snowsize))
			backward(int(snowsize))
			#bd(int(snowsize))  #ע��û��bd=backward������fd=forward��Сbug
			right(int(360/dens))  #ת���Ƕ�
 
drawsnow()
done()