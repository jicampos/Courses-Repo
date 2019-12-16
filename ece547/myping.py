from scapy.all import IP, ICMP, sr1
import sys
import time
import numpy as np 

# destination is passed as a command line arguement
ip = sys.argv[1]

# used to collect estimated rtt
time_lst = []

print("Pinging " + ip + " with 28 bytes of data:")

for i in range(10):
	# Create IP packet with ICMP request
	pkt = IP(dst=ip)/ICMP()
	
	t1 = time.time() # t1 = time before sending
	rcv_pkt = sr1(pkt, verbose=False)
	t2 = time.time() # t2 = time of arrival 
	time_lst.append((t2-t1)*1000)

	# print received packet info 
	print("Reply from {}: bytes={} time={:.1f}ms TTL={}"
		.format(rcv_pkt.src, rcv_pkt.len, time_lst[-1], rcv_pkt.ttl))

	# delay for 1 second
	time.sleep(1)
	

# Median Absolute Deviation
MAD = np.mean(np.absolute(time_lst-np.mean(time_lst)))
print("--- {} ping statistics ---".format(ip))
print("rtt min/avg/max/mdev: {:3f}/{:.3f}/{:.3f}/{:.3f} ms"
		.format(min(time_lst), np.mean(time_lst), np.max(time_lst), MAD))

'''    
Pinging www.google.com with 32 bytes of data:
Reply from 172.217.1.36: bytes=32 time=17ms TTL=54
Reply from 172.217.1.36: bytes=32 time=19ms TTL=54
Reply from 172.217.1.36: bytes=32 time=11ms TTL=54
Reply from 172.217.1.36: bytes=32 time=12ms TTL=54
'''