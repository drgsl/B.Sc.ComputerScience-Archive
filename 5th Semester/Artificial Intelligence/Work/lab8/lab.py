import pickle, gzip, numpy as np
import random
from matplotlib import pyplot as pltbias_Bupd

train_set_1 = []
train_set_2 = []
train_set = []
test_set_1 = []
test_set_2 = []
test_set = []
read = []
f = open("iris.data")
for line in f.readlines():
    if line.strip() != '':
        read.append(line.replace('\n', '').split(','))
random.shuffle(read)
j = 1


#'Iris-versicolor'  'Iris-virginica'  'Iris-setosa'
for i in range(0, len(read)):
    if i < 135:
        train_set_1.append(np.asarray(read[i][:-1]))
        if read[i][-1]== 'Iris-versicolor':
            train_set_2.append(0)
        elif read[i][-1]== 'Iris-virginica':
            train_set_2.append(1)
        elif read[i][-1]== 'Iris-setosa':
            train_set_2.append(2)
    else:
        test_set_1.append(np.asarray(read[i][:-1]))
        if read[i][-1]== 'Iris-versicolor':
            test_set_2.append(0)
        elif read[i][-1]== 'Iris-virginica':
            test_set_2.append(1)
        elif read[i][-1]== 'Iris-setosa':
            test_set_2.append(2)
train_set.append(np.asarray(train_set_1))
train_set.append(np.asarray(train_set_2))
test_set.append(np.asarray(test_set_1))
test_set.append(np.asarray(test_set_2))
train_set[0]=np.array(train_set[0],dtype=float)
test_set[0]=np.array(test_set[0],dtype=float)

I = np.identity(3)
EPOCH = 1500
LEARNING_RATE = 0.02
BATCH_SIZE = 5
MOMENTUM=0.000005
L2=0.5

input_size = len(train_set[0][0])
hidden_size = 10
output_size = 3

weights = []
weights.append(np.random.randn(hidden_size, input_size) / np.sqrt(input_size))
weights.append(np.random.randn(output_size, hidden_size) / np.sqrt(hidden_size))
biases = []
biases.append(np.random.rand(hidden_size, 1))
biases.append(np.random.rand(output_size, 1))

def sigmoid(x):
    return 1.0 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return sigmoid(x) * (1 - sigmoid(x))

def softmax(x):
    return np.exp(x) / np.sum(np.exp(x))


def feedforward( element):

    previous_layer=element
    layers_activations = [previous_layer]
    layers_sums = []
    for i in range(len(weights)):
        current_layer_sum=np.dot(weights[i],previous_layer)+biases[i]
        layers_sums.append(current_layer_sum)
        if i+1 != len(weights):
            previous_layer=sigmoid(current_layer_sum)
        else:
            previous_layer=softmax(current_layer_sum)
        layers_activations.append(previous_layer)

    return [layers_sums, layers_activations]

def backpropagation( annotation, layers_sums, layers_activations):

    weigthAdj = [np.zeros(w.shape) for w in weights]
    biase_adj = [np.zeros(b.shape) for b in biases]
        
    delta = layers_activations[-1] - I[annotation].reshape(len(I), 1)
    weigthAdj[-1] = np.dot(delta, layers_activations[-2].transpose())
    biase_adj[-1] = delta

    for i in range(2, len(weights) + 1):
        delta = np.dot(weights[-i + 1].transpose(), delta) * sigmoid_derivative(layers_sums[-i])
        weigthAdj[-i] = np.dot(delta, layers_activations[-i - 1].transpose())
        biase_adj[-i] = delta

    return [weigthAdj, biase_adj]

def train( train_set, EPOCH_number, batch_size, learning_rate,momentum,l2):

    data = train_set[0]
    labels = train_set[1]
    data_len = len(data)
    batches_number = data_len // batch_size

    l2_term = 2 * l2/data_len

    for ii in range(EPOCH_number):
        perm = [i for i in range(data_len)]
        random.shuffle(perm)

        for i in range(batches_number):
            weigth_Bupd = [np.zeros(w.shape) for w in weights]
            bias_Bupd = [np.zeros(b.shape) for b in biases]
            for j in range(batch_size):
                index=perm[i * batch_size + j]
                element = data[index].reshape(len(data[index]),1)
                annotation = labels[index]

                layers_sums, layers_activations = feedforward(element)
                weigthAdj, biase_adj = backpropagation( annotation, layers_sums, layers_activations)

                for k in range(len(weigthAdj)):
                    weigth_Bupd[k] += weigthAdj[k]
                    bias_Bupd[k] += biase_adj[k]

            frictionW = [np.ones(w.shape) for w in weights]
            frictionB = [np.ones(b.shape) for b in biases]
            for k in range(len(weigth_Bupd)):

                frictionW[k] = momentum * frictionW[k] - learning_rate * weigth_Bupd[k]
                frictionB = momentum * frictionB[k] - learning_rate * bias_Bupd[k]

                weights[k] = weights[k] + frictionW[k]-learning_rate*l2_term*weights[k]
                biases[k] = biases[k] + frictionB[k]-learning_rate*l2_term*biases[k]

        print(ii+1)

train(train_set, EPOCH, BATCH_SIZE, LEARNING_RATE,MOMENTUM,L2)

def test_ff( element):
    h_layer_sum = np.dot(weights[0], element) + biases[0]
    h_layer_output = sigmoid(h_layer_sum)
    o_layer_sum = np.dot(weights[1], h_layer_output) + biases[1]
    o_layer_output = softmax(o_layer_sum)
    return o_layer_output

wrong_classified_counter = 0
data = test_set[0]
labels = test_set[1]
for i in range(len(data)):
    element = data[i].reshape(len(data[i]),1)
    output_layer = test_ff(element)
    biggest = np.argmax(output_layer)
    if I[labels[i]][biggest]!=1:

        wrong_classified_counter += 1
print(round(100*(len(data)-wrong_classified_counter)/len(data),2),'%')