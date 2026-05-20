# 填空实现下面的深拷贝函数deepcopy

# def deepcopy(a):
# // 在此处补充你的代码
# a = [1,2,[3,[4],5],(6,[7,[8],9])]
# b = deepcopy(a)
# print(b)
# a[2][1].append(400)
# a[3][1][1].append(800)
# print(a)
# print(b)
# 输入
# 无
# 输出
# [1, 2, [3, [4], 5], (6, [7, [8], 9])]
# [1, 2, [3, [4, 400], 5], (6, [7, [8, 800], 9])]
# [1, 2, [3, [4], 5], (6, [7, [8], 9])]
# 样例输入
# 无
# 样例输出
# [1, 2, [3, [4], 5], (6, [7, [8], 9])]
# [1, 2, [3, [4, 400], 5], (6, [7, [8, 800], 9])]
# [1, 2, [3, [4], 5], (6, [7, [8], 9])]
def deepcopy(a):
    if isinstance(a,list):
        return [deepcopy(x) for x in a]
    elif isinstance(a,tuple):
        return tuple(deepcopy(x) for x in a)
    else:
        return a
a = [1,2,[3,[4],5],(6,[7,[8],9])]
b = deepcopy(a)
print(b)
a[2][1].append(400)
a[3][1][1].append(800)
print(a)
print(b)
#本题是实现一个deepcopy，在python中，所有的变量都是指针，如果直接对列表这种可交换元素直接=，会导致只发生浅拷贝
#因此我们需要采取递归方法来实现：
#1.若列表中的元素只是单个基本类型的元素，it is immutable,so we can just return it
#2.if the element is a list or tuple,we use the recursive method to split the element into fundamental element
