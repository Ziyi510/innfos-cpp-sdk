/*
*使能单个执行器
*/

#include <iostream>
#include "actuatorcontroller.h"
#include <thread>
#include <signal.h>
#include <string.h>
#include <chrono>
using namespace std;


int main(int argc, char *argv[])
{
    //Initialize the controller
    ActuatorController * pController = ActuatorController::initController();
    //ec Define an error type, ec==0x00 means no error, ec will be passed to pcontroller-> lookupActuators(ec) by reference,
    //when the error occurs, ec value will be modified by SDK to the corresponding error code
    Actuator::ErrorsDefine ec;
    //Find the connected actuators.
    // pController->lookupActuators(ec);
    //Gets an array of all actuator IDs
    // vector<uint8_t> idArray = pController->getActuatorIdArray();
    //Find the connected actuators and return the UnifiedID of all actuators found.
    std::vector<ActuatorController::UnifiedID> uIDArray = pController->lookupActuators(ec);
    //If the size of the idArray is greater than zero, the connected actuators have been found
    if(uIDArray.size() > 0)
    {
        //Enable an actuator
        // if(pController->enableActuator(idArray.at(0)))
        // {
        //     cout << "Enable actuator " << (int)idArray.at(0) << " successfully!" << endl;
        // }
        //Disable an actuator
        // pController->disableActuator(idArray.at(0));
        pController->disableAllActuators();
        cout << "All actuators have been disabled successfully! " << endl;
        //insure that the actuator has been closed
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    else
    {
        //ec=0x803 Communication with ECB(ECU) failed
        //ec=0x802 Communication with actuator failed
        cout << "Connected error code:" << hex << ec << endl;
    }

    return 0;
}
