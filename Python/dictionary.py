import pickle
import sys
import os

def load_dictionary():
    # Get the directory path of the script
    script_dir = os.path.dirname(os.path.realpath(__file__))
    
    # Construct the absolute path to dictionary.pkl
    pkl_file = os.path.join(script_dir, 'dictionary.pkl')
    
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
    # Load dictionary into memory
    dictionary = load_dictionary()
    if len(sys.argv) < 2:
        print("Usage: python script.py <argument>")
        return
    word = sys.argv[1]

    reading, meaning = lookup_word(word, dictionary)
    if reading and meaning:
        print("Reading:", reading)
        print("Meaning:", meaning)
    else:
        print("Word not found in dictionary.")
    return

if __name__ == "__main__":
    main()
