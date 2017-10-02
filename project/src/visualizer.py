import sys
import os.path
import drawer

def parseLine(line):
    line = line[:-1]
    vals = line.split(",")
    return vals

def drawFrame(ibodies):
    for b in ibodies:
        return 0
        #draw happens here

def main():
    if len(sys.argv) < 2:
        print("requires directory as second argument")
    elif not os.path.isdir(sys.argv[1]):
        print("second argument must be a directory")

    createImage(400,600)
    
    files = []
    for f in os.listdir(sys.argv[1]):
        fname = "./data/"
        fname += f
        files.append(fname)

    for fname in files:
        f = open(fname)
        ibodies = []
        for line in f:
            ibodies.append(parseLine(line))
        drawFrame(ibodies)


if __name__ == '__main__':
    main()
