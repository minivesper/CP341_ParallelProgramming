import sys
import os.path
from drawer import *

def parseLine(line):
    line = line[:-1]
    vals = line.split(",")
    return vals

def drawFrame(ibodies, pic_name):
    for b in ibodies:
        drawCircle(float(b[1]),float(b[2]),float(b[5]),(0,0,0))
    pn = "./out/" + str(pic_name) + ".png"
    saveImage(pn)

def main():
    if len(sys.argv) < 2:
        print("requires directory as second argument")
    elif not os.path.isdir(sys.argv[1]):
        print("second argument must be a directory")


    files = []
    for f in os.listdir(sys.argv[1]):
        fname = "./data/"
        fname += f
        files.append(fname)

    for fname in files:
        createImage(1000,1000)
        f = open(fname)
        ibodies = []
        f.readline()
        pic_name = int(f.readline())
        for line in f:
            ibodies.append(parseLine(line))
        drawFrame(ibodies,pic_name)


if __name__ == '__main__':
    main()
