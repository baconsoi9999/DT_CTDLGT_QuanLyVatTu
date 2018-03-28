#include <string.h>
#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "HOADON.h"
using namespace std;

/*file stream*/
ofstream f2;//write stream
// danh sach nhan vien ( binary serch tree)
struct Thongtin_NV{
	char MANV[100];
	char HO[100];
	char TEN[100];
	char PHAI[5];
};
struct Nhanvien{
	Thongtin_NV thongtin;
	DsHOADON nv_HOADON;			// tro den cac hoa don ma nhan vien do da lap
};
struct NodeNV{
	Nhanvien nv;
	NodeNV* left;
	NodeNV* right; 
};
typedef struct NodeNV* Tree;
int i =1;
int pt = 1;
struct DsNhanvien{
	Tree _nhanvien;
	int num = 0;
}DataNhanvien;

//void save_node(NodeNV* p){
//	if(p == NULL) return;
//	Thongtin_NV k = p->nv.thongtin;
//	//cout<<"k::::"<<k.MANV<<endl;
//	f2.write((char*) &k,sizeof(k));
//	save_node(p->left);
//	save_node(p->right);
//}
//void save_Nhanvien()
//{
//	
//	f2.open("Data/DataNhanvien.data",ios::binary |ios :: out);
//	save_node(DataNhanvien._nhanvien);
//	f2.close();
//}


void duyetLNR_test(Tree t){
	if(t== NULL) return;
	cout<<"ko he null";
	cout<<"co HD"<<t->nv.nv_HOADON.num<<endl;
	if(t->nv.nv_HOADON.hdHead == NULL) cout<<"hoa don NULL\n";
	for(NodeHD* p = t->nv.nv_HOADON.hdHead;p!=NULL;p = p->_next){
		cout<<"\nhoa don ::"<<p->thongtin.soHD<<endl;
	}
	duyetLNR_test(t->left);
	duyetLNR_test(t->right);
}
void XuatNhanvien(Nhanvien p,int x, int y,unsigned short int c_line[]){
	outtextxy(x+c_line[0],y,p.thongtin.MANV);
	outtextxy(x+c_line[1],y,p.thongtin.HO);
	outtextxy(x+c_line[2],y,p.thongtin.TEN);
	outtextxy(x+c_line[3],y,p.thongtin.PHAI);
}
void init_nv(Tree &root){
	root = NULL;
}


NodeNV* GetNode_NV(Nhanvien k){
	NodeNV* p = new NodeNV;
	p->nv  = k;
	p->left = p->right = NULL;
	init_hd( p->nv.nv_HOADON);
	return p;
}

void Insert_NV(NodeNV* p,Tree &root){
	if( root == NULL ){
		root = p;
		return;
	
	}
	
	if(strcmp(p->nv.thongtin.MANV,root->nv.thongtin.MANV)>0) Insert_NV(p,root->right);
	else Insert_NV(p,root->left);
}

// in ra man hinh day tang dan
void addNhanvien(Tree &root, Nhanvien nv){
	NodeNV* p = GetNode_NV(nv);

	Insert_NV(p,root);
	DataNhanvien.num++;
}
bool Find_NV(Tree root,char* MaNV){
	if(root == NULL ) return false;
	if(strcmp(MaNV , root->nv.thongtin.MANV) == 0) return true;
	 else return  (Find_NV(root->right,MaNV) | Find_NV(root->left,MaNV));
	 
}


void Output(Tree root, int page,int x,int y,unsigned short int c_line[]){
	if(root == NULL ) return ;
	if(root ->left != NULL)  Output(root->left,page,x,y,c_line);
	
	if(i>(page-1)*10 && i<=page*10 ) {
	if(i%10!=0)XuatNhanvien(root->nv,x,y+(i%10-1)*37,c_line);
	else XuatNhanvien(root->nv,x,y+9*37,c_line);
	}
	i++;
	if(root->right != NULL) Output(root->right,page,x,y,c_line); 
}
void PrintNhanvien(Tree root, int page,int x,int y,unsigned short int c_line[]){
	i = 1;
	Output(root, page,x,y,c_line);
}

void Find_NV_Return(Tree root, int k,Nhanvien &get){
	if(root == NULL) return;
	Find_NV_Return(root->left,k,get);
	if(i == k) {
		get = root->nv;
	}
	i++;
	Find_NV_Return(root->right,k,get);
}

Nhanvien searchTreebyNum(Tree root,int n){
		Nhanvien give;
		 i = 1;
		Find_NV_Return(root,n,give);
		return give;
}
void delKey(Tree &t, char MaNV[])     // xoa nut co key x
{	
    if (t==NULL) return ;
    else if (strcmp(MaNV,t->nv.thongtin.MANV)>0)  delKey(t->right, MaNV);
    else if (strcmp(MaNV,t->nv.thongtin.MANV)<0)  delKey(t->left, MaNV);
    else // T->key == x
    {
    	cout<<"vao\n";
        NodeNV *p = t;
        if (t->left == NULL) t = t->right;    // Node chi co cay con phai
        	else if (t->right == NULL) t = t->left;   // Node chi co cay con trai
        		else // Node co ca 2 con
			    {
			    //	bool flag = false;
			       NodeNV *s = t, *q = t->left;
			       // S la cha cua Q, Q la Node phai nhat cua cay con trai cua P
			       while (q->right != NULL)
			        {
			           s = q;
			           q = q->right;
			    	}
			    	
			        t->nv = q->nv;
			        if(q->left == NULL) t->left =NULL;
			        else s->right = q->left;
			        delete q;
			    }
	}
   
}


//void initdataNhanvien(){
//	ifstream f;
//	char* s ;
//	f.open("Data/DataNhanvien.data",ios::binary);
//	bool check = false;
//	if(f)
//	while(!f.eof()){
//		Thongtin_NV p;
//		check = true;
//		f.read((char*)&p,sizeof(p));
//		//cout<<"Nhanvien:::"<<p.MANV<<endl;
//		s = p.MANV;
//		Nhanvien q;
//		q.thongtin = p;
//		addNhanvien(DataNhanvien._nhanvien,q);
//	}
//	else init_nv(DataNhanvien._nhanvien);
//	delKey(DataNhanvien._nhanvien,s);
//
//	f.close();
//}
void initdataNhanvien(){
	ifstream f;
	char* s ;
	f.open("Data/DataNhanvien.data",ios::binary| ios::in);
	init_nv(DataNhanvien._nhanvien);
	if(f){
		Thongtin_NV p;
		
		while(f.read((char*)&p,sizeof(Thongtin_NV))){
		NodeNV* node_nv = new NodeNV;
		cout<<"doc :: Nhanvien:::"<<p.MANV<<endl;
		cout<<"doc::ho::"<<p.HO<<endl;
		cout<<"doc::ho::"<<p.TEN<<endl;
		cout<<"doc::ho::"<<p.PHAI<<endl;
		s = p.MANV;
		//cout<<"Ma NV "<<s<<endl;
		Nhanvien q;
		q.thongtin = p;
		int sl_hd;
		char * buf;
		f.read((char*)&buf,sizeof(int));
		sl_hd = (int) buf;
		cout<<"doc:::sl_hd:::"<<sl_hd<<endl;
		DsHOADON ds_hd;
		init_hd(ds_hd);
		
	//	cout<<"sl_hd ::"<<sl_hd<<endl;
	//	cout<<"2:::\n";
		for(int i = 1;i<=sl_hd;i++){
			Thongtin_HD v;
			f.read((char*)&v,sizeof(Thongtin_HD));
			int sl_ct;
			char* buff;
			NodeHD* node_hd = new NodeHD;
			f.read((char*)&buff,sizeof(int));
			sl_ct = (int) buff;
			cout<<"so luong ct::"<<sl_ct<<endl;
			CT_HOADON ct_hd;
		//	cout<<"so HD ::"<<v.soHD<<endl;
		//	cout<<"3::::";
			init_ct(ct_hd);
		
			for(int j=1; j<= sl_ct; j++){
				Thongtin_CT u;
			//	cout<<"4::\n";
				f.read((char*)&u,sizeof(Thongtin_CT));
				cout<<"CT VT:::"<<u.MAVT<<endl;
				cout<<"CT Dongia:::"<<u.Dongia<<endl;
				NodeCT* node_ct = new NodeCT; 
				node_ct = GetNode_CT(u);
				addTail_CT(ct_hd,node_ct);				
			}
			//cout<<"5:::\n";
			node_hd = GetNode_hd(v,ct_hd);
		//	cout<<"6::::\n";
			addTail_HD(ds_hd,node_hd);
		//	cout<<"7:::\n";
		}
		q.thongtin = p;
		node_nv = GetNode_NV(q);
		node_nv->nv.nv_HOADON = ds_hd;
		Insert_NV(node_nv,DataNhanvien._nhanvien);
		cout<<"xem q::"<<q.thongtin.MANV<<endl;
		cout<<"sl _ hd::"<<q.nv_HOADON.num<<endl;
	//	addNhanvien(DataNhanvien._nhanvien,q);
	}
	}
	cout<<"so NV::"<<DataNhanvien.num<<endl;
	if(DataNhanvien._nhanvien == NULL) cout<<"no bi NULL";
	duyetLNR_test(DataNhanvien._nhanvien);
//	delKey(DataNhanvien._nhanvien,s);
	cout<<"init thanh cong ";
	f.close();
}
bool Find_HD_byNum(Thongtin_HD &tt,CT_HOADON &ds,Tree t, char soHD[]){
	if(t == NULL ) return false;
	else{
		for(NodeHD* p = t->nv.nv_HOADON.hdHead ; p!=NULL; p = p->_next){
			if(strcmp(soHD,p->thongtin.soHD)==0) {
				tt = p->thongtin;
				ds = p->chitiet;
				return true;
			}
		}
		return (Find_HD_byNum (tt,ds,t->left,soHD)| Find_HD_byNum(tt,ds,t->right,soHD)); 
	}
}
void save_HD_to_NV(Tree &t, char MaNV[],NodeHD* p){
	if(t==NULL) return;
	if(strcmp(t->nv.thongtin.MANV,MaNV)==0){
		addTail_HD(t->nv.nv_HOADON,p);
	}
	if(strcmp(t->nv.thongtin.MANV,MaNV)>0) save_HD_to_NV(t->left,MaNV,p);
	if(strcmp(t->nv.thongtin.MANV,MaNV)<0) save_HD_to_NV(t->right,MaNV,p);
}
long Num_day(char ngay[], char thang[],char nam[]){
	
	long ans =0;
	if(strlen(ngay)==1) {
	ngay[1] = ngay[0];
	ngay[0] = '0';
	}
	if(strlen(thang)==1) {
	thang[1] = thang[0];
	thang[0] = '0';
	}

	for(int i=0;i<strlen(nam);i++) ans= ans*10 + (nam[i] -'0'); 
	for(int i=0;i<strlen(thang);i++) ans= ans*10 + (thang[i]-'0'); 
	for(int i=0;i<strlen(ngay);i++) ans= ans*10 + (ngay[i]-'0'); 
	return ans;
}
NodeNV* Find_HD_thongke (Tree t,int begin,int end){
	NodeNV* give = new NodeNV; 
	init_hd(give->nv.nv_HOADON);
	for(NodeHD* p = t->nv.nv_HOADON.hdHead;p!=NULL;p = p->_next){
		int num = Num_day(p->thongtin.day,p->thongtin.month,p->thongtin.year);
		cout<<"\nnum"<<num<<endl;
		NodeHD* s = new NodeHD;
		s->thongtin = p->thongtin;
		s->chitiet = p->chitiet;
		s->_next = NULL;
		if(num>=begin && num<=end){
			addTail_HD(give->nv.nv_HOADON,s);
		}
	}
	//cout<<"\nloop6";
	return give;
}
void Find_NV_thongke (Tree &ds,Tree t,int begin, int end){
	if(t == NULL ) return;
	NodeNV* p = new NodeNV;
	p = Find_HD_thongke(t,begin,end);
	p->nv.thongtin = t->nv.thongtin;
	if(p->nv.nv_HOADON.hdHead !=NULL) Insert_NV(p,ds);
	 Find_NV_thongke(ds,t->left,begin,end);
	 Find_NV_thongke(ds,t->right,begin,end);
}
DsNhanvien Thongke_HD(Tree t,int begin,int end){
	DsNhanvien ds_nv;
	init_nv(ds_nv._nhanvien);
	cout<<"\nloop2";
	Find_NV_thongke(ds_nv._nhanvien,t,begin,end);
	cout<<"\nloop3";
	return ds_nv;
}
int Number(char s[]){
	int ans = 0;
	for(int i=0;i<strlen(s);i++) ans= ans *10 + (s[i]-'0');
	return ans;
}
int Tri_gia_HD(CT_HOADON x){
	int ans = 0;
	for(NodeCT* q = x.ctHead; q!=NULL;q = q->_next){
		int sluong = Number(q->thongtin.soluong);
		int dgia = Number(q->thongtin.Dongia);
		int value = sluong*dgia;
		int Vat = Number(q->thongtin.VAT) ;
		ans += value*(1+Vat/100);
	}
	return ans;
}
void Xuat_TK_HD(Thongtin_HD tt,char Ho[],char Ten[],int trigia,int x,int y,unsigned short int c_line[]){
	outtextxy(x+c_line[0],y,tt.soHD);
	char ngay[100];
	char ten[100];
	strcpy(ngay,tt.day);
	strcat(ngay,"/");
	strcat(ngay,tt.month);
	strcat(ngay,"/");
	strcat(ngay,tt.year);
	strcpy(ten,Ho);
	strcat(ten," ");
	strcat(ten,Ten);
	outtextxy(x+c_line[1],y,ngay);
	char buff[2];
	buff[0] = tt.loai;
	buff[1] = '\0';
	outtextxy(x+c_line[2],y,buff);
	outtextxy(x+c_line[3],y,ten);
	char tgia[100];
	itoa(trigia,tgia,10);
	outtextxy(x+c_line[4],y,tgia);
}
void Print_TK_HD(Tree t,int x ,int y,int page, unsigned short int c_line[]){
	if( t== NULL) return;
	
	for(NodeHD* p = t->nv.nv_HOADON.hdHead;p!=NULL;p = p->_next){
	int sg = pt%10;
	if(sg == 0) sg =10;
		cout<<"Vi tri::"<<pt<<":::"<<sg<<endl;
	if(pt>(page-1)*10&&pt<=(page*10))	Xuat_TK_HD(p->thongtin,t->nv.thongtin.HO,t->nv.thongtin.TEN,Tri_gia_HD(p->chitiet),x,y+(sg-1)*37,c_line);
		pt++;
	}
	Print_TK_HD(t->left,x,y,page,c_line);
	Print_TK_HD(t->right,x,y,page,c_line);
	
}
void Print_TK(Tree t,int x ,int y,int page, unsigned short int c_line[]){
	pt = 1;
	Print_TK_HD(t,x,y,page,c_line);
}

void count_TK_HD(Tree t){
	if( t== NULL) return;
	
	for(NodeHD* p = t->nv.nv_HOADON.hdHead;p!=NULL;p = p->_next){
		pt++;
	}
	count_TK_HD(t->left);
	count_TK_HD(t->right);
	
}
int count_TK(Tree t){
	pt = 1;
	count_TK_HD(t);
	return pt;
}

void save_node(NodeNV* p){
	if(p == NULL) return;
	Thongtin_NV k = p->nv.thongtin;
	//cout<<"k::::"<<k.MANV<<endl;
	f2.write((char*) &k,sizeof(Thongtin_NV));
	int sl_hd = p->nv.nv_HOADON.num;
	f2.write((char*)&sl_hd,sizeof(int));
	for(NodeHD* q = p->nv.nv_HOADON.hdHead;q!=NULL;q = q->_next ){
		Thongtin_HD tt_hd = q->thongtin;
		f2.write((char*)&tt_hd,sizeof(Thongtin_HD));
		int get = q->chitiet.num;
		f2.write((char*)&get,sizeof(int));
		for(NodeCT* s = q->chitiet.ctHead ; s !=NULL;s = s->_next){
			Thongtin_CT tt_ct = s->thongtin;
			f2.write((char*)&tt_ct,sizeof(Thongtin_CT));
		}
	}
	save_node(p->left);
	save_node(p->right);
}

void save_Nhanvien()
{
 
	f2.open("Data/DataNhanvien.data",ios::binary | ios :: out);
	save_node(DataNhanvien._nhanvien);
	f2.close();
}
//void initdataNhanvien(){
//	ifstream f;
//	char* s ;
//	f.open("Data/DataNhanvien.data",ios::binary);
//	bool check = false;
//	int sl_nv;
//	if(f){
//	//	f.read((char*)bufnv,sizeof(int));
//		while(!f.eof()
//		Thongtin_NV p;
//		f.read(reinterpret_cast<char*>(&p),sizeof(p));
//		cout<<"doc :: Nhanvien:::"<<p.MANV<<endl;
//		s = p.MANV;
//		//cout<<"Ma NV "<<s<<endl;
//		Nhanvien q;
//		q.thongtin = p;
//		int sl_hd;
//		char * buf;
//		f.read(reinterpret_cast<char*>(&buf),sizeof(int));
//		sl_hd = (int) buf;
//		cout<<"doc:::sl_hd:::"<<sl_hd<<endl;
//		DsHOADON ds_hd;
//		init_hd(ds_hd);
//		q.nv_HOADON.num = sl_hd;
//	//	cout<<"sl_hd ::"<<sl_hd<<endl;
//	//	cout<<"2:::\n";
//		for(int i = 1;i<=sl_hd;i++){
//			Thongtin_HD v;
//			int sl_ct;
//			char* buff;
//			NodeHD* node_hd = new NodeHD;
//			f.read(reinterpret_cast<char*>(&buff),sizeof(int));
//			sl_ct = (int) buff;
//			CT_HOADON ct_hd;
//		//	cout<<"so HD ::"<<v.soHD<<endl;
//		//	cout<<"3::::";
//			init_ct(ct_hd);
//			f.read(reinterpret_cast<char*>(&sl_ct),sizeof(sl_ct));
//			for(int j=1; j<=sl_ct ;j++){
//				Thongtin_CT u;
//			//	cout<<"4::\n";
//				f.read(reinterpret_cast<char*>(&u),sizeof(u));
//				NodeCT* node_ct = GetNode_CT(u);
//				addTail_CT(ct_hd,node_ct);
//			}
//			//cout<<"5:::\n";
//			node_hd = GetNode_hd(v,ct_hd);
//		//	cout<<"6::::\n";
//			addTail_HD(ds_hd,node_hd);
//		//	cout<<"7:::\n";
//		}
//		q.nv_HOADON = ds_hd;
//		addNhanvien(DataNhanvien._nhanvien,q);
//	}
//	}
//	else init_nv(DataNhanvien._nhanvien);
////	delKey(DataNhanvien._nhanvien,s);
//	cout<<"init thanh cong ";
//	f.close();
//}
