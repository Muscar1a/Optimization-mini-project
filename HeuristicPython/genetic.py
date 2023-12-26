import numpy as np 
import copy 
import random 


class Genetic_Algorithm():
    def __init__(self, num_vertices, distance_matrix, num_par, num_pass, capacity, q):
        # num_vertices = num_cities
        self.num_vertices = num_vertices
        self.vertices = [int(i) for i in range(num_vertices)]
        self.distance_matrix = distance_matrix
        self.num_pass = num_pass
        self.num_par = num_par
        self.capacity = capacity
        self.q = q
        # q is a list present the weight of all parcels 
        
    def compute_capacity(self, config):
        cap = 0
        for x in config:
            if x > self.num_pass and x <= self.num_pass + self.num_par:
                cap += self.q[x - self.num_pass - 1]
            elif x > 2*self.num_pass + self.num_par:
                cap -= self.q[x - 2*self.num_pass - self.num_par - 1]
        return cap;
        
    def children(self, list_node, state):
        curCap = self.compute_capacity(state)
        res = []
        for n in list_node:
            if n not in state:
                if curCap > self.capacity:
                    if (n - self.num_pass - self.num_par) in state:
                        res.append(n)
                else:
                    if n > self.num_pass + self.num_par:
                        if (n - self.num_pass - self.num_par) in state:
                            res.append(n)
                        else: continue
                    else:
                        res.append(n)
        return res
        
        
        
    def generateValidState(self):
        state = [0]
        list_node = [int(i) for i in range(1, self.num_vertices)]
        curCap = 0
        while True:
            list_next_cities = self.children(list_node, state)
            if len(list_next_cities) == 0: break
            next_city = np.random.choice(list_next_cities, 1)[0]
            
            
            if next_city > self.num_pass and next_city <= self.num_pass + self.num_par:
                curCap += self.q[next_city - self.num_pass - 1]
            elif next_city > 2*self.num_pass + self.num_par:
                curCap -= self.q[next_city - 2*self.num_pass - self.num_par - 1]
            state.append(next_city)
        state.append(0)
        return state
        
        
        
    def solving_gene(self, maxIter=10, num_genes=5, crossover_rate=0.6, num_elites=5):
        population = []
        while len(population) != num_genes:
            initial_gene = self.generateValidState()
            print(initial_gene)
            population.append(initial_gene)#, self.cal_distance(initial_gene)])