/* main.c */
/*
  Project description
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/tests.h"
#include "../include/libtap.h"

#include "../include/macros.h"

int main(int argc, char* argv[], char* env[]) {
  srand(time(NULL));

  /* Debug log: argv variables */
  dbg("argc:\t%d\n", argc);
  dbg("argv:\t", NULL);
  for (int i = 0; i < argc; i++) dbg_no_info("%s ", argv[i]);
  dbg_no_info("\n", NULL);

  /* Debug log: env variables */
  dbg("env:\t", NULL);

  int colors[] = { 31, 32, 33, 34, 35 };
  int colors_len = 4;
  int colors_i = 0;

  for (int i = 0; env[i] != NULL; i++) {
    dbg_no_info("\033[0;%dm%s\033[0;0m ", colors[colors_i], env[i]);
    colors_i = colors_i == colors_len ? 0 : colors_i + 1;
  }
  dbg_no_info("\n", NULL);

  /* Initialize unit tests */
  plan(5);

  dbg("Running `run_json_tests`\n", NULL);
  run_json_tests(argc, argv, env);
  dbg("Running `run_argp_tests`\n", NULL);
  run_argp_tests(argc, argv, env);

  done_testing();

  return 0;
}
