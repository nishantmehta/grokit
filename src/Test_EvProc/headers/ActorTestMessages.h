
/*
 * Copyright 2015 Tera Insights, LLC. All Rights Reserved.
 *
 * This file has been automatically generated.
 *
 * Source:          Test_EvProc/php/ActorTestMessages.h.php
 * Generated on:    2015-04-17T23:45:06+0000
 *
 * Do not make modifications to this file, they will be wiped out on the next
 * compilation. Please make modifications to the source file instead.
 */
#include "Swap.h"
#include "Message.h"
#include "SerializeJson.h"

#ifndef _ACTOR_TEST_MESSAGES_H_
#define _ACTOR_TEST_MESSAGES_H_


class ResultMessage : public Message {
public:
    // members
    int id;
    Json::Value msg;

private:
    // constructor
    ResultMessage ( int id, Json::Value & msg ) :
        Message()
        // Copy constructed members
        , id( id )
    {
        // swapped members
        (this->msg).swap(msg);
    }

    // Default constructor
    ResultMessage ( void ) : Message() { }


public:
    // Destructor
    virtual ~ResultMessage() {}

    // type
    static constexpr off_t type = 0x3c0ff726d4b28d5eLL;
    virtual off_t Type(void) const OVERRIDE_SPEC { return 0x3c0ff726d4b28d5eLL; }
    virtual const char * TypeName(void) const OVERRIDE_SPEC { return "ResultMessage"; }

    // To/From Json
    virtual void ToJson( Json::Value & dest ) const OVERRIDE_SPEC {
        dest = Json::Value(Json::objectValue);

        ::ToJson(id, dest["id"]);
        ::ToJson(msg, dest["msg"]);
    }

    virtual void FromJson ( const Json::Value & src ) OVERRIDE_SPEC {
        if( ! src.isObject() ) {
            throw new std::invalid_argument("Tried to construct ResultMessage message from non-object JSON");
        }

        if( ! src.isMember("id") )
            throw new std::invalid_argument("JSON for message ResultMessage has no member for attribute id");
        ::FromJson(src["id"], id);
        if( ! src.isMember("msg") )
            throw new std::invalid_argument("JSON for message ResultMessage has no member for attribute msg");
        ::FromJson(src["msg"], msg);
    }


    // Constructor from JSON
    // This constructor has a bizarre signature on purpose as not to conflict
    // with messages that contain exactly 1 JSON value as their payload.
    // It is our hope that no sane individual would store 3 void pointers in a
    // message.
    ResultMessage( const Json::Value & src, void * dummy1, void * dummy2, void * dummy3 ) {
        FromJson(src);
    }

    // friend delcarations
    friend void ResultMessage_Factory( EventProcessor & __dest, int id, Json::Value & msg );

    // Factory function to build a ResultMessage object
    static void Factory( EventProcessor & __dest, int id, Json::Value & msg ) {
        Message * __msg = (Message *) new ResultMessage( id, msg );
        __dest.ProcessMessage(*__msg);
    }

}; // End of class ResultMessage
inline
void ToJson( const ResultMessage & src, Json::Value & dest ) {
    src.ToJson(dest);
}

inline
void FromJson( const Json::Value & src, ResultMessage & dest ) {
    dest.FromJson(src);
}


// Factory function to build ResultMessage objects
inline
void ResultMessage_Factory( EventProcessor & __dest, int id, Json::Value & msg ) {
    Message * __msg = (Message *) new ResultMessage( id, msg );
    __dest.ProcessMessage(*__msg);
}


class CreateSubTree : public Message {
public:
    // members
    int id;
    Json::Value msg;

private:
    // constructor
    CreateSubTree ( int id, Json::Value & msg ) :
        Message()
        // Copy constructed members
        , id( id )
    {
        // swapped members
        (this->msg).swap(msg);
    }

    // Default constructor
    CreateSubTree ( void ) : Message() { }


public:
    // Destructor
    virtual ~CreateSubTree() {}

    // type
    static constexpr off_t type = 0x662f62ef7894ddb3LL;
    virtual off_t Type(void) const OVERRIDE_SPEC { return 0x662f62ef7894ddb3LL; }
    virtual const char * TypeName(void) const OVERRIDE_SPEC { return "CreateSubTree"; }

    // To/From Json
    virtual void ToJson( Json::Value & dest ) const OVERRIDE_SPEC {
        dest = Json::Value(Json::objectValue);

        ::ToJson(id, dest["id"]);
        ::ToJson(msg, dest["msg"]);
    }

    virtual void FromJson ( const Json::Value & src ) OVERRIDE_SPEC {
        if( ! src.isObject() ) {
            throw new std::invalid_argument("Tried to construct CreateSubTree message from non-object JSON");
        }

        if( ! src.isMember("id") )
            throw new std::invalid_argument("JSON for message CreateSubTree has no member for attribute id");
        ::FromJson(src["id"], id);
        if( ! src.isMember("msg") )
            throw new std::invalid_argument("JSON for message CreateSubTree has no member for attribute msg");
        ::FromJson(src["msg"], msg);
    }


    // Constructor from JSON
    // This constructor has a bizarre signature on purpose as not to conflict
    // with messages that contain exactly 1 JSON value as their payload.
    // It is our hope that no sane individual would store 3 void pointers in a
    // message.
    CreateSubTree( const Json::Value & src, void * dummy1, void * dummy2, void * dummy3 ) {
        FromJson(src);
    }

    // friend delcarations
    friend void CreateSubTree_Factory( EventProcessor & __dest, int id, Json::Value & msg );

    // Factory function to build a CreateSubTree object
    static void Factory( EventProcessor & __dest, int id, Json::Value & msg ) {
        Message * __msg = (Message *) new CreateSubTree( id, msg );
        __dest.ProcessMessage(*__msg);
    }

}; // End of class CreateSubTree
inline
void ToJson( const CreateSubTree & src, Json::Value & dest ) {
    src.ToJson(dest);
}

inline
void FromJson( const Json::Value & src, CreateSubTree & dest ) {
    dest.FromJson(src);
}


// Factory function to build CreateSubTree objects
inline
void CreateSubTree_Factory( EventProcessor & __dest, int id, Json::Value & msg ) {
    Message * __msg = (Message *) new CreateSubTree( id, msg );
    __dest.ProcessMessage(*__msg);
}


class SendWorkMsg : public Message {
public:
    // members
    int id;
    Json::Value msg;
    EventProcessor resultProcessor;

private:
    // constructor
    SendWorkMsg ( int id, Json::Value & msg, EventProcessor & resultProcessor ) :
        Message()
        // Copy constructed members
        , id( id )
        , msg( msg )
        , resultProcessor( resultProcessor )
    {
        // swapped members
    }

    // Default constructor
    SendWorkMsg ( void ) : Message() { }


public:
    // Destructor
    virtual ~SendWorkMsg() {}

    // type
    static constexpr off_t type = 0x89cc4b1249b81ffcLL;
    virtual off_t Type(void) const OVERRIDE_SPEC { return 0x89cc4b1249b81ffcLL; }
    virtual const char * TypeName(void) const OVERRIDE_SPEC { return "SendWorkMsg"; }

    // To/From Json
    virtual void ToJson( Json::Value & dest ) const OVERRIDE_SPEC {
        FATAL("Message type SendWorkMsg is not serializable.");
    }

    virtual void FromJson ( const Json::Value & src ) OVERRIDE_SPEC {
        FATAL("Message type SendWorkMsg is not serializable.");
    }

    // Constructor from JSON
    // This constructor has a bizarre signature on purpose as not to conflict
    // with messages that contain exactly 1 JSON value as their payload.
    // It is our hope that no sane individual would store 3 void pointers in a
    // message.
    SendWorkMsg( const Json::Value & src, void * dummy1, void * dummy2, void * dummy3 ) {
        FromJson(src);
    }

    // friend delcarations
    friend void SendWorkMsg_Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & resultProcessor );

    // Factory function to build a SendWorkMsg object
    static void Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & resultProcessor ) {
        Message * __msg = (Message *) new SendWorkMsg( id, msg, resultProcessor );
        __dest.ProcessMessage(*__msg);
    }

}; // End of class SendWorkMsg
inline
void ToJson( const SendWorkMsg & src, Json::Value & dest ) {
    src.ToJson(dest);
}

inline
void FromJson( const Json::Value & src, SendWorkMsg & dest ) {
    dest.FromJson(src);
}


// Factory function to build SendWorkMsg objects
inline
void SendWorkMsg_Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & resultProcessor ) {
    Message * __msg = (Message *) new SendWorkMsg( id, msg, resultProcessor );
    __dest.ProcessMessage(*__msg);
}



class ResultMsg : public Message {
public:
    // members
    int id;
    Json::Value msg;
    EventProcessor worker;

private:
    // constructor
    ResultMsg ( int id, Json::Value & msg, EventProcessor & worker ) :
        Message()
        // Copy constructed members
        , id( id )
        , msg( msg )
    {
        // swapped members
        (this->worker).swap(worker);
    }

    // Default constructor
    ResultMsg ( void ) : Message() { }


public:
    // Destructor
    virtual ~ResultMsg() {}

    // type
    static constexpr off_t type = 0x9f00c49018f41db1LL;
    virtual off_t Type(void) const OVERRIDE_SPEC { return 0x9f00c49018f41db1LL; }
    virtual const char * TypeName(void) const OVERRIDE_SPEC { return "ResultMsg"; }

    // To/From Json
    virtual void ToJson( Json::Value & dest ) const OVERRIDE_SPEC {
        FATAL("Message type ResultMsg is not serializable.");
    }

    virtual void FromJson ( const Json::Value & src ) OVERRIDE_SPEC {
        FATAL("Message type ResultMsg is not serializable.");
    }

    // Constructor from JSON
    // This constructor has a bizarre signature on purpose as not to conflict
    // with messages that contain exactly 1 JSON value as their payload.
    // It is our hope that no sane individual would store 3 void pointers in a
    // message.
    ResultMsg( const Json::Value & src, void * dummy1, void * dummy2, void * dummy3 ) {
        FromJson(src);
    }

    // friend delcarations
    friend void ResultMsg_Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & worker );

    // Factory function to build a ResultMsg object
    static void Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & worker ) {
        Message * __msg = (Message *) new ResultMsg( id, msg, worker );
        __dest.ProcessMessage(*__msg);
    }

}; // End of class ResultMsg
inline
void ToJson( const ResultMsg & src, Json::Value & dest ) {
    src.ToJson(dest);
}

inline
void FromJson( const Json::Value & src, ResultMsg & dest ) {
    dest.FromJson(src);
}


// Factory function to build ResultMsg objects
inline
void ResultMsg_Factory( EventProcessor & __dest, int id, Json::Value & msg, EventProcessor & worker ) {
    Message * __msg = (Message *) new ResultMsg( id, msg, worker );
    __dest.ProcessMessage(*__msg);
}



#endif // _ACTOR_TEST_MESSAGES_H_
