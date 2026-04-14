#include "environment.h"
#include "evaluator.h"
#include "lexer.h"
#include "object.h"
#include "parser.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

static void printErrors(const Parser& p) {
  for (const auto& e : p.errors()) {
    std::cerr << "parse error: " << e << "\n";
  }
}

static void evalProgram(std::shared_ptr<Environment> env,
                        std::vector<std::unique_ptr<Program>>& program_storage, std::unique_ptr<Program> program,
                        bool printExprResult) {
  if (!program) {
    return;
  }
  program_storage.push_back(std::move(program));
  Program* prog = program_storage.back().get();
  try {
    Evaluator eval(prog);
    Value v = eval.eval(env);
    if (printExprResult && prog->statements.size() == 1 &&
        dynamic_cast<ExpressionStatementStmt*>(prog->statements[0].get())) {
      if (v.kind != Value::Kind::Null) {
        std::cout << v.inspect() << "\n";
      }
    }
  } catch (const std::exception& ex) {
    std::cerr << "runtime error: " << ex.what() << "\n";
  }
}

int main(int argc, char** argv) {
  auto env = std::make_shared<Environment>();
  std::vector<std::unique_ptr<Program>> program_storage;

  if (argc > 1) {
    std::ifstream f(argv[1]);
    if (!f) {
      std::cerr << "cannot open " << argv[1] << "\n";
      return 1;
    }
    std::ostringstream ss;
    ss << f.rdbuf();
    std::string source = ss.str();
    Lexer lexer(std::move(source));
    Parser parser(std::move(lexer));
    std::unique_ptr<Program> program = parser.parseProgram();
    if (!parser.errors().empty()) {
      printErrors(parser);
      return 1;
    }
    evalProgram(env, program_storage, std::move(program), true);
    return 0;
  }

  std::cout << "AdLang-style REPL (cpp). Try: let add = fn(a,b) { return a + b; }; add(3, 4);\n";
  std::cout << "Arrays/builtins: let a = [1,2,3]; puts(len(a));\n";
  std::cout << "Threads: let t = spawn(fn() { return 42; }); join(t);\n";
  std::cout << "Classes: class Counter { fn init(n) { this.count = n; } fn bump() { this.count = this.count + 1; } }; let c = new Counter(0); c.bump(); c.count;\n";
  std::cout << "Type :quit to exit.\n";

  std::string line;
  while (true) {
    std::cout << ">> ";
    if (!std::getline(std::cin, line)) {
      break;
    }
    if (line == ":quit" || line == ":q") {
      break;
    }
    if (line.empty()) {
      continue;
    }

    Lexer lexer(std::move(line));
    Parser parser(std::move(lexer));
    std::unique_ptr<Program> program = parser.parseProgram();
    if (!parser.errors().empty()) {
      printErrors(parser);
      continue;
    }
    evalProgram(env, program_storage, std::move(program), true);
  }

  return 0;
}
