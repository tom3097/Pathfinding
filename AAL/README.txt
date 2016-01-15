Autor: Tomasz Bochenski, 261416
Prowadzacy: dr Tomasz Gambin

1 ---Krotka specyfikacja problemu---:
Opracowanie algorytmu, ktory znajduje najkrotsza droge z okreslonego pola A do
pola B. Kazde pole jest albo bialego albo czarnego koloru. Poruszac sie mozna tylko po polach bialych.
Ponadto przy generacji danych nalezy zwrocic uwage na to, aby z kazdego pola bialego mozna sie bylo potencjalnie
dostac do dowolnego innego pola o tym kolorze. Ponadto nalezy porownac czas obliczen i wyniki roznych metod.

2 ---Uruchamianie---:
Program moze byc uruchomiony na dwie mozliwosci.

Pierwsza z nich to uruchomienie programu bez zadnych opcji ani parametrow (AAL.exe). Gdy uzytkownik wybierze ta opcje
na ekranie konsoli wyswietlanejest menu glowne z mozliwymi do wyboru opcjami. Uruchomione zostaje cos w stylu
konsolowego GUI.

Druga z nich to uruchomienie programu z opcjami i parametrami.
Dozwolone sa nastepujace polecenia aktywacji programu:

AAL.exe [-a/-dt/-dh/-bf] -f path
Program wyznacza najkrotsza sciezke dla rastra wczytanego z pliku, o sciezce path. Wyznaczanie tej sciezki
odbywa sie za pomoca jednego z 4 algorytmow (-a: A*, -dt: Dijkstra Table, -dh: Dijkstra Heap, -bf: Bellman-Ford).

AAL.exe [-a/-dt/-dh/-bf] -g M N probability
Program wyznacza najkrotsza sciezke dla rastra wygenerowanego automatycznie, przy czym M to liczba wierszy rastra,
N to liczba kolumn rastra, natomiast probability to liczba od 0 do 1 okreslajaca prawdopodobienstwo czy tez 
stosunek pol bialych - dozwolonych, do wszystkich pol rastra. Wyznaczanie tej sciezki odbywa sie za pomoca 
jednego z 4 algorytmow (-a: A*, -dt: Dijkstra Table, -dh: Dijkstra Heap, -bf: Bellman-Ford).

AAL.exe [-a/-dt/-dh/-bf] -t initM initN step
Program generuje tabelke ze statystykami dla okreslonego typu algorytmu (-a: A*, -dt: Dijkstra Table, -dh: Dijkstra Heap, 
-bf: Bellman-Ford). Parametry initM oraz initN okreslaja wymiary rastra poczatkowego, natomiast step jest to wartosc jaka jest dodawana
do obu wymiarow rastra przy jego zwiekszaniu.


3 ---Opis konwencji dotyczacych danych wejsciowych i prezentacji wynikow---
Itnieja 4 mozliwe sposoby dzialania aplikacji.
*Pierwszy z nich sluzy sprawdzeniu poprawnosci dzialania algorytmow i polega na wprowadzeniu danych z klawiatury.
Przykladowy raster wprowadzony z klawiatury moze miec postac:

.1..$..$....$..
...$$..$..$$.$.
.$...$$..$..$$.
..$..$..$..$...
..$.$$...$.....
....$$$..$.$$..
.$.........$$..
.$.$$.$$..$$..2

gdzie . - pole dozwolone - white, $ - pole niedozwolone - black, 1 - poczatek scizeki, 2 - cel sciezki
Raster zostanie stworzony jesli wszystkiedane sa prawidlowe, czyli dlugosc wierszy zawsze jest taka sama,
istnieje dokladnie jeden poczatek sciezki, istnieje dokladnie jeden cal sciezki oraz nie zostaly wpisane
znaki rozne od wczesniej wymienionych.

*Drugi z nich rowniez sluzy sprawdzeniu poprawnosci dzialania algorytmow i polega na wprowadzeniu danych z pliku.
Dane wprowadzane z pliku maja taka sama postac jak dane wprowadzane z klawiatury. Jedyna roznica jest fakt, ze
zamiast wpisywac dane z klawiatury mozna w ten sam sposob uzupelnic plik tekstowy, do ktorego nastepnie nalezy
podac sciezke. Prawidlowo stworzony plik z danymi powinien miec ostatnia linijke pusta - po napisaniu ostatniego
wiersza rastra nalezy nacisnac enter.

* Trzeci sposob rowniez sluzy sprawdzeniu poprawnosci dzialania algorytmu. W tym przypadku uzytkownik podaje wymiary
rastra oraz liczbe od 0 do 1 reprezentujaca stosunek pol bialych do wszystkich pol rastra. Nastepnie raster taki
jest generowany.

We wszystkich tych trzech przypadkach nastepuje rozwiazywanie zadanego problemu czterema roznymi sposobami, czyli
algorytmami A*, Dijkstra - tablica, Dijkstra - kopiec oraz Bellmana Forda.
Na poczatku wyswietlany jest wygenerowany raster. Ma on postac taka jak raster wprowadzany z klawiatury czy tez z pliku.

Nastepnie wyswietlane sa sciezki, wyznaczone przez poszczegolne algorytmy. Przykladowa wyswietlona sciezka:

..............
..###@........
.##...........
.#............
.#............
.#..####......
.#..#..#......
.####..######.
............@.

gdzie @ - poczatek / koniec sciezki, # - jednostka scizeki

* Czwarty sposob sluzy do oceny zlozonosci problemow. Uzytkownik wybiera jaki algorytm chce testowac.
Nastepnie wpisuje poczatkowe wymiary problemu, czyli poczatkowe wymiary rastra, oraz podaje o ile jednostek
ma wzrastac wymiar M i N po przejsciu do kolejnego, wiekszego rastra. W efekcie generowana jest tabelka
pozwalajaca ocenic poprawnosc teoretycznej zlozonosci asymptotycznej. Przyklad wygenerowanej tabelki:

n = ______20    t(n) = ________24095    T(n) = _____56    q = ___1.1234
n = ______56    t(n) = ________64795    T(n) = ____223    q = ___1.1356
n = _____110    t(n) = _______123245    T(n) = ____454    q = ___1.0567
n = _____182    t(n) = _______234543    T(n) = ____789    q = ___1.0345
n = _____224    t(n) = _______455443    T(n) = ___1234    q = ___0.9980

gdzie n - wymiar problemu, czyli przemnozona przez sobie ilosc wierszy i kolumn, t(n) - zmierzony
czas potrzebny na wykonanie algorytmu, T(n) - teoretyczna ocena algorytmu, q - wspolczynnik zgodnosci
oceny teoretycznej z pomiarem czasu, jesli jest on w przyblizeniu rowny 1 to oszacowanie jest dobre.

4 ---Krótki opis metod rozwiazania, zastosowanych algorytmow i struktor danych---:
* Algorytm Bellmana-Forda - idea tego algorytmu opiera sie na metodzie relaksacji. Metoda relaksacji krawedzi polegana
sprawdzeniu, czy przy przejsciu dana krawedzia grafu (u,v) z 'u' do 'v', nie otrzymamy krotszej niz dotychczasowa sciezki
z 's' do 'v'. Jesli tak, to odpowiednio zmniejszamy oszacowane wagi najkrotszej sciezki.

* Algorytm Dijkstry to przyklad algorytmu zachlannego. Algorytm ten dokonuje decyzji lokalnie oprtymalnej, a nastepnie
kontynuuje rozwiazanie podproblemu wynikajacego z podjetej decyzji. Mozna powiedziec, ze algorytm Dijkstry jest 
specjalnym przypadkiem algorytmu A*, gdzie parametr H zawsze wynosi 0 (funkcja heurystyczna kazdemu argumentowi
przyporzadkowuje wartosc 0). Algorytm Dijkstry jest tu zaimplementowany na 2 sposoby. W pierwszym z nich kolejka
priorytetowa zaimplementowana jest jako tablica, w drugim jako kopiec.

* ALgorytm A* - jest to algorytm heurystyczny. Szuka najkrotszej drogi laczacej pole startowe z polem koncowym.
W pierwszej kolejnosci sprawdzane sa pola, przez ktore prowadza potencjalnie najbardziej obiecujace drogi do celu.
Jest to zachowanie charakterystyczne dla algorytmow typu Best First Search, w ktorych w pierwszej kolejnosci
rozpatrywane sa potencjalnie najlepsze przypadki. Nie jest on algorytmem zachlannym.

Wszystkie wykorzystywane w algorytmie strukury danych zaimplementowalem sam. Sa to:
* struktura reprezentujace wspolrzedne
* struktura reprezentujaca pole rastra
* struktur reprezentujaca raster
* struktor reprezentujaca linie w tablece z wynikami

5 ---Informacje o funkcjonalnej dekompozycji programu na moduly---
Stworzone pliki naglowkowe:
* AStar.h - zawiera klase ze statyczna metoda do rozwiazywania problemu najkrotszej sciezki za pomoca
algorytmu A* oraz inne pomocnicze metody
* BellmanFord.h - zawiera klase ze statyczna metoda do rozwiazywania problemu najkrotszej sciezki za pomoca
algorytmu Bellmana-Forda oraz inne pomocnicze metody
* Coords.h - zawiera klase Coords ktora reprezentuje wspolrzedne. Posiada one standardowe metody czyli settery
oraz gettery a takze przeciazone niezbedne operatory
* DataGenerator.h - zawiera klase DataGenerator ktora sluzy do generowania danych. Posiada ona statyczne
metody pozwalajace na generowanie rastra na podstawie danego pliku, danych wprowadzanych z klawiatury.
Pozwala takze na generowanie parametryzowanego losowego rastra oraz generowanie statystyk wyswietlanych
potem w tablece ktora sluzy do obliczenia wspolczynnika zgodnosci oceny teoretycznej z pomiarem czasu.
* Dijkstra.h - zawiera klase ze statyczna metoda do rozwiazywania problemu najkrotszej sciezki za pomoca
algorytmu Dijkstry. Mozliwy jest wybor jednego z dwoch sposobow. W pierwszym z nich kolejka priorytetowa
zaimplementowana jest jako zwykla tablica. W drugim kolejka ta zaimplementowana jest jako kopiec.
Zawiera takze inne metody pomocnicze.
* Field.h - zawiera klase Field, ktora reprezentuje pole w rastrze. Pole to jest opisywane przez takie
wartosci jak informacja czy jest to pole zabronione - czarne, czy pole niezabronione - biale, wartosci
wspolczynnikow G, H oraz F wykorzystywane w algorytmie A*, informacje o wspolrzednych pola oraz o 
rodzicu pola.
* Heap.h - zawiera klase Heap, ktora reprezentuje kopiec, wykorzystywany w algorytmie Dijkstry.
Jest ona odpowiednio do tego celu zaimplementowana.
* MyMatrix.h - zawiera szablon klasy reprezentujacej macierz o okreslonych wymiarach, przechowujacej
dane typu okreslonego przez parametr szablonowy.
* Raster.h - zawiera klase reprezentujaca raster. Raster posiada rozne pola, niektore biale niektore
czarne oraz informacjew o polu poczatkowym oraz koncowym.
* TableLine.h - zawiera klase TableLine ktora reprezentuje linie z tabeli wynikow. Zapisane sa w niej
informacje o wielkosci rozwiazywanego problemum, czasie wykonania, teoretycznym, asymptotycznym czasie
oraz wartosc wspolczynnika zgodnosci oceny teoretycznej z pomiarem czasu
* Timer.h - zawiera klase Timer, ktora wykorzystywana jest do pomiaru czasu.
Stworzone pliki implementacyjne:
* AStar.cpp - implementacja klasy AStar
* BellmanFord.cpp - implementacja klasy BellmanFord
* Coords.cpp - implementacja klase Coords
* DataGenerator.cpp - implementacja klase DataGenerator
* Dijkstra.cpp - implementacja klase Dijkstra
* Field.cpp - implementacja klase Field
* Heap.cpp - implementacja klase Heap
* Raster.cpp - implementacja klase Raster
* TableLine.cpp - implementacja klase TableLine
* Timer.cpp - implementacja klase Timer






