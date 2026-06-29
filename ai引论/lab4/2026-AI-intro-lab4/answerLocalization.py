from typing import List
import numpy as np
from utils import Particle

### 可以在这里写下一些你需要的变量和函数 ###
COLLISION_DISTANCE = 1
MAX_ERROR = 50000
def is_in_wall(x,y,walls):
    if len(walls)==0:
        return False
    diff=np.abs(walls-np.array([x, y]))
    return np.any(np.all(diff<0.5,axis=1))
### 可以在这里写下一些你需要的变量和函数 ###


def generate_uniform_particles(walls, N):
    """
    输入：
    walls: 维度为(xxx, 2)的np.array, 地图的墙壁信息，具体设定请看README关于地图的部分
    N: int, 采样点数量
    输出：
    particles: List[Particle], 返回在空地上均匀采样出的N个采样点的列表，每个点的权重都是1/N
    """
    all_particles: List[Particle] = []
    for _ in range(N):
        all_particles.append(Particle(1.0, 1.0, 1.0, 0.0))
    ### 你的代码 ###
    if len(walls) > 0:
        min_x,min_y=np.min(walls,axis=0)-1.0
        max_x,max_y=np.max(walls,axis=0)+1.0
    else:
        min_x,min_y,max_x,max_y=0.0,0.0,20.0,20.0
    all_particles.clear()
    while len(all_particles)<N:
        x=np.random.uniform(min_x,max_x)
        y=np.random.uniform(min_y,max_y)
        if not is_in_wall(x,y,walls):
            theta=np.random.uniform(0.0,2*np.pi)
            all_particles.append(Particle(x,y,theta,1.0/N))
    ### 你的代码 ###
    return all_particles


def calculate_particle_weight(estimated, gt):
    """
    输入：
    estimated: np.array, 该采样点的距离传感器数据
    gt: np.array, Pacman实际位置的距离传感器数据
    输出：
    weight, float, 该采样点的权重
    """
    weight = 1.0
    ### 你的代码 ###
    distance=np.linalg.norm(estimated-gt)
    k=0.29
    weight=np.exp(-k*distance)+0.021
    ### 你的代码 ###
    return weight


def resample_particles(walls, particles: List[Particle]):
    """
    输入：
    walls: 维度为(xxx, 2)的np.array, 地图的墙壁信息，具体设定请看README关于地图的部分
    particles: List[Particle], 上一次采样得到的粒子，注意是按权重从大到小排列的
    输出：
    particles: List[Particle], 返回重采样后的N个采样点的列表
    """
    resampled_particles: List[Particle] = []
    for _ in range(len(particles)):
        resampled_particles.append(Particle(1.0, 1.0, 1.0, 0.0))
    ### 你的代码 ###
    N=len(particles)
    resampled_particles.clear()
    weights=np.array([p.weight for p in particles])
    weights_sum=np.sum(weights)
    if weights_sum>0:
        weights=weights/weights_sum
    else:
        weights=np.ones(N)/N
    sample_num=np.floor(weights*N).astype(int)
    pos_noise_std=0.1
    theta_noise_std=0.05
    for i,base_particle in enumerate(particles):
        for _ in range(sample_num[i]):
            retry_count=0
            new_x,new_y=base_particle.position[0],base_particle.position[1]
            while retry_count<10:
                test_x=base_particle.position[0]+np.random.normal(0.0,pos_noise_std)
                test_y=base_particle.position[1]+np.random.normal(0.0,pos_noise_std)
                if not is_in_wall(test_x,test_y,walls):
                    new_x,new_y=test_x,test_y
                    break
                retry_count+=1
            new_theta=(base_particle.theta+np.random.normal(0.0,theta_noise_std))%(2*np.pi)
            resampled_particles.append(Particle(new_x,new_y,new_theta,1.0/N))
    rest_num=N-len(resampled_particles)
    if rest_num>0:
        rest_particles=generate_uniform_particles(walls,rest_num)
        resampled_particles.extend(rest_particles)
    ### 你的代码 ###
    return resampled_particles

def apply_state_transition(p: Particle, traveled_distance, dtheta):
    """
    输入：
    p: 采样的粒子
    traveled_distance, dtheta: ground truth的Pacman这一步相对于上一步运动方向改变了dtheta，并移动了traveled_distance的距离
    particle: 按照相同方式进行移动后的粒子
    """
    ### 你的代码 ###
    p.theta+=dtheta
    dx=traveled_distance*np.cos(p.theta)
    dy=traveled_distance*np.sin(p.theta)
    p.position+=np.array([dx, dy])
    ### 你的代码 ###
    return p

def get_estimate_result(particles: List[Particle]):
    """
    输入：
    particles: List[Particle], 全部采样粒子
    输出：
    final_result: Particle, 最终的猜测结果
    """
    final_result = Particle()
    ### 你的代码 ###
    if len(particles)>0:
        final_result=particles[0]
    ### 你的代码 ###
    return final_result