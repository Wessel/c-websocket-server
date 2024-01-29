<img src="https://avatars.githubusercontent.com/u/29184334?v=4" align="left" width="192px" height="192px"/>
<img align="left" width="0" height="192px" hspace="10"/>

> C Websocket Server

[![MIT License](https://img.shields.io/badge/license-MIT-007EC7.svg?style=flat-square)](/LICENSE)

<br><br>

## Table of Contents
* Introduction
* Libraries
* Data Structure

## Introduction
This websocket server parses JSON data sent by the client
in order to control the state of GPIO pins by writing them to a SQL database.

## Libraries

[argp](https://www.gnu.org/software/libc/manual/html_node/Argp.html) is used
for simplification of command line argument parsing.

[libtap](https://github.com/zorgnax/libtap) is used for unit testing, all tests
can be found inside the [/tests](/tests) directory.

[wsServer](https://github.com/Theldus/wsServer) is used as socket server, writing
a custom socket library was abundant for the course followed.

[json-c](https://github.com/json-c/json-c) is used to cast incoming JSON objects
into data envelopes.

[libmysqlclient](https://dev.mysql.com/downloads/c-api/) is used for a connection
to the SQL database.

## Data Structure
A request from the client would look as follows:
```json
{
  "auth": <authentication:str>
  "payload": {
    "sensorId": <sensor.id:str>
    "sensorData": <sensor.data:str>
  }
}
```

After the request has been parsed, it will be processed by a handler which will
in turn give a status code / data struct. This can be one of:
```c
enum RESPONSE_CODES {
  SUCCESS,
  MISSING_JSON,
  MISSING_PAYLOAD,
  MISSING_AUTH
};

[ { "sensorId": <sensor.id:str>, "state": <sensor.state:str> }, ... ]
```
