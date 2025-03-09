def rle(string: str) -> str:
    i = 0
    output: str = ""
    while i < len(string):
        c = string[i]
        count = 1
        i += 1
        while i < len(string) and c == string[i]:
            i += 1
            count += 1
        output += f"{count}{c}"
    return output


def day10():
    input = "3113322113"
    tmp = input
    for i in range(50):
        tmp = rle(tmp)
        if i == 39:
            p1 = len(tmp)
    print(f"Part 1: {p1}")
    print(f"Part 2: {len(tmp)}")
