from itertools import accumulate

def day01():
    input: str = open('../inputs/day01.txt', encoding='utf-8').read().strip()
    nums = [1 if c == '(' else -1 for c in input]
    print(f"Part 1: {sum(nums)}")
    print(f"Part 2: {next(i for i, s in enumerate(accumulate(nums)) if s == -1) + 1}")