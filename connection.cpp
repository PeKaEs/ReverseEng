#include "connection.hpp"

client::client(char *host, int port){
  memset(&serv_addr,'0',sizeof(serv_addr));
    fd = 0;
    struct hostent *he = gethostbyname(host);
    if(!he) {
      printf("err gethostbyname\n");
      return;
    }
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      printf("err socket\n");
      return;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port);
    memcpy(&serv_addr.sin_addr, he->h_addr_list[0], he->h_length);
    if(connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
      printf("err connect\n");
      return;
    }

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 999999;
    if(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout))< 0){
      printf("err setsockopt\n");
    }
    if (setsockopt (fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
               sizeof(timeout)) < 0)
       printf("err setsockopt send\n");;
}
client::~client(){
  exit();
}
void client::exit(){
  close(fd);
}
void client::write(unsigned char *buf, unsigned size){
  unsigned char *pos = buf;
      while(size>0) {
        int ret = ::write(fd,pos,size);
        if(ret<=0) {
          printf("err write\n");
          exit();
          return;
        }
        pos  += ret;
        size -= ret;
      }
}
bool client::read(unsigned char *buf, unsigned size){
  unsigned char *pos = buf;

     while(size>0) {

       int ret = ::read(fd,pos,size);

       if(ret<=0) {
         //printf("err read\n");
         //exit();
         return false;
       }
       pos  += ret;
       size -= ret;
     }
    return true;
}
void client::auth (uint32_t idx) { write((unsigned char*)&idx,sizeof(idx)); }
void client::header(unsigned char in) { write(&in,sizeof(in));}
void client::ret() {header(0x0d);}
