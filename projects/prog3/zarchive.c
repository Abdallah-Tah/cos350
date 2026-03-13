/*
 * Author: Abdallah Mohamed
 * Date:   March 13, 2026
 * Program 3 - zarchive
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <utime.h>
#include <fcntl.h>

#define MAX_NAME 256
#define MAX_OWNER 64
#define MAX_LINE 2048
#define MAX_FILES 256
#define BUFFER_SIZE 4096

struct header
{
    unsigned int uid;
    char owner[64];
    unsigned int n_files;
};

struct file_info
{
    size_t size;
    time_t timestamp;
    char file_name[256];
    unsigned int options;
};

// Check if a file or directory exists
int file_exists(const char *name);
int get_archive_name(char *archive_name, size_t size, int argc, char *argv[]);
void add_z_extension(char *name, size_t size);
void get_user_name(unsigned int *uid, char *owner);
int file_filter(const struct dirent *entry);
int file_compare(const struct dirent **a, const struct dirent **b);
void format_time_string(time_t t, char *buffer, size_t size);
int show_current_files(void);
int get_all_files(char files[][MAX_NAME], int max_files, const char *skip_name);
int get_selected_files(char files[][MAX_NAME], int max_files, const char *skip_name);
int create_archive(const char *archive_name, int use_compression);
int add_one_file(FILE *archive_fp, const char *file_name, int use_compression);
void show_archive_contents(const char *archive_name);
int extract_archive(const char *archive_name, const char *extract_dir);
void make_output_path(char *out, size_t size, const char *dir, const char *file_name);
// Check if the file name is safe
int safe_file_name(const char *name);
int is_compressible(const unsigned char *data, size_t size);
unsigned char *z827_compress(const unsigned char *input, size_t input_size, size_t *output_size);
unsigned char *z827_decompress(const unsigned char *input, size_t input_size, size_t *output_size);

// Main function
int main(int argc, char *argv[])
{
    char archive_name[MAX_NAME];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s c [archive.z]\n", argv[0]);
        fprintf(stderr, "       %s cz [archive.z]\n", argv[0]);
        fprintf(stderr, "       %s x archive.z [dir]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "c") == 0)
    {
        if (get_archive_name(archive_name, sizeof(archive_name), argc, argv) != 0)
            return 1;

        return create_archive(archive_name, 0);
    }

    if (strcmp(argv[1], "cz") == 0)
    {
        if (get_archive_name(archive_name, sizeof(archive_name), argc, argv) != 0)
            return 1;

        return create_archive(archive_name, 1);
    }

    if (strcmp(argv[1], "x") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "Error: archive file name is required for x mode\n");
            return 1;
        }

        return extract_archive(argv[2], argc >= 4 ? argv[3] : NULL);
    }

    fprintf(stderr, "Error: mode must be c, cz, or x\n");
    return 1;
}

// Check if a file or directory exists
int file_exists(const char *name)
{
    struct stat info;
    return stat(name, &info) == 0;
}

// Check if the file name is safe
int safe_file_name(const char *name)
{
    int i;

    if (name[0] == '\0')
        return 0;

    for (i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '/')
            return 0;
    }

    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
        return 0;

    return 1;
}

// Check if the file can be compressed
int is_compressible(const unsigned char *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        if (data[i] & 0x80)
            return 0;
    }
    return 1;
}

// Compress with z827
unsigned char *z827_compress(const unsigned char *input, size_t input_size, size_t *output_size)
{
    unsigned char *output;
    unsigned int bitbuf = 0;
    int bitcount = 0;
    size_t in_pos = 0;
    size_t out_pos = 0;
    size_t max_out;

    // Calculate max output size
    max_out = 4 + ((input_size * 7 + 7) / 8) + 1;
    output = (unsigned char *)malloc(max_out);
    if (!output)
        return NULL;

    // Write 4-byte header
    output[out_pos++] = (unsigned char)(input_size & 0xFF);
    output[out_pos++] = (unsigned char)((input_size >> 8) & 0xFF);
    output[out_pos++] = (unsigned char)((input_size >> 16) & 0xFF);
    output[out_pos++] = (unsigned char)((input_size >> 24) & 0xFF);

    // Pack 7 bits at a time
    while (in_pos < input_size)
    {
        bitbuf |= ((unsigned int)(input[in_pos] & 0x7F)) << bitcount;
        bitcount += 7;
        in_pos++;

        while (bitcount >= 8)
        {
            output[out_pos++] = (unsigned char)(bitbuf & 0xFF);
            bitbuf >>= 8;
            bitcount -= 8;
        }
    }

    // Write remaining bits
    if (bitcount > 0)
        output[out_pos++] = (unsigned char)(bitbuf & 0xFF);

    *output_size = out_pos;
    return output;
}

// Decompress with z827
unsigned char *z827_decompress(const unsigned char *input, size_t input_size, size_t *output_size)
{
    unsigned char *output;
    unsigned int bitbuf = 0;
    int bitcount = 0;
    size_t in_pos = 0;
    size_t out_pos = 0;
    unsigned int original_size;

    if (input_size < 4)
        return NULL;

    // Read 4-byte header
    original_size = ((unsigned int)input[0]) |
                    ((unsigned int)input[1] << 8) |
                    ((unsigned int)input[2] << 16) |
                    ((unsigned int)input[3] << 24);
    in_pos = 4;

    output = (unsigned char *)malloc(original_size);
    if (!output)
        return NULL;

    // Unpack 7 bits at a time
    while (out_pos < original_size && in_pos < input_size)
    {
        bitbuf |= ((unsigned int)input[in_pos++]) << bitcount;
        bitcount += 8;

        while (bitcount >= 7 && out_pos < original_size)
        {
            output[out_pos++] = (unsigned char)(bitbuf & 0x7F);
            bitbuf >>= 7;
            bitcount -= 7;
        }
    }

    *output_size = out_pos;
    return output;
}

// Get archive name
int get_archive_name(char *archive_name, size_t size, int argc, char *argv[])
{
    if (argc >= 3)
    {
        strncpy(archive_name, argv[2], size - 1);
        archive_name[size - 1] = '\0';
    }
    else
    {
        printf("Enter archive file name: ");

        if (fgets(archive_name, (int)size, stdin) == NULL)
        {
            fprintf(stderr, "Error: could not read archive name\n");
            return 1;
        }

        archive_name[strcspn(archive_name, "\n")] = '\0';
    }

    if (archive_name[0] == '\0')
    {
        fprintf(stderr, "Error: archive name cannot be empty\n");
        return 1;
    }

    add_z_extension(archive_name, size);
    return 0;
}

// Add .z extension if it is missing
void add_z_extension(char *name, size_t size)
{
    size_t len = strlen(name);

    if (len >= 2 && strcmp(name + len - 2, ".z") == 0)
        return;

    if (len + 2 < size)
        strcat(name, ".z");
}

// Get user id and owner name
void get_user_name(unsigned int *uid, char *owner)
{
    struct passwd *pw;

    *uid = getuid();
    pw = getpwuid(*uid);

    if (pw == NULL)
    {
        snprintf(owner, MAX_OWNER, "uid%u", *uid);
        return;
    }

    strncpy(owner, pw->pw_name, MAX_OWNER - 1);
    owner[MAX_OWNER - 1] = '\0';
}

// Filter files for scandir
int file_filter(const struct dirent *entry)
{
    struct stat info;

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        return 0;

    if (stat(entry->d_name, &info) != 0)
        return 0;

    if (S_ISREG(info.st_mode))
        return 1;

    return 0;
}

// Compare file names
int file_compare(const struct dirent **a, const struct dirent **b)
{
    return strcmp((*a)->d_name, (*b)->d_name);
}

// Format modification time for display
void format_time_string(time_t t, char *buffer, size_t size)
{
    struct tm *tm_info;

    tm_info = localtime(&t);
    if (tm_info == NULL)
    {
        strncpy(buffer, "unknown", size - 1);
        buffer[size - 1] = '\0';
        return;
    }

    strftime(buffer, size, "%b %d %H:%M", tm_info);
}

// Show regular files in the current directory
int show_current_files(void)
{
    struct dirent **list;
    struct stat info;
    char time_string[64];
    int count;
    int i;

    count = scandir(".", &list, file_filter, file_compare);
    if (count < 0)
    {
        perror("scandir");
        return -1;
    }

    printf("\nFiles in current directory:\n");
    printf("%-12s %-16s %s\n", "Size", "Modified", "Name");

    for (i = 0; i < count; i++)
    {
        if (stat(list[i]->d_name, &info) == 0)
        {
            format_time_string(info.st_mtime, time_string, sizeof(time_string));
            printf("%-12ld %-16s %s\n",
                   (long)info.st_size,
                   time_string,
                   list[i]->d_name);
        }

        free(list[i]);
    }

    free(list);
    return count;
}

// Get all regular files except the archive itself
int get_all_files(char files[][MAX_NAME], int max_files, const char *skip_name)
{
    struct dirent **list;
    int count;
    int i;
    int used = 0;

    count = scandir(".", &list, file_filter, file_compare);
    if (count < 0)
    {
        perror("scandir");
        return -1;
    }

    for (i = 0; i < count && used < max_files; i++)
    {

        if (skip_name != NULL &&
            strcmp(list[i]->d_name, skip_name) == 0)
        {
            free(list[i]);
            continue;
        }

        strncpy(files[used], list[i]->d_name, MAX_NAME - 1);
        files[used][MAX_NAME - 1] = '\0';
        used++;

        free(list[i]);
    }

    free(list);
    return used;
}

// Read selected file names from the user
int get_selected_files(char files[][MAX_NAME], int max_files, const char *skip_name)
{
    char input[MAX_LINE];
    char *token;
    int count = 0;

    printf("\nEnter file names to archive (* for all): ");

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: could not read file list\n");
        return -1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "*") == 0)
        return get_all_files(files, max_files, skip_name);

    token = strtok(input, " \t");

    while (token != NULL && count < max_files)
    {

        if (skip_name != NULL && strcmp(token, skip_name) == 0)
        {
            token = strtok(NULL, " \t");
            continue;
        }

        if (!safe_file_name(token))
        {
            fprintf(stderr, "Warning: skipping %s (bad file name)\n", token);
            token = strtok(NULL, " \t");
            continue;
        }

        if (!file_exists(token))
        {
            fprintf(stderr, "Warning: skipping %s (file does not exist)\n", token);
            token = strtok(NULL, " \t");
            continue;
        }

        strncpy(files[count], token, MAX_NAME - 1);
        files[count][MAX_NAME - 1] = '\0';
        count++;

        token = strtok(NULL, " \t");
    }

    return count;
}

// Add a file to the archive
int add_one_file(FILE *archive_fp, const char *file_name, int use_compression)
{
    FILE *infile;
    struct stat info;
    struct file_info entry;
    unsigned char *file_data = NULL;
    unsigned char *compressed_data = NULL;
    size_t compressed_size = 0;
    size_t bytes_read;

    if (stat(file_name, &info) != 0)
    {
        fprintf(stderr, "Warning: cannot stat %s\n", file_name);
        return 0;
    }

    if (!S_ISREG(info.st_mode))
    {
        fprintf(stderr, "Warning: skipping %s (not a regular file)\n", file_name);
        return 0;
    }

    infile = fopen(file_name, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "Warning: cannot open %s\n", file_name);
        return 0;
    }

    entry.size = info.st_size;
    entry.timestamp = info.st_mtime;

    memset(entry.file_name, 0, sizeof(entry.file_name));
    strncpy(entry.file_name, file_name, sizeof(entry.file_name) - 1);

    entry.options = 0;

    // Try compression
    if (use_compression && entry.size > 0)
    {
        file_data = (unsigned char *)malloc(entry.size);
        if (file_data != NULL)
        {
            bytes_read = fread(file_data, 1, entry.size, infile);
            if (bytes_read == entry.size && is_compressible(file_data, entry.size))
            {
                compressed_data = z827_compress(file_data, entry.size, &compressed_size);
                if (compressed_data != NULL)
                {
                    entry.options = 1;
                    entry.size = compressed_size;
                }
            }
            if (compressed_data == NULL)
                rewind(infile);
        }
        else
        {
            rewind(infile);
        }
    }

    if (fwrite(&entry, sizeof(entry), 1, archive_fp) != 1)
    {
        fprintf(stderr, "Error: could not write header for %s\n", file_name);
        fclose(infile);
        if (file_data)
            free(file_data);
        if (compressed_data)
            free(compressed_data);
        return 0;
    }

    // Write compressed or original data
    if (compressed_data != NULL)
    {
        if (fwrite(compressed_data, 1, compressed_size, archive_fp) != compressed_size)
        {
            fprintf(stderr, "Error: could not write data for %s\n", file_name);
            fclose(infile);
            free(file_data);
            free(compressed_data);
            return 0;
        }
        free(compressed_data);
        free(file_data);
    }
    else
    {
        char buffer[BUFFER_SIZE];
        bytes_read = fread(buffer, 1, sizeof(buffer), infile);

        while (bytes_read > 0)
        {
            if (fwrite(buffer, 1, bytes_read, archive_fp) != bytes_read)
            {
                fprintf(stderr, "Error: could not write data for %s\n", file_name);
                fclose(infile);
                if (file_data)
                    free(file_data);
                return 0;
            }

            bytes_read = fread(buffer, 1, sizeof(buffer), infile);
        }
        if (file_data)
            free(file_data);
    }

    fclose(infile);
    return 1;
}

// Create archive and add files
int create_archive(const char *archive_name, int use_compression)
{
    FILE *archive_fp;
    struct header archive_header;
    char owner[MAX_OWNER];
    char files[MAX_FILES][MAX_NAME];
    int file_count;
    int i;
    unsigned int archived = 0;

    if (file_exists(archive_name))
    {
        fprintf(stderr, "Error: %s already exists\n", archive_name);
        return 1;
    }

    get_user_name(&archive_header.uid, owner);

    memset(archive_header.owner, 0, sizeof(archive_header.owner));
    strncpy(archive_header.owner, owner, MAX_OWNER - 1);

    archive_header.n_files = 0;

    printf("Archive owner: %s\n", archive_header.owner);

    if (show_current_files() < 0)
        return 1;

    file_count = get_selected_files(files, MAX_FILES, archive_name);

    if (file_count <= 0)
    {
        fprintf(stderr, "Error: no files selected\n");
        return 1;
    }

    archive_fp = fopen(archive_name, "wb");
    if (archive_fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    if (fwrite(&archive_header, sizeof(archive_header), 1, archive_fp) != 1)
    {
        fprintf(stderr, "Error: could not write archive header\n");
        fclose(archive_fp);
        return 1;
    }

    for (i = 0; i < file_count; i++)
        if (add_one_file(archive_fp, files[i], use_compression))
            archived++;

    archive_header.n_files = archived;

    fseek(archive_fp, 0, SEEK_SET);
    if (fwrite(&archive_header, sizeof(archive_header), 1, archive_fp) != 1)
    {
        fprintf(stderr, "Error: could not update archive header\n");
        fclose(archive_fp);
        return 1;
    }

    fclose(archive_fp);

    printf("\nCreated %s with %u file(s)\n", archive_name, archived);

    show_archive_contents(archive_name);

    return 0;
}

// Show archive contents
void show_archive_contents(const char *archive_name)
{
    FILE *archive_fp;
    struct header archive_header;
    struct file_info entry;
    char time_string[64];
    unsigned int i;

    archive_fp = fopen(archive_name, "rb");

    if (archive_fp == NULL)
    {
        fprintf(stderr, "Error: could not open archive\n");
        return;
    }

    if (fread(&archive_header, sizeof(archive_header), 1, archive_fp) != 1)
    {
        fprintf(stderr, "Error: could not read archive header\n");
        fclose(archive_fp);
        return;
    }

    printf("\nArchive contents:\n");
    printf("Owner: %s\n", archive_header.owner);
    printf("Files: %u\n", archive_header.n_files);
    printf("%-12s %-16s %s\n", "Size", "Modified", "Name");

    for (i = 0; i < archive_header.n_files; i++)
    {

        if (fread(&entry, sizeof(entry), 1, archive_fp) != 1)
        {
            fprintf(stderr, "Error: could not read file entry\n");
            fclose(archive_fp);
            return;
        }

        format_time_string(entry.timestamp, time_string, sizeof(time_string));

        printf("%-12ld %-16s %s\n",
               (long)entry.size,
               time_string,
               entry.file_name);

        fseek(archive_fp, entry.size, SEEK_CUR);
    }

    fclose(archive_fp);
}

// Build output path for extracted file
void make_output_path(char *out, size_t size, const char *dir, const char *file_name)
{
    if (dir == NULL)
        snprintf(out, size, "%s", file_name);
    else
        snprintf(out, size, "%s/%s", dir, file_name);
}

// Extract all files from the archive
int extract_archive(const char *archive_name, const char *extract_dir)
{
    FILE *archive_fp;
    FILE *outfile;
    struct header archive_header;
    struct file_info entry;
    struct utimbuf times;
    char out_path[512];
    char buffer[BUFFER_SIZE];
    size_t left;
    size_t chunk;
    size_t r;
    unsigned int i;

    if (!file_exists(archive_name))
    {
        fprintf(stderr, "Error: archive %s does not exist\n", archive_name);
        return 1;
    }

    if (extract_dir != NULL)
    {

        if (file_exists(extract_dir))
        {
            fprintf(stderr, "Error: directory %s already exists\n", extract_dir);
            return 1;
        }

        if (mkdir(extract_dir, 0755) != 0)
        {
            perror("mkdir");
            return 1;
        }
    }
    else
    {
        printf("Warning: extracting into current directory\n");
    }

    archive_fp = fopen(archive_name, "rb");

    if (archive_fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    if (fread(&archive_header, sizeof(archive_header), 1, archive_fp) != 1)
    {
        fprintf(stderr, "Error: could not read archive header\n");
        fclose(archive_fp);
        return 1;
    }

    printf("Archive owner: %s\n", archive_header.owner);
    printf("Extracting %u file(s)\n", archive_header.n_files);

    for (i = 0; i < archive_header.n_files; i++)
    {

        if (fread(&entry, sizeof(entry), 1, archive_fp) != 1)
        {
            fprintf(stderr, "Error: could not read file entry\n");
            fclose(archive_fp);
            return 1;
        }

        make_output_path(out_path, sizeof(out_path), extract_dir, entry.file_name);

        if (file_exists(out_path))
        {
            fprintf(stderr, "Error: %s already exists, will not overwrite\n", out_path);
            fclose(archive_fp);
            return 1;
        }

        outfile = fopen(out_path, "wb");

        if (outfile == NULL)
        {
            fprintf(stderr, "Error: could not create %s\n", out_path);
            fclose(archive_fp);
            return 1;
        }

        // Check for compression
        if (entry.options & 1)
        {
            unsigned char *compressed_data;
            unsigned char *decompressed_data;
            size_t decompressed_size;

            compressed_data = (unsigned char *)malloc(entry.size);
            if (compressed_data == NULL)
            {
                fprintf(stderr, "Error: out of memory\n");
                fclose(outfile);
                fclose(archive_fp);
                return 1;
            }

            r = fread(compressed_data, 1, entry.size, archive_fp);
            if (r != entry.size)
            {
                fprintf(stderr, "Error: could not read compressed data\n");
                free(compressed_data);
                fclose(outfile);
                fclose(archive_fp);
                return 1;
            }

            decompressed_data = z827_decompress(compressed_data, entry.size, &decompressed_size);
            free(compressed_data);

            if (decompressed_data == NULL)
            {
                fprintf(stderr, "Error: decompression failed for %s\n", out_path);
                fclose(outfile);
                fclose(archive_fp);
                return 1;
            }

            if (fwrite(decompressed_data, 1, decompressed_size, outfile) != decompressed_size)
            {
                fprintf(stderr, "Error: could not write decompressed data for %s\n", out_path);
                free(decompressed_data);
                fclose(outfile);
                fclose(archive_fp);
                return 1;
            }
            free(decompressed_data);
        }
        else
        {
            left = entry.size;

            while (left > 0)
            {

                chunk = left > BUFFER_SIZE ? BUFFER_SIZE : left;

                r = fread(buffer, 1, chunk, archive_fp);

                if (fwrite(buffer, 1, r, outfile) != r)
                {
                    fprintf(stderr, "Error: could not write data for %s\n", out_path);
                    fclose(outfile);
                    fclose(archive_fp);
                    return 1;
                }

                left -= r;
            }
        }

        fclose(outfile);

        times.actime = entry.timestamp;
        times.modtime = entry.timestamp;

        utime(out_path, &times);

        printf("Extracted %s\n", out_path);
    }

    fclose(archive_fp);

    return 0;
}
