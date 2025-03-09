from itertools import permutations
from operator import gt, lt


def parse_input(input_str: str):
    distances = {}
    for line in input_str.strip().splitlines():
        parts = line.split()
        city1, city2 = parts[0], parts[2]
        distance = int(parts[4])
        distances.setdefault(city1, {})[city2] = distance
        distances.setdefault(city2, {})[city1] = distance
    return distances


def calculate_total_distance(route, distances) -> int:
    total_distance = 0
    for i in range(len(route) - 1):
        total_distance += distances[route[i]][route[i + 1]]
    return total_distance


def find_route(distances, comp):
    cities = list(distances.keys())
    shortest_distance = 10_000 if comp is lt else 0
    shortest_route = None
    for route in permutations(cities):
        current_distance = calculate_total_distance(route, distances)
        if comp(current_distance, shortest_distance):
            shortest_distance = current_distance
            shortest_route = route
    return shortest_route, shortest_distance


def day09():
    input = open("../inputs/day09.txt", encoding="utf-8").read()
    distances = parse_input(input)
    _, shortest_distance = find_route(distances, lt)
    _, longest_distance = find_route(distances, gt)
    print(f"Part 1: {shortest_distance}")
    print(f"Part 2: {longest_distance}")
