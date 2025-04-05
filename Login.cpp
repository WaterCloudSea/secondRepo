#include "Login.h"

// 打印菜单
void menu() {
	printf("*****************************************************\n");
	printf("*****************************************************\n");
	printf("***********1. Register       2. Login****************\n");
	printf("***********3. Reback         0. exit*****************\n");
	printf("*****************************************************\n");
	printf("*****************************************************\n");
}

// 用户注册
void Register() {
	Users a, b; //创建用户结构体临时变量，a用于接收用户输入，b用来从文件中读取已注册用户数据与a比较
	char tmp[20] = ""; //用于下面判断

	printf("欢迎来到注册界面！\n");
	FILE* pf = fopen("users.dat", "rb");
	if (!pf) { //文件打开失败
		printf("%s", strerror(errno)); //error可以理解为报的错误对应的编号，strerror可以将这个编号翻译出来输出的屏幕上
		return;
	}
	fread(&b, sizeof(Users), 1,pf); // 从文件中读取已注册用户数据
	Sleep(800); //休眠800us
	printf("输入您的账号>>>");
	scanf("%s", a.id);
	while (1) {
		if (strcmp(a.id, b.id)) { // 两个用户名不相同
			if (!feof(pf)) { // 没读到文件末尾,更新b中的变量
				fread(&b, sizeof(Users), 1, pf);
			}
			else {  // 读到文件末尾，确认没有重复id
				break;
			}
		}
		else { //两个用户名相同
			printf("此用户已经存在，请重新输入\n");
			Sleep(1000);
			fclose(pf); // 关闭文件
			pf = NULL; // pf置空，避免野指针
			return;
		}
	}
	printf("输入您的姓名>>>");
	scanf("%s", a.name);
	printf("输入您的性别>>>");
	scanf("%s", a.sex);
	printf("输入您的电话号码>>>");
	scanf("%s", a.phone);
	printf("输入您的密码>>>");
	Getpwd(a.pwd); // 输入密码的函数，有掩盖功能
	printf("再次输入您的密码>>>");
	Getpwd(tmp);
	do {
		if (!strcmp(tmp, a.pwd)) {  // 两次输入密码相同
			pf = fopen("users.dat", "ab");
			fwrite(&a, sizeof(Users), 1, pf);
			printf("\n账号注册成功！，请登录！\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("\n两次输入密码不匹配，请重新输入>>>");
			Getpwd(a.pwd);
			printf("\n请再次确认>>>");
			Getpwd(tmp);
		}
	}while (1);

}

//登录
void Login() {
	Users a, b; // a用来读取用户输入信息，b从文件中读取已注册用户信息
	FILE* pf = fopen("users.dat", "rb");//以二进制只读的方式打开文件
	if (!pf) { // 如果读取失败
		printf("%s", strerror(errno));//error可以理解为报的错误对应的编号，strerror可以将这个编号翻译出来输出的屏幕上
		return;
	}
	printf("欢迎来到登录界面！\n");
	Sleep(1000);
	fread(&b, sizeof(Users), 1, pf);// 从文件中读取用户
	printf("请输入账号>>>");
	Sleep(800);
	scanf("%s", &a.id);
	
	while (1) {		// 在文件中找到与用户输入相同的id
		if (!strcmp(a.id, b.id)) {  // 从文件中读取到相同的id
			break;
		}
		else {
			if (!feof(pf)) { // 没有读到文件末尾，继续读取文件中的id到b中
				fread(&b, sizeof(Users), 1, pf);  
			}
			else {  // 读到文件末尾，没有找到与用户输入的相同账号
				printf("此账号不存在，请重新输入！\n");
				Sleep(500);
				fclose(pf);
				pf = NULL;
				return;
			}
		}
	}
	do {
		printf("请输入密码>>>");
		Getpwd(a.pwd);  // 获取密码
		if (strcmp(a.pwd, b.pwd)) {  // 输入密码与文件已注册用户密码相同
			printf("\n登录成功！欢迎使用！\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("\n密码输入错误，请重新输入\n");
		}
	} while (strcmp(a.pwd, b.pwd));

}

// 找回密码
void Reback() {
	char tmp[20] = "";  // 密码匹配使用
	Users a, b;

	FILE* pf = fopen("users.dat", "rb+");  // "rb+"以读和写的方式打开二进制文件

	if (!pf) {  // 文件打开失败
		printf("%s", strerror(errno));
		return;
	}
	fread(&b, sizeof(Users), 1, pf);

	printf("请输入您的账号>>>");
	Sleep(800);
	scanf("%s", a.id);

	while (1) {
		if (!strcmp(a.id, b.id)) {  // 在文件中找到用户输入的id
			break;
		}
		else {
			if (!feof(pf)) {   // 没有到文件末尾，继续寻找
				fread(&b, sizeof(Users), 1, pf);
			}
			else {
				printf("您输入的账号不存在！请重新输入！\n");
				Sleep(500);
				fclose(pf);
				pf = NULL;
				break;
			}
		}
	}

	// 信息匹配验证
	do {  // 匹配姓名
		printf("请输入您的姓名>>>");
		scanf("%s", a.name);
		if (!strcmp(a.name, b.name)) {
			break;
		}
		else {
			printf("输入错误，请重新输入！\n");
		}
	} while (strcmp(a.name, b.name));
	do {  // 匹配性别
		printf("请输入您的性别>>>");
		scanf("%s", a.sex);
		if (!strcmp(a.sex, b.sex)) {
			break;
		}
		else {
			printf("输入错误，请重新输入！\n");
		}
	} while (strcmp(a.phone, b.phone));

	// 修改密码
	printf("验证成功！请修改您的密码！\n");
	printf("请输入您的密码>>>");
	Getpwd(a.pwd);
	printf("请再次确认您的密码>>>");
	Getpwd(tmp);
	if (!pf) {
		printf("%s", strerror(errno));
		return;
	}
	// 覆盖原来的密码
	do {
		if (!strcmp(a.pwd, tmp)) {  // 两次密码相等
			fseek(pf, -((int)(sizeof(Users) - MAX_ID)), SEEK_CUR);  // 将文件流调回到要修改密码的位置
			fprintf(pf, "%s", a.pwd);  // 覆盖原来的密码
			printf("修改密码成功，请登录！\n");
			Sleep(500);
			fclose(pf);
			pf = NULL;
			return;
		}
		else {
			printf("两次密码不匹配！请重新输入>>>");
			scanf("%s", a.pwd);
			printf("请再次确认>>>");
			scanf("%s", tmp);
		}
	} while (1);
}


// 定位光标
void gotoxy(int x, int y) {
	// 更新光标位置
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle是Windows的API函数
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
}

