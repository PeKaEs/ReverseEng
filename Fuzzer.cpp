#include "connection.hpp"

int main(int argc, char *argv[]){
  char serv[] = "serwerownia.no-ip.org";
  char *host  = serv;
  int   port  = 7777;
  if(argc > 2){
    host = argv[1];
  }
  if(argc > 3){
    port = atoi(argv[2]);
  }
  client c(host,port);
  c.auth(210111);

  for(uint i=0;i<1000;++i){
    char buf[1024];

    //char j = (i*174)%255;
    c.write((char*)&i,sizeof(i));
    c.preamble();



      if(c.read(buf,4)){
        printf("data for :0x%04x\n",i);
      }else{
        printf("NO data for :0x%04x\n",i);
      }


  }
exit:
  return 0;
}
