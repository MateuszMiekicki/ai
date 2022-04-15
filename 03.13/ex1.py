import numpy as np


def functionA():
    numberA = 123
    numberB = 321
    return numberA * numberB


def functionB_add(vectorA, vectorB):
    return np.add(vectorA, vectorB)


def functionB_mult(vectorA, vectorB):
    return np.multiply(vectorA, vectorB)


def functionC_scalarProduct(vectorA, vectorB):
    return np.dot(vectorA, vectorB)


def functionC_euclideanDistance(vectorA, vectorB):
    return np.sqrt(np.sum((vectorA - vectorB) ** 2))


def functionD_mulMatrixByCoordniate(matrixA, matrixB):
    return matrixA*matrixB


def functionD_mulMatrix(matrixA, matrixB):
    return np.matmul(matrixA, matrixB)


def functionE():
    return np.random.randint(1, 101, size=(10, 5))


def functionF_average(matrix):
    return np.average(matrix)


def functionF_minAndMax(matrx):
    return (np.min(matrx), np.max(matrx))


def functionF_standardDevation(matrix):
    return np.std(matrix)


def main():
    print(functionA())
    vectorA = np.array([3, 8, 9, 10, 12])
    vectorB = np.array([8, 7, 7, 5, 6])
    print(functionB_add(vectorA, vectorB))
    print(functionB_mult(vectorA, vectorB))
    print(functionC_scalarProduct(vectorA, vectorB))
    print(functionC_euclideanDistance(vectorA, vectorB))
    matrixA = np.array([[32, 43, 12], [6, 43, 12], [32, 12, 47]])
    matrixB = np.array([[87, 98, 62], [76, 23, 0], [42, 72, 69]])
    print(functionD_mulMatrixByCoordniate(matrixA, matrixB))
    print(functionD_mulMatrix(matrixA, matrixB))
    matrixE = functionE()
    print(matrixE)
    print(functionF_average(matrixE))
    min, max = functionF_minAndMax(matrixE)
    print(functionF_minAndMax(matrixE))
    print(functionF_standardDevation(matrixE))
    indexMaxValueInMatrixE = matrixE.argmax()
    def f(x): return (x - min)/(max-min)
    print(f(matrixE))
    print(f(matrixE.item(indexMaxValueInMatrixE)))


main()
