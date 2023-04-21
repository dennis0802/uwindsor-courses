# Developer: Dennis Dao
# Date: Mar 24, 2023
# Student Number: 110010116

# Code for testing the SVM on the dataset

'''
NOTE TO GRADER:
While testing the code on a Jupyter notebook, some of the code does take
a while to execute. Using HalvingGridSearch took about 1.5h and depending
on the kernel or classification method of the support vector, it can take about
20 minutes or less to complete
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Setup board
index = []
board = ['a', 'b', 'c', 'd', 'e', 'f', 'g']

for i in board:
    for j in range(6):
        index.append(i + str(j+1))

column_names = index + ['Class']

# Read csv from provided dataset
# (dataset should be in the same directory as this)
csv_filename = "connect-4.data"
df = pd.read_csv(csv_filename, names=column_names)

# Total of 67557 rows in the dataset
df.head()

x = df.iloc[:, :-1].values
y = df.iloc[:, -1].values
# Replace x(1), o(0), and b(-1) with numerical encoding,
# the fitting function doesn't work with character data types
for i in range(len(x)):
    x[i] = list(map(lambda x: x.replace('b', '-1'), x[i]))
    x[i] = list(map(lambda x: x.replace('o', '0'), x[i]))
    x[i] = list(map(lambda x: x.replace('x', '1'), x[i]))

# Verify results
print("Connect-4 Data:")
print(x)
print("Connect-4 Classes:")
print(y)

# Encode classes
from sklearn.preprocessing import LabelEncoder

l_encode = LabelEncoder()
y = l_encode.fit_transform(y)
print("Encoded classes:")
print(y)

from sklearn.model_selection import train_test_split
# 40% test, 60% train
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.4, random_state=21)
print("Total # X-Training Strings: ", len(x_train))
print(x_train)
print("Total # Y-Training Strings: ", len(y_train))
print(y_train)
print("Total # X-Testing Strings: ", len(x_test))
print(x_test)
print("Total # Y-Testing Strings: ", len(y_test))
print(y_test)

# Defining the SVM classifier
from sklearn.svm import LinearSVC
from sklearn.svm import SVC
#svm = SVC(kernel='poly')
#svm = SVC(kernel='linear', C=1, gamma=0.0001)
#svm = SVC(kernel='sigmoid')
#svm = SVC(kernel='rbf')
svm = LinearSVC(random_state=21)

# Training the SVM classifier - covnergence warning may happen but still runs ok
from sklearn.model_selection import cross_val_score
clf = svm.fit(x_train, y_train)
scores = cross_val_score(clf, x, y, cv=5, n_jobs=-1)
print("SVM scores:")
print(scores)

# Predict result
y_pred = svm.predict(x_test)
print("Predicted y:")
print(y_pred)

y_pred_vertical = y_pred.reshape(len(y_pred), 1)
print("Predicted y vertical:")
print(y_pred_vertical)

y_true_vertical = y_test.reshape(len(y_test), 1)
print("True vertical y:")
print(y_true_vertical)

true_pred = np.concatenate((y_true_vertical, y_pred_vertical), axis=1)
print("True predicted y:")
print(true_pred)

# Plot the confusion matrix
from sklearn.metrics import confusion_matrix
confusion_mat = confusion_matrix(y_test, y_pred)
sns.heatmap(confusion_mat, annot=True)
plt.xlabel("Predicted Label")
plt.ylabel("True Label")
plt.title("Confusion Matrix")
# If all were predicted correctly, there should only be 1 kind of value per row
plt.show()

# Get classifier accuracy
from sklearn.metrics import accuracy_score
accuracy_score(y_test, y_pred)

# Refit (can take around 1.5h)
# To save some time, c=1 and gamma=0.0001 were returned when I ran this
from sklearn.model_selection import GridSearchCV
from sklearn.experimental import enable_halving_search_cv 
from sklearn.model_selection import HalvingGridSearchCV

# Define parameter range
param_grid = {'C': [0.1, 1, 10, 100, 100],
              'gamma': [1, 0.1, 0.01, 0.001, 0.0001],
              'kernel': ['linear']}
grid = HalvingGridSearchCV(SVC(), param_grid, refit=True, verbose=3)
grid.fit(x_train, y_train)

# Print best parameters
print("Best parameters: ", grid.best_params_)
# Print how model looks after hyper parameter tuning
print("Best estimator: ", grid.best_estimator_)
