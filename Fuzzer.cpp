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
  c.auth(2101111); // <-- your index number goes here
exit:
  return 0;
}
