import numpy as np
from visualization import *
def o_distance(data, u):
    return np.sqrt(np.sum((data[:,0:2] - u)**2,axis = 1))

def KmeansEstep(data, num_k, us):
    dataShape = data.shape
    argmin = np.zeros(shape = (dataShape[0], ), dtype = np.int)
    #argmin = -1;
    ui = us[0,:]
    mindis = o_distance(data, ui)
    for i in range(1,num_k):
        ui = us[i,:]
        tmpdis = o_distance(data, ui)
        tmppos = np.where(tmpdis<mindis)
        argmin[tmppos] = i
        mindis[tmppos] = tmpdis[tmppos]
    return argmin
    
def KmeansMstep(data, argmin, num_k):
    newu = np.zeros(shape = (num_k,2), dtype = np.float)
    for i in range(num_k):
        tmppos = np.where(argmin==i)
        if tmppos[0].shape[0]==0:
            continue
        else :
            newu[i,:] = np.mean(data[tmppos][:,0:2], axis = 0)
    return newu
def k_mean(data, num_k, init_u, max_ite = 10, converge = 0.01, outputpath = ''):
    #E-step, M-Step
    uShape = init_u.shape
    old_u = np.zeros_like(init_u)
    old_u[:,:] = init_u[:,:]
    if num_k!=uShape[0]:
        print "ERROR: number of clusters is wrong"
        return -1
    for i in range(max_ite):
        argmin = KmeansEstep(data, num_k, old_u)
        newu = KmeansMstep(data, argmin, num_k)
        delta = np.sum(np.sqrt(np.sum((newu - old_u)**2,axis = 1)))
        if outputpath!='':
            out = outputpath+str(i)+'.pdf'
            plotKmeans(data,num_k, argmin, newu, ['r', 'g', 'b', 'gold', 'darkorange'], outputpath = out)
        if delta < converge:
            return [argmin, newu, i+1]
        old_u[:,:] = newu[:,:]
    return [argmin, newu, max_ite]