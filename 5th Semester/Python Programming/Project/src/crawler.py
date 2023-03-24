# sys is used to get the command line arguments
import sys

# shopCrawler is used to crawl an online shop
import shopCrawler

# fileManager is used to save the data to a json file
import fileManager

"""
Se va crea un crawler pentru a prelua informatii despre: 
-pretul unor produse date ca lista de input.
Se va crea un fisier json in care se vor retine urmatoarele informatii: 
>numele produsului,
>pretul cel mai bun, 
>pretul cel mai mare, 
>numarul de oferte. 

Site-ul ce va fi utilizat ca si suport: https://www.compari.ro.

INPUT: compari.py <urls of products>
OUTPUT: Un fisier json in care se afla informatiile despre preturile produselor.
"""

if __name__ == '__main__':
    
    urls = []

    print(f"Found {len(sys.argv) - 1} url(s)")

    for i in range(1, len(sys.argv)):
        urls.append(sys.argv[i])
    
    productsInfo = shopCrawler.getProductsInfo(urls)

    fileManager.appendToEachFile(productsInfo)
    fileManager.saveToNewFile(productsInfo)
    
    print("Done :)")