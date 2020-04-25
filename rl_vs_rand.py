from env_wrapper import wzq_env
from policy.rand_policy import rand_agent
from policy.algo.ppo import PPO
from policy.net.net_v0 import policy_net
from policy.net.net_v0 import value_net
from policy.rl_policy import ppo_agent
import time
import numpy as np

agent0 = ppo_agent(size=15)
agent1 = rand_agent(size=15)
env = wzq_env([agent0, agent1])
env.run()