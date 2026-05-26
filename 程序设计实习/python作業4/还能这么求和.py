# 程序填空 程序先输出10(10=1+2+3+4),30， 然后读入若干整数，并输出它们的和

# def mysum(x):
# // 在此处补充你的代码
# def exec(g,i) : #call g for i times
#     if i == 1 :
#         g()
#     else:
#         g()
#         exec(g,i-1)

# k = mysum(1)(2)(3)(4)
# k2 = mysum(10)(20)

# print(k())
# print(k2())

# while True:
#     try:
#         s = input()
#         s = s.split()
#         k = mysum
#         for x in s:
#             k = k(int(x))
#         exec(k,int(s[0]))
#         print(k())
#     except:  #读到 eof产生异常
#         break
# 输入
# 多组数据，每组一行，包括不超过100个整数（至少一个），其中第一个整数一定大于0。
# 输出
# 对每组数据，输出所有整数的和
# 样例输入
# 1 2 3
# 4 5
# 样例输出
# 10
# 30
# 6
# 9
def mysum(x):
    def adder(y=None):
        if y is None:
            return x
        return mysum(x + y)
    return adder
def exec(g,i) : #call g for i times
    if i == 1 :
        g()
    else:
        g()
        exec(g,i-1)

k = mysum(1)(2)(3)(4)
k2 = mysum(10)(20)

print(k())
print(k2())

while True:
    try:
        s = input()
        s = s.split()
        k = mysum
        for x in s:
            k = k(int(x))
        exec(k,int(s[0]))
        print(k())
    except:  #读到 eof产生异常
        break
#这题依旧是要使用闭包来解决问题
#但如果只使用闭包，会导致后面链式调用和无参调用出问题
#因此这个闭包函数必须非常特殊
#于是我们加上形式参数y，用来实现没有参数就返回值的功能，以及有参数就返回函数本身，从而可以实现链式调用的功能
