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
    -Lcale â instruieÈte compilatorul sÄ caute Èi Ã®n directorul cale bibliotecile pe care le foloseÈte programul; opÈiunea se poate specifica de mai multe ori, pentru a adÃ£uga mai multe directoare
    -lbiblioteca â instruieÈte compilatorul cÃ£ programul are nevoie de biblioteca biblioteca. FiÈierul ce conÈine biblioteca trebuie sÄ se numeascÄ libbiblioteca.so sau libbiblioteca.a.
    -Icale â instruieÈte compilatorul sÃ£ caute fiÈierele antet (headere) Èi Ã®n directorul cale; opÈiunea se poate specifica de mai multe ori, pentru a adÃ£uga mai multe directoare
    -Onivel-optimizÄri, instuieÈte compilatorul ce nivel de optimizare trebuie aplicat:
        -O0, va determina compilatorul sÃ£ nu optimizeze codul generat;
        -O3, va determina compilatorul sÃ£ optimizeze la maxim codul generat;
        -O2, este pragul de unde compilatorul va Ã®ncepe sÃ£ insereze direct Ã®n cod functiile inline Ã®n loc sÃ£ le apeleze;
        -Os, va pune accentul pe optimizÄrile care duc la reducerea dimensiunii codului generat, Èi nu a vitezei la execuÈie.
    -g, dacÃ£ se foloseÈte aceastÄ opÈiune compilatorul va genera Ã®n fiÈierele de ieÈire informaÈii care pot fi apoi folosite de un debugger (informaÈii despre fiÈierele sursÃ£ Èi o mapare Ã®ntre codul maÈinÃ£ Èi liniile de cod ale fiÈierelor sursÃ£)

Paginile de ajutor ale GCC (man gcc, info gcc) oferÄ o listÄ cu toate opÈiunile posibile ale GCC.
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

## Windows:
```
cl hello.c
cl /?		/* list of options */
link /?	/* list of options */
```
# Optiuni:

* /Wall - activează toate warning-urile
* /LIBPATH:<dir> - această opţiune indică linker-ului să caute şi în directorul dir bibliotecile pe care trebuie să le folosească programul; opţiunea se foloseşte după /link
* /I<dir> - caută şi în acest director fişierele incluse prin directiva include
* /c - se va face numai compilarea, adică se va omite etapa de link-editare.
* /D<define_symbol> - definirea unui macro de la compilare

# Opţiuni privind optimizarea codului:

*    /O1 minimizează spaţiul ocupat
*    /O2 maximizează viteza
*    /Os favorizează spa?iul ocupat
*    /Ot favorizează viteza
*    /Od fără optimizări (implicit)
*    /Og activează optimizările globale

#  Setarea numelui pentru diferite fişiere de ieşire:

*    /Fo<file> nume fişier obiect
*    /Fa<file> nume fişier în cod de asamblare
*    /Fp<file> nume fişier header precompilat
*    /Fe<file> nume fişier executabil

## Biblioteci in Windows:
# Windows: Crearea unei biblioteci statice
```
>lib /out:<nume.lib> <lista fișiere obiecte>
```
Exemplu:
```
# obținem fișierul obiect f1.obj din sursa f1.c
>cl /c f1.c
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
f1.c
 
#obținem fișierul f2.obj din sursa f2.c
>cl /c f2.c
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
f2.c
 
>cl /c main.c
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
main.c
 
#obținem biblioteca statică intro.lib din f1.obj și f2.obj
>lib /out:intro.lib f1.obj f2.obj
Microsoft (R) Library Manager Version 8.00.50727.42
Copyright (C) Microsoft Corporation.  All rights reserved.
 
#intro.lib este compilat împreună cu main.obj pentru a obține main.exe
>cl main.obj intro.lib
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
Microsoft (R) Incremental Linker Version 8.00.50727.42
Copyright (C) Microsoft Corporation.  All rights reserved.
 
/out:main.exe
main.obj
intro.lib
```

# Windows: Crearea unei biblioteci dinamice:
Simboluri:
* __declspec(dllimport), este folosit pentru a importa o funcție dintr-o bibliotecă. 
* __declspec(dllexport), este folosit pentru a exporta o funcție dintr-o bibliotecă.

Header example:
```
    #ifndef FUNS_H
    #define FUNS_H   1
     
    #ifdef DLL_IMPORTS
    #define DLL_DECLSPEC __declspec(dllimport)
    #else
    #define DLL_DECLSPEC __declspec(dllexport)
    #endif
     
    DLL_DECLSPEC void f1 (void);
    DLL_DECLSPEC void f2 (void);
     
    #endif
```

Astfel, fisierele care vor exporta functii in DLL nu vor declara DLL_IMPORTS iar cele care le vor importa, vor declara:
```
#define DLL_IMPORTS
```
Procesul de compilare:
```
>cl /LD f1.obj f2.obj
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
Microsoft (R) Incremental Linker Version 8.00.50727.42
Copyright (C) Microsoft Corporation.  All rights reserved.
 
/out:f1.dll
/dll
/implib:f1.lib
f1.obj
f2.obj
   Creating library f1.lib and object f1.exp
 
>cl main.obj f1.lib
Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86
Copyright (C) Microsoft Corporation.  All rights reserved.
 
Microsoft (R) Incremental Linker Version 8.00.50727.42
Copyright (C) Microsoft Corporation.  All rights reserved.
 
/out:main.exe
main.obj
f1.lib
```

Alternativ, biblioteca poate fi obtinuta cu ajutorul comenzii link:
```
>link /nologo /dll /out:intro.dll /implib:intro.lib f1.obj f2.obj
  Creating library intro.lib and object intro.exp
 
>link /nologo /out:main.exe main.obj intro.lib
 
>main.exe
Current file name is f1.c
Current line 6 in file f2.c
```
