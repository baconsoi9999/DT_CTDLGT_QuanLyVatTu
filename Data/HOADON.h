// danh sach hoa don (danh sach lien ket don)
#include "CT_HOADON.h"
struct Thongtin_HD{
	char soHD[100];
	char day[3];
	char month[3];
	char year[5];
	char loai;
};
struct NodeHD{
	Thongtin_HD thongtin;
	CT_HOADON chitiet;
	NodeHD* _next;
};
struct DsHOADON{
	int num = 0;
	NodeHD* hdHead;
};
void init_hd(DsHOADON &hd){
	hd.hdHead = NULL;
	hd.num =0;
}
NodeHD* GetNode_hd(Thongtin_HD tt,CT_HOADON ct){
	NodeHD* p = new NodeHD;
	p->thongtin = tt;
	p->chitiet = ct;
	p->_next = NULL;
	return p;
}
void addTail_HD(DsHOADON &hd,NodeHD* p){
	if(hd.hdHead == NULL) hd.hdHead = p;
	else{
		NodeHD* q = hd.hdHead;
		while(q->_next!= NULL){
			q =q->_next;
			//cout<<"\nloop6";
		}
		q->_next = p;
	}
	hd.num++;
}
#define CTHEAD hd.hdHead->chitiet.ctHead

void Print_thongtin_HD(Thongtin_HD tt,int x ,int y,unsigned short int c_line[]){
	outtextxy(x,y,tt.soHD);
	outtextxy(x+c_line[0],y,tt.day);
	outtextxy(x+c_line[1],y,tt.month);
	outtextxy(x+c_line[2],y,tt.year);
	char loai_s [2];
	loai_s[0] = tt.loai;
	loai_s[1] = '\0';
	outtextxy(x+c_line[3],y,loai_s);
}
