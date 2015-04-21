/* This is the main test program. */

#include "ActorTestMessages.h"
#include "Message.h"
#include "TestActor.h"
#include "MessageMacros.h"
#include <iostream>
#include <ctime>

using namespace std;

void addWait(int count) {
    for( int i = 0; i < count; ++i ) {
        timespec to_sleep = { 1, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }
}

void NewMessagingSysTest() {
	Actor *root = new Actor();
    Json::Value msg = "work string";
    root->ForkAndSpin();
    
    CreateSubTree_Factory(*root, 1, msg);
    ResultMessage_Factory(*root, 1, msg);

    CreateSubTree_Factory(*root, 1, msg);
    ResultMessage_Factory(*root, 1, msg);

    CreateSubTree_Factory(*root, 1, msg);
    ResultMessage_Factory(*root, 1, msg);
    KillEvProc(*root);

    root->WaitForProcessorDeath();
}

void NewMessagingSysTest2() {
    Actor *root = new Actor();
    Json::Value msg = "work string";
    root->ForkAndSpin();

    DieMessage_Factory(*root);

    root->WaitForProcessorDeath();
}


int main(void){
	
	NewMessagingSysTest();
    //NewMessagingSysTest2();
    addWait(1);
	return 0;
}