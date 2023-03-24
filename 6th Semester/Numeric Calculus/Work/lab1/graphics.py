from tkinter import *

root = Tk()
root.geometry("300x300")
root.title(" Lab1 - Ex1 ")

def Take_input():
	INPUT = inputtxt.get("1.0", "end-1c")
	print(INPUT)
	if(1 + 10**(-int(INPUT)) != 1):
		Output.insert(END, 'FALSE')
	else:
		Output.insert(END, "TRUE")
	
l = Label(text = "Guess a value for m so that 1 + u != 1 \n ,where u = 10^-m")
inputtxt = Text(root, height = 10,
				width = 25,
				bg = "light yellow")

Output = Text(root, height = 5,
			width = 25,
			bg = "light cyan")

Display = Button(root, height = 2,
				width = 20,
				text ="Show",
				command = lambda:Take_input())

l.pack()
inputtxt.pack()
Display.pack()
Output.pack()

mainloop()
