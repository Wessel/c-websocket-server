#include "../../include/ws.h"
#include "../../include/active.h"

void onopen(ws_cli_conn_t* client) {
  char* cli;
  cli = ws_getaddress(client);

  connections[connections_head] = cli;
  connections_head += 1;

  int i = 0;
  while (connections[i] != NULL) {
    printf("\n%s\n", connections[i]);
    i += 1;
  }

  char res_message[2048];
  sprintf(res_message, "Welcome %s to c-ws-server!\nThere are currently %d other clients connected.\nCommands: exit, heartbeat, connected", cli, connections_head - 1);
  // sprintf(res_message, "Welcome %s", cli);

  ws_sendframe_txt(client, res_message);
  printf("Connection opened to:\t\t%s\n", cli);
}