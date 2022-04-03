import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix


def main():
    dataset = pd.read_csv('diabetes.csv')
    dataset.Outcome = [1 if i == 1 else 0 for i in dataset.Outcome]
    x = dataset.drop(["Outcome"], axis = 1)
    y = dataset.Outcome.values
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.37)
    nb = GaussianNB()
    nb.fit(x_train, y_train)
    nbscore=nb.score(x_test, y_test)
    print("Naive Bayes score: ",nbscore)


    knn1 = KNeighborsClassifier(n_neighbors=1, metric='euclidean')
    knn1.fit(x_train, y_train)
    knn1score = knn1.score(x_test,y_test)
    print("knn1score: ",knn1score)

    knn3 = KNeighborsClassifier(n_neighbors=3, metric='euclidean')
    knn3.fit(x_train, y_train)
    knn3score = knn3.score(x_test,y_test)
    print("knn3score ",knn3score)
    
    knn5 = KNeighborsClassifier(n_neighbors=5, metric='euclidean')
    knn5.fit(x_train, y_train)
    knn5score = knn5.score(x_test,y_test)
    print("knn5score: ",knn5score)

    y_predict = knn5.fit(x_train, y_train).predict(x_test)
    print(confusion_matrix(y_test, y_predict))

    knn11 = KNeighborsClassifier(n_neighbors=5, metric='euclidean')
    knn11.fit(x_train, y_train)
    knn11score = knn11.score(x_test,y_test)
    print("knn11score: ",knn11score)

    y_predict = knn11.fit(x_train, y_train).predict(x_test)
    print(confusion_matrix(y_test, y_predict))



    fig = plt.figure()
    ax = fig.add_axes([0,0,1,1])
    langs = ['GaussianNB', '1 NeighborsClassifier',  '3 NeighborsClassifier', '5 NeighborsClassifier','11 NeighborsClassifier']
    students = [nbscore,knn1score,knn3score,knn5score,knn11score]
    ax.bar(langs,students)
    plt.show()

if __name__ == '__main__':
    main()
