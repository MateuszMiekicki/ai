import pandas as pd
from matplotlib import pyplot as plt
from sklearn.cluster import KMeans

df = pd.read_csv("iris2D.csv")

coordinates = df.loc[:, ["PC1", "PC2"]]

plt.scatter(df.loc[:, "PC1"], df.loc[:, "PC2"])
plt.show()

kmeans = KMeans(n_clusters=3)
clusters = kmeans.fit_predict(coordinates)
centroides = kmeans.cluster_centers_

plt.scatter(x=coordinates["PC1"],
            y=coordinates["PC2"],
            c=kmeans.labels_)
plt.scatter(x=centroides[:, 0],
            y=centroides[:, :1],
            c="red")
plt.show()
