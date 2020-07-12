from tkinter import *


win = Tk()

b1 = Button(win, text="버튼1")
b1.grid(row=0, column=0)
b2 = Button(win, text="버튼2")
b2.grid(row=0, column=1)
l1 = Button(win, text="라벨1")
l1.grid(row=1, column=0)
b3 = Button(win, text="버튼3")
b3.grid(row=1, column=1)
l2 = Button(win, text="라벨2")
l2.grid(row=2, column=0, columnspan=2)


win.mainloop()
