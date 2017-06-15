#include "connection.hpp"

void dump(unsigned char* buf, unsigned size){
  for(unsigned i = 0; i<size; ++i){
    printf("%02x",buf[i]);
  }
  printf("\n");
}

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

  unsigned char buf[1024];
  uint32_t in = 0xfeedface;

for (uint i = 0 ; i<= 0xff ; ++i){
  c.header((unsigned char)i);
  c.write((unsigned char*)&in,sizeof(in));
  c.header((unsigned char)i);
  c.write((unsigned char*)&in,sizeof(in));
  c.ret();
  if(c.read(buf,4)) {printf("Data for: 0x%02x\n",(unsigned char)i);dump((unsigned char*)buf,4);}
}
  //for(uint i=0;i<1000;++i){
    //char buf[1024];

    //char j = (i*174)%255;
    //c.write((char*)&i,sizeof(i));
    //c.preamble();



      //if(c.read(buf,4)){
        //printf("data for :0x%04x\n",i);
      //}else{
        //printf("NO data for :0x%04x\n",i);
      //}


  //}
//exit:
  return 0;
}
