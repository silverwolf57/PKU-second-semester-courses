# 一副扑克牌有52张牌，分别是红桃，黑桃，方片，梅花各13张，不包含大小王，现在Alex抽到了n张牌，请将扑克牌按照牌面从大到小的顺序排序。
# 牌的表示方法：
# 红桃(heart)用字母h表示
# 黑描述
# 一桃(spade)用字母s表示
# 方片(dianmond)用字母d表示
# 梅花(club)用字母c表示
# 2~10的牌面直接用2,3,4,5,6,7,8,9,10 表示，其余的分别为A，J，Q，K
# 比如方片J用dJ表示， 红桃A用hA表示
# 牌面大小：
# 2>A>K>Q>J>10>9>……>4>3
# 相同牌面的按照花色（h>s>d>c）顺序排。
# 输入
# 多组数据。每组数据一行，表示当前摸到的n张牌（1 < n <=52）。
# 输出
# 针对每组数据，输出一行，即排序后的结果。
# 样例输入
# h7 c10 h4 s7 c5 cA dA c4 sJ h9 hQ d8 h2 s2 d9 sA dQ c6 hA
# h7 s8 s7 c5 c8 cK sQ d2 s3 hQ d8 s10 sA d5 h10 hA
# 样例输出
# h2 s2 hA sA dA cA hQ dQ sJ c10 h9 d9 d8 h7 s7 c6 c5 h4 c4 
# d2 hA sA cK hQ sQ h10 s10 s8 d8 c8 h7 s7 d5 c5 s3 
import sys
numbers={'2':13,'A':12,'K':11,'Q':10,'J':9,'10':8,'9':7,'8':6,'7':5,'6':4,'5':3,'4':2,'3':1}
colors={'h':4,'s':3,'d':2,'c':1}
def compare(card):
    color,number=card[0],card[1:]
    return colors[color]+numbers[number]*100
for lines in sys.stdin:
    data=lines.split()
    if not data:
        continue
    lst=sorted(data,key=compare,reverse=True)
    for i in range(len(lst)):
        print(lst[i],end=" ")
    print()
#这道题主要是两个部分
#1.处理输入，我们采用sys的标准輸入流來處理
#2.處理排序問題。這裏主要采用了映射的方法將字符串比較轉化成一個整數的比較，能有效地解決問題