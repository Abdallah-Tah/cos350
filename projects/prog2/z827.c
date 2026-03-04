/*
 * Author: Abdallah Mohamed
 * Date:   February 27, 2026
 * Program 2 - z827
 *
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EXT ".z827"
#define EXT_LEN 5

// Check if a file has the .z827 extension
static int is_z827(const char *name)
{
    size_t n = strlen(name);
    if (n < EXT_LEN)
        return 0;
    return strcmp(name + (n - EXT_LEN), EXT) == 0;
}

// Get output file name based on input file name and also whether decompressing
static char *out_name(const char *in, int decompress)
{
    size_t n = strlen(in);

    if (decompress)
    {
        if (n < EXT_LEN)
            return NULL;

        char *out = (char *)malloc(n - EXT_LEN + 1);
        if (!out)
            return NULL;

        memcpy(out, in, n - EXT_LEN);
        out[n - EXT_LEN] = '\0';
        return out;
    }
    else
    {
        char *out = (char *)malloc(n + EXT_LEN + 1);
        if (!out)
            return NULL;

        memcpy(out, in, n);
        memcpy(out + n, EXT, EXT_LEN + 1);
        return out;
    }
}

// Close file descriptor and handle errors
static void xclose(int fd)
{
    if (fd >= 0)
        close(fd);
}

// Compression function do_compress
static int do_compress(const char *in_file, const char *out_file)
{
    int in_fd = -1, out_fd = -1;
    struct stat st;

    in_fd = open(in_file, O_RDONLY);
    if (in_fd < 0)
    {
        perror("open input");
        return 1;
    }

    if (fstat(in_fd, &st) < 0)
    {
        perror("fstat");
        xclose(in_fd);
        return 1;
    }

    if (!S_ISREG(st.st_mode))
    {
        fprintf(stderr, "Error: input is not a regular file.\n");
        xclose(in_fd);
        return 1;
    }

    out_fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd < 0)
    {
        perror("open output");
        xclose(in_fd);
        return 1;
    }

    // write header
    unsigned int size = (unsigned int)st.st_size;
    unsigned char hdr[4];
    hdr[0] = (unsigned char)(size & 0xFF);
    hdr[1] = (unsigned char)((size >> 8) & 0xFF);
    hdr[2] = (unsigned char)((size >> 16) & 0xFF);
    hdr[3] = (unsigned char)((size >> 24) & 0xFF);

    if (write(out_fd, hdr, 4) != 4)
    {
        perror("write header");
        xclose(in_fd);
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    // Pack 7 bits at a time
    unsigned int bitbuf = 0;
    int bitcount = 0;
    unsigned char ch;
    ssize_t r;

    while ((r = read(in_fd, &ch, 1)) == 1)
    {
        if (ch & 0x80)
        {
            fprintf(stderr, "Error: file is not compressible (found 8th-bit-set byte).\n");
            xclose(in_fd);
            xclose(out_fd);
            unlink(out_file);
            return 1;
        }

        bitbuf |= ((unsigned int)(ch & 0x7F)) << bitcount;
        bitcount += 7;

        while (bitcount >= 8)
        {
            unsigned char outb = (unsigned char)(bitbuf & 0xFF);
            if (write(out_fd, &outb, 1) != 1)
            {
                perror("write compressed");
                xclose(in_fd);
                xclose(out_fd);
                unlink(out_file);
                return 1;
            }
            bitbuf >>= 8;
            bitcount -= 8;
        }
    }

    if (r < 0)
    {
        perror("read input");
        xclose(in_fd);
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    if (bitcount > 0)
    {
        unsigned char outb = (unsigned char)(bitbuf & 0xFF);
        if (write(out_fd, &outb, 1) != 1)
        {
            perror("write final byte");
            xclose(in_fd);
            xclose(out_fd);
            unlink(out_file);
            return 1;
        }
    }

    if (close(in_fd) < 0)
    {
        perror("close input");
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    if (close(out_fd) < 0)
    {
        perror("close output");
        unlink(out_file);
        return 1;
    }

    if (unlink(in_file) < 0)
    {
        perror("unlink original");
        return 1;
    }

    return 0;
}

// Decompress by extracting 7-bit chars from 8-bit bytes
static int do_decompress(const char *in_file, const char *out_file)
{
    int in_fd = -1, out_fd = -1;

    in_fd = open(in_file, O_RDONLY);
    if (in_fd < 0)
    {
        perror("open input");
        return 1;
    }

    out_fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd < 0)
    {
        perror("open output");
        xclose(in_fd);
        return 1;
    }

    /* Read 4-byte header */
    unsigned char hdr[4];
    if (read(in_fd, hdr, 4) != 4)
    {
        fprintf(stderr, "Error: bad input file (missing header).\n");
        xclose(in_fd);
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    unsigned int size =
        ((unsigned int)hdr[0]) |
        ((unsigned int)hdr[1] << 8) |
        ((unsigned int)hdr[2] << 16) |
        ((unsigned int)hdr[3] << 24);

    /* Extract 7 bits at a time */
    unsigned int produced = 0;
    unsigned int bitbuf = 0;
    int bitcount = 0;
    unsigned char byte;
    ssize_t r;

    while (produced < size && (r = read(in_fd, &byte, 1)) == 1)
    {
        bitbuf |= ((unsigned int)byte) << bitcount;
        bitcount += 8;

        while (bitcount >= 7 && produced < size)
        {
            unsigned char outc = (unsigned char)(bitbuf & 0x7F);
            if (write(out_fd, &outc, 1) != 1)
            {
                perror("write decompressed");
                xclose(in_fd);
                xclose(out_fd);
                unlink(out_file);
                return 1;
            }
            bitbuf >>= 7;
            bitcount -= 7;
            produced++;
        }
    }

    if (r < 0)
    {
        perror("read compressed");
        xclose(in_fd);
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    if (produced != size)
    {
        fprintf(stderr, "Error: decompression failed (unexpected end of file).\n");
        xclose(in_fd);
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    if (close(in_fd) < 0)
    {
        perror("close input");
        xclose(out_fd);
        unlink(out_file);
        return 1;
    }

    if (close(out_fd) < 0)
    {
        perror("close output");
        unlink(out_file);
        return 1;
    }

    if (unlink(in_file) < 0)
    {
        perror("unlink original");
        return 1;
    }

    return 0;
}

// Main function
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *in_file = argv[1];
    int decompress = is_z827(in_file);

    char *outfile = out_name(in_file, decompress);
    if (!outfile)
    {
        fprintf(stderr, "Error: cannot build output file name.\n");
        return 1;
    }

    int rc = decompress ? do_decompress(in_file, outfile)
                        : do_compress(in_file, outfile);

    free(outfile);
    return rc;
}