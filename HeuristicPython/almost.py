# Importing 

from collections import defaultdict
import time
import numpy as np 
import genetic


# Functions

def random_configuration(num_cars, num_par, num_pass, iter):
    '''
    There are some problems with this shit too, fixing is waste of time
    def random_conf():
        pair_config = defaultdict(lambda: [0, -1])
        for items in range(1, num_pass + num_par):
            car = np.random.choice(num_cars, 1)[0]
            if items > num_pass and items <= num_pass + num_par:
                pair_config[car + 1].append([items, -1])
                pair_config[car + 1].append([items + num_par + num_pass, -1])
            elif items >= 1 and items <= num_pass:
                pair_config[car + 1].append([items, items + num_par + num_pass])
        for i in range(1, num_cars + 1):
            pair_config[i] = sorted(pair_config[i])
            print(pair_config[i])
        return pair_config
    '''
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

    return uniform_random_conf()

def return_true_config(given_config, num_pass, num_par):
    true_config = []
    for i in given_config:
        true_config.append(i)
        if i >= 1 and i <= num_pass:
            true_config.append(i + num_par + num_pass)
    return true_config
    
    
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
    
    
    final_res = 1e9
    final_res_config = []
    for iter in range(10):
        res_conf = []
        dict_schedule = random_configuration(num_cars, num_par, num_pass, iter)
        max_res_each_config = 0
        for id_bus, schedule in dict_schedule.items():
            ga = genetic.Genetic_Algorithm(schedule, num_cities, matrix_distance, num_pass, num_pass, cars_capacities[id_bus - 1], q)
            # print("Initial schedule is: ", schedule)
            temp_res = ga.solving_gene()
            
            res_conf.append(temp_res)
            if max_res_each_config < temp_res[0]:
                max_res_each_config = temp_res[0]
            
        if final_res > max_res_each_config:
            final_res = max_res_each_config
            final_res_config = res_conf
    
    print(num_cars)
    for conf in final_res_config:
        true_config = return_true_config(conf[1], num_pass, num_par)
        print(len(true_config))
        for i in true_config:
            print(i, end = " ")
        print(f"- {conf[0]}")
            
    # TODO: fullfill the output
    
    total_running_time = time.time() - ga_start_time
    print(f"Running time = {total_running_time}")