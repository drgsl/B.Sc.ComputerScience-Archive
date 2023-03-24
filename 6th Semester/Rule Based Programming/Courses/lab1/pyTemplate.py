"""
Temă (5 puncte): 
Implementați o aplicație care interacționează cu utilizatorul
 în vederea alegerii opționalelor din semestrul 2 anul 3.
 Folosiți opțiunile disponibile aici: Informatică . 
 Ieșirea din program indică un curs din fiecare pachet. 
 Trebuie să aveți minim 3 întrebări pe pachet sau 7 în total. 
Bonus (1 punct): Implementarea aceleiași aplicații în CLIPS.
"""

"""
Discipline opţionale: 1 din 4
Programare bazată pe reguli 5 ECTS
C: 2 S: L: 2 Ex: E
Tehnici de programare pe platforme mobile 5 ECTS
C: 2 S: L: 2 Ex: E
Aspecte computaţionale în teoria numerelor 5 ECTS
C: 2 S: L: 2 Ex: E
Proiectarea jocurilor 5 ECTS
C: 2 S: L: 2 Ex: E


Discipline opţionale: 1 din 4
Psihologia comunicării profesionale în domeniul IT-lui 6 ECTS
C: 2 S: L: 2 Ex: E
Cloud Computing 6 ECTS
C: 2 S: L: 2 Ex: E
Interacțiune om-calculator 6 ECTS
C: 2 S: L: 2 Ex: E
Analiza reţelelor media sociale 6 ECTS


Discipline opţionale: 1 din 4
Reţele Petri şi aplicaţii 6 ECTS
C: 2 S: L: 2 Ex: E
Smart Card-uri şi Aplicaţii 6 ECTS
C: 2 S: L: 2 Ex: E
Inginerie software specifică automobilelor 6 ECTS
C: 2 S: L: 2 Ex: E
Introducere în Internetul lucrurilor 6 ECTS
C: 2 S: L: 2 Ex: E
"""


print("Hi, i'll help u choose one elective course from each course-pack")
print("i'll ask u some questions, and based on ur responses i'll choose what best fits ur needs")

print("you can answer with 1 or 0. 1 = Yes, 0 = No")

print("--Primul Pachet--")
print("First question: ")
answr = input("Would you like to implement games? (for mobile or for anything else)")
answr = int(answr)
if (answr == 1):
    answr2 = input("Do u want your games to be mobile-only?")
    answr2 = int(answr2)

    if(answr2 == 1):
        print("Tehnici de programare pe platforme mobile")
    else:
        print("Game Design")
else:
    answr2 = input("Do u like math?")    
    answr2 = int(answr2)

    if(answr2 == 1):
            print("Number Theory")
    else:
            print("Programare bazata pe reguli")


answr = input("Are u interested in humans?")
answr = int(answr)

if(answr == 1):
    answr2 = input("Are u interested in how humans interact with computers?")
    answr2 = int(answr2)
    
    if(answr2 == 1):
        print("Human-Computer Interaction")
    else:
        answr3 = ("Are u interested in analysing social media?")
        answr3 = int(answr3)

        if(answr3 == 1):
            print("analiza retelelor social media")
        else:
            print("psihologia comunicarii profesionale in it")
else:
    print("Cloud Computing")


answr = input("Are u interested in embedded systems or in IOT systems?")
answr = int(answr)

if(answr == 1):
    answr2 = input("Have u ever wondered how a debit card works?")
    answr2 = int(answr2)

    if answr2 == 1:
        print("Smart Card-uri si aplicatii")
    else:
        print("introduction in IOT")
else:
    answr2 = input("Are u interested in cars?")
    answr2 = int(answr2)

    if(answr2 == 1):
        print("ingineria software specifica automobilelor")
    else:
        print("retele petri si aplicatii")