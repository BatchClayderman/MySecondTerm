import sys

from main import main

banner = """ ____        _ _ _____          
| __ )  __ _| | | ____|___  ___ 
|  _ \ / _` | | |  _| / __|/ __|
| |_) | (_| | | | |___\__ \ (__ 
|____/ \__,_|_|_|_____|___/\___|
"""

if __name__ == '__main__':
    print(banner)
    print("Author: HengYi")
    print("[*] 简单：输入 1")
    print("[*] 普通：输入 2")
    print("[*] 困难：输入 3")
    try:
        num = int(input("请选择难度："))
        if num in [1, 2, 3]:
            main(num)
        else:
            print("无法处理～")
            sys.exit()
    except Exception as e:
        raise Exception("无法处理～")
