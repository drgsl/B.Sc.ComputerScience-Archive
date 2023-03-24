# Selenium is used to automate the browser
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.common import exceptions

# Colorama is used to color the output
from colorama import Fore, Back, Style
from colorama import init
init(autoreset=True)

# Sys is used to exit the program in case of an error
import sys

def getDriver():
    try:
        driver = webdriver.Chrome()
    except exceptions.SessionNotCreatedException:
        driver = webdriver.Firefox()
    except Exception as e:
        print(Back.RED + f"Could not create driver -> {e} ")
        sys.exit(1)
    
    print(f"{driver.capabilities['browserName']} Driver created")

    driver.minimize_window()
    return driver  

def navigateDriverTo(driver, url):
    try:
        driver.get(url)
    except Exception as e:
        print(Back.RED + f"Could not access url -> {e} ")
        print(Back.RED + f"url: {url} ")
        sys.exit(1)

    print(f"Successfully navigated to {url}")