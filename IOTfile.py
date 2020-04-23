import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sklearn as skl
from sklearn.metrics import r2_score as r2
from sklearn import linear_model as lm
from sklearn.model_selection import train_test_split as tts
x1=pd.read_excel(r"D:\ml files\\IOTPROJECT.xlsx") 
x=x1
indep=x.iloc[:,:-1]
dep=x.iloc[:,3:]
dep
indep

xtr,xte,ytr,yte=tts(indep,dep,test_size=0.20)

from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
xtr = sc_X.fit_transform(xtr)
xte = sc_X.transform(xte)

m1=lm.LinearRegression()
mod1=m1.fit(xtr,ytr)
m1.intercept_
m1.coef_
pred=m1.predict(xte)
pred
q1=r2(yte,pred)
q1
