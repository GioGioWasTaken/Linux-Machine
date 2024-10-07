# Define the ELF magic bytes
ELF_MAGIC = b'\x7FELF'

# Read the concatenated file
with open('decoded_output', 'rb') as f:
    data = f.read()

# Find the positions of the ELF magic bytes
first_elf_pos = data.find(ELF_MAGIC)
second_elf_pos = data.find(ELF_MAGIC, first_elf_pos + 1)

# If the second ELF header is found, split the files
if second_elf_pos != -1:
    # Extract the .so file (from start to the second ELF header)
    pam_passfile_so = data[first_elf_pos:second_elf_pos]
    # Extract the .o file (from the second ELF header to the end)
    pam_passfile_o = data[second_elf_pos:]

    # Write the split files
    with open('pam_passfile.so', 'wb') as f:
        f.write(pam_passfile_so)

    with open('pam_passfile.o', 'wb') as f:
        f.write(pam_passfile_o)

    print("Files split and written successfully: pam_passfile.so and pam_passfile.o.")
else:
    print("Could not find the second ELF header. Check the file format.")
