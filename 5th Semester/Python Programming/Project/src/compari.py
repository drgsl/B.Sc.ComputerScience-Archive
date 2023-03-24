# Selenium is used to browse the compari website
from selenium.webdriver.common.by import By

# Colorama is used to color the output
from colorama import Fore, Back, Style
from colorama import init
init(autoreset=True)


# Re is used to extract the number from the price
import re

"""
Main Functions
"""
# Returns the product details or None if the product details could not be found
def getProductDetails(driver):
    try:
        productDetails = driver.find_element(By.CLASS_NAME, "product-details")
    except Exception as e:
        print(Back.RED + f"Could not find product details -> {e} ")
        return None

    return productDetails

# Returns the brand name or "" if either no name was found or if the product details could not be found
def getBrandName(driver):
    productDetails = getProductDetails(driver)
    
    if productDetails is None:
        print(Back.RED + f"Could not get product details")
        return ""

    try:
        productBrand = productDetails.find_element(By.XPATH, "//*[contains(@itemprop, 'brand')]")
    except Exception as e:
        print(Back.RED + f"Could not find product brand -> {e} ")
        return ""
        
    print(f"Product Brand: ", end="")
    print(Back.GREEN + f"{productBrand.text}")

    return productBrand.text

# Returns the product name or "" if either no name was found or if the product details could not be found
def getProductName(driver):
    productDetails = getProductDetails(driver)
    
    if productDetails is None:
        print(Back.RED + f"Could not get product details")
        return ""

    try:
        productName = productDetails.find_elements(By.XPATH, "//span[contains(@itemprop, 'name')]")[1]
    except Exception as e:
        print(Back.RED + f"Product Name could not be found -> {e} ")
        return ""

    print(f"Product Name:", end="")
    print(Back.GREEN + f"{productName.text}")

    return productName.text

# Returns the lowest price of the product or -1 if either no price was found or if the product details could not be found
def getLowestPrice(driver):
    productDetails = getProductDetails(driver)
    
    if productDetails is None:
        print(Back.RED + f"Could not get product details")
        return -1

    try:
        lowestPriceText = productDetails.find_element(By.XPATH, "//*[contains(@itemprop, 'lowPrice')]")
        lowestPrice = getFloat(lowestPriceText.text)
    except Exception as e:
        print(Back.RED + f"Lowest Price could not be found -> {e} ")
        return -1

    print(f"Lowest Price: ", end="")
    print(Back.GREEN + f"{lowestPrice}")

    return lowestPrice

# Returns the highest price of the product or -1 if either no price was found or if the product details could not be found
def getHighestPrice(driver):
    productDetails = getProductDetails(driver)
    
    if productDetails is None:
        print(Back.RED + f"Could not get product details")
        return -1
    
    try:
        prices = getAllPrices(driver)
        if len(prices) == 0:
            print(Back.RED + f"Could not get prices")
            return -1
        highestPrice = ""
        for price in prices:
            if(price.text > highestPrice):
                highestPrice = price.text
    except Exception as e:
        print(Back.RED + f"Highest Price could not be found -> {e} ")
        return -1
    highestPrice = getFloat(highestPrice)

    print(f"Highest Price: ", end="")
    print(Back.GREEN + f"{highestPrice}")

    return highestPrice

# Returns the currency of the product or "" if either no currency was found or if the product details could not be found
def getCurrency(driver):
    productDetails = getProductDetails(driver)

    if productDetails is None:
        print(Back.RED + f"Could not get product details")
        return ""
    try:
        lowestPriceText = productDetails.find_element(By.XPATH, "//*[contains(@itemprop, 'lowPrice')]")
        currency = getLastWord(lowestPriceText.text)
    except Exception as e:
        print(Back.RED + f"Currency could not be found -> {e} ")
        return ""
        
    print(f"Currency: ", end="")
    print(Back.GREEN + f"{currency}")

    return currency



# Returns the number of shops that sell the product or -1 if the number of shops could not be found
def getNumberOfOffers(driver):
    try:
        offerCountText = driver.find_element(By.CLASS_NAME, "offer-count")
        offerCount = re.findall(r'\d+', offerCountText.text)[0]
    except Exception as e:
        print(Back.RED + f"No offer count found -> {e} ")
        return -1

    print(f"Found: ", end="")
    print(Back.GREEN + f"{offerCount} offers", end="")
    print(f" available")

    return int(offerCount)

"""
Helper Functions
"""
def getAllPrices(driver):
    try:
        prices = driver.find_elements(By.CLASS_NAME, "row-price")
    except Exception as e:
        print(Back.RED + f"Could not find prices -> {e} ")
        return None
    return prices


def getFloat(text):
    numbers = re.findall(r'\d+', text)
    number = ""
    
    for pairsOfDigits in numbers[:-1]:
        number += pairsOfDigits

    decimalDigits = float(numbers[-1]) / 100
    number = float(number)
    return number + decimalDigits 


def getLastWord(text):
    return text.split()[-1]

# def findHigestPriceWithTag(driver):
#     productDetails = getProductDetails(driver)
    
#     if productDetails is None:
#         print(Back.RED + f"Could not get product details")
#         return -1
    
#     try:
#         highestPriceText = productDetails.find_elements(By.XPATH, "//*[contains(@itemprop, 'highPrice')]")
#         for price in highestPriceText:
#             print(price.text)
#         # highestPrice = float(highestPriceText[1].text)
#         # print(Back.GREEN + f"Highest Price: ", end="")
#         # print(f"{highestPrice}")
#     except Exception as e:
#         print(Back.RED + f"Highest Price could not be found -> {e} ")
#     return -1