from functools import reduce
from operator import mul


def day02():
    lines = open("../inputs/day02.txt", encoding="utf-8").read().strip().splitlines()
    measurements = [sorted(map(int, x.split("x"))) for x in lines]
    part1 = sum(
        2 * sides[0] * sides[1]
        + 2 * sides[1] * sides[2]
        + 2 * sides[2] * sides[0]
        + sides[0] * sides[1]
        for sides in measurements
    )
    part2 = sum(
        sides[0] * 2 + sides[1] * 2 + reduce(mul, sides) for sides in measurements
    )
    print(f"Part 1: {part1}")
    print(f"Part 2: {part2}")
