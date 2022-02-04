FOR_BEGIN = "For"
FOR_END = "Endfor"
WHILE_BEGIN = "While"
WHILE_END = "Endwhile"
TYPEFOR_BEGIN = "("
TYPEWHILE_BEGIN = "["
TYPEFOR_END = ")"
TYPEWHILE_END = "]"

def generate_map_list(number_lines):
    line_from_last_loop = 0
    new_list = []
    special_strings = [FOR_BEGIN, WHILE_BEGIN, FOR_END, WHILE_END]
    for i in range(0, number_lines):
        new_line = input()
        if(new_line in special_strings):
            if(line_from_last_loop):
                new_list.append(line_from_last_loop)
        if(new_line == FOR_BEGIN):
            new_list.append(TYPEFOR_BEGIN)
        elif(new_line == WHILE_BEGIN):
            new_list.append(TYPEWHILE_BEGIN)
        elif(new_line == FOR_END):
            new_list.append(TYPEFOR_END)
        elif(new_line == WHILE_END):
            new_list.append(TYPEWHILE_END)
        else:
            line_from_last_loop += 1
        if(new_line in special_strings):
            line_from_last_loop = 0
    if(line_from_last_loop):
        new_list.append(line_from_last_loop)
    return new_list

def handle_end_char(char, stack, index, can_be_match):
    if(len(stack) == 0):
        stack.clear()
        return
    if(stack[-1][0] == TYPEFOR_BEGIN and char == TYPEFOR_END):
        can_be_match[stack[-1][1]] = True
        can_be_match[index] = True
        stack.pop()
    elif(stack[-1][0] == TYPEWHILE_BEGIN and char == TYPEWHILE_END):
        can_be_match[stack[-1][1]] = True
        can_be_match[index] = True
        stack.pop()
    else:
        stack.clear()

def generate_partial_sum(new_list):
    partial_sum = []
    special_strings = [TYPEFOR_BEGIN, TYPEFOR_END, TYPEWHILE_END, TYPEWHILE_BEGIN]
    for i in range(0, len(new_list)):
        inc = 0
        if(new_list[i] in special_strings):
            inc = 1
        else:
            inc = new_list[i]
        if(i == 0):
            partial_sum.append(inc)
        else:
            partial_sum.append(partial_sum[-1] + inc)
    return partial_sum

number_lines = int(input())
number_no_loop = 0
new_list = generate_map_list(number_lines)
stack = []
can_be_match = [False for i in range(0, len(new_list))]
for i in range(0, len(new_list)):
    start_strings = [TYPEFOR_BEGIN, TYPEWHILE_BEGIN]
    end_strings = [TYPEWHILE_END, TYPEFOR_END]
    if(new_list[i] in start_strings):
        if(new_list[i] == TYPEFOR_BEGIN):
            stack.append((TYPEFOR_BEGIN, i))
        else:
            stack.append((TYPEWHILE_BEGIN, i))
    elif(new_list[i] in end_strings):
        handle_end_char(new_list[i], stack, i, can_be_match)
    else:
        can_be_match[i] = True
number_for = 0
end = 0
start = 0
answer = 0
start_now = 0
partial_sum = generate_partial_sum(new_list)
for i in range(0, len(new_list)):
    if(can_be_match[i] != False):
        end_now = partial_sum[i]
        if(answer < number_for or (end_now - start_now > end - start and answer == number_for)):
            answer = number_for
            end = end_now
            start = start_now
    else:
        start_now = partial_sum[i]
        number_for = 0
    if(new_list[i] == TYPEFOR_BEGIN and can_be_match[i] == True):
        number_for += 1

print(answer, start, end)
