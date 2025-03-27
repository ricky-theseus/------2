#include <iostream>
#include <iomanip>
using namespace std;

#define n 5   // 进程个数
#define m 3   // 资源种类

int Available[m];    // 可用资源向量
int Alloc[n][m];     // 已分配资源矩阵  
int Need[n][m];      // 需求矩阵
bool Finish[n];      // 完成向量
int Work[m];         // 工作向量
int seq[n];          // 安全序列

// 初始化系统资源
void input() {
    cout << "初始化系统资源状态..." << endl;
    
    // 初始化Available
    Available[0] = 2;  // 资源A
    Available[1] = 3;  // 资源B
    Available[2] = 3;  // 资源C
    
    // 初始化已分配资源Alloc
    Alloc[0][0] = 2; Alloc[0][1] = 1; Alloc[0][2] = 2;  // P1
    Alloc[1][0] = 4; Alloc[1][1] = 0; Alloc[1][2] = 2;  // P2
    Alloc[2][0] = 3; Alloc[2][1] = 0; Alloc[2][2] = 5;  // P3
    Alloc[3][0] = 2; Alloc[3][1] = 0; Alloc[3][2] = 4;  // P4
    Alloc[4][0] = 3; Alloc[4][1] = 1; Alloc[4][2] = 4;  // P5
    
    // 初始化需求矩阵Need
    Need[0][0] = 3; Need[0][1] = 4; Need[0][2] = 7;  // P1
    Need[1][0] = 1; Need[1][1] = 3; Need[1][2] = 4;  // P2
    Need[2][0] = 0; Need[2][1] = 0; Need[2][2] = 3;  // P3
    Need[3][0] = 2; Need[3][1] = 2; Need[3][2] = 1;  // P4
    Need[4][0] = 1; Need[4][1] = 1; Need[4][2] = 0;  // P5
}

// 显示当前资源状态
void display_state() {
    cout << "\n当前系统资源状态:" << endl;
    cout << "进程\t分配资源\t\t需求资源" << endl;
    cout << "\tA  B  C\t\tA  B  C" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t";
        for (int j = 0; j < m; j++) {
            cout << Alloc[i][j] << "  ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++) {
            cout << Need[i][j] << "  ";
        }
        cout << endl;
    }
    
    cout << "\n可用资源: ";
    for (int j = 0; j < m; j++) {
        cout << Available[j] << "  ";
    }
    cout << endl;
}

// 安全状态检查
bool is_safe() {
    // (1) 设置Finish=(false,...,false) work=Available
    for (int i = 0; i < n; i++) {
        Finish[i] = false;
    }
    
    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }
    
    int count = 0;  // 计数器记录找到的安全进程数
    
    // (2)(3) 循环查找满足条件的进程
    while (count < n) {
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                // 检查需求是否能被满足
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // 进程i可以完成
                    for (int j = 0; j < m; j++) {
                        Work[j] += Alloc[i][j];
                    }
                    Finish[i] = true;
                    seq[count] = i;  // 记录安全序列
                    count++;
                    found = true;
                }
            }
        }
        
        // 如果本轮没找到符合条件的进程，退出循环
        if (!found) {
            break;
        }
    }
    
    // (4) 若Finish=(true,...,true) 则安全，否则不安全
    return (count == n);
}

// 处理资源请求
bool request_resources(int pid, int request[]) {
    cout << "\n进程P" << pid+1 << "请求资源: (";
    for (int i = 0; i < m; i++) {
        cout << request[i];
        if (i < m-1) cout << ",";
    }
    cout << ")" << endl;
    
    // (1) 检查请求是否合法 (requesti <= Needi)
    for (int i = 0; i < m; i++) {
        if (request[i] > Need[pid][i]) {
            cout << "错误: 请求超过了声明的最大需求!" << endl;
            return false;
        }
    }
    
    // (2) 检查资源是否足够 (requesti <= Available)
    for (int i = 0; i < m; i++) {
        if (request[i] > Available[i]) {
            cout << "资源不足，进程P" << pid+1 << "必须等待!" << endl;
            return false;
        }
    }
    
    // (3) 试探性分配
    for (int i = 0; i < m; i++) {
        Available[i] -= request[i];
        Alloc[pid][i] += request[i];
        Need[pid][i] -= request[i];
    }
    
    // (4) 安全性检查
    if (is_safe()) {
        cout << "资源分配成功! 系统处于安全状态." << endl;
        cout << "安全序列为: ";
        for (int i = 0; i < n; i++) {
            cout << "P" << seq[i]+1;
            if (i < n-1) cout << " -> ";
        }
        cout << endl;
        return true;
    } else {
        cout << "分配失败! 系统可能进入不安全状态，撤销分配." << endl;
        
        // 恢复原状态
        for (int i = 0; i < m; i++) {
            Available[i] += request[i];
            Alloc[pid][i] -= request[i];
            Need[pid][i] += request[i];
        }
        return false;
    }
}

int main() {
    int request[m];
    
    // 初始化资源
    input();
    display_state();
    
    cout << "\n======= 开始处理请求序列 =======" << endl;
    
    // a: 进程P2请求资源(0,3,4)
    cout << "\n测试请求a:";
    request[0] = 0; request[1] = 3; request[2] = 4;
    request_resources(1, request);  // P2的索引为1
    display_state();
    
    // b: 进程P4请求资源(1,0,1)
    cout << "\n测试请求b:";
    request[0] = 1; request[1] = 0; request[2] = 1;
    request_resources(3, request);  // P4的索引为3
    display_state();
    
    // c: 进程P1请求资源(2,0,1)
    cout << "\n测试请求c:";
    request[0] = 2; request[1] = 0; request[2] = 1;
    request_resources(0, request);  // P1的索引为0
    display_state();
    
    // d: 进程P3请求资源(0,0,2)
    cout << "\n测试请求d:";
    request[0] = 0; request[1] = 0; request[2] = 2;
    request_resources(2, request);  // P3的索引为2
    display_state();
    
    return 0;
}