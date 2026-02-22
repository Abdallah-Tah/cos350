Name: Abdallah Mohamed
Course: COS 350
Experiment 10
Date: Feb. 21, 2026

The RGB values for chartreuse are 127 255 0.

abdallah.mohamed@ant:~/experiments$ cd ..
abdallah.mohamed@ant:~$ cd ..
abdallah.mohamed@ant:/home$ cd ..
abdallah.mohamed@ant:/$ cd usr
abdallah.mohamed@ant:/usr$ find -name rgb.txt
./share/netpbm/rgb.txt
./share/X11/rgb.txt
find: ‘./local/anaconda’: Permission denied
find: ‘./local/cuda-12.6’: Permission denied
abdallah.mohamed@ant:/usr$ grep -i chartreuse /usr/share/netpbm/rgb.txt
127 255   0 Chartreuse
127 255	  0 Chartreuse1
118 238	  0 Chartreuse2
102 205	  0 Chartreuse3
 69 139	  0 Chartreuse4
abdallah.mohamed@ant:/usr$ grep -i chartreuse /usr/share/X11/rgb.txt
127 255   0		chartreuse
127 255	  0		chartreuse1
118 238	  0		chartreuse2
102 205	  0		chartreuse3
 69 139	  0		chartreuse4
abdallah.mohamed@ant:/usr$ 
