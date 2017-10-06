import sys
import os.path
from drawer import *

def parseLine(line):
    line = line[:-1]
    vals = line.split(",")
    return vals

def drawFrame(ibodies, pic_name):
    for b in ibodies:
        drawCircle(int(b[1]),int(b[2]),int(b[5]),(0,0,0))
    pn = "./out/" + pic_name + ".png"
    saveImage(pn)

def main():
    if len(sys.argv) < 2:
        print("requires directory as second argument")
    elif not os.path.isdir(sys.argv[1]):
        print("second argument must be a directory")

    createImage(600,400)

    files = []
    for f in os.listdir(sys.argv[1]):
        fname = "./data/"
        fname += f
        files.append(fname)

    for fname in files:
        f = open(fname)
        ibodies = []
        f.readline()
        pic_name = f.readline()[0]
        for line in f:
            ibodies.append(parseLine(line))
        drawFrame(ibodies,pic_name)


if __name__ == '__main__':
    main()
