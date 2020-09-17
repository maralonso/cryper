#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cryper.h"
#include "key.h"
#include "des.h"

#define OUTPUT_FILE "cipher.txt"

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

    FILE *file = fopen(opt.file_name, "r");
    if (file == NULL) {
		fprintf(stderr, "Could not open file %s", opt.file_name);
		exit(1);
    }

    FILE *cipher = fopen(OUTPUT_FILE, "w");
    if (cipher == NULL) {
		fprintf(stderr, "Could not open file %s", OUTPUT_FILE);
		exit(1);
    }

    uint64_t block;
    size_t bytes = fread(&block, 1, sizeof(uint64_t), file);
    while (bytes > 0) {
        uint64_t cipher_data = cipher_block(block, keys);  
        fwrite(&cipher_data, 1, sizeof(uint64_t), cipher);
        bytes = fread(&block, sizeof(uint64_t), 1, file);
    }

    fclose(cipher);
    fclose(file);
}
