# TIPS - A Modified Pascal Language

A compiler/interpreter implementation for **TIPS**, a simplified Pascal-like programming language. The project is built incrementally across four parts: lexical analysis, parsing, parse tree generation, and interpretation.

## Prerequisites

- **Flex** (lexical analyzer generator)
- **G++** (C++ compiler)
- **Make**

## Project Structure

```
Part_1_Canvas_Files/   - Part 1: Lexical Analyzer
Part-2-Canvas_Files/   - Part 2: Parser
Part-3-Canvas_Files/   - Part 3: Parse Tree Generation
Part-4-Canvas_Files/   - Part 4: Interpreter
```

## Parts Overview

### Part 1 - Lexical Analyzer

Tokenizes TIPS source code into a stream of tokens (keywords, operators, identifiers, literals, etc.) using Flex.

```bash
cd Part_1_Canvas_Files/Part_1_Canvas_Files/Part_1_Starting_Point
make
./tips_lex < sample.pas
```

### Part 2 - Parser

Validates TIPS program syntax against the grammar rules and produces a symbol table of declared variables.

```bash
cd Part-2-Canvas_Files/Part-2-Canvas_Files/Part-2-Starting_Point
make
./tips_parse sample.pas
```

### Part 3 - Parse Tree Generation

Extends the parser to construct an Abstract Syntax Tree (AST) and provides options to visualize it.

```bash
cd Part-3-Canvas_Files/Part-3-Canvas_Files/Part-3
make
./tips_parse sample.pas
```

**Flags:**
- `-p` - Print while parsing
- `-t` - Print the parse tree
- `-d` - Print while deleting the parse tree

### Part 4 - Interpreter

Executes TIPS programs by traversing and interpreting the parse tree. Supports variable assignment, arithmetic, control flow, and I/O.

```bash
cd Part-4-Canvas_Files/Part-4
make
./tips_parse sample.pas
```

**Flags:**
- `-p` - Print while parsing
- `-t` - Print the parse tree
- `-s` - Print the symbol table (with variable values after execution)
- `-d` - Print while deleting the parse tree

## TIPS Language Features

- **Keywords:** `BEGIN`, `END`, `IF`, `THEN`, `ELSE`, `WHILE`, `FOR`, `TO`, `DOWNTO`, `READ`, `WRITE`, `VAR`, `PROGRAM`, `LET`, `BREAK`, `CONTINUE`
- **Data types:** `INTEGER`, `REAL`
- **Operators:** `+`, `-`, `*`, `/`, `:=`, `=`, `<>`, `<`, `>`, `MOD`, `AND`, `OR`, `NOT`
- **Literals:** integers, floats, strings, identifiers (uppercase, max 8 chars)
- **Comments:** enclosed in `{ }` (single-line)

## Test Cases

Each part includes `.pas` test files with corresponding `.correct` expected output files. To run a test:

```bash
./tips_parse testfile.pas
```

Compare output against the `.correct` file to verify correctness.
