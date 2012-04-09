#!/usr/bin/env python
#-*- coding=utf-8 -*-
import math

vctlen = 16
samplelist = []
classlist = []
samplelineno = 0
classlineno = 0

# 采用欧几里德算法
def euclidean(v1,v2):
    d = 0.0
    for i in range(len(v1)):
        d += (int(v1[i])-int(v2[i]))**2
    return math.sqrt(d)

#获取训练样本数据-->samplelist
def sampletrain():
    lines = open("letter.txt",'r').readlines()
    num = []
    for line in lines:
        linestr = line.split()
        templist = []
        templist.append(linestr[0])
        templist.append(map(int,linestr[1:]))
        samplelist.append(templist)
        global samplelineno
        samplelineno += 1

#获取待分类数据-->classlist
def getclass():
    lines = open("sum.txt",'r').readlines()
    for line in lines:
        linestr = line.split()
        templist = []
        templist.append(linestr[0])
        templist.append(map(int,linestr[1:]))
        classlist.append(templist)
        global classlineno
        classlineno += 1



def classify():
    totalnum = 0
    rightnum = 0
    for j in range(classlineno):
        distancelist = []
        totalnum += 1
        for i in range(samplelineno):
             distancelist.append(euclidean(classlist[j][1],samplelist[i][1]))
        if samplelist[distancelist.index(min(distancelist))][0] == classlist[j][0]:
             rightnum += 1
    print '匹配率',float(rightnum)/totalnum

if __name__ =="__main__":
    sampletrain()
    getclass()
    classify()
