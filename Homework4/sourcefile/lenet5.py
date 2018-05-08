from __future__ import print_function
from keras.datasets import mnist
from keras.layers import Activation, Dense, Dropout, Flatten
from keras.layers import Convolution2D, MaxPooling2D
from keras.models import Sequential
from keras.optimizers import SGD, Adam
from keras.utils import np_utils
from matplotlib import pyplot as plt
import numpy as np
import time


def processData():
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    x_train = x_train.astype('float32')
    x_test = x_test.astype('float32')
    x_train /= 255
    x_test /= 255
    y_train = np_utils.to_categorical(y_train, 10)
    y_test = np_utils.to_categorical(y_test, 10)

    x_train = x_train.reshape(x_train.shape[0], 28,28,1)
    x_test = x_test.reshape(x_test.shape[0], 28,28,1)
    x_train = np.pad(x_train, [[0, 0], [2, 2], [2, 2], [0, 0]], mode='constant')
    x_test= np.pad(x_test, [[0, 0], [2, 2], [2, 2], [0, 0]],mode='constant')
    return [x_train, x_test, y_train, y_test]

x_train, x_test, y_train, y_test = processData()

num_filters = 16
filter_size = 5


def DefineModel():
    model = Sequential()
    # C1 Layer
    model.add(Convolution2D(16, (5, 5), activation='relu',padding='same', input_shape=(32, 32,1)))

    # Max pooling
    model.add(MaxPooling2D((2, 2)))

    #Dropout
    model.add(Dropout(0.25))

    # Second Layer
    model.add(Convolution2D(6, (5, 5), activation='relu', padding='same',input_shape=(14, 14,1)))

    # Max pooling
    model.add(MaxPooling2D((2, 2)))

    #Dropout
    model.add(Dropout(0.25))

    # Flatten the CNN output
    model.add(Flatten())
    # Add Three dense Layer for the FNN

    model.add(Dense(120))
    model.add(Activation('relu'))

    model.add(Dense(84))
    model.add(Activation('relu'))

    model.add(Dense(10))

    # For classification, the activation is softmax
    model.add(Activation('softmax'))

    # Define optimizer
    optmzr = Adam(lr=0.01, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=1.0)

    # Define loss function = cross entropy
    model.compile(loss='categorical_crossentropy', optimizer='adadelta', metrics=["accuracy"])
    return model

def TrainModel(data=None, epochs=10, batch=512):
    start_time = time.time()
    model = DefineModel()

    x_train, x_test, y_train, y_test = data
    print('Start training.')

    hist = model.fit(x_train, y_train, nb_epoch=epochs, batch_size=batch,
                        validation_data=(x_test, y_test), verbose=1)
    model.evaluate(x_test, y_test, verbose =1)
    print("Training took {0} seconds.".format(time.time() - start_time))
    return model, hist

def plot(train_value, test_value, value_is_loss_or_acc):
    f, ax = plt.subplots()
    plt.plot([None] + train_value, 'o-')
    plt.plot([None] + test_value, 'x-')
    plt.legend(['Train ' + value_is_loss_or_acc, 'Test ' + value_is_loss_or_acc], loc=0)
    plt.title('Training and Test ' + value_is_loss_or_acc + ' per epoch')
    plt.xlabel('Epoch')
    plt.ylabel(value_is_loss_or_acc)
    plt.show()


trained_model, training_hist = TrainModel(data=[x_train, x_test, y_train, y_test])
plot(training_hist.history['loss'], training_hist.history['val_loss'], 'Loss')
plot(training_hist.history['acc'], training_hist.history['val_acc'], 'Accuracy')


def TestModel(model=None, data=None):
    x_test, y_test = data
    scores = model.evaluate(x_test, y_test)
    return scores

test_score = TestModel(model=trained_model, data=[x_test, y_test])
print("Test loss {:.4f}, accuracy {:.2f}%".format(test_score[0], test_score[1] * 100))

def perf_measure(model = None, data = None):

    from sklearn.metrics import confusion_matrix
    x_test,y_test = data
    Y_pred = model.predict(x_test, verbose=2)
    y_pred = np.argmax(Y_pred, axis=1)
    for ix in range(10):
        print(ix, confusion_matrix(np.argmax(y_test, axis=1), y_pred)[ix].sum())
    print(confusion_matrix(np.argmax(y_test, axis=1), y_pred))


conf_score = perf_measure(model = trained_model, data = [x_test,y_test])

