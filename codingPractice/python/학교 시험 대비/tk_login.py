from tkinter import*

def login():
    global inID, inPW
    iid=e1.get()
    ipw=e1.get()
    if inID==iid and inPW == ipw:
        l3.configure(text="접근허가\n" + iid + "welcome", fg="green")
    else:
        l3.configure(text="nono\n" + iid + "gohome", fg="whilte", bg="red")

inID="yes99"
inPW="123"

win = Tk()
l1=Label(win, text = "ID")
l1.grid(row=0, column = 0)
e1=Entry(win)
e1.grid(row=0, column = 1)
l2=Label(win, text = "PW")
l2.grid(row=1, column = 0)
e2=Entry(win)
e2.grid(row=1, column = 1)

l3=Label(win)
l3.grid(row=2,column=1)
b=Button(win,text="LOGIN", command = login)
b.grid(row=1, column=2)

win.mainloop()