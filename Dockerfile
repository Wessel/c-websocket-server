FROM gcc:latest

WORKDIR /c-websocket

COPY . .

RUN apt-get update && \
  apt-get install -y libjson-c-dev default-libmysqlclient-dev

CMD [ "make", "clean", "run" ]

EXPOSE 8080
