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
			}//�ȴ���������Լ�֮ǰ�Ľ���ִ�����

			flags[pid]=ACTIVE;//����ռ�й�����Դ	

			index=0;
			while ((index<5)&&((index==pid)||(flags[index]!= ACTIVE))) index++;
			if ( index >= 5 && (turn == pid || flags[turn] == IDLE) ) break;//ռ�гɹ����˳�ѭ��
			//ռ��ʧ�ܺ�����ִ��ѭ��������ѭ����ͷ���Լ���ACTIVE״̬����
		}
		
		turn = pid;//������ռ�й�����Դ
		printf("Process %d fetches the resource\n",pid);
		//�������̱߳���Ҫ�����£������趨�����߳�ʲô��������ֻ�����������
		printf("Process %d is running\n",pid); 
		printf("Process %d releases the resource\n",pid);
		
		index=(turn+1)%5;
		while (flags[index]==IDLE) index=(index+1)%5;// Ѱ����һ����IDLE̬�Ľ��̣���turn����֮������turn�������Լ�

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

