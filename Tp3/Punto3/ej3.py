#!/usr/bin/env python3
from math import sqrt
def test(lista:list):
    suma=0
    for i in lista:
        try: #esto esa asi, si tiene la posicion 2 de la terna no tira error, si tira erro es por q no está entonces es una pokeparada
            suma-=i[2]
        except:
            suma+=3
    return suma
def distancias(lista:list):
    suma=0
    prev=lista[0]
    for i in lista:
        suma+=sqrt((i[0]-prev[0])**2 +(i[1]-prev[1])**2) # ** = potencia
    return suma

def tirarPokeParadas(pokeParadas:list,gimnasios:list,k:int):
    """
    Esto lo que hace es armar un nuevo array tal que tenga el orden de los gimnasios tal cual le llego pero antes de cada gimnasio
    tenes la cantidad necesaria de pokeparadas y las mas cercanas a ese gimnasio, luego son descartadas y si hay un gimnasio con esa pokeparada q le quede mas convenientemente,
    no la va a tomar en cuenta
    """
    suma=0
    res=[]
    for gym in gimnasios:
        while(suma<gym[2]):
            if len(pokeParadas) <1:()
                return -1
            suma+=3
            if(suma>k):
                suma=k
            pokeParadas=sorted(pokeParadas, key=lambda pokeParada: -sqrt((gym[0]-pokeParada[0])**2 +(gym[1]-pokeParada[1])**2))
            res.append(pokeParadas.pop())
        res.append(gym)
        suma-=gym[2]
    for p in pokeParadas:
        res.append(p)
    #return res,
    return distancias(res)

def copiaSwapeada(lista,pos_uno, pos_dos):
    copia = list(lista)
    copia[pos_uno] , copia[pos_dos] =lista[pos_dos],lista[pos_uno]
    return copia
def vecinitud (lista):
    n = len(lista)
    return [(i,j) for i in range(n) for j in range(n) if j!=i]
#main   X
n,m,k= tuple(map(int, input().split())) #toma n m y k como integers
gimnasios=[tuple(map(int, input().split())) for _ in range(n)] #toma los gimnasios como ternas de ints
pokeParadas=[tuple(map(int, input().split())) for _ in range(m)] #toma las pokeparadas como tuplas de its
#gimnasios=sorted(gimnasios, key= lambda gimnasio: gimnasio[2]) #ordena por el peso del gimnasio

tuplasVecinos= [(i,j) for i in range(n) for j in range(n) if j!=i]
actual = (gimnasios, tirarPokeParadas(pokeParadas, gimnasios, k))
mejora = True
while (mejora):
    vecindad = [(copiaSwapeada(actual[0], tupla[0], tupla[1]), tirarPokeParadas(pokeParadas,copiaSwapeada(actual[0], tupla[0], tupla[1]),k)) for tupla in tuplasVecinos ]
    vecindad = [(i,j) for i,j in vecindad if j!=-1]
    minim = min(vecindad, key=lambda res: res[1])
    mejora= minim[1]< actual[1]
    if(mejora):
        actual=minim
print(actual)

#print("Swapeo: "+str(tupla)+"=> ",tirarPokeParadas(pokeParadas,gimnasiosAA,k))
"""
5 9 10
0 1 5
0 3 3
0 6 3
1 7 10
20 20 5
1 1
7 2
0 0
0 2
0 4
0 5
7 7
9 1
200 200
"""
