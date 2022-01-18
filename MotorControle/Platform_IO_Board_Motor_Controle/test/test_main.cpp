#include <Arduino.h>
#include <unity.h>
#include "testComm/testComm.h"
#include "Test_Join.h"
#include "Test_StepperJoin.h"
#include "Test_DriveManager.h"
#include "Test_StateManager.h"

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{
    //initialisation
    TestComm test_comm;
    Test_Join test_join;
    Test_StepperJoin test_stepperjoin;
    Test_DriveManager test_drivemanager;
    Test_StateManager test_StateManager;

    //launch all test
    test_comm.test();
    test_join.test();
    test_stepperjoin.test();
    test_drivemanager.test();
    test_StateManager.test();


    UNITY_END(); // stop unit testing
    
}