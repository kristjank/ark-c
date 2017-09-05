#include "include/arkclient.h"
 
int main(void)
{
  
  int arkBlockchainSetupFailed = ark_client_setEnvironment(DEVELOPMENT);
  if (arkBlockchainSetupFailed == 0)
  {
      printf("[ARK] Unable to connect to ARK Peer\n");
      return 0;
  }


  int ps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[ARK] Active ArkPeer status: %d\n", ps);

  ArkAccountArray aaa = ark_api_accounts(global_selectedPeer.ip, global_selectedPeer.port, "");
  printf("[ARK] Num of accounts: %d\n", aaa.length);
  
  return 0;
}