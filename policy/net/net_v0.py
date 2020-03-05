"""
cnn
"""

import tensorflow as tf

def policy_net(obs):

    x = tf.layers.Conv2D(filters=256, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(obs)
    x = tf.layers.Conv2D(filters=256, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(4,4), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(4,4), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=64, kernel_size=(3,3), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=64, kernel_size=(3,3), padding="same", use_bias=True, data_format="channels_first")(x)

    x = tf.layers.flatten(x)
    x = tf.layers.Dense(256, activation=tf.nn.relu)(x)
    pi = tf.layers.Dense(15*15, activation=tf.nn.sigmoid)(x)
    log_p = tf.log(pi)
    return pi, log_p 


def value_net(obs):

    x = tf.layers.Conv2D(filters=256, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(obs)
    x = tf.layers.Conv2D(filters=256, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(5,5), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(4,4), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=128, kernel_size=(4,4), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=64, kernel_size=(3,3), padding="same", use_bias=True, data_format="channels_first")(x)
    x = tf.layers.Conv2D(filters=64, kernel_size=(3,3), padding="same", use_bias=True, data_format="channels_first")(x)

    x = tf.layers.flatten(x)
    x = tf.layers.Dense(256, activation=tf.nn.relu)(x)
    out = tf.layers.Dense(1, activation=tf.nn.sigmoid)(x)
    return out


