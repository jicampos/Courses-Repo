

# date and time
dt=$(date '+%m/%d/%Y,%H:%M:%S')
file_ping="ping.txt"
file_traceroute="traceroute.txt"
websites="www.purdue.edu www.rose-hulman.edu www.pace.edu www.princeton.edu www5.usp.br www.unicamp.br www.cam.ac.uk www.iitd.ac.in www.amu.ac.in" 

printf "$dt" >> $file_ping
printf "$dt" >> $file_traceroute
printf "DATE/TIME: $dt\n"
printf "Beginning to ping...\n\n"

for website in $websites
do
	printf "$website" 
	STRING="$(ping -c 12 $website | tail -1| awk -F '/' '{print $5}')"
	printf ",$STRING" >> $file_ping
	printf ": $STRING\n"
done

printf "\n" >> $file_ping 
printf "\nBeginning to traceroute...\n\n"

for website in $websites
do 
	printf "$website" 
	OUTPUT="$(traceroute $website | tail -1 | awk -F ' ' '{print $1}')"
	printf ",$OUTPUT" >> $file_traceroute
	printf ": $OUTPUT\n"
done 

printf "\n" >> $file_traceroute 
