import csv
from typing import Tuple, Dict
import matplotlib.pyplot as plt


def showCsvFile(fileName: str) -> list:
    with open(fileName, 'r') as file:
        cities = csv.reader(file, delimiter=',')
        rows = []
        for row in cities:
            rows.append(row)
        return rows


class Content():
    def __init__(self, year: int, citiesPopulation: Tuple[int, int, int]) -> None:
        self.year = year
        self.citiesPopulation = citiesPopulation

    def contetn(self, delimeter: str) -> str:
        return str(self.year) + delimeter + delimeter.join(str(i) for i in self.citiesPopulation)


def addDataForFile(fileName: str, delimeter: str, content: Content) -> None:
    with open(fileName, 'a') as file:
        print(content.contetn(delimeter))
        file.write(content.contetn(delimeter)+'\n')


class Population():
    def __init__(self, year, population) -> None:
        self.year = year
        self.population = population


def readPopulationOfCityFromFile(fileName: str) -> Dict[str, Dict[int, int]]:
    rows = []
    headers = ''
    with open(fileName, 'r') as file:
        reader = csv.reader(file)
        headers = next(reader)
        for row in reader:
            rows.append(row)

    content = {key: {} for key in headers[1:]}

    for row in rows:
        for i in range(1, len(row)):
            content[headers[i]].update({int(row[0]): int(row[i])})
    return content


def drawPlot(data) -> None:
    myList = data.items()
    myList = sorted(myList)
    x, y = zip(*myList)
    plt.plot(x, y, '-ok')
    plt.ylabel("Liczba ludnosci w tysiacach", size=5)
    plt.xlabel("Rok", size=5)
    plt.show()


def drawPlotForMultpleCities(data):
    N = len(data)
    cmap = plt.cm.get_cmap("hsv", N+1)
    i = 0
    for city in data:
        myList = data[city].items()
        myList = sorted(myList)
        x, y = zip(*myList)
        plt.plot(x, y, '-ok', c=cmap(i), label=city)
        i += 1
    plt.legend(loc='upper left')
    plt.ylabel("Liczba ludnosci w tysiacach", size=5)
    plt.xlabel("Rok", size=5)
    plt.show()


def main():
    fileName: str = "miasta.csv"
    print(showCsvFile(fileName))
    content = Content(2010, [460, 555, 405])
    addDataForFile(fileName, ',', content)

    data = readPopulationOfCityFromFile(
        fileName)
    drawPlot(data['Gdansk'])
    drawPlotForMultpleCities(data)


if __name__ == '__main__':
    main()
