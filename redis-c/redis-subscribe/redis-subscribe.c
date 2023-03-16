/*
 * This example will show how to subscribe to the selected channel in Redis
 * Program will connect to the redis, subscribe and do nothing until message is published to selected channel
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <signal.h>



#define REDIS_URL	    "192.168.4.214"
#define REDIS_PORT	    6379
const char* REDIS_CHANNELNAME = "tag:test";
const char* command_auth = "auth ictadmin";


/*
 * Redis Callback functions
 *
 */
void connectCallback(const redisAsyncContext *c, int status);
void disconnectCallback(const redisAsyncContext *c, int status);
void onMessage(redisAsyncContext * c, void *reply, void * privdata);
void getCallback(redisAsyncContext *c, void *r, void *privdata);



int main(){
  /*
   * REDIS Async Initialize
   *
   */  
  signal(SIGPIPE, SIG_IGN);
  struct event_base *base = event_base_new();
  redisOptions options = {0};
  REDIS_OPTIONS_SET_TCP(&options, REDIS_URL, REDIS_PORT);
  struct timeval tv = {0};
  tv.tv_sec = 1;
  options.connect_timeout = &tv;

  /*
   *  REDIS Async Connection
   *
   */
  redisAsyncContext *c = redisAsyncConnectWithOptions(&options);
  redisLibeventAttach(c,base);

  /*
   *  REDIS attach callback functions
   *
   */
  redisAsyncSetConnectCallback(c, connectCallback);
  redisAsyncSetDisconnectCallback(c, disconnectCallback);

  /*
   *  REDIS Authentication
   *
   */
  printf("REDIS Async : Send Authentication CMD\n");
  redisAsyncCommand(c, getCallback, NULL, command_auth);

  /*
   *  REDIS Subscribe
   *  This will go on forever
   */
  printf("REDIS Async : Send Subscribe for relay tag\n");
  redisAsyncCommand(c, onMessage, NULL, "SUBSCRIBE %s", REDIS_CHANNELNAME);
  event_base_dispatch(base);


  /* 
   * forever loop
   *
   */
  while(1){

    //do nothing
    sleep(5);
  }

  return 0;
}











/*
 * Redis Callback Functions
 *
 */

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    else{
        printf("REDIS async Connected...\n");
    }
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    else{
        printf("REDIS async Disconnected...\n");
    }
}

void onMessage(redisAsyncContext * c, void *reply, void * privdata) {
  redisReply * r = reply;
  if (reply == NULL) return;

  printf("got a message of type: %i\n", r->type);
  if (r->type == REDIS_REPLY_ARRAY) {
    for (int j = 0; j < r->elements; j++) {
      printf("%u) %s\n", j, r->element[j]->str);
    }
  }
}

void getCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = r;
    if (reply == NULL) return;
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);
}

