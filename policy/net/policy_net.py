"""
cnn
"""

import tensorflow as tf

def policy_net(obs_shape, out_shape):
    obs = tf.placeholder(shape=*obs_shape, dtype=tf.float32, name="obs")
    out = tf.placeholder(shape=out_shape, dtype=tf.float32, name="actions prob")

    x = tf.layers.Conv2D(obs, filters=256, kernel_size=(5,5), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=256, kernel_size=(5,5), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=128, kernel_size=(5,5), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=128, kernel_size=(4,4), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=128, kernel_size=(4,4), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=64, kernel_size=(3,3), padding="same", use_bias=True)
    x = tf.layers.Conv2D(x, filters=64, kernel_size=(3,3), padding="same", use_bias=True)

    x = tf.layers.Dense(x, 256, activation=tf.nn.relu)
    out = tf.layers.Dense(x, out_shape, activation=tf.nn.sigmoid)
    return out

