t = input()
s = input()
answer = 0
length = len(t)
div = (10 ** 8 + 7)
num = s.count('?')
n = [0]*(num+1)
n[0] = 1
for j in range(num):
    n[j+1] = 10*n[j] % div
k = num
for i in range(length):
    if s[i] == '?':
        k -= 1
        answer += (n[k]*int(t[i])) % div
        continue
    elif int(t[i]) > int(s[i]):
        answer += n[k] % div
        break
    elif int(t[i]) < int(s[i]):
        break;
print((answer % div))
