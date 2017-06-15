#ifndef FileEnc_hpp
#define FileEnc_hpp

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <inttypes.h>


class client {
  struct sockaddr_in serv_addr;
  int fd;
public:
  client(char *host, int port);
  ~client();
  void exit();
  void write(unsigned char *buf, unsigned size);
  bool read(unsigned char *buf, unsigned size);
  void auth (uint32_t idx);
  void ret();
  void header(unsigned char in);
};


#endif
