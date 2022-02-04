import sys
sys.setrecursionlimit(100000)

def find_island(row,col):
    land_array = [[0 for n in range(col)] for m in range(row)]
    for i in range(row):
        row_string = input().split()
        for j in range(col):
            land_array[i][j] = row_string[j]
    counter = 0
    for i in range(row):
        for j in range(col):
            if land_array[i][j] == '1':
                counter += 1
                search_island(land_array,i, j, row, col)
    print(counter)

def search_island(land_array,i, j, row, col):
    land_array[i][j] = '2'
    if i-1 >= 0:
        if land_array[i-1][j] == '1':
            search_island(land_array,i-1, j, row, col)
    if i+1 < row:
        if land_array[i+1][j] == '1':
            search_island(land_array,i+1, j, row, col)
    if j-1 >= 0:
        if land_array[i][j-1] == '1':
            search_island(land_array,i, j-1, row, col)
    if j+1 < col:
        if  land_array[i][j+1] == '1':
            search_island(land_array,i, j+1, row, col)

land_size = input()
row, col = land_size.split()
row = int(row)
col = int(col)
find_island(row, col)


