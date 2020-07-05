#include <Arduino.h>
#include "include/interface/agent/agent.h"
#include "include/agent_factory_impl.h"

airc::Agent* agent = nullptr;

void setup() {
  Serial.begin(115200);
  Serial.println("Initialize");
  String agent_name = airc::AGENT_NAME;
  airc::AgentFactory* factory = new airc::AgentFactory();
  agent = factory->create(agent_name.c_str());
}

void loop() {
  agent->drive();
}
