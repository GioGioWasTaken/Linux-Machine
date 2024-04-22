from selenium import webdriver
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

# def is_redirected(driver):
#     current_url = driver.current_url
#     return current_url.startswith("https://kaku-navi.com/")

def scrape_data(driver, counter, mylist):
    for i in range(99999):
        driver.get(f"https://kaku-navi.com/idiom/idiom{i}.html")
        # if is_redirected(driver):
        #     continue
        try:
            card = ExprCard()
            card.expr = driver.find_element_by_class_name("pageTitle").text
            manga_blocks = driver.find_elements_by_class_name("idiomMangaBlock")
            if len(manga_blocks) >= 2:
                card.secondlastimage = manga_blocks[-2].find_element_by_tag_name("img").get_attribute("src")
                card.lastimage = manga_blocks[-1].find_element_by_tag_name("img").get_attribute("src")
            cont_blocks = driver.find_elements_by_class_name("contTextBlock")
            if len(cont_blocks) >= 2:
                card.yomikata = cont_blocks[0].text
                card.meaning = cont_blocks[1].text
            cont_list_blocks = driver.find_elements_by_class_name("contListBlock")
            if len(cont_list_blocks) >= 2:
                card.douruigo = cont_list_blocks[1].text
            mylist.append(card)
            counter += 1
            if counter >= 99999:
                break
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
