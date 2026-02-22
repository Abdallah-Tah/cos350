
Yes, I see a pattern.

For small sizes like 1, 4, and 16 bytes, the difference between the first and last block is almost the same. 
This means that even if I request very small memory, malloc uses about the same amount of space each time.

When the size increases to 32 bytes and 64 bytes, the difference becomes larger. 
So the memory does not increase little by little. It increases in steps.

Output:
abdallah.mohamed@ant:~/experiments/e9$ gcc malloc.c -o malloc
abdallah.mohamed@ant:~/experiments/e9$ ./malloc

Size of malloc: 1 bytes
Address of first block (array[0]): 0x5c71a900f2a0
Address of last block (array[1000]): 0x5c71a9016fa0
Difference between array 0 and array 1000: 32000

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 2 bytes
Address of first block (array[0]): 0x5c71a900f360
Address of last block (array[1000]): 0x5c71a900f380
Difference between array 0 and array 1000: 32

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 4 bytes
Address of first block (array[0]): 0x5c71a900f2a0
Address of last block (array[1000]): 0x5c71a9016fa0
Difference between array 0 and array 1000: 32000

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 8 bytes
Address of first block (array[0]): 0x5c71a900f360
Address of last block (array[1000]): 0x5c71a900f380
Difference between array 0 and array 1000: 32

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 16 bytes
Address of first block (array[0]): 0x5c71a900f2a0
Address of last block (array[1000]): 0x5c71a9016fa0
Difference between array 0 and array 1000: 32000

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 32 bytes
Address of first block (array[0]): 0x5c71a90173d0
Address of last block (array[1000]): 0x5c71a9022f50
Difference between array 0 and array 1000: 48000

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 64 bytes
Address of first block (array[0]): 0x5c71a9022f80
Address of last block (array[1000]): 0x5c71a9015b90
Difference between array 0 and array 1000: 54256

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 128 bytes
Address of first block (array[0]): 0x5c71a9015be0
Address of last block (array[1000]): 0x5c71a9032e40
Difference between array 0 and array 1000: 119392

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000

Size of malloc: 256 bytes
Address of first block (array[0]): 0x5c71a9015fd0
Address of last block (array[1000]): 0x5c71a9052630
Difference between array 0 and array 1000: 247392

Array element addresses:
&array[0]: 0x7fff55971890
&array[1000]: 0x7fff559737d0
Array element difference: 8000
abdallah.mohamed@ant:~/experiments/e9$ 