#include <stdio.h>
#include <getopt.h>
char *l_opt_arg;


//optstring指定选项合法的选项，一个字符代表一个选项，在字符后面加一个’:‘表示该选项带一个参数，字符后带两个’:'表示该选项带可选参数(参数可有可无)，若有参数，optarg指向该该参数，否则optarg为0；
char* const short_options = "+hnbl:";

struct option long_options[] = {
	{"name", 0, NULL, 'n' },
	{"bf_name", 0, NULL, 'b' },
	{"love", 1, NULL, 'l' },
	{ "help",        0, 0, 'h' },
	{0, 0, 0, 0 },
};

static void usage(void)
{
    printf("mytest\n");
    printf("Usage:\n\tmytest [options]\n");

    printf("Options:\n"
		"\t-s, --love <string>\t\t\t设置值\n"
		"\t-b, --bf_name\t\t\tdisplay bf_name\n"
        "\t-n, --name\t\t\tdisplay name\n"
        "\t-h, --help\t\t\tDisplay help\n");
}

int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (c)
		{
        case 'h':
            usage();
            return 0;
		case 'n':
			printf("My name is XL.\n");
			break;
		case 'b':
			printf("His name is ST.\n");
			break;
		case 'l':
			l_opt_arg = optarg;							// -l 后面跟的值
			printf("Our love is %s!\n", l_opt_arg);
			break;
		}
	}
	return 0;
}
