# README

This is a crossword puzzle solver. It has the following form of input: 

    5 4
    -1 0 0 0 
    0 0 0 0 
    0 0 -1 0 
    0 0 0 0
    0 -1 0 0 
    10
    ad
    antas
    carn
    casa
    do
    lado
    lua
    os
    soda
    ur

The first line indicates the number of lines followed by the number of columns. The number -1 indicates that this is a black square. And 0 indicates it is a free square.

The next number, ten in this case, indicates the number of possible words to be considered for solving the puzzle. Following that are the K words. 

Let the character "-" represent empty squares and "*" represent blocked ones, such that
or previous example would be:

    * - - - 
    - - - -
    - - * - 
    - - - -
    - * - - 

Before introducing the algorithm, let's introduce the notation we will use for the problem. 

Horizontal game moves refer to a horizontal sequence of empty squares of a size bigger than one. They are indexed from left to right, top to bottom, starting with 0.
So in the above example, the layer of horizontal moves would be represented as: 

    * 0 0 0 
    1 1 1 1
    2 2 * -  
    3 3 3 3
    - * 4 4 

And we refer to the horizontal move 3 as the one represented by the squares with 3 in them. 

A play is the association between a game move and a word. For instance, we could 
make the association between horizontal position 3 and the word "lado". This would 
make our board look like: 

    * - - - 
    - - - -
    - - * - 
    l a d o 
    - * - -

The same idea extends for our notion of vertical moves and plays. 
The vertical layers of the example would be: 

    * 1 2 4 
    0 1 2 4
    0 1 * 4 
    0 1 3 4
    0 * 3 4 

In the same way we could associate the vertical move 3 with the word "do". This would make our board now look like: 

    * - - - 
    - - - -
    - - * - 
    l a d o 
    - * o -

The motivation for this notation is to make plays simpler to describe, all that is
required to represent a move is the initial line, initial column, size of the space, alignment, and the index of the word on the list. So the previous play "lado", for instance, could be described as:

    initial line: 3
    initial column: 0
    size of the word: 4
    alignment: horizontal
    word index: 5

Similarly the previous play "do" could be described as:

    initial line: 3
    initial column: 2
    size of the word: 2
    alignment: vertical
    word index: 4

We also introduce a shorthand notation for reduced visual clutter. 

    hx:y represents the horizontal move x with the word of index y
    vx:y represents vertical move x with the word of index y

For example the previous play "lado" would be described as h3:5. And "do" would
be described by v3:4. This makes it easy to represent a stack of moves in the order
they were made. For instance:

    h3:5 v3:4

Represents a stack with 2 elements, where h3:5 was made before v3:4. 

But even though a sequence of horizontal and vertical plays is all that is required to 
describe a game. We keep a variation on the matrix type representation above. This
is done such that we can build an adjacency matrix ???? adjacency list of the intersection between horizontal and vertical moves. Reducing the amount of comparisons we need to make. 
But the specifics are better explained in the implementation section. 


The general idea of the solution is to implement a backtracking algorithm. That tries a play, and proceeds with the intersecting plays if they are possible, and backtracks if they are not. 

We begin by putting the first 3 letter word in the list on the first horizontal move,
and marking it as used in our list. 

    * l u a h0:6
    - - - -
    - - * -  
    - - - -
    - * - - 

Then we make a intersecting vertical play. The word "lado" is the first
4-letter word that starts with "l" in our list. 

    * l u a h0:6 v1:5
    - a - -
    - d * -
    - o - -
    - * - -

We them proceed with intersecting horizontal move. The word "carn" is the
first 4-letter word that has "a" as it's second letter. 

    * l u a h0:6 v1:5 h1:2
    c a r n
    - d * -
    - o - -
    - * - -

The next boards follow with the same idea. 

    * l u a h0:6 v1:5 h1:2 v0:3
    c a r n
    a d * -
    s o - -
    a * - -

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0
    c a r n
    a d * -
    s o - -
    a * - -

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0 h3:8
    c a r n
    a d * -
    s o d a
    a * - -

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0 h3:8 v3:4
    c a r n
    a d * -
    s o d a
    a * o -

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0 h3:8 v3:4 h4:8
    c a r n
    a d * -
    s o d a
    a * o s

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0 h3:8 v3:4 h4:8 v4:1 
    c a r n
    a d * t
    s o d a
    a * o s

Here the board is filled, but we still haven't checked the third vertical move. 
In this case, we still don't know if "ur" is a valid word. After confirming it,
we get to the final state. 

    * l u a h0:6 v1:5 h1:2 v0:3 h2:0 h3:8 v3:4 h4:8 v4:1 v2:9
    c a r n
    a d * t
    s o d a
    a * o s

Now for an example that requires backtracking. We have the following input: 

    3 3
    -1  0  0
    0  0  0
    0 -1  0
    5
    ab 
    au  
    bug
    la
    lua

    First the representation of the board, horizontal and vertical moves:

    Board

    * - -
    - - -
    - * - 

    Horizontal Moves

    * 0 0 
    1 1 1
    - * - 

    Vertical Moves

    * 1 2 
    0 1 2
    0 * 2 

---------------

We start with the first 2-letter word in the list on horizontal move 0. And mark it
as used. 

    * a b  h0:0
    - - -
    - * -

It's first intersection is with vertical move 1. We put the word "au" there and 
mark it as used. 

    * a b  h0:0 v1:1
    - u -
    - * -

Now we do horizontal move 1. 

    * a b  h0:0 v1:1 h1:2
    b u g 
    - * -

But because of the absence of a 2-letter word starting with "b". We backtrack. 
Note the removal of h1:2 from our stack. 

    * a b  h0:0 v1:1 
    - u - 
    - * -

And them we try the next 3-letter word that has "u" as it's second letter. 

    * a b  h0:0 v1:1 h1:2
    l u a 
    - * -

Here we can expand on vertical move 0. The word "la" fit's the requirements. 

    * a b  h0:0 v1:1 h1:2 v0:3
    l u a 
    a * -

But we don't have a 3-letter word that starts with "ba". Therefore we backtrack. 

    * a b  h0:0 v1:1 h1:2 
    l u a 
    - * -

There isn't another 2-letter word starts with "la". Hence we backtrack again. 

    * a b  h0:0 v1:1 
    - u - 
    - * -

We also do not have another 3-letter word that has "u" as it's second letter. 

    * a b  h0:0 
    - - - 
    - * -

Similarly, after "au" there wasn't any 2-letter word that started with "a".

    * - -   
    - - - 
    - * -

We then try with another initial move. And proceed as expected. 

    * a u  h0:1 
    - - - 
    - * -

    * a u  h0:1 v1:0
    - b - 
    - * -

    * a u  h0:1 
    - - - 
    - * -

    * - - 
    - - - 
    - * -

    * l a h0:3 
    - - - 
    - * -

The isn't an unused 2-letter word that starts with "l" in our list. We find
our last board. 

    * - - 
    - - - 
    - * -

Now we have exhausted all the possibilities for the first move. Since none of them 
were able to fill the board. We can be sure that the board cannot be completed
with our current list of words. 

## Implementation details
