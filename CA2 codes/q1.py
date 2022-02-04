def count_number(str1):
    count = 1
    q = 1
    for i in range(1 ,len(str1)):
        if str1[i] == '(':
            count += 1
        elif str1[i] == ')':
            count -= 1
        q += 1
        if count == 0:
            return q


def cal(str2):
    sum2 = 0
    brace1 = 0
    brace2 = 0
    q = 0
    i = 0
    str2 += " "
    while i < len(str2) - 1:
        if str2[i] == '(':
            brace1 += 1
            q -= 1
        elif str2[i] == ')':
            brace2 += 1
            q += 1
        elif str2[i + 1] == '(':
            sum2 += int(str2[i]) * cal(str2[i + 1:])
            i += count_number(str2[i + 1:])

        elif str2[i] != '(' and str2[i] != ')':
            sum2 += int(str2[i])
        if q == 0 and brace1 != 0:
            return sum2
        i += 1
    return sum2


str0 = input()
sum0 = cal(str0)
print(sum0)

