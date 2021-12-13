from random import random, shuffle, randrange

city_map = {
    1: {2: 1,
        3: 2,
        4: 7,
        5: 5},
    2: {1: 1,
        3: 4,
        4: 4,
        5: 3},
    3: {1: 2,
        2: 4,
        4: 1,
        5: 2},
    4: {1: 7,
        2: 4,
        3: 1,
        5: 3},
    5: {1: 5,
        2: 3,
        3: 2,
        4: 3}
}
default_path = ['1', '2', '3', '4', '5']
mutation_chance = 0.01
pop_size = 4
epochs = 4


def calculate_sum(unit):
    temp_sum = 0
    for j in range(len(unit)):
        from_ = int(unit[j])
        if j == len(unit) - 1:
            to_ = int(unit[0])
            temp_sum += city_map[from_][to_]
        else:
            to_ = int(unit[j+1])
        temp_sum += city_map[from_][to_]
    return temp_sum


def pretty_print(population):
    order = 1
    print("No.        Traversal    Fitness")
    for (i, j) in enumerate(population[0]):
        print(f"{order}          {j}        {population[1][i]}")
        order += 1


def generate_population():
    result = ([], [])
    while len(result[0]) < pop_size:
        temp = default_path.copy()
        shuffle(temp)
        key = ''.join(temp)
        if not(key in result[0]):
            result[0].append(key)
            result[1].append(calculate_sum(key))
    return result


def crossover(population):
    paths = population[0]
    for i in range(len(paths) // 2):
        parents = [paths[randrange(0, len(paths)-1)]] * 2
        while parents[0] == parents[1]:
            parents[1] = paths[randrange(0, len(paths)-1)]
        rip1 = randrange(0, len(parents[0])-1)
        rip2 = randrange(0, len(parents[0])-1)
        for i in range(2):
            child = ['*'] * len(parents[0])
            for j in range(min(rip1, rip2), max(rip1, rip2)):
                child[j] = parents[-(i+1)][j]
            for j in parents[i][:: -1]:
                if j not in child:
                    child[child.index('*')] = j
            child = ''.join(child)
            population[0].append(child)
            population[1].append(calculate_sum(child))
    return population


def mutation(population):
    for (i, j) in enumerate(population[0]):
        if random() < mutation_chance:
            print(f"{j} mutated!", end=' ')
            limit = len(j)
            a = randrange(0, limit)
            b = randrange(0, limit)
            mutable = list(j)
            mutable[a], mutable[b] = mutable[b], mutable[a]
            mutable = ''.join(mutable)
            print(f"New value is {mutable}")
            population[0][i] = mutable
            population[1][i] = calculate_sum(mutable)
    return population


def selection(population):
    new_population = ([], [])
    sums = sorted(population[1])
    sums = sums[: pop_size]
    for (i, j) in enumerate(population[0]):
        if population[1][i] in sums and len(new_population[0]) < pop_size:
            new_population[0].append(j)
            new_population[1].append(population[1][i])
    return new_population


def genetic_algorithm(population, epoch):
    pretty_print(population)
    print('-'*32)
    if epoch > 0:
        result = selection(mutation(crossover(population)))
        genetic_algorithm(result, epoch - 1)
    else:
        print("Calculation complete.")
    return


genetic_algorithm(generate_population(), epochs)
