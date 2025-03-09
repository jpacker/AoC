def day08():
    lines = open("../inputs/day08.txt", encoding="utf-8").read().strip().splitlines()
    # cheating for part 1 :) by using eval
    # and then do it for real
    p1_eval_solution = 0
    p2_solution = 0
    for line in lines:
        code_length = len(line)
        memory_length = eval(f"len(b{line})")
        p1_eval_solution += code_length - memory_length
        line = line.replace("\\", "\\\\")
        line = line.replace('"', '\\"')
        encoded_length = len(line)
        p2_solution += encoded_length - code_length + 2

    print(f"Part 1: {p1_eval_solution}")
    print(f"Part 2: {p2_solution}")
