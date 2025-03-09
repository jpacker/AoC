from itertools import pairwise
from re import search


def day05():
    # must contain 3 vowels
    vowels = ["a", "e", "i", "o", "u"]
    # check naughty first since they contain vowel
    naughty = ["ab", "cd", "pq", "xy"]
    # third nice condition is containing double letters

    def nice_p1(line: str):
        is_nice = all(line.find(naught) == -1 for naught in naughty)
        is_nice = is_nice and sum(line.count(vowel) for vowel in vowels) >= 3
        is_nice = is_nice and any(a == b for a, b in pairwise(line))
        return is_nice

    def nice_p2(line: str):
        has_pair = search(r"(..).*\1", line) is not None
        is_nice = has_pair and search(r"(.).\1", line) is not None
        return is_nice

    lines = open("../inputs/day05.txt", encoding="utf-8").read().strip().splitlines()

    num_nice_p1 = sum(1 for line in lines if nice_p1(line))
    num_nice_p2 = sum(1 for line in lines if nice_p2(line))

    print(f"Part 1: {num_nice_p1}")
    print(f"Part 2: {num_nice_p2}")
