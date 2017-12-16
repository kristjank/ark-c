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

const char seed[] = "this is chrises top secret dev account passphrase";

int main(void)
{
	HDNode root;
	hdnode_from_seed((uint8_t *)seed, strlen(seed), SECP256K1_NAME, &root);
	hdnode_fill_public_key(&root);

	curve_point pub;
	ecdsa_read_pubkey(&secp256k1, root.public_key, &pub);
	printf(root.private_key);

	HDNode node;
	char addr1[MAX_ADDR_SIZE], addr2[MAX_ADDR_SIZE];

	for (int i = 0; i < 40; i++) {
		// unoptimized
		memcpy(&node, &root, sizeof(HDNode));
		hdnode_public_ckd(&node, i);
		hdnode_fill_public_key(&node);
		ecdsa_get_address(node.public_key, 0, HASHER_SHA2, addr1, sizeof(addr1));
		// optimized
		hdnode_public_ckd_address_optimized(&pub, root.chain_code, i, 0, HASHER_SHA2, addr2, sizeof(addr2), 0);
		// check
		//ck_assert_str_eq(addr1, addr2);
		printf(addr1);
		printf(addr2);

	}
  
  return 0;
}
