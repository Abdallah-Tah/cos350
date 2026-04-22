Name: Abdallah Mohamed
Course: COS 350
Experiment 22 - output append
Date: April 21, 2026

Question: When we use >> to append, does the shell use auto-append
mode (O_APPEND) or does it just seek to the end and write?

In lecture 13 (devices) we learned about fcntl and the O_APPEND flag.
The lecture showed that without append mode, if two users both do
lseek to end and then write, they can seek to the same spot and
overwrite each other (the "chaos" picture). With O_APPEND, the seek
and the write happen together as one step, so nothing gets lost.

Experiment:
I wrote two shell scripts that each append 1000 lines to the same
file output.txt using >>. One writes "A line 1", "A line 2"... and
the other writes "B line 1", "B line 2"... I run them at the same
time with & and wait for both to finish. Then I count the lines.

Files:
    writer.sh  - writes 1000 lines with a label (A or B)
    test.sh    - runs two writers at the same time and counts lines

To run:
    chmod +x writer.sh test.sh
    ./test.sh

If >> uses O_APPEND, both writers will add their lines to the end of
the file without overwriting each other. Total lines should be 2000.

If >> only seeks to the end, the two writers might seek to the same
position and one will overwrite the other. Total lines would be less
than 2000.

Results:
(Paste output from running ./test.sh on the server)

Conclusion:
(Fill in after running the experiment)
