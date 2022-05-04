# Lista zadań do przerobienia podczas semestru

## Legenda

* Liczby w nawiasach to ilość możliwych punktów
* gwiazdka(*) oznacza zadanie dodatkowe lub zadanie, które można rozwinąć

## Algorytm wspinaczkowy (2)

Zaimplementuj algorytm wspinaczkowy w obu wersjach:

* klasyczny z deterministycznym wyborem najlepszego sąsiada punktu roboczego
* z losowym wyborem sąsiada spośród otoczenia punktu roboczego

## Algorytm tabu (1 lub 2*)

Należy zaimplementować algorytm Tabu dla swojego problemu. Program powinien pozwalać na podanie rozmiaru tabu (pozwalamy
na nieograniczone tabu). Na punkt bonusowy - zaimplementuj cofanie się na liście do ostatniego punktu roboczego z
którego można było kontynuować obliczenia.

## Algorytm symulowanego wyżarzania (1)

Zaimplementuj algorytm SA dla swojego problemu. Będzie trzeba dobrze zdefiniować co rozumiesz przez otoczenie punktu
roboczego oraz jak "zasymulować" działanie pozwalające na losowanie punktu roboczego za pomocą rozkładu normalnego
zamiast jednorodnego. Zachęcam do konsultacji z prowadzącym. Parametrem niech będzie wybór schematu wyżarzania.

## Algorytm genetyczny (3)

Zaimplementuj GA dla Twojego zadania. Jest tu sporo elementów, dlatego dopuszczam częściowe rozwiązania i każde będę
oceniał indywidualnie. Niech będzie:

* 2 metody krzyżowania
* 2 metody mutacji
* 2 warunki zakończenia

Parametrami niech będzie - wybór metody krzyżowania, mutacji oraz warunku zakończenia. Parametrem niech będzie także
liczba osobników w populacji.

## Algorytm genetyczny - wersja równoległa (1)

Zaimplementuj algorytm genetyczny w wersji zrównoleglonej - zobacz jakie elementy algorytmu można rozbić na niezależne
zadania i wykorzystaj całą dostępną moc obliczeniową Twojego komputera. Najłatwiej zrównoleglić proces liczenia funkcji
oceny.

## Algorytm genetyczny - wersja wyspowa (1 lub 3*)

Zaimplementuj algorytm wyspowy. Niech dodatkowym parametrem będą: liczba wysp, tępo migracji oraz przerwa migracyjna.
Schemat łączenia migrantów jest tu dowolny, najłatwiej podmieniać losowego. Na dodatkowe 2 punkty - rozprosz obliczenia
na wiele fizycznych maszyn - możesz potem uruchomić eksperyment na pracowni.

## Programowanie genetyczne - demo (1*)

Przygotuj przykład pokazujący jak działa programowanie genetyczne. Proszę przygotować przykład inny niż typowe w
dokumentacji i na tutorialach (absolutnie nie rób o pogodzie).

## Strategia ewolucyjna (1*)

Zaimplementuj strategię ewolucyjną dla wybranego przez Ciebie problemu z zadań testowych dla
optymalizacji (https://en.wikipedia.org/wiki/Test_functions_for_optimization). Może to być nawet strategia z regułą 1/5
sukcesów.

## Eksperyment porównujący metody (2)

Zaimplementuj skrypt (dowolny język) porównujący wszystkie metody rozwiązywania Twojego zadania. Wnioski jakie
powinieneś dać radę otrzymać to:

* jaki zestaw parametrów daje najlepsze wyniki dla każdej metody
* jaka metoda kończy się najszybciej (porównujemy dla najlepszych parametrów)
* jaka metoda zużywa najmniej zasobów przy takim samym poziomie osiągniętych wyników (porównujemy dla najlepszych
  parametrów)
* jaka metoda najszybciej zbiega (porównujemy dla najlepszych parametrów)

Wnioski poprzyj wykresami i wynikami eksperymentów. Przygotuj się do pokazania jak w automatyczny sposób powtórzyć
eksperyment.