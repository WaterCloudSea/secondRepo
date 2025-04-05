#include "Login.h"

// ��ӡ�˵�
void menu() {
	printf("*****************************************************\n");
	printf("*****************************************************\n");
	printf("***********1. Register       2. Login****************\n");
	printf("***********3. Reback         0. exit*****************\n");
	printf("*****************************************************\n");
	printf("*****************************************************\n");
}

// �û�ע��
void Register() {
	Users a, b; //�����û��ṹ����ʱ������a���ڽ����û����룬b�������ļ��ж�ȡ��ע���û�������a�Ƚ�
	char tmp[20] = ""; //���������ж�

	printf("��ӭ����ע����棡\n");
	FILE* pf = fopen("users.dat", "rb");
	if (!pf) { //�ļ���ʧ��
		printf("%s", strerror(errno)); //error�������Ϊ���Ĵ����Ӧ�ı�ţ�strerror���Խ������ŷ�������������Ļ��
		return;
	}
	fread(&b, sizeof(Users), 1,pf); // ���ļ��ж�ȡ��ע���û�����
	Sleep(800); //����800us
	printf("���������˺�>>>");
	scanf("%s", a.id);
	while (1) {
		if (strcmp(a.id, b.id)) { // �����û�������ͬ
			if (!feof(pf)) { // û�����ļ�ĩβ,����b�еı���
				fread(&b, sizeof(Users), 1, pf);
			}
			else {  // �����ļ�ĩβ��ȷ��û���ظ�id
				break;
			}
		}
		else { //�����û�����ͬ
			printf("���û��Ѿ����ڣ�����������\n");
			Sleep(1000);
			fclose(pf); // �ر��ļ�
			pf = NULL; // pf�ÿգ�����Ұָ��
			return;
		}
	}
	printf("������������>>>");
	scanf("%s", a.name);
	printf("���������Ա�>>>");
	scanf("%s", a.sex);
	printf("�������ĵ绰����>>>");
	scanf("%s", a.phone);
	printf("������������>>>");
	Getpwd(a.pwd); // ��������ĺ��������ڸǹ���
	printf("�ٴ�������������>>>");
	Getpwd(tmp);
	do {
		if (!strcmp(tmp, a.pwd)) {  // ��������������ͬ
			pf = fopen("users.dat", "ab");
			fwrite(&a, sizeof(Users), 1, pf);
			printf("\n�˺�ע��ɹ��������¼��\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("\n�����������벻ƥ�䣬����������>>>");
			Getpwd(a.pwd);
			printf("\n���ٴ�ȷ��>>>");
			Getpwd(tmp);
		}
	}while (1);

}

//��¼
void Login() {
	Users a, b; // a������ȡ�û�������Ϣ��b���ļ��ж�ȡ��ע���û���Ϣ
	FILE* pf = fopen("users.dat", "rb");//�Զ�����ֻ���ķ�ʽ���ļ�
	if (!pf) { // �����ȡʧ��
		printf("%s", strerror(errno));//error�������Ϊ���Ĵ����Ӧ�ı�ţ�strerror���Խ������ŷ�������������Ļ��
		return;
	}
	printf("��ӭ������¼���棡\n");
	Sleep(1000);
	fread(&b, sizeof(Users), 1, pf);// ���ļ��ж�ȡ�û�
	printf("�������˺�>>>");
	Sleep(800);
	scanf("%s", &a.id);
	
	while (1) {		// ���ļ����ҵ����û�������ͬ��id
		if (!strcmp(a.id, b.id)) {  // ���ļ��ж�ȡ����ͬ��id
			break;
		}
		else {
			if (!feof(pf)) { // û�ж����ļ�ĩβ��������ȡ�ļ��е�id��b��
				fread(&b, sizeof(Users), 1, pf);  
			}
			else {  // �����ļ�ĩβ��û���ҵ����û��������ͬ�˺�
				printf("���˺Ų����ڣ����������룡\n");
				Sleep(500);
				fclose(pf);
				pf = NULL;
				return;
			}
		}
	}
	do {
		printf("����������>>>");
		Getpwd(a.pwd);  // ��ȡ����
		if (strcmp(a.pwd, b.pwd)) {  // �����������ļ���ע���û�������ͬ
			printf("\n��¼�ɹ�����ӭʹ�ã�\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("\n���������������������\n");
		}
	} while (strcmp(a.pwd, b.pwd));

}

// �һ�����
void Reback() {
	char tmp[20] = "";  // ����ƥ��ʹ��
	Users a, b;

	FILE* pf = fopen("users.dat", "rb+");  // "rb+"�Զ���д�ķ�ʽ�򿪶������ļ�

	if (!pf) {  // �ļ���ʧ��
		printf("%s", strerror(errno));
		return;
	}
	fread(&b, sizeof(Users), 1, pf);

	printf("�����������˺�>>>");
	Sleep(800);
	scanf("%s", a.id);

	while (1) {
		if (!strcmp(a.id, b.id)) {  // ���ļ����ҵ��û������id
			break;
		}
		else {
			if (!feof(pf)) {   // û�е��ļ�ĩβ������Ѱ��
				fread(&b, sizeof(Users), 1, pf);
			}
			else {
				printf("��������˺Ų����ڣ����������룡\n");
				Sleep(500);
				fclose(pf);
				pf = NULL;
				break;
			}
		}
	}

	// ��Ϣƥ����֤
	do {  // ƥ������
		printf("��������������>>>");
		scanf("%s", a.name);
		if (!strcmp(a.name, b.name)) {
			break;
		}
		else {
			printf("����������������룡\n");
		}
	} while (strcmp(a.name, b.name));
	do {  // ƥ���Ա�
		printf("�����������Ա�>>>");
		scanf("%s", a.sex);
		if (!strcmp(a.sex, b.sex)) {
			break;
		}
		else {
			printf("����������������룡\n");
		}
	} while (strcmp(a.phone, b.phone));

	// �޸�����
	printf("��֤�ɹ������޸��������룡\n");
	printf("��������������>>>");
	Getpwd(a.pwd);
	printf("���ٴ�ȷ����������>>>");
	Getpwd(tmp);
	if (!pf) {
		printf("%s", strerror(errno));
		return;
	}
	// ����ԭ��������
	do {
		if (!strcmp(a.pwd, tmp)) {  // �����������
			fseek(pf, -((int)(sizeof(Users) - MAX_ID)), SEEK_CUR);  // ���ļ������ص�Ҫ�޸������λ��
			fprintf(pf, "%s", a.pwd);  // ����ԭ��������
			printf("�޸�����ɹ������¼��\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("�������벻ƥ�䣡����������>>>");
			scanf("%s", a.pwd);
			printf("���ٴ�ȷ��>>>");
			scanf("%s", tmp);
		}
	} while (1);
}


// ��λ���
void gotoxy(int x, int y) {
	// ���¹��λ��
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle��Windows��API����
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
}

