#include <iostream>
using namespace std;

#define MAX_SIZE 32767

typedef struct node
{
	int adr;
	int size;
	struct node* next;
}Node;
Node* head1, * head2, * back1, * back2, * assign;


bool check(int address, int size, string c)//用于检查指定的释放块（由用户键入）的合法性
{
	Node* p, * head;
	if (address < 0 || size < 0){
		return false;
	}
	if(c=="F"||c=="f"){
		head = head1;
	}
	else {
		head = head2;
	}
	p = head->next;
	while ( p != NULL) {
		if (((address < p->adr) && (address + size > p->adr)) || ((address >= p->adr) && (address < p->adr + p->size))){
			return false;
		}
		else {
			p = p->next;
		}
	}
	return true;
}


void init()//初始化
{
	Node* p;
	head1 = (Node*)malloc(sizeof(Node));
	head2 = (Node*)malloc(sizeof(Node));
	p = (Node*)malloc(sizeof(Node));
	head1->next = p;
	head2->next = p;
	p->size = MAX_SIZE;
	p->adr = 0;
	p->next = NULL;
}


Node* assignment1(int req)
{
	Node* before, * after, * ass;
	ass = (Node*)malloc(sizeof(Node));
	before = head1;
	after = head1->next;
	ass->size = req;
	while (after->size < req){
		before = before->next;
		after = after->next;
	}
	if (after == NULL){
		ass->adr = -1;
	}
	else {
		if (after->size == req) {
			before->next = after->next;
			ass->adr = after->adr;
		}
		else {
			after->size -= req;
			ass->adr = after->adr;
			after->adr += req;
		}
	}
	return ass;
}


void acceptment1(int address, int siz)
{
	Node* before, * after;
	bool insert = false;
	back1 = (Node*)malloc(sizeof(Node));
	before = head1;
	after = head1->next;
	back1->adr = address;
	back1->size = siz;
	back1->next = NULL;
	while (!insert && after) {
		//按首地址大小  小->大  将要被回收的分区插入空闲区
		if ((after == NULL) || ((back1->adr <= after->adr) && (back1->adr >= before->adr))) {
			before->next = back1;
			back1->next = after;
			insert = true;
		}
		else {
			before = before->next;
			after = after->next;
		}
	}
	if (insert) {
		if (back1->adr == before->adr + before->size) {
			//和前边分区合并
			before->size += back1->size;
			before->next = back1->next;
			free(back1);
		}
		else if (after && back1->adr + back1->size == after->adr){
			//和后边合并
			back1->size += after->size;
			back1->next = after->next;
			free(after);
			after = back1;
		}
		cout << "首先分配算法回收内存成功！" << endl;
	}
	else {
		cout << "首先分配算法回收内存失败！" << endl;
	}
}


Node* assignment2(int req)
{
	Node* before, * after, * ass, * q;
	ass = (Node*)malloc(sizeof(Node));
	q = (Node*)malloc(sizeof(Node));
	before = head2;
	after = head2->next;
	ass->size = req;
	while (after->size < req) {
		before = before->next;
		after = after->next;
	}
	if (after == NULL) {
		ass->adr = -1;
	}
	else {
		if (after->size == req) {
			before->next = after->next;
			ass->adr = after->adr;
		}
		else {
			q = after;
			before->next = after->next;
			ass->adr = q->adr;
			q->size -= req;
			q->adr += req;
			before = head2;
			after = head2->next;
			if (after == NULL) {
				before->next = q;
				q->next = NULL;
			}
			else {
				while ((after->size) < (q->size)) {
					before = before->next;
					after = after->next;
				}
				before->next = q;
				q->next = after;
			}
		}
	}
	return ass;
}


void acceptment2(int address, int siz)
{
	Node* before, * after;
	bool insert = false;
	back2 = (Node*)malloc(sizeof(Node));
	before = head2;
	after = head2->next;
	back2->adr = address;
	back2->size = siz;
	back2->next = NULL;
	if (head2->next == NULL) {
		//空闲队列为空
		head2->next = back2;
		head2->size = back2->size;
	}
	else {
		//空闲队列不为空
		while (after) {
			if (back2->adr == after->adr + after->size){
				//和前边空闲分区合并
				before->next = after->next;
				after->size += back2->size;
				back2 = after;
			}
			else {
				before = before->next;
				after = after->next;
			}
		}
		before = head2;
		after = head2->next;
		while (after) {
			if (after->adr == back2->adr + back2->size){
				//和后边空闲区合并
				before->next = after->next;
				back2->size += after->size;
			}
			else{
				before = before->next;
				after = after->next;
			}
		}
		before = head2;
		after = head2->next;

		while (!insert) {
			//按分区 小->大 将被回收的块插入到恰当的位置
			if (after == NULL || ((after->size > back2 ->size) && (before->size < back2->size))){
				before->next = back2;
				back2->next = after;
				insert = true;
				break;
			}
			else{
				before = before->next;
				after = after->next;
			}
		}
	}
	if (insert) {
		cout << "最佳适应算法回收内存成功！" << endl;
	}
	else {
		cout << "最佳适应算法回收内存失败！" << endl;
	}
}


void print(string c)//打印空闲区队列
{
	int id = 0;
	Node* p;
	if (c == "f" || c == "F") {
		p = head1->next;
	}
	else {
		p = head2->next;
	}
	if (p) {
		system("cls");
		cout << "空闲区队列情况：" << endl;
		cout << "编号\t首址\t终址\t大小" << endl;
		while (p) {
			cout << id << "\t" << p->adr << "\t" << p->adr + p->size - 1 << "\t" << p->size << endl;
			p = p->next;
			id++;
		}
	}
}


int main(void)
{
	init();
	string c1 = "";
	string c2 = "";
	int r = 0, add = 0, rd = 0;
	select:
	cout << "F.最先适应算法" << endl;
	cout << "B.最佳适应算法" << endl;
	cin >> c1;
	if (c1 == "f" || c1 == "F") {
		cout << "已选择：最先适应算法"<<endl;
	}
	else if (c1 == "b" || c1 == "B") {
		cout << "已选择：最佳适应算法" << endl;
	}
	else {
		cout << "输入有误" << endl;
		goto select;
	}
	select2:
	cout << "\t1.分配内存\n\t2.回收内存\n\t3.查看内存\n\t4.返回" << endl;
	cin >> c2;
	if (c2 == "1") {
		cout << "输入申请分区的大小：";
		cin >> r;
		cout << endl;
		if (c1 == "f" || c1 == "F") {
			assign = assignment1(r);
		}
		else if (c1 == "b" || c1 == "B") {
			assign = assignment2(r);
		}

		if (assign->adr == -1) {
			cout << "内存分配失败" << endl;
		}
		else {
			cout << "内存分配成功，首址为：" << assign->adr <<endl;
		}
		goto select2;
	}
	else if (c2 == "2") {
		cout << "输入释放内存的首址：";
		cin >> add;
		cout << "\n输入释放内存的大小：";
		cin >> r;
		if (check(add, r, c1)) {
			if (c1 == "f" || c1 == "F") {
				acceptment1(add, r);
			}
			else if (c1 == "b" || c1 == "B") {
				acceptment2(add, r);
			}
		}
		else {
			cout << "输入不合法" << endl;
		}
		goto select2;
	}
	else if (c2 == "3") {
		print(c1);
		goto select2;
	}
	else if (c2 == "4") {
		system("cls");
		goto select;
	}
	else {
		cout << "输入有误" << endl;
		goto select2;
	}

}

