# filestat — A small file system information utility

This tiny utility inspects a file or directory using `lstat()` and prints some basic information: file path, type, size, and last-modified time.

The code for the utility is in `filestat.c` and is found in this directory.

Overview
--------
- Accepts exactly one command-line argument: the path to a file, directory, or symlink.
- Uses `lstat()` so that symbolic links are reported as *links* rather than following to their target.
- Prints:
  - File Path: the given path
  - File Type: one of ``Regular File``, ``Directory``, or ``Symbolic Link`` (and ``Other`` for any other type)
  - Size: file size in bytes (from `st_size`)
  - Last Modified: formatted timestamp (``YYYY-mm-dd HH:MM:SS``) taken from `st_mtime`.

Build
-----
To build the `filestat` program (requires `gcc`):

```bash
cd B4_File_System
gcc -std=c11 -Wall -Wextra -I.. filestat.c -o filestat
```

Usage
-----
Run the program with exactly one argument (the file or directory path):

```bash
./filestat <path>
```

Examples
--------
Inspect a regular file:
```bash
./filestat filestat
File Path: filestat
File Type: Regular File
Size: 16336 bytes
Last Modified: 2025-11-28 20:54:42
```

Inspect a directory:
```bash
./filestat ..
File Path: ..
File Type: Directory
Size: 4096 bytes
Last Modified: 2025-11-28 20:53:05
```

Inspect a symbolic link (note: because `lstat()` is used, symlink is reported as a link):
```bash
ln -s filestat symlink_test
./filestat symlink_test
File Path: symlink_test
File Type: Symbolic Link
Size: 8 bytes
Last Modified: 2025-11-28 20:55:22
```

Implementation notes
--------------------
- `lstat()` is used instead of `stat()` so that symbolic links are reported as links rather than resolved.
- File types are detected with the macros from `<sys/stat.h>`: `S_ISREG`, `S_ISDIR`, and `S_ISLNK`.
- `localtime()` and `strftime()` are used to present a human-readable timestamp for `st_mtime`.
- If an incorrect number of command-line arguments is provided, the program prints a usage message and exits.

Potential improvements
----------------------
- Add a `Makefile` for builds and testing.
- Display additional file types: block device, character device, FIFO, socket, etc. (`S_ISBLK`, `S_ISCHR`, `S_ISFIFO`, `S_ISSOCK`).
- Add a flag to display raw values (e.g., st_mode in octal, UID/GID, permissions).
- Add unit tests or CI checks to validate behavior automatically.

License & Author
----------------
Add license and author information here per your project conventions.
