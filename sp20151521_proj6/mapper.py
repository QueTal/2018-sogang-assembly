import sys

def read_input(file):
        for line in file:
                yield line.split(',')

def main(separator='\t'):
        data = read_input(sys.stdin)

        for line in data:
                print("%s%s%f"%(line[0],separator,float(line[1])))

if __name__ == "__main__":
        main()
