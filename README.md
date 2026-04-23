*This project has been created as part of the 42 curriculum by mleitao.*

<h1 id="description">Description</h1>

**get_next_line** is a project that implements a function that reads and returns a line from a file descriptor. It uses a static variable to preserve leftover data between calls, allowing successive calls to return successive lines. The bonus part extends this functionality to support multiple file descriptors.

<h3 id="overview">Overview</h3>

This function reads data from a file descriptor in fixed-size chunks into a buffer of size `BUFFER_SIZE`. Since a line may not be fully obtained in a single read, the data is stored in a static variable, allowing the function to retain and reuse it across multiple calls.

This function continues reading and appending data until it encounters a new line character, or reaches the end of the file. If more than one line is read at once, the extra characters are preserved in the static variable and used in subsequent calls.

<h1 id="instructions">Instructions</h1>

<h3 id="requirements">Requirements</h3>

- A C compiler, ideally `clang`.

<h3 id="usage">Usage</h3>
   
1. Clone the repository:
	```bash
	git clone ssh://git@codeberg.org/6times7/get_next_line.git
	```

2. Include [`get_next_line.h`](./get_next_line.h) in your `main.c`:
   ```c
	#include "get_next_line.h"
	#include <fcntl.h>
	#include <stdio.h>

	int	main(void)
	{
		int		fd;
		char	*line;

		fd = open("get_next_line.c", O_RDONLY);
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		return (0);
	}
	```

3. Compile it:
	```bash
	cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
	```

<h1 id="resources">Resources</h1>

<h3 id="references">References</h3>

- `man 2 read`
- [Using ssize_t vs int](https://stackoverflow.com/questions/19224655/using-ssize-t-vs-int)
- [How do I find the maximum stack size?](https://stackoverflow.com/questions/7535994/how-do-i-find-the-maximum-stack-size)
- Peer discussions

<h3 id="llm_usage">LLM Usage</h3>

LLMs were used for:

- General guidance during project development, primarily to make code more idiomatic
- Parts of this README

<h3 id="tests">Tests</h3>

This project was tested against [gnlTester](https://github.com/Tripouille/gnlTester). Kudos to [@Tripouille](https://github.com/Tripouille) for providing this test suite.
