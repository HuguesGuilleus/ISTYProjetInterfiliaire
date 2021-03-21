from tkinter import *
import os

def main_window():    #Affichage les evenements et le menu pour rajouter/modifier/supprimer un evenement
    window = Tk()
    window.geometry("1280x800+200+100")
    window.title("IHM !")
    window.configure(background="black")


    Label(window, text="Interface de choix des couleurs", bg="black", fg="red", font="TimesNewRoman 20 bold italic").grid(row=0, column=4, pady=20)


    Button(window, text="Choisir rouge", command=rouge).grid(row=1, column=3, pady=15)
    Button(window, text="Choisir bleu", command=bleu).grid(row=2, column=3, pady=15)
    Button(window, text="Choisir vert", command=vert).grid(row=3, column=3, pady=15)
    Button(window, text="Quitter", command=quit).grid(row=4, column=3, pady=15)
    


    window.mainloop()

def rouge():
    print("ROUGE!")
    os.system("python3 ball.py red")	

def bleu():
    print("BLEU")
    os.system("python3 ball.py blue")

def vert():
    print("VERT")
    os.system("python3 ball.py green")
    
def quit():
	exit()
    


main_window()
