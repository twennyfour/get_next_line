This version of the project fixes the still reachable memory leaks that the version I submitted (in main branch) contains.

The leaks occur when stash needs to keep track of the content that was read but is beyond a single line. \
Example: imagine a text file containing
```
abc
def
ghi
```

When BUFFER_SIZE is 5, it will read "abc\nd". In the main branch, stash is just a static pointer, which points to somewhere in memory. \
This memory needs to be persistent between calls, so it lives in the heap. The example I gave, if the user only calls `get_next_line` once,
and runs valgrind on it, it will have still reachable leaks, since the updated stash will be a pointer pointing at the character "d".

This branch fixes this by making the buffer array static, meaning the actual characters are persistent between calls with no need to store
in the heap.
