
    // Copyright 2013 Tera Insights, LLC. All Rights Reserved.

    #ifndef _ACTOR_H_
    #define _ACTOR_H_

    #include "EventGenerator.h"
    #include "EventGeneratorImp.h"
    #include "EventProcessorImp.h"
    #include "EventProcessor.h"
    #include "MessageMacros.h"
    #include "NishantMessages.h"

    using namespace std;
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
    class TreeActor : public EventProcessor{
        public: 
            TreeActor(int i);
            void killChildren();
            void SendMessages();
            void MakeSubTree(int level, int numberOfChildren);
    };
    class Actor : public EventProcessor {
        public:
            Actor() {
                evProc = new ActorImpl();
            }

            virtual ~Actor() { }
    };
    class TreeActorImpl : public EventProcessorImp {
        private:
            vector<TreeActor> children;
        public:
            TreeActorImpl(int i) {
                RegisterMessageProcessor(CreateSubTree:: type, &PS3);
            }

            void killChildren() {
                TreeActor temp(1);
                if(children.size() > 0) {
                for (int i = 0; i < children.size(); i++) {
                    temp = children.at(i);
                    temp.killChildren();
                    temp.Seppuku();
                }
                for (int i = 0; i < children.size(); i++) {
                    temp = children.at(i);
                    temp.WaitForProcessorDeath();
                }
            }
            }
            void MakeSubTree(int level, int numberOfChildren) {
                if(level > 0) {
                    TreeActor child(1);
                    for(int j = 0; j < numberOfChildren; j++) {  
                        child = TreeActor(1);
                        child.ForkAndSpin();
                        if((level - 1) > 0) {
                            child.MakeSubTree(level - 1, numberOfChildren);
                        }
                        children.push_back(child);
                    }
                }
            }
            void SendMessages() {
                cout<<"inside message send "<< children.empty()<< endl;
                Json::Value msg = "I'm a message!";
                for (int i =0; i< children.size(); i++) {
                    CreateSubTree_Factory(children.at(i), 1, msg);
                    children.at(i).SendMessages();
                }
            }

            virtual ~TreeActorImpl() { }
            MESSAGE_HANDLER_DECLARATION(PS3);
    };

    TreeActor::TreeActor(int i) {
        evProc = new TreeActorImpl(1);
    }
    void TreeActor::killChildren() {
        TreeActorImpl* temp = static_cast<TreeActorImpl*>(evProc);
        temp->killChildren();
    }
    void TreeActor::SendMessages() {
        TreeActorImpl* temp = static_cast<TreeActorImpl*>(evProc);
        temp->SendMessages();
    }

    void TreeActor::MakeSubTree(int level, int numberOfChildren) {
        TreeActorImpl* temp = static_cast<TreeActorImpl*>(evProc);
        temp->MakeSubTree(level, numberOfChildren);
    }

    #endif // _ACTOR_H_
