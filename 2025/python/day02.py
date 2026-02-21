import re


def calc(input: list[str], regex: re.Pattern[str]):
    sum = 0
    for id_range in input:
        lower, upper = (int(x) for x in id_range.split("-"))
        for i in range(lower, upper + 1):
            match = regex.match(str(i))
            if match:
                sum += i
    return sum


def part1(input: list[str]):
    repeated = re.compile("^(\\d+)\\1$")
    return calc(input, repeated)


def part2(input: list[str]):
    repeated = re.compile("^(\\d+)\\1+$")
    return calc(input, repeated)


def main():
    with open("../inputs/day02.txt") as f:
        input = f.readlines()
        input = input[0].split(",")
        p1 = part1(input)
        p2 = part2(input)
        print(f"Day 2:\n\tPart 1: {p1}\n\tPart 2: {p2}")


if __name__ == """__main__""":
    main()
