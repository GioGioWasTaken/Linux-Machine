import sys

def is_ascii(byte):
    return 0x20 <= byte <= 0x7F

def main():
    if(len(sys.argv) <2):
        print(f"usage python {sys.argv[0]} <ascii_num>")
        exit(1)
    # Input string with ASCII number
    input_hex = sys.argv[1]# Change this to test different inputs

    # Convert input hex string to an integer
    number = int(input_hex, 16)

    # Add 0x5555e000
    result = number + 0x5555e000

    # Convert result to bytes
    result_bytes = result.to_bytes((result.bit_length() + 7) // 8, byteorder='big')

    if all(is_ascii(byte) for byte in result_bytes):
        print(f"Received value: {hex(result)}")  # Print the result in hexadecimal format

if __name__ == "__main__":
    main()
