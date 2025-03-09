from hashlib import md5


def __solve(num_zeroes, input):
    key_md5 = md5(input.encode("ascii"))
    index = 1
    target = "0" * num_zeroes
    while True:
        my_hash = key_md5.copy()
        my_hash.update(str(index).encode("ascii"))
        if my_hash.hexdigest().startswith(target):
            break
        index += 1
    return index


def day04():
    input = "ckczppom"
    part1_val = __solve(5, input)
    part2_val = __solve(6, input)
    print(f"Part 1: {part1_val}")
    print(f"Part 2: {part2_val}")
