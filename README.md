# Homemade Unix commands
These C programs emulate some Unix commands. They were made by me in 2022 to practice C language.
My implementations do not claim to be an alternative to the original ones.

## Setup
Showing an example of `ls`
1. Compile the executable:
  ```bash
  gcc ls.c -o ls 
  ```
2. Run the executable:
  ```bash
  ./ls /insert/your/dirname/here
  ```
3. Enjoy!

## List of commands
### ls
- `ls [-al] [file]`
- `ls` only accepts a *single* file or directory as an argument, although in Unix it is possible to accept more than one;
- `-a` option completely mimics the original one: it displays all files and directories starting with a dot;
- `-l` option mimics the `-1` option from the original. It displays all files and directories line by line.

### tail
- `tail [+-n] [file1] [file2] [file3] ... [fileN]`;
- `tail` accepts *multiple* files as an argument;
- `-n` option displays `n` last lines (`n = 10` by default);
- `+n` option displays file the `n`-th line.

## Contributing
This repository is open for contributing. So feel free to open an issues and make pull requests.
