#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "include/arkclient.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
  return 0;
}

/* The suite cleanup function.
  * Closes the temporary file used by the tests.
  * Returns zero on success, non-zero otherwise.
  */
int clean_suite1(void)
{
  return 0;
}

/* Test Ark client environment setup
 * 1 == SUCCESS
 */
void test_arkSetup(void)
{
  int arkSetup = ark_client_setEnvironment(DEVELOPMENT);
  CU_ASSERT(arkSetup == 1)

  ArkDelegateArray ada = ark_api_delegates(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ARK - MOCK] Num of delegates: %d\n", ark_helpers_getTimestamp(), ada.length);

  ArkDelegate ad = ark_api_delegates_get(global_selectedPeer.ip, global_selectedPeer.port, "genesis_34");
  printf("[%s][ARK - MOCK] One delegate num of produced blocks: %dl\n", ark_helpers_getTimestamp(), ad.producedBlocks);

  ArkVoterArray ava = ark_api_delegates_voters(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ARK - MOCK] Num of voters: %d\n", ark_helpers_getTimestamp(), ava.length);

  ArkForgedDetails afd = ark_api_delegates_getForgedData(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ARK - MOCK] Ark Forged Details: %d\n", ark_helpers_getTimestamp(), afd.forged);

  int ps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ARK - MOCK] Active ArkPeer status: %d\n", ark_helpers_getTimestamp(), ps);

  ArkPeer p = ark_api_peers_get(global_selectedPeer, "167.114.29.44", 4002);
  printf("[ARK - MOCK] - ArkPeer details: %s\n", p.ip);

  ArkAccountArray aaa = ark_api_accounts(global_selectedPeer.ip, global_selectedPeer.port, "");
  printf("[ARK - MOCK] Num of accounts: %d\n", aaa.length);
  
}

void test_arkPeers(void)
{
  int arkSetup = ark_client_setEnvironment(DEVELOPMENT);
  printf("[ARK TESTS] - Ark setup status: %d\n", arkSetup);
  ArkPeer p = ark_api_peers_get(global_selectedPeer, "167.114.29.44", 4002);
  printf("[ARK TESTS] - ArkPeer details: %d\n", p.port);
  CU_ASSERT(p.port == 4002);
}

int main(void)
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
  if (NULL == pSuite)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
  if ((NULL == CU_add_test(pSuite, "test of ARKLIB PEERS", test_arkPeers)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
