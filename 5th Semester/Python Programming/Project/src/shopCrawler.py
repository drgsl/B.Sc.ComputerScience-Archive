# compari is used to crawl the compari.ro website
import compari

# seleniumDriver is used to use the Selenium WebDriver
import seleniumDriver

# datetime is used to get the current date and time 
from datetime import datetime 


def getProductsInfo(urls):
    productsInfo = []

    # Driver Setup
    driver = seleniumDriver.getDriver()

    for url in urls:
        productsInfo.append(getProductInfo(driver, url))
    
    driver.close()
    return productsInfo


def getProductInfo(driver, url):

    if driver is None:
        driver = seleniumDriver.getDriver()
    
    if url is None:
        return None

    # Driver Navigation
    seleniumDriver.navigateDriverTo(driver, url)        
        
    productDict = dict()

    # Add current date to dict
    todayDate = datetime.today().strftime("%d/%m/%y")
    productDict['date'] = todayDate

    # Add current time to dict
    currentTime = datetime.now().strftime("%H:%M:%S")
    productDict['time'] = currentTime

    # Add Brand Name to dict
    productDict["productBrand"] = compari.getBrandName(driver)

    # Add Product Name to dict
    productDict["productName"] = compari.getProductName(driver)

    # Add Number of Offers to dict
    productDict["offerCount"] = compari.getNumberOfOffers(driver)

    # Add Lowest Price to dict   
    productDict["lowestPrice"] = compari.getLowestPrice(driver)

    # Add Highest Price to dict
    productDict["highestPrice"] = compari.getHighestPrice(driver)
    
    # Add price Currency to dict
    productDict['Currency'] = compari.getCurrency(driver)

    return productDict
