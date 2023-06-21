#include <stdio.h>
#include <stdlib.h>

int ft_atoi(const char *str)
{
	int result;
	int sigin;
	int i;

	result = 0;
	sigin = 1;
	i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	if (str[i] == '-' || str[i] == '+')
		sigin = 1 - 2 * (str[i++] == '-');

	while (str[i] >= '0' && str[i] <= '9')
		result = 10 * result + (str[i++] - '0');

	return (result * sigin);
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		printf("ERROR: missing string to test or too much strings in invocation\n");
		return 1;
	}

    printf("ft_atoi(\"%s\"): %d\n", argv[1], ft_atoi(argv[1]));
    printf("atoi(\"%s\"): %d\n", argv[1], atoi(argv[1]));

    return 0;
}