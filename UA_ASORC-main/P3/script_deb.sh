mkdir $1
grep -R "$2" /var/log/* > $1/linuxlogs.txt
history | grep $2 > $1/historylinux.txt
