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

  /// LOADER
  ArkLoaderStatus als = ark_api_loader_status(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Loader status: %ld - %d %ld\n", ark_helpers_getTimestamp(), als.now, als.loaded, als.blocksCount);

  ArkLoaderSyncStatus alss = ark_api_loader_statusSync(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Loader sync status: %s - %d %ld %ld\n", ark_helpers_getTimestamp(), alss.id, alss.syncing, alss.height, alss.blocks);

  /// DELEGATES
  ArkDelegateArray ada = ark_api_delegates(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of delegates: %d\n", ark_helpers_getTimestamp(), ada.length);

  ArkDelegate ad = ark_api_delegates_get(global_selectedPeer.ip, global_selectedPeer.port, "genesis_34");
  printf("[%s][ -ARK- ] One delegate num of produced blocks: %ld\n", ark_helpers_getTimestamp(), ad.producedBlocks);

  ArkVoterArray ava = ark_api_delegates_voters(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ -ARK- ] Num of voters: %d\n", ark_helpers_getTimestamp(), ava.length);

  ArkForgedDetails afd = ark_api_delegates_getForgedData(global_selectedPeer.ip, global_selectedPeer.port, "0267b310eac2bb0d6594de382a1ab74ac75b91e9d64a590b6249247b10fd9be829");
  printf("[%s][ -ARK- ] Ark Forged Details: %ld\n", ark_helpers_getTimestamp(), afd.forged);

  /// PEERS
  ArkPeer p = ark_api_peers_get(global_selectedPeer, "167.114.29.44", 4002);
  printf("[%s][ -ARK- ] ArkPeer details: %s\n", ark_helpers_getTimestamp(), p.ip);

  ArkPeerArray apa = ark_api_peers(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of peers: %d\n", ark_helpers_getTimestamp(), apa.length);

  ArkPeerStatus aps = ark_api_peers_getStatus(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Active ArkPeer status: %s\n", ark_helpers_getTimestamp(), aps.header.payloadHash);

  ArkPeerArray apa2 = ark_api_peers_getList(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of peers in a list: %d\n", ark_helpers_getTimestamp(), apa2.length);

  /// BLOCKS
  ArkFee af = ark_api_blocks_getFees(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Peer fee delegate: %ld\n", ark_helpers_getTimestamp(), af.delegate);
  
  ArkBlockArray aba = ark_api_blocks(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of blocks: %d\n", ark_helpers_getTimestamp(), aba.length);

  ArkBlock ab = ark_api_blocks_get(global_selectedPeer.ip, global_selectedPeer.port, "8337280477377825977");
  printf("[%s][ -ARK- ] Ark Block signature: %s\n", ark_helpers_getTimestamp(), ab.blockSignature);
  
  long f1 = ark_api_blocks_getFee(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Ark fee num: %ld\n", ark_helpers_getTimestamp(), f1);
  
  ArkBlockHeight abh = ark_api_blocks_getHeight(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Ark Block height: %s %ld\n", ark_helpers_getTimestamp(), abh.id, abh.height);
  
  /// ACCOUNTS
  ArkAccount aa = ark_api_accounts(global_selectedPeer.ip, global_selectedPeer.port, "DBi2HdDY8TqMCD2aFLVomEF92gzeDmEHmR");
  printf("[%s][ -ARK- ] Ark account publicKey: %s\n", ark_helpers_getTimestamp(), aa.publicKey);
  
  ArkAccountBalance aab = ark_api_accounts_getBalance(global_selectedPeer.ip, global_selectedPeer.port, "DBi2HdDY8TqMCD2aFLVomEF92gzeDmEHmR");
  printf("[%s][ -ARK- ] Ark account unconfirmed balance: %s\n", ark_helpers_getTimestamp(), aab.unconfirmedBalance);
  
  char* aapk = ark_api_accounts_getPublicKey(global_selectedPeer.ip, global_selectedPeer.port, "DBi2HdDY8TqMCD2aFLVomEF92gzeDmEHmR");
  printf("[%s][ -ARK- ] Ark account public key: %s\n", ark_helpers_getTimestamp(), aapk);
  
  /// TRANSACTIONS
  ArkTransactionArray ata = ark_api_transactions(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of Ark transactions in list: %d\n", ark_helpers_getTimestamp(), ata.length);

  ArkTransactionArray atau = ark_api_transactions_unconfirmed(global_selectedPeer.ip, global_selectedPeer.port);
  printf("[%s][ -ARK- ] Num of unconfirmed Ark transactions in list: %d\n", ark_helpers_getTimestamp(), atau.length);

  if (ata.length > 0)
  {
    ArkTransaction at = ark_api_transactions_get(global_selectedPeer.ip, global_selectedPeer.port, ata.data[0].id);
    printf("[%s][ -ARK- ] ArkTransaction signature: %s\n", ark_helpers_getTimestamp(), at.signature);
  }

  if (atau.length > 0)
  {
    ArkTransaction atu = ark_api_transactions_get(global_selectedPeer.ip, global_selectedPeer.port, atau.data[0].id);
    printf("[%s][ -ARK- ] Unconfirmed ArkTransaction signature: %s\n", ark_helpers_getTimestamp(), atu.signature);
  }

  return 0;
}
