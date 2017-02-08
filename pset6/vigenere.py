import cs50
import sys

def main():
    # reject incorrect usage
    if len(sys.argv) != 2 or not sys.argv[1].isalpha():
        print("Usage: python vigenere.py alphabetical_key")
        return 1
    
    # save key
    key = sys.argv[1].upper()
    
    # get input from user
    print("plaintext: ", end="")
    text = cs50.get_string()
    
    cipher = ""
    i = 0
    for char in text:
        # only apply to alphabetical characters
        if char.isalpha():
            # find the letter from the key that needs to be used
            change = ord(key[i % len(key)]) - 65
            
            # generate new character using key letter
            # treat uppercase and lowercase differently
            if ord(char) > 90:
                new_char = chr(((ord(char) + change - 97) % 26) + 97)
                cipher += new_char
            else:
                new_char = chr(((ord(char) + change - 65) % 26) + 65)
                cipher += new_char
            
            # only increment when a letter has been processed
            i += 1
        # otherwise just add the character to the returned cipher
        else:
            cipher += char
    
    print(cipher)

if __name__ == "__main__":
    main()