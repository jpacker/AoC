from argparse import ArgumentParser
from runpy import run_path

parser = ArgumentParser(
    prog="Advent of Code 2015",
    description="Solve all days of AoC 2015 a selective day.",
)

parser.add_argument("-d", "--day", type=int)
args = parser.parse_args()

if args.day is None:
    day_mods = {}

    for i in range(10):
        day_str = f"day{i + 1:02}"
        day_mods[day_str] = run_path(f"{day_str}.py")

    for day, mod in day_mods.items():
        print(f"\nDay {day[3:]}:")
        mod[day]()
else:
    day_str = f"day{args.day:02}"
    mod = run_path(f"{day_str}.py")
    print(f"\nDay {day_str[3:]}:")
    mod[day_str]()
