from dataclasses import dataclass
from itertools import chain, compress
from operator import not_
from time import perf_counter_ns


@dataclass
class Board:
    numbers: list[list[int]]
    called: list[list[bool]]


def new_bingo_board(rows, cols):
    return Board(
        [[] for y in range(rows)],
        [[False for x in range(cols)] for y in range(rows)]
    )
         

def bingo_board_wins(board: Board):
    for row in board.called:
        if all(row):
            return True
    for col in zip(*board.called):
        if all(col):
            return True
    return False


def sum_uncalled_numbers(board: list[Board]):
    return sum(compress(chain.from_iterable(board.numbers), map(not_, chain.from_iterable(board.called))))


def read_input(board_rows: int, board_cols: int, boards : list[Board]):
    with open(r'../inputs/day4.txt') as input:
        bingo_calls = [int(s.strip()) for s in input.readline().split(',')]
        next(input)
        board_num = 0
        row_num = 0
        for l in input:
            row_nums = [int(s.strip()) for s in l.split()]
            if len(row_nums):
                boards[board_num].numbers[row_num] = row_nums.copy()
                row_num += 1
            else:
                boards.append(new_bingo_board(board_rows, board_cols))
                board_num += 1
                row_num = 0
    return bingo_calls


def process_bingo_calls(bingo_calls, boards: list[Board]):
    for call in bingo_calls:
        for board in boards:
            for r, row in enumerate(board.numbers):
                for i, number in enumerate(row):
                    if number == call:
                        board.called[r][i] = True
            if bingo_board_wins(board):
                return (board, call)
    return None


def day1():
    board_rows, board_cols = (5, 5)
    start = perf_counter_ns()
    bingo_calls = []
    boards = [new_bingo_board(board_rows, board_cols)]
    bingo_calls = read_input(board_rows, board_cols, boards)
    winner = process_bingo_calls(bingo_calls, boards)
    sum_unmarked = sum_uncalled_numbers(winner[0])
    end = perf_counter_ns()
    print(f'{(end - start)/1000} usecs')
    print(sum_unmarked * winner[1])


if __name__ == "__main__":
    day1()
