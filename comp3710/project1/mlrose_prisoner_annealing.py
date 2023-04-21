'''
Developer: Dennis Dao
Feb 10, 2023
110010116
'''

import six
import sys
sys.modules['sklearn.externals.six'] = six
import mlrose
import numpy as np
import random
import matplotlib.pyplot as plt

def prisonerDilemma(state):
    # Intialize counter
    fitness_cnt = 0
    opponentSetup = []

    # Try generated strategy on a randomized opponent
    for i in range(len(state)):
        opponentSetup.append(random.randint(0,1))
    
    opponent = np.array(opponentSetup)

    # Good fitness if both cooperate with each other
    for i in range(len(state)-1):
        if(state[i] == 0 and state[i] == opponent[i]):
            fitness_cnt +=1
    return fitness_cnt

'''
def prisonerDilemma(state):
    # Intialize counter
    fitness_cnt = 0
    opponentSetup = []

    # Try generated strategy on a randomized opponent
    for i in range(len(state)):
        opponentSetup.append(random.randint(0,1))
    
    opponent = np.array(opponentSetup)

    # Good fitness if no defect-cooperate/cooperate-defect occurs
    for i in range(len(state)-1):
        
        Equivalent to state being 0 or 1 AND that the opponent did the same on iteration i - good fitness
        
        if((state[i] == 0 or state[i] == 1) and state[i] == opponent[i]):
            fitness_cnt +=1
    return fitness_cnt
'''

# Calculate player score against opponent
def calculateJailTime(player, opponent):
    playerJailTime = 0
    opponentJailTime = 0
    # Use + to avoid confusion while graphing
    for i in range(len(player)):
        if(player[i] == opponent[i] and player[i] == 0):
            playerJailTime += 1
            opponentJailTime += 1
        elif(player[i] == opponent[i] and player[i] == 1):
            playerJailTime += 10
            opponentJailTime += 10
        elif(player[i] == 0 and opponent[i] == 1):
            playerJailTime += 20
            opponentJailTime += 0
        elif(player[i] == 1 and opponent[i] == 0):
            playerJailTime += 0
            opponentJailTime += 20
    return playerJailTime, opponentJailTime

# Test against human strategies
def testHumanStrategies(original, player, playerLen):
    #TFT
    # Comment out optScore and oriScore for all human strategies not interested
    # in graphing. (ie. interested in TFT, comment out all optScore and oriScore
    # EXCEPT for the one in the TFT section)
    opponent = []

    opponent.append(0)
    for i in range(1, playerLen):
        if(player[i-1] == 1):
            opponent.append(1);
        else:
            opponent.append(0)

    print("\nHUMAN STRATEGY 1 - TFT")
    print(opponent)
    optScore = calculateJailTime(player, opponent)
    print(optScore)
    for i in range(1, playerLen):
        if(original[i-1] == 1):
            opponent.append(1);
        else:
            opponent.append(0)
    oriScore = calculateJailTime(original, opponent)
    print("WITHOUT SIMULATED ANNEALING:", oriScore)

    #TF2T
    opponent = []

    opponent.append(0)
    opponent.append(0)
    for i in range(2, playerLen):
        if(player[i-1] == 1 and player[i-1] == player[i-2]):
            opponent.append(1);
        else:
            opponent.append(0)

    print("\nHUMAN STRATEGY 2 - TF2T")
    print(opponent)
    optScore = calculateJailTime(player, opponent)
    print(optScore)
    for i in range(2, playerLen):
        if(player[i-1] == 1 and player[i-1] == player[i-2]):
            opponent.append(1);
        else:
            opponent.append(0)
    oriScore = calculateJailTime(original, opponent)
    print("WITHOUT SIMULATED ANNEALING:", oriScore)

    #ALL-C
    opponent = []
    for i in range(playerLen):
        opponent.append(0)

    print("\nHUMAN STRATEGY 3 - ALL-COOPERATE")
    print(opponent)
    optScore = calculateJailTime(player, opponent)
    print(optScore)
    oriScore = calculateJailTime(original, opponent)
    print("WITHOUT SIMULATED ANNEALING:", oriScore)

    #ALL-D
    opponent = []
    for i in range(playerLen):
        opponent.append(1)
        
    print("\nHUMAN STRATEGY 4 - ALL-DEFECT")
    print(opponent)
    optScore = calculateJailTime(player, opponent)
    print(optScore)
    oriScore = calculateJailTime(original, opponent)
    print("WITHOUT SIMULATED ANNEALING:", oriScore)

    #RAND
    opponent = []
    for i in range(playerLen):
        opponent.append(random.randint(0,1))

    print("\nHUMAN STRATEGY 5 - ALL-RANDOM")
    print(opponent)
    optScore = calculateJailTime(player, opponent)
    print(optScore)
    oriScore = calculateJailTime(original, opponent)
    print("WITHOUT SIMULATED ANNEALING:", oriScore)

    return optScore[0], oriScore[0], optScore[1], oriScore[1]

fitness_cst = mlrose.CustomFitness(prisonerDilemma)
# In terms of the prisoner's dilemma, maybe try to minimize the amount of years in jail somehow
problem = mlrose.DiscreteOpt(length = 10, fitness_fn = fitness_cst,\
                             maximize = True, max_val = 2)


# Let 0 be cooperate, let be 1 be defect (mlrose doesn't accept 'C' or 'D' characters)
player = []
playerLen = 10
# Should correspond to the number of experiments
xAxis = [1,2,3,4,5,6, 7, 8, 9, 10]
yOpt1 = []
yOri1 = []
yOpt2 = []
yOri2 = []

for i in range(playerLen):
    player.append(random.randint(0,1))
# Comment out to switch between a static player and a random player
'''
player = [0, 1, 0, 0, 0, 0, 0, 0, 1, 0]
'''
print("Given the player:", player, "\n")
init_state = np.array(player)

# Solve the prisoner's dilemma with simulated annealing
# Receive the fitness score of the strategy and the optimized(?) strategy
schedule = mlrose.ExpDecay()
best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                        max_attempts = 100, max_iters = 1000,\
                                                        init_state = init_state, random_state = 1)
print('SIMULATED ANNEALING SOLUTION 1: 100 attempts, 1000 iterations,\nexpontential decay, random state 1')
print("The best calculated state is", best_state, " with fitness", best_fitness)
results = testHumanStrategies(player, best_state, len(best_state))

schedule = mlrose.ExpDecay()
best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                      max_attempts = 1000, max_iters = 1000,\
                                                      init_state = init_state, random_state = 1)

print('\nSIMULATED ANNEALING SOLUTION 2: 1000 attempts, 1000 iterations,\nexpontential decay, random state 1')
print("The best calculated state is", best_state, " with fitness", best_fitness)
testHumanStrategies(player, best_state, len(best_state))

# Add this for loop, results, and y-variables to test case of interest to graph
for i in range(10):
    schedule = mlrose.ArithDecay()
    best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                          max_attempts = 100, max_iters = 1000,\
                                                          init_state = init_state, random_state = 3)
    print('\nSIMULATED ANNEALING SOLUTION 3: 100 attempts, 1000 iterations,\narithmetic decay, random state 3')
    print("The best calculated state is", best_state, " with fitness", best_fitness)
    results = testHumanStrategies(player, best_state, len(best_state))
    yOpt1.append(results[0])
    yOri1.append(results[1])
    yOpt2.append(results[2])
    yOri2.append(results[3])

schedule = mlrose.ArithDecay()
best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                      max_attempts = 1000, max_iters = 1000,\
                                                      init_state = init_state, random_state = 3)
print('\nSIMULATED ANNEALING SOLUTION 4: 1000 attempts, 1000 iterations,\narithmetic decay, random state 3')
print("The best calculated state is", best_state, " with fitness", best_fitness)
testHumanStrategies(player, best_state, len(best_state))

# Careful with iterations and attempts here, has thrown Overflow errors
schedule = mlrose.GeomDecay()
best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                        max_attempts = 100, max_iters = 100,\
                                                        init_state = init_state, random_state = 5)
print('\nSIMULATED ANNEALING SOLUTION 5: 100 attempts, 100 iterations,\ngeometric decay, random state 5')
print("The best calculated state is", best_state, " with fitness", best_fitness)
testHumanStrategies(player, best_state, len(best_state))


schedule = mlrose.GeomDecay()
best_state, best_fitness = mlrose.simulated_annealing(problem, schedule = schedule,\
                                                      max_attempts = 100, max_iters = 1000,\
                                                      init_state = init_state, random_state = 5)
print('\nSIMULATED ANNEALING SOLUTION 6: 100 attempts, 1000 iterations,\ngeometric decay, random state 5')
print("The best calculated state is", best_state, " with fitness", best_fitness)
testHumanStrategies(player, best_state, len(best_state))

# Graph plotting
plt.plot(xAxis, yOpt1, label = "P1 Score: SA vs. RAND")
plt.plot(xAxis, yOri1, label = "P1 Score: original vs. RAND")
plt.plot(xAxis, yOpt2, label = "P2 Score: SA vs. RAND")
plt.plot(xAxis, yOri2, label = "P2 Score: original vs. RAND")
plt.xlabel('Iteration Number')
plt.ylabel('Prisoner Jail Time')
plt.title("Simulated Annealing: 100 attempts, 1000 iterations, arith decay")
plt.legend()
plt.show()

