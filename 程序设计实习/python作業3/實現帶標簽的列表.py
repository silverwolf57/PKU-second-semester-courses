# TaggedList 表示元素带标签的列表。每个元素都有不同标签，标签是字符串。元素可以用整数做下标访问，也可以用标签做下标访问。请给出该类的实现

# exit = None
# class TaggedList:  #元素带标签的列表
# // 在此处补充你的代码
# a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
# print(len(a),78 in a, 80 in a) #>>4 False True
# print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
# print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
# a[1] = a['物理'] = 85
# print(a) #>>语文:70,数学:85,英语:90,物理:85,
# 输入
# 无
# 输出
# 如样例
# 样例输入
# 无
# 样例输出
# 4 False True
# 语文:70,数学:80,英语:90,物理:100,
# 70 80
# 语文:70,数学:85,英语:90,物理:85,
exit = None
class TaggedList:  
    def __init__(self, lst, ref):
        self.values = list(lst)
        self.tags = list(ref)

    def __str__(self):
        result = ""
        for i in range(len(self.values)):
            result += f"{self.tags[i]}:{self.values[i]},"
        return result
    
    def __len__(self):
        return len(self.values)

    def print(self):
        print(str(self))

    def __contains__(self, item):
        return item in self.values

    def __getitem__(self, key):
        if isinstance(key, int):
            return self.values[key]
        else:
            if key in self.tags:
                idx = self.tags.index(key)
                return self.values[idx]

    def __setitem__(self, key, value):
        if isinstance(key, int):
            self.values[key] = value
        else:
            if key in self.tags:
                idx = self.tags.index(key)
                self.values[idx] = value

a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
print(len(a),78 in a, 80 in a) #>>4 False True
print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
a[1] = a['物理'] = 85
print(a) #>>语文:70,数学:85,英语:90,物理:85,
#to solve the problem,we first need to store the two lists,we just use lists to store
#the problem requires us to rewrite many operators:len(),str,[],print,in
#the str,len,in and the print are easy to write
#for the[],to achieve the two directions.we need to record the index of the key to write the getitem and use the same trick for the setitem