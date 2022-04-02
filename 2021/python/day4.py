from dataclasses import dataclass
from itertools import chain
from functools import reduce


@dataclass
class BoardEntry:
    number: int
    called: bool

board_rows, board_cols = (5, 5)

def transpose(array_2d):
    return [list(x) for x in zip(*array_2d)]


def new_bingo_board(rows, cols):
    return [[BoardEntry(0, False) for x in range(cols)] for y in range(rows)]


def board_row_wins(row):
    return all(map(lambda entry: entry.called, row))


def bingo_board_wins(board):
    def any_row_wins(b):
        return any(map(lambda row: board_row_wins(row), b))

    if any_row_wins(board):
        return board
    else:
        transposed_board = transpose(board)
        if any_row_wins(transposed_board):
            return board
        else:
            return None


def sum_uncalled_numbers(board):
    return reduce(lambda acc, e: acc + e.number, filter(lambda e: not e.called, chain.from_iterable(board)), 0)


def read_input(board_rows, board_cols, boards):
    with open(r'../inputs/day4.txt') as input:
        bingo_calls = [int(s.strip()) for s in input.readline().split(',')]
        next(input)
        board_num = 0
        row_num = 0
        for l in input:
            row_nums = [int(s.strip()) for s in l.split()]
            if len(row_nums):
                for i, v in enumerate(row_nums):
                    boards[board_num][row_num][i].number = v
                row_num += 1
            else:
                boards.append(new_bingo_board(board_rows, board_cols))
                board_num += 1
                row_num = 0
    return bingo_calls

def process_bingo_calls(bingo_calls, boards):
    for call in bingo_calls:
        for board in boards:
            for row in board:
                for entry in row:
                    if entry.number == call:
                        entry.called = True
            winner = bingo_board_wins(board)
            if winner is not None:
                break
        if winner is not None:
            break
    if winner is not None:
        return (winner, call)
    else:
        return None

if __name__ == "__main__":
    bingo_calls = []
    boards = [new_bingo_board(board_rows, board_cols)]
    bingo_calls = read_input(board_rows, board_cols, boards)
    winner = process_bingo_calls(bingo_calls, boards)

    sum_unmarked = sum_uncalled_numbers(winner[0])
    print(sum_unmarked * winner[1])
