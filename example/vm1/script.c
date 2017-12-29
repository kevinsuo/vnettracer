

#include <uapi/linux/ptrace.h>
#include <uapi/linux/if_ether.h>

#include <linux/skbuff.h>
#include <uapi/linux/udp.h>
#include <bcc/proto.h>

#include <config/containerIP.h>


#define TCP 6
#define UDP 17

#define MESSAGE_LEN  16




void fun1(struct __sk_buff *skb) {
	u64 ts = 0;
	u8 *cursor = 0;
	u32 label = 0;
	char message[17];
			
	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));
	if(ethernet->type == ETH_P_IP) {

		struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));
		u32 sip = ip->src;
		u32 dip = ip->dst;

		if (sip == CLIENT_SOURCE && dip == SERVER_SOURCE) {

				ts = bpf_ktime_get_ns();
				label = 11;

				int i = 0;
				int j = 0;
				for (i = 42; i < 42 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';
				bpf_trace_printk("%llu %u %s\n", ts, label, message);
				return;

		}


		if (dip == CLIENT_SOURCE && sip == SERVER_SOURCE) {

				ts = bpf_ktime_get_ns();
				label = 26;

				int i = 0;
				int j = 0;
				for (i = 42; i < 42 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';

				bpf_trace_printk("%llu %u %s\n", ts, label, message);
				return;
		}

	}
}




void fun2(struct __sk_buff *skb) {
	u64 ts = 0;
	u8 *cursor = 0;
	u32 label = 0;
	char message[17];
			
	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));
	if(ethernet->type == ETH_P_IP) {

		struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));

		u32 sip = ip->src;
		u32 dip = ip->dst;

		if (sip == CLIENT_SOURCE && dip == SERVER_SOURCE) {

				ts = bpf_ktime_get_ns();
	
				label = 12;

				int i = 0;
				int j = 0;
				for (i = 42; i < 42 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';

				bpf_trace_printk("%llu %u %s\n", ts, label, message);
				return;
		}


		if (dip == CLIENT_SOURCE && sip == SERVER_SOURCE) {


				ts = bpf_ktime_get_ns();
	
				label = 25;

				int i = 0;
				int j = 0;
				for (i = 42; i < 42 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';

				bpf_trace_printk("%llu %u %s\n", ts, label, message);
				return;
		}
	}
}




void fun3(struct __sk_buff *skb) {
	u64 ts = 0;
	u8 *cursor = 0;
	u32 label = 0;
	char message[17];
	

	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet) + 50);
	if(ethernet->type == ETH_P_IP) {

		struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));
	
		u32 sip = ip->src;
		u32 dip = ip->dst;


		if (sip == CLIENT_SOURCE && dip == SERVER_SOURCE) {

				u64 ts = bpf_ktime_get_ns();

				label = 13;

				int i = 0;
				int j = 0;
				for (i = 92; i < 92 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';

				bpf_trace_printk("%llu %u %s\n", ts, label, message);	
				return;
		}



		if (dip == CLIENT_SOURCE && sip == SERVER_SOURCE) {

				u64 ts = bpf_ktime_get_ns();

				label = 24;

				int i = 0;
				int j = 0;
				for (i = 92; i < 92 + MESSAGE_LEN; i++) {
					message[j] = load_byte(skb, i);
					j++;
				}
				message[MESSAGE_LEN] = '\0';

				bpf_trace_printk("%llu %u %s\n", ts, label, message);	
				return;
		}
	}
}


