import pandas as pd
from matplotlib import pyplot as plt
from sklearn.cluster import DBSCAN

df = pd.read_csv("iris2D.csv")

coordinates = df.loc[:, ["PC1", "PC2"]]

plt.scatter(df.loc[:, "PC1"], df.loc[:, "PC2"])
plt.show()

dbscan = DBSCAN(eps=.33)
clusters = dbscan.fit_predict(coordinates)

plt.scatter(x=coordinates["PC1"],
            y=coordinates["PC2"],
            c=dbscan.labels_)
plt.show()
