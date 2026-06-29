import numpy as np
from typing import List
from utils import TreeNode
from simuScene import PlanningMap


### 定义一些你需要的变量和函数 ###
STEP_DISTANCE = 1
TARGET_THREHOLD = 0.809
MAX_ITERATIONS = 7000
### 定义一些你需要的变量和函数 ###


class RRT:
    def __init__(self, walls) -> None:
        """
        输入包括地图信息，你需要按顺序吃掉的一列事物位置 
        注意：只有按顺序吃掉上一个食物之后才能吃下一个食物，在吃掉上一个食物之前Pacman经过之后的食物也不会被吃掉
        """
        self.map = PlanningMap(walls)
        self.walls = walls
        
        # 其他需要的变量
        ### 你的代码 ###      
        self.path_idx=0
        ### 你的代码 ###
        
        # 如有必要，此行可删除
        self.path = None
        
        
    def find_path(self, current_position, next_food):
        """
        在程序初始化时，以及每当 pacman 吃到一个食物时，主程序会调用此函数
        current_position: pacman 当前的仿真位置
        next_food: 下一个食物的位置
        
        本函数的默认实现是调用 build_tree，并记录生成的 path 信息。你可以在此函数增加其他需要的功能
        """
        
        ### 你的代码 ###      
        self.path_idx=0
        ### 你的代码 ###
        # 如有必要，此行可删除
        self.path = self.build_tree(current_position, next_food)
        
        
    def get_target(self, current_position, current_velocity):
        """
        主程序将在每个仿真步内调用此函数，并用返回的位置计算 PD 控制力来驱动 pacman 移动
        current_position: pacman 当前的仿真位置
        current_velocity: pacman 当前的仿真速度
        一种可能的实现策略是，仅作为参考：
        （1）记录该函数的调用次数
        （2）假设当前 path 中每个节点需要作为目标 n 次
        （3）记录目前已经执行到当前 path 的第几个节点，以及它的执行次数，如果超过 n，则将目标改为下一节点
        
        你也可以考虑根据当前位置与 path 中节点位置的距离来决定如何选择 target
        
        同时需要注意，仿真中的 pacman 并不能准确到达 path 中的节点。你可能需要考虑在什么情况下重新规划 path
        """
        target_pose = np.zeros_like(current_position)
        ### 你的代码 ###
        if self.path is not None and len(self.path)>0:
            if self.path_idx>=len(self.path):
                self.path_idx=len(self.path)-1
            target_pose=np.array(self.path[self.path_idx])
            dist_to_curr=np.linalg.norm(current_position-target_pose)
            if self.path_idx<len(self.path)-1:
                next_pose=np.array(self.path[self.path_idx + 1])
                if dist_to_curr<TARGET_THREHOLD:
                    if self.map.checkline((float(current_position[0]),float(current_position[1])),(float(next_pose[0]),float(next_pose[1]))):
                        self.path_idx+=1
                        target_pose=next_pose
                elif dist_to_curr<0.25:
                    self.path_idx+=1
                    target_pose=next_pose
        else:
            target_pose=current_position
        ### 你的代码 ###
        return target_pose
        
    ### 以下是RRT中一些可能用到的函数框架，全部可以修改，当然你也可以自己实现 ###
    def build_tree(self, start, goal):
        """
        实现你的快速探索搜索树，输入为当前目标食物的编号，规划从 start 位置食物到 goal 位置的路径
        返回一个包含坐标的列表，为这条路径上的pd targets
        你可以调用find_nearest_point和connect_a_to_b两个函数
        另外self.map的checkoccupy和checkline也可能会需要，可以参考simuScene.py中的PlanningMap类查看它们的用法
        """
        path = []
        graph: List[TreeNode] = []
        graph.append(TreeNode(-1, start[0], start[1]))
        ### 你的代码 ###
        goal_node=np.array(goal)
        for _ in range(MAX_ITERATIONS):
            if np.random.rand()<0.2:
                sample=goal_node
            else:
                sample=np.array([np.random.uniform(min(start[0], goal[0])-10,max(start[0],goal[0])+10),np.random.uniform(min(start[1],goal[1])-10,max(start[1],goal[1])+10)])
            n_idx,_=self.find_nearest_point(sample,graph)
            p_a=graph[n_idx].pos
            is_empty,newpt=self.connect_a_to_b(p_a,sample)
            if is_empty:
                if not self.map.checkoccupy((float(newpt[0]),float(newpt[1]))):
                    new_node=TreeNode(n_idx,newpt[0],newpt[1])
                    graph.append(new_node)
                    if np.linalg.norm(newpt-goal_node)<STEP_DISTANCE and self.map.checkline((float(newpt[0]),float(newpt[1])),(float(goal_node[0]),float(goal_node[1]))):
                        graph.append(TreeNode(len(graph)-1,goal[0],goal[1]))
                        curr_idx=len(graph)-1
                        while curr_idx!=-1:
                            path.append([graph[curr_idx].pos[0],graph[curr_idx].pos[1]])
                            curr_idx=graph[curr_idx].parent_idx
                        path.reverse()
                        break
        ### 你的代码 ###
        return path

    @staticmethod
    def find_nearest_point(point, graph):
        """
        找到图中离目标位置最近的节点，返回该节点的编号和到目标位置距离、
        输入：
        point：维度为(2,)的np.array, 目标位置
        graph: List[TreeNode]节点列表
        输出：
        nearest_idx, nearest_distance 离目标位置距离最近节点的编号和距离
        """
        nearest_idx = -1
        nearest_distance = 10000000.
        ### 你的代码 ###
        for idx,node in enumerate(graph):
            d=np.linalg.norm(point-node.pos)
            if d<nearest_distance:
                nearest_distance=d
                nearest_idx=idx
        ### 你的代码 ###
        return nearest_idx, nearest_distance
    
    def connect_a_to_b(self, point_a, point_b):
        """
        以A点为起点，沿着A到B的方向前进STEP_DISTANCE的距离，并用self.map.checkline函数检查这段路程是否可以通过
        输入：
        point_a, point_b: 维度为(2,)的np.array，A点和B点位置，注意是从A向B方向前进
        输出：
        is_empty: bool，True表示从A出发前进STEP_DISTANCE这段距离上没有障碍物
        newpoint: 从A点出发向B点方向前进STEP_DISTANCE距离后的新位置，如果is_empty为真，之后的代码需要把这个新位置添加到图中
        """
        is_empty = False
        newpoint = np.zeros(2)
        ### 你的代码 ###
        vec=point_b-point_a
        dist=np.linalg.norm(vec)
        if dist>1e-6:
            newpoint=point_a+(vec/dist)*STEP_DISTANCE
            if self.map.checkline((float(point_a[0]),float(point_a[1])),(float(newpoint[0]),float(newpoint[1]))):
                is_empty=True
        else:
            newpoint=point_a
        ### 你的代码 ###
        return is_empty, newpoint
