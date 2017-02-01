import cs50

h = -1
while (h < 0 or h > 23):
    print("Height: ", end = "")
    h = cs50.get_int()
    
for i in range(h):
    line = ""
    for j in range(h-i-1):
        line += " "
    for j in range(i+1):
        line += "#"
    line += "  "
    for j in range(i+1):
        line += "#"
    print(line)
