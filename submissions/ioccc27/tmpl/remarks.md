# document templating system

## Building

Typical Build:

```
${CC} prog.c -o prog
```

Compiles cleanly with all warnings enabled:

```
clang -Wall -Wextra -Weverything -pedantic -o prog prog.c
```

## Usage

```
./prog < template.tmpl > template.txt
./prog < template.tmpl > template.html
```

## Demo

```
./prog < tutorial.tmpl > tutorial.html
```

## Description

This program provides a simple document templating system. Any command or
shell expression enclosed in `${...}` is executed and replaced by the
command output. Example: `There are ${who|wc -l} users logged into ${hostname}`.
For generating HTML pages, enclose the command in `%{...}`. To include the
literals `${` and `%{`, simply escape them with a leading backslash: `\${` and
`\%{`. This tool is very useful for generating reports, emails, and status
pages. It's very simple and small, weighing in at less than 500 elements as
counted by the `iocccsize` tool.
