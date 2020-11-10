procs = [8, 4, 2, 1, 8]

while len(procs) > 0:

    curr = procs.pop(0)
    curr -= 1
    if curr != 0:
        procs.append(curr)

    print(procs)