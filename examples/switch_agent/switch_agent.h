#include <stdint.h>
#include "immintrin.h"
#include "../common/statistics.h"
#include <arpa/inet.h>
#include <bpf/bpf.h>
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <locale.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <xsknf.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <bpf/bpf_endian.h>
#include "timestamp.h"
#include "haraka.h"
#include "csum.h"
#include "murmur.h"
#include "timeit.h"
#include "pthread.h"
#define MSTONS 1000000
#define DEBUG 0
#define DEBUG_PRINT(fmt, ...) \
	if (DEBUG)                \
	printf(fmt, ##__VA_ARGS__)
#define RETH1 0
#define RETH2 1
#define TS_START bpf_ntohl(0x01010000)



__u64 u1_mac = 0x030012ac4202;
__u64 u2_mac = 0x030013ac4202;
__u64 reth1_mac = 0x020012ac4202;
__u64 reth2_mac = 0x020013ac4202;

struct common_synack_opt
{
	uint32_t MSS;
	uint16_t SackOK;
	struct tcp_opt_ts ts;
} __attribute__((packed));

struct eth_mac_t
{
    uint8_t buf[6];
}__attribute__((packed));

struct global_data {
	int action;
	int double_macswap;
};

struct pkt_5tuple {
  uint32_t src_ip;
  uint32_t dst_ip;
  uint16_t src_port;
  uint16_t dst_port;
  uint32_t sand[5];
} __attribute__((packed));

// Redirect from ingress_ifindex to redirect_ifindex
// Set eth.src to ingress_ifindex's mac and eth.dst to redirect_ifindex's mac
static inline int redirect_if(int ingress_ifindex, int redirect_ifindex, struct ethhdr* eth);




