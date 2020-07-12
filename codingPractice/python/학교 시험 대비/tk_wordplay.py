from tkinter import*

def display(txt):
    global string
    if txt == "초기화":
        string = ""
    else:
        string = string + txt
    l.configure(text = string)

win =Tk()
buttonList = ["나는", "당신을", "좋아합니다",
            "너는", "나를", "싫어합니다",
            "고양이는", "고양이를", "초기화"]

rowindex, colindex = 1,0
string=""
l = Label(win)
l.grid(row = 0, column=0, columnspan=3)
for btext in buttonList:

    def click_button(t = btext):
        display(t)

    Button(win, text = btext, width=20, command = click_button).grid(row=rowindex,column = colindex)
    colindex = colindex +1
    if colindex >=3:
        colindex = 0
        rowindex = rowindex +1

win.mainloop()