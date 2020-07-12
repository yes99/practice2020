from tkinter import*

k=1
for i in range(1,20+1):
    k = k *i


win = Tk()

l= Label(win, text = "1부터20까지의 곲 = "+ str(k))
l.pack()


win.mainloop()