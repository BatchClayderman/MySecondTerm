#coding=gbk
import os
from turtle import *
import random
os.system("title 圣诞老人祝您圣诞节快乐！Merry Christmas!&cls&mshta vbscript:msgbox(\"亲爱的主人，您好，下面请允许我为您绘制一棵精致的圣诞树。\",64,\"圣诞节快乐，天天快乐哟！\")(window.close)")
title("May this festive season sparkle and shine, may all of your wishes and dreams come true!")
bgcolor("black")
n=100.0
speed("fastest")
left(90)
forward(3*n)
color("orange", "yellow")
begin_fill()
left(126)
for i in range(5):
	forward(n/5)
	right(144)
	forward(n/5)
	left(72)
end_fill()
right(126)
color("green")
backward(n*4.8)
def tree(d, s):
	if d<=0:
		return
	forward(s)
	tree(d-1, s*.8)
	right(120)
	tree(d-3, s*.5)
	right(120)
	tree(d-3, s*.5)
	right(120)
	backward(s)
tree(15, n)
backward(n/2)
for i in range(200):
	a=200-400*random.random()
	b=10-20*random.random()
	up()
	forward(b)
	left(90)
	forward(a)
	down()
	if random.randint(0,1)==0:
		color('tomato')
	else:
		color('wheat')
	circle(2)
	up()
	backward(a)
	right(90)
	backward(b)
done()