import requests
import json
from test_dict import get_word_definitions
# AnkiConnect URL
ANKI_CONNECT_URL = "http://localhost:8765"

def add_flashcard(deck_name, front, back):
    # Create a note (card) payload
    payload = {
        "action": "addNote",
        "version": 6,
        "params": {
            "note": {
                "deckName": deck_name,
                "modelName": "Basic", "fields": {
                    "Front": front,
                    "Back": back
                },
                "options": {
                    "allowDuplicate": False
                },
                "tags": ["AutoGenerated"]
            }
        }
    }

    # Make a request to AnkiConnect
    response = requests.post(ANKI_CONNECT_URL, json=payload)

    # Check if the request was successful
    if response.status_code == 200:
        print("Flashcard added successfully!")
    else:
        print("Failed to add flashcard:", response.text)

def main():
    # Open the JSON file for reading
    with open('extracted_values.json', 'r') as file:
    # Iterate over each line in the file
        characters_to_remove ='",'
        for line in file:
            # Strip whitespace and newline characters from the line
            line = line.strip()
            for char in characters_to_remove:
                line = line.replace(char,'')
            # Check if the line is not empty
            if line:
                print(line)
                # print(get_word_definitions(line),type(get_word_definitions(line)))
                add_flashcard("psychometry_deck",line,get_word_definitions(line))
if __name__ == "__main__":
    main()