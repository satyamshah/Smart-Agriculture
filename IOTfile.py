import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sklearn as skl
from sklearn.metrics import r2_score as r2
from sklearn import linear_model as lm
from sklearn.model_selection import train_test_split as tts
x1=pd.read_excel(r"D:\ml files\\IOTproject.xlsx") 
x=x1
indep=x.iloc[:,:-1]
dep=x.iloc[:,3:]
dep
indep
xn,xt,yn,yt=tts(indep,dep,test_size=0.30)
m1=lm.LinearRegression()
mod1=m1.fit(xn,yn)
m1.intercept_
m1.coef_
pred=m1.predict(xt)
pred
q1=r2(yt,pred)
q1
