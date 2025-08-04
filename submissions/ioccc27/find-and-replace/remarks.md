# find and replace utility

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
./prog subject replacement < text.txt
```

## Demo

```
echo "This is a test." | ./prog test text
```

## Algorithm

Pre-obfuscation, the algorithm is very elegant and only uses argc/argv, 2
index variables, and an `int` to hold a character. There is no memory
allocation, and it runs fast. It simply scans the input for `argv[1]`
and outputs `argv[2]` upon a match, otherwise it just copies characters
from input to output.

## Portability

This program only uses a few library functions: `getc`, `putc`, `strlen`,
and `exit`. Some of the obfuscation assumes at least a 32 bit integer.
Other than that, it should run almost anywhere. It has been tested
on Mac OS X, Linux, and FreeBSD.

## Obfuscation

The truly great thing about this program isn't what's in it, it's
what's not in it. Look at the function bodies: no flow control except
a single pair of setjmp/longjmp calls. This is done by abusing
function pointers. A two element array of function pointers indexed
by a boolean expression chooses `arr[1]` when `true` and `arr[0]`
when `false`.

Formatting was changed to make the code harder to follow. There's a
`#define` which expands to something more complicated. Comments are
sprinkled throughout, some misleading. `!1` and `!0` are used to force
a `0` or `1`. Bitwise math was used to obfuscate several integer
constants. Functions were given misleading names, some are mispellings
of C keywords. Random `{` `}` blocks were added. Constants such as
`SIGKILL` and `O_RDWR` were added to further confuse the reader.
