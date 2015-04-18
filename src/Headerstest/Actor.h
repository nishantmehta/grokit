
// Copyright 2013 Tera Insights, LLC. All Rights Reserved.

#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "EventGenerator.h"
#include "EventGeneratorImp.h"
#include "EventProcessorImp.h"
#include "EventProcessor.h"
#include "MessageMacros.h"
#include "NishantMessages.h"


class ActorSystemStarterImpl : public EventGeneratorImp {
    private:
        // Proxy to send the test messages
        EventProcessor target;

        // Current message ID
        int id;

    public:
        // Constructors / Destructor
        ActorSystemStarterImpl(EventProcessor& _target);

        virtual ~ActorSystemStarterImpl() { }

        virtual int ProduceMessage(void);
};

class ActorSystemStarter : public EventGenerator {
    public:
        ActorSystemStarter(EventProcessor& _target) { 
        	evGen = new ActorSystemStarterImpl(_target);
        }
        virtual ~ActorSystemStarter() { }

};

class ActorImpl : public EventProcessorImp {
    private:

    public:
        // Constructors / Destructor
        ActorImpl() {
            RegisterMessageProcessor(ResultMessage::type, &ProcessTestMessage);
            RegisterMessageProcessor(SendWorkMsg::type, &ProcessTestMessage1);
        }

        virtual ~ActorImpl() { }

        MESSAGE_HANDLER_DECLARATION(ProcessTestMessage);
        MESSAGE_HANDLER_DECLARATION(ProcessTestMessage1);
};

class Actor : public EventProcessor {
    public:
        Actor() {
            evProc = new ActorImpl();
        }

        virtual ~Actor() { }
};

#endif // _ACTOR_H_
