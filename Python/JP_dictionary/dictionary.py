import pickle
import sys
import os

def contains_english(text):
    # Define the Unicode range for English characters
    english_range = range(0x0041, 0x007B)  # Includes A-Z, a-z, and common punctuation
    
    # Check each character in the input text
    for char in text:
        if ord(char) in english_range:
            return True
    return False

def load_dictionary(lang):
    # Get the directory path of the script
    script_dir = os.path.dirname(os.path.realpath(__file__))
    
    if lang == 'jp':
        # Construct the absolute path to jp_dictionary.pkl
        pkl_file = os.path.join(script_dir, 'jp_dictionary.pkl')
    else:
        # Construct the absolute path to en_dictionary.pkl
        pkl_file = os.path.join(script_dir, 'en_dictionary.pkl')

    try:
        # Try to load the preprocessed dictionary from disk
        with open(pkl_file, 'rb') as f:
            dictionary = pickle.load(f)
    except FileNotFoundError:
        raise Exception("Dictionary file not found error!")

    return dictionary

def lookup_word(word, dictionary):
    entry = dictionary.get(word)
    if entry:
        return entry['reading'], entry['meaning']
    else:
        return None, None

def main():
    if len(sys.argv) < 2:
        print("Usage: python script.py <word>")
        return
    
    word = sys.argv[1]

    if contains_english(word):
        lang = 'en'
    else:
        lang = 'jp'

    # Load dictionary into memory based on detected language
    dictionary = load_dictionary(lang)
    
    reading, meaning = lookup_word(word, dictionary)
    if reading and meaning:
        print("Reading:", reading)
        print("Meaning:", meaning)
    else:
        print("Word not found in dictionary.")

if __name__ == "__main__":
    main()
