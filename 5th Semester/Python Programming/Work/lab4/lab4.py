import os
import sys



"""
1)	Să se scrie o funcție ce primeste un singur parametru,
director, ce reprezintă calea către un director. 

Funcția returnează o listă cu extensiile unice 
sortate crescator (in ordine alfabetica) 
a fișierelor din directorul dat ca parametru.

Mențiune: extensia fișierului ‘fisier.txt’ este ‘txt’ 
"""

def pb1():
    print(extensii("/home/dragosel/fii/year3/py/lab4/"))

def extensii (director) :
    extensii_list = set([])
    files = os.listdir(director)
    
    for file in files :
        for poz in range(len(file) - 1 , 0, -1):
            if (file[poz] == '.') :
                extensii_list.add(file[poz + 1:])
                break

    return sorted( extensii_list )


"""
2)	Să se scrie o funcție ce primește 
ca argumente două căi: director si fișier. 

Implementati functia astfel încât în fișierul 
de la calea fișier să fie scrisă pe câte o linie, 
calea absolută a fiecărui fișier din interiorul 
directorului de la calea folder, ce incepe cu litera A. 
"""
def pb2():
    print(director_records("/home/dragosel/fii/year3/py/lab4", "/home/dragosel/fii/year3/py/lab4/pb2_absolutePathOfFoldersFromGivenDir"))

def director_records(director, fisier) :
    files_in_dir = os.listdir(director)
    files_record = open(fisier, "w")

    for file_in_dir in files_in_dir :
        cale = os.path.join(director, file_in_dir)
        if os.path.isfile(cale) == True :
            files_record.write(cale)
            files_record.write("\n")
    print("Written in ", fisier )
    return


"""
3) Să se scrie o funcție ce primește 
ca parametru un string my_path.

Dacă parametrul reprezintă calea către un fișier, 
se vor returna ultimele 20 de caractere din 
conținutul fișierului. 
Dacă parametrul reprezintă calea către un director, 
se va returna o listă de tuple (extensie, count), 
sortată descrescător după count, 
unde extensie reprezintă extensie de fișier, 
iar count - numărul de fișiere cu acea extensie. 

Lista se obține din toate fișierele (recursiv) 
din directorul dat ca parametru. 
"""

def pb3():
    print ( fisier_file("/home/dragosel/fii/year3/py/lab4/lab4.py") )
    print()
    print ( fisier_file("/home/dragosel/fii/year3/py/") )

def fisier_file(my_path) :
    if os.path.isfile (my_path) :
        input_file = open(my_path, "r")
        data = input_file.read()

        return data[-20:]
    
    elif os.path.isdir (my_path) :
        extensions_dict = dict([])

        for (root, director, files) in os.walk(my_path) :
            for file in files :
                for poz in range(len(file) - 1, 0, -1) :
                    if (file[poz] == '.') :
                        
                        if (file[poz:] in extensions_dict) == False :
                            extensions_dict[file[poz:]] = 1
                        else :
                            extensions_dict[file[poz:]] += 1
                        break
        
        return extensions_dict




"""
4) Să se scrie o funcție ce returnează 
o listă cu extensiile unice a fișierelor din directorul 
dat ca argument la linia de comandă (nerecursiv). 

Lista trebuie să fie sortată crescător.

Mențiune: extensia fișierului ‘fisier.txt’ 
este ‘txt’, iar ‘fisier’ nu are extensie, 
deci nu va apărea în lista finală. 
"""

def pb4():

    print(getExtensionsRecursively("/home/dragosel/fii/year3/py/lab4"))

def getExtensionsRecursively(initialDir):
    dictionar_extensii = dict([])

    for file in os.listdir(initialDir) :
        
        if os.path.isfile(file) :
            for poz in range( len(file) - 1, 0, -1) :

                
                if (file[poz] == '.') :
                    if (file[poz:] in dictionar_extensii) == False :
                        dictionar_extensii[file[poz:]] = 1
                    else :
                        dictionar_extensii[file[poz:]]  += 1
                    break
    return dictionar_extensii



"""
5)	Să se scrie o funcție care primește ca argumente 
două șiruri de caractere, target și to_search și 
returneaza o listă de fișiere care conțin to_search. 

Fișierele se vor căuta astfel: 
dacă target este un fișier, se caută doar in 
fișierul respectiv iar dacă este un director 
se va căuta recursiv in toate fișierele din acel director. 
Dacă target nu este nici fișier, nici director, 
se va arunca o excepție de tipul ValueError cu 
un mesaj corespunzator.
"""

def pb5():
    print("Not implemented")

"""
6)	Să se scrie o funcție care are același 
comportament ca funcția de la exercițiul anterior, 
cu diferența că primește un parametru în plus: 

o funcție callback, care primește un parametru, 
iar pentru fiecare eroare apărută în procesarea 
fișierelor, se va apela funcția respectivă cu 
instanța excepției ca parametru.
"""

def pb6():
    print("Not implemented")

"""
7)	Să se scrie o funcție care primește ca parametru 
un șir de caractere care reprezintă calea către un fișer 

si returnează un dicționar cu următoarele cămpuri: 
full_path = calea absoluta catre fisier, 
file_size = dimensiunea fisierului in octeti, 
file_extension = extensia fisierului (daca are) sau "", 
can_read, can_write = True/False daca se poate citi 
din/scrie in fisier.
"""

def pb7():
    print(file_caracteristics("/home/dragosel/fii/year3/py/lab4/lab4.py"))

def file_caracteristics (file_path) :
    caracteristics_dict = dict([])

    caracteristics_dict["full_path"] = os.path.abspath(file_path)
    caracteristics_dict["file_size"] = os.path.getsize(file_path)
    caracteristics_dict["file_exteson"] = os.path.splitext(file_path)[1]
    caracteristics_dict["can_read"] = os.access(file_path, os.W_OK)
    caracteristics_dict["can_write"] = os.access(file_path, os.R_OK)

    return caracteristics_dict

"""
8)	Să se scrie o funcție ce primește un parametru cu 
numele dir_path. 

Acest parametru reprezintă calea către un director 
aflat pe disc. 

Funcția va returna o listă cu toate căile absolute 
ale fișierelor aflate în rădăcina directorului dir_path.

Exemplu apel funcție: 

functie("C:\\director") 
va returna:
["C:\\director\\fisier1.txt", "C:\\director\\fisier2.txt"]

Calea "C:\\director" are pe disc următoarea structură:

C:\\director\\fisier1.txt <- fișier

C:\\director\\fisier2.txt <- fișier

C:\\director\\director1 <- director

C:\\director\\director2 <- director
"""

def pb8():
    print ( absolute_paths("/home/dragosel/fii/year3/py/lab4/") )

def absolute_paths (root_path) :

    absolute_paths_list = []

    for file in os.listdir(root_path) :
        if os.path.isfile(file) :
            absolute_paths_list.append(os.path.abspath( os.path.join(root_path, file) ) ) 

    return absolute_paths_list

if __name__ == '__main__':

  print()
  print()

  print(" ------ ------ Problem 1 ------ -----")
  pb1()
  print()

  print(" ------ ------ Problem 2 ------ -----")
  pb2()
  print()

  print(" ------ ------ Problem 3 ------ -----")
  pb3()
  print()

  print(" ------ ------ Problem 4 ------ -----")
  pb4()
  print()

  print(" ------ ------ Problem 5 ------ -----")
  pb5()
  print()

  print(" ------ ------ Problem 6 ------ -----")
  pb6()
  print()

  print(" ------ ------ Problem 7 ------ -----")
  pb7()
  print()

  print(" ------ ------ Problem 8 ------ -----")
  pb8()
  print()
