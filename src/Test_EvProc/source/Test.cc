/* This is the main test program. */
#include "NishantMessages.h"
#include "Actor.h"
#include "MessageMacros.h"

#include <iostream>
#include <ctime>

using namespace std;

MESSAGE_HANDLER_DEFINITION_BEGIN ( ActorImpl, ProcessTestMessage, ResultMessage) {
    int id = msg.id;
    auto message = msg.msg;
    cout << "Received results from : [" << id << "]: " << message.asString() << endl;

} MESSAGE_HANDLER_DEFINITION_END

MESSAGE_HANDLER_DEFINITION_BEGIN ( ActorImpl, ProcessTestMessage1, SendWorkMsg) {

    int id = msg.id;
    auto message = msg.msg;

    /*
    Threads wait for some time to simulate work
    */
    for( int i = 0; i < id%3; ++i ) {
        timespec to_sleep = { 5, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }

    cout << "sending result from : [" << id << "]: to ResultCollector " << endl;

    //send the results to another actor
    ResultMessage_Factory(msg.resultProcessor,  id, message);


} MESSAGE_HANDLER_DEFINITION_END


int main(void){

    Actor ResultCollector;
    ResultCollector.ForkAndSpin();

    Json::Value msg = "work string";
    Actor workers[10];

    for(int i = 0; i<5; i++) {
        workers[i].ForkAndSpin();
        SendWorkMsg_Factory(workers[i], i, msg, ResultCollector);    
    }


    //wait fort the actors to finish work
    for( int i = 0; i < 5; ++i ) {
        timespec to_sleep = { 5, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }

    //kill all the worker actors
    for(int i = 0; i<10; i++) {
        KillEvProc(workers[i]);
        workers[i].WaitForProcessorDeath();   
    }

    KillEvProc(ResultCollector);
    ResultCollector.WaitForProcessorDeath();

	return 0;
}