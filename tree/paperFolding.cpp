#include <iostream>
using namespace std;

//down = true ��ʾ"��"
//up = false ��ʾ"͹" 
void printFold(int times, int total, bool flag) {
    if (times > total) return;

    //���������� flag��Ϊtrue
    printFold(times+1, total, true);
    //������(��ӡ)�˴νڵ��ֵ
    flag ? cout << times << "��" << " " : cout <<  times << "͹" << " ";
    //������͹��flag��Ϊfalse
    printFold(times+1, total, false);
}


int main() {
    int foldTimes = 4;      //�ܹ���ֽ�Ĵ�����Ҳ���Ƕ������Ĳ���
    printFold(1,foldTimes,true);    //�ӵ�һ�㿪ʼ�㣬��ֻ��һ��ʱ��Ϊ����flag����true

    system("pause");
    return 0;
}