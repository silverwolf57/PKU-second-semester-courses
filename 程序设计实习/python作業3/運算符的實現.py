# class A:
# 	def __init__(self,x):
# 		self.x = x
# // 在此处补充你的代码
# a,b,c = map(int,input().split())
# print(isinstance(A(2),A))
# print(A(a) < A(b))
# print(A(a) >= A(c))
# print(A(a) < c)
# 输入
# 输入三个整数a,b,c
# 输出
# 先输出一行True
# 然后
# 依次输出 a < b， a >= c , a < c 三个表达式的值(True或False)
# 样例输入
# 2 8 5
# 样例输出
# True
# True
# False
# True
class A:
	def __init__(self,x):
		self.x = x
	def __lt__(self,other):
		if(isinstance(other,A)):
			return self.x<other.x
		else:
			return self.x<other
	def __ge__(self,other):
		return self.x>=other.x
a,b,c = map(int,input().split())
print(isinstance(A(2),A))
print(A(a) < A(b))
print(A(a) >= A(c))
print(A(a) < c)
