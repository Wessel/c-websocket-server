#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#include "../include/macros.h"

/* Sets global variables | @WARNING these can be accessed by any other programme.*/
// Database connection
MYSQL* conn;
extern char _server[56];
extern char _user[56];
extern char _password[56];
extern char _database[56];

// Debug log prefixes
extern char* PREFIX_HEARTBEAT;
extern char* PREFIX_DATABASE;
extern char* PREFIX_GPIO;


/** @brief Gracefully ends the connection to `_server` on error.
 *
 * This function is used to gracefully exit the
 * database connection when operations lead to an error.
 * After the connection has been closed the program will
 * also be forced to exit.
 *
 * @returns Void.
 */
void finish_with_error() {
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

/** @brief Initializes the connection to the database
 *
 * Initializes a conncection to `_user@_server`
 * That will be used by the rest of this lib.
 *
 * @returns Void.
 */
MYSQL* init_mysql() {
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, _server, _user, _password, _database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  return conn;
}

/** @brief Returns the current state of light sensors in the connected DB.
 *
 * This function will send the following query to the connected DB:
 *  `SELECT (state) FROM sensors WHERE sensorId={sensorId}`
 * to retrieve the current state of `sensorId` and return it.
 *
 * @param sensorId the ID of the sensor to check for
 * @returns The state of `sensorId` according to the connected DB.
 */
int get_sensor_state(int sensorId) {
  int state = 0;

  dbg_no_info("%s Start sensor state check\n", PREFIX_HEARTBEAT);

  char query[50];
  sprintf(query, "SELECT (state) FROM sensors WHERE sensorId=%d;", sensorId);
  if (mysql_query(conn, query)) finish_with_error();

  MYSQL_RES* result = mysql_store_result(conn);
  if (result == NULL) finish_with_error();

  int num_fields = mysql_num_fields(result);
  dbg("num_fields=%d\n", num_fields);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result))) {
    for (int i = 0; i < num_fields; i++) {
      // sprintf(row_as_str, (row[i] ? row[i] : "NULL"));
      dbg_no_info("%s Sensor read as %s\n", PREFIX_DATABASE, row[i]);

      char *row_safe = row[i] ? row[i] : "NULL";

      if (strcmp(row_safe, "1") == 0) {
        // Sensor state 1 (ON)
        state = 1;
        // dbg_no_info("%s Setting pin `%s` to `1`\n", PREFIX_GPIO, GPIO_PIN);
        // set_pin(GPIO_PIN, state);
      } else if (strcmp(row_safe, "0") == 0) {
        // Sensor state "OFF" (0)
        state = 0;
        // dbg_no_info("%s Setting pin `%s` to `0`\n", PREFIX_GPIO, GPIO_PIN);
        // set_pin(GPIO_PIN, state);
      }
    }
  }

  finish:
    dbg_no_info("%s Free mysql result\n", PREFIX_DATABASE);
    mysql_free_result(result);
    dbg_no_info("%s Finished sensor state check. return state as %d\n", PREFIX_HEARTBEAT, state);
    return state;
}

MYSQL_RES* res;
MYSQL_ROW row;

/** @brief Construct a SQL query, execute it and log any output.
 *
 * This function can be used as a simpler way to execute singular
 * SQL queries. The SQL query is parsed, ran and then its outputs
 * are logged to `STDOUT`.
 *
 * @param command The SQL query to execute
 * @returns The exit code
 */
int construct_and_exec(char* command) {
  if (mysql_query(conn, command)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
    exit(1);
  }

  while ((row = mysql_fetch_row(res)) != NULL) {
    printf("%s\n", row[0]);
  }

  return 0;
}
