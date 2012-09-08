hanoic
======

[wiki]: http://en.wikipedia.org/wiki/Tower_of_Hanoi "Tower of Hanoi"
[algo]: http://sciences.siteduzero.com/forum-83-694709-p24.html#r7525181 "algorithm explanation and proof"

[img1]: tree/master/screenshots/screenshot1.png
[img2]: tree/master/screenshots/screenshot2.png
[img3]: tree/master/screenshots/screenshot3.png

**hanoic** is an incredible, colorful, interactive console program allowing you to play and solve the **[Tower of Hanoi][wiki]** puzzle. You can setup an initial position, try to solve it, and see the best solution from the current position.


## The Tower of Hanoi

This puzzle features three pegs and *N* disks of distinct diameters. The disks can be stacked on the pegs. A disk can not stand over a smaller one. We can only move the top disks from a peg to another (where it is stacked on the top).
The goal is to stack all the *N* disks on the third peg. Initially, in the base game, the *N* disks are on the first peg.

This program can solve any position, not only the basic one.

### Algorithm

The algorithm used by this program to solve any random position is explained and demonstrated (in French) [here][algo]. It is the optimal solution. In the worst case, it needs 2<sup>*N*</sup> - 1 moves.

**FIXME:** explain/demonstrate the algorithm here and in English.


## Using hanoic

Simply launch the program:

    ./hanoic
If you put it somewhere in your path:

    hanoic
This init the position with 4 disks.

Additionally, you can specify an initial position from the command-line. Possible syntaxes are

    hanoic -N
    hanoic POSITION
where `N` is the number of disks, or `POSITION` the initial position. This latter must be a sequence of digits between 1 and 3. These digits indicate on which peg is each disk (and their number indicates the number of disks). The first digit matchs the disk *N* (the larger), the second digit matchs the disk *N*-1 (the second larger), and so on.  
If no position is specified, the default is “all disks on the first peg”.

Note that a maximum of 12 disks is allowed, because more disks would induce too much computations and a potentially very long solution (remember, it can take up to 2<sup>*N*</sup>-1 moves). Nobody has time to lose doing 8 191 to solve a position with 13 disks (I hope).

Then, you will get this beautiful screen, or something similar:
![initial position][img1]
The big “6” in the top-left corner is the number *N* of disks in your position. On the top-right corner, some statistics about the position. “Last, but not least”, surely you guessed that the center is occupied by the puzzle itself. You see the three pegs, and the *N* disks (numbered by ascending diameter). Here, all the disks are on the first peg, which is the “normal” initial position. The aim is to move them to the last peg, so as to obtain this:
![final position][img3]
Obviously, that’s not as easy as that. :) You have to move each disk one by one, according to the rules of the puzzle (see above).
![random position][img2]
For that, use the command keys listed above!

### Command keys

There are several keys to move disks:

- `←` and `→`: the left and right arrows allows you to move the “cursor” below the pegs, to choose from which peg you want to select a disk, and on which one you want to stack it.
- `1`, `2` and `3`: moves directly the cursor to the first, second or third peg.
- `<space>`: select the top disk of the current peg (it appears above the peg it comes from), or release the previously selected disk on the current peg (if allowed).
- `4`, `5` and `6`: because stroking 4 keys to move a disk is awkward, here are some shortcuts; they move the cursor to the peg 1, 2 or 3, then perform a “select/release”.
- `7`, `8` and `9`: because stroking 2 keys to move a disk is still *a bit* awkward, you can use more evil shortcuts; if possible, they perform one move between pegs 1 and 2, 1 and 3, or 2 and 3 respectively, in the direction allowed by the position. Use them at your own risks!

Of course, you also have keys for <strike>cheating</strike> playing the Ultimate Solution from the current position:

- `s`: plays the next move.
- `S`: plays the entire solution, move by move (or, if the solution is already being played, stop it).

Last, maybe you would like to set up the position, *hmm*?

- `+` and `-`: increases or decreases *N*.
- `i`: set up the classical initial position (all disks on peg 1).
- `r`: set up a random position.
- `m`: set up a manual position. You will be asked for each disk, in descending diameter; hit `1`, `2` or `3` for each of them to tell on which peg you want them.

Before I forget, maybe from time to timeyou will need to `q`uit this wonderful program.

### Statistics

There are four mystical numbers shown by the program (the big ASCII-art number is not mystical, just awesome, as we said before).

- “you”: that’s simply the number of moves you have done since the setup of the position.
- “errors” indicates the number of errors (!), *ie.* moves you have done but which were not the ones expected for the optimal solution.
- “optimal solution” is the minimal number of moves that were needed to solve the initial position.
- “from now” is the same, from the current position (*ie.* it is updated after each move).


## Just a footnote on colors

This program paints graphics with gorgeous colors. If they are ugly, that’s not hanoic’s fault. You probably need to revise your likes, as the program simply uses your terminal’s predefined colors (which is of course customizable). The background painting (the big ASCII-art number, the pegs and the cursor) use the color #0 (conventionally black). Disks use colors #1 to #7, according to their number. ;)


## Compiling

To compile this project under GNU/Linux, simply run the command:

    make
You will get an executable file called `hanoic`.

Not tested on others platforms, but the program use some POSIX APIs, mainly *pthread* and *ncurses*.