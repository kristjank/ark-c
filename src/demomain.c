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

  ArkLoaderStatus als = ark_api_loader_status(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Loader status: %ld - %d %ld\n", ark_helpers_getTimestamp(), als.now, als.loaded, als.blocksCount);

  ArkLoaderSyncStatus alss = ark_api_loader_statusSync(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Loader sync status: %s - %d %ld %ld\n", ark_helpers_getTimestamp(), alss.id, alss.syncing, alss.height, alss.blocks);

  ArkDelegateArray ada = ark_api_delegates(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of delegates: %d\n", ark_helpers_getTimestamp(), ada.length);

  ArkDelegate ad = ark_api_delegates_get(global_selectedPeer.ip, global_selectedPeer.port, "genesis_34");
  printf("[%s][ -ARK- ] One delegate num of produced blocks: %ld\n", ark_helpers_getTimestamp(), ad.producedBlocks);

  ArkVoterArray ava = ark_api_delegates_voters(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ -ARK- ] Num of voters: %d\n", ark_helpers_getTimestamp(), ava.length);

  ArkForgedDetails afd = ark_api_delegates_getForgedData(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ -ARK- ] Ark Forged Details: %ld\n", ark_helpers_getTimestamp(), afd.forged);

  ArkPeer p = ark_api_peers_get(global_selectedPeer, "167.114.29.44", 4002);
  printf("[%s][ -ARK- ] ArkPeer details: %s\n", ark_helpers_getTimestamp(), p.ip);

  ArkPeerArray apa = ark_api_peers(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of peers: %d\n", ark_helpers_getTimestamp(), apa.length);

  ArkPeerStatus aps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Active ArkPeer status: %s\n", ark_helpers_getTimestamp(), aps.header.payloadHash);

  ArkAccountArray aaa = ark_api_accounts(global_selectedPeer.ip, global_selectedPeer.port, "");
  printf("[%s][ -ARK- ] Num of accounts: %d\n", ark_helpers_getTimestamp(), aaa.length);
  
  return 0;
}
