from cryptography.fernet import Fernet

# Generate a key for encryption
key = Fernet.generate_key()

# Create a Fernet object using the key
fernet = Fernet(key)

print("Key : " + str(key))
print("fernet : "+ str(fernet))

# Maximum text length allowed
max_text_length = 1024

def read_text(max_text_length):
    text = []
    print("Enter a multiline text (press Enter twice to finish):")

    while True:
        line = input()

        # Check if the input is two consecutive newlines (an empty line)
        if len(line) == 0 and len(text) > 0 and text[-1] == '\n':
            break
        
        # Add the line to the text list
        text.append(line + '\n')

        # Check if the buffer is full
        if len(''.join(text)) >= max_text_length - 1:
            print("Text limit reached. Press Enter to finish.")
            break

    return ''.join(text)

def write_file(file, max_text_length):
    content = read_text(max_text_length)
    file.write(content + "\n")

def encrypt_file(file_name):
    # Open the file in read mode to read its contents
    with open(file_name, 'r') as file:
        file_content = file.read()

    # Encrypt the file content using Fernet
    encrypted_content = fernet.encrypt(file_content.encode()).decode()

    # Open the file in write mode to overwrite with the encrypted content
    with open(file_name, 'w+') as file:
        file.write(encrypted_content)
        file.seek(0)  
        content = file.read()  
        print(content) 
        

    print("File has been encrypted successfully.")


def decrypt_file(file_name):
    try:
        # Open the file in read mode to get the encrypted content
        with open(file_name, 'r') as file:
            file_content = file.read()

        # Decrypt the file content using Fernet
        decrypted_content = fernet.decrypt(file_content.encode()).decode()

        # Open the file in write mode to overwrite with the decrypted content
        with open(file_name, 'w') as file:
            file.write(decrypted_content)

        print("File has been decrypted successfully.")
        print("Decrypted content:\n", decrypted_content)

    except Exception as e:
        print(f"An error occurred during decryption: {e}")
  

file_name = input("Enter the file name to encrypt : ")

with open(file_name,"w+") as file:
    write_file(file,max_text_length)  
    file.seek(0) 
    
encrypt_file(file_name)
decrypt_file(file_name)
