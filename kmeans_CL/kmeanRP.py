#Exercise 2
#k-mean with RPCL
#基本想法：靠近最近的，远离倒数第二近的
import numpy as np
from visualization import *
def o_distance(data, u):
    return np.sqrt(np.sum((data[:,0:2] - u)**2,axis = 1))

def KmeansEstepRP(data, num_k, us):
    dataShape = data.shape
    dis = np.zeros(shape=(dataShape[0],num_k), dtype = np.float)
    for i in range(num_k):
        dis[:,i] = o_distance(data[:,0:2], us[i,0:2])
    argmin=np.argpartition(dis, 2)[:,0:2]
    return argmin
def KmeansMstepRP(data, num_k, argmin, oldu, gamma=0.1):
    newu = np.zeros(shape = (num_k,2), dtype = np.float64)
    #gamma = 0.1
    #newu = np.zeros(shape = (num_k,2), dtype = np.float64)

    for i in range(num_k):
        pos1 = np.where(argmin[:,0]==i)
        pos2 = np.where(argmin[:,1]==i)
        p = np.mean(data[pos1][:,0:2],axis=0)
        q = np.mean(data[pos2][:,0:2],axis=0)
        du = (p-oldu[i,0:2])+gamma*(oldu[i,0:2]-q)
        newu[i,0:2] = oldu[i,0:2]+du
    return newu
def k_mean_RP(data, num_k, init_u, max_ite = 10, converge = 0.01, gamma=0.1, outputpath = ''):
    #E-step, M-Step
    uShape = init_u.shape
    old_u = np.zeros_like(init_u)
    old_u[:,:] = init_u[:,:]
    if num_k!=uShape[0]:
        print "ERROR: number of clusters is wrong"
        return -1
    for i in range(max_ite):
        argmin = KmeansEstepRP(data, num_k, old_u)
        newu = KmeansMstepRP(data, num_k, argmin, old_u, gamma)
        delta = np.sum(np.sqrt(np.sum((newu - old_u)**2,axis = 1)))
        if outputpath!='':
            out = outputpath+str(i)+'.pdf'
            plotKmeans(data,num_k, argmin[:,0], newu, ['r', 'g', 'b', 'gold', 'darkorange'], outputpath = out)
        if delta < converge:
            return [argmin[:,0], newu, i+1]
        old_u[:,:] = newu[:,:]
    return [argmin[:,0], newu, max_ite]