#!/usr/bin/env python3
import sys
from lexer import Lexer
from parser import Parser
from evaluator import monkey_eval, Environment


def run(source: str, env: Environment):
    lexer = Lexer(source)
    parser = Parser(lexer)
    program = parser.parse_program()

    if parser.errors:
        for err in parser.errors:
            print(f"  parser error: {err}")
        return None

    result = monkey_eval(program, env)
    return result


def repl():
    print("Monkey lang REPL  (type 'exit' to quit)")
    env = Environment()

    while True:
        try:
            line = input(">> ")
        except (EOFError, KeyboardInterrupt):
            print()
            break

        if line.strip() in ("exit", "quit"):
            break
        if not line.strip():
            continue

        result = run(line, env)
        if result is not None:
            print(result)


def run_file(path: str):
    with open(path) as f:
        source = f.read()
    env = Environment()
    result = run(source, env)
    if result is not None and str(result) != "null":
        print(result)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        run_file(sys.argv[1])
    else:
        repl()
