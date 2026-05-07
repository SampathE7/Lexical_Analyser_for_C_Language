# Lexical_Analyser_for_C_Language
A Lexical Analyzer (Tokenizer) for the C programming language written in C.

This project reads a C source file character by character and converts it into a sequence of tokens such as:

- Keywords
- Identifiers
- Numbers (Decimal, Float, Hexadecimal, Octal, Binary)
- Operators
- Symbols
- String Literals

The analyzer also:
- Ignores comments
- Ignores preprocessor directives
- Detects lexical and syntax-related errors
- Validates brackets and semicolons

---

## Features

### Supported Tokens
- C Keywords
- Identifiers
- Numeric Constants
- String Literals
- Operators
- Symbols

### Supported Numeric Formats
- Decimal
- Floating Point
- Hexadecimal
- Octal
- Binary

### Error Detection
- Invalid identifiers
- Invalid numeric constants
- Unterminated comments
- Missing semicolons
- Unmatched brackets
- Missing string termination

---

## Compilation
gcc main.c helper.c -o lex
./lex sample.c
