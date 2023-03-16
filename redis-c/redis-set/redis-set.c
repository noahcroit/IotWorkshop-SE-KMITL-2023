/*
 *
 * This example will show ho to use Redis's "SET" command to write value to the selected channel.
 * Program will run forever for writing the string of integer value from 0 to ...
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>



#define REDIS_URL	    "192.168.4.214"
#define REDIS_PORT	    6379
const char* REDIS_CHANNELNAME = "tag:test";
const char* command_auth = "auth ictadmin";


int main(){
  /*
   * REDIS Connect & Authentication Test
   *
   */
  redisContext* client = redisConnect((char*)REDIS_URL, REDIS_PORT);
  redisReply* r = (redisReply*)redisCommand(client, command_auth);
  

  /*
   * REDIS SET & GET loop
   * Redis client will be used for Redis's "SET" and "GET" command
   *
   */
  int i=0;
  while(1){
    // reconnect
    client = redisConnect((char*)REDIS_URL, REDIS_PORT);

    if(!(client->err)){
      // authenticate
      freeReplyObject(r);
      r = (redisReply*)redisCommand(client, command_auth);

      // set value to specific channel
      char value[10];
      sprintf(value, "%d", i);
      r = (redisReply*)redisCommand(client, "%s %s %s", "set", REDIS_CHANNELNAME, value);
      
      // increase for the next value
      i++;
    }
    // free client object, have to reconnect again but memory safe
    redisFree(client);

    sleep(5); // period of every 5 second
  }


  return 0;
}

