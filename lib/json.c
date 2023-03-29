#include <string.h>

#include <json-c/json.h>

// Structs for JSON data to parse
#include "../include/json.h"


/** @brief Casts a JSON object from string to `Envelope`
 *
 * Iterates through the fields of `json` and casts the wanted
 * fields to `Envelope`. Returns the following codes:
 *  0 = Success
 *  1 = Malformed json object
 *  2 = Missing `payload` field
 *  3 = Missing `auth` field
 *
 * @param json The string to cast
 * @param Envelope the Envelope struct to cast into
 *
 * @returns The status code
*/
int parse_envelope_json(const char* json, Envelope* envelope) {
  json_object* parsed = json_tokener_parse(json);
  if (!parsed) return MISSING_JSON;

  json_object* parsed_payload;
  if (json_object_object_get_ex(parsed, "payload", &parsed_payload)) {
    json_object* parsed_sensorId;
    if (json_object_object_get_ex(parsed_payload, "sensorId", &parsed_sensorId)) {
      envelope->payload.sensorId = strdup(json_object_get_string(parsed_sensorId));
    } else {
      envelope->payload.sensorId = "Nil";
    }

    json_object* parsed_sensorData;
    if (json_object_object_get_ex(parsed_payload, "sensorData", &parsed_sensorData)) {
      envelope->payload.sensorData = strdup(json_object_get_string(parsed_sensorData));
    } else {
      envelope->payload.sensorData = "Nil";
    }
  } else {
    return MISSING_PAYLOAD;
  }

  json_object* parsed_auth;
  if (json_object_object_get_ex(parsed, "auth", &parsed_auth)) {
    envelope->auth = strdup(json_object_get_string(parsed_auth));
  } else {
    return MISSING_AUTH;
  }

  json_object_put(parsed);

  return SUCCESS;
}