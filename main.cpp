#include <iostream>
#include <iomanip>

using namespace std;

#define n 5 //进程数
#define m 3 //资源数

int Available[m]; //系统可用资源
int Alloc[n][m]; //已分配资源
int Need[n][m]; //需求资源
bool Finish[n]; //进程是否完成
int work[m]; //工作向量
int seq[n]; //安全序列

//初始化数据
//已分配资源数量	资源需求量
//进程	A	B	C	A	B	C   
//P1	2	1	2	3	4	7
//P2	4	0	2	1	3	4
//P3	3	0	5	0	0	3
//P4	2	0	4	2	2	1
//P5	0	1	4	1	1	0


void input(){
    cout<<"初始化数据。。。"<<endl;

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

 //显示当前资源
 void display(){
    cout<<"当前资源情况："<<endl;
    cout << "进程\t分配资源\t\t需求资源" << endl;
    cout << "\tA  B  C\t\tA  B  C" << endl;

    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<"\t";
        for(int j=0;j<m;j++){
            cout<<Alloc[i][j]<<"  ";
        }
        cout<<"\t\t";
        for(int j=0;j<m;j++){
            cout<<Need[i][j]<<"  ";
        }
        cout<<endl;
    }

    cout<<"\n可用资源:";
    for(int j=0;j<m;j++){
        cout<<Available[j]<<"  ";
    }
    cout<<endl;
 }

 //安全性检查
 bool safe(){
    //初始化
 }