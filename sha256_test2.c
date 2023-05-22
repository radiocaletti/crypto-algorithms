/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
	          implementation. These tests do not encompass the full
	          range of available test vectors, however, if the tests
	          pass it is very, very likely that the code is correct
	          and was compiled properly. This code also serves as
	          example usage of the functions.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"

/*********************** FUNCTION DEFINITIONS ***********************/
int sha256_mytest()
{
	return 0;
}

void conv_to_string(BYTE* byteptr, int len)
{
	/* 16-adic repres. */
	char c[64];
	BYTE b;
	size_t j = 0;
	int n;

	for(int i = 0; i < len; i++)
	{
		b = byteptr[i];
		n = b % 16;
		if(n <= 9)
		{
			c[j+1] = n + '0';
		}
		else{
			c[j+1] = n - 10 + 'a';
		}
		n = (b - n)/16;
		if(n <= 9)
		{
			c[j] = n + '0';
		}
		else{
			c[j] = n - 10 + 'a';
		}
		j = j+2;
	}

	for(int i = 0; i < 64; i++)
	{
		printf("%c", c[i]);
	}
}

static void hash_to_string(char string[65], BYTE hash[32])
{
	size_t i;
	for (i = 0; i < 32; i++) {
		string += sprintf(string, "%02x", hash[i]);
	}
}


int main()
{
	BYTE text1[] = {"hello"};
	BYTE text2[] = {"s"};
	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);

	printf("SHA-256 testing.\n");
	
	conv_to_string(buf, 32);

	printf("\n");

	sha256_init(&ctx);
	sha256_update(&ctx, text2, strlen(text2));
	sha256_final(&ctx, buf);

	char str[65];
	hash_to_string(str, buf);

	for(int i = 0; i < 64; i++)
	{
		printf("%c", str[i]);
	}

	printf("\n");
	printf("Hash written.\n");

	return(0);
}
