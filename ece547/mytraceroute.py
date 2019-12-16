from scapy.all import IP, ICMP, sr1
import sys
import time

# destination is passed as a command line arguement
ip = sys.argv[1]

for i in range(1,31):

	time_lst = []
	# Create IP packet with ICMP request
	pkt = IP(dst=ip, ttl=i)/ICMP()	
	source = ip
	
	for j in range(3):
		t1 = time.time() # t1 = time before sending
		rcv_pkt = sr1(pkt, verbose=False)
		t2 = time.time() # t2 = time of arrival 
		time_lst.append((t2-t1)*1000)
		source = rcv_pkt.src

	# print received packet info 
	print("{}  {:.1f} ms {:.1f} ms {:.1f} ms {}"
		.format(i, time_lst[0], time_lst[1], time_lst[2],  source))
