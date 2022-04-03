from fileinput import filename
from hashlib import algorithms_available
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import sklearn.metrics as smetrics


def prepare_data_for_traing_and_test(file_name: str):
    dataset = pd.read_csv(file_name)
    dataset.Outcome = [1 if i == 1 else 0 for i in dataset.Outcome]
    y = dataset.Outcome
    x = dataset.drop(["Outcome"], axis=1)
    return (x, y)


def split_dataset(traintset: pd.DataFrame, testset: list[int], test_size: float):
    x_train, x_test, y_train, y_test = train_test_split(
        traintset, testset, test_size=test_size)
    return (x_train, x_test, y_train, y_test)


def gaussian_naive_bayes(x_train, x_test, y_train, y_test):
    nb = GaussianNB()
    predict = nb.fit(x_train, y_train).predict(x_test)
    score = nb.score(x_test, y_test)
    print("gaussian_naive_bayes:", score)
    confusion_matrix = smetrics.confusion_matrix(y_test, predict)
    print("confusion_matrix:", confusion_matrix)
    print("-------------------")
    return score


def k_neighbors(neighbors: int, x_train, x_test, y_train, y_test):
    knn = KNeighborsClassifier(n_neighbors=neighbors, metric='euclidean')
    knn.fit(x_train, y_train)
    knnscore = knn.score(x_test, y_test)
    print("knn "+str(neighbors)+":", knnscore)
    predict = knn.fit(x_train, y_train).predict(x_test)
    confusion_matrix = smetrics.confusion_matrix(y_test, predict)
    print("confusion_matrix:", confusion_matrix)
    print("-------------------")
    return knnscore


def main():
    file_name = 'diabetes.csv'
    x, y = prepare_data_for_traing_and_test(file_name)
    x_train, x_test, y_train, y_test = split_dataset(x, y, 0.37)
    nb_score = gaussian_naive_bayes(x_train, x_test, y_train, y_test)

    k1socre = k_neighbors(1, x_train, x_test, y_train, y_test)
    k3socre = k_neighbors(3, x_train, x_test, y_train, y_test)
    k5socre = k_neighbors(5, x_train, x_test, y_train, y_test)
    k11score = k_neighbors(11, x_train, x_test, y_train, y_test)

    fig = plt.figure()
    ax = fig.add_axes([0, 0, 1, 1])
    algorithms = ['GaussianNB', '1 NeighborsClassifier',  '3 NeighborsClassifier',
                  '5 NeighborsClassifier', '11 NeighborsClassifier']
    scores = [nb_score, k1socre, k3socre, k5socre, k11score]
    ax.bar(algorithms, scores)
    plt.show()


if __name__ == '__main__':
    main()
