#coding=gbk
import os
from turtle import *
from random import random, randint
os.system("title 圣诞老人祝您圣诞节快乐！Merry Christmas!&cls&mshta vbscript:msgbox(\"亲爱的主人，请允许我为您绘制一棵圣诞树。\",64,\"圣诞节快乐，要天天快乐哟！\")(window.close)")
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
	ht()  #隐藏笔头，ht=hideturtle
	pensize(2)  #定义笔头大小
	for i in range(200): #画多少雪花
		pencolor("white") #定义画笔颜色为白色，其实就是雪花为白色
		pu() #提笔
		setx(randint(-350, 350)) #定义x坐标，随机从-350到350之间选择
		sety(randint(-100, 350)) #定义y坐标，注意雪花一般在地上不会落下，所以不会从太小的纵座轴开始
		pd() #落笔
		dens = 6 #雪花瓣数设为6
		snowsize = randint(1,10) #定义雪花大小
		for j in range(dens): #就是6，那就是画5次，也就是一个雪花五角星
			#forward(int(snowsize))  #int（）取整数
			fd(int(snowsize))
			backward(int(snowsize))
			#bd(int(snowsize))  #注意没有bd=backward，但有fd=forward，小bug
			right(int(360/dens))  #转动角度
 
drawsnow()
done()