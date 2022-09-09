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
    abalone_train = pd.read_csv(
    "humidity dataset.csv",
    names=["Temperature", "Moisture"])

    abalone_train.head()

    abalone_features = abalone_train.copy()
    abalone_labels = abalone_features.pop('Moisture')
    abalone_features = np.array(abalone_features)
    abalone_features
    abalone_model = tf.keras.Sequential([
      layers.Dense(64, activation="sigmoid"),
      layers.Dense(1, activation="sigmoid")
    ])
    optimizer = tf.keras.optimizers.SGD(learning_rate=0.1)
    abalone_model.compile(loss="MSE",
                          optimizer=optimizer)

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
    time.sleep(1800)
