SRC = main.c \
	  \
	  client/init_client.c \
	  client/send_ping.c \
	  client/receive.c \
	  client/ping_loop.c \
	  client/handle_echo_reply.c \
	  client/handle_err.c \
	  client/bitmap.c \
	  \
	  network/process_hosts.c \
	  network/resolve_addr.c \
	  \
	  parsing/parsing.c \
	  parsing/handle_flags.c \
	  parsing/set_opt.c \
	  \
	  packet/parse_packet.c \
	  packet/read_raw.c \
	  packet/checksum.c \
	  \
	  packet/ip/parse_ip_hdr.c \
	  \
	  packet/icmp/parse_icmp_msg.c \
	  \
	  utils/signal.c \
	  utils/print_ip.c \
	  utils/print_help.c \
	  utils/interval.c \
