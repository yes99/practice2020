from tkinter import *

def click():
    print("CLICK")
    l.configure(text="CLICK")

def click2():
    global i
    i= i+1
    b2.configure(text=str(i))


i = 0 #전역변수
win =Tk()

l=Label(win,text="Hello Woorld")
l.pack()
b = Button(win, text="My button", command = click)
b.pack()
b2=Button(win, text = "Your button", command = click2)
b2.pack()

win.mainloop()