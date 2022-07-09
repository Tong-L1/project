#include<iostream>
#include<string>
using namespace std;

typedef struct node
{
	string name;	//进程标示符
	int prio;		//进程优先数
	int round;		//进程每次轮转的时间片数
	int cputime;	//进程累计占用CPU的时间片数
	int needtime;	//进程到完成还需要的时间片数
	char state;		//进程状态
	int count;		//记录执行数
	struct node* next;//链指针
}PCB;

int num;

PCB* ready = NULL;	//就需队列头指针
PCB* run = NULL;	//当前运行进程指针
PCB* finish = NULL; //完成队列头指针
PCB* tail = NULL;	//就需队列尾指针

void getFirst() //获得第一个就绪节点
{
	run = ready;
	if (ready != NULL)
	{
		run->state = 'R';
		ready = ready->next;
		run->next = NULL;
	}
}

void outPut() //输出队列
{
	PCB* p;
	p = run;
	cout << "name\tcputime\tneedtime\tpriority\tstate" << endl;
	while (p != NULL)
	{
		cout << p->name << "\t" << p->cputime << "\t" << p->needtime << "\t\t" << p->prio << "\t\t" << p->state << endl;
		p = p->next;
	}
	p = ready;
	while (p != NULL)
	{
		cout << p->name << "\t" << p->cputime << "\t" << p->needtime << "\t\t" << p->prio << "\t\t" << p->state << endl;
		p = p->next;
	}
	p = finish;
	while (p != NULL)
	{
		cout << p->name << "\t" << p->cputime << "\t" << p->needtime << "\t\t" << p->prio << "\t\t" << p->state << endl;
		p = p->next;
	}
}

void insertPrio(PCB* in)//创建优先级队列
{
	PCB* fst, * nxt;
	fst = nxt = ready;
	if (ready == NULL) {
		in->next = ready;
		ready = in;
	}
	else {
		if (in->prio >= fst->prio) {
			in->next = ready;
			ready = in;
		}
		else {
			while (fst->next != NULL) {
				nxt = fst;
				fst = fst->next;
			}
			in->next = fst->next;
			fst->next = in;
		}
	}
}

void insertTime(PCB* in) //轮转-将进程插入到就绪队列尾部
{
	PCB* fst;
	fst = ready;
	if (ready == NULL) {
		in->next = ready;
		ready = in;
	}
	else {
		while (fst->next != NULL) {
			fst = fst->next;
		}
		in->next = fst->next;
		fst->next = in;
	}
}

void insertFinish(PCB* in) //将进程插入到完成队列尾部
{
	PCB* fst;
	fst = finish;
	if (finish == NULL) {
		in->next = finish;
		finish = in;
	}
	else {
		while (fst->next != NULL) {
			fst = fst->next;
		}
		in->next = fst->next;
		fst->next = in;
	}
}

void prioCreate()
{
	PCB* tmp;
	int i;
	cout << "输入进程名和进程所需时间:" << endl;
	for (i = 0; i < num; i++)
	{
		if ((tmp = new PCB) == NULL)
		{
			cerr << "malloc" << endl;
			exit(1);
		}

		cin >> tmp->name;
		cin >> tmp->needtime;
		tmp->cputime = 0;
		tmp->state = 'W';
		tmp->prio = 50 - tmp->needtime;
		tmp->round = 0;
		tmp->count = 0;
		insertPrio(tmp);
	}
	
}
void timeCreate() //轮转
{
	PCB* tmp;
	int i;

	cout << "输入进程名字和进程时间所需时间：" << endl;
	for (i = 0; i < num; i++)
	{
		if ((tmp = new PCB) == NULL)
		{
			cerr << "malloc" << endl;
			exit(1);
		}
		cin >> tmp->name;
		
		cin >> tmp->needtime;
		tmp->cputime = 0;
		tmp->state = 'W';
		tmp->prio = 0;
		tmp->round = 2;
		tmp->count = 0;
		insertTime(tmp);

	}
	
}
void priorty()
{
	int flag = 1;
	getFirst();
	while (run != NULL)
	{
		outPut();
		while (flag)
		{
			run->prio = 3;
			run->cputime++;
			run->needtime--;
			if (run->needtime == 0)
			{
				run->state = 'F';
				run->count++;
				insertFinish(run);
				flag = 0;

			}
			else
			{
				run->state = 'W';
				run->count++;
				insertTime(run);
				flag = 0;
			}
		}
		flag = 1;
		getFirst();

	}
}
void roundRun()
{
	int flag = 1;
	getFirst();
	while (run != NULL)
	{
		outPut();
		while (flag)
		{
			run->count++;
			run->cputime++;
			run->needtime--;
			if (run->needtime == 0)
			{
				run->state = 'F';
				insertFinish(run);
				flag = 0;
			}
			else if (run->count == run->round)
			{
				run->state = 'W';
				run->count = 0;
				insertTime(run);
				flag = 0;
			}
		}
		flag = 1;
		getFirst();

	}
}


int main(void) {
	int n;
	cout << "进程个数：" << endl;
	cin >> num;

	cout << "1.优先级调度" << endl;
	cout << "2.循环轮转调度" << endl;
	cin >> n;
	if (n == 1) {
		//system("cls");
		cout << "1.优先级调度:" << endl;
		prioCreate();
		priorty();
		outPut();
	}
	else if(n == 2) {
		//system("cls");
		cout << "2.循环轮转调度" << endl;
		timeCreate();
		roundRun();
		outPut();
	}
	else {
		cout << "错误"<<endl;
	}
}