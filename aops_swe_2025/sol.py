#!/usr/bin/python3

import sys  



# reading the input from a file
def read_input(file):
    with open(file, 'r') as f:
        return f.read().splitlines()

# input list of lines in the input file
# output a list of lists where the ith row has i elements
def process_input(lines):
    first_line = lines[0]
    try:
        words = first_line.split(" ")
        target = int(words[1])

    except ValueError:
        sys.exit("Invalid first line. Format the first line like 'Target: n', where n is the target number")

    
    pyramid = []

    for line in lines[1:]:
        numbers = line.split(",")
        row = [int(num) for num in numbers]
        
        pyramid.append(row)

    return pyramid, target


# actual algorithm (DP approach)
# want to store information about product and direction took for each node in the pyramid
def solve(pyramid, target):
    path_product = []

    # adding the 0th row
    path_product.append([])

    # adding the 0, 0th entry (which is a list of just the first node, and empty directions)
    path_product[0].append([ (pyramid[0][0], "")])
   
    for r in range(1, len(pyramid)):
        row = []
        for c in range(len(pyramid[r])):
            # print(f"Row: {r}, Col: {c}")
            # print(path_product)

            # contains tuples of direction and product
            rc_product = [ ]

            # if we can go right (taking the r-1, c-1 element in path product)
            if c > 0 and c != r:
                # multiply by current value, add L to the old tuple
                right = [(pair[0] * pyramid[r][c], pair[1] + "R") for pair in path_product[r-1][c-1]]
                for pair in right:
                    rc_product.append(pair)
            # other wise, we can only go left, so we get the r-1, c element
            elif c == 0:
                left = [(path_product[r-1][c][0][0] * pyramid[r][c], path_product[r-1][c][0][1] + "L")]
                rc_product.append(left[0])

            # if we cant go left to get to this node, we have to be at the end
            if c == r:
                right = [(path_product[r-1][c-1][0][0] * pyramid[r][c], path_product[r-1][c-1][0][1] + "R")]
                rc_product.append(right[0])
            # Other wise we can go left
            elif c < r and c != 0: 
                right = [(pair[0] * pyramid[r][c], pair[1] + "L") for pair in path_product[r-1][c]]
                for pair in right:
                    rc_product.append(pair)
    
            row.append(rc_product)
        path_product.append(row)


    flat_path_product = [pp for row in path_product for col in row for pp in col]
    # print(flat_path_product)

    pair = [pp for pp in flat_path_product if pp[0] == target]
   
    if(len(pair) == 0):
        sys.exit("No Pair Found")

    return pair[0][1]

# Assume that the file is in the correct format
def main():
    file = input("Enter file name: ")
    lines = read_input(file)
    pyramid, target = process_input(lines)

    result = solve(pyramid, target)
    sys.stdout.write(result + "\n")

if __name__ == "__main__":
    main()
