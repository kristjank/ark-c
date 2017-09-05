#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "include/arkcore.h"


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
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

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
 void testFPRINTF(void)
 {
	int arkBlockchainSetupFailed = ark_core_setEnvironment(DEVELOPMENT);
	if (arkBlockchainSetupFailed == 0)
	{
		printf("[ARK] Unable to connect to blockchain\n");
		return 0;
	}


	int ps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
	printf("[ARK] Active ArkPeer status: %d\n", ps);
 

    CU_ASSERT(0 == 0);
    CU_ASSERT(2 == 2);
    CU_ASSERT(7 == 8);

 }
 

int main(void)
{
  CU_pSuite pSuite = NULL;
  
     /* initialize the CUnit test registry */
     if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
  
     /* add a suite to the registry */
     pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
     if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
     }
  
     /* add the tests to the suite */
     /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
     if ((NULL == CU_add_test(pSuite, "test of fprintf()", testFPRINTF)))
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
