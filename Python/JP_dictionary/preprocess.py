import pickle
import xml.etree.ElementTree as ET
def preprocess_dictionary():
    dictionary = {}
    tree = ET.parse('JMdict_e.xml')
    root = tree.getroot()

    for entry in root.findall('entry'):
        kanji_elements = entry.findall('./k_ele/keb')
        if not kanji_elements:
            continue

        kanji = kanji_elements[0].text
        reading = entry.find('./r_ele/reb').text
        meaning = entry.find('./sense/gloss').text
        dictionary[kanji] = {'reading': reading, 'meaning': meaning}
    print("Dictionary saved")
    # Serialize and save the dictionary to disk
    with open('dictionary.pkl', 'wb') as f:
        pickle.dump(dictionary, f)



preprocess_dictionary()

