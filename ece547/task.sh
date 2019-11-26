

# date and time
dt=$(date '+%m/%d/%Y,%H:%M:%S')
file_ping="ping.txt"
file_traceroute="traceroute.txt"
websites="www.purdue.edu www.rose-hulman.edu www.nyu.edu www.stonybrook.edu www5.usp.br www.unicamp.br www.cam.ac.uk www.iitd.ac.in www.iitb.ac.in" 

printf "$dt" >> $file_ping
printf "$dt" >> $file_traceroute
printf "DATE/TIME: $dt\n"
printf "Beginning to ping...\n\n"

for website in $websites
do
	printf "$website\n" 
	STRING=",$(ping -c 1 $website | tail -1| awk -F '/' '{print $5}')"
	# printf ",$STRING" >> $file_ping
	if [ $STRING = "," ]; then
		printf ",0" >> $file_ping
	else 
		printf "$STRING" >> $file_ping
	fi
done

printf "\n" >> $file_ping 
printf "\nBeginning to traceroute...\n\n"

for website in $websites
do 
	printf "$website\n" 
	OUTPUT="$(traceroute $website | wc -l)"
	printf ",$(($OUTPUT-1))" >> $file_traceroute
	# echo "$(($OUTPUT-1)),"
done 

printf "\n" >> $file_traceroute 
