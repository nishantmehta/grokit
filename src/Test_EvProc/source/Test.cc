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
    //cout << "Received results from : [" << id << "]: " << message.asString() << endl;

} MESSAGE_HANDLER_DEFINITION_END

MESSAGE_HANDLER_DEFINITION_BEGIN ( TreeActorImpl, PS3, CreateSubTree) {
    cout<<"Received msg"<<endl;
    int id = msg.id;
    auto message = msg.msg;
    for( int i = 0; i < 1; ++i ) {
        timespec to_sleep = { 5, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }
    cout <<"finished processing"<< endl;

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

    //cout << "sending result from : [" << id << "]: to ResultCollector " << endl;

    //send the results to another actor
    ResultMessage_Factory(msg.resultProcessor,  id, message);


} MESSAGE_HANDLER_DEFINITION_END


void addWait(int count) {
    for( int i = 0; i < count; ++i ) {
        timespec to_sleep = { 5, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }
}

void testParallelShutdown() {
    cout<<"Testing parallel shutdown"<<endl;
    Actor ResultCollector;
    ResultCollector.ForkAndSpin();
    int wo = 150;
    Json::Value msg = "work string";
    Actor *worker = new Actor[wo];
    for(int i = 0; i<wo; i++) {
        worker[i].ForkAndSpin();
        SendWorkMsg_Factory(worker[i], i, msg, ResultCollector);    
    }

    for(int i = 0; i<wo; i++) {
        KillEvProc(worker[i]);
    }
    for(int i = 0; i<wo; i++) {
        worker[i].WaitForProcessorDeath();  
    }

    KillEvProc(ResultCollector);
    ResultCollector.WaitForProcessorDeath();
    delete [] worker;
    cout<<"parallel shutdown tested"<<endl;
}

void testTreeFormation() {

    cout<<"building a tree structure"<<endl;
    TreeActor root(1);
    root.ForkAndSpin();
    int numberofLevel = 3, numberOfChildrenPerLevel = 2;
    root.MakeSubTree(numberofLevel, numberOfChildrenPerLevel);
    cout<<"tree structure created"<<endl;

    cout<<"sending messages to children(cascading messages)"<<endl;
    root.SendMessages();   

    cout<<"waiting for actors to send messages"<<endl;
    addWait(2);
    cout<<"wait completed, kill tree structure"<<endl;

    root.killChildren();
    KillEvProc(root);
    root.WaitForProcessorDeath();

}

void testActorPartialDeath() {
    
    TreeActor root(1);
    Json::Value msg = "work string";
    root.ForkAndSpin();
    cout<<"killing actor"<<endl;
    KillEvProc(root);
    cout<<"waiting for actor to die"<<endl;
    root.WaitForProcessorDeath();
    cout<<"actor death confirmed, sending message to actor"<<endl;
    CreateSubTree_Factory(root, 1, msg);
    cout<<"test completed"<<endl;
}

int main(void){
    //testParallelShutdown();
    testTreeFormation();
    testActorPartialDeath();
    cout<<"all done"<<endl;
	return 0;
}
