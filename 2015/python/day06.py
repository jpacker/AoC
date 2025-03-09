import numpy as np
import re


def day06():
    light_mat_p1 = np.zeros((1000, 1000), np.bool)
    light_mat_p2 = np.zeros((1000, 1000), np.int32)
    lines = open("../inputs/day06.txt", encoding="utf-8").read().splitlines()
    pattern = re.compile(r"(toggle|turn off|turn on) (\d+),(\d+) through (\d+),(\d+)")
    for line in lines:
        pat_match = pattern.match(line)
        action, x1, y1, x2, y2 = pat_match.groups()
        x1, y1, x2, y2 = map(int, [x1, y1, x2, y2])
        ref_mat_p1 = light_mat_p1[y1 : y2 + 1, x1 : x2 + 1]
        ref_mat_p2 = light_mat_p2[y1 : y2 + 1, x1 : x2 + 1]
        match action:
            case "turn on":
                ref_mat_p1[:, :] = True
                ref_mat_p2[:, :] += 1
            case "turn off":
                ref_mat_p1[:, :] = False
                ref_mat_p2[:, :] -= 1
                ref_mat_p2[ref_mat_p2 < 0] = 0
            case "toggle":
                np.bitwise_not(
                    ref_mat_p1,
                    out=ref_mat_p1,
                )
                ref_mat_p2[:, :] += 2
    print(f"Part 1: {np.count_nonzero(light_mat_p1)}")
    print(f"Part 2: {np.sum(light_mat_p2)}")
