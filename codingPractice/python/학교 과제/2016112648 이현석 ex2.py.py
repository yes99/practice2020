from tkinter import *


def func1():
    global k
    k= k+1
    l1.configure(text = str(k))

def func2():
    global k
    k= k-1
    l1.configure(text = str(k))



k=0
win = Tk()

l1 = Label(win, text = k)
l1.pack()


b1 = Button(win, text = "증가", command = func1)
b1.pack()
b2 = Button(win, text="감소", command = func2)
b2.pack()

win.mainloop()


