#include "linecount.h"

#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

struct thread_job {
    const char *filename;
    unsigned long long count;
    int error;
};

static void *count_file(void *arg)
{
    struct thread_job *job = arg;

    errno = 0;
    if (count_lines_file(job->filename, &job->count) != 0) {
        job->error = errno;
        return NULL;
    }

    job->error = 0;
    return NULL;
}

static void print_count(unsigned long long count, const char *name)
{
    printf("%7llu %s\n", count, name);
}

int main(int argc, char *argv[])
{
    pthread_t *threads;
    struct thread_job *jobs;
    unsigned long long total = 0;
    int exit_status = 0;
    int started = 0;
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s file ...\n", argv[0]);
        return 1;
    }

    threads = calloc((size_t)(argc - 1), sizeof(*threads));
    jobs = calloc((size_t)(argc - 1), sizeof(*jobs));
    if (threads == NULL || jobs == NULL) {
        perror("calloc");
        free(threads);
        free(jobs);
        return 1;
    }

    for (i = 1; i < argc; ++i) {
        int rc;

        jobs[i - 1].filename = argv[i];
        jobs[i - 1].count = 0;
        jobs[i - 1].error = 0;

        rc = pthread_create(&threads[i - 1], NULL, count_file, &jobs[i - 1]);
        if (rc != 0) {
            fprintf(stderr, "%s: pthread_create failed for %s: %s\n",
                    argv[0], argv[i], strerror(rc));
            jobs[i - 1].error = rc;
            exit_status = 1;
            break;
        }

        ++started;
    }

    for (i = 0; i < started; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "%s: pthread_join failed for %s\n",
                    argv[0], jobs[i].filename);
            exit_status = 1;
            continue;
        }

        if (jobs[i].error != 0) {
            fprintf(stderr, "%s: %s: %s\n",
                    argv[0], jobs[i].filename, strerror(jobs[i].error));
            exit_status = 1;
            continue;
        }

        print_count(jobs[i].count, jobs[i].filename);
        total += jobs[i].count;
    }

    if (argc > 2) {
        print_count(total, "total");
    }

    free(threads);
    free(jobs);
    return exit_status;
}
