make 
insmod pschedule.ko
cat /proc/pschedule_proc
echo "something" > /proc/pschedule_proc 
rmmod pschedule
