#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cryper.h"
#include "key.h"

typedef struct {
    char *file_name;
    char *key;
    actions_e action;
}options_t;

static void parse_args(int argc, char **argv, options_t *opt)
{
    extern char *optarg;
	extern int optind;
	int c, err = 0; 
	static const char usage[] = "usage: %s {-c (Encrypt) | -d (Decrypt)} -f fname -k key\n";

    memset(opt, 0x0, sizeof(options_t));

	while ((c = getopt(argc, argv, "cdf:k:")) != -1) {
		switch (c) {
		case 'c':
			opt->action = ENCRYPT;
			break;
		case 'd':
			opt->action = DECRYPT;
			break;
		case 'f':
			opt->file_name = optarg;
			break;
		case 'k':
			opt->key = optarg;
			break;
		case '?':
			err = 1;
			break;
		}
    }

	if (err | (opt->file_name == NULL) | (opt->key == NULL) | (opt->action == 0)) {	
		fprintf(stderr, usage, argv[0]);
		exit(1);
    }
}

int main(int argc,char **argv)
{
    options_t opt;
    parse_args(argc, argv, &opt);

    uint64_t key = 0;
    for (int i = 0; i < 8; i++) {
        if (strlen(opt.key) >= i) {
            key |= (uint64_t)opt.key[i] << (i * 8);
        }
    }

    sub_keys_t keys;
    get_sub_keys(key, opt.action, &keys);

}
