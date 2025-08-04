# Past IOCCC Submissions

This repository contains my past submissions to the International
Obfuscated C Coding Contest.

- [IOCCC 28](https://github.com/tcort/ioccc/tree/main/submissions/ioccc28)
  - [Text to Morse](https://github.com/tcort/ioccc/tree/main/submissions/ioccc28/text-to-morse) - renders text into International Morse Code and writes the output to a Waveform Audio File (`.wav` file). Very detailed [remarks.md](https://github.com/tcort/ioccc/blob/main/submissions/ioccc28/text-to-morse/remarks.md).
- [IOCCC 27](https://github.com/tcort/ioccc/tree/main/submissions/ioccc27)
  - [Find and Replace](https://github.com/tcort/ioccc/tree/main/submissions/ioccc27/find-and-replace) - lots of goofy comments, strange indentation, misleading variable names, and a single `setjmp()` and `longjmp()` for flow control. Very small memory footprint.
  - [Spell](https://github.com/tcort/ioccc/tree/main/submissions/ioccc27/spell) - a spell checker consisting of 5 subprograms (`makewords`, `lowercase`, `sort`, `uniq`, `mismatch`) demonstrated in a [Bell Labs video from 1982](https://youtu.be/XvDZLjaCJuw?t=870).
  - [Template](https://github.com/tcort/ioccc/tree/main/submissions/ioccc27/tmpl) - a templating system which calls shell commands (e.g. `Hello ${logname}, and welcome to ${hostname}!`). Less than 500 elements as calculated by the `iocccsize` tool.
