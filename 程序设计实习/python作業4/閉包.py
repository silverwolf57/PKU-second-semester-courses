# 描述
# 程序填空，完成函数cons

# 按要求输出结果

# def cons(x,y):
# 	s = a = b = None #防止作弊用
# // 在此处补充你的代码
# s = input().split()
# a,b = s[0],s[1]
# pair = cons(a,b)
# print(pair(int(input())))
# 输入
# 第一行是两个字符串,用空格隔开
# 第二行是一个整数n
# 输出
# 如果n 为0，则输出第一个字符串
# 如果n 为1，则输出第二个字符串
# 如果n 为其它数，则输出error
# 样例输入
# #样例1：
# 13 5
# 0
# #样例2：
# 4 aa
# 1
# #样例3：
# bd c
# 7
# 样例输出
# #样例1：
# 13
# #样例2：
# aa
# #样例3：
# error
def cons(x,y):
	s = a = b = None #防止作弊用
	def f(n):
		if n==1:
			return y
		elif n==0:
			return x
		else:
			return 'error'
	return f
s = input().split()
a,b = s[0],s[1]
pair = cons(a,b)
print(pair(int(input())))