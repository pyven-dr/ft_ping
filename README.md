# ft_ping

A recreation of the Unix `ping` utility written in C, inspired by **GNU inetutils 2.0**.

`ft_ping` sends ICMP Echo Request packets to IPv4 hosts and processes incoming replies to measure round-trip time (RTT),
detect duplicate packets, and calculate network statistics.

## Features

- IPv4 hostname resolution.
- ICMP Echo Request generation and transmission.
- ICMP Echo Reply processing.
- Round-trip time (RTT) measurement.
- Duplicate packet detection.
- Packet loss and transmission statistics.
- Configurable packet size, interval, TTL and timeout.
- Support for multiple destinations.
- Graceful termination with `Ctrl+C`.

## Build

Compile the project using `make`:

```sh
make
```

Running `ft_ping` may require administrator privileges.

## Usage

```sh
sudo ./ft_ping [OPTION...] HOST...
```

Multiple hosts can be specified:

```sh
sudo ./ft_ping google.com 8.8.8.8
```

### Examples

Send ICMP Echo Requests to a host:

```sh
sudo ./ft_ping google.com
```

Send 5 packets:

```sh
sudo ./ft_ping -c 5 google.com
```

Set the packet size and sending interval:

```sh
sudo ./ft_ping -s 128 -i 0.5 google.com
```

Set a TTL:

```sh
sudo ./ft_ping --ttl=64 google.com
```

## Options

| Option                  | Description                                               |
| ----------------------- | --------------------------------------------------------- |
| `-c, --count=NUMBER`    | Stop after sending NUMBER packets.                        |
| `-i, --interval=NUMBER` | Wait NUMBER seconds between packets.                      |
| `-n, --numeric`         | Display numeric addresses instead of resolving hostnames. |
| `--ttl=N`               | Set the IP time-to-live value.                            |
| `-v, --verbose`         | Enable verbose output.                                    |
| `-w, --timeout=N`       | Stop after N seconds.                                     |
| `-W, --linger=N`        | Wait N seconds for replies after the last packet.         |
| `-s, --size=NUMBER`     | Set the number of data octets in each packet.             |
| `-?, --help`            | Display the help message.                                 |

Press `Ctrl+C` to stop execution and display the final statistics.
