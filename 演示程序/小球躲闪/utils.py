# -*- coding: utf-8 -*-
import pygame
from setting import FIRST_STEP, SECOND_STEP, BG_COLOR, WIDTH, HEIGHT


# Note: 根据难度生成对应的小球
# Time: 2021/12/17 8:35 下午
# Author: HengYi
def ballNum(ladderNum, time):
    index = 0
    if FIRST_STEP <= time < SECOND_STEP:
        index = 1
    if SECOND_STEP <= time:
        index = 2
    numMap = [
        [2, 3, 5],
        [3, 5, 6],
        [4, 6, 7]
    ]
    return numMap[ladderNum - 1][index]


# Note: 根据小球个数设置防止误触时间
# Time: 2021/12/17 8:43 下午
# Author: HengYi
def protectTime(ballsNum):
    if ballsNum in [2, 3, 4]:
        return 1
    else:
        return 2


# Note: 根据时间设置小球大小
# Time: 2021/12/17 8:58 下午
# Author: HengYi
def howBigBallIs(ladderNum, time):
    index = 0
    if FIRST_STEP <= time < SECOND_STEP:
        index = 1
    if SECOND_STEP <= time:
        index = 2
    numMap = [
        [25, 20, 15],
        [24, 20, 16],
        [26, 20, 16]
    ]
    return numMap[ladderNum - 1][index]


# Note: 根据时间难度计算球体的大小和速度
# Time: 2021/12/17 9:15 下午
# Author: HengYi
def judgeDiff(ladderNum, time):
    index = 0
    if FIRST_STEP <= time < SECOND_STEP:
        index = 1
    if SECOND_STEP <= time:
        index = 2
    numMap = [
        [(30, 30, 3.5, 3.5), (28, 28, 6, 6), (26, 26, 9, 9)],
        [(30, 30, 4.5, 4.5), (27, 27, 8, 8), (25, 25, 10, 10)],
        [(30, 30, 5, 5), (26, 26, 9, 9), (24, 24, 12, 12)]
    ]
    return numMap[ladderNum - 1][index]


# Note: 创建平台窗口
# Time: 2021/12/17 2:58 下午
# Author: HengYi
def makeGameBg(width, height):
    pygame.init()
    screen = pygame.display.set_mode((width, height))  # 设置窗口大小
    pygame.display.set_caption('小球逃逃逃')  # 设置窗口标题
    background = pygame.Surface(screen.get_size())  # 填充背景
    return screen, background


# Note: 添加小球产生的事件
# Time: 2021/12/17 3:06 下午
# Author: HengYi
def ballCome():
    COME_AGAIN = pygame.USEREVENT
    pygame.time.set_timer(COME_AGAIN, 1000)
    return COME_AGAIN


# Note: 提示字体
# Time: 2021/12/17 3:11 下午
# Author: HengYi
def makeTips(content, size, color, position, screen):
    font = pygame.font.SysFont('arial', size)
    text_sf = font.render(content, True, color, BG_COLOR)
    screen.blit(text_sf, position)


# Note: 字体展示
# Time: 2021/12/18 4:20 下午
# Author: HengYi
def draw(screen, SCORE, TIME):
    screen.fill(BG_COLOR)  # 防止出现拖影
    makeTips('SCORE: ', 30, (34, 139, 34), (5, 40), screen)
    makeTips('TIME(s): ', 30, (64, 158, 255), (5, 75), screen)
    makeTips(str(int(SCORE)), 30, (34, 139, 34), (135, 40), screen)
    makeTips(str(int(TIME)), 30, (64, 158, 255), (135, 75), screen)
    if TIME in [FIRST_STEP, FIRST_STEP + 1]:
        makeTips('Ops! LEVEL_2~', 30, (60, 179, 113), (WIDTH / 2 - 30 * 3.5, HEIGHT / 2 - 50), screen)
    elif TIME in [SECOND_STEP, SECOND_STEP + 1]:
        makeTips('Congratulations! LEVEL_3', 25, (60, 179, 113), (WIDTH / 2 - 25 * 6.25, HEIGHT / 2 - 50), screen)
