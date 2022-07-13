#include "seqQueue.h"

/*
新学期开始了，小哈是小哼的新同学，小哼向小哈询问QQ号，小哈当然不会直接告诉小哼。所以小哈给了小哼一串加密过的数字，
同时小哈也告诉了小哼解密规则。规则是这样的：首先将第1个数删除，紧接着将第2个数放到这串数的末尾，再将第3个数删除并将第4个数再放到这串数的末尾，
再将第5个数删除……直到剩下最后一个数，将最后一个数也删除。按照刚才删除的顺序，把这些删除的数连在一起就是小哈的QQ啦。现在你来帮帮小哼吧。
小哈给小哼加密过的一串数是6 3 1 7 5 8 9 2 4。解密后小哈的QQ号应该是6 1 5 9 4 7 2 8 3。

输入描述：
只有2行，第1行有一个整数n (1 ≤ n ≤ 10^5)
第2行有n个整数为加密过的QQ号，每个整数之间用空格隔开。每个整数在 1~9 之间。
对于100%的数据满足1 ≤ n ≤ 10^5。
输出描述：
只有一行，输出解密后的QQ号。

示例 1：
输入：
9
6 3 1 7 5 8 9 2 4
输出：
6 1 5 9 4 7 2 8 3
*/

int main() {
    // 顺序队列实现
    
    int num, d;
    cin >> num;
    seqQueue<int> sq(num+1);        //因为头指针赋值为0，所以在使用时，申请空间要+1
   
    for (int i=1; i<=num; ++i) {
        cin >> d;
        sq.enQueue(d);
    }

    int out1;
    int flag = 0;
    while (!sq.isEmpty()) {
        out1 = sq.deQueue();
        if (!flag) {
            cout << out1 << " ";
        }else {
            sq.enQueue(out1);
        }
        flag ^= 1;              //这个用法很漂亮
    }
    cout << endl;

    // seqQueue<int> out(num+1);
    // while (true) {
    //     out1 = sq.deQueue();
    //     out.enQueue(out1);
    //     if (sq.isEmpty()) {
    //         break;
    //     }
    //     out1 = sq.deQueue();
    //     if (sq.isEmpty()) {
    //         out.enQueue(out1);
    //         break;
    //     }
    //     sq.enQueue(out1);
    // }

    // while (!out.isEmpty()) {
    //     cout << out.deQueue() << " ";
    // }
    // cout << endl;

    system("pause");
    return 0;
}

/*
#include <cstdio> 
#include <cstring> 
#include <iostream> 
#include <algorithm> 
#define N 1000005 
using namespace std; 

int n; 
int q[N], l, r;  

int main() { 
    int n; 
    scanf("%d", &n); 

    l = r = 0; 
    for (int i = 1; i <= n; ++i) { 
        int x; 
        scanf("%d", &x); 
        q[r++] = x; 
    } 

    int flag = 0; 
    while (l < r) { 
        int x = q[l++]; 
        if (!flag) printf("%d ", x); 
        else q[r++] = x; 
        flag ^= 1; 
    } 
    return 0; 
}


*/