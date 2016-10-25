#!/usr/bin/env python3
from math import sqrt
def test(lista:list)->int:
    suma=0
    for i in lista:
        try: #esto esa asi, si tiene la posicion 2 de la terna no tira error, si tira erro es por q no está entonces es una pokeparada
            suma-=i[2]
        except:
            suma+=3
    return suma
def distancias(lista:list)->float:
    suma=0
    prev=lista[0]
    for i in lista:
        suma+=sqrt((i[0]-prev[0])**2 +(i[1]-prev[1])**2) # ** = potencia
    return suma

def tirarPokeParadas(pokeParadas:list,gimnasios:list,k:int)->tuple: #lista, lista
    """
    Esto lo que hace es armar un nuevo array tal que tenga el orden de los gimnasios tal cual le llego pero antes de cada gimnasio
    tenes la cantidad necesaria de pokeparadas y las mas cercanas a ese gimnasio, luego son descartadas y si hay un gimnasio con esa pokeparada q le quede mas convenientemente,
    no la va a tomar en cuenta
    """
    suma=0
    res=[]
    for gym in gimnasios:
        while(suma<gym[2]):
            suma+=3
            if(suma>k):
                suma=k
            pokeParadas=sorted(pokeParadas, key=lambda pokeParada: -sqrt((gym[0]-pokeParada[0])**2 +(gym[1]-pokeParada[1])**2))
            res.append(pokeParadas.pop())
        res.append(gym)
        suma-=gym[2]
    for p in pokeParadas:
        res.append(p)
    return res,distancias(res)


#main
n,m,k= tuple(map(int, input().split())) #toma n m y k como integers
gimnasios=[tuple(map(int, input().split())) for _ in range(n)] #toma los gimnasios como ternas de ints
pokeParadas=[tuple(map(int, input().split())) for _ in range(m)] #toma las pokeparadas como tuplas de its
gimnasios=sorted(gimnasios, key= lambda gimnasio: gimnasio[2]) #ordena por el peso del gimnasio
print("Caso A: gimnasios ordenados de menor a mayor",tirarPokeParadas(pokeParadas,gimnasios,k))
print("Caso B: gimnasios ordenados de mayor a menor",tirarPokeParadas(pokeParadas,reversed(gimnasios),k))
"""
3 4 5
0 1 5
0 3 3
0 6 3
0 0
0 2
0 4
0 5
"""
