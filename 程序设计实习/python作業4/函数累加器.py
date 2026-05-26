# 编写一个函数累加器accfunc



# #pylint: disable = no-value-for-parameter
# def accfunc(f):
# // 在此处补充你的代码
# def f1(x):
#     return x + 1
# def f2(x):
#     return x * x
# def f3(x):
#     return x + x
# def f4(x):
#     return x*3
# def f5(x):
#     return x-4

# while True:
#     try:
#         s = input()
#         n = int(input())
#         s = s.split()
#         k = accfunc
#         for x in s:
#             k = k(eval(x))
#         print(k()(n))
#     except:  #读到 eof产生异常
#         break
# 输入
# 多组数据，每组2行
# 第一行形如：
# p_1 p_2 p_3 ....p_n
# p_i 是个字符串，值是 "f1", "f2", "f3", "f4", "f5" 中间的任何一个，代表程序中相应函数
# 这一行项数不定，至少有1项
# 第二行是个整数x
# 对每组数据，输出以下函数调用的结果:
# p_n(p_n-1(...(p2(p1(x)...)
# 输出
# 对每组数据，输出以下函数调用的结果:

# p_n(p_n-1(...(p2(p1(x)...)
# 样例输入
# f1 f2 f3
# 4
# f2
# 5
# f2 f2 f5
# 3
# 样例输出
# 50
# 25
# 77

# 提示
# 第一个例子，输出结果是 f3(f2(f1(4)))
# 第二个例子，输出结果是 f2(5)

#pylint: disable = no-value-for-parameter
def accfunc(f):
    def acc(y=None):
        if y!=None:
            return accfunc(lambda x:y(f(x)))
        else:
            return f
    return acc
def f1(x):
    return x + 1
def f2(x):
    return x * x
def f3(x):
    return x + x
def f4(x):
    return x*3
def f5(x):
    return x-4

while True:
    try:
        s = input()
        n = int(input())
        s = s.split()
        k = accfunc
        for x in s:
            k = k(eval(x))
        print(k()(n))
    except:  #读到 eof产生异常
        break