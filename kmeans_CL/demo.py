from pylib.visualization import *
from pylib.dataGen import *
from pylib.kmean import *
from pylib.CL import *
import numpy as np

mean1 = np.array([0, 0])
cov1 = [[1,  -2], 
        [-2, 10]]  # diagonal covariance
mean2 = np.array([10, 9])
cov2 = [[4.4, 3],
        [3,  6]]
mean3 = np.array([3,15])
cov3 = [[10, 0.2],
        [0.2,  5]]

means = np.array([mean1, mean2, mean3])
covs = np.array([cov1, cov2, cov3])
data = gaussianGen(3, [1000, 500, 700], means, covs)
colormap = ['r', 'g', 'b', 'gold', 'darkorange']
init_u = init_means(data, 3)

plotGaussian(data,3, data[:,2], means, covs, colormap, outputpath = 'output/gaussianData.pdf')
[argmin, u, ite] = k_mean(data, 3, init_u, 3, 0.01, 'output/kmean_')
[argminCL, uresCL, ite] = CL_learning(data, init_u, 3, 0.1, 3, converge=2, outputpath= 'output/CL_')
[argminFSCL, uresFSCL, FSCLite] = CL_learning(data, init_u, 3, 0.1, 3, converge=2, isFSCL=True, outputpath= 'output/FSCL_')
[argminRPCL, uresRPCL, RPCLite] = CL_learning(data, init_u, 3, 0.1, 3, converge=2, 
                                              isFSCL=True, isRPCL=True, gamma=0.1,
                                              outputpath= 'output/RPCL_')
