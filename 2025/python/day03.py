def solve(input: list[str], num_digits: int):
    sum = 0
    for line in input:
        l = line.strip()
        num_voltages = len(l)
        num = ""
        cur_pos = 0
        for i in range(num_digits - 1, -1, -1):
            prev_cur_pos = cur_pos
            cur_pos, max_digit = max(
                enumerate(l[cur_pos : num_voltages - i]), key=lambda x: x[1]
            )
            cur_pos += prev_cur_pos + 1
            num += max_digit
        sum += int(num)
    return sum


def part1(input: list[str]):
    return solve(input, 2)


def part2(input: list[str]):
    return solve(input, 12)


def main():
    with open("../inputs/day03.txt") as f:
        input = f.readlines()
        p1 = part1(input)
        p2 = part2(input)
        print(f"Day 3:\n\tPart 1: {p1}\n\tPart 2: {p2}")


if __name__ == """__main__""":
    main()
