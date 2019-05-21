Operation: (Must be correct and efficient for full credit.)


1. BFS print (lab 12, -10 if not working):
   Correct

2. Shortest Paths (25): 20
   When a direct edge is longer than the shortest path, it uses the direct
   edge instead of 2 other edges that are shorter together.

3. Minimal cost spanning tree (25): 10
   Crashes on graphs of more than 2 cities, with
     libc++abi.dylib: terminating with uncaught exception of \
     type std::length_error: vector

4. Connected Components (25): 25
   Correct!

5. Articulation Points (25): 10
   segfault's on each call.


Total for operation, 1-5: 65

* Collaboration (5): Jenny 4, Fei-Fei 0
  Pull requests give no indication of pair programming, and are not
  balanced.  Almost all the work was done from Jenny's account.

* Design (5): 4
  Mostly good

* Comments (5): 3
  Don't fully explain methods.  See comments in graph.h.
  Nothing about how the code or algorithms work.

* Tests (5): 4
  test.in is missing from github, so I can't grade it (and make fails).

* Makefile and output (5): 3

The code has gets some compiler warnings that would be pretty easy to fix.
The main benefit is making it easier to see real errors.  I fixed some,
by changing "int i" to "size_t i", to show you how.

Output format doesn't match provided output exactly, making it harder
to tell if it is correct.

Code has lines that are too long

* Status (-5 if missing): ok

----------------
Total (out of 100, 125 possible):  Jenny 83, Fei-Fei 79
