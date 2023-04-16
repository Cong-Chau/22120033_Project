#include"Header_Pro.h"



//           Dang nhap                //
//Mau chu
void textColor(int a) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, a);
}
//Phan header
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


//Dang nhap
int Login(Account* p, int n) {
	textColor(10);
	cout << "\n\t    ======= DANG NHAP TAI KHOAN =======" << endl;
	textColor(7);
	int mssv;
	cout << "\tTen tai khoan: "; cin >> mssv;
	int mk;
	cout << "\tMat khau: "; cin >> mk;
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
		cout << "\tTen tai khoan: "; cin >> mssv;
		cout << "\tMat khau: "; cin >> mk;
		return mssv;
	}
}

//Doi mat khau
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
		cout << "Ten tai khoan: "; cin >> ms;
		cout << "Mat khau cu: "; cin >> mkcu;
		cout << "Mat khau moi: "; cin >> mkmoi_1;
		cout << "Xac nhan mat khau: "; cin >> mkmoi_2;
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

///////////////////////////////////////////////////
//Sinh vien
	//Luu mat khau moi
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
		ofstream write("accountGV.txt", ios::out);
		for (int i = 0; i < n; i++) {
			write << p[i].mssv_gv << endl;
			write << p[i].password << endl;
		}
		write.close();
	}

}

//Xem file co bao nhieu dong
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
//Doc du lieu tu file tendn vào p
void Read_file_sv(Account*& p, int n) {
	ifstream read("accountSV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_gv;
		read >> p[i].password;
	}
	read.close();
}
//Tim vi tri cua mssv duoc nhap, tra ve -1 neu khong tim thay vi tri
int Find_Location(Account* p, int n, int x) {
	for (int i = 0; i < n; i++) {
		if (x == p[i].mssv_gv)
			return i;
	}
	return -1;
}
//Kiem tra mssv co ton tai hay khong
bool checkMSSV_MSGV(Account* p, int n, int ms) {
	for (int i = 0; i < n; i++) {
		if (ms == p[i].mssv_gv)
			return true;
	}
	return false;
}
//Kiem tra mat khau co chinh xac hay khong
bool checkMK(Account* p, int n, int ms, int pass) {
	int vitri = Find_Location(p, n, ms);
	if (vitri == -1)
		return false;
	if (pass == p[vitri].password)
		return true;
	return false;
}


//////////////////////////////////////////////////////////


//Giang vien

int DEM_gv() {
	ifstream read("accountGV.txt", ios::in);
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
	ifstream read("accountGV.txt", ios::in);
	for (int i = 0; i < n; i++) {
		read >> p[i].mssv_gv;
		read >> p[i].password;
	}
	read.close();
}

//// Tao 1 nam hoc gom so: nam, so luong lop mo, danh sach lop mo


/////////Chuc nang cho sinh vien

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
		int p; cout << "Chon: "; cin >> p;
		if (p == 2) {
			return;
		}
	}
}


void Function_after_Login_GV() {
	/*
	du lieu duoc khai bao sau
	*/
	Node_year* year = NULL;
	while (1) {
		cout << endl << "                    --GIAO VIEN--                " << endl;
		cout << "   ==================================================================" << endl;
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
		switch (chon) {
		case 1: {
			Create_1_year(year);
			break;
		}
		case 2: {
			cout << "Chua duoc cap nhat\n";
			break;
		}
		}
		cout << "   Ban muon quay tro lai hay thoat?\n";
		cout << "     1. Tro lai     2. Thoat\n";
		int p; cout << "Chon: "; cin >> p;
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
//////////// tao lop hoc cho sinh vien nam nhat /////////
void upper_Class(char x[]) {
	for (int i = 0; i < strlen(x); i++) {
		if (x[i] >= 'a' && x[i] <= 'z')
			x[i] -= 32;
	}
}