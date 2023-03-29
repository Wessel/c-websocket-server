#include <argp.h>

#include "../include/libtap.h"
#include "../include/macros.h"

// Define the structure to store the arguments
struct arguments {
  int port;
  int timeout;
};

// Define the argument parser
static struct argp_option options[] = {
  {"port", 'p', "PORT", 0, "Port number"},
  {"timeout", 't', "TIMEOUT", 0, "Timeout in seconds"},
  {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;
  switch (key) {
  case 'p':
    arguments->port = atoi(arg);
    break;
  case 't':
    arguments->timeout = atoi(arg);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, 0 };



void run_argp_tests(int argc, char* argv[], char* env[]) {

  printf("\033[0;35m--Tests for parsing CL args--\033[0;0m\n");

  /* Unit tests for parsing console arguments */
  struct arguments args;

  // Set default values for the arguments
  args.port = 8080;
  args.timeout = 10;
  dbg("defaults(Arguments { port: 8080, timeout: 10 })\n", NULL);

  // Parse the arguments
  argp_parse(&argp, argc, argv, 0, 0, &args);
  dbg("parsed(Arguments { port: %d, timeout: %d })\n", args.port, args.timeout);

  ok(args.port == 6060, "Arg `port` is `6060`");
  ok(args.timeout == 500, "Arg `timeout` is `500`");

}