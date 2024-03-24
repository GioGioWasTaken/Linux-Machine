grep -v '^words_options' non-advanced.txt > modified_words.js
rm psychometry_words.txt
prepend_text="
const fs = require('fs');
var words=new Array;"

append_text="
var extractedValues = [];

for (var i = 0; i < words.length; i++) {
    extractedValues.push(words[i][1]);
}

var jsonData = JSON.stringify(extractedValues, null, 2);

fs.writeFileSync('extracted_values.json', jsonData);

console.log('Data written to extracted_values.json');
"

# Name of the original file
original_file="modified_words.js"

# Create a temporary file
temp_file=$(mktemp)

# Write the text to prepend to the temporary file
echo "$prepend_text" > "$temp_file"

# Append the content of the original file to the temporary file
cat "$original_file" >> "$temp_file"

# Overwrite the original file with the contents of the temporary file
mv "$temp_file" "$original_file"

# Remove the temporary file
rm "$temp_file"

echo $append_text >> $original_file
node modified_words.js
#rm modified_words.js
python3 anki_api.py
