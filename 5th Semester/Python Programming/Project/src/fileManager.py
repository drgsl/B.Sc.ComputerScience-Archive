# os is used to save the json file in the correct directory
import os

# json is used to save the data to a json file
import json

# datetime is used to get the current date and time 
from datetime import datetime 

def getProjectPath():
    return os.path.abspath(os.path.join(".", os.pardir))

def removeIllegalCharacters(string):
    illegalCharacters = ['\\', '/', ':', '*', '?', '"', '<', '>', '|']
    for character in illegalCharacters:
        string = string.replace(character, '')
    return string

def appendToEachFile(productsInfo):
    projPath = getProjectPath()

    for productInfo in productsInfo:
        productJson = json.dumps(productInfo)
        fileName = f'{productInfo["productBrand"]}_{productInfo["productName"]}.json'
        fileName = removeIllegalCharacters(fileName)
        filePath = os.path.join(projPath, '', 'output', fileName)
        print(f"Saving {fileName} to {filePath}")
        open(filePath, 'a').write(productJson + '\n')

def saveToNewFile(productsInfo):
    projPath = getProjectPath()
        
    todayDate = datetime.today().strftime("%d-%m-%y")
    currentTime = datetime.now().strftime("%H;%M;%S")

    fileName = f'{todayDate} {currentTime}.json'
    filePath = os.path.join(projPath, '', 'output', fileName)

    for productInfo in productsInfo:
        productJson = json.dumps(productInfo)
        open(filePath, 'a').write(productJson + '\n')
    
    print(f"Saved {fileName} to {filePath}")
