import pandas as pd
import numpy as np
import serial
import time
# Make numpy values easier to read.
np.set_printoptions(precision=3, suppress=True)
import tensorflow as tf
from tensorflow.keras import layers
from tensorflow.keras.layers.experimental import preprocessing


arduino = serial.Serial(port='COM15', baudrate=115200, timeout=.1)
print('Established serial connection to Arduino')

def check_float(potential_float):
    try:
        float(potential_float)
        return True
    except ValueError:
        return False

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

def write(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)

def read():
    data = arduino.readline()
    return data
def temp():
    while(True):
        temper= str(read())[2:7]
        time.sleep(1)
        is_valid_float = check_float(temper)

        print(is_valid_float)
        if is_valid_float:
            break
    tem= float(temper)
    print(tem)
    time.sleep(1)
    print(tem)
    time.sleep(1)
    print(tem)
    time.sleep(1)
    print(tem)

    abalone_train = pd.read_csv(          # Reading the dataset file
        "height dataset.csv",
        names=["Height", "Fertilizers"]) # Naming the first column "Height" and the second "Fertilizers"

    # The artificial neural network code
    abalone_train.head()
    abalone_features = abalone_train.copy()
    abalone_labels = abalone_features.pop('Fertilizers')
    abalone_features = np.array(abalone_features)
    abalone_features
    abalone_model = tf.keras.Sequential([
      layers.Dense(64, activation="sigmoid"), # sigmoid is the activation function
      layers.Dense(1, activation="sigmoid")
    ])

    # The learning rate is a parameter that controls how much to change the model in response
    #  to the estimated error each time the model weights are updated and in our AI, the learning rate = 0.1
    optimizer = tf.keras.optimizers.SGD(learning_rate=0.1)
    abalone_model.compile(loss="MSE",optimizer=optimizer)

    abalone_model.fit(abalone_features, abalone_labels, epochs=10000)
    data = np.array([[tem]])
    predictions = abalone_model.predict(data)
    pre=str(predictions)
    pr=''.join(c for c in pre if c.isdigit())
    print(pr)

    print('Program started')

    # Setting up the Arduino
    write(pr)
    time.sleep(3)

while True:
    temp()
    time.sleep(20)
