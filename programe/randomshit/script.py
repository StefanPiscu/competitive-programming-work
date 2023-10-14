f=open("text.txt", "r")
lines=f.readlines()

for line in lines:
    if line[0] != ".": continue
    print(line.split("\\")[-1].split(".")[0])