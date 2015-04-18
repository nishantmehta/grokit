<?php

// Copyright 2013 Tera Insights, LLC. All Rights Reserved.

require_once('MessagesFunctions.php');

?>

#ifndef _ACTOR_TEST_MESSAGES_H_
#define _ACTOR_TEST_MESSAGES_H_

<?php
grokit\create_message_type( 'ResultMessage', [ 'id' => 'int' ], [ 'msg' => 'Json::Value' ], true );
?>
<?php
grokit\create_message_type( 'CreateSubTree', [ 'id' => 'int' ], [ 'msg' => 'Json::Value' ], true );
?>
<?
grokit\create_message_type(
    'SendWorkMsg',
    [  'id' => 'int', 'msg' => 'Json::Value' , 'resultProcessor' => 'EventProcessor' ],
    [ ]
);
?>

<?
grokit\create_message_type(
    'ResultMsg',
    [  'id' => 'int', 'msg' => 'Json::Value' ],
    [ 'worker' => 'EventProcessor' ]
);
?>


#endif // _ACTOR_TEST_MESSAGES_H_
