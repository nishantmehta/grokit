    // Copyright 2013 Tera Insights, LLC. All Rights Reserved.

    #ifndef _TEST_ACTOR_H_
    #define _TEST_ACTOR_H_

    #include "EventGenerator.h"
    #include "EventGeneratorImp.h"
    #include "EventProcessorImp.h"
    #include "EventProcessor.h"
    #include "MessageMacros.h"
    #include "ActorTestMessages.h"

    using namespace std;

	class Actor : public EventProcessor{
        public: 
            Actor();
    };
	class ActorImpl : public EventProcessorImp {
        public:
        	ActorImpl() {};

        	void foo(ResultMessage &msg) {
        		cout<<"foo executed"<<endl;
        	}

        	void bar(CreateSubTree &msg) {
        		cout<<"bar executed"<<endl;
        	}

            ACTOR_HANDLE
                HANDLER(ResultMessage, foo)
                HANDLER(CreateSubTree, bar)
            END_HANDLE


    };
    Actor::Actor() {
        evProc = new ActorImpl();
    }
	#endif // _TEST_ACTOR_H_