mkdir $1
grep -R "$2" /var/log/* > $1/unixlogs.txt
history > $1/historyunix.txt
