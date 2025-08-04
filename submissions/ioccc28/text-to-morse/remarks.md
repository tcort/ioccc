# Text to Morse Code Audio File

## Overview

This utility renders text into International Morse Code and writes the output
to a Waveform Audio File (`.wav` file).

References:

- https://en.wikipedia.org/wiki/Morse_code
- https://en.wikipedia.org/wiki/WAV

## Prior Art

There have been two past winners who created utilities to render text into
International Morse Code in a textual representation: `hague` in 1986 and
`dorssel` in 1998. Surprisingly, the two entries and this entry all used
different approaches to mapping ASCII characters to Morse Code.

References:

- https://www.ioccc.org/1986/hague/index.html
- https://www.ioccc.org/1998/dorssel/dorssel.html
- https://medium.com/@alex24dutertre/understand-jim-hagues-code-1986-ioccc-winner-7715093b0b3b
- https://medium.com/@calypsobronte/worst-abuse-of-the-c-preprocessor-ioccc-winner-1986-906d75b6d37

## Morse Code Basics

Morse Code has been used to communicate for nearly 200 years. It consists of
a series of on/off states called elements. There is a short element, `dit`,
and a long element, `dah`. The `dit` is on for one unit of time. The `dah` is
on for three units of time. Those two elements are used to build characters.

Characters consist of one or more elements, separated by space for one unit
of time. The most common letters, `T` and `E` are single elements, `dah` and
`dit`. Uncommon letters consist of more elements; for example, `X` is `dah`,
`dit`, `dit`, `dah`.

Characters are used to build words. Each character is separated by space for
3 units of time. Characters are case insensitive; `a` and `A` are
represented with the same elements, a `dit` followed by a `dah`.  Words are
separated by space for 7 units of time.

While it can be used with lights or written on paper, Morse Code is most
commonly received aurally.

References:

- https://morsecode.world/international/timing.html

### Choosing Morse Code Parameters

Morse Code can be sent and received at various speeds. The novice might begin
at 5 words per minute. The expert might be able to handle 50 words per
minute or more. 20 words per minute is achievable by most people and is the
minimum proficiency required for a commercial radiotelegraph operator's
license in the United States. Thus, a speed of 20 words per minute was chosen
using the `"PARIS "` standard.

The frequency of the audio tone is generally between 400 Hz and 1000 Hz, and
it is mostly a listener preference. 600 Hz is common in commercially available
radiotelegraph transceivers, so that frequency was chosen for this project.

References:

- https://en.wikipedia.org/wiki/Words_per_minute

## A Compact Digital Representation of ASCII Characters in Morse Code

### Overview

Characters in Morse Code are variable length from 1 to 6 elements long. The
characters consist of a series of `dits` and `dahs` (two states). The goal
is to go from an ASCII character to a representation of the Morse Code for
that character, so there are three pieces of information:

- ASCII code (1 byte)
- Morse Code representation
 - Number of Elements (3 bits)
 - Series of Elements (1 to 6 bits)

### Dead Ends

The most straightforward implementation would be a look-up table indexed on the
ASCII code. However, even if the Morse Code representation was packed into
a single integer per character, this is very expensive in terms of source code
size. There are many ASCII codes with no Morse Code equivalent. Space is at a
premium in IOCCC.

Another straightforward implementation would be to write the data to a file
and load it at runtime. While this would work, it is a crutch, and there is a
better solution hiding out there that does not involve loading files and
is fairly space efficient.

### Solution

The solution is to store the ASCII characters in such a way that the Morse
Code representation can be inferred from the data structure. This allows the
ASCII to Morse Code mapping to be reduced from 17 bits of information to
just 1 byte (technically 7 bits), and since it is stored as a string, less
source code is used to represent the values than a traditional array with
commas separating each element of the array.

Data:

```
const char X[]=" \netianmsurwdkgohvf l pjbxcyzq  54 3   2& +    16=/   ( 7   \
8 90            ?     \"  .    @   '  -           )     ,    :              ";
```

Algorithm:

- Define an `X` array as above.
- Define a `dit` as `0` and a `dah` as `1`.
- Example Input Character: `A`.
- Downcase the input character (`A` to `a`).
- Find the index of the lower case Input Character in the array (`i=5`).
- Within the binary representation of index `5` (i.e. `000000101`), locate the position of the most significant bit. This can be done with `log2(i)`.
- The bits remaining after the most significant bit (`01`) hold the Morse Code representation of the character (`a` has `01`, so `dit dah`)

### Opportunities for Obfuscation

There are some gaps in the string as not all possible Morse Codes have
corresponding characters. This presents a nice opportunity for obfuscation.
The algorithm finds the index of the first occurrence of a character in the
array. Any of the blanks can be filled in by characters that have already
appeared in the string.

## Generating Audio

### Overview

Generating audio is surprisingly simple. Morse Code is most commonly
represented aurally as a sine wave. The software just needs to construct a
sine wave and toggle the it on and off at specific intervals to create a
signal that can be interpreted.

### Building the Building Blocks

There are five building blocks in Morse Code:

- 2 elements: `dit` (1 time unit) and `dah` (3 time units)
- 3 spaces: intra-character spaces (1 time unit), inter-character spaces (3 time units), and intra-word spaces (7 time units)

With these five blocks, all Morse Code can be generated. At start-up, the
program generates the waveforms (or silence) for each of these five pieces.

### Eliminating Clicks with Waveform Shaping

The abrupt switching of the sine wave off and on causes audible clicks. These
aren't noticeable when Morse Code is sent slowly. However, as speeds increase,
so does the intensity of the clicks. It makes the audio uncomfortable to listen
to for more than a few minutes. The solution to this is to ramp up the volume
as a Morse Code element begins and ramp down the volume as a Morse Code
element ends.

A value of 5ms was suggested on a mailing list. Using that value eliminated
the clicks and made listening to the output a pleasure.

References:

- https://groups.io/g/RGO-ONE/message/805

### Building the Output

The five building blocks are concatenated together to create the final output.
For example, the letter `a` is a `dit` followed by an intra-character space
followed by a `dah` followed by an inter-character space, and then the next
letter is constructed.

### WAV Format

WAV format was chosen for the output file format as it's one of the simplest
formats to implement and there is very limited source code space in IOCCC to
implement fancy compression algorithms.

The file format consists of a 44 byte header with basic information about
the file and the data that follows the header. The header includes the number
of channels, sample rate, bits per sample, file size, etc.

There are two approaches to constructing WAVE files for machine generated
audio:

- Option 1: write most of the header, write the data, compute the file size after writing all of the data, and then fill in the header with the correct size.
- Option 2: generate the entire WAVE file in memory, compute the file size, write the header and the data in one pass.

The second option was the one chosen for implementation. While option 1 is
generally more attractive as it is much more memory efficient, option 2 can
be implemented much more simply and concisely.

References:

- https://docs.fileformat.com/audio/wav/

#### Byte Order Considerations

WAV Files are stored in little endian byte order. Most modern computers
used by the general public use this byte order but not every computer.
To allow this utility to generate valid WAV files on a big endian machine,
a couple of simple conversion functions were implemented.

References:

- https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
- https://en.wikipedia.org/wiki/Endianness

### Choosing WAV File Parameters

With every digital representation of an analog value, there is a tension
between fidelity and data sizes. The source code size limits of IOCCC preclude
implementing most types of compression, so PCM format was chosen.

Sample rate was chosen through trial and error from a list of common sample
rates. A sample rate of 8 kHz was chosen as it is nearly indistinguishable from
CD quality audio (44.1 kHz) in this use case.

Mono output (i.e. a single audio channel) was chosen in favour of Stereo
output as there was no need for a second audio channel to contain anything
other than what was in the first channel. This reduces the output file size
greatly.

Samples of 16-bits were chosen to reduce output file sizes compared to 24-bit
CD quality audio. 8-bit samples were experimented with, but they contained a
lot of distortion.

- https://en.wikipedia.org/wiki/Nyquist%E2%80%93Shannon_sampling_theorem
- https://github.com/audiojs/sample-rate
- https://isip.piconepress.com/projects/speech/software/tutorials/production/fundamentals/v1.0/section_02/s02_01_p05.html

## Eliminating the need for `math.h` and `-lm`

Depending on the platform and its vintage, using functions from `math.h`
sometimes requires linking to `libm`. This is enough of a pain to work around
in `autotools` or `cmake`. In an effort to avoid disappointing users, avoid
complex build systems, and have zero dependencies (besides `libc`), the use
of `math.h` was eliminated early on in development. This program could have
used `libm` for `sin()` as well as `log2()`.

### `log2(x)` Replacement

`log2(x)` is just `log(x)/log(2)`. `log(x)` is implemented using the
Newton-Raphson method with a few lines of code. It does depend on `exp(x)`,
but that can be implemented in a few lines of code too as a Taylor series
expansion.

References:

- https://en.wikipedia.org/wiki/Taylor_series
- https://en.wikipedia.org/wiki/Newton%27s_method

### `sin(x)` Alternative

`sin(x)` can be implemented with minimal code as a Taylor series expansion
as well. However, there are some inaccuracies and limitations of this approach.
It was attempted. However, either due to the author failing to implement it
properly or the limits of this approach, the resulting output audio did not
sound as clean as it did when produced with the system `sin(x)` function.

If one cannot implement `sin(x)`, then the next best option is a look-up table.
In an effort to avoid using data files and wasting precious bytes on storing
such a table, the author took a third approach.

In the third approach, it a data table was built containing the values for one
cycle of the sine wave. Looping through the values repeatedly can build an
arbitrary length sine wave of the same frequency. The output of the program
in development was captured and used in the data table.

## Limitations

### Duration Limit

The length of the output file is limited by the WAV format itself. Using a
single channel with 16-bit samples, the duration is limited to 13 hours and
31 minutes.

References:

- https://manual.audacityteam.org/man/size_limits_for_wav_and_aiff_files.html

### Fixed Frequency Morse Code Tone

Since the sine wave was pre-computed, the audio frequency of the Morse Code
`dits` and `dahs` cannot be changed at runtime.

### Morse Code Character Speed

The character speed is fixed at 20 words per minute.

### Character Sets

ASCII characters with common International Morse Code representations are
supported.

There is no support for alternative outputs (e.g. American Morse Code)

Additionally, there is no support for alternative inputs (e.g. Japanese
language in kana characters).

- https://en.wikipedia.org/wiki/American_Morse_code
- https://en.wikipedia.org/wiki/Wabun_code

