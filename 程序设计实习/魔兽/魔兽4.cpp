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
#include<iomanip>
#include<unordered_map>
#include<sstream>
#include<algorithm>

using namespace std;

int current_time = 0;//当前时间
bool red_conquered = false;
bool blue_conquered = false;
int loyaltyDecrease, timeLimit, cityCount, arrowPower;

unordered_map<string, int> initialHPs;
unordered_map<string, int> initialForces;
unordered_map<string, vector<string>> buildOrder;
vector<string> weapon_kinds = {"sword", "bomb", "arrow"};

enum fight_result { BOTH_DEAD, BOTH_ALIVE, BLUE_WIN, RED_WIN, NO_FIGHT };
const int NO_SIDE = 0;
const int RED_SIDE = 1;
const int BLUE_SIDE = 2;
const int SWORD_ID = 0;
const int BOMB_ID = 1;
const int ARROW_ID = 2;

string get_format_clock() {
    int hour = current_time / 60;
    int minute = current_time % 60;
    ostringstream ost;
    ost << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return ost.str();
}

string side_name(int side) {
    return side == RED_SIDE ? "red" : "blue";
}

int side_id(const string& side) {
    return side == "red" ? RED_SIDE : BLUE_SIDE;
}

int weapon_index(const string& name) {
    if (name == "sword") return SWORD_ID;
    if (name == "bomb") return BOMB_ID;
    return ARROW_ID;
}

class weapon {
public:
    string name;
    weapon(string name_) : name(name_) {}
    virtual ~weapon() {}
    virtual void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) {}
    virtual bool is_usable() { return true; }
};

class sword : public weapon {
public:
    int power;
    sword(string name_, int power_) : weapon(name_), power(power_) {}
    void attack(int attacker_force, string attacker_name, int& attacker_hp, int& injure_hp) override {
        injure_hp -= power;
        power = power * 8 / 10;
    }
    bool is_usable() override { return power > 0; }
};

class bomb : public weapon {
public:
    bool usable;//是否可以使用
    bomb(string name_) : weapon(name_), usable(true) {}
    bool is_usable() override { return usable; }
};

class arrow : public weapon {
public:
    int use_count; // 这里表示剩余可用次数，出生时为3
    arrow(string name_, int use_count_) : weapon(name_), use_count(use_count_) {}
    bool is_usable() override { return use_count > 0; }
};

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
        : id(id_), hp(hp_), force(force_), side(side_), name(name_), location(location_), cur_weapon_ind(0) {
        weapons = vector<weapon*>(3, nullptr);
    }

   
    warrior(warrior& w) {
        id = w.id;
        hp = w.hp;
        force = w.force;
        side = w.side;
        name = w.name;
        location = w.location;
        cur_weapon_ind = w.cur_weapon_ind;
        weapons = w.weapons;
        w.weapons.assign(3, nullptr);
    }

    virtual ~warrior() {
        for (weapon* p : weapons) delete p;
    }

    virtual void after_march() {}

    virtual void march() {
        int direction = (side == "red" ? 1 : -1);
        location += direction;
        after_march();
        cout << get_format_clock() << " " << side << " " << name << " " << id
             << " marched to city " << location << " with " << hp
             << " elements and force " << force << endl;
    }

    virtual void reach_headquarter() {
        int direction = (side == "red" ? 1 : -1);
        location += direction;
        after_march();
        string enemy_side = side == "blue" ? "red" : "blue";
        cout << get_format_clock() << " " << side << " " << name << " " << id
             << " reached " << enemy_side << " headquarter with " << hp
             << " elements and force " << force << endl;
    }

    void sort_weapons(bool used_first) {
        clear_weapons();
    }

    int count_weapons() {
        clear_weapons();
        int cnt = 0;
        for (weapon* p : weapons) if (p != nullptr) cnt++;
        return cnt;
    }

    void clear_weapons() {
        for (int i = 0; i < 3; i++) {
            if (weapons[i] != nullptr && !weapons[i]->is_usable()) {
                delete weapons[i];
                weapons[i] = nullptr;
            }
        }
    }

    bool has_weapon(const string& weapon_name) {
        int ind = weapon_index(weapon_name);
        clear_weapons();
        return weapons[ind] != nullptr;
    }

    sword* get_sword() {
        clear_weapons();
        return dynamic_cast<sword*>(weapons[SWORD_ID]);
    }

    bomb* get_bomb() {
        clear_weapons();
        return dynamic_cast<bomb*>(weapons[BOMB_ID]);
    }

    arrow* get_arrow() {
        clear_weapons();
        return dynamic_cast<arrow*>(weapons[ARROW_ID]);
    }

    int sword_power() {
        sword* s = get_sword();
        return s == nullptr ? 0 : s->power;
    }

    int use_sword() {
        sword* s = get_sword();
        if (s == nullptr) return 0;
        int ret = s->power;
        s->power = s->power * 8 / 10;
        clear_weapons();
        return ret;
    }

    int attack_damage(bool fight_back = false) {
        int base_force = fight_back ? force / 2 : force;
        return base_force + use_sword();
    }

    int predict_damage(bool fight_back = false) {
        int base_force = fight_back ? force / 2 : force;
        return base_force + sword_power();
    }

    void hurt(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    void set_weapon(weapon* w) {
        if (w == nullptr) return;
        int ind = weapon_index(w->name);
        if (weapons[ind] != nullptr) delete weapons[ind];
        weapons[ind] = w;
    }

    void take_weapons_after_fight(warrior* enemy) {
        if (this == enemy || hp <= 0 || enemy == nullptr) return;
        if (name != "wolf") return;
        clear_weapons();
        enemy->clear_weapons();
        for (int i = 0; i < 3; i++) {
            if (weapons[i] == nullptr && enemy->weapons[i] != nullptr) {
                weapons[i] = enemy->weapons[i];
                enemy->weapons[i] = nullptr;
            }
        }
    }

    bool is_alive() { return hp > 0; }

    weapon* find_proper_weapon() { return nullptr; }

    void attack(warrior* enemy) {
        if (enemy == nullptr) return;
        enemy->hurt(attack_damage(false));
    }

    bool reached_enemy_headquarter() {
        return (side == "red" && location == cityCount + 1) ||
               (side == "blue" && location == 0);
    }
};

class dragon : public warrior {
public:
    double morale;
    dragon(warrior& w, double morale_) : warrior(w), morale(morale_) {}
    void yell(vector<string>* logs = nullptr) {
        ostringstream ost;
        ost << get_format_clock() << " " << side << " " << name << " " << id
            << " yelled in city " << location;
        if (logs) logs->push_back(ost.str());
        else cout << ost.str() << endl;
    }
};

class lion : public warrior {
public:
    int loyalty;
    lion(warrior& w, int loyalty_) : warrior(w), loyalty(loyalty_) {}

    void march() override {
        warrior::march();
    }

    bool escape() {
        if (reached_enemy_headquarter()) return false;
        if (loyalty > 0) return false;
        cout << get_format_clock() << " " << side << " lion " << id << " ran away\n";
        return true;
    }
};

class iceman : public warrior {
public:
    int march_steps;
    iceman(warrior& w) : warrior(w), march_steps(0) {}
    void after_march() override {
        march_steps++;
        if (march_steps % 2 == 0) {
            if (hp - 9 <= 0) hp = 1;
            else hp -= 9;
            force += 20;
        }
    }
};

class wolf : public warrior {
public:
    wolf(warrior& w) : warrior(w) {}
    void rob_weapons(warrior* enemy) {
        take_weapons_after_fight(enemy);
    }
};

class ninja : public warrior {
public:
    ninja(warrior& w) : warrior(w) {}
};

class city {
public:
    warrior* first;   // red warrior
    warrior* second;  // blue warrior
    int elements;
    int flag;         // 0 none, 1 red, 2 blue
    int lastWinner;   // 上一次在本城市杀死敌人的一方；平局清零

    city(warrior* red = nullptr, warrior* blue = nullptr)
        : first(red), second(blue), elements(0), flag(NO_SIDE), lastWinner(NO_SIDE) {}
};

vector<city> cities;

void warrior_born(warrior& w);

class headquarter {
public:
    string side;
    int totalLife;
    int totalCount;
    int currentIdx;
    int enemyCount;

    headquarter(string side_, int totalLife_)
        : side(side_), totalLife(totalLife_), totalCount(0), currentIdx(0), enemyCount(0) {}

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

    weapon* make_weapon(string name, int warrior_force) {
        if (name == "sword") {
            int sword_power = warrior_force * 2 / 10;
            if (sword_power == 0) return nullptr;
            return new sword(name, sword_power);
        }
        if (name == "bomb") return new bomb(name);
        if (name == "arrow") return new arrow(name, 3);
        return nullptr;
    }

    warrior* further_process(warrior* p) {
        if (p == nullptr) return nullptr;

        string w_name = p->name;
        warrior* ret = nullptr;

        if (w_name == "dragon") {
            string weapon_name = weapon_kinds[p->id % 3];
            p->set_weapon(make_weapon(weapon_name, p->force));
            double morale = 1.0 * totalLife / initialHPs[w_name];
            ret = new dragon(*p, morale);
        } else if (w_name == "ninja") {
            string weapon_name1 = weapon_kinds[p->id % 3];
            string weapon_name2 = weapon_kinds[(p->id + 1) % 3];
            p->set_weapon(make_weapon(weapon_name1, p->force));
            p->set_weapon(make_weapon(weapon_name2, p->force));
            ret = new ninja(*p);
        } else if (w_name == "iceman") {
            string weapon_name = weapon_kinds[p->id % 3];
            p->set_weapon(make_weapon(weapon_name, p->force));
            ret = new iceman(*p);
        } else if (w_name == "lion") {
            ret = new lion(*p, totalLife);
        } else if (w_name == "wolf") {
            ret = new wolf(*p);
        }
        delete p;
        return ret;
    }

    void make_warriors() {
        warrior* p = further_process(make_warrior());
        if (p != nullptr) {
            warrior_born(*p);
            if (p->side == "red") {
                cities[0].first = p;
            } else {
                cities[cityCount + 1].second = p;
            }
        }
    }
};

void warrior_born(warrior& w) {
    cout << get_format_clock() << " " << w.side << " " << w.name << " " << w.id << " born\n";
    if (w.name == "dragon") {
        dragon* d = dynamic_cast<dragon*>(&w);
        cout << "Its morale is " << fixed << setprecision(2) << d->morale << endl;
    } else if (w.name == "lion") {
        lion* l = dynamic_cast<lion*>(&w);
        cout << "Its loyalty is " << l->loyalty << endl;
    }
}

void happen00_warrior_born(headquarter& red, headquarter& blue) {
    red.make_warriors();
    blue.make_warriors();
}

void happen05_lion_escape() {
    for (int i = 0; i <= cityCount + 1; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        if (r != nullptr && r->name == "lion") {
            lion* l = dynamic_cast<lion*>(r);
            if (l->escape()) {
                delete cities[i].first;
                cities[i].first = nullptr;
            }
        }
        if (b != nullptr && b->name == "lion") {
            lion* l = dynamic_cast<lion*>(b);
            if (l->escape()) {
                delete cities[i].second;
                cities[i].second = nullptr;
            }
        }
    }
}

struct MoveEvent {
    int dest;
    int order;
    warrior* w;
};

void happen10_warrior_march(headquarter& red, headquarter& blue) {
    vector<MoveEvent> moves;

    for (int i = 0; i <= cityCount; i++) {
        if (cities[i].first != nullptr) {
            moves.push_back({i + 1, 0, cities[i].first});
            cities[i].first = nullptr;
        }
    }
    for (int i = cityCount + 1; i >= 1; i--) {
        if (cities[i].second != nullptr) {
            moves.push_back({i - 1, 1, cities[i].second});
            cities[i].second = nullptr;
        }
    }

    sort(moves.begin(), moves.end(), [](const MoveEvent& a, const MoveEvent& b) {
        if (a.dest != b.dest) return a.dest < b.dest;
        return a.order < b.order; // 同一城市红武士先输出，蓝武士后输出
    });

    for (MoveEvent& e : moves) {
        warrior* w = e.w;
        if (e.dest == 0 || e.dest == cityCount + 1) {
            w->reach_headquarter();
            if (e.dest == 0) {
                red.enemyCount++;
                if (cities[0].second == nullptr) cities[0].second = w;
                else delete w;
                if (red.enemyCount == 2) {
                    cout << get_format_clock() << " red headquarter was taken\n";
                    red_conquered = true;
                }
            } else {
                blue.enemyCount++;
                if (cities[cityCount + 1].first == nullptr) cities[cityCount + 1].first = w;
                else delete w;
                if (blue.enemyCount == 2) {
                    cout << get_format_clock() << " blue headquarter was taken\n";
                    blue_conquered = true;
                }
            }
        } else {
            w->march();
            if (w->side == "red") cities[e.dest].first = w;
            else cities[e.dest].second = w;
        }
    }
}

void happen20_city_produce() {
    for (int i = 1; i <= cityCount; i++) cities[i].elements += 10;
}

void happen30_city_life(headquarter& red, headquarter& blue) {
    for (int i = 1; i <= cityCount; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        bool red_alive = (r != nullptr && r->is_alive());
        bool blue_alive = (b != nullptr && b->is_alive());
        if (cities[i].elements == 0) continue;
        if (red_alive && !blue_alive) {
            cout << get_format_clock() << " red " << r->name << " " << r->id
                 << " earned " << cities[i].elements << " elements for his headquarter\n";
            red.totalLife += cities[i].elements;
            cities[i].elements = 0;
        } else if (!red_alive && blue_alive) {
            cout << get_format_clock() << " blue " << b->name << " " << b->id
                 << " earned " << cities[i].elements << " elements for his headquarter\n";
            blue.totalLife += cities[i].elements;
            cities[i].elements = 0;
        }
    }
}

struct ArrowEvent {
    int location;
    int order;
    warrior* shooter;
    warrior* target;
};

void happen35_arrow_shot() {
    vector<ArrowEvent> actions;
    for (int i = 1; i <= cityCount; i++) {
        warrior* r = cities[i].first;
        if (r != nullptr && r->is_alive() && r->get_arrow() != nullptr && i + 1 <= cityCount) {
            warrior* target = cities[i + 1].second;
            if (target != nullptr && target->is_alive()) actions.push_back({i, 0, r, target});
        }
        warrior* b = cities[i].second;
        if (b != nullptr && b->is_alive() && b->get_arrow() != nullptr && i - 1 >= 1) {
            warrior* target = cities[i - 1].first;
            if (target != nullptr && target->is_alive()) actions.push_back({i, 1, b, target});
        }
    }

    for (ArrowEvent& e : actions) {
        arrow* a = e.shooter->get_arrow();
        if (a == nullptr) continue;
        e.target->hurt(arrowPower);
        a->use_count--;
    }

    sort(actions.begin(), actions.end(), [](const ArrowEvent& a, const ArrowEvent& b) {
        if (a.location != b.location) return a.location < b.location;
        return a.order < b.order;
    });

    for (ArrowEvent& e : actions) {
        e.shooter->clear_weapons();
        cout << get_format_clock() << " " << e.shooter->side << " " << e.shooter->name << " " << e.shooter->id << " shot";
        if (!e.target->is_alive()) {
            cout << " and killed " << e.target->side << " " << e.target->name << " " << e.target->id;
        }
        cout << endl;
    }
}

int get_attacker_side(int city_id) {
    if (cities[city_id].flag != NO_SIDE) return cities[city_id].flag;
    return (city_id % 2 == 1) ? RED_SIDE : BLUE_SIDE;
}

bool should_use_bomb(warrior* self, warrior* enemy, bool self_attack_first) {
    if (self == nullptr || enemy == nullptr || !self->is_alive() || !enemy->is_alive()) return false;
    if (self->get_bomb() == nullptr) return false;

    if (self_attack_first) {
        int attack_dmg = self->predict_damage(false);
        if (enemy->hp <= attack_dmg) return false; // 敌人会先死，自己不会被反击杀死
        if (enemy->name == "ninja") return false;
        int back_dmg = enemy->predict_damage(true);
        return self->hp <= back_dmg;
    } else {
        int enemy_attack_dmg = enemy->predict_damage(false);
        return self->hp <= enemy_attack_dmg;
    }
}

void happen38_bomb() {
    for (int i = 1; i <= cityCount; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        if (r == nullptr || b == nullptr || !r->is_alive() || !b->is_alive()) continue;

        int attackerSide = get_attacker_side(i);
        warrior* attacker = (attackerSide == RED_SIDE) ? r : b;
        warrior* defender = (attackerSide == RED_SIDE) ? b : r;
        warrior* user = nullptr;

        if (should_use_bomb(defender, attacker, false)) user = defender;
        else if (should_use_bomb(attacker, defender, true)) user = attacker;

        if (user != nullptr) {
            warrior* enemy = (user == r) ? b : r;
            cout << get_format_clock() << " " << user->side << " " << user->name << " " << user->id
                 << " used a bomb and killed " << enemy->side << " " << enemy->name << " " << enemy->id << endl;
            delete cities[i].first;
            delete cities[i].second;
            cities[i].first = cities[i].second = nullptr;
        }
    }
}

string attack_log(warrior* a, warrior* d, int city_id) {
    ostringstream ost;
    ost << get_format_clock() << " " << a->side << " " << a->name << " " << a->id
        << " attacked " << d->side << " " << d->name << " " << d->id
        << " in city " << city_id << " with " << a->hp << " elements and force " << a->force;
    return ost.str();
}

string fight_back_log(warrior* a, warrior* d, int city_id) {
    ostringstream ost;
    ost << get_format_clock() << " " << a->side << " " << a->name << " " << a->id
        << " fought back against " << d->side << " " << d->name << " " << d->id
        << " in city " << city_id;
    return ost.str();
}

string killed_log(warrior* w, int city_id) {
    ostringstream ost;
    ost << get_format_clock() << " " << w->side << " " << w->name << " " << w->id
        << " was killed in city " << city_id;
    return ost.str();
}

void update_dragon_morale(warrior* w, bool win) {
    dragon* d = dynamic_cast<dragon*>(w);
    if (d == nullptr || !d->is_alive()) return;
    d->morale += win ? 0.2 : -0.2;
}

void decrease_lion_loyalty(warrior* w) {
    lion* l = dynamic_cast<lion*>(w);
    if (l != nullptr && l->is_alive()) l->loyalty -= loyaltyDecrease;
}

void lion_hp_transfer(warrior* dead, warrior* winner, int dead_pre_hp) {
    if (dead != nullptr && winner != nullptr && dead->name == "lion" && winner->is_alive()) {
        winner->hp += dead_pre_hp;
    }
}

void happen40_war(headquarter& red, headquarter& blue) {
    vector<vector<string>> logs(cityCount + 2);
    vector<int> winnerSide(cityCount + 2, NO_SIDE);
    vector<warrior*> winnerWarrior(cityCount + 2, nullptr);
    vector<bool> tie(cityCount + 2, false);

    for (int i = 1; i <= cityCount; i++) {
        warrior *r = cities[i].first, *b = cities[i].second;
        if (r == nullptr || b == nullptr) continue;

        bool red_alive = r->is_alive();
        bool blue_alive = b->is_alive();
        int attackerSide = get_attacker_side(i);
        warrior* attacker = (attackerSide == RED_SIDE) ? r : b;
        warrior* defender = (attackerSide == RED_SIDE) ? b : r;

        if (!red_alive && !blue_alive) {
            continue;
        } else if (red_alive && !blue_alive) {
            winnerSide[i] = RED_SIDE;
            winnerWarrior[i] = r;
            update_dragon_morale(r, true);
            r->take_weapons_after_fight(b);
            if (attackerSide == RED_SIDE) {
                dragon* d = dynamic_cast<dragon*>(r);
                if (d != nullptr && d->morale > 0.8) d->yell(&logs[i]);
            }
            continue;
        } else if (!red_alive && blue_alive) {
            winnerSide[i] = BLUE_SIDE;
            winnerWarrior[i] = b;
            update_dragon_morale(b, true);
            b->take_weapons_after_fight(r);
            if (attackerSide == BLUE_SIDE) {
                dragon* d = dynamic_cast<dragon*>(b);
                if (d != nullptr && d->morale > 0.8) d->yell(&logs[i]);
            }
            continue;
        }

        int red_pre_hp = r->hp;
        int blue_pre_hp = b->hp;

        logs[i].push_back(attack_log(attacker, defender, i));
        defender->hurt(attacker->attack_damage(false));

        if (!defender->is_alive()) {
            logs[i].push_back(killed_log(defender, i));
            winnerSide[i] = side_id(attacker->side);
            winnerWarrior[i] = attacker;
            update_dragon_morale(attacker, true);
            lion_hp_transfer(defender, attacker, defender == r ? red_pre_hp : blue_pre_hp);
            attacker->take_weapons_after_fight(defender);
        } else {
            if (defender->name != "ninja") {
                logs[i].push_back(fight_back_log(defender, attacker, i));
                attacker->hurt(defender->attack_damage(true));
                if (!attacker->is_alive()) {
                    logs[i].push_back(killed_log(attacker, i));
                    winnerSide[i] = side_id(defender->side);
                    winnerWarrior[i] = defender;
                    update_dragon_morale(defender, true);
                    lion_hp_transfer(attacker, defender, attacker == r ? red_pre_hp : blue_pre_hp);
                    defender->take_weapons_after_fight(attacker);
                }
            }
        }

        if (winnerSide[i] == NO_SIDE) {
            tie[i] = true;
            update_dragon_morale(r, false);
            update_dragon_morale(b, false);
            decrease_lion_loyalty(r);
            decrease_lion_loyalty(b);
        }

        // dragon 只有在“自己主动进攻”的战斗结束后仍存活且士气>0.8才欢呼。
        if (attacker->is_alive()) {
            dragon* d = dynamic_cast<dragon*>(attacker);
            if (d != nullptr && d->morale > 0.8) d->yell(&logs[i]);
        }
    }

    // 司令部先奖励，红方优先奖励靠近蓝方司令部的武士，蓝方反之。
    for (int i = cityCount; i >= 1; i--) {
        if (winnerSide[i] == RED_SIDE && winnerWarrior[i] != nullptr && winnerWarrior[i]->is_alive()) {
            if (red.totalLife >= 8) {
                red.totalLife -= 8;
                winnerWarrior[i]->hp += 8;
            }
        }
    }
    for (int i = 1; i <= cityCount; i++) {
        if (winnerSide[i] == BLUE_SIDE && winnerWarrior[i] != nullptr && winnerWarrior[i]->is_alive()) {
            if (blue.totalLife >= 8) {
                blue.totalLife -= 8;
                winnerWarrior[i]->hp += 8;
            }
        }
    }

    // 再回收城市生命元，并处理旗帜。输出仍按城市从西到东。
    for (int i = 1; i <= cityCount; i++) {
        if (winnerSide[i] != NO_SIDE && winnerWarrior[i] != nullptr) {
            warrior* w = winnerWarrior[i];
            if (cities[i].elements > 0) {
                ostringstream ost;
                ost << get_format_clock() << " " << w->side << " " << w->name << " " << w->id
                    << " earned " << cities[i].elements << " elements for his headquarter";
                logs[i].push_back(ost.str());
                if (winnerSide[i] == RED_SIDE) red.totalLife += cities[i].elements;
                else blue.totalLife += cities[i].elements;
                cities[i].elements = 0;
            }

            if (cities[i].lastWinner == winnerSide[i]) {
                if (cities[i].flag != winnerSide[i]) {
                    cities[i].flag = winnerSide[i];
                    ostringstream ost;
                    ost << get_format_clock() << " " << side_name(winnerSide[i]) << " flag raised in city " << i;
                    logs[i].push_back(ost.str());
                }
            } else {
                cities[i].lastWinner = winnerSide[i];
            }
        } else if (tie[i]) {
            cities[i].lastWinner = NO_SIDE;
        }

        for (string& s : logs[i]) cout << s << endl;

        if (cities[i].first != nullptr && !cities[i].first->is_alive()) {
            delete cities[i].first;
            cities[i].first = nullptr;
        }
        if (cities[i].second != nullptr && !cities[i].second->is_alive()) {
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
    if (w == nullptr || !w->is_alive()) return;
    w->clear_weapons();
    cout << get_format_clock() << " " << w->side << " " << w->name << " " << w->id << " has ";

    vector<string> reports;
    arrow* a = w->get_arrow();
    if (a != nullptr) {
        ostringstream ost;
        ost << "arrow(" << a->use_count << ")";
        reports.push_back(ost.str());
    }
    bomb* b = w->get_bomb();
    if (b != nullptr) reports.push_back("bomb");
    sword* s = w->get_sword();
    if (s != nullptr) {
        ostringstream ost;
        ost << "sword(" << s->power << ")";
        reports.push_back(ost.str());
    }

    if (reports.empty()) {
        cout << "no weapon\n";
    } else {
        for (int i = 0; i < (int)reports.size(); i++) {
            if (i) cout << ",";
            cout << reports[i];
        }
        cout << endl;
    }
}

void happen55_report_warriors() {
    for (int i = 0; i <= cityCount + 1; i++) report_warrior(cities[i].first);
    for (int i = 0; i <= cityCount + 1; i++) report_warrior(cities[i].second);
}

void init_game() {
    current_time = 0;
    blue_conquered = false;
    red_conquered = false;

    buildOrder["blue"] = {"lion", "dragon", "ninja", "iceman", "wolf"};
    buildOrder["red"] = {"iceman", "lion", "wolf", "ninja", "dragon"};

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
        cout << "Case " << c << ":\n";
        int tot_elements;
        cin >> tot_elements >> cityCount >> arrowPower >> loyaltyDecrease >> timeLimit;

        cin >> initialHPs["dragon"] >> initialHPs["ninja"]
            >> initialHPs["iceman"] >> initialHPs["lion"]
            >> initialHPs["wolf"];

        cin >> initialForces["dragon"] >> initialForces["ninja"]
            >> initialForces["iceman"] >> initialForces["lion"]
            >> initialForces["wolf"];

        init_game();

        headquarter red("red", tot_elements);
        headquarter blue("blue", tot_elements);

        for (current_time = 0; current_time <= timeLimit && !blue_conquered && !red_conquered; current_time++) {
            int minute = current_time % 60;
            if (minute == 0) happen00_warrior_born(red, blue);
            else if (minute == 5) happen05_lion_escape();
            else if (minute == 10) happen10_warrior_march(red, blue);
            else if (minute == 20) happen20_city_produce();
            else if (minute == 30) happen30_city_life(red, blue);
            else if (minute == 35) happen35_arrow_shot();
            else if (minute == 38) happen38_bomb();
            else if (minute == 40) happen40_war(red, blue);
            else if (minute == 50) happen50_report_base(red, blue);
            else if (minute == 55) happen55_report_warriors();
        }
    }
    return 0;
}
