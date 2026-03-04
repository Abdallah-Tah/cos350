Author: Abdallah Mohamed
Date: February 27, 2026
Program 2 - z827 Compression

DESCRIPTION
This program compresses and decompresses text files using 7-bit encoding.
It works by removing the unused 8th bit from ASCII characters and packing
them together to save space (about 12.5% smaller).

COMPLETENESS
All required features are implemented and working correctly:
- Compression with .z827 extension
- Decompression by removing .z827 extension
- 4-byte header with original file size
- Error checking for non-7-bit files
- Proper file deletion (only after successful write)
- All system calls from section 2 (open, read, write, close, unlink, fstat)

KNOWN ISSUES
None. The program works correctly on all test cases.

DEVIATIONS FROM SPECIFICATION
None. I followed all requirements from the assignment.

EXTRA FEATURES
- I check the return value of close() which is more careful than required
- I use fstat() to check that the input is a regular file (not a directory)
- I clean up partial output files if any error happens during compression

TESTING
I tested the program with:
- Small text files (short.txt)
- Large text files (shake.txt)
- Files with bad characters (8th bit set)
- Missing files
- No command line arguments
- Directories instead of files

All tests passed correctly.

SELF-EVALUATION

Manual Page (20pts):
	X works  _ mostly works _ sometimes works _ not implemented

Reading the input file using read() (5pts):
	X works  _ mostly works _ sometimes works _ not implemented

Creating the correctly named output file (5pts):
	X works  _ mostly works _ sometimes works _ not implemented

Correctly compressing data (30pts):
	X works  _ mostly works _ sometimes works _ not implemented

Correct file size at the start of the file (5pts):
	X works  _ mostly works _ sometimes works _ not implemented

Removing old file after processing (5pts):
	X works  _ mostly works _ sometimes works _ not implemented

Decompression (20pts):
	X works  _ mostly works _ sometimes works _ not implemented

Error Handling (10pts):
	X works  _ mostly works _ sometimes works _ not implemented

TOTAL: 100 points

WHAT I LEARNED
- How to use bit shifting operators (<<, >>, &, |)
- How to work with binary files using system calls
- The importance of checking return values for all system calls
- How to use a bit buffer to pack and unpack bits
- Memory management with malloc() and free()
- Why it is important to only delete files after successful operations
