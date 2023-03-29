#include <mysql/mysql.h>

#ifndef DATABASE_H
#define DATABASE_H

extern char _server[56];
extern char _user[56];
extern char _password[56];
extern char _database[56];


MYSQL* init_mysql();
void kill_mysql();
void finish_with_error();
int construct_and_exec(char* command);
int get_sensor_state(int sensorId);

#endif