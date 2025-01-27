# What is this?

This is a garbled mess of my current understanding of music theory, as tailored to someone who is trying to self-study it to play a piano(me). There may be a lot of inaccuarcies, but I will do my best to ensure there aren't.

## General info:

1. Piano keys are organized by repeating 12-note patterns (7 white + 5 black).
2. Each black key has two possible names (sharp or flat).
3. on a standard 88-key piano, the leftmost key is A0, which is the lowest note. The full range of the piano runs from A0 (the lowest) to C8 (the highest).

## The white keys
It starts with 7 key cycles. We will take the C key as an example given that that's the example I was first intorduced with. A piano is divided into multiple such sets of keys.

The first one starting from the left will be given a letter [A,G], depending on the piano, and the number 1. The next letter which equals 1 when its position (1 indexed) is modulo'd with 7, will be given the letter and the number 2. So key 8 would be A2, since 8%7=1=A. This repeats all throughout the white keys of the piano. The difference between two such notes(e.g. A1 and A2), is that A2 is one octave higher then A1. This means that its frequency is twice as large.

## The black keys

The black keys also follow the 7 key cycle, as do the whites. Except that each one of them is referred to as C# (reading: C sharp), or flat, depending on context.

The black key between C1 and D1 is C♯1 (or D♭1, reading: d flat.) , and between C2 and D2, it's C♯2/D♭2, etc.

## Steps

We define, on a piano, distance between keys in terms of steps.

Step (Whole Step):
- A whole step is an interval that spans two keys (either white or black).
- For example, from C to D is a whole step (because you skip C♯ or D♭).

Half Step:
- A half step is the smallest interval in Western music, spanning from one key to the immediately adjacent key (whether white or black).
- For example, from C to C♯ is a half step. Similarly, from E to F is also a half step, because there's no black key between them.

To summarize:

 - Whole step = 2 half steps.
 - Half step = the smallest interval, moving to the adjacent key.


## Difference between notes

### What's an octave? 

In musical terms, an octave is the interval between two notes with the same name(denoted by the same letter, e.g. C1 and C2), where the higher note vibrates at twice the frequency of the lower one.

For example:
- If A0 has a frequency of 27.5 Hz, then A1 (one octave higher) will have a frequency of 55 Hz.

- There are 12 keys (7 white + 5 black) in one octave.

On a piano, moving from C1 to C2 means going through 12 keys (C, C♯, D, D♯, E, F, F♯, G, G♯, A, A♯, B), then arriving at C2, which is the start of the next octave.


###  Major Seventh

C1 to B1 is not a full octave but a smaller interval called a `major seventh`, meaning B1 is the highest white key before reaching C2.


## What's a scale?

A scale is a series of musical notes ordered by pitch, typically spanning an octave. The most common scales in Western music are the major and minor scales. A scale provides the foundation for melodies and harmonies.


A scale is defined by the sequence of intervals between notes, not by their exact octave. The octave numbering (C1, C2, etc.) simply indicates which pitch range the notes belong to.

For example, the `C major scale` is the same regardless of whether it starts at C1, C2, or C3—it's defined by the pattern of intervals between the notes.

It has a pattern of `whole steps` (W) and `half steps` (H):

W, W, H, W, W, W, H.

that is to say the difference between C to D is W, a whole step, D-> E W, E-> F is H, etc

C1, D1, E1, F1, G1, A1, B1, C2 would be one specific version of the C major scale.
C2, D2, E2, F2, G2, A2, B2, C3 would be another version of the same scale, just an octave higher.


### Why start at C?

We commonly start from C in music theory because of the way modern Western music is structured around the `C major scale `, which contains no sharps or flats and serves as a natural reference point.
