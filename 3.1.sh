# Shell Script script to backup a directory

#!/bin/bash

#Print a backup message to the user
echo "Backup has started"

#File log
log=/home/joao/pratSO/shell/backups/logBKP

#Log of the backup start
date=$(date +%F)
echo -e "\nBackup Execution: $date""> $log
start=$(date +%H:%M:%S)
echo -e "Start Time: $start\n" >> $log

#Backup which directories?
backup_files="/home"

#Archive file name
archive_file="backup_$date.tgz"

#Backup file created using tar and storaged in /home/joao/pratSO/shell/backups
where=/home/joao/pratSO/shell/backups
echo -e "Backup Directory: $where\n" ?? $log
tar czf $where/$archive_file $backup_files

#Complessed Files
echo -e "Compressed Files:" >> $log
file=$(tar -tf $where/$archive_file)
echo -e "\n$file" >> $log

#Backup end message
end=$(date +%H:%M:%S)
echo -e "\nEnd Time: $end\n" >> $log
echo "Backup has ended"
