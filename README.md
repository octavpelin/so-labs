## so-labs
## PRIVATE REPO
# Debug construct:
```
#ifdef DEBUG
#define Dprintf(msg, ...) printf("[%s]:%d" msg, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg, ...)	/* do nothing */
#endif
```
# Linux GCC: Optiuni utile:
```
    -Lcale – instruiește compilatorul să caute și în directorul cale bibliotecile pe care le folosește programul; opțiunea se poate specifica de mai multe ori, pentru a adãuga mai multe directoare
    -lbiblioteca – instruiește compilatorul cã programul are nevoie de biblioteca biblioteca. Fișierul ce conține biblioteca trebuie să se numească libbiblioteca.so sau libbiblioteca.a.
    -Icale – instruiește compilatorul sã caute fișierele antet (headere) și în directorul cale; opțiunea se poate specifica de mai multe ori, pentru a adãuga mai multe directoare
    -Onivel-optimizări, instuiește compilatorul ce nivel de optimizare trebuie aplicat:
        -O0, va determina compilatorul sã nu optimizeze codul generat;
        -O3, va determina compilatorul sã optimizeze la maxim codul generat;
        -O2, este pragul de unde compilatorul va începe sã insereze direct în cod functiile inline în loc sã le apeleze;
        -Os, va pune accentul pe optimizările care duc la reducerea dimensiunii codului generat, și nu a vitezei la execuție.
    -g, dacã se folosește această opțiune compilatorul va genera în fișierele de ieșire informații care pot fi apoi folosite de un debugger (informații despre fișierele sursã și o mapare între codul mașinã și liniile de cod ale fișierelor sursã)

Paginile de ajutor ale GCC (man gcc, info gcc) oferă o listă cu toate opțiunile posibile ale GCC.
```
# Linux: Crearea unei biblioteci statice:
Primul pas:
```
so@spook$ gcc -Wall -c f1.c
so@spook$ gcc -Wall -c f2.c
```
Al doilea pas (arhivarea):
```
so@spook$ ar rc libintro.a f1.o f2.o
so@spook$ gcc -Wall main.c -o main -lintro
/usr/bin/ld: cannot find -lintro
collect2: ld returned 1 exit status
so@spook$ gcc -Wall main.c -o main -lintro -L .
so@spook$ ./main
Current file name is f1.c
Current line 5 in file f2.c
```
# Linux: Crearea unei biblioteci partajate:
```
so@spook$ gcc -fPIC -c f1.c
so@spook$ gcc -fPIC -c f2.c
so@spook$ gcc -shared f1.o f2.o -o libintro_shared.so
so@spook$ gcc -Wall main.c -o main -lintro_shared -L.
so@spook$ ./main
./main: error while loading shared libraries: libintro_shared.so:
     cannot open shared object  file: No such file or directory
```
Includerea LibPath:
Metoda 1:
```
so@spook$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
so@spook$ ./main
Current file name is f1.c
Current line 5 in file f2.c
```
Metoda 2:
```
so@spook$ LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.  ./main
Fisierul curent este f1.c
Va aflati la linia 5 din fisierul f2.c
so@spook$ ./main
./main: error while loading shared libraries: libintro_shared.so:
     cannot open shared object  file: No such file or directory
```
