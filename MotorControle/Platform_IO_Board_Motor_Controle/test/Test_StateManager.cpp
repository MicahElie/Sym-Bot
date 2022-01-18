#include <unity.h> 
#include "Test_StateManager.h"
#include "StateManager.h"
#include "TestJoinDevice.h"

#include "Comm/SerialComm.h"
#include "Comm/ControlMessage.h"
#include "Comm/MessageIO.h"
#include "testComm/TestCommDevice2.h"

void Test_StateManager::test()
{
    RUN_TEST(test_updateState);
    RUN_TEST(test_callGoToHome);
    RUN_TEST(test_goTo);
    RUN_TEST(test_callibrateDrive);

}

//faire ce test la en dernier, ca ce test sert a valider que l,ensemble du test fonctionne
void Test_StateManager::test_callibrateDrive()
{
    TEST_ASSERT_EQUAL(1,1);
}

void Test_StateManager::test_goTo()
{
    StateManager* stateManager;
    DriveManager* driveManager;
    TestJoinDevice* testJoinDevice1 = new TestJoinDevice(0,228100,0,0,0);
    driveManager = new DriveManager;
    driveManager->addJoin(testJoinDevice1);
    stateManager = new StateManager(driveManager);

    MessageIO msgIO1;
    TestCommDevice2 device1;
    msgIO1.addDevice(&device1);

    int data1[] = {15041};
    ControlMessage msg(7,1,data1);
    msgIO1.sendMessage(0,msg);
    ControlMessage* Cmsg1 = msgIO1.readMessage(0);
    stateManager->updateState(Cmsg1);
    TEST_ASSERT_EQUAL(15041,testJoinDevice1->getPosition());
}


void Test_StateManager::test_callGoToHome()
{
    StateManager* stateManager;
    DriveManager* driveManager;
    TestJoinDevice* testJoinDevice1 = new TestJoinDevice(0,228100,54,0,0);
    driveManager = new DriveManager;
    driveManager->addJoin(testJoinDevice1);
    stateManager = new StateManager(driveManager);

    stateManager->callGoToHome();
    TEST_ASSERT_EQUAL(54,testJoinDevice1->getPosition());

}


void Test_StateManager::test_updateState()
{
    StateManager* stateManager;
    DriveManager* driveManager;
    TestJoinDevice* testJoinDevice1 = new TestJoinDevice(0,228100,-540,0,0);
    driveManager = new DriveManager;
    driveManager->addJoin(testJoinDevice1);
    stateManager = new StateManager(driveManager);

    MessageIO msgIO1;
    TestCommDevice2 device1;
    msgIO1.addDevice(&device1);

    //test with type = 7
    int data7[] = {-8401};
    ControlMessage msg7(7,1,data7);
    msgIO1.sendMessage(0,msg7);
    ControlMessage* Cmsg7 = msgIO1.readMessage(0);
    stateManager->updateState(Cmsg7);
    TEST_ASSERT_EQUAL(-8401,testJoinDevice1->getPosition());

    //test with type = 9
    int data9[] = {101};
    ControlMessage msg9(9,1,data9);
    msgIO1.sendMessage(0,msg9);
    ControlMessage* Cmsg9 = msgIO1.readMessage(0);
    stateManager->updateState(Cmsg9);
    TEST_ASSERT_EQUAL(-540,testJoinDevice1->getPosition());
}


