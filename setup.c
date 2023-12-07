#include <stdio.h>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>


// this file captures network packets using pcap, writes them to a file,
// and then reads that file's contents

void packet_handler_live(unsigned char *user, const struct pcap_pkthdr *pkthdr, const unsigned char *packet) {
    pcap_dumper_t *dumper = (pcap_dumper_t *)user;

    // write the packet data to the file with pcap_dump
    pcap_dump((u_char *)dumper, pkthdr, packet);
}


int main() {
    char errbuf[PCAP_ERRBUF_SIZE];

    // use pcap for live packet capture
    pcap_t *live_handle = pcap_open_live("en0", BUFSIZ, 1, 1000, errbuf);

    // create a pcap dump file for writing captured packets
    pcap_dumper_t *dumper = pcap_dump_open(live_handle, "captured_packets.pcap");


    const int FINAL_NUM_OF_PACKETS_BEING_CAPTURED = 10.0;


    // start capturing live packets and write them to the dump file (limited to 10 packets for now)
    pcap_loop(live_handle, FINAL_NUM_OF_PACKETS_BEING_CAPTURED, packet_handler_live, (unsigned char *)dumper);

    pcap_close(live_handle);
    pcap_dump_close(dumper);


    FILE *outputFile;
    outputFile = fopen("output.txt", "w");
    fprintf(outputFile, "%d\n", FINAL_NUM_OF_PACKETS_BEING_CAPTURED);

    fclose(outputFile);

    return 0;
}



// gcc setup.c -o setup -lpcap 
// sudo ./setup


// gcc setup.c -o setup -lpcap ; gcc pcap_reader.c -o pcap_reader -lpcap -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto ; gcc pcap_reader_with_sha.c -o pcap_reader_with_sha -lpcap -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto ; gcc analysis.c -o analysis ; sudo ./setup ; sudo ./pcap_reader ; sudo ./pcap_reader_with_sha ; sudo ./analysis
