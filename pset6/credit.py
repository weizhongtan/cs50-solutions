import cs50

def main():
    print("Number: ", end = "")
    
    # convert to string
    string = str(cs50.get_int())
    num = len(string)
    
    # start from second last digit
    index = num - 2
    total = 0
    
    # loop through every other digit from the end
    while (index >= 0):
        # get digit at index position of the string
        temp = 2 * int(string[index])
        
        # add the sum of its digits to total
        if (temp < 10):
            total += temp
        else:
            total += 1 + (temp % 10)
        index -= 2
    
    # loop through all the other digits and add to running total
    index = num - 1
    while (index >=0):
        total += int(string[index])
        index -= 2
    
    # checksum
    if (total % 10 == 0):
        d = int(string[:2])
        print(d)
        if ((d == 34 or d == 37) and num == 15):
            print("AMEX")
        elif (51 <= d and d <= 55 and num == 16):
            print("MASTERCARD")
        elif (int(d / 10) == 4 and (num == 13 or num == 16)):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()