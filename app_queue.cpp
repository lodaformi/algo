/*
队列可以应用于列车车厢重排问题。

问题描述
一列货运列车共有n节车厢，每节车厢将被放在不同的车站。假定n个车站的编号分别为1 – n，货运列车按照第n站到第1站的次序经过这些车站。
车厢的编号与它们的目的地相同。为了便于从列车上卸掉相应的车厢，必须重新排列这些车厢，将第n节车厢放在最后，第1节车厢放在最前面。
*/

// 把车厢in，放入缓冲轨道，buffer是存储缓冲轨道队列的数组，size表示缓冲轨道的数量
// 如果车厢能放入合适的缓冲轨道则返回true，否则返回false
bool putBuffer(linkQueue<int> *buffer, int size, int in) { 
    // 希望把车厢放到编号为avail的缓冲轨道上，max表示所有合适轨道队尾编号最大的车厢
    int avail = -1, max = 0;     

    for (int j = 0 ; j < size; ++j)  {        
        if (buffer[j].isEmpty()) { if (avail == -1) avail = j; }  
        else if (buffer[j].getTail() < in && buffer[j].getTail() > max) {          
            avail = j;
            max = buffer[j].getTail();
        }
    }
    if (avail != -1) {          
        buffer[avail].enQueue(in);
        cout << in << "移入缓冲区 " << avail << endl;
        return true;
    } else {
        cout << "无可行的方案" << endl;
        return false;
    }
}

// 检查能否将缓冲轨道上的车厢移动到输出轨道，last代表输出轨道上最后一列车厢的标号
void checkBuffer( linkQueue<int> *buffer, int size, int &last) {
    // 表示需要检查缓冲轨道
    bool flag = true;    
    while (flag) {       
        flag = false;
        for (int j = 0; j < size; ++j) {    
            if (! buffer[j].isEmpty() &&  buffer[j].getHead() == last + 1) { 
                cout << "将" << buffer[j].deQueue() << "从缓冲区" << j  << "移到出轨" << endl;
                ++last;
                // 有车厢出轨后再次将flag设置为true
                flag = true;
                break;   
            }
        }
    }
}

// in表示输入轨道中车厢的排列，总共n个车厢，通过k个缓冲轨道
void arrange(int in[], int n, int k)
{
     linkQueue<int> *buffer = new linkQueue<int>[k];           
     int last = 0;
     // 依次把每节车厢放入缓冲轨道，然后检查能否将缓冲轨道中的车厢移动到输出轨道
     for (int i = 0; i < n; ++i) {
        // 如果车厢放不进去，表示重排失败，不必再进行下去
	    if ( ! putBuffer(buffer, k, in[i]) ) return;
        checkBuffer(buffer, k, last);
    }
}