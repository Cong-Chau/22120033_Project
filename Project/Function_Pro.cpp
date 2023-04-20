#include"Header_Pro.h"

char tail[] = { ".CSV" };

//--------------Dang nhap-------------//
//Mau chu
void textColor(int a) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, a);
}
//---------Phan header
void Display_Header() {
	textColor(243);
	cout << "==========================================================" << endl;
	cout << "=                                                        =" << endl;
	cout << "=               CHAO MUNG DEN VOI HE THONG               =" << endl;
	cout << "=        QUAN LY THONG TIN SINH VIEN VA GIANG VIEN       =" << endl;
	cout << "=                                                        =" << endl;
	cout << "==========================================================" << endl;
	textColor(7);
}
//-----------Dang nhap
int Login(Account* p, int n) {
	textColor(10);
	cout << "\n\t    ======= DANG NHAP TAI KHOAN =======" << endl;
	textColor(7);
	int mssv;
	cout << "\tTen tai khoan : "; cin >> mssv;
	int mk;
	cout << "\tMat khau      : "; cin >> mk;
	while ((checkMSSV_MSGV(p, n, mssv) == false) || (checkMK(p, n, mssv, mk) == false)) {
		textColor(12);
		cout << "\t*Ten tai khoan hoac mat khau khong chinh xac*" << endl;
		cout << "\t1. Thoat" << endl;
		cout << "\t2. Dang nhap lai" << endl;
		int x; cout << "\tChon: "; cin >> x;
		textColor(7);
		if (x == 1)
			return -1;
		system("cls");//Reset lai man hinh
		Display_Header();
		textColor(10);
		cout << "\n\t    ======= DANG NHAP TAI KHOAN =======" << endl;
		textColor(7);
		cout << "\tTen tai khoan : "; cin >> mssv;
		cout << "\tMat khau      : "; cin >> mk;
		return mssv;
	}
}

//----------Doi mat khau
void changeMK(Account*& p, int n, int y) {
	system("cls");
	Display_Header();
	textColor(10);
	cout << "\n    ===DOI MAT KHAU===" << endl;
	textColor(7);
	int  ms;
	cout << "Ten tai khoan: "; cin >> ms;
	int vitri = Find_Location(p, n, ms);

	while (vitri == -1) {
		textColor(12);
		cout << "*Ten tai khoan vua nhap khong the tim thay*" << endl;
		textColor(7);
		cout << "1. Thoat" << endl;
		cout << "2. Nhap lai Ten tai khoan" << endl;
		int x; cout << "Chon: "; cin >> x;
		if (x == 1)
			return;
		system("cls");
		Display_Header();
		cout << "==VUI LONG NHAP TEN TAI KHOAN==" << endl;
		cout << "Ten tai khoan: "; cin >> ms;
		vitri = Find_Location(p, n, ms);
	}
	int mkcu, mkmoi_1, mkmoi_2;
	cout << "Mat khau cu: "; cin >> mkcu;
	cout << "Mat khau moi: "; cin >> mkmoi_1;
	cout << "Xac nhan mat khau: "; cin >> mkmoi_2;

	if (checkMK(p, n, ms, mkcu) == false)
		cout << "*Mat khau cu khong chinh xac*" << endl;
	else {
		if (mkmoi_1 != mkmoi_2) {
			cout << "*Xac nhan mat khau khong chinh xac*" << endl; textColor(10);
		}
		else
			textColor(10); cout << "*Cap nhat mat khau thanh cong.*\n" << endl;
	}
	textColor(7);

	while ((checkMK(p, n, ms, mkcu) == false) || (mkmoi_1 != mkmoi_2)) {
		cout << "1. Thoat" << endl;
		cout << "2. Nhap lai" << endl;
		int x; cout << "Chon: "; cin >> x;
		if (x == 1)
			return;
		system("cls");
		Display_Header();
		textColor(12);
		cout << "\n   ==VUI LONG NHAP LAI==" << endl;
		textColor(7);
		cout << "Ten tai khoan     : "; cin >> ms;
		cout << "Mat khau cu       : "; cin >> mkcu;
		cout << "Mat khau moi      : "; cin >> mkmoi_1;
		cout << "Xac nhan mat khau : "; cin >> mkmoi_2;
		textColor(12);
		if (checkMK(p, n, ms, mkcu) == false)
			cout << "*Mat khau cu khong chinh xac*" << endl;
		else {
			if (mkmoi_1 != mkmoi_2) {
				cout << "*Xac nhan mat khau khong chinh xac*" << endl; textColor(10);
			}
			else
				textColor(10); cout << "*Cap nhat mat khau thanh cong.*\n" << endl;
		}
		textColor(7);
	}
	savePASS(p, n, ms, mkmoi_1, y);
}

//---------------------------------------------------------------//
//                     SINH VIEN
	//----------Luu mat khau moi-----------------//
void savePASS(Account*& p, int n, int mssv, int x, int y) {
	int vitri = Find_Location(p, n, mssv);
	p[vitri].password = x;
	if (y == 1) {
		ofstream write("accountSV.txt", ios::out);
		for (int i = 0; i < n; i++) {
			write << p[i].mssv_gv << endl;
			write << p[i].password << endl;
		}
		write.close();
	}
	if (y == 2) {
		ofstream write("accountNV.txt", ios::out);
		for (int i = 0; i < n; i++) {
			write << p[i].mssv_gv << endl;
			write << p[i].password << endl;
		}
		write.close();
	}

}

//---------------Xem file co bao nhieu phan tu
int DEM_sv() {
	ifstream read("accountSV.txt", ios::in);
	int n = 0;
	char tmp[100];
	while (!read.eof()) {
		read.getline(tmp, 100);
		if (strlen(tmp) == 0)
			n--;
		n++;
	}
	read.close();
	return n;
}
//--------------Doc du lieu tu file account vào p
void Read_file_sv(Account*& p, int n) {
	ifstream read("accountSV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_gv;
		read >> p[i].password;
	}
	read.close();
}
//-------Tim vi tri cua mssv duoc nhap, tra ve -1 neu khong tim thay vi tri
int Find_Location(Account* p, int n, int x) {
	for (int i = 0; i < n; i++) {
		if (x == p[i].mssv_gv)
			return i;
	}
	return -1;
}
//------Kiem tra mssv co ton tai hay khong
bool checkMSSV_MSGV(Account* p, int n, int ms) {
	for (int i = 0; i < n; i++) {
		if (ms == p[i].mssv_gv)
			return true;
	}
	return false;
}
//------Kiem tra mat khau co chinh xac hay khong
bool checkMK(Account* p, int n, int ms, int pass) {
	int vitri = Find_Location(p, n, ms);
	if (vitri == -1)
		return false;
	if (pass == p[vitri].password)
		return true;
	return false;
}


//////////-------------FUNCTION--------------//////////////


//--------------------Giang vien---------------------//

int DEM_gv() {
	ifstream read("accountNV.txt", ios::in);
	int n = 0;
	char tmp[100];
	while (!read.eof()) {
		read.getline(tmp, 100);
		if (strlen(tmp) == 0)
			n--;
		n++;
	}
	read.close();
	return n;
}
void Read_file_gv(Account*& p, int n) {
	ifstream read("accountNV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_gv;
		read >> p[i].password;
	}
	read.close();
}

////---------------Chuc nang cho sinh vien

void Function_after_Login_SV(int mssv) {
	/*
	du lieu duoc khai bao sau
	*/
	while (1) {
		system("cls");
		Display_Header();
		cout << endl << "                    --SINH VIEN--                " << endl;
		cout << "   ===================================================" << endl;
		cout << "   =  0. Thoat" << endl;
		cout << "   =  1. Xem danh sach lop da duoc dang ky           =" << endl;
		cout << "   =  2. Xem bang diem tong ket                      =" << endl;
		cout << "   ===================================================" << endl;
		int chon; cout << "   Muc ban muon xem : "; cin >> chon;
		switch (chon) {
		case 0:{
			return;
		}
		case 1: {
			cout << "Chua duoc cap nhat\n";
			break;
		}
		case 2: {
			cout << "Chua duoc cap nhat\n";
			break;
		}
		}
		cout << "   Ban muon quay tro lai hay thoat?\n";
		cout << "     1. Tro lai     2. Thoat\n";
		int p; cout << "  Chon: "; cin >> p;
		if (p == 2) {
			return;
		}
	}
}

////---------------Chuc nang cho nhan vien vien



void Function_after_Login_NV() {
	/*
	du lieu duoc khai bao sau
	*/
	int year_now, hk;
	Node_year* year = NULL;
	
	while (1) {
		cout << endl << "                    --GIAO VIEN--                " << endl;
		cout << "   ==================================================================" << endl;
		cout << "   =  0. Thoat" << endl;
		cout << "   =  1. Tao mot nam hoc moi                                        =" << endl;
		cout << "   =  2. Tao mot so lop cho sinh vien nam nhat                      =" << endl;
		cout << "   =  3. Them moi hoc sinh nam 1 vao cac lop nam 1                  =" << endl;
		//	cout << "   =  4. Nhap tep CSV chua thong tin sinh vien                      =" << endl;
		cout << "   =  4. Tao 1 hoc ki moi                                           =" << endl;
		cout << "   =  5. Them khoa hoc                                              =" << endl;
		cout << "   =  6. Tai tep CSV sinh vien da dang ky khoa hoc                  =" << endl;
		cout << "   =  7. Xem danh sach cac khoa hoc                                 =" << endl;
		cout << "   =  8. Cap nhat thong tin khoa hoc                                =" << endl;
		cout << "   =  9. Them 1 sinh vien vao khoa hoc                              =" << endl;
		cout << "   = 10. Xoa 1 sinh vien ra khoi khoa hoc                           =" << endl;
		cout << "   = 11. Xoa khoa hoc                                               =" << endl;
		cout << "   = 12. Xem danh sach cac lop                                      =" << endl;
		cout << "   = 13. Xem danh sach hoc sinh trong lop                           =" << endl;
		cout << "   = 14. Xem danh sach hoc sinh trong moi khoa hoc                  =" << endl;
		cout << "   = 15. Xuat danh sach sinh vien trong moi khoa hoc ra file CSV    =" << endl;
		cout << "   = 16. Nhap bang diem cua 1 khoa hoc                              =" << endl;
		cout << "   = 17. Xem bang diem cua 1 khoa hoc                               =" << endl;
		cout << "   = 18. Cap nhat ket qua cua hoc sinh                              =" << endl;
		cout << "   = 19. Xem ban diem cua lop                                       =" << endl;
		cout << "   ==================================================================" << endl;
		int chon; cout << "Ban muc muon xem: "; cin >> chon;
		system("cls");
		Display_Header();
		switch (chon) {
		case 0: {
			return;
		}
		case 1: {
			cout << "\tTao nam hoc moi\n";
			Create_1_year(year);
			break;
		}
		case 2: {
			cout << "Tao mot so lop hoc moi\n";
			Node_class* clss = NULL;
			create_NewClass(clss);
			break;
		}
		case 3: {
			
			cout << "Danh sach cac lop: \n";
			Node_class* clss = NULL;
			int n = Count_file_class();
			Read_file_class(clss, n);
			List_class(clss);
			Choose_Class(clss);

			break;
		}
		case 4: {
			cout << "   TAO HOC KI\n";
			char start[max], end[max];
			Create_HK(year_now, hk, start, end);
			break;
		}
		}
		cout << "   Ban muon thuc hien thao tac khac hay thoat?\n";
		cout << "     1. Tro lai     2. Thoat\n";
		int p; cout << "  Chon: "; cin >> p;
		if (p == 2) {
			return;
		}
		system("cls");
		Display_Header();
	}
}

/////////////Tao nam hoc moi///////////
Node_year* makeNode_year(NamHoc x) {
	Node_year* tmp = new Node_year;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_year(Node_year*& y, NamHoc x) {
	Node_year* tmp = makeNode_year(x);
	if (y == NULL)
		y = tmp;
	else {
		Node_year* last = y;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}

void input_Year(NamHoc& x) {
	cout << "  Nam hoc: "; cin >> x.year;
	cout << "  So luong lop mo: "; cin >> x.solg;
}

void write_File_year(Node_year* year) {
	ofstream write("namhoc.txt", ios::out);

	while (year != NULL) {
		write << year->data.year << endl;
		write << year->data.solg << endl;
		year = year->next;
	}
	write.close();
}

void Create_1_year(Node_year*& year) {
	NamHoc x;
	input_Year(x);
	addLast_year(year, x);
	write_File_year(year);
}
/////----------- tao lop hoc cho sinh vien nam nhat------------////

void upper_Class(char x[]) {
	for (int i = 0; i < strlen(x); i++) {
		if (x[i] >= 'a' && x[i] <= 'z')
			x[i] -= 32;
	}
}

Node_class* makeNode_Class(Class x) {
	Node_class* tmp = new Node_class;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_Class(Node_class * &clss, Class x) {
	Node_class* tmp = makeNode_Class(x);
	if (clss == NULL)
		clss = tmp;
	else {
		Node_class* last = clss;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}

void input_Class(Class& x) {
	cin.ignore();
	cout << "  Ma lop: "; cin.getline(x.idclass, max); upper_Class(x.idclass);
	cout << "  Ten mon hoc: "; cin.getline(x.nameclass, max); upper_Class(x.nameclass);
//	cout << "  So luong hoc sinh toi da: "; cin >> x.amount;
	cout << endl;
}

void write_File_class(Node_class* clss) {
	ofstream write("class.txt", ios::app);
	while (clss != NULL) {
		write << clss->data.idclass << endl;
		write << clss->data.nameclass << endl;
		write << clss->data.amount << endl;
		clss = clss->next;
	}
	write.close();
}

void create_NewClass(Node_class*& clss) {
	Class x;
	int n;
	cout << "So luong lop muon tao: "; cin >> n;
	for (int i = 0; i < n; i++) {
		input_Class(x);
		addLast_Class(clss, x);
		Create_ALL_clss(clss);
	}
	write_File_class(clss);
	textColor(10); cout << "Cac lop hoc da duoc tao thanh cong\n\n"; textColor(7);
}

///-----------tao mot ki hoc moi-------------///
int Count_file_year() {
	int dem = 0;
	ifstream read("namhoc.txt", ios::in);
	while(!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	return dem;
}

void Read_file_year(Node_year* year) {
	int n = Count_file_year();
	ifstream read("namhoc.txt", ios::in);
	for (int i = 0; i < n; i++) {
		NamHoc x;
		read >> x.year;
		read >> x.solg;
		addLast_year(year, x);
	}
	read.close();
}

void Create_HK(int& namhoc, int& hk, char start[], char end[]) {
	cout << "  Nam hoc cua hoc ki nay    : "; cin >> namhoc;
	Node_year* year = NULL;
	cout << "  Day la hoc ki(1,2,3)      : "; cin >> hk;
	cin.ignore();
	cout << "  Ngay bat dau(DD/MM/YYYY)  : "; cin.getline(start, max);
	cout << "  Ngay ket thuc(DD/MM/YYYY) : "; cin.getline(end, max);
	textColor(10); cout << "Da xac nhan hoc ki hien tai \n\n"; textColor(7);
}

//------------------them hoc sinh nam 1 vao cac lop nam 1----------------//
int Change_char_int(char x[]) {// chuyen tu char sang int
	int rec = 0;
	for (int i = 0; i < strlen(x); i++) {
		rec = rec * 10 + (x[i] - '0');
	}
	return rec;
}

Node_Stu* makeNode_student(Student x) {
	Node_Stu* tmp = new Node_Stu;
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}

void addLast_stu(Node_Stu*& y, Student x) {
	Node_Stu* tmp = makeNode_student(x);
	if (y == NULL)
		y = tmp;
	else {
		Node_Stu* last = y;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = tmp;
	}
}

int Count_file_csv(char file[]) {
	int dem = 0;
	ifstream read(file, ios::in);
	while (!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	return dem - 1;
}
void Read_file_csv(Node_Stu*& stu, char file[]) {
	cout << file << endl;
	ifstream read(file, ios::in);
	if (read.is_open()) {
		char tmp[max];
		read.getline(tmp, max);
		for (int i = 0; i < Count_file_csv(file); i++) {
			Student x;
			char No[max];
			read.getline(No, max, ',');//
			char tmp_id[max];
			read.getline(tmp_id, max, ',');//
			x.ID = Change_char_int(tmp_id);
			read.getline(x.name, max, ',');//
			read.getline(x.ho, max, ',');//
			read.getline(x.sex, max, ',');//
			read.getline(x.birth, max, ','); //
			char tmp_cccd[max];
			read.getline(tmp_cccd, max); //
			x.cccd = Change_char_int(tmp_cccd);
			addLast_stu(stu, x);
		}
	}
	cout << endl;
	read.close();
}
int Count_file_class() {
	int dem = 0;
	ifstream read("class.txt", ios::in);
	while (!read.eof()) {
		char x[max];
		read.getline(x, max);
		if (strlen(x) != 0)
			dem++;
	}
	read.close();
	return dem / 3;
}

void Read_file_class(Node_class*& clss, int n) {
	ifstream read("class.txt", ios::in);
	for (int i = 0; i < n; i++) {
		Class x;
		read.getline(x.idclass, max);
		read.getline(x.nameclass, max);
		read >> x.amount;
		read.ignore();
		addLast_Class(clss, x);
	}
	read.close();
}

bool check_File_Class(char x[]) {
	Node_class* clss = NULL;
	Read_file_class(clss, Count_file_class());
	while (clss != NULL) {
		if (strcmp(x, clss->data.idclass) == 0)
			return true;
		clss = clss->next;
	}
	return false;
}
//------in ra man hinh danh sach cac lop
void List_class(Node_class* clss) {  
	cout << "  Danh sach cac lop: \n";
	for (int i = 1; clss != NULL; i++, clss = clss->next) {
		if (strlen(clss->data.idclass) != 0) {
			cout << i << ". " << clss->data.idclass;
			cout << "\t: " << clss->data.nameclass << endl;
		}
	}
}
//------tao ten file csv
void Connect_Char(char x[],char y[], char file[]) {
	int dem = 0;
	for (int i = 0; i < strlen(x); i++) {
		file[dem] = x[i];
		dem++;
	}
	file[dem] = '_';
	dem++;
	for (int i = 0; i < strlen(y); i++) {
		file[dem] = y[i];
		dem++;
	}
	int lim = strlen(x) + strlen(y) + strlen(tail);
	for (int i = 0; i < strlen(tail); i++) {
		file[dem] = tail[i];
		dem++;
	}
	file[lim + 1] = '\0';
}
//------tao 1 file lop
void Create_file_clss(Class x) {
		char file[max];
		Connect_Char(x.idclass, x.nameclass, file);
//		cout << file << endl;
		ofstream write(file, ios::out);
		write.close();
}
//------tao tat ca file lop
void Create_ALL_clss(Node_class* clss) {
	while (clss != NULL) {
		Create_file_clss(clss->data);
		clss = clss->next;
	}
}
//------ghi danh sach sinh vien vao file lop
void Write_csv_class(Node_Stu* stu, int chon, int lim) {

	Node_class* clss = NULL;
	int n = Count_file_class();
	Read_file_class(clss, n);
	for (int i = 1; i < chon; i++) {
		clss = clss->next;
	}
	char file[max];
	Connect_Char(clss->data.idclass, clss->data.nameclass, file);
	cout << endl << file << endl;
//	int lim = Count_file_csv(file);
	ofstream write(file, ios::out);
	write << "No" << ",";
	write << "MSSV" << ",";
	write << "Ten" << ",";
	write << "Ho" << ",";
	write << "Gioi tinh" << ",";
	write << "Ngay sinh" << ",";
	write << "CMND/CCCD" << endl;
	if (write.is_open()) {
		
		for (int i = 0; i < lim; i++) {
			write << i + 1 << ",";
			write << stu->data.ID << ",";
			write << stu->data.name << ",";
			write << stu->data.ho << ",";
			write << stu->data.sex << ",";
			write << stu->data.birth << ",";
			write << stu->data.cccd << endl;
			stu = stu->next;
		}
		textColor(10); 
		cout << "  Da them sinh vien vao file: " << file << "\n\n"; 
		textColor(7);
		write.close();
	}
}
//------ chuc nang them hoc sinh nam 1 vao cac lop nam 1
void Choose_Class(Node_class* clss) {
	int chon;
	cout << "  Lop ban muon them danh sach: ";
	cin >> chon;
	while (chon < 1 || chon > Count_file_class()) {
		cout << "  Lop duoc chon khong hop le!\n";
		cout << "  Muon nhap lai hay dung thao tac? \n";
		cout << "   1. Nhap lai    2. Dung\n";
		int c;
		cin >> c;
		if (c == 2)
			return;
		
		system("cls");
		Display_Header();
		List_class(clss);
		if (c == 1) {
			cout << "\n  Lop ban muon them danh sach: ";
			cin >> chon;
		}
	}
	char link[50];
	cout << "  Link file sinh vien: ";
	cin.ignore();
	cin.getline(link, max);
	Node_Stu* stu = NULL;
	Read_file_csv(stu, link);
	cout << "  Danh sach sinh vien: \n";
	Node_Stu* tmp = stu;
	int i = 1;
	while (tmp != NULL) {
		cout << i << ",";
		cout << tmp->data.ID << ",";
		cout << tmp->data.name << ",";
		cout << tmp->data.ho << ",";
		cout << tmp->data.sex << ",";
		cout << tmp->data.birth << ",";
		cout << tmp->data.cccd << endl;
		tmp = tmp->next;
		i++;
	}
	int lim = Count_file_csv(link);
	Write_csv_class(stu, chon, lim);
}