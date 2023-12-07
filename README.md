# IT_HONORS_CONTRACT
Honors Contract Assignment for 198:352 at Rutgers UNiversity, Internet Technology with Professor Richard Martin. SHA-256 Hashing and its Efficiencies


setup.c
This pulls outgoing network messages from the machine, and stores them in a pcap file
It also created a txt file that will later be used for analysis. The number of packets being stored is added to this file as a double.

pcap_reader.c
This opens and accesses all of the packets from the pcap file created by setup.c
It stores some of the packet data in temporary variables
The time taken to open all pcap files is also recorded, and added to the txt file

pcap_reader_with_sha.c
The file does the same thing as the previous file. 
The only difference is that while reading the stored packets in the pcap file, it also computes the sha256 hash of each packet data
The time is also recorded, and added to the txt file

analysis.c
This file uses the txt file to demonstrate a number of analytics relating to the time taken to access the packets VS the time taken to access the packets and compute the sha256 hash
Sample output is shown below:

_OVERALL:
Time taken while using sha256: 2763750 nanoseconds
Time taken without using sha256: 60833 nanoseconds
Percentage Difference: 19138.52%
Difference Factor: 191.39x
Absolute Difference: 2702917 nanoseconds

AVERAGES BASED ON 10 PACKETS:
Average Time per Packet with sha256: 276375.00 nanoseconds
Average Time per Packet without sha256: 6083.30 nanoseconds
Average Difference Factor: 191.39x
Average Percentage Difference: 19138.52%
Average Difference Factor: 191.39x
Average Absolute Difference: 270292 nanoseconds
_



The commands used to run each file are at the bottom of the respective file.

In order to run all the files with one command, we can use the following:

_gcc setup.c -o setup -lpcap ; gcc pcap_reader.c -o pcap_reader -lpcap -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto ; gcc pcap_reader_with_sha.c -o pcap_reader_with_sha -lpcap -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto ; gcc analysis.c -o analysis ; sudo ./setup ; sudo ./pcap_reader ; sudo ./pcap_reader_with_sha ; sudo ./analysis_







Concepts that I was able to learn and general design decisions are demonstrated in the files themselves, and the discussions I had with the professor throughout the semester.
