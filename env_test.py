from env_wrapper import wzq_env
from policy.rand_policy import rand_agent
import time
agent0 = rand_agent(size=15)
agent1 = rand_agent(size=15)
env = wzq_env([agent0, agent1])

env.run(10000)

