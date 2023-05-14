#include<iostream>
#include<fstream>
#include<windows.h>
#include<string.h>
#include<conio.h>
#define max 100
using namespace std;


struct Account {
	int mssv_nv;
	int password;
};

struct Node_Account {
	Account data;
	Node_Account* next;
};

struct Student {
	//int No;
	int ID; //mssv
	char name[max]; //Ten
	char ho[max]; //Ho va ten dem
	char sex[max]; //Gioi tinh
	char birth[max]; //Ngay sinh
	int cccd; //So cccd hoac cmnd
};

struct Node_Stu {
	Student data;
	Node_Stu* next;
};

struct Class {
	char id[max]; // ma lop
	char faculty[max]; // khoa cua lop truc thuoc
};

struct Node_Class {
	Class data;
	Node_Class* next;
};

struct Course {
	char id[max]; // ma mon hoc
	char name[max]; // ten khoa hoc
	char id_class[max]; // lop hoc
	char teacher[max]; //ten giao vien
	char credit[2]; // so tin chi
	int max_stu = 50; // sinh vien toi da
	char day[max]; // ngay hoc trong tuan
	char lesson[max]; // tiet hoc trong tuan
};

struct Node_Course {
	Course data;
	Node_Course* next;
};

struct NamHoc {
	int year;  //Nam hoc
	int solg;
};

struct Node_year {
	NamHoc data;
	Node_year* next;
};

struct Node_Namefile {
	char data[max];
	Node_Namefile* next;
};


void Display_Header();
void textColor(int a);
int Count_file(char file[]);
int Find_Location(Account* p, int n, int x);
bool checkMSSV_MSNV(Account* p, int n, int ms);
bool checkMK(Account* p, int n, int ms, int pass);
int Login(Account* p, int n);
void changeMK(Account*& p, int n, int y);
void savePASS(Account*& p, int n, int ms, int x, int y);

//sinh vien
int DEM_sv();
void Read_file_sv(Account*& p, int n);

//giao vien
int DEM_nv();
void Read_file_nv(Account*& p, int n);
void Function_after_Login_SV(int mssv);
void Function_after_Login_NV();

//  tao 1 nam hoc
Node_year* makeNode_year(NamHoc x);
void addLast_year(Node_year*& y, NamHoc x);
void input_Year(NamHoc& x);
void write_File_year(Node_year* year);
void Create_1_year(Node_year*& year);

// tao lop hoc cho sinh vien nam nhat
void Upper(char x[]);
Node_Class* makeNode_Class(Class x);
void addLast_Class(Node_Class*& cla, Class x);
//int Count_file_class();
void input_Class(Class& x);
void Create_Class(Node_Class*& cla, int n);
void Connect_class(char x[], char file[]);
void Write_file_class(Class cla);
void Write_namefile_class(char x[]);
void Create_file(char file[]);
void Create_AllFile_Class(Node_Class* cla);
bool Check_namefile_exist(Node_Class* cla, int local, char file[]);

// them sinh vien nam nhat vao cac lop nam nhat
void List_Class(Node_Class* cla);
void Read_file_class(Node_Class*& cla, int n);
void Write_csv_class(Node_Stu* stu, int chon, int lim);
void Choose_Class(Node_Class* cla);

// doc file csv
int Change_char_int(char x[]);
Node_Stu* makeNode_student(Student x);
void addLast_stu(Node_Stu*& y, Student x);
int Count_file_csv(char file[]);
int Read_file_csv(Node_Stu*& stu, char file[]);
Node_Account* makeNode_Account(Account x);
void addLast_Account(Node_Account*& acc, Account x);
bool Check_Account(int mssv);
void Update_Account(Node_Stu* stu);

// tao hoc ki hien tai
int Count_file_year();
void Read_file_year(Node_year* year);
void Create_HK(int& namhoc, int& hk, char start[], char end[]);

// tao khoa hoc
Node_Course* makeNode_Course(Course x);
void addLast_Course(Node_Course*& cou, Course x);
void Connect_Course(char x[], char y[], char file[]);
void input_Course(Course& x);
void Write_file_course(Course x);
void Create_Course(Node_Course*& cou);
void Read_file_course(Node_Course*& cou, int n);
bool check_File_Course(char x[], char  y[]);
void Write_namefile_course(char x[]);
void Create_AllFile_Course(Node_Course* cou);
void List_Course(Node_Course* cou);
void Choose_Course(Node_Course* cou);

// xem danh sach khoa hoc
void Display_Course(Node_Course* cou);

// cap nhat thong tin khoa hoc
void Update_Course(Node_Course*& cou);
void Re_Write_file_course(Node_Course* cou);
void Re_Write_namefile_course(Node_Course* cou);

// them 1 sinh vien vao khoa hoc
void Input_Student(Student& x);
void Add_Student(Node_Stu*& stu, int& lim);
void Choose_AddStudent(Node_Course* cou);

// xoa 1 sinh vien ra khoi khoa hoc
void Delete_First_Stu(Node_Stu*& stu);
void Delete_Middle_Stu(Node_Stu*& stu, int vitri);
void Delete_Last_Stu(Node_Stu*& stu, int n);
void Display_Student(Node_Stu* stu);
int Local_Student(Node_Stu* stu, int ID);
void Delete_Student(Node_Course* cou);

// xoa 1 khoa hoc
void Read_Namefile(Node_Namefile*& nam, char file[]);
void Delete_Course(Node_Course*& cou, int& n, Node_Namefile*& nam);
void ReWrite_course(Node_Course* cou, Node_Namefile* nam, int n);

// xem danh sach lop hoc

// xem danh sach sinh vien trong moi lop
void Display_Student_ofClass(Node_Class* cla, int n);

// xem danh sach sinh vien trong khoa hoc
void Display_Student_ofCourse(Node_Course* cou, int n);