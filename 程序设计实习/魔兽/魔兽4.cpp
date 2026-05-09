/*
A:魔兽世界终极版
查看提交统计提问
总时间限制: 6000ms 内存限制: 65536kB
描述
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，
城市从西向东依次编号为1,2,3 .... N ( N <= 20 )。
红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），
则武士死亡（消失）。

有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。

武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。
每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。
被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。
反击可能致敌人于死地。

如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。
当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。
注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。
对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。

如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。

城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。
在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。

当某个城市有连续两场战斗都是同一方的武士杀死敌人
(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间有平局的战斗，就不算连续了) ，
那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。旗帜一旦插上，就一直插着，直到被敌人更换。
一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。

各种武器有其特点：

sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。
但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。
sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.

arrow有一个攻击力值R。如果下一步要走到的城市有敌人，
那么拥有arrow的武士就会放箭攻击下一个城市的敌人（不能攻击对方司令部里的敌人）而不被还击。
arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。arrow使用3次后即被耗尽，武士失去arrow。
两个相邻的武士可能同时放箭把对方射死。

拥有bomb的武士，在战斗开始前如果判断自己将被杀死
（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，而且假设武士可以知道敌人的攻击力和生命值），
那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。

武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

不同的武士有不同的特点。

dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。
dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。
dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。
dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。士气增减发生在欢呼之前。

ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。

iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。iceman 每前进两步，
在第2步完成的时候，生命值会减少9，攻击力会增加20。但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。
即iceman不会因走多了而死。

lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。
每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。
但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。
所谓“战斗前”，就是每个小时的40分前的一瞬间。

wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。
被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。

以下是不同时间会发生的不同事件：

在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。
例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。

在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。
或从和敌军司令部相邻的城市到达敌军司令部。

在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。

在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。

在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。
注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。

在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。

在每个小时的第40分：在有两个武士的城市，会发生战斗。 
如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。
此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事件发生，但战斗胜利后应该发生的事情都会发生。
如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。

在每个小时的第50分，司令部报告它拥有的生命元数量。

在每个小时的第55分，每个武士报告其拥有的武器情况。

武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。

任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。

任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。

给定一个时间，要求你将从0点0分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：



1) 武士降生
输出样例： 000:00 blue lion 1 born

表示在 0点0分，编号为1的蓝魔lion武士降生
如果造出的是dragon，那么还要多输出一行，例：

000:00 blue dragon 1 born
Its morale is 23.34

表示该该dragon降生时士气是23. 34(四舍五入到小数点后两位)

如果造出的是lion，那么还要多输出一行，例:
000:00 blue lion 1 born
Its loyalty is 24

表示该lion降生时的忠诚度是24

2) lion逃跑
输出样例： 000:05 blue lion 1 ran away
表示在 0点5分，编号为1的蓝魔lion武士逃走

3) 武士前进到某一城市
输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
表示在 0点10分，红魔1号武士iceman前进到1号城市，此时他生命值为20,攻击力为30
对于iceman,输出的生命值和攻击力应该是变化后的数值

4)武士放箭
输出样例： 000:35 blue dragon 1 shot
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
000:35 blue dragon 1 shot and killed red lion 4
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。

5)武士使用bomb
输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。

6) 武士主动进攻
输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
表示在0点40分，1号城市中，红魔1号武士iceman 进攻蓝魔1号武士lion,在发起进攻前，红魔1号武士iceman生命值为20，攻击力为 30

7) 武士反击
输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1
表示在1点40分，1号城市中，蓝魔2号武士dragon反击红魔2号武士lion

8) 武士战死
输出样例：001:40 red lion 2 was killed in city 1
被箭射死的武士就不会有这一条输出。

9) 武士欢呼
输出样例：003:40 blue dragon 2 yelled in city 4

10) 武士获取生命元( elements )
输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter

输出不包括在30分不是通过战斗获取的elements

11) 旗帜升起
输出样例：004:40 blue flag raised in city 4

12) 武士抵达敌军司令部
输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
(此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值

13) 司令部被占领
输出样例：003:10 blue headquarter was taken

14)司令部报告生命元数量
000:50 100 elements in red headquarter
000:50 120 elements in blue headquarter
表示在0点50分，红方司令部有100个生命元，蓝方有120个

15)武士报告武器情况
000:55 blue wolf 2 has arrow(2),bomb,sword(23)
000:55 blue wolf 4 has no weapon
000:55 blue wolf 5 has sword(20)
表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。
蓝魔4号武士wolf没武器。
蓝魔5号武士wolf有一支攻击力为20的sword。
交代武器情况时，次序依次是：arrow,bomb,sword。如果没有某种武器，某种武器就不用提。
报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。

在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。
一次战斗中的这些事件，序号小的应该先输出。

两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。

显然，13号事件发生之前的一瞬间一定发生了12号事件。输出时，这两件事算同一时间发生，但是应先输出12号事件

虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

输入
第一行是t,代表测试数据组数
每组样例共三行。
第一行，五个整数 M,N,R,K, T。其含义为：

每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000

输出
对每组数据，先输出一行：
Case n:
如对第一组数据就输出 Case1:
然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时: 分”，“时”有三位，“分”有两位。

样例输入
1
20 1 10 10 1000
20 20 30 10 20
5 5 5 5 5
样例输出
Case 1:
000:00 blue lion 1 born
Its loyalty is 10
000:10 blue lion 1 marched to city 1 with 10 elements and force 5
000:30 blue lion 1 earned 10 elements for his headquarter
000:50 20 elements in red headquarter
000:50 20 elements in blue headquarter
000:55 blue lion 1 has no weapon
001:00 blue dragon 2 born
Its morale is 0.00
001:10 blue lion 1 reached red headquarter with 10 elements and force 5
001:10 blue dragon 2 marched to city 1 with 20 elements and force 5
001:30 blue dragon 2 earned 10 elements for his headquarter
001:50 20 elements in red headquarter
001:50 10 elements in blue headquarter
001:55 blue lion 1 has no weapon
001:55 blue dragon 2 has arrow(3)
002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
002:10 red headquarter was taken
*/

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<iomanip>
#include<unordered_map>
#include<utility>
#include<queue>
#include<cstdio>
#include<sstream>

using namespace std;

int current_time = 0;
bool red_conquered = false;
bool blue_conquered = false;
int loyaltyDecrease, timeLimit, cityCount;

unordered_map<string, int> initialHPs;
unordered_map<string, int> initialForces;
unordered_map<string, vector<string>> buildOrder;
vector<string> weapon_kinds = {"sword", "bomb", "arrow"};

enum fight_result { BOTH_DEAD, BOTH_ALIVE, BLUE_WIN, RED_WIN };

string get_format_clock() {
    int hour = current_time / 60;
    int minute = current_time % 60;
    ostringstream ost;
    ost << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return move(ost.str());
}

class weapon {
public:
    string name;
    weapon(string name_) : name(name_) {}
    virtual ~weapon() {}
    virtual void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) {}
    virtual bool is_usable() { return false; }
};

class sword : public weapon {
public:
    sword(string name_) : weapon(name_) {}
    void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) override {
        int attack_dmg = (attacker_force * 2) / 10;
        injure_hp -= attack_dmg;
    }
    bool is_usable() override { return true; }
};

class bomb : public weapon {
public:
    bool usable;
    bomb(string name_) : weapon(name_), usable(true) {}
    void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) override {
        if (!usable) return;
        int attack_dmg = (attacker_force * 4) / 10;
        int self_attack = (attacker_name == "ninja") ? 0 : attack_dmg / 2;
        attacker_hp -= self_attack;
        injure_hp -= attack_dmg;
        usable = false;
    }
    bool is_usable() override { return usable; }
};

class arrow : public weapon {
public:
    int use_count;
    arrow(string name_, int use_count_) : weapon(name_), use_count(use_count_) {}
    void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) override {
        if (use_count >= 2) return;
        int attack_dmg = (attacker_force * 3) / 10;
        injure_hp -= attack_dmg;
        use_count++;
    }
    bool is_usable() override { return use_count < 2; }
};


sword* sw = nullptr;

class warrior {
public:
    int id;              
    int hp;              
    int force;           
    string side;         
    string name;         
    int location;        
    int cur_weapon_ind;  
    vector<weapon*> weapons;

    warrior(int id_, int hp_, string side_, string name_, int location_, int force_)
        : id(id_), hp(hp_), side(side_), name(name_), location(location_), force(force_) {
        weapons = vector<weapon*>(10, nullptr);
    }
    
    warrior(warrior& w) {
        id = w.id;
        hp = w.hp;
        force = w.force;
        side = w.side;
        name = w.name;
        location = w.location;
        weapons = std::move(w.weapons);
    }
    
    virtual ~warrior() {}

    virtual void march() {
        int direction = side == "red" ? 1 : -1;
        location += direction;
        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " marched to city " << location << " with " << hp 
             << " elements and force " << force << endl;
    }

    void reach_headquarter() {
        if (name == "iceman") {
            int decrease_elements = hp / 10;
            hp -= decrease_elements;
        }
        string enemy_side = side == "blue" ? "red" : "blue";

        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " reached " << enemy_side << " headquarter with " << hp 
             << " elements and force " << force << endl;
        cout << get_format_clock() << " " << enemy_side << " headquarter was taken\n";
        
        if (enemy_side == "blue")
            blue_conquered = true;
        else
            red_conquered = true;
    }

    void sort_weapons(bool used_first) {
        int sword_cnt = 0, bomb_cnt = 0, new_arrow_cnt = 0, used_arrow_cnt = 0;
        for (int i = 0; i < 10; i++) {
            weapon* p = weapons[i];
            if (p == nullptr) continue;
            if (p->name == "sword") {
                sword_cnt++;
            } else if (p->name == "bomb") {
                bomb* b = dynamic_cast<bomb*>(p);
                if (b->is_usable()) {
                    bomb_cnt++;
                }
                delete p;
            } else {
                arrow* a = dynamic_cast<arrow*>(p);
                if (a->use_count == 0) {
                    new_arrow_cnt++;
                } else if (a->use_count == 1) {
                    used_arrow_cnt++;
                }
                delete p;
            }
            weapons[i] = nullptr;
        }
        int ind = 0;
        while (sword_cnt--) weapons[ind++] = sw;
        while (bomb_cnt--) weapons[ind++] = new bomb("bomb");
        if (!used_first) {
            while (new_arrow_cnt--) weapons[ind++] = new arrow("arrow", 0);
            while (used_arrow_cnt--) weapons[ind++] = new arrow("arrow", 1);
        } else {
            while (used_arrow_cnt--) weapons[ind++] = new arrow("arrow", 1);
            while (new_arrow_cnt--) weapons[ind++] = new arrow("arrow", 0);
        }
        cur_weapon_ind = 0;
    }

    int count_weapons() {
        int cnt = 0;
        for (weapon* p : weapons) {
            if (p != nullptr) cnt++;
            else break;
        }
        return cnt;
    }

    void clear_weapons() {
        for (int i = 0; i < 10; i++) {
            if (weapons[i] != nullptr && !weapons[i]->is_usable()) {
                delete weapons[i];
                weapons[i] = nullptr;
            }
        }
    }

    void take_weapons_after_fight(warrior* enemy) {
        if (this == enemy) return;
        if (hp <= 0) return;
        enemy->clear_weapons();
        enemy->sort_weapons(false);
        clear_weapons();
        sort_weapons(true);
        int tot_weapon = count_weapons();
        int ind = 0;
        for (int i = tot_weapon; i < 10; i++) {
            weapons[i] = enemy->weapons[ind++];
        }
        sort_weapons(true);
    }

    bool is_alive() { return hp > 0; }

    weapon* find_proper_weapon() {
        weapon* res = weapons[cur_weapon_ind];
        if (res != nullptr && res->is_usable()) {
            cur_weapon_ind = (cur_weapon_ind + 1) % 10;
            return res;
        } else {
            int weapon_ind = (cur_weapon_ind + 1) % 10;
            while (weapon_ind != cur_weapon_ind) {
                res = weapons[weapon_ind];
                if (res != nullptr && res->is_usable()) {
                    cur_weapon_ind = (weapon_ind + 1) % 10;
                    return res;
                } else {
                    weapon_ind = (weapon_ind + 1) % 10;
                }
            }
        }
        return nullptr;
    }

    void attack(warrior* enemy) {
        weapon* w = find_proper_weapon();
        if (w == nullptr) return;
        w->attack(this->force, this->name, this->hp, enemy->hp);
    }
};

class dragon : public warrior {
public:
    dragon(warrior& w) : warrior(w) {}
    void yell() {
        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " yelled in city " << location << endl;
    }
};

class lion : public warrior {
public:
    int loyalty;
    lion(warrior& w, int loyalty_) : warrior(w), loyalty(loyalty_) {}
    
    void march() override {
        int direction = side == "red" ? 1 : -1;
        location += direction;
        loyalty -= loyaltyDecrease;
        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " marched to city " << location << " with " << hp 
             << " elements and force " << force << endl;
    }
    
    bool escape() {
        if (loyalty > 0) return false;
        else {
            cout << get_format_clock() << " " << side << " lion " << id << " ran away\n";
            return true;
        }
    }
};

class iceman : public warrior {
public:
    iceman(warrior& w) : warrior(w) {}
    void march() override {
        int direction = side == "red" ? 1 : -1;
        location += direction;
        int decrease_elements = hp / 10;
        hp -= decrease_elements;
        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " marched to city " << location << " with " << hp 
             << " elements and force " << force << endl;
    }
};

class wolf : public warrior {
public:
    wolf(warrior& w) : warrior(w) {}
    void rob_weapons(warrior* enemy) {
        if (enemy->name == "wolf") return;
        if (enemy == this) return;
        enemy->clear_weapons();
        enemy->sort_weapons(false);
        clear_weapons();
        sort_weapons(true);

        weapon* first_weapon = enemy->weapons[0];
        if (first_weapon == nullptr) return;

        string first_weapon_name = first_weapon->name;
        int self_ind = count_weapons(), enemy_ind = 0;
        for (weapon* p : enemy->weapons) {
            if (p == nullptr || p->name != first_weapon_name) break;
            weapons[self_ind++] = p;
            enemy->weapons[enemy_ind++] = nullptr;
        }
        enemy->sort_weapons(false);
        sort_weapons(true);
        cout << get_format_clock() << " " << side << " " << name << " " << id 
             << " took " << enemy_ind << " " << first_weapon_name 
             << " from " << enemy->side << " " << enemy->name << " " << enemy->id 
             << " in city " << location << endl;
    }
};

class ninja : public warrior {
public:
    ninja(warrior& w) : warrior(w) {}
};


class city {
public:
    warrior* first;
    warrior* second;
    city(warrior* red, warrior* blue) : first(red), second(blue) {}
};

vector<city> cities; 

void warrior_born(warrior& w);

class headquarter {
public:
    string side;
    int totalLife;
    int totalCount;
    int currentIdx;

    headquarter(string side_, int totalLife_)
        : side(side_), totalLife(totalLife_), totalCount(0), currentIdx(0) {}

    warrior* make_warrior() {
        warrior* ret = nullptr;
        string w_name = buildOrder[side][currentIdx];
        int cost = initialHPs[w_name];

        if (cost <= totalLife) {
            totalCount++;
            int warrior_id = totalCount;
            int location = (side == "red") ? 0 : cityCount + 1;
            totalLife -= cost;
            currentIdx = (currentIdx + 1) % 5;
            
            ret = new warrior(warrior_id, cost, side, w_name, location, initialForces[w_name]);
        }
        return ret;
    }

    weapon* make_weapon(string name) {
        if (name == "sword") return sw;
        if (name == "bomb") return new bomb(name);
        if (name == "arrow") return new arrow(name, 0);
        return nullptr;
    }

    warrior* further_process(warrior* p) {
        if (p == nullptr) return nullptr;
        
        string name = p->name;
        warrior* ret = nullptr;
        
        if (name == "dragon") {
            string weapon_name = weapon_kinds[p->id % 3];
            p->weapons[0] = make_weapon(weapon_name);
            ret = new dragon(*p);
        } else if (name == "ninja") {
            string weapon_name1 = weapon_kinds[p->id % 3];
            string weapon_name2 = weapon_kinds[(p->id + 1) % 3];
            p->weapons[0] = make_weapon(weapon_name1);
            p->weapons[1] = make_weapon(weapon_name2);
            ret = new ninja(*p);
        } else if (name == "iceman") {
            string weapon_name = weapon_kinds[p->id % 3];
            p->weapons[0] = make_weapon(weapon_name);
            ret = new iceman(*p);
        } else if (name == "lion") {
            string weapon_name = weapon_kinds[p->id % 3];
            p->weapons[0] = make_weapon(weapon_name);
            ret = new lion(*p, totalLife);
        } else if (name == "wolf") {
            ret = new wolf(*p);
        }
        return ret;
    }

    void make_warriors() {
        warrior* p = further_process(make_warrior());
        if (p != nullptr) {
            warrior_born(*p);
            if (p->side == "red") {
                cities[0].first = p;
            } else {
                cities[cities.size() - 1].second = p;
            }
        }
    }
};

void warrior_born(warrior& w) {
    cout << get_format_clock() << " " << w.side << " " << w.name << " " << w.id << " born\n";
    if (w.name == "lion") {
        lion* l = dynamic_cast<lion*>(&w);
        cout << "Its loyalty is " << l->loyalty << endl;
    }
}

void happen00_warrior_born(headquarter& red, headquarter& blue) {
    red.make_warriors();
    blue.make_warriors();
}

void happen05_lion_escape() {
    for (int i = 0; i < cities.size(); i++) {
        warrior *first = cities[i].first, *second = cities[i].second;
        if (first != nullptr && first->name == "lion") {
            lion* l = dynamic_cast<lion*>(first);
            if (l->escape()) {
                delete cities[i].first;
                cities[i].first = nullptr;
            }
        }
        if (second != nullptr && second->name == "lion") {
            lion* l = dynamic_cast<lion*>(second);
            if (l->escape()) {
                delete cities[i].second;
                cities[i].second = nullptr;
            }
        }
    }
}

void happen10_warrior_march() {
    warrior* b = cities[1].second;
    if (b != nullptr) {
        b->reach_headquarter();
        delete cities[1].second;
        cities[1].second = nullptr;
    }

    warrior* next_move_red = cities[0].first;
    cities[0].first = nullptr;

    for (int i = 1; i < cities.size() - 1; i++) {
        warrior *r = next_move_red, *b = cities[i + 1].second;
        next_move_red = cities[i].first;
        if (r != nullptr) r->march();
        cities[i].first = r;

        if (b != nullptr) b->march();
        cities[i].second = b;
    }
    cities[cities.size() - 1].second = nullptr;
    if (next_move_red != nullptr) {
        next_move_red->reach_headquarter();
        delete next_move_red;
    }
}

void happen35_wolf_rob() {
    for (int i = 1; i < cities.size() - 1; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        if (r == nullptr || b == nullptr) continue;
        
        if (r->name == "wolf") {
            wolf* w = dynamic_cast<wolf*>(r);
            w->rob_weapons(b);
        }
        if (b->name == "wolf") {
            wolf* w = dynamic_cast<wolf*>(b);
            w->rob_weapons(r);
        }
    }
}

fight_result trigger_fight(warrior* first, warrior* second) {
    int still_epoch = 0;
    while (first->is_alive() && second->is_alive()) {
        int first_elements = first->hp, second_elements = second->hp;
        if (first->is_alive()) first->attack(second);
        if (second->is_alive()) second->attack(first);
        
        if (first_elements == first->hp && second_elements == second->hp) {
            still_epoch++;
        }
        if (still_epoch >= 12) return BOTH_ALIVE;
    }
    warrior* alived_warrior = first->is_alive() ? first : second;
    if (!alived_warrior->is_alive()) return BOTH_DEAD;
    else {
        if (alived_warrior->side == "red") return RED_WIN;
        else return BLUE_WIN;
    }
}

void happen40_war() {
    for (int i = 1; i < cities.size() - 1; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        if (r == nullptr || b == nullptr) continue;
        
        r->clear_weapons();
        r->sort_weapons(true);
        b->clear_weapons();
        b->sort_weapons(true);
        
        fight_result res;
        if (i % 2) res = trigger_fight(r, b);
        else res = trigger_fight(b, r);
        
        dragon* rd = dynamic_cast<dragon*>(r);
        dragon* bd = dynamic_cast<dragon*>(b);
        
        if (res == BOTH_ALIVE) {
            cout << get_format_clock() << " both red " << r->name << " " << r->id 
                 << " and blue " << b->name << " " << b->id << " were alive in city " << r->location << endl;
            if (rd != nullptr) rd->yell();
            if (bd != nullptr) bd->yell();
        } else if (res == BOTH_DEAD) {
            cout << get_format_clock() << " both red " << r->name << " " << r->id 
                 << " and blue " << b->name << " " << b->id << " died in city " << r->location << endl;
        } else if (res == RED_WIN) {
            r->take_weapons_after_fight(b);
            cout << get_format_clock() << " red " << r->name << " " << r->id 
                 << " killed blue " << b->name << " " << b->id << " in city " << r->location 
                 << " remaining " << r->hp << " elements\n";
            if (rd != nullptr) rd->yell();
        } else {
            b->take_weapons_after_fight(r);
            cout << get_format_clock() << " blue " << b->name << " " << b->id 
                 << " killed red " << r->name << " " << r->id << " in city " << b->location 
                 << " remaining " << b->hp << " elements\n";
            if (bd != nullptr) bd->yell();
        }
        
        r->clear_weapons();
        r->sort_weapons(true);
        b->clear_weapons();
        b->sort_weapons(true);
        
        if (!r->is_alive()) {
            delete cities[i].first;
            cities[i].first = nullptr;
        }
        if (!b->is_alive()) {
            delete cities[i].second;
            cities[i].second = nullptr;
        }
    }
}

void report_base(headquarter& base) {
    cout << get_format_clock() << " " << base.totalLife << " elements in " << base.side << " headquarter\n";
}

void happen50_report_base(headquarter& red, headquarter& blue) {
    report_base(red);
    report_base(blue);
}

void report_warrior(warrior* w) {
    if (w == nullptr) return;
    int sword_cnt = 0, bomb_cnt = 0, arrow_cnt = 0;
    w->clear_weapons();
    w->sort_weapons(true);
    for (weapon* p : w->weapons) {
        if (p == nullptr) continue;
        if (p->name == "sword") sword_cnt++;
        if (p->name == "bomb") bomb_cnt++;
        if (p->name == "arrow") arrow_cnt++;
    }
    cout << get_format_clock() << " " << w->side << " " << w->name << " " << w->id 
         << " has " << sword_cnt << " sword " << bomb_cnt << " bomb " << arrow_cnt 
         << " arrow and " << w->hp << " elements\n";
}

void happen55_report_warriors() {
    for (int i = 1; i < cities.size() - 1; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        report_warrior(r);
        report_warrior(b);
    }
}

void init_game() {
    current_time = 0;
    blue_conquered = false;
    red_conquered = false;
    
    buildOrder["blue"] = {"lion", "dragon", "ninja", "iceman", "wolf"};
    buildOrder["red"] = {"iceman", "lion", "wolf", "ninja", "dragon"};
    
    if (sw == nullptr) sw = new sword("sword");
    
    for (city& c : cities) {
        if (c.first != nullptr) delete c.first;
        if (c.second != nullptr) delete c.second;
    }
    cities.clear();
    for (int i = 0; i < cityCount + 2; i++) {
        cities.push_back(city(nullptr, nullptr));
    }
}

int main() {
    int tot;
    if (!(cin >> tot)) return 0;
    
    for (int c = 1; c <= tot; c++) {
        printf("Case %d:\n", c);
        int tot_elements;
        cin >> tot_elements >> cityCount >> loyaltyDecrease >> timeLimit;
        
        cin >> initialHPs["dragon"] >> initialHPs["ninja"] 
            >> initialHPs["iceman"] >> initialHPs["lion"] 
            >> initialHPs["wolf"];
            
        cin >> initialForces["dragon"] >> initialForces["ninja"] 
            >> initialForces["iceman"] >> initialForces["lion"] 
            >> initialForces["wolf"];
            
        init_game();
        
        headquarter red("red", tot_elements);
        headquarter blue("blue", tot_elements);
        
        while (current_time <= timeLimit && !blue_conquered && !red_conquered) {
            if (current_time % 60 == 0) happen00_warrior_born(red, blue);
            else if (current_time % 60 == 5) happen05_lion_escape();
            else if (current_time % 60 == 10) happen10_warrior_march();
            else if (current_time % 60 == 35) happen35_wolf_rob();
            else if (current_time % 60 == 40) happen40_war();
            else if (current_time % 60 == 50) happen50_report_base(red, blue);
            else if (current_time % 60 == 55) happen55_report_warriors();
            
            current_time += 5;
        }
    }
    return 0;
}