'''
Developer: Dennis Dao
Date: Feb 2, 2022
Student #: 110010116

Hill-climbing implementation for the Iterated Prisoner's Dilemma
Background info:
* 2 prisoners are in jail, they cannot communicate with each other
* The police propose the following to each:
    Betray your partner in crime and you go free
* If both prisoners cooperate with each other, both get charged 1 year
* If one defects, the defector goes free while the accused gets 20 years
* If both cooperate with the police, they each get 10 years

* The rational reasoning - don't defect, I potentially get 20 years
                         - defect, I potentially get 10 years
'''

import random

# Randomly generate a solution to the problem
# In this case, a random selection of when to defect and cooperate
def randomSolution(dilemma):

    mainSol = []

    for k in range(len(dilemma)):
        choices = list(range(len(dilemma[k])))
        solution = []
        for i in range(len(dilemma[k])):
            # Randomly pick a strategy to iteration i
            randomStrat = choices[random.randint(0, len(choices)-1)]
            solution.append(dilemma[k][randomStrat])
            choices.remove(randomStrat)
        mainSol.append(solution)

    return mainSol

def calculateScore(dilemma, solution):
    score1 = 0
    score2 = 0

    # Target is to have the minimum amount of years in jail
    # Getting the minimum sentence will maximize a prisoner's score
    for j in range(len(dilemma[0])):
        # Both will be in jail for the min if they cooperate with each other
        if solution[0][j] == 'C' and solution[1][j] == 'C':
            score1 -= 1
            score2 -= 1
        # Prisoner 2 cooperates, Prisoner 2 defects
        elif solution[0][j] == 'C' and solution[1][j] == 'D':
            score1 -= 20
            score2 -= 0
        # Prisoner 1 confesses, Prisoner 1 defects
        elif solution[0][j] == 'D' and solution[1][j] == 'C':
            score1 -= 0
            score2 -= 20
        # Both confess, resulting in a moderate sentence
        elif solution[0][j] == 'D' and solution[1][j] == 'D':
            score1 -= 10
            score2 -= 10
    return score1, score2


def getNeighbours(solution):
    neighbours = []
    neighbourPair = []

    # Neighbours are current solutions with decisions swapped
    for i in range(len(solution[0])):
        for j in range(i+1, len(solution[0])):
            for k in range(2):
                neighbour = solution[k].copy()
                neighbour[i] = solution[k][j]
                neighbour[j] = solution[k][i]
                neighbours.append(neighbour)
    return neighbours

# Get best strategy (neighbour)
def getBestStrategy(dilemma, neighbours):
    bestNeighbour = []
    bestNeighbour.append(neighbours[0])
    bestNeighbour.append(neighbours[1])
    bestScores = calculateScore(dilemma, bestNeighbour)

    # To ensure items are grabbed in pairs
    # even indices = prisoner1, odd indices = prisoner2
    for i in range(0,len(neighbours)//2,2):
        strat = []
        strat.append(neighbours[2*i])
        strat.append(neighbours[2*i+1])
        currentScore = calculateScore(dilemma, strat)

        if currentScore > bestScores:
            bestNeighbour = strat
            bestScore = currentScore
            
    return bestNeighbour, bestScores

# Core of hill climbing
def hillClimbing(dilemma):
    # Create a random solution and get the score
    currentSolution = randomSolution(dilemma)
    currentScore = calculateScore(dilemma, currentSolution)
    
    # Create neighbours and find the best one
    neighbours = getNeighbours(currentSolution)
    bestNeighbour, bestNeighbourhoodScore = getBestStrategy(dilemma, neighbours)

    # Repeat above process
    while bestNeighbourhoodScore < currentScore:
        currentSolution = bestNeighbour
        currentScore = bestNeighbourhoodScore
        neighbours = getNeighbours(currentSolution)
        bestNeighbour, bestNeighbourhoodScore = getBestStrategy(dilemma, neighbours)
 
    return currentSolution, currentScore

# Generate prisoner problems of size iterations (# of times the dilemma is repeated
def problemGenerator(iterations):
    dilemma = []
    strat = []

    # C = cooperate with fellow prisoner, D = defect
    for i in range(2):
        for i in range(iterations):
            # Could switch this parameter - currently, equally likely to
            # defect or cooperate
            # 50% = moderate amount of years often
            # 75% = low amount of years often
            # 25% = high amount of years often
            if random.randint(0,100) < 75:
                strat.append('C')
            else:
                strat.append('D')
        dilemma.append(strat)
        strat = []
    return dilemma

# A solution where the prisoner always cooperates
def generateAllCooperate(iterations):
    strat = []
    for i in range(iterations):
        strat.append('C')
    return strat

# A solution where the prisoner always defect
def generateAllDefect(iterations):
    strat = []
    for i in range(iterations):
        strat.append('D')
    return strat

# Generate based on titForTat
def titForTat(prisoner2):
    strat = []
    strat.append('C')

    for i in range(1, len(prisoner2[0])):
        if(prisoner2[0][i-1] == 'D'):
            strat.append('D')
        else:
            strat.append('C')
    return strat

# Generate based on titFor2at
def titFor2Tat(prisoner2):
    strat = []
    strat.append('C')
    strat.append('C')

    for i in range(2, len(prisoner2[0])):
        if(prisoner2[0][i-1] == 'D' and prisoner2[0][i-2] == 'D'):
            strat.append('D')
        else:
            strat.append('C')
    return strat

def main():
    dilemma = problemGenerator(10)
    print("Given the dilemma:")
    print(dilemma, calculateScore(dilemma,dilemma))

    # RANDOMLY GENERTED
    print("\nPrisoner's dilemma where it is equally likely for a prisoner to choose to defect/cooperate")
    print("30 iterations of completely randomly generated")
    for i in range(30):
        print(hillClimbing(dilemma))

    # HUMAN STRATEGIES
    print("\nHuman strategies to the prisoner's dilemma in hill-climbing")
    dilemma = []
    # Full cooperation
    print("All cooperate")
    for i in range(2):
        allCooperate = generateAllCooperate(10)
        dilemma.append(allCooperate)
    print(hillClimbing(dilemma))
    print("Compared with regular:")
    print(dilemma, calculateScore(dilemma, dilemma))

    # Full defection
    dilemma = []
    print("\nAll defect")
    for i in range(2):
        allDefect = generateAllDefect(10)
        dilemma.append(allDefect)
    print(hillClimbing(dilemma))
    print("Compared with regular:")
    print(dilemma, calculateScore(dilemma, dilemma))

    # One defects, one cooperates
    dilemma = []
    print("\nOne always defects, one always cooperates")
    dilemma.append(generateAllDefect(10))
    dilemma.append(generateAllCooperate(10))
    print(hillClimbing(dilemma))
    print("Compared with regular:")
    print(dilemma, calculateScore(dilemma, dilemma))

    # Tit-for-tat
    dilemma = []
    print("\nTit-for-tat")
    dilemma.append(['D', 'D', 'C', 'C', 'C', 'C', 'C', 'D', 'D', 'C'])
    dilemma.append(titForTat(dilemma))
    dilemma.reverse()
    for i in range(20):
        print(hillClimbing(dilemma))
    print("Compared with regular tit-for-tat:")
    print(dilemma, calculateScore(dilemma, dilemma))

    # Tit-for-2Tat
    dilemma = []
    print("\nTit-for-2tat")
    dilemma.append(['D', 'D', 'C', 'C', 'C', 'C', 'C', 'D', 'D', 'C'])
    dilemma.append(titFor2Tat(dilemma))
    dilemma.reverse()
    for i in range(20):
        print(hillClimbing(dilemma))
    print("Compared with regular tit-for-2tat:")
    print(dilemma, calculateScore(dilemma, dilemma))

if __name__ == "__main__":
    main()
