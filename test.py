from env_wrapper import wzq_env
from policy.rand_policy import rand_agent

size = 15
a0 = rand_agent(size)
a1 = rand_agent(size)

wrapper = wzq_env([a0, a1], size=size)
wrapper.run(100)
