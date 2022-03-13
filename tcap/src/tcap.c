// Copyright © 2022 The Certsar Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//   ██████╗███████╗██████╗ ████████╗███████╗ █████╗ ██████╗
//  ██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██╔══██╗
//  ██║     █████╗  ██████╔╝   ██║   ███████╗███████║██████╔╝
//  ██║     ██╔══╝  ██╔══██╗   ██║   ╚════██║██╔══██║██╔══██╗
//  ╚██████╗███████╗██║  ██║   ██║   ███████║██║  ██║██║  ██║
//   ╚═════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝

#include "tcap.h"
#include "version.h"
#include <pcap.h>
#include <stdio.h>

void about(void) {
    printf("     > tcap version: %s \n", VERSION);
    printf("     > libtcap.so.%s \n", VERSION);
}



// tcap_next
//
// Simple implementations first. If people actually use this we can
// add device and network support as needed.
//
// Wraps pcap and returns a tcap_digest
struct tcap_digest tcap_next(void) {

    struct tcap_digest digest;
	pcap_if_t *interfaces, *temp;
	pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
	int i_c = 0;
    char *dev;

	struct bpf_program fp;		    /* The compiled filter */
	bpf_u_int32 mask;		        /* Our netmask */
	bpf_u_int32 net;		        /* Our IP */
	struct pcap_pkthdr header;	    /* The header that pcap gives us */
	const u_char *packet;		    /* A packet */

    // Filter system taken from tlsdump.tcpdump
    char filter_exp[] = "(tcp[((tcp[12] & 0xf0) >>2)] = 0x16) && (tcp[((tcp[12] & 0xf0) >>2)+5] = 0x01)";	/* The filter expression */

	if(pcap_findalldevs(&interfaces, errbuf) == -1 ){
        fprintf(stderr, "error listing devices: %s\n", errbuf);
        return digest;
	}
    // Default device (according to pcap.h) is the FIRST device
    for(temp=interfaces; temp; temp=temp->next){
        dev = temp->name;
        break;
    }
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "error getting netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	    return digest;
	}
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "error opening device %s: %s\n", dev, errbuf);
	    return digest;
	}
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		fprintf(stderr, "error parsing filter %s: %s\n", filter_exp, pcap_geterr(handle));
	    return digest;
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "error setting filter %s: %s\n", filter_exp, pcap_geterr(handle));
	    return digest;
	}

	// TODO We will need to rebuild the full TLS digest in memory from the corresponding packets
	// TODO For now we just add the first one to packets[]
	packet = pcap_next(handle, &header);
    pcap_close(handle);
    digest.packets[0] = packet;

    return digest;
}