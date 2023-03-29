#include "../../include/ws.h"
#include "../../include/active.h"
#include "../../include/array.h"

void onclose(ws_cli_conn_t* client) {
  char* cli;
  cli = ws_getaddress(client);

  printf("Connection closed by:\t\t%s\n", cli);

  int index = find_index(connections, 100, cli);
  if (index  == -1) return;

  for (int i = index - 1; i < connections_size - 1; i++) {
    connections[i] = connections[i + 1];
  }
  connections_head -= 1;
}