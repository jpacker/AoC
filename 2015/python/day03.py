from itertools import islice


def __run_instructions(the_range, visited):
    cur_pos = (0, 0)
    visited[cur_pos] = 1
    for c in the_range:
        match c:
            case "<":
                cur_pos = (cur_pos[0] - 1, cur_pos[1])
            case ">":
                cur_pos = (cur_pos[0] + 1, cur_pos[1])
            case "^":
                cur_pos = (cur_pos[0], cur_pos[1] + 1)
            case "v":
                cur_pos = (cur_pos[0], cur_pos[1] - 1)
        visited[cur_pos] = 1


def day03():
    visited = {}
    instructions = open("../inputs/day03.txt", encoding="utf-8").read().strip()
    __run_instructions(instructions, visited)

    print(f"Part 1: {len(visited)}")

    visited.clear()

    __run_instructions(islice(instructions, 0, None, 2), visited)
    __run_instructions(islice(instructions, 1, None, 2), visited)

    print(f"Part 2: {len(visited)}")
