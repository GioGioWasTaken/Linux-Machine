import nltk
from nltk.corpus import wordnet

# Download the WordNet corpus (if not already downloaded)
nltk.download('wordnet')

def get_word_definitions(word):
    # Get synsets (sets of synonyms) for the word
    synsets = wordnet.synsets(word)

    # Check if any synsets were found
    if synsets:
        definitions_string=""
        # Get the definitions of all synsets
        definitions = [synset.definition() for synset in synsets]
        for index, definition in enumerate(definitions):
            definitions_string +=f"{index + 1}. {definition}<br>"
        return definitions_string  # Strip trailing newline
    else:
        return ["No definition found for the word '{}'.".format(word)]

# Example word
word = "table"

if __name__ == "__main__":
    get_word_definitions(word)
