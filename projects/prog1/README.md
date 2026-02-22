
Author: Abdallah Mohamed
Date:   February 12, 2026
Project 1: myexpand

Test runs:

./myexpand -t 3 < tabtest.txt
The hidden message appears to be GOOD JOB.

abdallah.mohamed@ant:~/projects/prog1$ ./myexpand -t 3 < tabtest.txt
tab test for prog1 in COS350
   0
1  1
22 2
333   3
4444  4
55555 5
666666   6
7777777  7
88888888 8
1  1  1  1  1
22 22 22 22 22
333   333   333   333   333

 #####  ####### ####### ######               # ####### ######
#     # #     # #     # #     #              # #     # #     #
#       #     # #     # #     #              # #     # #     #
#  #### #     # #     # #     #              # #     # ######
#     # #     # #     # #     #        #     # #     # #     #
#     # #     # #     # #     #        #     # #     # #     #
 #####  ####### ####### ######          #####  ####### ######


./myexpand < tabtest.txt

The message does not appears clearly.
abdallah.mohamed@ant:~/projects/prog1$ ./myexpand < tabtest.txt
tab test for prog1 in COS350
        0
1       1
22      2
333     3
4444    4
55555   5
666666  6
7777777 7
88888888        8
1       1       1       1       1
22      22      22      22      22
333     333     333     333     333

 #####  ####### ####### ######                                  # ####### ######
#               # #       # #            # #            #                                       # #       # #            #
#                 #       # #            # #            #                                       # #       # #            #
#       #### #    # #            # #            #                                       # #       # ######
#               # #       # #            # #            #                       #               # #       # #            #
#               # #       # #            # #            #                       #               # #       # #            #
 #####  ####### ####### ######                   #####  ####### ######


./myexpand 3 < tabtest.txt
This cmd failed to run because the output shows an error message.

Error: invalid command line arguments.
Usage: ./myexpand [-t tabstop]
