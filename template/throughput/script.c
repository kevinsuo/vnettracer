/*
 * Trace network packet send.
 * For Linux, uses BCC, eBPF. See .py file.
 *
 * Copyright (c) 2017 Tony Suo.
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * 22-Jun-2017	Tony Suo	Created this.
 */

#include <uapi/linux/ptrace.h>
#include <uapi/linux/if_ether.h>

#include <linux/skbuff.h>
#include <uapi/linux/udp.h>
#include <bcc/proto.h>

#include <config/containerIP.h>
#include <config/servicePort.h>


#define TCP 6
#define UDP 17

#define ETH_HLEN 14

#define MESSAGE_LEN  16

void function1(struct __sk_buff *skb) {
	u64 ts = 0;
	u8 *cursor = 0;
	u32 label = 0;

	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));
	if(ethernet->type == ETH_P_IP) {

		struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));

		//calculate ip header length
		//value to multiply * 4
		//e.g. ip->hlen = 5 ; IP Header Length = 5 x 4 byte = 20 byte
		u32 ip_header_length = ip->hlen << 2; 
		u32 sip = ip->src;
		u32 dip = ip->dst;

		if (sip == CLIENT_SOURCE && dip == SERVER_SOURCE) {

			if (ip->nextp == TCP) {
				struct tcp_t *tcp = cursor_advance(cursor, sizeof(*tcp));

				if (tcp->dst_port == SERVICE_PORT) {
					//calculate tcp header length
					//value to multiply *4
					//e.g. tcp->offset = 5 ; TCP Header Length = 5 x 4 byte = 20 byte
					//u32 tcp_header_length = tcp->offset << 2; //SHL 2 -> *4 multiply
					//u32 payload_length = ip->tlen - ip_header_length - tcp_header_length;
					u32 packet_length = ETH_HLEN + ip->tlen; 

					ts = bpf_ktime_get_ns();
					label = 11;

					bpf_trace_printk("%llu %u %u\n", ts, label, packet_length);
					return;
				}
			} else if (ip->nextp == UDP) {
				struct udp_t *udp = cursor_advance(cursor, sizeof(*udp));
				if (udp->dport == SERVICE_PORT) {
					u32 udp_length = udp->length << 2; 
					u32 packet_length = ETH_HLEN + ip->tlen;

					ts = bpf_ktime_get_ns();
					label = 12;

					bpf_trace_printk("%llu %u %u\n", ts, label, packet_length);
					return;
				}
	
			}

		}
	}
}



