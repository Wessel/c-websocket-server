#include <string.h>
#include <unistd.h>

#include "../../include/ws.h"
#include "../../include/json.h"
#include "../../include/utils.h"
#include "../../include/active.h"

#include "../../include/macros.h"
#include "../../include/database.h"
#include "../../include/gpio.h"

extern char* GPIO_RED;
extern char* GPIO_RNG;
extern char* GPIO_GRN;

enum MESSAGES{
  STATE = 274811398,
  CONNECTED = -1975448840,
  HEARTBEAT = -1211425067,
  EXIT = 2090237503,
  GREEN = -1349713758,
  RED = -1945597812
};

void onmessage(ws_cli_conn_t* client,
  const unsigned char* msg,
  uint64_t size,
  int type) {
  char* cli = ws_getaddress(client);

  if (size < 1) {
    printf("Received empty message from:\t%s\n", cli);
    return;
  }

  int hashed_msg = (int)hash(msg);
  printf("Received message from:\t\t%s\nContents (%u):\t%s\nHashed:\t\t%d\n", cli, size, msg, hashed_msg);

  switch (hashed_msg) {
    case EXIT:
      ws_sendframe_txt(client, "cya");
      ws_close_client(client);
      break;
    case HEARTBEAT:
      ws_sendframe_txt(client, "heartbeat");
      break;
    case CONNECTED:
      int i = 0;
      while (connections[i] != NULL) {
        char packet[512];
        sprintf(packet, "%s", connections[i]);
        ws_sendframe_txt(client, packet);
        i += 1;
      }
      break;
    case STATE:
      char* state = (char*) malloc(100);
      int sensor_states[2] = { get_sensor_state(1), get_sensor_state(2) };
      sprintf(state, "[ { \"sensorId\": 1, \"state\": %d }, { \"sensorId\": 2, \"state\": %d } ]", sensor_states[0], sensor_states[1]);
      ws_sendframe_txt(client, state);
      free(state);
      break;
    case GREEN:
    // TODO(wessel): to-green
    // TODO(wessel): add state check
      // set_pin(GPIO_RED, 0);
      // set_pin(GPIO_GRN, 1);

      construct_and_exec("UPDATE sensors SET state=1 WHERE sensorId=1");
      return ws_sendframe_txt(client, "OK");
    case RED:
      // TODO(wessel): to-red
      // TODO(wessel): add state check
      // set_pin(GPIO_GRN, 0);
      // set_pin(GPIO_RNG, 1);
      // sleep(1);
      // set_pin(GPIO_RNG, 0);
      // set_pin(GPIO_RED, 1);

      construct_and_exec("UPDATE sensors SET state=0 WHERE sensorId=1");
      return  ws_sendframe_txt(client, "OK");
    default:
      Envelope envelope;
      int parsed = parse_envelope_json(msg, &envelope);
      if (parsed == 0) {
        printf("Auth: %s\n", envelope.auth);
        printf("Payload.sensorId: %s\n", envelope.payload.sensorId);
        printf("Payload.sensorData: %s\n", envelope.payload.sensorData);

        char query[68];
        sprintf(query, "UPDATE sensors SET state=%s WHERE sensorId=%s", envelope.payload.sensorData, envelope.payload.sensorId);
        construct_and_exec(query);

        char res_message[32];
        sprintf(res_message, "ok(parse_envelop_json:%d)", SUCCESS);
        ws_sendframe_txt(client, res_message);
        return;
      }

      char res_message[32];
      sprintf(res_message, "error(parse_envelop_json:%d)", parsed);

      ws_sendframe_txt(client, res_message);
      break;
  }
}
