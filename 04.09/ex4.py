import pandas as pd
from sklearn.cluster import DBSCAN, KMeans
from sklearn.metrics.cluster import contingency_matrix, adjusted_rand_score
import numpy as np

df = pd.read_csv("irisORG.csv")
X = df.iloc[:, :-1]
Y = df.iloc[:, -1:]


k_means = KMeans(n_clusters=3)
y_pred = k_means.fit_predict(X)
cont_m = contingency_matrix(y_pred, Y)

puirty = np.sum(np.max(cont_m, axis=1))/np.sum(cont_m)
rand_score = adjusted_rand_score(list(y_pred), list(Y.iloc[:, 0]))
print("puirty:"+str(puirty))
print("rand_score:"+str(rand_score))


dbscan = DBSCAN(eps=.33)
y_pred = dbscan.fit_predict(X)
cont_m = contingency_matrix(y_pred, Y)

puirty = np.sum(np.max(cont_m, axis=1))/np.sum(cont_m)
rand_score = adjusted_rand_score(list(y_pred), list(Y.iloc[:, 0]))
print("puirty:"+str(puirty))
print("rand_score:"+str(rand_score))
