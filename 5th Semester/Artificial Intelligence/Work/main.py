from rdflib import Graph
import random
import nltk

g = Graph()
g.parse("food.rdf")
ontologie = ""
lista_ontologii = []

for concept1, relatie, concept2 in g:
    #print(concept1,relatie,concept2)
    if "#" in concept1 and "#" in relatie and "#" in concept2:
        ontologie += concept1.split("#")[1] + "-" + relatie.split("#")[1] + "-" + concept2.split("#")[1] + "\n"
        lista_ontologii.append([concept1.split("#")[1],relatie.split("#")[1],concept2.split("#")[1]])

with open("ontologie.txt","w") as w:
    w.write(ontologie)

with open("ontologie.txt", "r") as r:
    Lines = r.readlines()

#print(lista_ontologii)

length_list = len(lista_ontologii)
cuvinte_si_relatii = ""
cuvinte_si_relatii_1 = ""
index = 0
while index < length_list:
    cuvinte_si_relatii += lista_ontologii[index][0] + "\n" + lista_ontologii[index][2]
    cuvinte_si_relatii_1 += lista_ontologii[index][2] + "\n" + lista_ontologii[index][0]
    index1 = 0
    while index1 < length_list:
        if index != index1:
            if lista_ontologii[index][0] == lista_ontologii[index1][0]:
                cuvinte_si_relatii += "," + lista_ontologii[index1][2]
            if lista_ontologii[index][0] == lista_ontologii[index1][2]:
                cuvinte_si_relatii += "," + lista_ontologii[index1][0]
            if lista_ontologii[index][2] == lista_ontologii[index1][0]:
                cuvinte_si_relatii_1 += "," + lista_ontologii[index1][2]
            if lista_ontologii[index][2] == lista_ontologii[index1][2]:
                cuvinte_si_relatii_1 += "," + lista_ontologii[index1][0]
        index1 += 1
    cuvinte_si_relatii += "\n"
    cuvinte_si_relatii_1 += "\n"
    index += 1
with open("cuvinte_si_relatii.txt","w") as w:
    w.write(cuvinte_si_relatii + cuvinte_si_relatii_1)
    print("Success")



print("Raspunde la urmatoarele intrebari: \n")
while 1:
    n = random.randint(0,len(lista_ontologii)-1)
    index_question = random.randint(0,2)
    index_question1 = random.randint(0,2)
    type_of_question = random.randint(0,2)
    type1 = 0
    question = ""
    if type_of_question == 0 and index_question1 != index_question and (index_question == 0 or index_question == 2) and (index_question1 == 0 or index_question1 == 2):
        question += "Care este relatia dintre " + lista_ontologii[n][index_question] + " si " + lista_ontologii[n][index_question1] + "? \n"
    elif type_of_question == 1 and (index_question == 0 or index_question == 2):
        type1 = random.randint(0,2)
        if type1 == 1:
            question += "Cine este in relatie cu " + lista_ontologii[n][index_question] + "? Scrieti un singur element \n"
        else:
            question += "Cine este in relatie cu " + lista_ontologii[n][index_question] + "? \n" \
                                "Scrieti toate raspunsurile, sub urmatoarea structura: raspuns1,raspuns2 etc., fara a fi separate prin spatii raspunsurile \n"
    else:
        continue
    answer = input(question)
    ok = 0
    if type_of_question == 0 and answer == lista_ontologii[n][1]:
        ok = 1
    elif type_of_question  == 1:
        if type1 == 1:
            for element in lista_ontologii:
                if element[0] == lista_ontologii[n][index_question]:
                    if answer == element[2]:
                        ok = 1
                if element[2] == lista_ontologii[n][index_question]:
                    if answer == element[0]:
                        ok = 1
        else:
            lista_relatii_cerinta = []
            for element in lista_ontologii:
                if element[0] == lista_ontologii[n][index_question]:
                    if answer == element[2]:
                        lista_relatii_cerinta += element[0]
                if element[2] == lista_ontologii[n][index_question]:
                    if answer == element[0]:
                        lista_relatii_cerinta += element[2]
            lista_relatii_raspuns = answer.split(",").sort()
            lista_relatii_cerinta.sort()
            if lista_relatii_raspuns == lista_relatii_cerinta:
                print("The answer is okay")
            else:
                print("The answer is not okay")

    if ok == 1:
        print("The answer is okay")
    else:
        print("The answer is not okay")
    answer_next = input("Trecem la urmatoarea intrebare? Daca vrei sa iesim, scrie 'exit' \n")
    while answer_next != "da":
        if answer_next == "exit":
            quit()
        answer_next = input("Trecem la urmatoarea intrebare? Daca vrei sa iesim, scrie 'exit' \n")