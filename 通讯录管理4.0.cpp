#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<windows.h>
#include<math.h>
//描述了一个联系人
typedef struct Linkman {
	char name[1024];
	char gender[1024];
	char age[1024];
	char number[1024];
	char address[1024];
}Linkman;
 
//描述了一个通讯录，里面包含了多个联系人，size是当前联系人数
typedef struct AddressList {
	//把这个数组改成指针，通过malloc来动态分配内存
	Linkman* persons;
	//表示当前这个指针指向的数组的最大容量
	int capacity;
	int size;
}AddressList;
 
//创建一个全局变量
AddressList addressList;
 
//保存内容到文件（存档）
void save(AddressList* list) {
	FILE* fp = fopen("E:/address_list.txt", "w");
	//查看是否打开成功
	if (fp == NULL) {
		printf("打开存档文件失败\n");
		return;
	}
	//使用fwrite来写
	fwrite(list->persons, sizeof(Linkman), list->size, fp);
	fclose(fp);
	printf("存档成功\n");
}
 
//函数声明
//extern void save(AddressList* list);
 
//把文件中数据加载到内存中（读档）
void load(AddressList* list) {
	FILE* fp = fopen("E:/address_list.txt", "r");
	if (fp == NULL) {
		printf("打开存档文件失败\n");
		return;
	}
	//写文件中，一共要读多少个元素，直接通过size就知道了
	//读文件中，一共要读多少元素就不好确定，只能一个一个读，直到读到文件末尾 
	while (1) {
		if (list->size > list->capacity) {
			list->capacity += 100;
			list->persons = realloc(list->persons, sizeof(Linkman) * list->capacity);
		}
		size_t n = fread(&list->persons[list->size], sizeof(Linkman), 1, fp);
		if (n == 0) {
			//读到文件末尾了
			break;
		}
		list->size++;
	}
	fclose(fp);
	printf("读档成功！\n");
}
 
//初始化
void init(AddressList* list) {
	list->size = 0;
	list->capacity = 100;
	list->persons = (Linkman*)malloc(sizeof(Linkman) * list->capacity);
	//(list->num).name = { 0 };
}
 
int menu() {
	printf("+----------------------------+\n");
	printf("|      通讯录管理系统        |\n");
	printf("+----------------------------+\n");
	printf("|    1、添加联系人           |\n");
	printf("|    2、查找一个联系人       |\n");
	printf("|    3、修改联系人           |\n");
	printf("|    4、删除联系人           |\n");
	printf("|    5、展示所有联系人       |\n");
	printf("|    6、清空所有联系人       |\n");
	printf("|    7、以名字排序所有联系人 |\n");
	printf("|    0、退出                 |\n");
	printf("+----------------------------+\n");
	printf("请输入你的选择：");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}
 
//添加联系人
void insert(AddressList* list) {
	assert(list != NULL);
	//通讯录满了的话就返回
	/*if (list->size >= 1000) {
		printf("通讯录已满\n");
		return;
	}*/
	//进行扩容
	if (list->size > list->capacity) {
		list->capacity += 100;
		list->persons = (Linkman*)realloc(list->persons, sizeof(Linkman) * list->capacity);
	}
	Linkman person = { 0 };
	printf("请输入联系人姓名：");
	scanf("%s", person.name);
	printf("请输入联系人性别：");
	scanf("%s", person.gender);
	printf("请输入联系人年龄：");
	scanf("%s", person.age);
	printf("请输入联系人电话：");
	scanf("%s", person.number);
	printf("请输入联系人住址:");
	scanf("%s", person.address);
	//把联系人放在通讯录中
	list->persons[list->size] = person;
	list->size++;
	printf("新增联系人成功\n");
	//Sleep(2000); //显示两秒
	//system("cls");
	save(list);
}
//修改联系人
void change(AddressList* list) {
	int id = 0;
	printf("请输入你要修改的联系人的序号:");
	scanf("%d", &id);
	if (id < 0 || id > list->size - 1) {
		printf("你的输入有误");
		return;
	}
	Linkman* p = &list->persons[id];
	printf("请输入修改后的联系人的姓名：");
	scanf("%s", p->name);
	printf("请输入修改后的联系人的性别：");
	scanf("%s", p->gender);
	printf("请输入修改后的联系人的年龄：");
	scanf("%s", p->age);
	printf("请输入修改后的联系人的电话：");
	scanf("%s", p->number);
	printf("请输入修改后的联系人的住址：");
	scanf("%s", p->address);
	printf("修改联系人成功！\n");
	save(list);
}
 
//查找联系人
void find(AddressList* list) {
	int id = 0;
	printf("请输入要查看联系人的序号:");
	scanf("%d", &id);
	if (id < 0 || id > list->size - 1) {
		printf("你的输入有误");
		return;
	}
	for (int i = 0; i < list->size; i++) {
		if (id == i) {
			Linkman* p = &list->persons[i];
			printf("姓名：%s\t性别：%s\t年龄：%s\t电话：%s\t住址：%s\n", p->name, p->gender, p->age, p->number, p->address);
			printf("%s", list->persons[i].name);
		}
	}
}
//查看所有联系人
void show(AddressList* list) {
	//printf("查看所有联系人\n");
	for (int i = 0; i < list->size; i++) {
		Linkman* p = &list->persons[i];
		printf("[%d]\t%s\t%s\n", i, p->name, p->number);
	}
	printf("一共有%d个联系人\n", list->size);
}
//清空所有联系人
void empty(AddressList* list) {
	int i = 0;
	printf("确定要清空所有联系人吗，确定请按1，按其余键返回\n");
	scanf("%d", &i);
	if (i == 1) {
		list->size = 0;
		printf("删除成功！\n");
	}
	return;
	save(list);
}
//按照姓名排序
void sort(AddressList* list) {
	for (int i = 0; i < list->size - 1; i++) {
		for (int j = 0; j < list->size - 1 - i; j++) {
			Linkman* p1 = &list->persons[j];
			Linkman* p2 = &list->persons[j + 1];
			if (memcmp(p1->name, p2->name, sizeof(p1->name)) > 0) {
				Linkman tmp = list->persons[j];
				list->persons[j] = list->persons[j + 1];
				list->persons[j + 1] = tmp;
			}
		}
	}
	printf("排序成功！\n");
	save(list);
}
 
//删除一个联系人（逻辑删除）
void update(AddressList* list) {
	int id = 0;
	printf("请输入要删除的联系人的序号：\n");
	scanf("%d", &id);
	if (id < 0 || id > list->size) {
		printf("你的输入有误\n");
		return;
	}
	else if (id == list->size - 1) {//要删除的是最后一个联系人
		list->size--;
		printf("删除成功！\n");
	}
	//取出最后一个联系人的地址
	Linkman* p = &list->persons[list->size - 1];
	list->persons[id] = *p;
	list->size--;
	printf("删除成功！\n");
	save(list);
}
 
 
//定义一个函数指针
typedef void(*Func)(AddressList*);
 
int main() {
	init(&addressList);
	//定义一个函数指针数组
	load(&addressList);//程序启动前进行一次读档即可
	//为了降低圈复杂度，采用转移表的方式
	Func func[] = { NULL,insert,find,change,update,show,empty,sort };//NULL纯粹为了占位
	while (1) {
		int choice = menu();
		if (choice == 0) {
			printf("goodbye\n");
			break;
		}
		else if (choice < 0 || choice > 7) {
			printf("你的输入有误，请重新输入\n");
			continue;
		}
		func[choice](&addressList);
		system("pause");
		system("cls");
		//Func func = func[choice]
		//func(&addressList)
	}
	system("pause");
	//当前这个数组的生命周期本就应该跟随整个程序，既然这个数组一直不需要用，就不能提前释放
	//当程序结束，内存会被系统自动回收
}
