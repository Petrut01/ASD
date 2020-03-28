import random,time,copy

def bubbleSort(arr):
    n = len(arr)
    if n>3000:
        return 0
    else:
        rez = [x for x in arr]
        for i in range(n):
            for j in range(0, n - i - 1):
                if rez[j] > rez[j + 1]:
                    rez[j], rez[j + 1] = rez[j + 1], rez[j]
    return rez


def merge_lists(lst, ldr):
    i = j = 0
    rez = []
    while i < len(lst) and j < len(ldr):
        if lst[i] <= ldr[j]:
            rez.append(lst[i])
            i += 1
        else:
            rez.append(ldr[j])
            j += 1
    rez.extend(lst[i:])
    rez.extend(ldr[j:])
    return rez

def merge_sort(ls):
    if len(ls) <= 1:
        return ls
    else:
        mij = len(ls) // 2
        lst = merge_sort(ls[:mij])
        ldr = merge_sort(ls[mij:])
        return merge_lists(lst, ldr)


def CountSort (v):
    aux=v[:]
    if aux!=[]:
        if (max(aux) > 4500000):
            return 0
        else:
            frecv = [ 0 for i in range (max(aux)+1) ]
            for x in aux:
                frecv[x] += 1
            rez = []
            for x in range(max(v)+1):
                while frecv[x] != 0:
                    rez.append(x)
                    frecv[x] -= 1
            return rez
    else:
        return v


def alegere_pivot(l):
    if (len(l)<=5):
        return l[len(l)//2]
    else:
        med=[]
        A=[l[i:i+5] for i in range (0,len(l),5)]
        for sl in A:
            med.append(sl[len(sl)//2])
    return alegere_pivot(med)


def quicksort(l):
    if len(l)>200000:
        return 0
    else:
        less = []
        equal = []
        greater = []

        if len(l) > 1:
            pivot = alegere_pivot(l)
            for x in l:
                if x < pivot:
                    less.append(x)
                elif x == pivot:
                    equal.append(x)
                elif x > pivot:
                    greater.append(x)

            return quicksort(less) + equal + quicksort(greater)

        else:
            return l

def RadixSort (v):
    if v!=[]:
        if len(v)>300000:
            return 0
        else:
            l = max(v)
            l = len(str(l))
            p = 1
            rez = [ x for x in v]
            for i in range (l):
                C = [[] for x in range(10)]
                for x in rez:
                    C[x // p % 10 ].append(x)
                rez = []
                for x in C:
                    rez.extend(x)
                p *= 10
            return rez
    else:
        return v

def Verificare (v, l):
    if len(v) != len(l):
        return False
    else:
        l.sort()
        for i in range ( len(v)):
            if v[i] != l[i]:
                return False
    return True

def generator_nr_mari(n):
    l=[]
    for i in range(n):
        l.append(random.randint(100000,500000000000))
    return l

def generator_nr_mici(n):
    l=[]
    for i in range(n):
        l.append(random.randint(1,100))
    return l


l1=[]
l2=generator_nr_mari(3000)
l3=generator_nr_mici(100000)
l4=generator_nr_mari(200000)
l5=[int(x) for x in range(1000)]

teste = [l1,l2,l3,l4,l5]


for i in teste:
    aux=i[:]
    init_time=time.time()
    a=bubbleSort(i)
    fin_time=time.time()
    i=aux
    if a==0:
        print("Dimensiunea vectorului este prea mare")
    elif Verificare(a, i):
        print("Bubble sort ruleaza in ", fin_time-init_time, "secunde")
    else:
        print("Sortare incorecta")

print('\n')


for i in teste:
    aux=i[:]
    init_time=time.time()
    a=CountSort(i)
    fin_time=time.time()
    i=aux
    if a==0:
        print("Valoare maxima prea mare")
    else:
        if Verificare(a, i):
            print("Count sort ruleaza in ", fin_time-init_time, "secunde")
        else:
            print("Sortare incorecta")
print('\n')


for i in teste:
    aux = i[:]
    init_time=time.time()
    a=merge_sort(i)
    fin_time=time.time()
    i = aux
    if a==0:
        print("Nu se executa sortarea")
    else:
        if Verificare(a,i):
            print("Merge sort ruleaza in ", fin_time-init_time, "secunde")
        else:
            print("Sortare incorecta")
print('\n')



for i in teste:
    aux = i[:]
    init_time=time.time()
    a=RadixSort(i)
    fin_time=time.time()
    i = aux
    if a==0:
        print("Nu se executa sortarea")
    else:
        if Verificare(a,i):
            print("Radix sort ruleaza in ", fin_time-init_time, "secunde")
        else:
            print("Sortare incorecta")


print('\n')


for i in teste:
    aux = i[:]
    init_time=time.time()
    a=quicksort(i)
    fin_time=time.time()
    i = aux
    if a==0:
        print("Dimensiunea vectorului este prea mare")
    elif Verificare(a, i):
        print("Quick sort ruleaza in ", fin_time-init_time, "secunde")
    else:
        print("Sortare incorecta")

print('\n')

for i in teste:
    aux = i[:]
    init_time=time.time()
    i.sort()
    fin_time=time.time()
    i = aux
    print("Sortarea din python ruleaza in ", fin_time-init_time, "secunde")
