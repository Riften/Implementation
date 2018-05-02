import numpy as np
def gaussianGen(num_k, num_v, means, covs):
    num = np.sum(num_v)
    data = np.zeros(shape = (num, 3), dtype = np.float)
    counter = 0
    for i in range(num_k):
        data[counter:counter+num_v[i], 0:2] = np.random.multivariate_normal(means[i], covs[i], num_v[i])
        data[counter:counter+num_v[i],2] = i
        counter = counter+num_v[i]
    return data

def init_means(data, num_k):
    num_v = data.shape[0]
    sam = np.array(np.round(np.random.sample(num_k)*(num_v-1)), dtype = np.int8)
    init_u = np.zeros(shape = (num_k,2), dtype = np.float64)
    for i in range(num_k):
        init_u[i,:] = data[sam[i], 0:2]
    return init_u