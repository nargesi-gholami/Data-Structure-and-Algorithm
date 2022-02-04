def check(i,j,puzzle_size, one_col, one_row):
    if (one_row[i] == puzzle_size or one_col[j] == puzzle_size):
        return False
    else:
        return True

def puzzle_output(i,j,puzzle_size, zero_row, zero_col):
    if zero_row > 0 or zero_col > 0:
        return False
    else:
        return True

puzzle_size = input()
puzzle_size = int(puzzle_size)
one_col = ([0]*puzzle_size)
one_row = ([0]*puzzle_size)
zero_row = puzzle_size
zero_col = puzzle_size
global end
end = True
for k1 in range(puzzle_size):
    for k2 in range(puzzle_size):
        input_text = input()
        i, j = input_text.split()
        i = int(i)-1
        j = int(j)-1
        if (one_row[i] == 0):
            zero_row -= 1
        one_row[i] += 1
        if (one_col[j] == 0):
            zero_col -= 1
        one_col[j] += 1
        if(end):
            end = check(i,j,puzzle_size, one_col, one_row)
            if puzzle_output(i,j,puzzle_size, zero_row, zero_col) and end:
                print("LOVELY")
            else:
                print("HIDEOUS")
        else:
            print("HIDEOUS")