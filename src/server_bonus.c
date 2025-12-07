#include "minitalk.h"

int	main(int argc, char **argv)
{
	if (argc >= 1)
	{
		teste_make("Server Bonus -> OK");
		printf("%s\n", argv[1]);
		count(argc);
	}
}