#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void DoConvert(unsigned char *key, char *keyDB, int len)
{
		int i;
         char strVal[]="0123456789ABCDEF";
         for (i = 0; i < len ; i++)
         {
                   keyDB[2*i] = strVal[(key[i]&0xF0) >> 4];
                   
                   keyDB[2*i+1] = strVal[(key[i]&0x0F)];
         
         }
}

//

int main(int argc , char* argv[])
{
	char* in_file, *out_file = NULL;
    FILE *in_fp, *out_fp = NULL;
	int size, ret = 0;
	char *in_buf, *out_buf;

	struct stat st;

	if(argc < 2)
	{
		printf("Usage: conver_to_hex input_file output_file\n");
		goto err;
	} else {
        in_file = argv[1];
        out_file = argv[2];
	}

	in_fp = fopen(in_file, "rb+");
	if(in_fp == NULL) {
		printf("Open %s error.\n", in_file);
		goto err;
	}

	out_fp = fopen(out_file, "w+");
	if(out_fp == NULL) {
		printf("Open %s error.\n", out_file);
		goto err;
	}

	stat(argv[1], &st);
	size = st.st_size;

    printf("size = %d\n", size);

	in_buf = malloc(sizeof(char) * size);
	out_buf = malloc(sizeof(char) * size * 2);	

	ret = fread(in_buf, sizeof(char) * size, 1, in_fp);
	if(ret <= 0) {
		printf("Read %s error.\n", in_file);
		fclose(in_fp);
		goto err;
	}

    if(in_buf != NULL && out_buf != NULL) {
        DoConvert(in_buf, out_buf, size);
	} else {
        printf("Alloc memory fail!.\n");
        goto err;
    }

    ret = fwrite(out_buf, sizeof(char) * size * 2, 1, out_fp);
	if(ret <= 0) {
		printf("Write %s error.\n", out_file);
		fclose(out_fp);
		goto err;
	}
	
	free(in_buf);
	free(out_buf);

	fclose(in_fp);
	fclose(out_fp);
	printf("Done.\n");

	return 0;

    err:
        return -1;
}
