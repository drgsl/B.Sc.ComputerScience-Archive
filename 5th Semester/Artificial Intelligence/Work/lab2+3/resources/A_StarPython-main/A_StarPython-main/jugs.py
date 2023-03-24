# jugs.py
# Andrew Craig, CSE 5120-02
# HW #2

import random
import copy

JUG_START = [0,0] # start state
GOAL = [0,2] # goal state

def jugs_goal_fct(state, goal):
    return state == goal

def jugs_eval_fct(state, goal):
    return 0

def jugs_show_fct(state):
    print (state)
    return

def jugs_successor_fct(jugs):
    nextjugs = [fill3(jugs), fill4(jugs), dump3(jugs), dump4(jugs), pour34(jugs), pour43(jugs)]
    succ = []
    for j in nextjugs:
        if j != None:
            succ.append(j)
        return succ

def fill3(jugs):
    if jugs[0] == 3:
        return None

    newjugs = jugs[:]
    newjugs[0] = 3
    return newjugs

def fill4(jugs):
    if jugs[1] == 4:
        return None

    newjugs = jugs[:]
    newjugs[1] = 4
    return newjugs

def dump3(jugs):
    newjugs = jugs[:]
    newjugs[0] = 0
    return newjugs

def dump4(jugs):
    newjugs = jugs[:]
    newjugs[1] = 0
    return newjugs

def pour34(jugs):
    newjugs = jugs[:]
    if newjugs[0] + newjugs[1] > 4:
        temp = newjugs[0] + newjugs[1]
        newjugs[0] = temp - 4
        newjugs [1] = 4
        return newjugs

    newjugs[1] = newjugs[0] + newjugs[1]
    newjugs[0] = 0
    return newjugs

def pour43(jugs):
    newjugs = jugs[:]
    if newjugs[0] + newjugs[1] > 3:
        temp = newjugs[0] + newjugs[1]
        newjugs[1] = temp - 3
        newjugs[0] = 3
        return newjugs

    newjugs[0] = newjugs[0] + newjugs[1]
    newjugs[1] = 0
    return newjugs
    
    
