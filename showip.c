// C program to display hostname
// and IP address
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// Returns hostname for the local computer
void checkHostName(int hostname)
{
	if (hostname == -1)
	{
		perror("gethostname");
		exit(1);
	}
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
	if (hostentry == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
	if (NULL == IPbuffer)
	{
		perror("inet_ntoa");
		exit(1);
	}
}

// Driver code
int main(int argc, char **argv)
{
	char hostbuffer[256];
	char *IPbuffer;
	struct hostent *host_entry;
	int hostname;

	// To retrieve hostname
	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	checkHostName(hostname);

	// To retrieve host information
	host_entry = gethostbyname(hostbuffer);
	checkHostEntry(host_entry);

	// To convert an Internet network
	// address into ASCII string
	IPbuffer = inet_ntoa(*((struct in_addr*)
	host_entry->h_addr_list[0]));
	
	const char *version = "1.0.0";

	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0)
		{
			printf("showip v%s\nUsage:\nshowip        Display own IP address\nshowip -h     Display this help and exit\nshowip -hn    Display own hostname\nshowip -hnip  Display own and hostname IP address\nshowip -v     Display version and exit\n", version);
		}
		else if (strcmp(argv[1], "-v") == 0)
		{
			printf("showip v%s\n", version);
		}
		else if (strcmp(argv[1], "-hn") == 0)
		{
			printf("%s\n", hostbuffer);
		}
		else if (strcmp(argv[1], "-hnip") == 0)
		{
			printf("%s\n%s\n", IPbuffer, hostbuffer);
		}
		else // NOTE: Currently only prints out 127.0.1.1. Every address in the 127.0.0.0 subnet just points to the device it's called from. 
		{
			printf("%s\n", IPbuffer);
		}
	}
	else
	{
		printf("%s\n", IPbuffer);
	}

	return 0;
}
