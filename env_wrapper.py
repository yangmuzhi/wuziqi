from game import kernel
import numpy as np
from tqdm import tqdm


# agents list, agent.get_action
# action -> row col
# 被禁止的action

class wzq_env:

    def __init__(self, agents, size=15, update_fq=10):
        self.kernel = kernel()
        self.a0 = agents[0]
        self.a1 = agents[1]
        self.size = size
        self._prepare()
        self.flag = True
        self.update_fq = update_fq

        self._forbidden_actions = []

    def reset(self):
        # todo load his map
        self._forbidden_actions.clear()
        self.a0.reset(self.size)
        self.a1.reset(self.size)
        self.kernel.reset()
        return self.kernel.get_feature(self.flag), False, False
    
    def step(self, action):
        # action -> row, col
        self.flag = ! self.flag
        assert not action in self._forbidden_actions, "forbidden action"
        self._forbidden_actions.append(action)
        row, col = self.dict.get(action)
        is_win, is_dead = self.kernel.step(row, col)
        return self.kernel.get_feature(self.flag), is_win, is_dead

    def _prepare(self):
        self.dict = {i:(i // self.size, i % self.size) for i in range(self.size**2)}

    def run(self, e=10000):
        e = tqdm(range(e))
        #databatch：一个列表，分别是state, action, reward, done, early_stop, next_state。每个是矩阵或向量。
        databatch = []
        state
        for i in e:
            obs = self.reset()
            while True:
                a0 = self.a0.get_action(obs, self._forbidden_actions)
                obs, is_win, is_dead = self.step(a0)
                # print(a0)
                if is_win or is_dead:
                    break
                a1 = self.a1.get_action(obs, self._forbidden_actions)
                obs, is_win, is_dead = self.step(a1)
                self.obs = obs
                # print(a1)
                if is_win or is_dead:
                    if i % self.update_fq ==0 :
                        self.a0.update(databatch)
                        self.a1.update(databatch)
                        databatch.clear()
                        break