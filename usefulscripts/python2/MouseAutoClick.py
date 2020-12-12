# coding: utf-8
# Auther: Pentakilj
# Time: 2020-11-23

import time
import pyautogui as pag
try:
    import tkinter as tk
    from tkinter import ttk
except:
    import Tkinter as tk
    import ttk

# todo:中建有点问题
class MouseAutoClickGUI(object):
    # 异常保护，左上角退出
    pag.FAILSAFE = True

    def __init__(self):
        self.root = tk.Tk()
        self.root.title("MouseAutoClick-GUI")
        # todo: 不同frame配置，GUI面板
        self.frameL1 = tk.Frame(self.root)
        self.frameL1.pack({"side": "bottom"})
        self.frameL2 = tk.Frame(self.root)
        self.frameL2.pack({"side": "top"})
        self.PositionList = []
        self.ClickNumList = []
        self.MouseKeyList = []
        # loop control flag
        self.isStartGetPos = True
        self.notClick = False
        # UI response pause time
        self.UI_Response_MS = 1
        self._init_basic_click_gui()
        self._init_basic_mouse_pos_gui()
        self._init_basic_keyboard_gui()
        self.root.mainloop()
    def _init_basic_click_gui(self):
        # root gui rows count
        self.RowNums = 1
        # name row 0, display only
        self.PositionLabel = tk.Label(self.frameL2, text="鼠标位置")
        self.ClickNumLabel = tk.Label(self.frameL2, text="点击次数")
        self.MouseKeyLabel = tk.Label(self.frameL2, text="点击按键")
        self.PositionLabel.grid(row=0, column=0)
        self.ClickNumLabel.grid(row=0, column=1)
        self.MouseKeyLabel.grid(row=0, column=2)
        self.RepeatNumsLabel = tk.Label(self.frameL2, text="总重复次数")
        self.RepeatNumsLabel.grid(row=1, column=3)
        # input var bind with entry
        self.RepeatNums = tk.StringVar()
        # accept input from entry: input var bind with entry
        self.RepeatEntry = tk.Entry(self.frameL2, show=None, textvariable=self.RepeatNums)
        self.RepeatEntry.grid(row=1, column=4)
        self.RepeatNums.set("1")
        # show button and bind command
        self.AddButton = tk.Button(self.frameL2, text="添加新点击", command=self.AddFrame)
        self.AddButton.grid(row=0, column=3)
        # add the second rows, for pos, mouse key, click nums' input var
        self.AddFrame()
        # show button and bind command
        self.StartButton = tk.Button(self.frameL2, text="开始", fg='green', command=self.StartClick)
        self.StartButton.grid(row=0, column=4)
        self.StartButton = tk.Button(self.frameL2, text="停止", fg='yellow', command=self.stopClicks)
        self.StartButton.grid(row=0, column=5)
    def _init_basic_mouse_pos_gui(self):
        # dispaly
        self.MousePosTagLabel = tk.Label(self.frameL2, text="鼠标位置")
        self.MousePosTagLabel.grid(row=1, column=6)
        # var
        self.MousePosition = tk.StringVar()
        # set default value
        self.MousePosition.set('0,0')
        # bind var
        self.MousePosLabel = tk.Label(self.frameL2, textvariable=self.MousePosition)
        self.MousePosLabel.grid(row=2, column=6)
        # button and cmd
        self.getMousePositonButton = tk.Button(self.frameL2, text="开始获取鼠标位置", command=self.startGetMousePositon)
        self.getMousePositonButton.grid(row=1, column=5)
        # button and cmd
        self.stopgetMousePositonButton = tk.Button(self.frameL2, text="停止获取鼠标位置", command=self.stopGetMousePositon)
        self.stopgetMousePositonButton.grid(row=2, column=5)
        # button and cmd
        self.QuitButton = tk.Button(self.frameL2, text="退出", fg='red', command=self.Quit).grid(row=0, column=6)
        self.Click_Pause_Lable = tk.Label(self.frameL2, text="每次点击间隔时间" )
        self.Click_Pause_Lable.grid(row=2, column=3)
        self.Click_Pause_MS = tk.IntVar()
        self.CLick_Puase_Entry = tk.Entry(self.frameL2, textvariable=self.Click_Pause_MS)
        self.Click_Pause_MS.set(3)
        self.CLick_Puase_Entry.grid(row=2,column=4)
    # 自动按键待调试
    def _init_basic_keyboard_gui(self):
        self.keyboard_label = tk.Label(self.frameL1, text="键盘输入")
        self.keyboard_label.pack({'side': 'left'})
        self.keyboard_var = tk.StringVar()
        self.keyboard_entry = tk.Entry(self.frameL1, textvariable=self.keyboard_var)
        self.keyboard_var.set("Input key.")
        self.keyboard_entry.pack({'side': 'left'})
    # 循环timer (递归）
    def _getPosition(self):
        # todo: 设置屏幕大小
        # ScreenSize = pag.size()
        pos_x, pos_y = pag.position()
        Positon = '{},{}'.format(pos_x, pos_y)
        # set positon valuse
        self.MousePosition.set(Positon)
        # async timer control event (for loop)
        self._posTimer = self.root.after(self.UI_Response_MS, self._getPosition)
    # 点击button调用一次， timer要封装函数放入循环中
    def startGetMousePositon(self):
        # 循环（递归获取位置放入循环， timer控制）
        while self.isStartGetPos:
            self._getPosition()
            self.isStartGetPos = False
        return
    # 设置事件，flag 停止loop 调用递归
    def stopGetMousePositon(self):
        print self.isStartGetPos
        self.root.after_cancel(self._posTimer )
        self.isStartGetPos = True
        return
    # 单次点击
    def _singleClick(self, pos, key):
        pos_x, pos_y = map(int, pos.split(","))
        if key == 0:
            print "Left click", key
            pag.click(pos_x, pos_y, clicks=1, button="LEFT")
        elif key == 1:
            print "Right click", key
            pag.click(pos_x, pos_y, clicks=1, button="MIDDLE")
        else:
            print "Mid click", key
            pag.click(pos_x, pos_y, clicks=1, button="RIGHT")
    # click
    def SingleClick(self, pos, key):
        self._singleClick(pos, key)
    # one rows' opreaton
    # 配置响应停止操作， 多批次的任务会同时执行（after执行后，即开始下次循环）
    def RowClicks(self, pos, key, ClickNums):
        # 更新GUI (每次after后先刷新）
        self.root.update_idletasks()
        if not isinstance(ClickNums, int):
            ClickNums = int(ClickNums)
        if ClickNums == 0 or self.notClick:
            self.root.after_cancel(self.click_timer)
            self.notClick = False
            return
        print "do the {} click".format(ClickNums)
        self.SingleClick(pos, key)
        ClickNums -= 1
        # 让GUI能响应其他操作
        # after中的ms是用于UI时间等待，不是函数的等待时间，对func的控制应单独用时间控制
        # 通过递归方式运用，预留递归推出
        self.click_timer = self.root.after(self.UI_Response_MS,
                                            self.RowClicks,
                                            *(pos, key, ClickNums))
        return
    def stopClicks(self):
        self.root.after_cancel(self.click_timer)
        self.notClick = False
    # 开始点击
    def StartClick(self):
        # pag所以操作增加延迟,留出时间用于执行操作，防止一直点击
        pag.PAUSE = self.Click_Pause_MS.get()
        for index in range(len(self.MouseKeyList)):
            self.RowClicks(self.PositionList[index].get(), self.MouseKeyList[index].current(), self.ClickNumList[index].get())
            if self.notClick:
                self.root.after_cancel(self.click_timer)
                self.notClick = True
                break
        return
    # 添加第二列输入
    def AddFrame(self):
        # position
        self.Positions = tk.StringVar()
        self.PositionEntry = tk.Entry(self.frameL2, show=None, textvariable=self.Positions)
        self.PositionEntry.grid(row=self.RowNums, column=0)
        self.PositionList.append(self.Positions)
        # click nums
        self.ClickNums = tk.StringVar()
        self.ClickNUmEntry = tk.Entry(self.frameL2, show=None, textvariable=self.ClickNums)
        self.ClickNUmEntry.grid(row=self.RowNums, column=1)
        self.ClickNumList.append(self.ClickNums)
        # mouse key
        # 当前 多个按键没法区分
        # self.MouseKeyCombobox = ttk.Combobox(self.root, text="点击按键")
        self.MouseKeyCombobox = ttk.Combobox(self.frameL2)
        self.MouseKeyCombobox["values"] = ("左键", "中键", "右键")
        # 0 is values' index
        self.MouseKeyCombobox.current(2)
        self.MouseKeyCombobox.grid(row=self.RowNums, column=2)
        self.MouseKeyList.append(self.MouseKeyCombobox)
        # 总行数增加
        self.RowNums += 1
    # todo:参数验证
    # 退出
    def Quit(self):
        try:
            if self.click_timer:
                self.root.after_cancel(self.click_timer)
        except:
            pass
        try:
            if self._posTimer:
                self.root.after_cancel(self._posTimer)
        except:
            pass
        self.root.quit()

    def _filter(self):
        pass
    # todo:a计时器位置整理
    def _degug_after_after_cancel_(self):
        pass

print "aaa"
# if __name__=="__mian__":
print "Start:"
MouseAutoClickGUI()
print "End"