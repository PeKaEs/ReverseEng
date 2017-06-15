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
}
client::~client(){
  exit();
}
void client::exit(){
  close(fd);
}
void client::write(char *buf, unsigned size){
  char *pos = buf;
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
void client::read(char *buf, unsigned size){
  char *pos = buf;
     while(size>0) {
       int ret = ::read(fd,pos,size);
       if(ret<=0) {
         printf("err read\n");
         exit();
         return;
       }
       pos  += ret;
       size -= ret;
     }
}
void client::auth (uint32_t idx) { write((char*)&idx,sizeof(idx)); }
