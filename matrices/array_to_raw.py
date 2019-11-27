import sys

def main():
    input_filename = sys.argv[1];
    arr = ""
    with open(input_filename, 'r') as content:
        arr = content.read()
        out = open(input_filename.split('.')[0] + "_raw.txt", 'w')

        #print dimension of filters
        dims = (arr.split('=')[0]).split('[')[2:]
        dims = [dim.strip(' ]') for dim in dims]
        for dim in dims:
            out.write(dim + '\n')

        arr = arr.split('=')[1]
        arr = arr.split('32\'d')[1:]
        # realign negative signs properly
        last_minus = 0
        for i in range(len(arr)):
            last_minus = arr[i].rfind("-")
            if (last_minus > 0):
                arr[i] = arr[i][:last_minus] + arr[i][last_minus+1:]
                arr[i+1] = '-' + arr[i+1]

        arr = [word.strip(' ,}{;\n') for word in arr]

    for word in arr:
        out.write(word + ' ')

    out.close()

if __name__ == "__main__":
    main()
