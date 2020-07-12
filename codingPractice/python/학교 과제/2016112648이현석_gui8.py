from tkinter import *
import random
def change_picture():
    i = random.randint(1,99)

    if i % 3 == 0:
        l.configure(image = photo1)
    elif i % 3 == 1:
        l.configure(image = photo2)
    else:
        l.configure(image = photo3)
    i = i+i  
    l1.configure(text = i)

win = Tk()
photo1 = PhotoImage(file = "r.gif")
photo2 = PhotoImage(file = "s.gif")
photo3 = PhotoImage(file = "p.gif")

l = Label(win, image = "")
l.pack()
l1 = Label(win, text=2)
l1.pack()
b = Button(win, text="change", command = change_picture)
b.pack()

win.mainloop()