This code has been taken from
http://pointer-overloading.blogspot.in/2013/09/linux-creating-entry-in-proc-file.html


$ sudo insmod hello_proc.ko
$ cat /proc/hello_proc
Hello proc!
$ ls -l /proc/hello_proc
-r--r--r-- 1 root root 0 2013-09-18 21:32 /proc/hello_proc
$ sudo rmmod hello_proc

