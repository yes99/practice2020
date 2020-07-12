from tkinter import *


def func1():
    l3.configure(text = str(value1))
    l4.configure(text = str(value2))
   
win = Tk()


l1 = Label(win, text = "이름")
l1.pack()
e1 = Entry(win)
e1.pack()
l2 = Label(win, text = "학번")
l2.pack()
e2 = Entry(win)
e2.pack()
value1 = e1.get()
value2 = e2.get()


l3 = Label(win, text =" " )
l3.pack()
l4 = Label(win, text = " ")
l4.pack()

b1 = Button(win, text = "입력", command = func1)
b1.pack()




win.mainloop()


