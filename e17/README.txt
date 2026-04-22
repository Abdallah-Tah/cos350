Name: Abdallah Mohamed
Course: COS 350
Experiment 17 - ps
Date: April 07, 2026

The ps command showed only 2 processes: bash and ps.
The ps aux command showed all processes running on the system.

My account has more processes than shown by ps. I only knew about bash and ps.
I did not know about other processes such as systemd, migration, and daemon.


Results:
abdallah.mohamed@ant:~/exp17$ ps
    PID TTY          TIME CMD
2138903 pts/7    00:00:00 bash
2138981 pts/7    00:00:00 ps

abdallah.mohamed@ant:~/exp17$ ps
    PID TTY          TIME CMD
2138903 pts/7    00:00:00 bash
2138981 pts/7    00:00:00 ps
abdallah.mohamed@ant:~/exp17$ ps aux
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.6  0.1  51220 40332 ?        Rs   Mar24 134:11 /usr/lib/syst
root           2  0.0  0.0      0     0 ?        S    Mar24   0:00 [kthreadd]
root           3  0.0  0.0      0     0 ?        S    Mar24   0:00 [pool_workque
root           4  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-rc
root           5  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-rc
root           6  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sl
root           7  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ne
root           9  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/0:0H
root          12  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-mm
root          13  0.0  0.0      0     0 ?        I    Mar24   0:00 [rcu_tasks_kt
root          14  0.0  0.0      0     0 ?        I    Mar24   0:00 [rcu_tasks_ru
root          15  0.0  0.0      0     0 ?        I    Mar24   0:00 [rcu_tasks_tr
root          16  0.0  0.0      0     0 ?        S    Mar24   0:14 [ksoftirqd/0]
root          17  0.0  0.0      0     0 ?        I    Mar24  16:42 [rcu_preempt]
root          18  0.0  0.0      0     0 ?        S    Mar24   0:43 [migration/0]
root          19  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          20  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/0]
root          21  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/1]
root          22  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          23  0.0  0.0      0     0 ?        S    Mar24   0:45 [migration/1]
root          24  0.0  0.0      0     0 ?        S    Mar24   0:05 [ksoftirqd/1]
root          26  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/1:0H
root          27  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/2]
root          28  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          29  0.0  0.0      0     0 ?        S    Mar24   1:05 [migration/2]
root          30  0.0  0.0      0     0 ?        S    Mar24   0:03 [ksoftirqd/2]
root          32  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/2:0H
root          33  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/3]
root          34  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          35  0.0  0.0      0     0 ?        S    Mar24   1:01 [migration/3]
root          36  0.0  0.0      0     0 ?        S    Mar24   0:02 [ksoftirqd/3]
root          38  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/3:0H
root          39  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/4]
root          40  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          41  0.0  0.0      0     0 ?        S    Mar24   0:37 [migration/4]
root          42  0.0  0.0      0     0 ?        S    Mar24   0:02 [ksoftirqd/4]
root          44  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/4:0H
root          45  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/5]
root          46  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          47  0.0  0.0      0     0 ?        S    Mar24   0:29 [migration/5]
root          48  0.0  0.0      0     0 ?        S    Mar24   0:02 [ksoftirqd/5]
root          50  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/5:0H
root          51  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/6]
root          52  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          53  0.0  0.0      0     0 ?        S    Mar24   0:30 [migration/6]
root          54  0.0  0.0      0     0 ?        S    Mar24   0:02 [ksoftirqd/6]
root          56  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/6:0H
root          57  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/7]
root          58  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          59  0.0  0.0      0     0 ?        S    Mar24   0:31 [migration/7]
root          60  0.0  0.0      0     0 ?        S    Mar24   0:01 [ksoftirqd/7]
root          62  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/7:0H
root          63  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/8]
root          64  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          65  0.0  0.0      0     0 ?        S    Mar24   0:22 [migration/8]
root          66  0.0  0.0      0     0 ?        S    Mar24   0:01 [ksoftirqd/8]
root          68  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/8:0H
root          69  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/9]
root          70  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          71  0.0  0.0      0     0 ?        S    Mar24   0:24 [migration/9]
root          72  0.0  0.0      0     0 ?        S    Mar24   0:01 [ksoftirqd/9]
root          74  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/9:0H
root          75  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/10]
root          76  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          77  0.0  0.0      0     0 ?        S    Mar24   0:21 [migration/10
root          78  0.0  0.0      0     0 ?        S    Mar24   0:00 [ksoftirqd/10
root          80  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/10:0
root          81  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/11]
root          82  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          83  0.0  0.0      0     0 ?        S    Mar24   0:20 [migration/11
root          84  0.0  0.0      0     0 ?        S    Mar24   0:00 [ksoftirqd/11
root          86  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/11:0
root          87  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/12]
root          88  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          89  0.0  0.0      0     0 ?        S    Mar24   0:18 [migration/12
root          90  0.0  0.0      0     0 ?        S    Mar24   0:01 [ksoftirqd/12
root          92  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/12:0
root          93  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/13]
root          94  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root          95  0.0  0.0      0     0 ?        S    Mar24   0:17 [migration/13
root          96  0.0  0.0      0     0 ?        S    Mar24   0:01 [ksoftirqd/13
root          98  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/13:0
root          99  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/14]
root         100  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root         101  0.0  0.0      0     0 ?        S    Mar24   0:16 [migration/14
root         102  0.0  0.0      0     0 ?        S    Mar24   0:02 [ksoftirqd/14
root         104  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/14:0
root         105  0.0  0.0      0     0 ?        S    Mar24   0:00 [cpuhp/15]
root         106  0.0  0.0      0     0 ?        S    Mar24   0:00 [idle_inject/
root         107  0.0  0.0      0     0 ?        S    Mar24   0:20 [migration/15
root         108  0.0  0.0      0     0 ?        S    Mar24   0:07 [ksoftirqd/15
root         110  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/15:0
root         111  0.0  0.0      0     0 ?        S    Mar24   0:00 [kdevtmpfs]
root         112  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-in
root         113  0.0  0.0      0     0 ?        S    Mar24   0:00 [kauditd]
root         114  0.0  0.0      0     0 ?        S    Mar24   0:01 [khungtaskd]
root         115  0.0  0.0      0     0 ?        S    Mar24   0:00 [oom_reaper]
root         117  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-wr
root         119  0.0  0.0      0     0 ?        S    Mar24   1:14 [kcompactd0]
root         120  0.0  0.0      0     0 ?        SN   Mar24   0:00 [ksmd]
root         122  0.0  0.0      0     0 ?        SN   Mar24   0:06 [khugepaged]
root         123  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ki
root         124  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-kb
root         125  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-bl
root         126  0.0  0.0      0     0 ?        S    Mar24   0:18 [irq/9-acpi]
root         128  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-tp
root         129  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-at
root         130  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-md
root         131  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-md
root         132  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ed
root         133  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-de
root         134  0.0  0.0      0     0 ?        S    Mar24   0:00 [watchdogd]
root         136  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-qu
root         137  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/7:1H
root         139  0.0  0.0      0     0 ?        S    Mar24   0:29 [kswapd0]
root         140  0.0  0.0      0     0 ?        S    Mar24   0:00 [ecryptfs-kth
root         142  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-kt
root         143  0.0  0.0      0     0 ?        S    Mar24   0:00 [irq/122-aerd
root         144  0.0  0.0      0     0 ?        S    Mar24   0:00 [irq/122-pcie
root         155  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ac
root         156  0.0  0.0      0     0 ?        S    Mar24   0:18 [hwrng]
root         157  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ml
root         158  0.0  0.0      0     0 ?        I<   Mar24   0:04 [kworker/3:1H
root         159  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ip
root         166  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ks
root         168  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/u33:
root         181  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ch
root         205  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/0:1H
root         208  0.0  0.0      0     0 ?        I<   Mar24   0:02 [kworker/4:1H
root         209  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/10:1
root         225  0.0  0.0      0     0 ?        I<   Mar24   0:05 [kworker/2:1H
root         250  0.0  0.0      0     0 ?        I<   Mar24   0:02 [kworker/5:1H
root         251  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/13:1
root         252  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/8:1H
root         264  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/12:1
root         265  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/15:1
root         266  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/1:1H
root         267  0.0  0.0      0     0 ?        I<   Mar24   0:02 [kworker/11:1
root         268  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/6:1H
root         269  0.0  0.0      0     0 ?        I<   Mar24   0:22 [kworker/14:1
root         270  0.0  0.0      0     0 ?        I<   Mar24   0:01 [kworker/9:1H
root         280  0.0  0.0      0     0 ?        S    Mar24   0:00 [scsi_eh_0]
root         281  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sc
root         283  0.0  0.0      0     0 ?        S    Mar24   0:00 [scsi_eh_1]
root         284  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sc
root         285  0.0  0.0      0     0 ?        S    Mar24   0:00 [scsi_eh_2]
root         286  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sc
root         287  0.0  0.0      0     0 ?        S    Mar24   0:00 [scsi_eh_3]
root         288  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sc
root         317  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-US
root         320  0.0  0.0      0     0 ?        S    Mar24   0:00 [scsi_eh_4]
root         321  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-sc
root         322  0.0  0.0      0     0 ?        S    Mar24   2:00 [usb-storage]
root         323  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ua
root         325  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-US
root         364  0.0  0.0      0     0 ?        S    Mar24   0:52 [jbd2/sda2-8]
root         365  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-ex
root         659  0.0  0.0      0     0 ?        S    Mar24   0:00 [irq/133-mei_
root         679  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-cr
root         944  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-tt
root         946  0.0  0.0      0     0 ?        S    Mar24   0:00 [card1-crtc0]
root         947  0.0  0.0      0     0 ?        S    Mar24   0:00 [card1-crtc1]
root         948  0.0  0.0      0     0 ?        S    Mar24   0:00 [card1-crtc2]
root         949  0.0  0.0      0     0 ?        S    Mar24   0:00 [nv_queue]
root         950  0.0  0.0      0     0 ?        S    Mar24   0:00 [nv_queue]
root         951  0.0  0.0      0     0 ?        S    Mar24   0:00 [nv_open_q]
root        1002  0.0  0.0      0     0 ?        S    Mar24   0:00 [nvidia-modes
root        1003  0.0  0.0      0     0 ?        S    Mar24   0:00 [nvidia-modes
root        1009  0.0  0.0      0     0 ?        S    Mar24   0:00 [irq/136-nvid
root        1010  0.0  0.0      0     0 ?        S    Mar24   0:00 [nvidia]
root        1011  0.0  0.0      0     0 ?        S    Mar24   0:00 [nv_queue]
_rpc        1279  0.0  0.0   8084  3416 ?        Ss   Mar24   2:01 /sbin/rpcbind
root        1287  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-rp
root        1288  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-xp
avahi       1426  0.0  0.0  19972  3592 ?        Ss   Mar24   0:03 avahi-daemon:
message+    1429  0.0  0.0  38280  6572 ?        Ss   Mar24   0:21 @dbus-daemon 
polkitd     1491  0.0  0.0 412132 10180 ?        Ssl  Mar24   0:27 /usr/lib/polk
nvidia-+    1503  0.0  0.0   5380  1780 ?        Ss   Mar24   0:00 /usr/bin/nvid
root        1509  0.0  0.0  38088  7080 ?        Ss   Mar24   0:02 /usr/sbin/sss
root        1515  0.0  0.0 424872  7512 ?        Ssl  Mar24   1:00 /usr/sbin/the
root        1517  3.0  0.2 552460 87024 ?        Rsl  Mar24 625:14 /usr/libexec/
avahi       1540  0.0  0.0  19780   920 ?        S    Mar24   0:00 avahi-daemon:
syslog      1610  0.0  0.0 233864  5032 ?        Ssl  Mar24   0:38 /usr/sbin/rsy
root        1648  0.1  0.0 336356 10320 ?        Ssl  Mar24  21:49 /usr/sbin/Net
root        1661  0.0  0.0  17384  3564 ?        Ss   Mar24   0:05 /usr/sbin/wpa
root        1663  0.0  0.0 318364  8132 ?        Ssl  Mar24   0:00 /usr/sbin/Mod
root        1683  0.0  0.0  49616 11928 ?        S    Mar24   0:34 /usr/libexec/
root        1737  0.0  0.0  73448 13384 ?        S    Mar24   0:19 /usr/libexec/
root        1738  0.0  0.0  39536 11824 ?        S    Mar24   0:18 /usr/libexec/
root        1739  0.0  0.0  37072  6616 ?        S    Mar24   0:11 /usr/libexec/
root        1747  0.0  0.0  28080  8680 ?        S    Mar24  18:11 /usr/bin/perl
root        1754  0.0  0.0 323096  7300 ?        Ssl  Mar24   0:50 /usr/libexec/
root        1756  0.0  0.0  28108  8448 ?        Ss   Mar24   0:04 /usr/lib/syst
root        1888  0.0  0.1 1086876 56720 ?       Ssl  Mar24  16:52 /usr/bin/pyth
root        1890  0.0  0.0 117972  6612 ?        Ssl  Mar24   0:00 /usr/bin/pyth
colord      1895  0.0  0.0 320196  8416 ?        Ssl  Mar24   0:00 /usr/libexec/
root        1997  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-nf
root        2016  0.0  0.0      0     0 ?        I    Mar24   0:00 [NFSv4 callba
root        2020  0.0  0.0      0     0 ?        I    Mar24   0:00 [NFSv4 callba
root        2042  0.0  0.0  20004  3208 ?        Ss   Mar24   0:02 /usr/sbin/cro
root        2046  0.0  0.0 685540  4992 ?        Ssl  Mar24   0:56 /usr/sbin/aut
kernoops    2053  0.0  0.0  12744  1632 ?        Ss   Mar24   0:01 /usr/sbin/ker
root        2061  0.0  0.0 389640  5696 ?        SLsl Mar24   0:00 /usr/sbin/lig
kernoops    2064  0.0  0.0  12744  1552 ?        Ss   Mar24   0:01 /usr/sbin/ker
root        2074  0.0  0.0  11428  1328 ?        Ss   Mar24   0:00 nginx: master
www-data    2075  0.0  0.0  24852  7416 ?        S    Mar24   0:04 nginx: worker
www-data    2076  0.0  0.0  25052  7564 ?        S    Mar24   0:05 nginx: worker
www-data    2077  0.0  0.0  24896  7436 ?        S    Mar24   0:04 nginx: worker
www-data    2079  0.0  0.0  24856  7556 ?        S    Mar24   0:04 nginx: worker
www-data    2080  0.0  0.0  24856  7448 ?        S    Mar24   0:04 nginx: worker
www-data    2081  0.0  0.0  24876  7400 ?        S    Mar24   0:03 nginx: worker
www-data    2082  0.0  0.0  25280  7908 ?        S    Mar24   0:04 nginx: worker
www-data    2084  0.0  0.0  25276  7960 ?        S    Mar24   0:03 nginx: worker
www-data    2085  0.0  0.0  24860  7564 ?        S    Mar24   0:05 nginx: worker
www-data    2086  0.0  0.0  24864  7440 ?        S    Mar24   0:03 nginx: worker
www-data    2087  0.0  0.0  24988  7540 ?        S    Mar24   0:03 nginx: worker
www-data    2088  0.0  0.0  25040  7704 ?        S    Mar24   0:03 nginx: worker
www-data    2089  0.0  0.0  24860  7436 ?        S    Mar24   0:03 nginx: worker
www-data    2090  0.0  0.0  24992  7596 ?        S    Mar24   0:04 nginx: worker
www-data    2092  0.0  0.0  24856  7504 ?        S    Mar24   0:05 nginx: worker
www-data    2093  0.0  0.0  24864  7436 ?        S    Mar24   0:04 nginx: worker
root        2099  0.0  0.0   8704  1760 tty1     Ss+  Mar24   0:00 /sbin/agetty 
lightdm     2177  0.6  0.1  49104 37904 ?        Rs   Mar24 131:43 /usr/lib/syst
lightdm     2178  0.0  0.0  32788  1216 ?        S    Mar24   0:00 (sd-pam)
lightdm     2189  0.0  0.0 119164  4852 ?        S<sl Mar24   0:00 /usr/bin/pipe
lightdm     2190  0.0  0.0  97736  3700 ?        Ssl  Mar24   0:00 /usr/bin/pipe
lightdm     2193  0.0  0.0 571732  9508 ?        S<sl Mar24   0:00 /usr/bin/wire
lightdm     2194  0.0  0.0 109400  5856 ?        S<sl Mar24   0:00 /usr/bin/pipe
lightdm     2195  0.0  0.0 316484  5728 ?        Ssl  Mar24   0:00 /usr/bin/gnom
lightdm     2205  0.0  0.0  21084  4232 ?        Ss   Mar24   0:00 /usr/bin/dbus
rtkit       2220  0.0  0.0  22940  3172 ?        SNsl Mar24   0:15 /usr/libexec/
lightdm     2236  0.0  0.0 610292  5740 ?        Ssl  Mar24   0:00 /usr/libexec/
lightdm     2244  0.0  0.0 309308  4724 ?        Ssl  Mar24   0:00 /usr/libexec/
root        2251  0.0  0.0   2704  1988 ?        Ss   Mar24   0:00 fusermount3 -
lightdm     2259  0.0  0.0 382872  5156 ?        Ssl  Mar24   0:00 /usr/libexec/
lightdm     2266  0.0  0.0  20648  3520 ?        S    Mar24   0:00 /usr/bin/dbus
lightdm     2269  0.0  0.0 314160  5124 ?        Ssl  Mar24   0:00 /usr/libexec/
lightdm     2277  0.0  0.0 459708  4664 ?        Sl   Mar24   0:00 /usr/libexec/
lightdm     2325  0.0  0.0 236068  4784 ?        Sl   Mar24   0:00 /usr/libexec/
root       10360  0.0  0.1 648624 36276 ?        Ssl  Mar24   1:15 /usr/libexec/
root       10375  0.0  0.0 317320  7112 ?        Ssl  Mar24   0:00 /usr/libexec/
root       22829  0.0  0.1 26224360 39124 tty7   Ssl+ Mar24   4:53 /usr/lib/xorg
root       22850  0.0  0.0 245688  5552 ?        Sl   Mar24   0:00 lightdm --ses
lightdm    22875  0.0  0.0   2800  1920 ?        Ss   Mar24   0:00 /bin/sh /usr/
lightdm    22876  0.0  0.1 837532 62828 ?        Sl   Mar24   6:18 /usr/sbin/lig
root       22901  0.0  0.0  12520  4152 ?        S    Mar24   0:00 lightdm --ses
root       32230  0.0  0.0      0     0 ?        S    Mar24   0:00 [UVM global q
root       32231  0.0  0.0      0     0 ?        S    Mar24   0:00 [UVM deferred
root       32232  0.0  0.0      0     0 ?        S    Mar24   0:00 [UVM Tools Ev
root       38290  0.0  0.0      0     0 ?        I<   Mar24   0:00 [kworker/R-tl
root       38622  0.4  0.2 298532 80356 ?        Ssl  Mar24  83:15 /opt/jupyterh
root       38625  0.0  0.2 656040 66988 ?        Ssl  Mar24   2:32 node /usr/loc
jasonh     38735  0.0  0.0 687856 15296 ?        Ssl  Mar24   2:25 /opt/jupyterh
jasonh     38852  0.0  0.0 760808  8576 ?        Ssl  Mar24   1:21 /opt/jupyterh
james.q+   39982  0.0  0.4 681148 142200 ?       Ssl  Mar24   0:38 /opt/jupyterh
root      292717  0.0  0.0  12024  5384 ?        Ss   Mar25   0:18 sshd: /usr/sb
root      294255  0.0  0.3 173784 101148 ?       S<s  Mar25   2:19 /usr/lib/syst
systemd+  294360  0.0  0.0  91028  5764 ?        Ssl  Mar25   0:04 /usr/lib/syst
root      294456  0.0  0.0  31144  8480 ?        Ss   Mar25   0:06 /usr/lib/syst
root      294458  0.0  0.0      0     0 ?        S    Mar25   0:00 [psimon]
systemd+  294552  0.0  0.0  21692  6652 ?        Ss   Mar25   0:02 /usr/lib/syst
root      571399  0.0  0.0      0     0 ?        S    Apr06   0:00 [psimon]
ella.ha+  740787  0.0  0.0 435968 14892 ?        Ssl  Mar26   0:09 /opt/jupyterh
root     1228662  0.0  0.0  38756 12908 ?        Ss   01:21   0:00 /usr/sbin/cup
kristin+ 1536233  0.0  0.1 880996 40004 ?        Ssl  Mar28   0:12 /opt/jupyterh
kristin+ 1536350  0.0  0.0  21812  4200 pts/0    Ss+  Mar28   0:00 /bin/bash -l
root     1999198  0.0  0.0      0     0 ?        I    18:27   0:00 [kworker/10:2
root     2053168  0.0  0.0      0     0 ?        I    19:39   0:00 [kworker/12:0
root     2055157  0.0  0.0      0     0 ?        I    19:41   0:00 [kworker/u32:
root     2056353  0.0  0.0      0     0 ?        I    19:43   0:00 [kworker/10:0
root     2074470  0.0  0.0      0     0 ?        I    20:08   0:00 [kworker/2:0-
root     2077352  0.0  0.0      0     0 ?        I    20:12   0:00 [kworker/6:2-
root     2081645  0.0  0.0      0     0 ?        I    20:17   0:00 [kworker/8:1-
root     2089151  0.0  0.0      0     0 ?        I    20:27   0:00 [kworker/13:3
root     2089907  0.0  0.0      0     0 ?        I    20:28   0:00 [kworker/5:2-
root     2090858  0.0  0.0      0     0 ?        I    20:29   0:00 [kworker/1:2-
root     2092807  0.0  0.0      0     0 ?        I    20:32   0:00 [kworker/11:2
root     2095620  0.0  0.0      0     0 ?        I    20:36   0:00 [kworker/6:1-
root     2095705  0.0  0.0      0     0 ?        I    20:36   0:00 [kworker/5:3-
root     2096870  0.0  0.0      0     0 ?        I    20:37   0:00 [kworker/9:1-
root     2098518  0.0  0.0      0     0 ?        I    20:40   0:00 [kworker/7:2-
root     2104862  0.0  0.0      0     0 ?        I    20:48   0:00 [kworker/0:0-
root     2107009  0.0  0.0      0     0 ?        I    20:51   0:00 [kworker/u32:
root     2107043  0.0  0.0      0     0 ?        I    20:51   0:00 [kworker/3:2-
root     2112948  0.0  0.0      0     0 ?        I    20:59   0:00 [kworker/0:1]
root     2115735  0.0  0.0      0     0 ?        I    21:03   0:00 [kworker/3:0-
root     2115788  0.0  0.0      0     0 ?        I    21:03   0:00 [kworker/u32:
root     2118066  0.0  0.0      0     0 ?        I    21:06   0:00 [kworker/1:1-
root     2123054  0.0  0.0      0     0 ?        I    21:13   0:00 [kworker/7:0-
root     2124233  0.0  0.0      0     0 ?        I    21:14   0:00 [kworker/2:2-
root     2124500  0.0  0.0      0     0 ?        I    21:14   0:00 [kworker/15:2
root     2125345  0.0  0.0      0     0 ?        I    21:15   0:00 [kworker/4:1-
root     2127950  0.0  0.0      0     0 ?        I    21:19   0:00 [kworker/4:3-
root     2128208  0.0  0.0      0     0 ?        I    21:19   0:00 [kworker/6:0-
root     2128433  0.0  0.0      0     0 ?        I    21:19   0:00 [kworker/9:3-
root     2128798  0.0  0.0      0     0 ?        I    21:20   0:00 [kworker/15:1
root     2129285  0.0  0.0      0     0 ?        I    21:21   0:00 [kworker/14:0
root     2129933  0.0  0.0      0     0 ?        I    21:22   0:00 [kworker/8:2-
root     2130349  0.0  0.0      0     0 ?        I    21:22   0:00 [kworker/u32:
root     2132607  0.0  0.0      0     0 ?        I    21:25   0:00 [kworker/0:2-
root     2132976  0.0  0.0      0     0 ?        I    21:25   0:00 [kworker/11:0
root     2133481  0.0  0.0      0     0 ?        I    21:26   0:00 [kworker/14:1
root     2133631  0.0  0.0      0     0 ?        I    21:26   0:00 [kworker/13:0
root     2134415  0.0  0.0      0     0 ?        I    21:27   0:00 [kworker/12:2
root     2135782  0.0  0.0  42420 11364 ?        Ss   21:29   0:00 sshd: abdalla
root     2135910  0.0  0.0      0     0 ?        I    21:29   0:00 [kworker/2:1]
abdalla+ 2136133  0.0  0.0  42556  7984 ?        S    21:29   0:00 sshd: abdalla
abdalla+ 2136134  0.0  0.0  22360  6696 pts/3    Ss   21:29   0:00 -bash
root     2136146  0.0  0.0  37080 12572 ?        Ss   21:29   0:00 /usr/libexec/
root     2136151  0.0  0.0      0     0 ?        I    21:29   0:00 [kworker/4:0-
root     2136248  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/1:0]
root     2136249  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/1:3-
root     2136257  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/9:0]
root     2136499  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/u32:
root     2136756  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/15:0
root     2136757  0.0  0.0      0     0 ?        I    21:30   0:00 [kworker/15:3
root     2137534  0.0  0.0      0     0 ?        I    21:31   0:00 [kworker/14:2
root     2137538  0.0  0.0      0     0 ?        I    21:31   0:00 [kworker/u32:
root     2138294  0.0  0.0  14344  9828 ?        Ss   21:32   0:00 sshd: root [p
sshd     2138295  0.0  0.0  12152  6224 ?        S    21:32   0:00 sshd: root [n
root     2138412  0.0  0.0  14344  9848 ?        Ss   21:33   0:00 sshd: root [p
sshd     2138413  0.0  0.0  12152  6408 ?        S    21:33   0:00 sshd: root [n
root     2138738  0.0  0.0  23948 10436 ?        Ss   21:33   0:00 sshd: unknown
sshd     2138739  0.0  0.0  12152  6284 ?        S    21:33   0:00 sshd: unknown
abdalla+ 2138797 63.7  0.4 2574212 132100 ?      Ssl  21:33   0:08 /snap/snapd/c
root     2138835  0.0  0.0      0     0 ?        I    21:33   0:00 [kworker/3:1]
root     2138836 78.6  0.3 2582756 125184 ?      Ssl  21:33   0:09 /snap/snapd/c
abdalla+ 2138902  0.0  0.0   8304  2328 pts/3    S+   21:33   0:00 script result
abdalla+ 2138903  0.0  0.0  21708  6568 pts/7    Ss   21:33   0:00 bash -i
nathani+ 2138945  134  0.3 2499520 110004 ?      Ssl  21:33   0:08 /snap/snapd/c
abdalla+ 2139026  0.0  0.0  24188  5884 pts/7    R+   21:33   0:00 ps aux
abdalla+ 2564558  1.2  0.1  49076 38112 ?        Ss   Mar31 124:54 /usr/lib/syst
abdalla+ 2564559  0.0  0.0  48560  1068 ?        S    Mar31   0:00 (sd-pam)
abdalla+ 2564571  0.0  0.0 118648  4684 ?        Ssl  Mar31   0:00 /usr/bin/pipe
abdalla+ 2564572  0.0  0.0 107364  3928 ?        Ssl  Mar31   0:00 /usr/bin/pipe
abdalla+ 2564576  0.0  0.0 414532 10564 ?        Ssl  Mar31   0:00 /usr/bin/wire
abdalla+ 2564578  0.0  0.0 118880  6016 ?        Ssl  Mar31   0:00 /usr/bin/pipe
abdalla+ 2564612  0.0  0.0  29888  4296 ?        Ss   Mar31   0:00 /usr/bin/dbus
abdalla+ 2564700  0.0  0.0 536560  5580 ?        Ssl  Mar31   0:00 /usr/libexec/
abdalla+ 2564704  0.0  0.0 309308  4816 ?        Ssl  Mar31   0:00 /usr/libexec/
root     2564711  0.0  0.0  13152  2564 ?        Ss   Mar31   0:00 fusermount3 -
abdalla+ 2565804  0.0  0.0   8304  2148 ?        S    Mar31   0:00 script result
abdalla+ 2565805  0.0  0.0  22132  4268 pts/2    Ss+  Mar31   0:00 bash -i
nathani+ 2762298  1.3  0.1  49064 38144 ?        Ss   Apr01 124:10 /usr/lib/syst
nathani+ 2762299  0.0  0.0  48556  1068 ?        S    Apr01   0:00 (sd-pam)
nathani+ 2762310  0.0  0.0 118648  4680 ?        Ssl  Apr01   0:00 /usr/bin/pipe
nathani+ 2762311  0.0  0.0 107364  3876 ?        Ssl  Apr01   0:00 /usr/bin/pipe
nathani+ 2762313  0.0  0.0 413684  9812 ?        Ssl  Apr01   0:00 /usr/bin/wire
nathani+ 2762314  0.0  0.0 118880  6008 ?        Ssl  Apr01   0:00 /usr/bin/pipe
nathani+ 2762343  0.0  0.0  29888  4132 ?        Ss   Apr01   0:00 /usr/bin/dbus
nathani+ 2762428  0.0  0.0 536560  5748 ?        Ssl  Apr01   0:00 /usr/libexec/
nathani+ 2762432  0.0  0.0 309308  4756 ?        Ssl  Apr01   0:00 /usr/libexec/
root     2762439  0.0  0.0  13152  2564 ?        Ss   Apr01   0:00 fusermount3 -
nathani+ 2767304  0.0  0.0  24620  4980 ?        Ss   Apr01   0:00 tmux new
nathani+ 2767305  0.0  0.0  21972  5104 pts/4    Ss+  Apr01   0:00 -bash
kristin+ 3166286  0.0  0.0  21812  4756 pts/5    Ss+  Apr02   0:00 /bin/bash -l
kristin+ 3166287  0.0  0.0  21812  4772 pts/9    Ss+  Apr02   0:00 /bin/bash -l
kristin+ 3166414  0.0  0.0  21812  4772 pts/10   Ss+  Apr02   0:00 /bin/bash -l
kristin+ 3173356  0.0  0.0  21944  4952 pts/11   Ss+  Apr02   0:00 /bin/bash -l
root     3406039 99.2  0.1  87644 64644 ?        RNs  Apr03 6852:50 (mandb)
abdallah.mohamed@ant:~/exp17$ 