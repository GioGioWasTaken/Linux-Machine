import sys

# Generate the first 64 arguments as 'A'
args = ['A'] * 64

# Append the 65th and 66th arguments as bytes
args.append("$'\0'")
args.append("$' \n\r'")

for i in range(34):
    args.append('A')

# Print the generated arguments list
print(' '.join(args))
