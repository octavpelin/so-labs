#ifndef FUNS_H
#define FUNS_H 1

#ifdef DLL_IMPORTS
#define DLL_DECLSPEC __declspec(dllimport)
#else
#define DLL_DECLSPEC __declspec(dllexport)
#endif

DLL_DECLSPEC void f1(void);
DLL_DECLSPEC void f2(void);

#endif