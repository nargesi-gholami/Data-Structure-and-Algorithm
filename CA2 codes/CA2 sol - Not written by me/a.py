PARANTHESES_OPEN = '('
PARANTHESES_CLOSE = ')'

def run_new_parantheses(stack):
    sum_numbers = 0
    last_digit = 0
    if(stack[-1] != PARANTHESES_OPEN):
        last_digit = stack[-1]
        stack.pop()
    while(stack[-1] != PARANTHESES_OPEN):
        sum_numbers += stack[-1]
        stack.pop()
    stack.pop()
    number_repeat = stack[-1]
    if(number_repeat == PARANTHESES_OPEN or number_repeat == PARANTHESES_CLOSE):
        stack.append(sum_numbers)
        stack.append(last_digit)
        return
    stack.pop()
    if(number_repeat == 0):
        return
    stack.append(number_repeat * sum_numbers + (number_repeat - 1) * last_digit)
    stack.append(last_digit)

input_string = input()
stack = [1, PARANTHESES_OPEN]
for char in input_string:
    if(char == PARANTHESES_CLOSE):
        run_new_parantheses(stack)
    elif(char == PARANTHESES_OPEN):
        stack.append(PARANTHESES_OPEN)
    else:
        stack.append(int(char))
run_new_parantheses(stack)
sum_all = 0
for number in stack:
    sum_all += number
print(sum_all)
