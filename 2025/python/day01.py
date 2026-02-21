def part1(input: list[str]) -> int:
    num_zeros: int = 0
    dial = 50
    for line in input:
        num = int(line[1:])
        match line[0]:
            case "R":
                dial = (dial + num) % 100
            case "L":
                dial = (dial - num) % 100
            case _:
                raise Exception("Bad prefix")
        if dial == 0:
            num_zeros += 1
    return num_zeros


def part2(input: list[str]) -> int:
    # There is math for this, but why figure it out?
    num_passed_zero: int = 0
    dial = 50
    for line in input:
        num = int(line[1:])
        match line[0]:
            case "R":
                dial = dial + num
            case "L":
                dial = dial - num
            case _:
                raise Exception("Bad prefix")
        dir = -1 if dial > 99 else 1
        while dial < 0 or dial > 99:
            dial = dial + (100 * dir)
            num_passed_zero += 1
    return num_passed_zero


def main():
    with open("../inputs/day01.txt") as f:
        input = f.readlines()
        p1 = part1(input)
        p2 = part2(input)
        print(f"Day 1:\n\tPart 1: {p1}\n\tPart 2: {p2}")


if __name__ == """__main__""":
    main()
