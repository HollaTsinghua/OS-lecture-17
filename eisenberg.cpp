#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

enum State {IDLE,WAITING,ACTIVE};

pthread_t thread[5];
enum State flags[5];
int turn=0;

void* process(void* args) {
	int t,index,pid=*(int*)args;
	printf("Process %d starts\n",pid);

	for (t=0;t<3;t++) 
	{
		while (true) 
		{
			flags[pid]=WAITING;

			index=turn;
			while (index!=pid) 
			{
				if (flags[index]!=IDLE) index=turn;
				else index=(index+1)%5;
			}//等待序号排在自己之前的进程执行完毕

			flags[pid]=ACTIVE;//尝试占有共享资源	

			index=0;
			while ((index<5)&&((index==pid)||(flags[index]!= ACTIVE))) index++;
			if ( index >= 5 && (turn == pid || flags[turn] == IDLE) ) break;//占有成功后退出循环
			//占有失败后重新执行循环，并在循环开头将自己的ACTIVE状态撤销
		}
		
		turn = pid;//声明已占有共享资源
		printf("Process %d fetches the resource\n",pid);
		//这里是线程本身要做的事，我们设定所有线程什么都不做，只输出正在运行
		printf("Process %d is running\n",pid); 
		printf("Process %d releases the resource\n",pid);
		
		index=(turn+1)%5;
		while (flags[index]==IDLE) index=(index+1)%5;// 寻找下一个非IDLE态的进程，将turn赋予之，否则将turn保留给自己

		turn=index;
		printf("Process %d assigns %d to the variable turn\n",pid,turn);
		printf("\n");
		flags[pid]=IDLE;
	}
	return NULL;
}

int main() {
	int i;
	int thread_id[5];
	srand((unsigned int)time(0));
	for (i=0;i<5;i++) {
		flags[i]=IDLE;
		thread_id[i]=i;
	}

	printf("order:3 2 4 1\n");
	pthread_create(&thread[3],NULL,process,(void*)&thread_id[3]);
	pthread_create(&thread[2],NULL,process,(void*)&thread_id[2]);
	pthread_create(&thread[4],NULL,process,(void*)&thread_id[4]);
	pthread_create(&thread[1],NULL,process,(void*)&thread_id[1]);
	for (i=0;i<5;i++) pthread_join(thread[i],NULL);  
	return 0;
}

