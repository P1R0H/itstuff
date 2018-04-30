import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

mnist = input_data.read_data_sets("/tmp/data/", one_hot=True)

n_nodes_hl1 = 500   
n_nodes_hl2 = 500
n_nodes_hl3 = 500

hm_epochs = 15

n_classes = 10
batch_size = 100
input_size = 784

x = tf.placeholder('float', shape=[None, input_size])
y = tf.placeholder('float')

def nn_model(data):
    hidden_layer_1 = {'weigths': tf.Variable(tf.random_normal([input_size, n_nodes_hl1])), 
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl1]))}
    hidden_layer_2 = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl1, n_nodes_hl2])),
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl2]))}
    hidden
    main()_layer_3 = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl2, n_nodes_hl3])),
                      'biases': tf.Variable(tf.random_normal([n_nodes_hl3]))}
    output_layer = {'weigths': tf.Variable(tf.random_normal([n_nodes_hl3, n_classes])),
                    'biases': tf.Variable(tf.random_normal([n_classes]))}

    l1 = tf.nn.relu(tf.matmul(data, hidden_layer_1['weigths']) + hidden_layer_1['biases'])
    l2 = tf.nn.relu(tf.matmul(l1, hidden_layer_2['weigths']) + hidden_layer_2['biases'])
    l3 = tf.nn.relu(tf.matmul(l2, hidden_layer_3['weigths']) + hidden_layer_3['biases'])
    
    return tf.matmul(l3, output_layer['weigths']) + output_layer['biases']

def train_nn(data):
    prediction = nn_model(data)
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=prediction, labels=y))
    optimizer = tf.train.AdamOptimizer().minimize(cost)

    with tf.Session() as s:
        s.run(tf.global_variables_initializer())

        for epoch in range(1, hm_epochs+1):
            epoch_loss = 0
            for _ in range(int(mnist.train.num_examples/batch_size)):
                img_batch, lb_batch = mnist.train.next_batch(batch_size)
                _, c = s.run([optimizer, cost], feed_dict = {x: img_batch, y: lb_batch})
                epoch_loss += c
            print('Epoch', epoch, 'completed out of', hm_epochs,'loss:', epoch_loss)

        correct = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
        accuracy = tf.reduce_mean(tf.cast(correct, 'float'))
        print('Accuracy:', accuracy.eval({x: mnist.test.images, y: mnist.test.labels}))

def main():
    train_nn(x)

if __name__=='__main__':
    main()