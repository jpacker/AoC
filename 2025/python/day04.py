from dataclasses import dataclass


type Grid = list[str]


@dataclass
class Position:
    x: int
    y: int


@dataclass
class Solution:
    number: int
    positions: list[Position]


def count_rolls_in_adjacent(x: int, y: int, grid: Grid) -> int:
    min_x = max(0, x - 1)
    max_x = min(len(grid[0]), x + 1)
    min_y = max(0, y - 1)
    max_y = min(len(grid), y + 1)
    slices = [row[min_x : max_x + 1] for row in grid[min_y : max_y + 1]]
    num_at = 0
    num_at += sum([l.count("@") for l in slices])  # noqa: E741
    return num_at - 1


def part1(input: list[str]):
    sol = Solution(0, [])
    for y, row in enumerate(input):
        for x, column in enumerate(row):
            if column != "@":
                continue

            num_rolls = count_rolls_in_adjacent(x, y, input)
            if num_rolls < 4:
                sol.positions.append(Position(x, y))
                sol.number += 1

    return sol


def part2(input: list[str]):
    local_input = input.copy()
    total = 0
    while True:
        sol = part1(local_input)
        total += sol.number
        if len(sol.positions) == 0:
            break

        for pos in sol.positions:
            local_input[pos.y] = (
                f"{local_input[pos.y][: pos.x]}X{local_input[pos.y][pos.x + 1 :]}"
            )

    return total


def main():
    with open("../inputs/day04.txt") as f:
        input = f.readlines()
        p1 = part1(input).number
        p2 = part2(input)
        print(f"Day 4:\n\tPart 1: {p1}\n\tPart 2: {p2}")


if __name__ == """__main__""":
    main()
