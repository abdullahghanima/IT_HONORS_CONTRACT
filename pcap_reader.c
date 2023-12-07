#include <stdio.h>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#include <mach/mach_time.h>

#include <unistd.h>


void packet_handler_offline(unsigned char *user, const struct pcap_pkthdr *pkthdr, const unsigned char *packet) {
    // access headers data
    struct ether_header *eth = (struct ether_header *)packet;
    struct ip *ip = (struct ip *)(packet + sizeof(struct ether_header));
    struct udphdr *udp = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));

    // access the payload data
    unsigned char *payload = (unsigned char *)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
    int payload_length = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));

}


int main() {
    char errbuf[PCAP_ERRBUF_SIZE];


    uint64_t start_time = mach_absolute_time();
    // open and read the file for offline packet processing
    pcap_t *offline_handle = pcap_open_offline("captured_packets.pcap", errbuf);
    pcap_loop(offline_handle, 0, packet_handler_offline, NULL);
    uint64_t end_time = mach_absolute_time();
    mach_timebase_info_data_t timebase_info;
    mach_timebase_info(&timebase_info);
    // Calculate and print the time difference in nanoseconds
    uint64_t elapsed_nanoseconds = (end_time - start_time) * timebase_info.numer / timebase_info.denom;
    // printf("Time difference_no_sha: %lld nanoseconds\n", elapsed_nanoseconds);
    // printf("Time difference_no_sha: %.6f milliseconds\n", (double)elapsed_nanoseconds / 1e6);
    pcap_close(offline_handle);


    FILE *outputFile;
    outputFile = fopen("output.txt", "a");    
    fprintf(outputFile, "%lld\n", elapsed_nanoseconds);
    fclose(outputFile);

    return 0;
}



// gcc pcap_reader.c -o pcap_reader -lpcap -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
// sudo ./pcap_reader


