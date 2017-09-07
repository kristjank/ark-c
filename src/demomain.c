#include "include/arkclient.h"
 
int main(void)
{
  char* ts = NULL;

  int arkSetup = ark_client_setEnvironment(DEVELOPMENT);
  if (arkSetup == 0)
  {
      printf("[ARK] Unable to connect to ARK Peer\n");
      return 0;
  }

  ArkDelegateArray ada = ark_api_delegates(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ARK - MOCK] Num of delegates: %d\n", ark_helpers_getTimestamp(), ada.length);

  ArkDelegate ad = ark_api_delegates_get(global_selectedPeer.ip, global_selectedPeer.port, "genesis_34");
  printf("[%s][ARK - MOCK] One delegate num of produced blocks: %dl\n", ark_helpers_getTimestamp(), ad.producedBlocks);

  ArkVoterArray ava = ark_api_delegates_voters(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ARK - MOCK] Num of voters: %d\n", ark_helpers_getTimestamp(), ava.length);

  ArkForgedDetails afd = ark_api_delegates_getForgedData(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ARK - MOCK] Ark Forged Details: %ld\n", ark_helpers_getTimestamp(), afd.forged);

  int ps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ARK - MOCK] Active ArkPeer status: %d\n", ark_helpers_getTimestamp(), ps);

  ArkPeer p = ark_api_peers_get(global_selectedPeer, "167.114.29.44", 4002);
  printf("[%s][ARK - MOCK] - ArkPeer details: %s\n", ark_helpers_getTimestamp(), p.ip);

  ArkAccountArray aaa = ark_api_accounts(global_selectedPeer.ip, global_selectedPeer.port, "");
  printf("[%s][ARK - MOCK] Num of accounts: %d\n", ark_helpers_getTimestamp(), aaa.length);
  
  return 0;
}
