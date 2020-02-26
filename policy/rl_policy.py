"""
ppo rl algo
"""

from .algo.ppo import PPO
from tqdm import tqdm


class ppo_agent(object):

    def __init__(self):
        self.ppo = PPO(rnd=0,dim_obs=None, dim_act=None,
                                        policy_fn=None, value_fn=None,
                                        discount=0.99, gae=0.95, clip_ratio=0.2,
                                        train_epoch=40, policy_lr=1e-3, value_lr=1e-3,
                                        save_path="./log", log_freq=10, save_model_freq=100)

    def reset(self, size):
        self.actions = set(list(range(size**2)))
        self.actions_ind = [True] * (size**2)

    def get_action(self, obs, forbidden_actions):
        """
        sample action  
        """
        action =  self.actions
        self.actions.difference_update(set(forbidden_actions))
        diff = action.difference(self.actions)
        self.actions_ind [diff] = False
        # 这里希望return action probs
        action_prob = self.ppo.get_action(obs)
        action = np.argmax(action_prob[self.actions_ind])

        return action