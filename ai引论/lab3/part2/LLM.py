import re
from Maze import Maze
from openai import OpenAI


# TODO: Replace this with your own prompt.
your_prompt = """# LLM.py 中的 your_prompt 修改示例
"""
your_prompt = """
你是一个精通迷宫寻路算法和吃豆人游戏的策略执行者。请分析当前的游戏状态，并为吃豆人做出最佳的下一步移动决策。
你的终极目标是用最少的步数吃掉迷宫中所有的豆子。有兩个要求：1.绝对不能移动到“墙壁”上。
绝对不能移动到鬼的位置（否则游戏失败终止）。
你需要避免死循环，'曾经走过的位置”记录了你过去的足迹。尽量不要反复走重复的路，除非为了去吃远处的豆子而不得不折返。
优先选择未走过且有豆子的方向。
坐标系统如下：
1.向上移动(0)：行数减1，即 (x, y) 变成 (x-1, y)
2.向下移动(1)：行数加1，即 (x, y) 变成 (x+1, y)
3.向左移动(2)：列数减1，即 (x, y) 变成 (x, y-1)
4.向右移动(3)：列数加1，即 (x, y) 变成 (x, y+1)
你需要执行如下策略：
1. 检查当前吃豆人的坐标，以及“可用方向”列表（你只能在可用方向中选择一个）。
2. 计算在可用方向中，哪一个方向的相邻格子是豆子。如果有，优先选择。
3. 如果周围没有直接的豆子，观察整体迷宫中距离你最近的豆子在什么方向，并结合“曾经走过的位置”，
选择一条能走向豆子且不走回头路、不撞上鬼的路径。
4. 严格按照下面要求的格式输出。
"""
"""
"""

# Don't change this part.
output_format = """
输出必须是0-3的整数，上=0，下=1，左=2，右=3。
*重点*：(5,5)的上方是(4,5)，下方是(6,5)，左方是(5,4)，右方是(5,6)。
输出格式为：
“分析：XXXX。
动作：0（一个数字，不能出现其他数字）。”
"""

prompt = your_prompt + output_format


def get_game_state(maze: Maze, places: list, available: list) -> str:
    """
    Convert game state to natural language description.
    """
    description = ""
    for i in range(maze.height):
        for j in range(maze.width):
            description += f"({i},{j})="
            if maze.grid[i, j] == 0:
                description += f"空地"
            elif maze.grid[i, j] == 1:
                description += "墙壁"
            else:
                description += "豆子"
            description += ","
        description += "\n"
    places_str = ','.join(map(str, places))
    available_str = ','.join(map(str, available))
    state = f"""当前游戏状态（坐标均以0开始）：\n1、迷宫布局（0=空地,1=墙,2=豆子）：\n{description}\n2、吃豆人位置：{maze.pacman_pos[4]}\n3、鬼魂位置：{maze.pacman_pos[3]}\n4、曾经走过的位置：{places_str}\n5、可用方向：{available_str}\n"""
    return state


def get_ai_move(client: OpenAI, model_name: str, maze: Maze, file, places: list, available: list) -> int:
    """
    Get the move from the AI model.
    :param client: OpenAI client instance.
    :param model_name: Name of the AI model.
    :param maze: The maze object.
    :param file: The log file to write the output.
    :param places: The list of previous positions.
    :param available: The list of available directions.
    :return: The direction chosen by the AI.
    """
    state = get_game_state(maze, places, available)

    file.write("________________________________________________________\n")
    file.write(f"message:\n{state}\n")
    print("________________________________________________________")
    print(f"message:\n{state}")

    print("Waiting for AI response...")
    all_response = client.chat.completions.create(
        model=model_name,
        messages=[
            {
                "role": "system",
                "content": prompt
            },
            {
                "role": "user",
                "content": state
            }
        ],
        stream=False,
        temperature=.0
    )
    info = all_response.choices[0].message.content

    file.write(f"AI response:\n{info}\n")
    print(f"AI response:\n{info}")
    numbers = re.findall(r'\d+', info)
    choice = numbers[-1]
    return int(choice), info
