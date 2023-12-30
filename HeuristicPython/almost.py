# Importing 

from collections import defaultdict
import time
import numpy as np 
import genetic


# Functions

def random_configuration(num_cars, num_par, num_pass, iter):
    def random_conf():
        config = defaultdict(lambda: [0])
        pair_config = defaultdict(lambda: [[0, -1]])
        for items in range(1, num_pass + num_par):
            car = np.random.choice(num_cars, 1)[0]
            if items > num_pass and items <= num_pass + num_par:
                config[car + 1].append([items])
                config[car + 1].append([items + num_par + num_pass])
            elif items >= 1 and items <= num_pass:
                config[car + 1].append([items])
        for i in range(1, num_cars + 1):
            temp = list()
            for j in config[i]:
                if type(j) == list:
                    temp.append(j[0])
            sorted(temp)
            for j in temp:
                if j >= 1 and j <= num_pass:
                    pair_config[i].append([j, j + num_par + num_pass])
                else:
                    pair_config[i].append([j, -1])
        return pair_config
    
    #* when meet a passenger, just take him, we can temporarily ignore he/she's destination
    def uniform_random_conf():
        pair_config = defaultdict(lambda: [[0, -1]])
        arr = np.arange(1, num_pass + num_par + 1)
        np.random.shuffle(arr)
        split_arr = np.array_split(arr, num_cars)
        for car in range(num_cars):
            single_pair_conf = list()
            for items in split_arr[car]:
                if items > num_pass and items <= num_pass + num_par:
                    single_pair_conf.append([items, -1])
                    single_pair_conf.append([items + num_par + num_pass, -1])
                elif items >= 1 and items <= num_pass:
                    single_pair_conf.append([items, items + num_par + num_pass])
            pair_config[car + 1].extend(sorted(single_pair_conf))
        return pair_config

    if iter&1:
        return uniform_random_conf()
    else:
        return random_conf()

def return_true_config(given_config, num_pass, num_par):
    true_config = []
    for i in given_config:
        true_config.append(i)
        if i >= 1 and i <= num_pass:
            true_config.append(i + num_par + num_pass)
    return true_config
    
    
def cal_distance(config, distance_matrix, num_pass, num_par):
        cost = 0
        explore = []
        for city in range(1, len(config)):
            explore.append(config[city])
            cost += distance_matrix[config[city - 1]][config[city]]
            if config[city] > 2*num_pass + num_par:
                if (config[city] - num_pass - num_par) not in explore:
                    return (-1)
        return cost
            
# Main and input

"""
N, M, K = map(int, input().split())
q = [int(x) for x in input().split()] # size = M
Q = [int(x) for x in input().split()] # size = K
d = [list(map(int, input().split())) for _ in range(2*N + 2*M + 1)] # size = (2*N + 2*M + 1)*(2*N + 2*M + 1)
"""
# Read input from file



with open("D:\GIT\Optimization-mini-project\HeuristicPython\\almost.inp", "r") as file:
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
    
    # matrix distance is correct
    
    final_res = 1e9
    final_res_config = []
    
    for iter in range(16):
        # print(f"iter {iter}:")
        res_conf = []
        dict_schedule = random_configuration(num_cars, num_par, num_pass, iter)
        max_res_each_config = 0
        for id_bus, schedule in dict_schedule.items():
            ga = genetic.Genetic_Algorithm(schedule, num_cities, matrix_distance, num_pass, num_pass, cars_capacities[id_bus - 1], q)
            # print("Initial schedule is: ", schedule)
            temp_res = ga.solving_gene()
            
            res_conf.append(temp_res)
            temp = cal_distance(return_true_config(temp_res[1], num_pass, num_par), matrix_distance, num_pass, num_par)
            if max_res_each_config < temp:
                max_res_each_config = temp
            # print(temp_res[1], temp_res[0], sep = " - ", end='\n')
        if final_res > max_res_each_config:
            final_res = max_res_each_config
            final_res_config = res_conf
        # print(final_res)
    
    print(num_cars)
    for conf in final_res_config:
        true_config = return_true_config(conf[1], num_pass, num_par)
        print(len(true_config))
        for i in true_config:
            print(i, end = " ")
        print(f"- {cal_distance(true_config, matrix_distance, num_pass, num_par)}")    
    print(final_res) 
    
    
    total_running_time = time.time() - ga_start_time
    print(f"Running time = {total_running_time}")
    
    # DONE WITH GENETIC ALGORITHM