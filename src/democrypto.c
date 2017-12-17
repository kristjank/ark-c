#include <string.h>

#include "include/arkclient.h"

#include "../ark-crypto/../ark-crypto/bignum.h"
#include "../ark-crypto/base32.h"
#include "../ark-crypto/base58.h"
#include "../ark-crypto/bip32.h"
#include "../ark-crypto/bip39.h"
#include "../ark-crypto/ecdsa.h"
#include "../ark-crypto/pbkdf2.h"
#include "../ark-crypto/address.h"
#include "../ark-crypto/secp256k1.h"
#include "../ark-crypto/curves.h"

#define FROMHEX_MAXLEN 512
const char seed[] = "this is chrises top secret dev account passphrase";

const uint8_t *fromhex(const char *str)
{
	static uint8_t buf[FROMHEX_MAXLEN];
	size_t len = strlen(str) / 2;
	if (len > FROMHEX_MAXLEN) len = FROMHEX_MAXLEN;
	for (size_t i = 0; i < len; i++) {
		uint8_t c = 0;
		if (str[i * 2] >= '0' && str[i*2] <= '9') c += (str[i * 2] - '0') << 4;
		if ((str[i * 2] & ~0x20) >= 'A' && (str[i*2] & ~0x20) <= 'F') c += (10 + (str[i * 2] & ~0x20) - 'A') << 4;
		if (str[i * 2 + 1] >= '0' && str[i * 2 + 1] <= '9') c += (str[i * 2 + 1] - '0');
		if ((str[i * 2 + 1] & ~0x20) >= 'A' && (str[i * 2 + 1] & ~0x20) <= 'F') c += (10 + (str[i * 2 + 1] & ~0x20) - 'A');
		buf[i] = c;
	}
	return buf;
}

int main(void)
{
	HDNode root;
	char addr1[MAX_ADDR_SIZE], addr2[MAX_ADDR_SIZE];
	hdnode_from_seed((uint8_t *)seed, strlen(seed), SECP256K1_NAME, &root);
	hdnode_fill_public_key(&root);

	curve_point pub;
	ecdsa_read_pubkey(&secp256k1, root.public_key, &pub);
	ecdsa_get_address(root.public_key, 0x17, HASHER_SHA2, addr1, sizeof(addr1));
	printf(addr1);

/*
	memcpy(&node, &root, sizeof(HDNode));
	hdnode_public_ckd(&node, i);
	hdnode_fill_public_key(&node);
	ecdsa_get_address(node.public_key, 0x17, HASHER_SHA2, addr1, sizeof(addr1));
	// optimized
	hdnode_public_ckd_address_optimized(&pub, root.chain_code, i, 0, HASHER_SHA2, addr2, sizeof(addr2), 0);
	// check
	//ck_assert_str_eq(addr1, addr2);
	printf(addr1);
	printf(addr2);
*/
	
  return 0;
}
