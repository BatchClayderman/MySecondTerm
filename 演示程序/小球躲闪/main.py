# -*- coding: utf-8 -*-
import random
from setting import *
from utils import *


class Ball(pygame.sprite.Sprite):
    def __init__(self, *keys):  # 创建球
        super().__init__()
        self.timeSec = 0
        w, h, xs, ys = keys[0]
        self.w = w
        self.h = h
        self.xs = xs
        self.ys = ys
        x = random.randint(0, WIDTH - self.w)
        y = random.randint(0, HEIGHT - self.h)
        self.rect = pygame.Rect(x, y, self.w * 2, self.h * 2)

    def update(self, screen, *args):
        # 根据设置的速度进行运动
        self.rect.x += self.xs
        self.rect.y += self.ys
        # 当遇到墙的时候进行反弹
        if self.rect.x > WIDTH - self.w or self.rect.x < 0:
            self.xs = -self.xs
        elif self.rect.y > HEIGHT - self.h or self.rect.y < 0:
            self.ys = -self.ys
        if self.timeSec <= args[0]:
            pygame.draw.rect(screen, (100, 149, 237), [self.rect.x, self.rect.y, self.rect.w, self.rect.h], 2)
        pygame.draw.circle(screen, (255, 0, 0), [self.rect.center[0], self.rect.center[1]], self.w)

    def timerAdd(self):
        self.timeSec += 1
        return self.timeSec

    def __del__(self):  # 销毁的时候
        pass


class Mouse(pygame.sprite.Sprite):
    def __init__(self, *keys):
        super().__init__()
        self.size = keys[0]  # 设置圆的大小
        self.rect = pygame.Rect(WIDTH / 2 - self.size, HEIGHT / 2 - self.size, self.size * 2, self.size * 2)  # 实则是一个正方形

    def update(self, screen, *args):
        if pygame.mouse.get_focused():  # 如果存在于页面内
            self.rect.center = pygame.mouse.get_pos()
        # 限制球不能半身跑到边框上
        if self.rect.x < 0:
            self.rect.x = 0
        elif self.rect.x > WIDTH - self.rect.w:
            self.rect.x = WIDTH - self.rect.w
        elif self.rect.y < 0:
            self.rect.y = 0
        elif self.rect.y > HEIGHT - self.rect.h:
            self.rect.y = HEIGHT - self.rect.h
        pygame.draw.circle(screen, (255, 0, 0), [self.rect.center[0], self.rect.center[1]], self.size)  # 根据圆心画圆


def main(ladderNum):
    # -------------------画布初始化-----------------------
    screen, background = makeGameBg(WIDTH, HEIGHT)
    clock = pygame.time.Clock()
    comeAgain = ballCome()
    # --------------------------------------------------

    # --------------------对象存储-------------------------
    global TIME, SCORE
    balls = pygame.sprite.Group(Ball(judgeDiff(ladderNum, TIME)))
    mouse = Mouse(howBigBallIs(ladderNum, TIME))
    mouseObject = pygame.sprite.Group(mouse)
    # --------------------------------------------------

    # ---------------------游戏主程序-----------------------
    RUNNING = True
    SHOWINFO = False
    while True:
        draw(screen, SCORE, TIME)  # 动态添加文字
        if SHOWINFO:
            makeTips('Please Press The Space To Restart', 30, (255, 99, 71), (WIDTH / 2 - 240, HEIGHT / 2 - 50),
                     screen)
        for each in balls:
            if pygame.sprite.spritecollide(each, mouseObject, False, collided=None) and each.timeSec > 2:
                RUNNING = False
                SHOWINFO = True
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit(0)
            elif event.type == pygame.KEYDOWN:  # 重新开始
                if event.key == pygame.K_SPACE:
                    SCORE = 0
                    TIME = 0
                    for each in balls.sprites():
                        balls.remove(each)
                    SHOWINFO = False
                    RUNNING = True
            elif event.type == comeAgain and RUNNING:  # 每秒增加
                TIME += 1
                ballsNum = ballNum(ladderNum, TIME)
                diff = judgeDiff(ladderNum, TIME)
                SCORE += (ballsNum * diff[3])
                if TIME in [10, 20]:
                    mouseObject.remove(mouseObject.sprites()[0])
                    mouseObject.add(Mouse(howBigBallIs(ladderNum, TIME)))
                if len(balls) < ballsNum:
                    balls.add(Ball(diff))
                for each in balls:  # 防止误触的保护罩
                    each.timerAdd()
        balls.update(screen, protectTime(ballNum(ladderNum, TIME)))
        mouseObject.update(screen)
        clock.tick(FPS)
        pygame.display.update()  # 刷新
    print('游戏结束')
