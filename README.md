# AoC 2024

This time around, I will try to write whatever I have time for in C.

I do not have as much time left over as last time, but we will see.

## Allowed libraries
I will try to only use builtins and:
 * stddef.h for:
   * sizeof
   * NULL
 * stdlib.h for:
   * malloc
   * free

Lists and matrices etc will be written from scratch.
Math will be written from scratch as needed. Screw performance.

See below for a (mostly joking) implementation of an integer-based sqrt...
```c
int slowSQRTestimate(int v) {
    int last = -1;
    int current;
    for (int i = 0; i < v; i++) {
    	current = i * i;
    	if (current == v) {
	    return current;
	} else if (current > v) {
	    return (last < 0) ? 1 : last;
	}
    }

    return -1;
}
```