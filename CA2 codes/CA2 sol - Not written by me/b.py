PREORDER_TYPE = "Preorder"
MULTIPLY = "*"
PLUS = "+"
NEGATIVE = "-"

def is_operation(char):
    if(char == MULTIPLY or char == NEGATIVE or char == PLUS):
        return True
    return False

def operate(number1, number2, operator):
    if(operator == MULTIPLY):
        return number1 * number2
    elif(operator == PLUS):
        return number1 + number2
    else:
        return number2 - number1

def check_can_operate_preorder(stack):
    while(len(stack) >= 3):
        number1 = stack[-1]
        number2 = stack[-2]
        operator = stack[-3]
        if(is_operation(number1) or is_operation(number2) or is_operation(operator) == False):
            return
        new_number = operate(number1, number2, operator)
        for i in range(0, 3):
            stack.pop()
        stack.append(new_number)

def calculate_preorder(operation):
    stack = []
    for char in operation:
        if(is_operation(char)):
            stack.append(char)
        else:
            stack.append(int(char))
            check_can_operate_preorder(stack)
    check_can_operate_preorder(stack)
    return stack[0]

def check_can_operate_postorder(stack):
    while(len(stack) >= 3):
        number1 = stack[-2]
        number2 = stack[-3]
        operator = stack[-1]
        if(is_operation(number1) or is_operation(number2) or is_operation(operator) == False):
            return
        new_number = operate(number1, number2, operator)
        for i in range(0, 3):
            stack.pop()
        stack.append(new_number)

def calculate_postorder(operation):
    stack = []
    for char in operation:
        if(is_operation(char)):
            stack.append(char)
            check_can_operate_postorder(stack)
        else:
            stack.append(int(char))
    return stack[0]

type = input()
operation = input()
if(type == PREORDER_TYPE):
    print(calculate_preorder(operation))
else:
    print(calculate_postorder(operation))
