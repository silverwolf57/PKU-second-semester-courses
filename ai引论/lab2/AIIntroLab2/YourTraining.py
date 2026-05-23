import numpy as np
import mnist
from autograd.BaseGraph import Graph
from autograd.BaseNode import Linear, relu, LogSoftmax, NLLLoss, Dropout, BatchNorm
import pickle
from scipy.ndimage import rotate, shift
import time
from autograd.utils import PermIterator
import os

save_path = "model/your_model.pkl"

lr = 0.05       
wd1 = 0.0
wd2 = 1e-4
batchsize = 256

def buildGraph(Y):
    return Graph([
        BatchNorm(784),
        Linear(784, 512),
        BatchNorm(512),
        relu(),
        Dropout(0.2),
        Linear(512, 128),
        BatchNorm(128),
        relu(),
        Dropout(0.2),
        Linear(128, 10),
        LogSoftmax(dim=-1),
        NLLLoss(Y)
    ])

def augment_data(X):
    X = X.reshape(-1, 28, 28)
    ret = np.zeros_like(X)
    for i in range(X.shape[0]):
        img = X[i]
        angle = np.random.uniform(-15, 15)
        img = rotate(img, angle, reshape=False, mode='constant', cval=0.0, order=0)
        
        shift_x = np.random.uniform(-2, 2)
        shift_y = np.random.uniform(-2, 2)
        img = shift(img, (shift_x, shift_y), mode='constant', cval=0.0, order=0)
        
        ret[i] = img
    return ret.reshape(-1, 784)

if __name__ == "__main__":
    os.makedirs("model", exist_ok=True)
    
    base_X = np.concatenate([mnist.trn_X, mnist.val_X], axis=0)
    base_Y = np.concatenate([mnist.trn_Y, mnist.val_Y], axis=0)
    
    graph = buildGraph(base_Y)
    
    start_time = time.time()
    epoch = 0
    
    dataloader = PermIterator(base_X.shape[0], batchsize)
    while time.time() - start_time < 450:
        epoch += 1
        graph.train()
        acc_sum = 0
        
        for perm in dataloader:
            tX = base_X[perm].copy()
            tY = base_Y[perm]
            half = len(tX) // 2
            tX[:half] = augment_data(tX[:half])
            
            graph[-1].y = tY
            graph.flush()
            outputs = graph.forward(tX)
            pred = outputs[-2]
            
            graph.backward()
            for node in graph:
                if hasattr(node, 'grad') and len(node.grad) > 0:
                    for j in range(len(node.grad)):
                        node.grad[j] = np.clip(node.grad[j] / len(tX), -5.0, 5.0)
                        
            graph.optimstep(lr, wd1, wd2)
            
            preds = np.argmax(pred, axis=-1)
            acc_sum += np.sum(preds == tY)
            
            if time.time() - start_time > 450:
                break
                
        print(f"Epoch {epoch} finished. Acc: {acc_sum / len(base_X):.4f}")
    graph.eval()
    with open(save_path, "wb") as f:
        pickle.dump(graph, f)
    print("Training finished and model saved.")