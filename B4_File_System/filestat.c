#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static const char* file_type_str(const struct stat *st)
{
    if (S_ISREG(st->st_mode)) return "Regular File";
    if (S_ISDIR(st->st_mode)) return "Directory";
    if (S_ISLNK(st->st_mode)) return "Symbolic Link";
    return "Other";
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];
    struct stat st;
    if (lstat(path, &st) != 0) {
        perror("lstat");
        return EXIT_FAILURE;
    }

    /* File path */
    printf("File Path: %s\n", path);

    /* File type */
    const char *type = file_type_str(&st);
    printf("File Type: %s\n", type);

    /* Size */
    printf("Size: %lld bytes\n", (long long)st.st_size);

    /* Last Modified */
    char timebuf[64];
    struct tm *ptm = localtime(&st.st_mtime);
    if (ptm == NULL) {
        /* fallback */
        printf("Last Modified: (invalid time)\n");
    } else {
        if (strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", ptm) == 0) {
            printf("Last Modified: (could not format time)\n");
        } else {
            printf("Last Modified: %s\n", timebuf);
        }
    }

    return EXIT_SUCCESS;
}
