import requests
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.by import By
from selenium import webdriver

class ExprCard:
    def __init__(self):
        self.expr = ""
        self.secondlastimage = ""
        self.lastimage = ""
        self.yomikata = ""
        self.meaning = ""
        self.douruigo = ""
        self.src_url =""


def add_to_anki(card):
    anki_note = {
        "deckName": "皮のいい（可愛い）名言",
        "modelName": "Migaku Japanese- Clone for vocab",
        "fields": {
            "Is Vocabulary Card": "X",
            "Target Word": card.expr,
            "Translation": card.yomikata,
            "Definitions": card.meaning,
            "Word Audio": card.douruigo,
            "Example Sentences": card.src_url
        },
        "options": {
            "allowDuplicate": False
        },
        "tags": ["japanese_idioms"],
        "picture": [
            {
                "url": card.secondlastimage,
                "filename": "sentence_image.jpg",
                "fields": ["Sentence"]
            },
            {
                "url": card.lastimage,
                "filename": "image.jpg",
                "fields": ["Images"]
            }
        ]
    }

    # Send a request to Anki-Connect to add the note
    response = requests.post("http://localhost:8765", json={
        "action": "addNote",
        "version": 6,
        "params": {
            "note": anki_note
        }
    })

    # Check if the request was successful
    if response.json().get("error") is None:
        print(f"Added {card.expr} to Anki.")
    else:
        print(f"Failed to add {card.expr} to Anki: {response.json()['error']}")


def scrape_data(driver, counter, mylist):
    print(f"idiom count: { len(mylist) }")
    for i in mylist:
        print(i)
        format_str = f"https://kaku-navi.com/idiom/idiom{i:05d}.html"
        driver.get(format_str)
        try:
            card = ExprCard()

            card.src_url = format_str

            card.expr = driver.find_element(By.CLASS_NAME, "pageTitle").text

            # Get the single idiom manga block
            manga_blocks = driver.find_elements(By.CLASS_NAME, "idiomMangaBlock")

            number_of_panels = 0
            panels = None

            # Ensure there's at least one manga block
            if manga_blocks:
                # Get the first manga block
                manga_block = manga_blocks[0]
                
                # Find all <p> elements within the manga block
                panels = manga_block.find_elements(By.TAG_NAME, "p")
                
                number_of_panels = len(panels)

            if number_of_panels >= 2 and panels!=None:

                card.secondlastimage = panels[-2].find_element(By.TAG_NAME, "img").get_attribute("src")
                print("" +card.secondlastimage)

                card.lastimage = panels[-1].find_element(By.TAG_NAME, "img").get_attribute("src")

            cont_blocks = driver.find_elements(By.CLASS_NAME, "contTextBlock")
            if len(cont_blocks) >= 2:
                card.yomikata = cont_blocks[0].text
                card.meaning = cont_blocks[1].text
            cont_list_blocks = driver.find_elements(By.CLASS_NAME, "contListBlock")
            if len(cont_list_blocks) >= 2:
                card.douruigo = cont_list_blocks[1].text

            # Add card to Anki
            add_to_anki(card)

            counter += 1
            if counter >= 99999:
                break
        except NoSuchElementException:
            continue

def main():
    options = webdriver.FirefoxOptions()
    options.headless = True
    driver = webdriver.Firefox(options=options)
    counter = 0
    array = [1, 12, 14, 16, 17, 24, 28, 29, 30, 34, 35, 52, 57, 58, 59, 67, 68, 75, 80, 82, 86, 93, 97, 99, 102, 103, 105, 108, 112, 113, 114, 124, 126, 127, 129, 145, 148, 154, 156, 169, 177, 178, 182, 187, 190, 195, 197, 198, 204, 219, 226, 228, 239, 249, 255, 267, 274, 280, 281, 282, 287, 289, 311, 313, 316, 332, 375, 376, 378, 380, 390, 391, 420, 425, 451, 458, 462, 469, 475, 494, 519, 537, 547, 556, 574, 578, 597, 631, 634, 637, 639, 643, 647, 659, 662, 677, 683, 696, 697, 698, 726, 748, 750, 757, 764, 773, 775, 787, 791, 792, 794, 795, 798, 799, 801, 802, 806, 807, 808, 810, 811, 814, 823, 831, 833, 836, 841, 874, 884, 908, 918, 922, 932, 934, 970, 1004, 1015, 1018, 1019, 1020, 1021, 1023, 1024, 1026, 1036, 1044, 1054, 1055, 1065, 1066, 1067, 1071, 1072, 1078, 1087, 1099, 1101, 1104, 1109, 1119, 1121, 1140, 1143, 1144, 1150, 1151, 1154, 1219, 1221, 1223, 1224, 1225, 1232, 1264, 1267, 1270, 1271, 1278, 1280, 1281, 1283, 1295, 1308, 1309, 1320, 1322, 1324, 1326, 1328, 1329, 1332, 1337, 1343, 1344, 1366, 1369, 1376, 1384, 1385, 1429, 1430, 1431, 1432, 1436, 1437, 1446, 1461, 1496, 1542, 1544, 1555, 1560, 1570, 1584, 1586, 1587, 1591, 1592, 1594, 1597, 1599, 1604, 1606, 1609, 1615, 1616, 1617, 1619, 1621, 1630, 1633, 1634, 1641, 1667, 1683, 1695, 1698, 1700, 1706, 1707, 1710, 1711, 1714, 1719, 1724, 1733, 1741, 1744, 1746, 1749, 1753, 1770, 1806, 1846, 1870, 1879, 1901, 1903, 1911, 1913, 1918, 1922, 1923, 1964, 1978, 1986, 1992, 1998, 2003, 2010, 2011, 2015, 2017, 2018, 2023, 2025, 2028, 2037, 2039, 2043, 2044, 2046, 2048, 2060, 2065, 2069, 2074, 2087, 2088, 2094, 2100, 2101, 2102, 2110, 2111, 2113, 2122, 2125, 2147, 2149, 2152, 2160, 2161, 2214, 2218, 2219, 2232, 2237, 2238, 2246, 2257, 2258, 2296, 2396, 2443, 2479, 2480, 2514, 2553, 2556, 2557, 2558, 2564, 2567, 2579, 2581, 2583, 2591, 2593, 2597, 2599, 2607, 2614, 2621, 2623, 2642, 2644, 2645, 2656, 2666, 2670, 2680, 2698, 2708, 2720, 2725, 2734, 2736, 2738, 2774, 2791, 2806, 2812, 2813, 2835, 2844, 2847, 2848, 2862, 2863, 2871, 2949, 2980, 3007, 3049, 3051, 3068, 3069, 3072, 3073, 3074, 3075, 3114, 3120, 3122, 3136, 3143, 3145, 3160, 3176, 3198, 3200, 3222, 3224, 3249, 3262, 3274, 3285, 3336, 3429, 3452, 3457, 3468, 3477, 3479, 3485, 3489, 3510, 3630, 3639, 3649, 3650, 3651, 3657, 3659, 3666, 3740, 3751, 3776, 3813, 3824, 3826, 3827, 3828, 3834, 3845, 3902, 3958, 3963, 3979, 3987, 4029, 4039, 4042, 4044, 4052, 4072, 4093, 4095, 4106, 4127, 4147, 4149, 4150, 4151, 4165, 4180, 4188, 4191, 4192, 4194, 4199, 4206, 4210, 4212, 4214, 4224, 4227, 4232, 4234, 4240, 4263, 4274, 4283, 4289, 4310, 4337, 4339, 4352, 4354, 4356, 4422, 4426, 4440, 4468, 4488, 4525, 4526, 4527, 4535, 4537, 4540, 4543, 4545, 4547, 4548, 4549, 4552, 4578, 4601, 4603, 4607, 4608, 4609, 4623, 4624, 4626, 4627, 4629, 4640, 4643, 4646, 4656, 4657, 4662, 4676, 4679, 4681, 4699, 4709, 4749, 4758, 4787, 4840, 4870, 4880, 4904, 4906, 4915, 4916, 4921, 4923, 4924, 4930, 4934, 4949, 4950, 4958, 4974, 4978, 4979, 4991, 4992, 4993, 4997, 5006, 5025, 5031, 5038, 5042, 5048, 5049, 5053, 5061, 5067, 5072, 5077, 5079, 5083, 5089, 5097, 5102, 5111, 5113, 5114, 5115, 5145, 5148, 5161, 5162, 5167, 5169, 5172, 5178, 5179, 5181, 5186, 5187, 5188, 5190, 5193, 5211, 5217, 5224, 5230, 5234, 5241, 5242, 5245, 5246, 5247, 5251, 5255, 5257, 5259, 5260, 5262, 5263, 5264, 5266, 5267, 5271, 5273, 5278, 5287, 5289, 5295, 5300, 5306, 5307, 5312, 5343, 5347, 5348, 5354, 5356, 5377, 5390, 5392, 5413, 5428, 5446, 5448, 5449, 5450, 5457, 5464, 5478, 5483, 5492, 5495, 5498, 5507, 5509, 5516, 5518, 5520, 5522, 5526, 5527, 5530, 5532, 5533, 5536, 5539, 5543, 5567, 5571, 5574, 5578, 5582, 5595, 5667, 5673, 5676, 5681, 5683, 5684, 5692, 5709, 5723, 5733, 5742, 5744, 5745, 5746, 5759, 5760, 5763, 5771, 5777, 5778, 5783, 5791, 5828, 5851, 5878, 5901, 5918, 5958, 5965, 5967, 5971, 5991, 5995, 6012, 6026, 6027, 6029, 6073, 6097, 6122, 6124, 6130, 6133, 6137, 6148, 6212, 6234, 6236, 6250, 6272, 6277, 6284, 6288, 6298, 6300, 6301, 6304, 6305, 6310, 6313, 6314, 6331, 6335, 6338, 6343, 6347, 6349, 6359, 6368, 6370, 6371, 6373, 6376, 6382, 6385, 6389, 6392, 6396, 6398, 6399, 6400, 6405, 6406, 6407, 6408, 6414, 6424, 6426, 6432, 6434, 6451, 6453, 6454, 6457, 6462, 6471, 6473, 6485, 6487, 6490, 6492, 6521, 6522, 6523, 6525, 6526, 6527, 6528, 6548, 6549, 6560, 6568, 6570, 6574, 6576, 6577, 6584, 6586, 6597, 6598, 6611, 6619, 6645, 6646, 6649, 6663, 6664, 6665, 6666, 6672, 6674, 6677, 6678, 6680, 6681, 6682, 6683, 6689, 6697, 6698, 6708, 6714, 6715, 6717, 6724, 6727, 6730, 6733, 6739, 6741, 6748, 6749, 6751, 6763, 6764, 6790, 6801, 6802, 6803, 6816, 6818, 6819, 6820, 6822, 6828, 6839, 6846, 6850, 6851, 6852, 6853, 6858, 6861, 6863, 6864, 6865, 6866, 6878, 6882, 6885, 6886, 6899, 6901, 6903, 6910, 6931, 6952, 6957, 6959, 6961, 6962, 6963, 6964, 6965, 6966, 6989, 7001, 7010, 7016, 7017, 7021, 7027, 7031, 7044, 7045, 7062, 7070, 7111, 7115, 7202, 7204, 7206, 7216, 7226, 7234, 7246, 7261, 7265, 7268, 7270, 7283, 7289, 7297, 7298, 7299, 7302, 7304, 7308, 7309]
    scrape_data(driver, counter, array)
    driver.quit()
    print(mylist)

if __name__ == "__main__":
    main()
