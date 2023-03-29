/* main.c */
/*
  A simple C websocket server that can accept, parse and send JSON data.
*/
#include <argp.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "../include/utils.h"
#include "../include/ws.h"
#include "../include/json.h"
#include "../include/active.h"
#include "../include/macros.h"
#include "../include/config.h"
#include "../include/database.h"
#include "../include/gpio.h"

#include "./events/events.c"

size_t connections_size = 100;
int connections_head = 0;
char* connections[100] = {};

#ifndef __MAIN__
  #define __MAIN__
  #define __DEBUG__ ACTIVE

  char _server[56] = "172.17.0.1";
  char _user[56] = "root";
  char _password[56] = "password";
  char _database[56] = "lightcontroller";

  MYSQL* sql_conn;

  // char* GPIO_RED = "21";
  // char* GPIO_RNG = "22";
  // char* GPIO_GRN = "23";

  const char* PREFIX_HEARTBEAT = "[\033[31mHRTB\033[0m]\t";
  const char* PREFIX_DATABASE = "[\033[36mDTBS\033[0m]\t";
  const char* PREFIX_GPIO = "[\033[35mGPIO\033[0m]\t";
#endif


// Define the structure to store the arguments
struct arguments {
  int port;
  int timeout;
};

// Define the argument parser
static struct argp_option options[] = {
  { "port", 'p', "PORT", 0, "Port number" },
  { "timeout", 't', "TIMEOUT", 0, "Timeout in seconds" },
  { 0 }
};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;
  switch (key) {
    case 'p': arguments->port = atoi(arg); break;
    case 't': arguments->timeout = atoi(arg); break;
    default: return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, 0, 0 };

int main(int argc, char *argv[], char *env[]) {
  struct arguments args;

  // Set default values for the arguments
  args.port = 8080;
  args.timeout = 10;

  // Parse the arguments
  argp_parse(&argp, argc, argv, 0, 0, &args);

  sql_conn = init_mysql();

  // init_pin(GPIO_RED, "out");
  // init_pin(GPIO_RNG, "out");
  // init_pin(GPIO_GRN, "out");

  struct ws_events events;
  events.onopen = &onopen;
  events.onclose = &onclose;
  events.onmessage = &onmessage;

  ws_socket(&events, args.port, 0, args.timeout);

  return 0;
}