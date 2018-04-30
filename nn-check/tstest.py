'''
Handwritten Digits Classification
python3.5

requies following python modules:
    TensorFlow - provides data manipulation and operations on matrices
    NumPy - provides  initial array generation
    MNIST - provides manipulation with MNIST training and testing datasets

created by Andrej Dravecky

'''

import tensorflow as tf
import numpy as np
from mnist import MNIST

#============ Configuration ============#

# Neural Network layers
input_size = 784 # input layer 

n_nodes_hl1 = 512 # first hidden layer
n_nodes_hl2 = 512 # second hidden layer
n_nodes_hl3 = 512 # third hidden layer

n_classes = 10 # output layer

# Training distribution
hm_epochs = 15
batch_size = 100

#=======================================#

# Loading locally saved MNIST datasets using mnist python module
mnist = MNIST('./resources')
tmpi, tmpl = mnist.load_training()
tmpti, tmptl = mnist.load_testing()

# Converting digits data to proper form to feed them to tensorflow
img_train_data = np.array(tmpi)
img_test_data = np.array(tmpti)

# Converting labels data to one-hot form
lb_train_data = np.zeros((int(len(tmpl)), n_classes))
lb_train_data[np.arange(int(len(tmpl))), tmpl] = 1
lb_test_data = np.zeros((int(len(tmptl)), n_classes))
lb_test_data[np.arange(int(len(tmptl))), tmptl] = 1

# data placeholders
x = tf.placeholder('float', shape=[None, input_size])
y = tf.placeholder('float')

def nn_model(data):
    """
    models our neural network prediction model according to our settings
    and feeds it with random weigths and biases

    :param data: data format placeholder
    :return: neural network prediction model
    
    """
    hidden_layer_1 = {'weigths': tf.Variable(tf.random_normal([input_size, n_nodes_hl1])), 
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl1]))}
    hidden_layer_2 = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl1, n_nodes_hl2])),
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl2]))}
    hidden_layer_3 = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl2, n_nodes_hl3])),
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl3]))}
    output_layer = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl3, n_classes])),
                    'biases': tf.Variable(tf.random_normal([n_classes]))}

    l1 = tf.nn.relu(tf.matmul(data, hidden_layer_1['weigths']) + hidden_layer_1['biases'])
    l2 = tf.nn.relu(tf.matmul(l1, hidden_layer_2['weigths']) + hidden_layer_2['biases'])
    l3 = tf.nn.relu(tf.matmul(l2, hidden_layer_3['weigths']) + hidden_layer_3['biases'])
    
    return tf.matmul(l3, output_layer['weigths']) + output_layer['biases']

def train_nn(data):
    """
    handles neural network training and accuracy evaluation

    :param data: data format placeholder

    """
    prediction = nn_model(data)
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=prediction, labels=y))
    optimizer = tf.train.AdamOptimizer().minimize(cost)

    with tf.Session() as s:
        s.run(tf.global_variables_initializer())

        # training
        for epoch in range(1, hm_epochs+1):
            epoch_loss = 0

            for i in range(0, len(img_train_data), batch_size):
                img_batch = img_train_data[i:i+batch_size]
                lb_batch = lb_train_data[i:i+batch_size]
                _, c = s.run([optimizer, cost], feed_dict = {x: img_batch, y: lb_batch})
                epoch_loss += c
            print('Epoch', epoch, 'completed out of', hm_epochs,'loss:', epoch_loss)

        # Accuracy evaluation
        correct = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
        accuracy = tf.reduce_mean(tf.cast(correct, 'float'))
        print('Accuracy:', accuracy.eval({x: img_test_data, y: lb_test_data}))

def main():
    train_nn(x)

if __name__=='__main__':
    main()