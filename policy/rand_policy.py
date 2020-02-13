"""
rand policy
"""
import random

class rand_agent:

    def __init__(self, size):
        self.reset(size)
    
    def reset(self, size):
        self.actions = set(list(range(size**2)))

    def get_action(self, obs, forbidden_actions):
        self.actions.difference_update(set(forbidden_actions))
        return random.choice(list(self.actions))