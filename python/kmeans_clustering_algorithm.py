# https://gist.github.com/bistaumanga/6023692

# Or how to use numpy

import sys
import pylab as plt
import numpy as np


def kmeans_clustering_algorithm(X, K, show=True):
    # K = 3
    # np.random.seed(142)
    centroids = X[(1,2,3),:] # X[ np.random.choice(np.arange(len(X)), K), :]
    for i in range(10):
        # Cluster Assignment step
        C = np.array(
            [ np.argmin( [np.dot(x_i-y_k, x_i-y_k) for y_k in centroids]) for x_i in X ] 
        )
        # Move centroids step
        centroids = np.array( [X[C == k].mean(axis = 0) for k in range(K)] )

        if show:
            plt.clf()
            # plt.scatter(X[:,0], X[:,1])
            for k in range(K):
                plt.scatter(X[C == k][:,0],X[C == k][:,1])
            plt.scatter(centroids[:,0], centroids[:,1])
            plt.title(str(i))
            plt.pause(0.5)
    
    return centroids


def demo():

    print("\n")
    print("kmeans_clustering_algorithm demo")
    print("------------------------------------")

    # generate 3 cluster data
    # data = np.genfromtxt('data1.csv', delimiter=',')
    m1, cov1 = [9, 8], [[1.5, 2], [1, 2]]
    m2, cov2 = [5, 13], [[2.5, -1.5], [-1.5, 1.5]]
    m3, cov3 = [3, 7], [[0.25, 0.5], [-0.1, 0.5]]
    data1 = np.random.multivariate_normal(m1, cov1, 250)
    data2 = np.random.multivariate_normal(m2, cov2, 180)
    data3 = np.random.multivariate_normal(m3, cov3, 100)

    X = np.vstack((data1,np.vstack((data2,data3))))
    np.random.shuffle(X)

    kmeans_clustering_algorithm(X, K=3)


if __name__ == "__main__":
    demo()
