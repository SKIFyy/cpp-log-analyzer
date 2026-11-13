# C++ Log Analyzer

A small command-line program that reads `logs.txt`, counts `INFO`, `WARNING`, and `ERROR` records, and prints the most frequent `ERROR` message. If several messages share the highest count, the program prints all of them.

## Log format

Each valid line has a level, a colon, and non-empty text:

```text
INFO: Application started
WARNING: Sensor response is slow
ERROR: Sensor timeout
```

The supported levels are `INFO`, `WARNING`, and `ERROR`. Spaces immediately after the colon are skipped. Other colons in the message are kept as part of the text. Lines with an unknown level, no colon, or no message are reported with their line number and excluded from the counts.

## Build and run

From the project directory, using GCC with C++17:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o main.exe
.\main.exe
```

The program opens `logs.txt` from the **current working directory**. Run it from the project directory to use the included sample file. If the file cannot be opened, the program prints an error and exits with status `1`.

With the included `logs.txt`, the level counts are `INFO: 5`, `WARNING: 2`, and `ERROR: 5`; the most frequent error is `Sensor timeout` (3 occurrences).

## Test inputs

Each subdirectory of `testdata` contains a `logs.txt` for a different case:

| Directory | Case |
| --- | --- |
| `empty` | Empty file |
| `malformed` | Invalid lines and an additional colon in a message |
| `no_errors` | Valid log without `ERROR` records |
| `spaces_only` | Message containing only spaces |
| `tie` | Two error messages with the same highest count |

To try a case, copy its `logs.txt` into the current working directory before running the program, or run the executable with that case directory as the working directory. To check the missing-file case, run it from a directory without `logs.txt`.
