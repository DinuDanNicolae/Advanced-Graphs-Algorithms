    In implementarea task-ului 1 am folosit algoritmul lui Dijkstra pentru aflarea drumului de cost minim.
Stocarea grafului a fost efectuata cu o matricea de adiacenta care retinea costul muchiei dintre nodurile date ca indici.
In interiorul functiei am declarat doi vectori care vor retine distantele, cat si cont daca un nod a fost sau nu vizitat.
Astfel, initializez distantele cu o valoare foarte mare, in afara de distanta pana la sursa, acesta fiind 0, iar in vectorul de vizitati, -1.
Ulterior, algoritmul se va repeta printr-o instructiune while, cat timp nodul tinta nu a fost vizitat. 
In interiorul acestei intructiuni, voi parcurge fiecare nod, calculandu-i cost. 
De asemnea, voi tine cont daca distanta calculata este cea minima si daca nodul a mai fost sau nu vizitat.
Complexitatea algoritmului efectuat este O(n^2), functia sa returnand o variabila double reprezentand costul minim pentru un drum.
Acesta este apelat de 2 ori interschimband parametrii, astfel efectuandu-se costul minim la dus si la intos.
Drumul parcurs este retinut in vectorul transmis ca parametru "prev",afisarea acestuia fiind efectuata intr-o functie auxiliara.
Costul drumului total este suma rezultatelor functiei dijkstra pentru dus si intors.
Fiecare vector alocal dinamic a fost dezalocat, iar eliberarea memoriei ocupate de graf prin matricea de adiacenta este efectuata in functia freeGraph.