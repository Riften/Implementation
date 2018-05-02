import numpy as np
from visualization import *
def f_distance(us, d, counter):
    return np.sqrt(np.sum((us[:,0:2] - d)**2,axis = 1))*np.log(counter+10)

def o_distance(data, u):
    return np.sqrt(np.sum((data[:,0:2] - u)**2,axis = 1))

def CL_epoch(data, tmp_u, argmin, lr, isFSCL=False, isRPCL=False, gamma = 0):
    num = data.shape[0]
    counter = np.zeros(shape = (tmp_u.shape[0],), dtype = np.int)
    for (i,d) in enumerate(data):
        if not(isFSCL):
            dis = o_distance(tmp_u, d[0:2])
        else:
            dis = f_distance(tmp_u, d[0:2], counter)
        idx=np.argpartition(dis, 2)
        c = idx[0]
        r = idx[1]
        argmin[i] = c
        counter[c] = counter[c]+1
        tmp_u[c,:] = tmp_u[c,:] + lr*(d[0:2] - tmp_u[c,:])
        if(isRPCL):
            tmp_u[r,:] = tmp_u[r,:] - lr*gamma*(d[0:2] - tmp_u[r,:])

def CL_learning(data, init_u, num_k, lr, max_ite=1, converge = 0.01, isFSCL=False, isRPCL = False, gamma = 0, outputpath=''):
    #lr = 0.1
    old_u = np.zeros_like(init_u)
    newu = np.zeros_like(init_u)
    old_u[:,:] = init_u[:,:]
    newu[:,:] = init_u[:,:]
    
    num = data.shape[0]
    argmin = np.zeros(shape = (num,), dtype = np.int)
    for i in range(max_ite):
        np.random.shuffle(data)
        CL_epoch(data, newu, argmin, lr, isFSCL, isRPCL, gamma)
        delta = np.sum(np.sqrt(np.sum((newu - old_u)**2,axis = 1)))
        if outputpath!='':
            out = outputpath+str(i)+'.pdf'
            plotKmeans(data,num_k, argmin, newu, ['r', 'g', 'b', 'gold', 'darkorange'], outputpath = out)
        if delta < converge:
            return [argmin, newu, i+1]
        old_u[:,:] = newu[:,:]
    #argmin = KmeansEstep(data, num_k, tmp_u)
    return [argmin,newu, max_ite]
