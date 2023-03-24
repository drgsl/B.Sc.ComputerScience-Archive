import os
import sys

def sortUniqueWords(csvFile, columnName):

    if(os.path.exists(csvFile) == False):
        exception = Exception("File not found")
        return exception

    try:
        f = open(csvFile, 'r')
        text = f.read()
        f.close()
    except:
        exception = Exception("IO Error")
        return exception

    words = text.split()

    words = text.split(',')

    maxCols = 3
    currCol = 0

    index = -1
    for word in words:
        if(word.upper() == columnName.upper()):
            
            if(index != -1):
                exception = Exception("Duplicate column name")
                return exception
            index = words.index(columnName)
        currCol += 1

        if(currCol >= maxCols):
            if(index == -1):
                exception = Exception("Unknown column name")
                return exception
            


    words.sort()

    uniqueWords = []

    for word in words:
        if word not in uniqueWords:
            uniqueWords.append(word)
    return uniqueWords

if __name__ == '__main__':
    try:
        print(sortUniqueWords(sys.argv[0], sys.argv[1]))
    except Exception as e:
        print(e)