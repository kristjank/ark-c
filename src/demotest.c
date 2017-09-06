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
