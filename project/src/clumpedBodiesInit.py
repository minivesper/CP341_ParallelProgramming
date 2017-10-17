import sys
import random

def genCluster(body_num, centerX, centerY,outfname):
    f = open(outfname, "a")
    f.write("1000000,"+centerX+","+centerY+",0,0,20\n")
    for b in range(int(body_num)):
        body = ""
        body += str(2) + ","
        if b%4 == 0:
            body += str(int(centerX) + random.randint(50, 600)) + ","
            body += str(int(centerY) + random.randint(0,0)) + ","
            body += str(random.randint(0,0)) + ","
            body += str(random.randint(-150,-50)) + ","
        else:
            body += str(int(centerX) + random.randint(-600, -50)) + ","
            body += str(int(centerY) + random.randint(0,0)) + ","
            body += str(random.randint(0,0)) + ","
            body += str(random.randint(50,150)) + ","
        body += str(1) + "\n"
        f.write(body)

def main():
    if len(sys.argv) < 4 or  len(sys.argv)%3 != 2:
        print("usage: <string> write_filename <int> c1 num_bodies <int> c1_center_x <int> c1_center_y ...")

    clusters = []
    for i in range(2,len(sys.argv)-1):
        if(i%3 == 2):
            x = [sys.argv[i],sys.argv[i+1],sys.argv[i+2]]
            clusters.append(x)

    for c in clusters:
        genCluster(c[0],c[1],c[2],sys.argv[1])

if __name__ == '__main__':
    main()
