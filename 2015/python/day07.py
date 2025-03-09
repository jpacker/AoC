from dataclasses import dataclass
from enum import Enum
from operator import and_, or_, lshift, rshift
import re

# This is a little verbose. You could do a trick where all
# the strings have their ops rewritten to python code
# and sorting the outputs by length and then lexicographically
# then have python evaluate it


class BinaryOperation(Enum):
    UNKNOWN = 0
    AND = 1
    OR = 2
    LSHIFT = 3
    RSHIFT = 4


class UnaryOperation(Enum):
    NOT = 5
    ASSIGN = 6


@dataclass
class UnaryOp:
    operation: UnaryOperation
    op1: str
    result: str


@dataclass
class BinaryOp:
    op1: str
    operation: BinaryOperation
    op2: str
    result: str


type Instruction = UnaryOp | BinaryOp


def parseNot(lineDict) -> Instruction:
    return UnaryOp(UnaryOperation.NOT, lineDict["op1"], lineDict["result"])


def parseBinaryOp(lineDict) -> Instruction:
    operator = BinaryOperation.UNKNOWN
    match lineDict["operator"]:
        case "AND":
            operator = BinaryOperation.AND
        case "OR":
            operator = BinaryOperation.OR
        case "LSHIFT":
            operator = BinaryOperation.LSHIFT
        case "RSHIFT":
            operator = BinaryOperation.RSHIFT

    return BinaryOp(lineDict["op1"], operator, lineDict["op2"], lineDict["result"])


def parseAssignment(lineDict) -> Instruction:
    return UnaryOp(UnaryOperation.ASSIGN, lineDict["op1"], lineDict["result"])


def parse(lineDict) -> Instruction:
    if lineDict["notop"]:
        return parseNot(lineDict)
    elif lineDict["operator"]:
        return parseBinaryOp(lineDict)
    else:
        return parseAssignment(lineDict)


def run_not_op(inst: Instruction, variables: dict[str:int]):
    if inst.operation == UnaryOperation.NOT and inst.op1 in variables:
        variables[inst.result] = ~variables[inst.op1]
        variables[inst.result] = variables[inst.result] & 0xFFFF
        return True

    return False


def run_assign_op(inst: Instruction, variables: dict[str:int]):
    if inst.operation == UnaryOperation.ASSIGN and inst.op1 in variables:
        variables[inst.result] = variables[inst.op1]
        variables[inst.result] = variables[inst.result] & 0xFFFF
        return True

    return False


operators = [and_, or_, lshift, rshift]


def run_binary_op(inst: Instruction, variables: dict[str:int]):
    if type(inst) is BinaryOp:
        op = operators[inst.operation.value - 1]
        op1_value = -1
        op2_value = -1
        if inst.op1 in variables:
            op1_value = variables[inst.op1]
        elif inst.op1.isdigit():
            op1_value = int(inst.op1)
        else:
            return False
        if inst.op2 in variables:
            op2_value = variables[inst.op2]
        elif inst.op2.isdigit():
            op2_value = int(inst.op2)
        else:
            return False

        variables[inst.result] = op(op1_value, op2_value)
        variables[inst.result] = variables[inst.result] & 0xFFFF
        return True

    return False


def run_sim(instructions, variables):
    # cheating here since a is only assigned once
    while "a" not in variables:
        for inst in instructions:
            if run_not_op(inst, variables):
                continue
            elif run_assign_op(inst, variables):
                continue
            else:
                run_binary_op(inst, variables)


def day07():
    regex = re.compile(
        r"(?P<notop>NOT)?[\s]?(?P<op1>\w+)[\s]?(?P<operator>AND|OR|LSHIFT|RSHIFT)?[\s]?(?P<op2>\w+)?[\s]?-> (?P<result>\w+)"
    )

    lines = open("../inputs/day07.txt", encoding="utf-8").read().strip().splitlines()

    instructions = []
    for line in lines:
        matches = regex.match(line)
        instructions.append(parse(matches.groupdict()))

    variables: dict[str:int] = {
        inst.result: int(inst.op1)
        for inst in instructions
        if inst.operation == UnaryOperation.ASSIGN and inst.op1.isdigit()
    }

    instructions_filtered = [
        inst
        for inst in instructions
        if inst.operation != UnaryOperation.ASSIGN or inst.op1.isalpha()
    ]

    run_sim(instructions_filtered, variables)

    a_val = variables["a"]
    print(f"Part 1: {a_val}")

    variables.clear()
    variables = {
        inst.result: int(inst.op1)
        for inst in instructions
        if inst.operation == UnaryOperation.ASSIGN and inst.op1.isdigit()
    }
    variables["b"] = a_val

    run_sim(instructions_filtered, variables)

    a_val = variables["a"]
    print(f"Part 1: {a_val}")
