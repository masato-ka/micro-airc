#include "interface/agent/agent.h"
#include "interface/parts/motor_driver.h"
#include "interface/parts/range_sensor.h"
#include "pid_agent_impl.h"
#include "remote_agent_impl.h"
#include "nn_agent_impl.h"
#include "range_sensor_impl.h"
#include "drv8835_impl.h"


#ifndef PID_AGENT_FACTORU_IMPL
#define PID_AGENT_FACTORU_IMPL

namespace airc{

class AgentFactory{
public:
    Agent* create(const char* agent_name);
};

}

#endif