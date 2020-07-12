from tkinter import*

def func():
    b2.configure(text = "버튼이 클릭되었음")
    l1.configure(text = "버튼이 클릭되었음")


win =Tk()

l1 = Label(win, text="Hello World!", font = ("굴림체","15", "italic"))
l1.pack()
b1 = Button(win, text="버튼")
b1.pack()
b2 = Button(win, text = "버튼", command = func)
b2.pack()

win.mainloop()