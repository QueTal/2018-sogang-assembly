import sys

def read_mapper_output(file):
        for line in file:
                yield line.split('\t')

def main():
        data = read_mapper_output(sys.stdin)

        maxN = {}

        for line in data:
                if line[0] in maxN.keys() : maxN[line[0]] = max(float(line[1]),maxN[line[0]])
                else : maxN[line[0]] = float(line[1])

        for i in maxN.keys():
                print("%s\t%f"%(i,maxN[i]))

if __name__ == "__main__":
        main()

