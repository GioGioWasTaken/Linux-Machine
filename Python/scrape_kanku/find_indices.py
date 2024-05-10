from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.options import Options
from selenium.common.exceptions import NoSuchElementException

class ExprCard:
    def __init__(self):
        self.expr = ""
        self.secondlastimage = ""
        self.lastimage = ""
        self.yomikata = ""
        self.meaning = ""
        self.douruigo = ""

def scrape_data(driver, counter, mylist):
    for i in range(99999):
        print(i)
        driver.get(f"https://kaku-navi.com/idiom/idiom{i:05d}.html")
        try:
            card = ExprCard()
            card.expr = driver.find_element(By.CLASS_NAME, "pageTitle").text
            print(card.expr)
            if(card.expr):
                mylist.append(i)
                print(mylist)
        except NoSuchElementException:
            continue

def main():
    options = Options()
    options.headless = True
    driver = webdriver.Firefox(options=options)  # Headless Firefox driver
    counter = 0
    mylist = []  # List to hold the scraped data
    scrape_data(driver, counter, mylist)
    driver.quit()
    print(mylist)

if __name__ == "__main__":
    main()
