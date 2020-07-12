from tkinter import *
from random import *

def game():
    rsp = randint(1,3)
    if rsp == 1:
        l.configure(image = rock)
    elif rsp == 2:
        l.configure(image = scissor)
    else :
        l.configure(image = paper) 

win = Tk()

rock = PhotoImage(file = "r.gif")
scissor = PhotoImage(file = "s.gif")
paper = PhotoImage(file = "p.gif")
l = Label(win, image = rock)
l.pack()
b = Button(win, text = "Change",command = game)
b.pack()

win.mainloop()