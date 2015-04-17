/* This is the main test program. */
#include "NishantMessages.h"
#include "Message.h"
#include "Actor.h"
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

MESSAGE_HANDLER_DEFINITION_BEGIN ( ActorImpl, ProcessTestMessage, ResultMessage) {
    int id = msg.id;
    auto message = msg.msg;

} MESSAGE_HANDLER_DEFINITION_END

MESSAGE_HANDLER_DEFINITION_BEGIN ( TreeActorImpl, PS3, CreateSubTree) {
	cout<<"called once"<<endl;
    int id = msg.id;
    auto message = msg.msg;
    for( int i = 0; i < 1; ++i ) {
        timespec to_sleep = { 5, 0 };
        timespec remaining;

        while( nanosleep( &to_sleep, &remaining ) != 0 ) {
            to_sleep = remaining;
        }
    }

} MESSAGE_HANDLER_DEFINITION_END

MESSAGE_HANDLER_DEFINITION_BEGIN ( ActorImpl, ProcessTestMessage1, SendWorkMsg) {

    int id = msg.id;
    auto message = msg.msg;
    /*
    Threads wait for some time to simulate work
    */
	addWait(3);

    //send the results to the result collector
    ResultMessage_Factory(msg.resultProcessor,  id, message);


} MESSAGE_HANDLER_DEFINITION_END


void testParallelShutdown() {
    cout<<"Testing parallel shutdown"<<endl;

    Actor *ResultCollector = new Actor();
    ResultCollector->ForkAndSpin();
    int numberOfWorkers = 150;
    Json::Value msg = "work string";
    Actor *worker = new Actor[numberOfWorkers];
    for(int i = 0; i<numberOfWorkers; i++) {
        worker[i].ForkAndSpin();
        SendWorkMsg_Factory(worker[i], i, msg, *ResultCollector);    
    }

    for(int i = 0; i<numberOfWorkers; i++) {
        KillEvProc(worker[i]);
    }
    for(int i = 0; i<numberOfWorkers; i++) {
        worker[i].WaitForProcessorDeath();  
    }

    KillEvProc(*ResultCollector);
    ResultCollector->WaitForProcessorDeath();
    cout<<"parallel shutdown tested"<<endl;
}

void testTreeFormation() {

    cout<<"building a tree structure"<<endl;
    TreeActor *root = new TreeActor(1);
    root->ForkAndSpin();
    int numberofLevel = 3, numberOfChildrenPerLevel = 2;
    root->MakeSubTree(numberofLevel, numberOfChildrenPerLevel);
    cout<<"tree structure created"<<endl;
    cout<<"sending messages to children(cascading messages)"<<endl;
    root->SendMessages();   
    root->killChildren();
    KillEvProc(*root);
    root->WaitForProcessorDeath();
}

void testActorPartialDeath() {
    
    TreeActor *root = new TreeActor(1);
    Json::Value msg = "work string";
    root->ForkAndSpin();
    cout<<"killing actor"<<endl;
    KillEvProc(*root);
    CreateSubTree_Factory(*root, 1, msg);
    cout<<"waiting for actor to die"<<endl;
    root->WaitForProcessorDeath();
    cout<<"actor death confirmed, sending message to actor"<<endl;
    CreateSubTree_Factory(*root, 1, msg);
}

void testingMessageHandling() {
    
    TreeActor *root = new TreeActor(1);
    Json::Value msg = "work string";
    root->ForkAndSpin();
    cout<<"killing actor"<<endl;
    //ResultMessage_Factory(*root, 1, msg);
       	
    CreateSubTree_Factory(*root, 1, msg);
    addWait(1);
    KillEvProc(*root);
    root->WaitForProcessorDeath();
    
}


#define MACRO(X,Y)                         \
do {                                       \
  cout << "1st arg is:" << (X) << endl;    \
  cout << "2nd arg is:" << (Y) << endl;    \
  cout << "Sum is:" << ((X)+(Y)) << endl;  \
  findArgs(X,Y);						   \
} while (0)





#define MORE_CODE \
    cout<< "this is more code" <<endl; \
}

#define MSG_HANDLER (MSG_TYPE, MSG_HANDLER) \
if()

/*
FUNCTION_ABC
MORE_CODE
*/
//void findArgs(int a, int b) {

//}

class Car {
    
public:
    int a;
    Car () {

    }
    Car(int a ){
        this->a = a;
    }
    virtual void methodSig() {
        
    }
};

class NewCar: public Car {
public:
    int abc =1;
    NewCar(int a) {
        this->a = a;
        abc =2;
    }
    void print() {
        cout<<"hi" <<abc<<endl;
    }
    virtual void methodSig() {

    }
};


class NewCar1: public Car {
public:
    char b;
    NewCar1(int a) {
        this->a = a;
    }
    virtual void methodSig() {
        
    }
};
void checkObj(Car* obj) {

    try {
        NewCar* c = dynamic_cast<NewCar*>(obj);
        
        if(c == NULL) {
            cout << "object did not match " << endl;    
        } else {
            cout << "object mached " << endl;
        }
        
    } catch (...) {
        
    }
}

/*
void f1(Car car) {
	cout<<"car"<<endl;
}*/
void f1(NewCar car) {
	cout<<"car"<<endl;

}
void f1(NewCar1 car) {
	cout<<"car"<<endl;
}

int main(void){
	testingMessageHandling();
	/*
	MACRO(1,2);
    //MACRO(1,3);
    //calMySuff(1);
  //  Car *a = new Car(1);
  //  cout << typeid(a).name()<<endl;
    Car *b = new Car(2);
    
    NewCar* c = new NewCar(1);
    NewCar1* c1 = new NewCar1(1);
    
    b = c;
    
    //f1(b);

    // /SendWorkMsg msg = new Message();
    int a =  ResultMessage::type;
    cout<<a<<endl;
    cout<<(int)ResultMessage::type<<endl;
    /*
	for(int i = 0; i <100; i++){
   		testParallelShutdown();
    	testTreeFormation();
    	testActorPartialDeath();
	}
    cout<<"all done"<<endl;
    */
	return 0;
}

/*
# define MACRO_TEST(classname, methodname, args, argsMethod) \
void Java_somepackage_##classname##_fixMethod args  {\
    cout << "2nd arg is:"<< endl;\
} 
MACRO_TEST(MyClassA, methodForClassA, (int arg1, int arg2), (arg1, arg2))
*/
