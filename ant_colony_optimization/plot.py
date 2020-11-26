import matplotlib.pyplot as plt
import sys
import os
import pandas as pd

def load(path):
    if(not os.path.exists(path)):
        print(path + "not exists ")
        sys.exit()
    ls = []
    with open(path) as file:
        for line in file:
            if line != "\n":
                ls.append(float(line.strip()))
    return ls

def toW(string):
    if not isinstance(string,str):
        print("param should be str")
        sys.exit()
    words_ls = string.split(" ")
    while "" in words_ls:
        words_ls.remove("")
    return words_ls

def load_road(path):
    if(not os.path.exists(path)):
        print(path + " not exists!")
        sys.exit()
    ls = []
    with open(path) as file:
        line = file.readline()
        cities = toW(line)
        for it in cities:
            ls.append(int(it.strip()))
    return ls

class city:
    def __init__(self,x_,y_):
        if isinstance(x_,float):
            self.x = x_
        else :
            print("x should be float")
            sys.exit()
        if isinstance(y_,float):
            self.y = y_
        else :
            print("y should be float")
            sys.exit()

def load_city(path):
    if(not os.path.exists(path)):
        print(path + " not exists!")
        sys.exit()
    ls = []
    with open(path) as file:
        for line in file:
            if line != "\n":
                line = line.strip()
                x,y= toW(line)
                x = float(x)
                y = float(y)
                ls.append(city(x,y))
    return ls

if __name__ == '__main__':
    path = load_road("data/res")
    print("path len -> {}".format(len(path)))
    cs = load_city("data/countries")
    fig,aix = plt.subplots(1,2)
    for i in range(len(path)-1) :
        aix[0].plot([cs[path[i]].x,cs[path[i+1]].x],[cs[path[i]].y,cs[path[i+1]].y])
    aix[0].plot([cs[path[0]].x,cs[path[len(path)-1]].x],[cs[path[0]].y,cs[path[len(path)-1]].y])
    val_ls = load("distance")
    aix[1].plot(list(range(len(val_ls))),val_ls)
    plt.savefig("two-figure.png")