### Install the driver
    cd driver
    make
    su
    insmod chardevsimple.ko
    dmesg | less
    mknod /dev/chardevsimple c 2xx 0
    ls /dev/ |grep chardev
    chmod 777 /dev/chardevsimple

#### Test it!
    cd testapp
    make
    ./userapp
