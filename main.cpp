	#include "GUI.h"
	#include <windows.h>

#include <iostream>

int main()
{
	initdataVattu();
	initdataNhanvien();
	duyetLNR_test(DataNhanvien._nhanvien);
	initwindow( SCREAN_W, SCREAN_H);
	init_R();
	GUI_Init();	
	Home();

	while(GUIkey)
	{
		int x=-1;
		int y=-1;
		getmouseclick(WM_LBUTTONDOWN,x,y);
		clearmouseclick(WM_LBUTTONDOWN);
		delay(1);
		if ((x==-1)&&(y==-1)) continue;
	
			F_R[R[y][x]]();	
	}
	save_Vattu();
	save_Nhanvien();
	duyetLNR_test(DataNhanvien._nhanvien);
	return 0;
};
