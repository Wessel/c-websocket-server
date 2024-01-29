/* test(json-c): Unit tests for data casting */
#include "../include/json.h"
#include "../include/macros.h"

#include "../include/libtap.h"

void run_json_tests(int argc, char* argv[], char* env[]) {
  /* Unit test for parsing JSON object*/
  printf("\033[0;35m--Tests for parsing JSON object--\033[0;0m\n");

  char* json_string = "{ \"auth\": 1, \"payload\": { \"sensorId\": \"LDR_1\", \"sensorData\": \"55\"  } }";
  Envelope envelope;
  int status_code = parse_envelope_json(json_string, &envelope);
  dbg("status_code(%d)\nEnvelope { auth: %s, payload: Message { sensorId: %s, sensorData: %s } }\n", status_code, envelope.auth, envelope.payload.sensorId, envelope.payload.sensorData);

  ok(status_code == 0, "`parse_envelope_json` returned `json_string` casted as `Envelope`.");
  like(envelope.payload.sensorId, "LDR_1", "`envelope.payload.sensorId is the same as `json_string` (`LDR_1`)");
  like(envelope.payload.sensorData, "55", "`envelope.payload.sensorData is the same as `json_string` (`55`)");
}
