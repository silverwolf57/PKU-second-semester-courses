# // 输入一个n行m列的矩阵A，输出它的转置AT。

# // 输入
# // 第一行包含两个整数n和m，表示矩阵A的行数和列数。1 <= n <= 100，1 <= m <= 100。
# // 接下来n行，每行m个整数，表示矩阵A的元素。相邻两个整数之间用单个空格隔开，每个元素均在1~1000之间。
# // 输出
# // m行，每行n个整数，为矩阵A的转置。相邻两个整数之间用单个空格隔开。
# // 样例输入
# // 3 3
# // 1 2 3
# // 4 5 6
# // 7 8 9
# // 样例输出
# // 1 4 7
# // 2 5 8
# // 3 6 9
m,n=map(int,input().split())
lst=[[0 for j in range(n)]for i in range(m)]
for i in range(m):
    row=list(map(int,input().split()))
    for j in range(n):
        lst[i][j]=row[j]
for j in range(n):
    for i in range(m):
        print(lst[i][j],end=" ")
    print()
#這道題的主要問題是：
#1.處理矩陣輸入。由於Input.split會返回一個列表，我們需要用map來轉換爲Int
#2.初始化列表。這裏最好用列表初始化表達式。
#3.輸出。轉置輸出意味著要交換循環順序，同時由於Print輸出完會自動換行，要加入end來分割
#更好的初始化代碼如下：
# m,n=map(int,input().split())
# lst=[list(map(int,input().split())) for _ in range(m)]


