# Importing 

from collections import defaultdict
import time
import numpy as np 
import genetic


# Functions

def random_configuration(num_cars, num_par, num_pass, iter):
    def random_conf():
        linear_config = defaultdict(lambda: [0])
        pair_config = defaultdict(lambda: [0, -1])
        for items in range(1, num_pass + num_par):
            car = np.random.choice(num_cars, 1)[0]
            if items > num_pass and items <= num_pass + num_par:
                linear_config[car + 1].append(items)
                linear_config[car + 1].append(items + num_par + num_pass)
                pair_config[car + 1].append([items, -1])
                pair_config[car + 1].append([items + num_par + num_pass, -1])
            elif items >= 1 and items <= num_pass:
                linear_config[car + 1].append(items)
                linear_config[car + 1].append(items + num_par + num_pass)
                pair_config[car + 1].append([items, items + num_par + num_pass])
        return linear_config, pair_config

    #* when meet a passenger, just take him, we can temporarily ignore he/she's destination
    def uniform_random_conf():
        linear_config = defaultdict(lambda: [0])
        pair_config = defaultdict(lambda: [0, -1])
        arr = np.arange(1, num_pass + num_par + 1)
        np.random.shuffle(arr)
        split_arr = np.array_split(arr, num_cars)
        for car in range(num_cars):
            single_conf = split_arr[car].tolist()
            single_pair_conf = list()
            for items in split_arr[car]:
                if items > num_pass and items <= num_pass + num_par:
                    single_conf.append(items + num_par + num_pass)
                    single_pair_conf.append([items, -1])
                    single_pair_conf.append([items + num_par + num_pass, -1])
                elif items >= 1 and items <= num_pass:
                    single_pair_conf.append([items, items + num_par + num_pass])
            linear_config[car + 1].extend(sorted((single_conf)))
            pair_config[car + 1].extend(sorted(single_pair_conf))
        return (linear_config, pair_config)
    # if iter&1:
    #     return random_conf()
    # else:
    return uniform_random_conf()
    
def generate_dis_mat(matrix_distance, list_passengers):
    return matrix_distance[list_passengers, :][:, list_passengers]
# Main and input

"""
N, M, K = map(int, input().split())
q = [int(x) for x in input().split()] # size = M
Q = [int(x) for x in input().split()] # size = K
d = [list(map(int, input().split())) for _ in range(2*N + 2*M + 1)] # size = (2*N + 2*M + 1)*(2*N + 2*M + 1)
"""
# Read input from file
with open("D:\GIT\Optimization-mini-project\HeuristicPython\input.inp", "r") as file:
    N, M, K = map(int, file.readline().split())
    q = list(map(int, file.readline().split()))  # size = M
    Q = list(map(int, file.readline().split()))  # size = K
    d = [list(map(int, file.readline().split())) for _ in range(2 * N + 2 * M + 1)]  # size = (2 * N + 2 * M + 1) * (2 * N + 2 * M + 1)

if __name__ == "__main__":
    num_cities = 2*N + 2*M + 1 
    num_cars = K
    cars_capacities = Q
    
    matrix_distance = d
    num_pass_par = N + M
    num_pass = N
    num_par = M
    
    print("Genetic Algorithm")
    ga_start_time = time.time()
    
    for iter in range(1):
        dict_schedule = random_configuration(num_cars, num_par, num_pass, iter)
        for id_bus, schedule in dict_schedule:
            # matrix_dist_of_a_car = generate_dis_mat(matrix_distance, linear_schedule)
            # ga = genetic.Genetic_Algorithm(num_cities, matrix_dist_of_a_car, num_pass, num_pass, cars_capacities[id_bus - 1], q)
            # print("Initial schedule is: ", linear_schedule)
            # res = ga.solving_gene()
            print(schedule[0])
    #? everything is not daijobu, python is both stupid and not stupid
    
    total_running_time = time.time() - ga_start_time
    print(f"Running time = {total_running_time}")