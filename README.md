hanoic
======

[wiki]: http://en.wikipedia.org/wiki/Tower_of_Hanoi "Tower of Hanoi"
[algo]: http://sciences.siteduzero.com/forum-83-694709-p24.html#r7525181 "algorithm explanation and proof"

[img1]: https://raw.github.com/Maelan/hanoic/master/screenshots/screenshot1.png "the classical initial position with 6 disks"
[img2]: https://raw.github.com/Maelan/hanoic/master/screenshots/screenshot2.png "some random position"
[img3]: https://raw.github.com/Maelan/hanoic/master/screenshots/screenshot3.png "the wanted final position"

**hanoic** is an incredible, colorful, interactive console program allowing you to play and solve the **[Tower of Hanoi][wiki]** puzzle. You can setup an initial position, try to solve it, and see the best solution from the current position.


## The Tower of Hanoi

This puzzle features three pegs and *N* disks of distinct diameters. The disks can be stacked on the pegs. A disk can not stand over a smaller one. We can only move the top disks from a peg to another (where it is stacked on the top).
The goal is to stack all the *N* disks on the third peg. Initially, in the base game, the *N* disks are on the first peg.

This program can solve any position, not only the basic one.

### Algorithm

The algorithm used by this program to solve any random position is explained and demonstrated (in French) [here][algo]. It is the optimal solution. In the worst case, it needs 2<sup>*N*</sup> - 1 moves.

#### Research of the optimal algorithm and number of moves

Let ***n*** be the number of disks. We give number 1 to the smallest disk, 2 to the second smallest, etc., until *n* for the largest disk.
We also number the three pegs 1, 2 and 3 (from left to right). Let **P**<sub>***k***</sub> be the peg on which the disk *k* currently is. P<sub>*k*</sub> is only defined by the position.

Let ***t***<sub>***k***</sub>(Q) be the number of moves needed to regroup the *k* first disks onto the peg Q. Let also **R** be the remaining peg (that is, R = 6 - P<sub>*k*</sub> - Q), which play the role of an “intermediate” peg. In fact, what we are looking for is *t*<sub>*n*</sub>(3), since we want to have the *n* disks on the right peg.

Now, let consider a disk *k*. There are two cases:

- P<sub>*k*</sub> = Q. The disk is already where we want it to be. In that case, we just have to move the *k*-1 first disks onto Q.
- P<sub>*k*</sub> ≠ Q. We have to move that disk. To achieve this goal, we first must move all the *k*-1 first disks onto R (because, to be able to move the disk *k* from P<sub>*k*</sub> to Q, there must not be disks over it, nor disks smaller than it on Q). Then, we move the disk *k* from P<sub>*k*</sub> to Q. After that, we continue solving the position by moving the *k*-1 first disks onto Q. This last step is well-known because it corresponds to the classical position: all the disks to be moved are stacked on the same peg. We know that this step will take 2<sup>*k*-1</sup>-1 moves (the prove for that particular case is similar than the one being done here, and can be found easily across the web).

In both cases, the solution is optimal, because the explanation show us we can not do better: in the second case, we **have to** move the disk *k* from P<sub>*k*</sub> to Q, and for that we first **have to** move the *k*-1 smaller disks onto R.

It leads us to a recursive solving algorithm. And, if you ask, we also have a recursive definition for *t*<sub>*k*</sub>(P):
> *t*<sub>0</sub>(Q) = 0
> 
> *t*<sub>*k*</sub>(Q) =
> 
> - *t*<sub>*k*-1</sub>(Q)             if P<sub>*k*</sub> = Q,
> - *t*<sub>*k*-1</sub>(R) + 2<sup>*k*-1</sup>    otherwise.

The second formula is the simplification of *t*<sub>*k*-1</sub>(R) + 1 + (2<sup>*k*-1</sup>-1).

It appears that *t*<sub>*n*</sub>(Q) is a sum of powers of two: we add 2<sup>*k*-1</sup> if (and only if) the disk *k* is not *well-placed*. We could write *t*<sub>*n*</sub> like that:
> *t*<sub>*n*</sub>  =  ∑<sub>*k*=1</sub><sup>*n*</sup>  *b*<sub>*k*</sub> 2<sup>*k*-1</sup>

where the *b*<sub>*k*</sub> are booleans: 1 if the disk *k* is well-placed, 0 otherwise. Whether a disk is well-placed or not depends on its position and what we want to do with the larger disks, according to the algorithm we just defined.

#### The worst case(s)

This brings us to a description of the worst case. In such a case, the number of moves is maximal, which involves that no disk is well-placed. Thus, we have
> *t*<sub>*n*</sub>  =  ∑<sub>*k*=1</sub><sup>*n*</sup>  2<sup>*k*-1</sup>  =  2<sup>*n*</sup> - 1.

We remark that this is also the minimal number of moves when all the disks initially stand on the same peg. Indeed: if all the disks are on peg 1, and we want them on peg 3, then the disk *n* has to move onto peg 3; but for that, the disk *n*-1 must go on peg 2, which need the disk *n*-2 to be on peg 3… Finally, every disk must move.

But other cases exist. Now we are in, what about counting them? In order for disk *k* not to be well-placed, we have two possibilities (since there are three pegs, and only one correct place). Finally, there are 2<sup>*n*</sup> positions in which each of the *n* disks is not well-placed. Moreover, there exists 3<sup>*n*</sup> different positions. So, randomly mixing the disks has a probability of (2/3)<sup>*n*</sup> to lead to a worst case (which decrease when *n* increases).


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

Note that a maximum of 12 disks is allowed, because more disks would induce too much computations and a potentially very long solution (remember, it can take up to 2<sup>*N*</sup>-1 moves). Nobody has time to lose doing 8 191 moves to solve a position with 13 disks (I hope).

Then, you will get this beautiful screen, or something similar:
![initial position][img1]

The big “6” in the top-left corner is the number *N* of disks in your position. On the top-right corner, some statistics about the position. “Last, but not least”, surely you guessed that the center is occupied by the puzzle itself. You see the three pegs, and the *N* disks (numbered by ascending diameter). Here, all the disks are on the first peg, which is the usual initial position. The aim is to move them to the last peg, so as to obtain this:
![final position][img3]

Obviously, that’s not as easy as that. :) You have to move each disk one by one, according to the rules of the puzzle (see above).
![random position][img2]

For that, use the command keys listed below!

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

Before I forget, maybe from time to time you will need to `q`uit this wonderful program.

### Statistics

There are four mystical numbers shown by the program (the big ASCII-art number is not mystical, just awesome, as we said before).

- “you”: that’s simply the number of moves you have done since the setup of the position.
- “errors” indicates the number of errors (!), *ie.* moves you have done but which were not the ones expected according to the optimal solution.
- “optimal solution” is the minimal number of moves that were needed to solve the initial position.
- “from now” is the same, from the current position (*ie.* it is updated after each move).


## Just a footnote on colors

This program paints graphics with gorgeous colors. If they are ugly, that’s not hanoic’s fault. You probably need to revise your likes, as the program simply uses your terminal’s predefined colors (which are of course customizable). The background painting (the big ASCII-art number, the pegs and the cursor) use the color #0 (conventionally black). Disks use colors #1 to #7, according to their number. ;)


## Compiling

To compile this project under GNU/Linux, simply run the command:

    make
You will get an executable file called `hanoic`.

Not tested on others platforms, but the program use some POSIX APIs, mainly *pthread* and *ncurses*.
