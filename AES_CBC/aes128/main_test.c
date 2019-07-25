#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"

int main(int argc, char*argv[])
{
	int i;
	
	const unsigned char master_key[32] = {
		'h', 'd', 'a', '2', '0', '1', '8','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'
	};
	const unsigned char text[16] = {0};

	const unsigned char iv[16] = {
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	};

	FILE *fr = fopen(argv[1], "rb+");
	int readRes = fread(text,sizeof(text),1,fr);

	unsigned char ivc[16];
	
	unsigned char encrypted[16], decrypted[16];
	memset(encrypted, 0, 16*sizeof(char));
	memset(decrypted, 0, 16*sizeof(char));

	AES_KEY key;

	printf("plaintext:\n");
	for (i = 0; i < 16; i++) {
		printf("%02x ", (unsigned int)text[i]);
	}

	printf("\n=============================\n");
	
	printf("decrypted:\n");
	AES_set_decrypt_key(master_key, 256, &key);
	// ecb
	// AES_ecb_encrypt(encrypted, decrypted, &key, AES_DECRYPT);

	//cbc
	memcpy( ivc, iv, 16*sizeof(char));
	AES_cbc_encrypt(encrypted,decrypted,16,&key,iv,AES_DECRYPT);
	for (i = 0; i < 16; i++) {
		printf("%c ", (unsigned int)decrypted[i]);
	}
	printf("\n");
	fclose(fr);
	return 0;

}
