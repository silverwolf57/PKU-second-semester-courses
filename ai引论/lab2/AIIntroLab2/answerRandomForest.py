from numpy.random import rand
import mnist
from answerTree import *
import numpy as np

# 超参数
# TODO: You can change the hyperparameters here
num_tree = 10     # 树的数量
ratio_data = 1.0   # 采样的数据比例
ratio_feat = 0.2 # 采样的特征比例
hyperparams = {
    "depth":15, 
    "purity_bound":1e-3,
    "gainfunc": negginiDA
    } # 每颗树的超参数


def buildtrees(X, Y):
    """
    构建随机森林
    @param X: n*d, 每行是一个输入样本。 n: 样本数量， d: 样本的维度
    @param Y: n, 样本的label
    @return: List of DecisionTrees, 随机森林
    """
    # TODO: YOUR CODE HERE
    # 提示：整体流程包括样本扰动、属性扰动和预测输出
    trees = []
    n, d = X.shape
    num_samples = int(n * ratio_data)
    num_features = int(d * ratio_feat)
    for i in range(num_tree):
        sample_indices = np.random.choice(n, size=num_samples, replace=True)
        X_sample = X[sample_indices]
        Y_sample = Y[sample_indices]
        feat_indices = np.random.choice(d, size=num_features, replace=False).tolist()
        depth = hyperparams["depth"]
        purity_bound = hyperparams["purity_bound"]
        gainfunc = hyperparams["gainfunc"]
        print(f"Building tree {i+1}/{num_tree} ...") 
        tree = buildTree(X_sample, Y_sample, feat_indices, depth, purity_bound, gainfunc)
        trees.append(tree)
    return trees

def infertrees(trees, X):
    """
    随机森林预测
    @param trees: 随机森林
    @param X: n*d, 每行是一个输入样本。 n: 样本数量， d: 样本的维度
    @return: n, 预测的label
    """
    pred = [inferTree(tree, X)  for tree in trees]
    pred = list(filter(lambda x: not np.isnan(x), pred))
    upred, ucnt = np.unique(pred, return_counts=True)
    return upred[np.argmax(ucnt)]
