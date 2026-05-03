#include "linecount.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static void print_count(unsigned long long count, const char *name)
{
    printf("%7llu %s\n", count, name);
}

int main(int argc, char *argv[])
{
    unsigned long long total = 0;
    int exit_status = 0;
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s file ...\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; ++i) {
        unsigned long long count = 0;

        errno = 0;
        if (count_lines_file(argv[i], &count) != 0) {
            fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
            exit_status = 1;
            continue;
        }

        print_count(count, argv[i]);
        total += count;
    }

    if (argc > 2) {
        print_count(total, "total");
    }

    return exit_status;
}
