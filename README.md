# Lexical_Analyser_for_C_Language
DESCRIPTION:
This project implements a Lexical Analyzer (Tokenizer) for the C programming language. The lexical analyzer reads a C source file character by character and converts it into a sequence of tokens such as:
-Keywords
-Identifiers
-Numbers (integer & floating-point)
-Operators (single and multi-character)
-Symbols
-String literals
It also ignores comments and preprocessor directives, as they are not required for syntax analysis.

OBJECTIVE:
-To understand compiler front-end design
-To practice safe, embedded-friendly C programming

SCOPE:
✔ C keywords
✔ Identifiers
✔ Numbers (10, 3.14)
✔ Operators (+, +=, ==, >>)
✔ Symbols ({ } ( ) ;)
✔ Strings ("Hello")
✔ Single-line & multi-line comments

This project implements a lexical analyzer for C. It scans source code character by character, groups characters into tokens, removes comments and preprocessor directives, applies longest-match rules for operators, and classifies tokens into keywords, identifiers, numbers, strings, operators, and symbols.
