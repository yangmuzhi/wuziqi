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


## TODO
- [x] Env python  wrapper  
- [x] feature engineer
- [ ] reinforcement learning algo 

## notes
- 

## Feature Description

When player0 actions, then update player0 and player1 feature. generally, player0 step then player1 get_feature

| Serial number | name | description | done |
| :------| :------ | :------ |
| 0 | who | size*size full 0 or 1， present first 1 or second 0| ok | 
| 1 | the player's  current map | current chess | ok | 
| 2 | the player's  former-1 map | former-1 chess | ok | 
| 3 | the player's  former-2 map | former current-2 chess | ok | 
| 4 | the player's  former-3 map | former-3 chess | ok | 
| 5 | the player's  former-4 map | former-4 chess | ok | 
| 6 | the opposite player's  current map | current chess | ok | 
| 7 | the opposite player's  former-1 map | former-1 chess | ok | 
| 8 | the opposite player's  former-2 map | former current-2 chess | ok | 
| 9 | the opposite player's  former-3 map | former-3 chess | ok | 
| 10 | the opposite player's  former-4 map | former-4 chess | ok | 
| 11 | used place | comb player and opposite player current | ok|

- 深搜 连起来的点， 3、4个以上.一步一步更新的深搜

