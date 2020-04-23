import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Importing the dataset 

dataset = pd.read_csv("IOTPROJECT.csv")
X = dataset.iloc[:,:-1]
Y = dataset.iloc[:,3]


# Splitting the dataset into test_set and train_set

from sklearn.model_selection import train_test_split
X_train,X_test,Y_train,Y_test = train_test_split(X,Y,test_size = 0.2)


# Feature Scaling

from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)

#Fitting Simple Linear Regression in the dataset

from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(X_train,Y_train)
regressor.intercept_
regressor.coef_

#predicting the value for the dataset

pred=regressor.predict(X_test)
pred

#Checking the accuracy of the predicted Model

from sklearn.metrics import r2_score as r2
q1=r2(Y_test,pred)
q1

#Predicting the moisture content on the basis of user interface input

T=[]
Moist=0.0
print("Enter the values of humidity(70-80), light(755-1000) and temperature(30-40) ")
for i in range(1,4):
    T.append(float(input()))
Moist=float(input("Enter the current moisture level : "))
T = sc_X.transform([T])
Y_pred = regressor.predict(T)
print("\nThe amount of water required is {} units.".format(Y_pred))
if(Y_pred[0] > Moist):
    print("Motor turned on.")
elif(Y_pred[0] < Moist):
    print("Excess moisture in the soil.")
else:
    print("Moisture just right.")



#Visualizing the Training set results
    
Z = X_train[:,1:2]
plt.scatter(Z,Y_train,color="Red")
plt.plot(Z,regressor.predict(X_train),color="Blue")
plt.title("Light vs Moisture (Training set)")
plt.xlabel("Light")
plt.ylabel("Moisture")
plt.show()

#Visualizing the Test set results

Z = X_test[:,1:2]
plt.scatter(Z,Y_test,color="Red")
plt.plot(Z,regressor.predict(X_test),color="Blue")
plt.title("Light vs Moisture (Test set)")
plt.xlabel("Light")
plt.ylabel("Moisture")
plt.show()

