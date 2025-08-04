# spell checker and other assorted utilities

## Building

Typical Build:

```
${CC} -D_WITH_GETLINE -D_DEFAULT_SOURCE -o prog prog.c
```

Compiles cleanly with all warnings enabled:

```
clang -D_WITH_GETLINE -D_DEFAULT_SOURCE -Wall -Wextra -Weverything -pedantic \
-o prog prog.c
```

## Usage

`./prog 1` (`makewords`) splits lines of text into words (one per line):

```
./prog 1 < foo.txt > words.txt
```

`./prog 2` (`lowercase`) converts all upper case characters to lower case:

```
./prog 2 < words.txt > lower.txt
```

`./prog 3` (`sort`) puts the input in alphabetical order.

```
./prog 3 < lower.txt > sorted.txt
```

`./prog 4` (`uniq`) removes duplicates from sorted input.

```
./prog 4 < sorted.txt > unique.txt
```

`./prog 5` (`mismatch`) finds lines in standard input that don't appear in the
file. Both inputs must be sorted.

```
./prog 5 /usr/share/dict/words < unique.txt > spelling_errors.txt
```

`spell` can be made with this pipeline:

```
./prog 1 text | ./prog 2 | ./prog 3 | ./prog 4 | ./prog 5 /usr/share/dict/words
```

## Demo

```
./prog 1 text | ./prog 2 | ./prog 3 | ./prog 4 | ./prog 5 words
```

## Description

Inspired by [UNIX: Making Computers Easier To Use -- AT&T Archives film from 1982, Bell Laboratories](https://youtu.be/XvDZLjaCJuw?t=870),
5 utilities were implemented that can be combined in a pipeline to form a
spell checker. Most of the utilities have fairly straightforward
implementations. The implementation of `sort` is the most interesting because
it doesn't store all of the lines in memory. It writes all of the lines to a
file in `/tmp` and just keeps pointers to the start of each line. This reduces
the memory usage at the cost of some additional I/O.

## Sample files

A small word list is provided as is a sample text. They may be found in
`words` and `text`.
