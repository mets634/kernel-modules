/*
 * Packet Dropper --
 *
 * Drops all incoming packets, using a netfilter hook.*/

// kernel module includes
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

// packet filtering includes
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

// module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mets634");
MODULE_DESCRIPTION("Drops all incoming packets.");
MODULE_VERSION("1.0");

// packet filter hook
static struct nf_hook_ops hops;

unsigned int drop_hook(void *priv, struct sk_buff *skb,
		const struct nf_hook_state *state) {
	printk(KERN_INFO "Dropping packet...");
	return NF_DROP;
}

// init and exit functions
static int __init drop_init(void) {
	// setup hook
	hops.hook = drop_hook;
	hops.hooknum = 0; // prerouting
	hops.pf = PF_INET;
	hops.priority = NF_IP_PRI_FIRST;

	// register hook
	nf_register_hook(&hops);

	printk(KERN_INFO "Registered hook.");
	return 0;
}

static void __exit drop_exit(void) {
	nf_unregister_hook(&hops);
	printk(KERN_INFO "Unregistered hook.");
}

// setup init and exit
module_init(drop_init);
module_exit(drop_exit);
