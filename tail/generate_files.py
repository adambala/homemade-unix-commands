from random import randint

n_files = int(input("Number of files: "))
n = int(input("Number of lines: "))
raw = input("Numbers from _ to _ (separated by space): ")
start, finish = map(int, raw.split())

for i in range(1, n_files + 1):
    with open(f"file{i}.txt", "w") as file:
        for j in range(n):
            file.write(f"{randint(start, finish)}" + "\n")

    