#include"Header_Pro.h"



int main() {
	Display_Header();
	int n = DEM_sv() / 2;//So sinh vien trong  file accountSV.txt
	Account* sv, * nv;
	sv = new Account[n];
	int m = DEM_nv() / 2;//So giang vien trong  file accountnv.txt
	nv = new Account[m];

	//----- Doc file vao bien ----//
	Read_file_sv(sv, n);//Thong tin tron file accountSV.txt
	Read_file_nv(nv, m);//Thong tin tron file accountnv.txt


	cout << endl << "             --DANG NHAP VOI TU CACH--" << endl;
	cout << "     =============================================" << endl;
	cout << "     =  0. Thoat                                 =" << endl;
	cout << "     =  1. Sinh vien                             =" << endl;
	cout << "     =  2. Nhan vien                             =" << endl;
	cout << "     =============================================" << endl;
	int x; cout << "      Chon: "; cin >> x;
	while (x != 0 && x != 1 && x != 2) {
		system("cls");
		Display_Header();
		cout << endl << "             --DANG NHAP VOI TU CACH--" << endl;
		cout << "     =============================================" << endl;
		cout << "     =  0. Thoat                                 =" << endl;
		cout << "     =  1. Sinh vien                             =" << endl;
		cout << "     =  2. Nhan vien                             =" << endl;
		cout << "     =============================================" << endl;
		textColor(12);
		cout << "                  Khong hop le, vui long chon lai!\n";
		textColor(7);
		cout << "      Chon: "; cin >> x;
	}
	system("cls");
	Display_Header();
	switch (x) {
	case 1: {
		cout << endl << "                      --SINH VIEN--                " << endl;
		cout << "     ===================================================" << endl;
		cout << "     =  0. Thoat                                       =" << endl;
		cout << "     =  1. Dang nhap                                   =" << endl;
		cout << "     =  2. Doi mat khau                                =" << endl;
		cout << "     ===================================================" << endl;
		int x1; cout << "      Chon: "; cin >> x1;
		while (x1 != 0 && x1 != 1 && x1 != 2) {
			system("cls");
			Display_Header();
			cout << endl << "                      --SINH VIEN--                " << endl;
			cout << "     ===================================================" << endl;
			cout << "     =  0. Thoat                                     =" << endl;
			cout << "     =  1. Dang nhap                                   =" << endl;
			cout << "     =  2. Doi mat khau                                =" << endl;
			cout << "     ===================================================" << endl;
			textColor(12);
			cout << "                        Khong hop le, vui long chon lai!\n";
			textColor(7);
			cout << "      Chon: "; cin >> x1;
		}
		switch (x1) {
		case 1: {
			system("cls");
			Display_Header();
			int mssv = Login(sv, n);
			if (mssv == -1)
				return 0;
			system("cls");
			Display_Header();
			Function_after_Login_SV(mssv);
			break;
		}
		case 2: {
			changeMK(sv, n, x);
			cout << "Ban co muon quay lai trang dang nhap?\n";
			cout << "\t1.Co\t2.Khong\n";
			int c; cin >> c;
			if (c == 1) {
				system("cls");
				Display_Header();
				int mssv = Login(sv, n);
				if (mssv == -1)
					return 0;
				system("cls");
				Display_Header();
				Function_after_Login_SV(mssv);
			}
			if (c == 2)
				return 0;
			break;
		}
		}
		break;
	}
	case 2: {
		cout << endl << "                      --NHAN VIEN--                " << endl;
		cout << "     ===================================================" << endl;
		cout << "     =  0. Thoat                                       =" << endl;
		cout << "     =  1. Dang nhap                                   =" << endl;
		cout << "     =  2. Doi mat khau                                =" << endl;
		cout << "     ===================================================" << endl;
		int x1; cout << "      Chon: "; cin >> x1;
		while (x1 != 0 && x1 != 1 && x1 != 2) {
			system("cls");
			Display_Header();
			cout << endl << "                      --NHAN VIEN--                " << endl;
			cout << "     ===================================================" << endl;
			cout << "     =  0. Thoat                                       =" << endl;
			cout << "     =  1. Dang nhap                                   =" << endl;
			cout << "     =  2. Doi mat khau                                =" << endl;
			cout << "     ===================================================" << endl;
			textColor(12);
			cout << "                        Khong hop le, vui long chon lai!\n";
			textColor(7);
			cout << "      Chon: "; cin >> x1;
		}
		switch (x1) {
		case 1: {
			system("cls");
			Display_Header();
			int msnv = Login(nv, m);
			if (msnv == -1)
				return 0;
			system("cls");
			Display_Header();
			Function_after_Login_NV();
			break;
		}
		case 2: {
			changeMK(nv, m, x);
			cout << "     Ban co muon quay lai trang dang nhap?\n";
			cout << "     \t1.Co\t2.Khong\n";
			int c; cin >> c;
			if (c == 1) {
				system("cls");
				Display_Header();
				Login(nv, m);
				system("cls");
				Display_Header();
				Function_after_Login_NV();
			}
			if (c == 2)
				return 0;
			break;
		}
		}
		break;
	}
	}
	delete[]sv;
	delete[]nv;
	cout << endl;
	system("pause");
	return 0;
}

