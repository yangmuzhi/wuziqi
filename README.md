## wuziqi enviroment for AI algos

- wuziqi/ 五子棋
- c++, cython
- gym style
- two random policy 1059.15it/s

## usage
```
# build env

python setup.py build_ext --inplace

```


## todo
- [x] Env python  wrapper  
- [ ] feature engineer
- [ ] reinforcement learning algo 


## Feature Description
| Serial number | name | description |
| :------| :------ | :------ |
| 0 | who | size*size full 0 or 1， present first 1 or second 0|
| 1 | the player's  map |  |
| 2 | the opposite player's  map |  |
| 3 | the player's  map |  |
| 1 | the player's  map |  |
