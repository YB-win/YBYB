#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<windows.h>
#include<math.h>
//������һ����ϵ��
typedef struct Linkman {
	char name[1024];
	char gender[1024];
	char age[1024];
	char number[1024];
	char address[1024];
}Linkman;
 
//������һ��ͨѶ¼����������˶����ϵ�ˣ�size�ǵ�ǰ��ϵ����
typedef struct AddressList {
	//���������ĳ�ָ�룬ͨ��malloc����̬�����ڴ�
	Linkman* persons;
	//��ʾ��ǰ���ָ��ָ���������������
	int capacity;
	int size;
}AddressList;
 
//����һ��ȫ�ֱ���
AddressList addressList;
 
//�������ݵ��ļ����浵��
void save(AddressList* list) {
	FILE* fp = fopen("E:/address_list.txt", "w");
	//�鿴�Ƿ�򿪳ɹ�
	if (fp == NULL) {
		printf("�򿪴浵�ļ�ʧ��\n");
		return;
	}
	//ʹ��fwrite��д
	fwrite(list->persons, sizeof(Linkman), list->size, fp);
	fclose(fp);
	printf("�浵�ɹ�\n");
}
 
//��������
//extern void save(AddressList* list);
 
//���ļ������ݼ��ص��ڴ��У�������
void load(AddressList* list) {
	FILE* fp = fopen("E:/address_list.txt", "r");
	if (fp == NULL) {
		printf("�򿪴浵�ļ�ʧ��\n");
		return;
	}
	//д�ļ��У�һ��Ҫ�����ٸ�Ԫ�أ�ֱ��ͨ��size��֪����
	//���ļ��У�һ��Ҫ������Ԫ�ؾͲ���ȷ����ֻ��һ��һ������ֱ�������ļ�ĩβ 
	while (1) {
		if (list->size > list->capacity) {
			list->capacity += 100;
			list->persons = realloc(list->persons, sizeof(Linkman) * list->capacity);
		}
		size_t n = fread(&list->persons[list->size], sizeof(Linkman), 1, fp);
		if (n == 0) {
			//�����ļ�ĩβ��
			break;
		}
		list->size++;
	}
	fclose(fp);
	printf("�����ɹ���\n");
}
 
//��ʼ��
void init(AddressList* list) {
	list->size = 0;
	list->capacity = 100;
	list->persons = (Linkman*)malloc(sizeof(Linkman) * list->capacity);
	//(list->num).name = { 0 };
}
 
int menu() {
	printf("+----------------------------+\n");
	printf("|      ͨѶ¼����ϵͳ        |\n");
	printf("+----------------------------+\n");
	printf("|    1�������ϵ��           |\n");
	printf("|    2������һ����ϵ��       |\n");
	printf("|    3���޸���ϵ��           |\n");
	printf("|    4��ɾ����ϵ��           |\n");
	printf("|    5��չʾ������ϵ��       |\n");
	printf("|    6�����������ϵ��       |\n");
	printf("|    7������������������ϵ�� |\n");
	printf("|    0���˳�                 |\n");
	printf("+----------------------------+\n");
	printf("���������ѡ��");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}
 
//�����ϵ��
void insert(AddressList* list) {
	assert(list != NULL);
	//ͨѶ¼���˵Ļ��ͷ���
	/*if (list->size >= 1000) {
		printf("ͨѶ¼����\n");
		return;
	}*/
	//��������
	if (list->size > list->capacity) {
		list->capacity += 100;
		list->persons = (Linkman*)realloc(list->persons, sizeof(Linkman) * list->capacity);
	}
	Linkman person = { 0 };
	printf("��������ϵ��������");
	scanf("%s", person.name);
	printf("��������ϵ���Ա�");
	scanf("%s", person.gender);
	printf("��������ϵ�����䣺");
	scanf("%s", person.age);
	printf("��������ϵ�˵绰��");
	scanf("%s", person.number);
	printf("��������ϵ��סַ:");
	scanf("%s", person.address);
	//����ϵ�˷���ͨѶ¼��
	list->persons[list->size] = person;
	list->size++;
	printf("������ϵ�˳ɹ�\n");
	//Sleep(2000); //��ʾ����
	//system("cls");
	save(list);
}
//�޸���ϵ��
void change(AddressList* list) {
	int id = 0;
	printf("��������Ҫ�޸ĵ���ϵ�˵����:");
	scanf("%d", &id);
	if (id < 0 || id > list->size - 1) {
		printf("�����������");
		return;
	}
	Linkman* p = &list->persons[id];
	printf("�������޸ĺ����ϵ�˵�������");
	scanf("%s", p->name);
	printf("�������޸ĺ����ϵ�˵��Ա�");
	scanf("%s", p->gender);
	printf("�������޸ĺ����ϵ�˵����䣺");
	scanf("%s", p->age);
	printf("�������޸ĺ����ϵ�˵ĵ绰��");
	scanf("%s", p->number);
	printf("�������޸ĺ����ϵ�˵�סַ��");
	scanf("%s", p->address);
	printf("�޸���ϵ�˳ɹ���\n");
	save(list);
}
 
//������ϵ��
void find(AddressList* list) {
	int id = 0;
	printf("������Ҫ�鿴��ϵ�˵����:");
	scanf("%d", &id);
	if (id < 0 || id > list->size - 1) {
		printf("�����������");
		return;
	}
	for (int i = 0; i < list->size; i++) {
		if (id == i) {
			Linkman* p = &list->persons[i];
			printf("������%s\t�Ա�%s\t���䣺%s\t�绰��%s\tסַ��%s\n", p->name, p->gender, p->age, p->number, p->address);
			printf("%s", list->persons[i].name);
		}
	}
}
//�鿴������ϵ��
void show(AddressList* list) {
	//printf("�鿴������ϵ��\n");
	for (int i = 0; i < list->size; i++) {
		Linkman* p = &list->persons[i];
		printf("[%d]\t%s\t%s\n", i, p->name, p->number);
	}
	printf("һ����%d����ϵ��\n", list->size);
}
//���������ϵ��
void empty(AddressList* list) {
	int i = 0;
	printf("ȷ��Ҫ���������ϵ����ȷ���밴1�������������\n");
	scanf("%d", &i);
	if (i == 1) {
		list->size = 0;
		printf("ɾ���ɹ���\n");
	}
	return;
	save(list);
}
//������������
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
	printf("����ɹ���\n");
	save(list);
}
 
//ɾ��һ����ϵ�ˣ��߼�ɾ����
void update(AddressList* list) {
	int id = 0;
	printf("������Ҫɾ������ϵ�˵���ţ�\n");
	scanf("%d", &id);
	if (id < 0 || id > list->size) {
		printf("�����������\n");
		return;
	}
	else if (id == list->size - 1) {//Ҫɾ���������һ����ϵ��
		list->size--;
		printf("ɾ���ɹ���\n");
	}
	//ȡ�����һ����ϵ�˵ĵ�ַ
	Linkman* p = &list->persons[list->size - 1];
	list->persons[id] = *p;
	list->size--;
	printf("ɾ���ɹ���\n");
	save(list);
}
 
 
//����һ������ָ��
typedef void(*Func)(AddressList*);
 
int main() {
	init(&addressList);
	//����һ������ָ������
	load(&addressList);//��������ǰ����һ�ζ�������
	//Ϊ�˽���Ȧ���Ӷȣ�����ת�Ʊ�ķ�ʽ
	Func func[] = { NULL,insert,find,change,update,show,empty,sort };//NULL����Ϊ��ռλ
	while (1) {
		int choice = menu();
		if (choice == 0) {
			printf("goodbye\n");
			break;
		}
		else if (choice < 0 || choice > 7) {
			printf("���������������������\n");
			continue;
		}
		func[choice](&addressList);
		system("pause");
		system("cls");
		//Func func = func[choice]
		//func(&addressList)
	}
	system("pause");
	//��ǰ���������������ڱ���Ӧ�ø����������򣬼�Ȼ�������һֱ����Ҫ�ã��Ͳ�����ǰ�ͷ�
	//������������ڴ�ᱻϵͳ�Զ�����
}
