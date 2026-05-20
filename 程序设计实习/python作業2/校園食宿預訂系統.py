# 描述
# 某校园为方便学生订餐，推出食堂预定系统。食宿平台会在前一天提供菜单，学生在开饭时间前可订餐。 食堂每天会推出m个菜，每个菜有固定的菜价和总份数，售卖份数不能超过总份数。
#  假设共有n个学生点餐，每个学生固定点3个菜，当点的菜售罄时, 学生就买不到这个菜了。 
# 请根据学生预定记录，给出食堂总的预定收入 数据满足1 <= n <= 6000，3 <= m <= 6000，单品菜价不大于1000元，每个菜的配额不超过3000

# 输入
# 第一行两个整数n和m，代表有n个学生订餐，共有m个可选的菜
# 下面m行，每行三个元素，分别是菜名、售价和可提供量，保证菜名不重合，菜价为整数
# 下面n行，每行三个元素，表示这个学生点的三个菜的菜名
# 输出
# 一个整数，表示食堂的收入
# 样例输入
# 5 5
# yangroupaomo 13 10
# jituifan 7 5
# luosifen 16 3
# xinlamian 12 20
# juruo_milktea 999 1
# yangroupaomo luosifen juruo_milktea
# luosifen xinlamian jituifan
# yangroupaomo jituifan juruo_milktea
# jituifan xinlamian luosifen
# yangroupaomo yangroupaomo yangroupaomo
# 样例输出
# 1157
# 提示
# 如果用python做，要用字典，
# 如果用其它语言做，也要用类似的数据结构
# 否则会超时
# 名字长度范围没有给出，长度不会太离谱。请自己选用合适的办法确保这不是个问题
m,n=map(int,input().split())
menu={}
for _ in range(n):
    name,cost,num=input().split()
    cost,num=int(cost),int(num)
    menu[name]=[cost,num]
profit=0
for _ in range(m):
    ord1,ord2,ord3=input().split()
    if menu[ord1][1]>=1:
        profit+=menu[ord1][0]
        menu[ord1][1]-=1
    if menu[ord2][1]>=1:
        profit+=menu[ord2][0]
        menu[ord2][1]-=1
    if menu[ord3][1]>=1:
        profit+=menu[ord3][0]
        menu[ord3][1]-=1
print(profit)
#這道題的主要思路很簡單，通過字典來構建菜單，再根據輸入的東西來模擬即可
#優化代碼如下：
#n, m = map(int, input().split())

# menu = {}

# for _ in range(m):
#     name, cost, num = input().split()
#     menu[name] = [int(cost), int(num)]

# total = 0

# for _ in range(n):
#     orders = input().split()

#     for food in orders:
#         if menu[food][1] > 0:
#             total += menu[food][0]
#             menu[food][1] -= 1

# print(total)