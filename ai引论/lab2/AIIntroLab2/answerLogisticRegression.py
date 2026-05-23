import numpy as np

# 超参数
# TODO: You can change the hyperparameters here
lr = 1  # 学习率
wd = 1e-3  # l2正则化项系数


def predict(X, weight, bias):
    """
    使用输入的weight和bias，预测样本X是否为数字0。
    @param X: (n, d) 每行是一个输入样本。n: 样本数量, d: 样本的维度
    @param weight: (d,)
    @param bias: (1,)
    @return: (n,) 线性模型的输出，即wx+b
    """
    # TODO: YOUR CODE HERE
    return np.dot(X,weight)+bias
    raise NotImplementedError

def sigmoid(x):
    return 1 / (np.exp(-x) + 1)


def step(X, weight, bias, Y):
    """
    单步训练, 进行一次forward、backward和参数更新
    @param X: (n, d) 每行是一个训练样本。 n: 样本数量， d: 样本的维度
    @param weight: (d,)
    @param bias: (1,)
    @param Y: (n,) 样本的label, 1表示为数字0, -1表示不为数字0
    @return:
        haty: (n,) 模型的输出, 为正表示数字为0, 为负表示数字不为0
        loss: (1,) 由交叉熵损失函数计算得到
        weight: (d,) 更新后的weight参数
        bias: (1,) 更新后的bias参数
    """
    # TODO: YOUR CODE HERE
    n = X.shape[0]
    haty = predict(X, weight, bias)
    z = -Y * haty 
    loss_vec = np.where(z > 0, z + np.log(1 + np.exp(-z)), np.log(1 + np.exp(z)))
    loss = np.mean(loss_vec) 
    sig_z = np.where(z > 0, 1 / (1 + np.exp(-z)), np.exp(z) / (1 + np.exp(z)))
    grad_haty = -Y * sig_z / n  
    grad_weight = np.dot(X.T, grad_haty) + wd * weight
    grad_bias = np.sum(grad_haty)
    weight = weight - lr * grad_weight
    bias = bias - lr * grad_bias
    return haty, loss, weight, bias
    raise NotImplementedError
