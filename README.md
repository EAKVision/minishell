# Minishell 🐚

A custom Unix shell implementation written in C, built as part of the 42 School curriculum. This project mirrors the architecture and behavior of bash, handling process execution, pipelines, redirections, and signal handling.

---

## 🛠 Features

- **Prompt Display:** Custom interactive command line prompt.
- **Command Execution:** Searches and launches executables based on the PATH variable or relative/absolute paths.
- **Built-in Commands:**
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd` (with no options)
  - `export` (with no options)
  - `unset` (with no options)
  - `env` (with no options or arguments)
  - `exit`
- **Redirections:**
  - `<` Redirect input
  - `>` Redirect output
  - `<<` Here-doc (reads input until delimiter is reached)
  - `>>` Redirect output in append mode
- **Pipes (`|`):** Connects the output of one command to the input of the next.
- **Environment Variables:** Expansion of `$VAR` and `$?` (exit status of the last executed foreground pipeline).
- **Signal Handling:** Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` in interactive mode to behave like bash.

---

## 🏎 Quick Start

### Prerequisites
Ensure you have `gcc` or `clang`, `make`, and `readline` library installed on your Unix/Linux/WSL system.

### Compilation
Clone the repository and build the executable:

```bash
git clone [https://github.com/EAKVision/minishell.git](https://github.com/EAKVision/minishell.git)
cd minishell
make
