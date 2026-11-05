SRC = main.c \
	  process_hosts.c \
	  resolve_addr.c \
	  checksum.c \
	  interval.c \
	  \
	  client/init_client.c \
	  client/send_ping.c \
	  client/receive.c \
	  client/ping_loop.c \
	  \
	  parsing/parsing.c \
	  parsing/handle_flags.c \
	  parsing/set_opt.c \
	  \
	  packet/parse_packet.c \
	  packet/read_raw.c \
	  packet/handle_packet.c \
	  \
	  packet/ip/parse_ip_hdr.c \
	  \
	  packet/icmp/parse_icmp_msg.c \
