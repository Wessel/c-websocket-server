#ifndef JSON_H
#define JSON_H

typedef struct {
  char* sensorId;
  char* sensorData;
} Message;

typedef struct {
  Message payload;
  char* auth;
} Envelope;

enum RESPONSE_CODES {
  SUCCESS,
  MISSING_JSON,
  MISSING_PAYLOAD,
  MISSING_AUTH
};

int parse_envelope_json(const char* json, Envelope* envelope);

#endif