import random
import time
from enum import Enum
import gymnasium as gym
import numpy as np
import matplotlib.pyplot as plt

LINES = 4
COLUMNS = 12
ACTIONS = 4
LEARNING_RATE = 0.1
DISCOUNT = 0.95
EPOCHS = 1000

states = LINES * COLUMNS  # Start/Nothing/Cliff/End
q_table = list(list(0 for i in range(ACTIONS)) for j in range(states))

# #########################
# State      #  UP  #  LEFT #  DOWN  #  RIGHT #
# ##########################################
# 0  (0,0)   #  0   #   0   #   0    #    0   #
# 1  (0,1)   #  0   #   0   #   0    #    0   #
# 2  (0,2)   #  0   #   0   #   0    #    0   #
# ...........................................
# 47 (3, 11) #  0   #   0   #   0    #    0   #
# ##########################################

env = gym.make('CliffWalking-v0')
env.reset()


def get_next_action(a_state, an_action):
    if a_state not in range(0, 38):
        raise ValueError(f"STATE NOT IN RANGE 0 38 {a_state}")
    match action:
        case 0:  # up
            a_state -= 12
        case 1:  # left
            a_state -= 1
        case 2:  # down
            a_state += 12
        case 3:  # right
            a_state += 1
        case _:
            raise ValueError("action is not 0-3")

    return a_state


state = env.reset()[0]  # value of the initial state
steps = 1
done_perfectly = 0

start_time = time.process_time()
# for stats
x = []
y = []
# ####
for i in range(EPOCHS):
    done = False
    state = env.reset()[0]
    # print(f"EPOCH: {i}")
    # for stats
    steps = 0
    rewards = []
    # ##########
    while not done:
        action = np.argmax(q_table[state])

        new_state, reward, done, _, _ = env.step(action)
       # print(f"NEW_STATE = {new_state} OLD_STATE = {state}")

        env.render()
        rewards.append(reward)

        if not done:
            # print(f"POSSIBLE Q'S: {q_table[new_state]}")
            max_future_q = np.max(q_table[new_state])
            # g_n_a = get_next_action(state, action) only in env we stepped on, so we can do this
            g_n_a = new_state
            current_q = q_table[g_n_a][action]
            new_q = (1 - LEARNING_RATE) * current_q + LEARNING_RATE * (reward + DISCOUNT * max_future_q)
            #  print(f"NEW_Q {new_q}")
            q_table[state][action] = new_q
            # if it goes off
            if new_state in range(36, 47):
                state = env.reset()[0]
                break
        elif new_state == 47:  # final state
            if steps == 14:
                done_perfectly += 1
            q_table[state][action] = 100
            print(f"HOORAY!!!! STEPS: {steps}")
            break

        steps += 1
        state = new_state
    # for stats
    time_elapsed = time.process_time()
    avg_reward = sum(rewards)/len(rewards)
    print(f"Avg_reward for this epoch: {avg_reward}")
    x.append(time_elapsed)
    y.append(avg_reward)

    if i == EPOCHS - 1:
        print("DONE")
    ######

plt.plot(x, y)
plt.show()
print("ACCURACY: ", done_perfectly / EPOCHS)