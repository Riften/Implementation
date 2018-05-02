import numpy as np
from scipy import linalg
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse
def plotGaussian(data,num_k, argmin, means, covs, colormap, outputpath = ''):
    fig = plt.figure(figsize=(4,4))
    ax = fig.add_subplot(111)
    num = data.shape[0]
    X = data[:,0]
    Y = data[:,1]
    xmax = np.max(X)
    xmin = np.min(X)
    ymax = np.max(Y)
    ymin = np.min(Y)
    xlen = xmax - xmin
    ylen = ymax - ymin
    if xlen > ylen:
        plt.xlim(xmin, xmax)
        pad = (xlen - ylen)/2
        plt.ylim(ymin-pad, ymax+pad)
    else:
        plt.ylim(ymin, ymax)
        pad = (ylen - xlen)/2
        plt.xlim(xmin - pad, xmax+pad)
    #print np.max(X)
    #color_pred = np.zeros(shape = (num,), dtype = '|S1')

    # Plot an ellipse to show the Gaussian component
    
    for i in range(num_k):
        pos = (argmin == i)
        if len(pos)==0:
            v = [xlen*0.1, xlen*0.1]
            angle=0
        else:
            plt.scatter(X[pos], Y[pos], .8, color=colormap[i])
            v, w = linalg.eigh(covs[i])
            v = 3. * np.sqrt(2.) * np.sqrt(v)
            u = w[0] / linalg.norm(w[0])
            angle = np.arctan(u[1] / u[0])
            angle = 180. * angle / np.pi  # convert to degrees
        ell = Ellipse(means[i], v[0], v[1], 180. + angle, color=colormap[i])
        #e = Ellipse(u[i,:], d, d, 0, color = colormap[i])
        ell.set_alpha(0.3)
        ax.add_artist(ell)
    if(outputpath!=''):
        fig.savefig(outputpath)

def plotKmeans(data,num_k, argmin, u, colormap, outputpath = ''):
    fig = plt.figure(figsize=(4,4))
    ax = fig.add_subplot(111)
    num = data.shape[0]
    X = data[:,0]
    Y = data[:,1]
    xmax = np.max(X)
    xmin = np.min(X)
    ymax = np.max(Y)
    ymin = np.min(Y)
    xlen = xmax - xmin
    ylen = ymax - ymin
    if xlen > ylen:
        plt.xlim(xmin, xmax)
        pad = (xlen - ylen)/2
        plt.ylim(ymin-pad, ymax+pad)
    else:
        plt.ylim(ymin, ymax)
        pad = (ylen - xlen)/2
        plt.xlim(xmin - pad, xmax+pad)
    #print np.max(X)
    color_pred = np.zeros(shape = (num,), dtype = '|S1')

    for i in range(num_k):
        pos = (argmin == i)
        
        if np.sum(pos)==0:
            width=height=xlen*0.2
        else:
            width = np.max(X[pos]) - np.min(X[pos])
            height = np.max(Y[pos]) - np.min(Y[pos])
            plt.scatter(X[pos], Y[pos], .8, color=colormap[i])
        d = np.min([width, height])
        
        e = Ellipse(u[i,:], d, d, 0, color = colormap[i])
        e.set_alpha(0.4)
        ax.add_artist(e)
    if(outputpath!=''):
        fig.savefig(outputpath)