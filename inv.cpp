#include <windows.h>
#include "resource.h"
#include <mmsystem.h>
#include <dsound.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define randomize() srand ((unsigned int)time (NULL))

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "msimg32.lib")

LPDIRECTSOUND8 ds;
LPDIRECTSOUNDBUFFER snd_play[15];

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LPCTSTR frm_title=TEXT("c_form_view");
HINSTANCE hInst;

int screenW = GetSystemMetrics(SM_CXSCREEN);
int screenH = GetSystemMetrics(SM_CYSCREEN);
int scrw =1032;
int scrh =802;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
        HWND hWnd;
        MSG Msg_frm;
        WNDCLASS WndClass;
		hInst=hInstance;
        
        WndClass.style=CS_HREDRAW | CS_VREDRAW;
        WndClass.lpfnWndProc=WndProc;
        WndClass.cbClsExtra=0;
        WndClass.cbWndExtra=0;
        WndClass.hInstance=hInstance;
        WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON2));
        WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
        WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
        WndClass.lpszMenuName=NULL;
        WndClass.lpszClassName=frm_title;

        RegisterClass(&WndClass);

        hWnd=CreateWindow(
                frm_title,
                "임진왜란",
                WS_OVERLAPPEDWINDOW,
                (screenW-scrw)/2,
                (screenH-scrh)/2,
                scrw,
                scrh,
                NULL,
                (HMENU)NULL,
                hInstance,
                NULL);

        ShowWindow(hWnd,nCmdShow);
        
        while (GetMessage(&Msg_frm,NULL,0,0)) {
                TranslateMessage(&Msg_frm);
                DispatchMessage(&Msg_frm);
        }
        return (int)Msg_frm.wParam;
}


int dsloadwave(int sndnum,char *FileName);
void key_dwn(int ke);
HWND hWnd1;

struct data{
	int map; //진행량
	int umoney; //사용된돈
	int money; //소유돈
	int pop; //소유인구수
	int upop; //사용인구수
	int utime; //소모시간
	int life; //라이프
	int att; //공격력
	int dif; //방어력
	int enemy; //적군 공.방어력 비율
	int food; //식량
	int farmer; //농부
};
struct mon1{
	int on;
	int x;
	int y;
	int hp;
	int mv;
};
struct mon2{
	int on;
	int x;
	int y;
	int hp;
	int mv;
};
struct mon3{
	int on;
	int x;
	int y;
	int hp;
	int mv;
};
struct mon4{
	int on;
	int x;
	int y;
	int hp;
	int mv;
};


	int sn=0,titlen=-1,titlem=0,titlew=0,buth=-1001,butn=0,maptype=0,cnt=0,tm=0,tmh,gstm,gst=0,tmm,tms,first,stm,x,y,tshow,ton=0,snm=0,gm=0,fs,fsb,fming=0,stpx=120,flmo=0,gk,flsize[12],minfo=0,petcnt=0,petk,petcntn=0,wnum,blendn=250,Bx,By,g1wn,g1won=0,g1wc=0,g1m1x[20],mdl[4][20],chp,tchp,cham,chad,gg,hh,g2dl=0,g2ck=0,g2x,g2y,g2k=0,g2at=0,g2m=0,g2ma=0,g2am=0,g3road=0,g3road2=0,g3chax,g3cham,g3chaw,g3chamm,g3ln,g3lnk,g3p,g3py,g3pa=0,g3page,g3gage,barg,g4gage,g4c1,g4c2,g4c4,g4c3,g4c1cnt,g4c2cnt,g4c3cnt,g4c4cnt,g4k,g4e1cnt,g4e2cnt,g4e3cnt,g4e4cnt,g4ehp[100],g4eon[100],g4et[100],g4ex[100],g4emv[100],g4emvv[100],g4gg,ext,exg1,exg2,exg3,exg4,exxon;
	int dif,difon=0,difx=0,papx=120,pwords=0,pp=0,ppp=0,wrd=0,aa=0,bb=0,cc=0,dd=0,ee=0,ff,ii,jj,kk,mapix=0,mapon=0,mapbut=0,b1release=0,b2release=0,chanum=0,uclx=-230,dclx=1024,g1wx=366,g1wy=0,g1m1y[20],mvn[4][20],barl,chax,chay,chac=0,g2f=0,g2ff=0,g2m1d[7],g2m2d[7],g2m3d[5],g2m4d,g3pilon,g3pily,g3x,g3by[170],g3bx[170],g3bon[170],g3bt=0,g3mt=0,g3gg=0,mk[50],g3poc[170],g3pocx[170],g3pocy[170],g3pocm[170],g3pocmm[170],g3cnt=0,g3tm=0,g3tmm=0,g4mv,g4mvy,g4bga,g4bbg,g4cn,g4chp[100],g4con[100],g4ct[100],g4cx[100],g4cmv[100],g4cmvv[100],g4e1,g4e2,g4e3,g4e4,g4en,g4ctch[100],g4etch[100],g4cm[100],g4em[100],g4ec,g4e,ebar,g4s,cout,mout,pout;
	char prn_wrd[500],warnam[50],wor[50],warex[10][500];
	long tsc;
	struct data dat;
	struct mon1 m1[20];
	struct mon2 m2[20];
	struct mon3 m3[10];
	struct mon4 m4[10];
	struct mon1 m[50];


LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,DC1,btmDC,DC;
	PAINTSTRUCT PS1;
	static HBITMAP btm_bg,btm_title,btm_but,btm_pet,btm_g4sun,btm_stampe,btm_ppe,btm_let,btm_lev,btm_levbut,btm_paper,btm_upg,btm_win,btm_lose,btm_stamp,btm_town,btm_mapfield,btm_chai,btm_paperf,btm_road,btm_g1we,btm_g1re,btm_g2re,btm_g2map,btm_g3map,btm_g3re,btm_g3cha,btm_pps,btm_ppu,btm_ppg,btm_ppm,btm_ppp,btm_nstamp,btm_gex,btm_g4re,btm_g4cha,btm_g4bg,btm_texp1,btm_g1exp1,btm_g1exp2,btm_g2exp1,btm_g2exp2,btm_g3exp1,btm_g3exp2,btm_g4exp,btm_exx,btm_tore;
	HBITMAP btm1,mbtm1,mbtm2;
	FILE *input;
	


 BLENDFUNCTION a;
     static int Alpha = 200;
     int bx = 120, by = 120;
     a.BlendOp = AC_SRC_OVER;
     a.BlendFlags = 0;
     a.SourceConstantAlpha = Alpha;
     a.AlphaFormat = 0;	



	static HANDLE hin,hout;
	static INPUT_RECORD rec;

	HFONT font1,font2;
//	FILE *input;
//	char ch;

        switch (iMsg) {
		case WM_CREATE:

			for(dd=0;dd<20;dd++){
				m1[dd].on=0;
				m1[dd].mv=0;
				m1[dd].x=0;
				m1[dd].y=0;

				m2[dd].on=0;
				m1[dd].mv=0;
				m2[dd].x=0;
				m2[dd].y=0;
				if(dd<=9){
					m3[dd].on=0;
					m3[dd].mv=0;
					m3[dd].x=0;
					m3[dd].y=0;

					m4[dd].on=0;
					m4[dd].mv=0;
					m4[dd].x=0;
					m4[dd].y=0;
				}
				mvn[0][dd]=0;
				mvn[1][dd]=0;
				mvn[2][dd]=0;
				mvn[3][dd]=0;
				mdl[0][dd]=0;
				mdl[1][dd]=0;
				mdl[2][dd]=0;
				mdl[3][dd]=0;
			}
			dd=0;
			g4s=0;
			ext=0;
			exg1=0;
			exg2=0;
			exg3=0;
			exg4=0;
			exxon=0;
			DirectSoundCreate8(NULL,&ds,NULL);
			ds->SetCooperativeLevel(hWnd,DSSCL_NORMAL);
			dsloadwave(0,".\\sound\\start_bg.wav");
			dsloadwave(1,".\\sound\\title.wav");
			dsloadwave(2,".\\sound\\sbut.wav");
			dsloadwave(3,".\\sound\\town.wav");
			dsloadwave(4,".\\sound\\money.wav");
			dsloadwave(5,".\\sound\\upgrade.wav");
			dsloadwave(6,".\\sound\\walk.wav");
			dsloadwave(7,".\\sound\\game1_bg.wav");
			dsloadwave(8,".\\sound\\game1_effect.wav");
			dsloadwave(9,".\\sound\\game2_bg.wav");
			dsloadwave(10,".\\sound\\game2_effect.wav");
			dsloadwave(11,".\\sound\\game3_bg.wav");
			dsloadwave(12,".\\sound\\game3_effect.wav");
			dsloadwave(13,".\\sound\\game4_bg.wav");
			dsloadwave(14,".\\sound\\game4_effect.wav");
			btm_bg=LoadBitmap(hInst,MAKEINTRESOURCE(bg));
			btm_title=LoadBitmap(hInst,MAKEINTRESOURCE(titles));
			btm_but=LoadBitmap(hInst,MAKEINTRESOURCE(buts));
			btm_lev=LoadBitmap(hInst,MAKEINTRESOURCE(levs));
			btm_levbut=LoadBitmap(hInst,MAKEINTRESOURCE(levbuts));
			btm_paper=LoadBitmap(hInst,MAKEINTRESOURCE(paper));
			btm_stamp=LoadBitmap(hInst,MAKEINTRESOURCE(stamp));
			btm_town=LoadBitmap(hInst,MAKEINTRESOURCE(town));
			btm_mapfield=LoadBitmap(hInst,MAKEINTRESOURCE(mapfield));
			btm_chai=LoadBitmap(hInst,MAKEINTRESOURCE(chai));
			btm_paperf=LoadBitmap(hInst,MAKEINTRESOURCE(paperf));
			btm_road=LoadBitmap(hInst,MAKEINTRESOURCE(road));
			btm_g1re=LoadBitmap(hInst,MAKEINTRESOURCE(g1re));
			btm_g1we=LoadBitmap(hInst,MAKEINTRESOURCE(g1we));
			btm_g2re=LoadBitmap(hInst,MAKEINTRESOURCE(g2re));
			btm_g2map=LoadBitmap(hInst,MAKEINTRESOURCE(g2map));
			btm_g3map=LoadBitmap(hInst,MAKEINTRESOURCE(g3map));
			btm_g3re=LoadBitmap(hInst,MAKEINTRESOURCE(g3re));
			btm_g3cha=LoadBitmap(hInst,MAKEINTRESOURCE(g3cha));
			btm_pps=LoadBitmap(hInst,MAKEINTRESOURCE(papers));
			btm_ppu=LoadBitmap(hInst,MAKEINTRESOURCE(paperu));
			btm_ppg=LoadBitmap(hInst,MAKEINTRESOURCE(paperg));
			btm_ppm=LoadBitmap(hInst,MAKEINTRESOURCE(paperm));
			btm_ppp=LoadBitmap(hInst,MAKEINTRESOURCE(paperp));
			btm_nstamp=LoadBitmap(hInst,MAKEINTRESOURCE(nstamp));
			btm_gex=LoadBitmap(hInst,MAKEINTRESOURCE(gex));
			btm_upg=LoadBitmap(hInst,MAKEINTRESOURCE(upg));
			btm_win=LoadBitmap(hInst,MAKEINTRESOURCE(win));
			btm_lose=LoadBitmap(hInst,MAKEINTRESOURCE(lose));
			btm_pet=LoadBitmap(hInst,MAKEINTRESOURCE(pet));
			btm_ppe=LoadBitmap(hInst,MAKEINTRESOURCE(papere));
			btm_stampe=LoadBitmap(hInst,MAKEINTRESOURCE(stampe));
			btm_let=LoadBitmap(hInst,MAKEINTRESOURCE(let));
			btm_g4re=LoadBitmap(hInst,MAKEINTRESOURCE(g4re));
			btm_g4bg=LoadBitmap(hInst,MAKEINTRESOURCE(g4bg));
			btm_g4cha=LoadBitmap(hInst,MAKEINTRESOURCE(g4cha));
			btm_g4sun=LoadBitmap(hInst,MAKEINTRESOURCE(g4sun));
			btm_texp1=LoadBitmap(hInst,MAKEINTRESOURCE(texp1));
			btm_g1exp1=LoadBitmap(hInst,MAKEINTRESOURCE(g1exp1));
			btm_g1exp2=LoadBitmap(hInst,MAKEINTRESOURCE(g1exp2));
			btm_g2exp1=LoadBitmap(hInst,MAKEINTRESOURCE(g2exp1));
			btm_g2exp2=LoadBitmap(hInst,MAKEINTRESOURCE(g2exp2));
			btm_g3exp1=LoadBitmap(hInst,MAKEINTRESOURCE(g3exp1));
			btm_g3exp2=LoadBitmap(hInst,MAKEINTRESOURCE(g3exp2));
			btm_g4exp=LoadBitmap(hInst,MAKEINTRESOURCE(g4exp));
			btm_exx=LoadBitmap(hInst,MAKEINTRESOURCE(exx));
			btm_tore=LoadBitmap(hInst,MAKEINTRESOURCE(tore));
			SetTimer(hWnd,1,40,NULL);
			hin=GetStdHandle(STD_INPUT_HANDLE);
			hout=GetStdHandle(STD_OUTPUT_HANDLE);


			for(cc=0;cc<12;cc++){
				flsize[cc]=50;
			}


			return 0;



		case WM_TIMER:
			if(sn==0){//시작화면
				titlem+=3;
				if(titlem>50){
					if(titlen<3){
						titlen++;
						titlew=10;
						snd_play[1]->Play(0,0,NULL);
					}
					titlem=0;
				}
				if(titlen==3){
					if(buth<437){
						buth=buth+70;
					}else if(buth>437){
						buth=437;
						snd_play[0]->Play(0,0,DSBPLAY_LOOPING);
					}
				}
				if(difon==2)
					if(snm==0)
						if(papx<894)
							papx=papx+60;
						else if(papx>894)
							papx=894;
						else if(papx=894)
							pwords=1;

					if(snm==1)
						if(papx>129)
							papx=papx-60;
						else if(papx<129)
							papx=129;
						else if(papx=129)
							snm=2;

					if(snm==2)
						if(blendn>0){
							blendn=blendn-20;
						}else if(blendn<=0){
							sn=1;
							snm=0;
							chax=(1024-96)/2;
							chay=(768-96)/2;
							chad=0;
							cham=0;
						}
				if(petcnt==1){
					petcntn+=4;
					if(petcntn>100){
						petcnt=0;
						petcntn=0;
						if(petk==1){
							snm=2;
						}
					}
				}
			}else if(sn==1){
				key_dwn(wParam);
				if(petcnt==1){
					petcntn++;
					if(petcntn>25 && maptype==3){
						petcnt=0;
						petcntn=0;
						if(maptype==3){
							mapon=0;
							mapbut=0;
							maptype=0;
							chay+=30;
						}
					}else if(petcntn>45){
						petcnt=0;
						petcntn=0;
						cout=0;
						pout=0;
						mout=0;
					}
				}
				if(mapon==1){
						if(papx<894)
							papx=papx+60;
						else if(papx>894){
							papx=894;
						}else if(papx=894){
							mapbut=1;
							if(flmo==0)
								for(aa=0;aa<12;aa++)
									if(flsize[0]>28)
										flsize[aa]=flsize[aa]-2;
									else if(flsize[0]<=28)
										flmo=1;

						}
				}else if(mapon==2){
						if(papx>129)
							papx=papx-60;
						else if(papx<129)
							papx=129;
						else if(papx=129)
							mapon=0;
							flmo=0;
							maptype=0;

				}
			}else if(sn==2){
				if(gst<25) gst++;
				else{
					gst=0;
					gstm++;
				}
				if(uclx<=1024){
					uclx=uclx+1;
				}else if(uclx>1024){
					uclx=-196;
				}
				if(dclx>=-180){
					dclx=dclx-2;
				}else if(dclx<-180){
					dclx=1024;
				}
				if(g1won==1){
					g1wc++;
					if(g1wc>=1){
						if(g1wn<11){
							g1wn++;
						}else{
							g1wn=0;
							g1won=0;
						}
						g1wc=0;
					}
				}
				if(ton==1){
					tshow++;
					if(tshow>=75){
						tshow=0;
						ton=0;
						first=0;
						sn=1;
					}
				}
			}else if(sn==3){
				key_dwn(wParam);
				g2ff++;
				if(g2ff>=15){
					g2f++;
					g2ff=0;
				}
				if(g2f>=4)
					g2f=0;
				if(ton==1){
					tshow++;
					if(tshow>=75){
						tshow=0;
						ton=0;
						first=0;
						sn=1;
					}
				}
			}else if(sn==4){
				g3road+=6;
				if(g3road>768)
					g3road=0;
				g3road2+=6;
				if(g3road2>768)
					g3road2=0;
				g3chamm++;
				if(g3cham<6){
					if(g3chamm>2){
						g3cham++;
						g3chamm=0;
					}
				}else if(g3cham>=6){
					if(g3chamm>6){
						g3cham=0;
						g3chamm=0;
					}
				}
				g3bt++;
				g3mt++;
				g3lnk++;
			}
			g3tmm++;
			if(g3tmm>25){
				g3tmm=0;
				g3tm++;
			}
				if(ton==1){
					tshow++;
					if(tshow>=75){
						tshow=0;
						ton=0;
						first=0;
						sn=1;
					}
				}
			if(sn!=0){
				if(dat.map<12 || dat.life < 0){
					if(tm<25) tm++;
					else{
						tm=0;
						dat.utime++;
					}
					if(fming==0){
						fsb=dat.utime;
						fming=1;
					}else if(fming==1){
						if(dat.utime>= fsb+60){
							dat.food+=dat.farmer;
							fming=0;
						}
					}
				}
			}
			InvalidateRect(hWnd,NULL,FALSE);
			return 0;



		case WM_PAINT:
			hWnd1=hWnd;
			DC=BeginPaint(hWnd,&PS1);//실제
			DC1=CreateCompatibleDC(DC);//더블
			btmDC=CreateCompatibleDC(DC);
			mbtm1=CreateCompatibleBitmap(DC,1024,768);
			mbtm2=(HBITMAP)SelectObject(DC1,mbtm1);
			PatBlt(DC1,0,0,1024,768,WHITENESS);
			if(sn==0){//시작화면	
				btm1=(HBITMAP)SelectObject(btmDC,btm_bg);
				//GetObject(btm1,sizeof(BITMAP),&bit1);
				BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCCOPY);//시작배경

				btm1=(HBITMAP)SelectObject(btmDC,btm_title);
				BitBlt(DC1,titlew,0,1024,768,btmDC,1024*titlen,768,SRCPAINT);//시작제목
				BitBlt(DC1,titlew,0,1024,768,btmDC,1024*titlen,0,SRCAND);
				titlew=0;

				btm1=(HBITMAP)SelectObject(btmDC,btm_but);
				BitBlt(DC1,650,buth,254,331,btmDC,butn*254,331,SRCPAINT);//시작버튼
				BitBlt(DC1,650,buth,254,331,btmDC,butn*254,0,SRCAND);
				if(difon==1){
					btm1=(HBITMAP)SelectObject(btmDC,btm_lev);
					BitBlt(DC1,312,259,400,250,btmDC,dif*400,0,SRCCOPY);//난이도버튼
					btm1=(HBITMAP)SelectObject(btmDC,btm_levbut);
					BitBlt(DC1,670,262,25,25,btmDC,difx*25,0,SRCCOPY);//난이도취소버튼
				}else if(difon==2){ //두루마기
					btm1=(HBITMAP)SelectObject(btmDC,btm_paperf);
					BitBlt(DC1,0,0,papx,759,btmDC,0,759,SRCPAINT);
					BitBlt(DC1,0,0,papx,759,btmDC,0,0,SRCAND);
					BitBlt(DC1,papx,0,129,759,btmDC,894,759,SRCPAINT);
					BitBlt(DC1,papx,0,129,759,btmDC,894,0,SRCAND);
					if(pwords==1){
						if(snm==0){
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							BitBlt(DC1,750,480,120,122,btmDC,aa*120,122,SRCPAINT); //도장
							BitBlt(DC1,750,480,120,122,btmDC,aa*120,0,SRCAND);
						}else if(snm==1){
							if(papx<=870){
								if(stpx>0)
									stpx=stpx-60;
								btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
								BitBlt(DC1,750,480,stpx,122,btmDC,aa*120,122,SRCPAINT);
								BitBlt(DC1,750,480,stpx,122,btmDC,aa*120,0,SRCAND);
							}
						}

					}

				}
				if(petcnt==1){
					btm1=(HBITMAP)SelectObject(btmDC,btm_pet);
					BitBlt(DC1,312,259,400,250,btmDC,0,petk*250,SRCCOPY);
				}
				if(snm==2){
					Alpha=blendn;
					PatBlt(DC,0,0,1024,768,BLACKNESS);
					AlphaBlend(DC,0,0,1024,768,DC1,0,0,1024,768,a);			
				}
				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);
			}else if(sn==1){//마을화면
				snd_play[0]->Stop();
				snd_play[7]->Stop();
				snd_play[9]->Stop();
				snd_play[11]->Stop();
				snd_play[13]->Stop();
				snd_play[3]->Play(0,0,DSBPLAY_LOOPING);

				btm1=(HBITMAP)SelectObject(btmDC,btm_town);
				BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCCOPY); //마을
				
				btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
				BitBlt(DC1,chax,chay,96,96,btmDC,384+chac*96,600+chad*96,SRCPAINT);//캐릭터
				BitBlt(DC1,chax,chay,96,96,btmDC,chac*96,600+chad*96,SRCAND);

				if(ext==0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_texp1);//설명1
					BitBlt(DC1,0,0,1024,768,btmDC,0,768,SRCPAINT);
					BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCAND);	
					
					btm1=(HBITMAP)SelectObject(btmDC,btm_tore);//설명2
					BitBlt(DC1,chax-10,chay-10,329,113,btmDC,768,713,SRCPAINT);
					BitBlt(DC1,chax-10,chay-10,329,113,btmDC,768,600,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_exx);//설명버튼
					BitBlt(DC1,6,81,153,37,btmDC,0,37*exxon,SRCCOPY);
				}

				btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
				BitBlt(DC1,10,10,30,30,btmDC,1137,630,SRCPAINT);
				BitBlt(DC1,10,10,30,30,btmDC,1137,600,SRCAND);//동전아이콘

				BitBlt(DC1,5,45,40,31,btmDC,1097,631,SRCPAINT);
				BitBlt(DC1,5,45,40,31,btmDC,1097,600,SRCAND);//인구수아이콘

				BitBlt(DC1,950,15,60,40,btmDC,768+mapix*60,866,SRCPAINT);
				BitBlt(DC1,950,15,60,40,btmDC,768+mapix*60,826,SRCAND);//지도아이콘

				font1=CreateFont(20,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
				SetBkMode(DC1,TRANSPARENT);
				font2=(HFONT)SelectObject(DC1,font1);
				wsprintf(prn_wrd,"%d전",dat.money);
				TextOut(DC1,50,13,prn_wrd,strlen(prn_wrd));
				wsprintf(prn_wrd,"목숨 %d개",dat.life);
				TextOut(DC1,50,48,prn_wrd,strlen(prn_wrd));
				 
				if(chax>=420 && chax <= 624-96 && chay>=150-96&& chay <= 196-96){
					maptype=2;	
					if(mapon==0) mapon=1;
				}else if(chax >= 315 && chax <= 430-96 && chay>=340-96 && chay <= 382-96){
					maptype=3;
					if(mapon==0) mapon=1;
				}else if(chax >= 600-96 && chax <= 634-96 && chay>=419-96 && chay <= 443-96){
					maptype=4;
					if(mapon==0) mapon=1;
				}else if(chax >= 400 && chax <= 430 && chay>=560-96 && chay <= 590-96){
					maptype=5;
					if(mapon==0) mapon=1;
				}else if(chax >= 600-96 && chax <= 634-96 && chay>=700-96 && chay <= 730-96){
					maptype=6;
					if(mapon==0) mapon=1;
				}
				if(dat.map>=12||dat.life<0){
					maptype=7;
					if(mapon==0) mapon=1;
				}
				if(mapon>=1){
					if(maptype==1) btm1=(HBITMAP)SelectObject(btmDC,btm_mapfield);
					else if(maptype==2) btm1=(HBITMAP)SelectObject(btmDC,btm_ppg);
					else if(maptype==3) btm1=(HBITMAP)SelectObject(btmDC,btm_pps);
					else if(maptype==4) btm1=(HBITMAP)SelectObject(btmDC,btm_ppm);
					else if(maptype==5) btm1=(HBITMAP)SelectObject(btmDC,btm_ppp);
					else if(maptype==6) btm1=(HBITMAP)SelectObject(btmDC,btm_ppu);
					else if(maptype==7) btm1=(HBITMAP)SelectObject(btmDC,btm_ppe);
						BitBlt(DC1,0,0,papx,759,btmDC,0,759,SRCPAINT);
						BitBlt(DC1,0,0,papx,759,btmDC,0,0,SRCAND);
						BitBlt(DC1,papx,0,129,759,btmDC,894,759,SRCPAINT);
						BitBlt(DC1,papx,0,129,759,btmDC,894,0,SRCAND);
					if(maptype==1){
						if(mapbut==1){
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							BitBlt(DC1,750,480,120,122,btmDC,dd*120,122,SRCPAINT); //도장
							BitBlt(DC1,750,480,120,122,btmDC,dd*120,0,SRCAND);

							btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
							if(dat.map>11){
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,858,906,30,30,SRCPAINT); //노량
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==11){
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<11){
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,500,557,flsize[11],flsize[11],btmDC,768,906,30,30,SRCAND);
							}

							if(dat.map>10){
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,858,906,30,30,SRCPAINT); //명량
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==10){
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<10){
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,415,570,flsize[10],flsize[10],btmDC,768,906,30,30,SRCAND);
							}
							
							if(dat.map>9){
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,858,906,30,30,SRCPAINT); //행주
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==9){
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<9){
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,446,324,flsize[9],flsize[9],btmDC,768,906,30,30,SRCAND);
							}	


							if(dat.map>8){
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,858,906,30,30,SRCPAINT); //평양성
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==8){
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<8){
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,387,240,flsize[8],flsize[8],btmDC,768,906,30,30,SRCAND);
							}

							if(dat.map>7){
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,858,906,30,30,SRCPAINT); //진주
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==7){
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<7){
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,520,529,flsize[7],flsize[7],btmDC,768,906,30,30,SRCAND);
							}

							if(dat.map>6){
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,858,906,30,30,SRCPAINT); //연안
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==6){
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<6){
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,387,296,flsize[6],flsize[6],btmDC,768,906,30,30,SRCAND);
							}	
		
							if(dat.map>5){
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,858,906,30,30,SRCPAINT); //거창 사랑암
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==5){
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<5){
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,525,477,flsize[5],flsize[5],btmDC,768,906,30,30,SRCAND);
							}	


							if(dat.map>4){
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,858,906,30,30,SRCPAINT); //청주성
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==4){
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<4){
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,479,412,flsize[4],flsize[4],btmDC,768,906,30,30,SRCAND);
							}	
		

							if(dat.map>3){
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,858,906,30,30,SRCPAINT); //영천성
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==3){
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<3){
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,588,456,flsize[3],flsize[3],btmDC,768,906,30,30,SRCAND);
							}

							if(dat.map>2){
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,858,906,30,30,SRCPAINT); //한산도
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==2){
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<2){
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,546,544,flsize[2],flsize[2],btmDC,768,906,30,30,SRCAND);
							}


							if(dat.map>1){
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,858,906,30,30,SRCPAINT); //웅치-이치
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==1){
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,828,906,30,30,SRCAND);
							}else if(dat.map<1){
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,484,456,flsize[1],flsize[1],btmDC,768,906,30,30,SRCAND);
							}

							if(dat.map>0){
								StretchBlt(DC1,525,508,flsize[0],flsize[0],btmDC,858,906,30,30,SRCPAINT); //정암진
								StretchBlt(DC1,525,508,flsize[0],flsize[0],btmDC,798,906,30,30,SRCAND);
							}else if(dat.map==0){
								StretchBlt(DC1,525,508,flsize[0],flsize[0],btmDC,858,906,30,30,SRCPAINT);
								StretchBlt(DC1,525,508,flsize[0],flsize[0],btmDC,828,906,30,30,SRCAND);
							}

							if(flmo==1){
								if(minfo==1){
									btm1=(HBITMAP)SelectObject(btmDC,btm_chai);
									BitBlt(DC1,123,199,170,124,btmDC,170*(chanum-1),124,SRCPAINT); //맵 인물얼굴
									BitBlt(DC1,123,199,170,124,btmDC,170*(chanum-1),0,SRCAND);
									TextOut(DC1,192,345,warnam,strlen(warnam));
									TextOut(DC1,166,376,wor,strlen(wor));
									for(bb=1;bb<=wnum;bb++)
										TextOut(DC1,123,437+25*(bb-1),warex[bb],strlen(warex[bb]));
								}
							}
						}
					}else if(maptype==2){//게임진행창
						if(mapbut==1){
							if(dat.map==0){
								wsprintf(prn_wrd,"정암진 전투");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"잔당소탕전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"10명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=3;
								wsprintf(warex[1],"아군의 첫 승전");
								wsprintf(warex[2],"왜군의 전라도 진격을 저지");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=2;
							}else if(dat.map==1){
								wsprintf(prn_wrd,"웅치-이치 전투");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"성벽방어전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"12명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=3;
								gk=2;
								wsprintf(warex[1],"전주성 접근을 저지");
								wsprintf(warex[2],"한산도 대첩과 이 전투로");
								wsprintf(warex[3]," 인해 전투 상황이 역전");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=1;
							}else if(dat.map==2){
								wsprintf(prn_wrd,"한산도 대첩");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"해상전투");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"14명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=3;
								gk=4;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"학익진을 선보이며 대승을 거둠");
								wsprintf(warex[3],"이 전투로 남해의 재해권 장악");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=3;
							}else if(dat.map==3){
								wsprintf(prn_wrd,"영천성 전투");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"공성전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"16명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=5;
								wsprintf(warex[1],"왜군 수급을 얻어 큰 수확을 거둠");
								wsprintf(warex[2],"왜군은 상주로 퇴각");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=4;
							}else if(dat.map==4){
								wsprintf(prn_wrd,"청주성 전투");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"공성전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"18명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=5;
								wsprintf(warex[1],"곡식을 모두 태워 적의 재점거를");
								wsprintf(warex[2]," 불가능하게 함");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=4;
							}else if(dat.map==5){
								wsprintf(prn_wrd,"거창 사랑암 조우전");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"잔당소탕전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"20명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=3;
								wsprintf(warex[1],"왜군의 전라도 진출을 다시한번");
								wsprintf(warex[2]," 저지");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=2;
							}else if(dat.map==6){
								wsprintf(prn_wrd,"연안 대첩");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"성벽방어전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"22명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=2;
								wsprintf(warex[1],"수적 열세가 컸으나 대승을 거둠");
								wsprintf(warex[2],"후퇴하는 왜군을 쳐 큰 수확을 거둠");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=1;
							}else if(dat.map==7){
								wsprintf(prn_wrd,"진주 대첩");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"성벽방어전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"24명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=3;
								gk=2;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"이마에 탄환을 맞고 김시민 전사");
								wsprintf(warex[3],"왜군의 병력에 엄청난 손실을 입힘");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=1;
							}else if(dat.map==8){
								wsprintf(prn_wrd,"평양성 전투");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"공성전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"26명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=2;
								gk=5;
								wsprintf(warex[1],"조명 연합군의 첫 전투");
								wsprintf(warex[2],"왜군이 수세에 몰리는 결정적인 계기");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=4;
							}else if(dat.map==9){
								wsprintf(prn_wrd,"행주 대첩");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"성벽방어전");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"28명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=6;
								gk=2;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"사기가 최고인 3만 왜군을");
								wsprintf(warex[3]," 적은수로 물리침");
								wsprintf(warex[4],"이 전투에서 이기기 위해 여자들이");
								wsprintf(warex[5]," 긴 치마를 잘라 돌을 욺겼는데");
								wsprintf(warex[6]," 그래서 행주치마란 명칭이 생김");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=1;
							}else if(dat.map==10){
								wsprintf(prn_wrd,"명량 해전");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"해상전투");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"30명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=3;
								gk=4;
								wsprintf(warex[1],"13척의 배로 133척의 왜군 배를 수장");
								wsprintf(warex[2],"이 싸움으로 조선의");
								wsprintf(warex[3]," 해상권을 다시 회복");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=3;
							}else if(dat.map==11){
								wsprintf(prn_wrd,"노량 해전");
								TextOut(DC1,302,286,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"해상전투");
								TextOut(DC1,302,332,prn_wrd,strlen(prn_wrd));
								wsprintf(prn_wrd,"32명");
								TextOut(DC1,302,378,prn_wrd,strlen(prn_wrd));
								wnum=3;
								gk=4;
								wsprintf(warex[1],"임진왜란의 마지막 전투");
								wsprintf(warex[2],"퇴각하는 쫒아 큰 피해를 입힘");
								wsprintf(warex[3],"이순신 장군이 이 전투에서 사망");
								font1=CreateFont(22,0,0,0,FW_NORMAL,1,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
								for(bb=1;bb<=wnum;bb++)
									TextOut(DC1,185,465+25*(bb-1),warex[bb],strlen(warex[bb]));
								gm=3;
							}
							wsprintf(prn_wrd,"%d 명",dat.pop);
							TextOut(DC1,773,160,prn_wrd,strlen(prn_wrd));
							btm1=(HBITMAP)SelectObject(btmDC,btm_gex);
							BitBlt(DC1,600,270,280,330,btmDC,280*(gm-1),330,SRCPAINT);//게임설명
							BitBlt(DC1,600,270,280,330,btmDC,280*(gm-1),0,SRCAND);
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							BitBlt(DC1,475,225,120,122,btmDC,dd*120,122,SRCPAINT);//확인버튼
							BitBlt(DC1,475,225,120,122,btmDC,dd*120,0,SRCAND);
							btm1=(HBITMAP)SelectObject(btmDC,btm_nstamp);
							BitBlt(DC1,475,360,120,122,btmDC,ee*120,122,SRCPAINT);//취소버튼
							BitBlt(DC1,475,360,120,122,btmDC,ee*120,0,SRCAND);
							if(petcnt==1){
								btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
								BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
							}
						}
					}else if(maptype==3){//게임저장창
						if(mapbut==1){
							if(dat.enemy ==8) wsprintf(prn_wrd,"하급");
							else if(dat.enemy ==10) wsprintf(prn_wrd,"중급");
							else if(dat.enemy ==12) wsprintf(prn_wrd,"상급");
							TextOut(DC1,357,240,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d단 강화",(dat.att-10)/2);
							TextOut(DC1,357,278,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d단 강화",(dat.dif-10)/2);
							TextOut(DC1,357,316,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d/12단계",dat.map);
							TextOut(DC1,357,354,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 개",dat.life);
							TextOut(DC1,357,392,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 가마",dat.food);
							TextOut(DC1,357,430,prn_wrd,strlen(prn_wrd));
							stm=dat.utime;
							if(stm>=3600){
								tmh=stm/3600;
								tmm=(stm-tmh*3600)/60;
								tms=stm-tmh*3600-tmm*60;
							}else if(stm< 3600 && stm >= 60){
								tmh=0;
								tmm=(stm-tmh*3600)/60;
								tms=stm-tmh*3600-tmm*60;
							}else if(stm<60){
								tmh=0;
								tmm=0;
								tms=stm-tmh*3600-tmm*60;
							}							
							wsprintf(prn_wrd,"%d 전",dat.money);
							TextOut(DC1,700,240,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 명",dat.pop);
							TextOut(DC1,700,278,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 명",dat.farmer);
							TextOut(DC1,700,316,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d시간 %d분 %d초",tmh,tmm,tms);
							TextOut(DC1,700,354,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 전",dat.umoney);
							TextOut(DC1,700,392,prn_wrd,strlen(prn_wrd));
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							BitBlt(DC1,610,460,120,122,btmDC,dd*120,122,SRCPAINT);//확인버튼
							BitBlt(DC1,610,460,120,122,btmDC,dd*120,0,SRCAND);
							btm1=(HBITMAP)SelectObject(btmDC,btm_nstamp);
							BitBlt(DC1,760,460,120,122,btmDC,ee*120,122,SRCPAINT);//취소버튼
							BitBlt(DC1,760,460,120,122,btmDC,ee*120,0,SRCAND);
							if(petcnt==1){
								btm1=(HBITMAP)SelectObject(btmDC,btm_pet);
								BitBlt(DC1,312,259,400,250,btmDC,0,petk*150,SRCCOPY);
							}
						}
					}else if(maptype==4){//상점창
						if(mapbut==1){
							wsprintf(prn_wrd,"%d 전",dat.money);
							TextOut(DC1,772,145,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 가마",dat.food);
							TextOut(DC1,772,184,prn_wrd,strlen(prn_wrd));
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							StretchBlt(DC1,333,245,60,61,btmDC,dd*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,333,245,60,61,btmDC,dd*120,0,120,122,SRCAND);
							StretchBlt(DC1,784,245,60,61,btmDC,ee*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,784,245,60,61,btmDC,ee*120,0,120,122,SRCAND);
							BitBlt(DC1,452,456,120,122,btmDC,ff*120,122,SRCPAINT);
							BitBlt(DC1,452,456,120,122,btmDC,ff*120,0,SRCAND);
							if(petcnt==1){
								btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
								if(mout==1){
									BitBlt(DC1,212,234,600,300,btmDC,600,0,SRCCOPY);
								}else if(cout==1){
									BitBlt(DC1,212,234,600,300,btmDC,600,300,SRCCOPY);
								}
							}
						}
					}else if(maptype==5){//농부창
						if(mapbut==1){
							wsprintf(prn_wrd,"%d 명",dat.farmer);
							TextOut(DC1,753,225,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 가마",dat.farmer);
							TextOut(DC1,753,266,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 가마",dat.food);
							TextOut(DC1,753,303,prn_wrd,strlen(prn_wrd));
							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							StretchBlt(DC1,350,248,60,61,btmDC,dd*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,350,248,60,61,btmDC,dd*120,0,120,122,SRCAND);
							StretchBlt(DC1,350,435,60,61,btmDC,ee*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,350,435,60,61,btmDC,ee*120,0,120,122,SRCAND);
							BitBlt(DC1,728,442,120,122,btmDC,ff*120,122,SRCPAINT);
							BitBlt(DC1,728,442,120,122,btmDC,ff*120,0,SRCAND);
							if(petcnt==1){
								btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
								if(cout==1){
									BitBlt(DC1,212,234,600,300,btmDC,600,300,SRCCOPY);
								}else if(pout==1){
									BitBlt(DC1,212,234,600,300,btmDC,0,300,SRCCOPY);
								}
							}
						}
					}else if(maptype==6){//제련소창
						if(mapbut==1){
							wsprintf(prn_wrd,"%d 전",dat.money);
							TextOut(DC1,677,158,prn_wrd,strlen(prn_wrd));


							btm1=(HBITMAP)SelectObject(btmDC,btm_stamp);
							StretchBlt(DC1,408,416,60,61,btmDC,dd*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,408,416,60,61,btmDC,dd*120,0,120,122,SRCAND);
							StretchBlt(DC1,836,416,60,61,btmDC,ee*120,122,120,122,SRCPAINT);
							StretchBlt(DC1,836,416,60,61,btmDC,ee*120,0,120,122,SRCAND);
							BitBlt(DC1,428,494,120,122,btmDC,ff*120,122,SRCPAINT);
							BitBlt(DC1,428,494,120,122,btmDC,ff*120,0,SRCAND);
							btm1=(HBITMAP)SelectObject(btmDC,btm_upg);
							if(dat.map>=0) btm1=(HBITMAP)SelectObject(btmDC,btm_upg);
							BitBlt(DC1,206,270,150,150,btmDC,1350,0,SRCPAINT);
							BitBlt(DC1,206,270,150,150,btmDC,(dat.att-10)/2*150,0,SRCAND);
							BitBlt(DC1,652,270,150,150,btmDC,1350,0,SRCPAINT);
							BitBlt(DC1,652,270,150,150,btmDC,(dat.dif-10)/2*150,150,SRCAND);
							wsprintf(prn_wrd,"(강화 가격: %d 전)",(dat.att-9)*(dat.att-9)*100);
							TextOut(DC1,180,465,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"(강화 가격: %d 전)",(dat.dif-9)*(dat.dif-9)*100);
							TextOut(DC1,615,465,prn_wrd,strlen(prn_wrd));
							if(petcnt==1){
								btm1=(HBITMAP)SelectObject(btmDC,btm_tore);
								BitBlt(DC1,212,234,600,300,btmDC,600,0,SRCCOPY);
							}
						}
					}else if(maptype==7){//게임 종료창
						if(mapbut==1){
							btm1=(HBITMAP)SelectObject(btmDC,btm_let);
							if(dat.life<0) BitBlt(DC1,311,236,103,70,btmDC,0,70,SRCCOPY);
							else if(dat.map >= 12) BitBlt(DC1,311,236,103,70,btmDC,0,0,SRCCOPY);
							tsc=dat.map*dat.enemy*(dat.money * 2 + dat.umoney + dat.life * 100 + dat.food * 50 +dat.pop *50 - dat.utime) / 10;
							wsprintf(prn_wrd,"%d 점",tsc);
							TextOut(DC1,305,305,prn_wrd,strlen(prn_wrd));
							if(dat.enemy ==8) wsprintf(prn_wrd,"하급");
							else if(dat.enemy ==10) wsprintf(prn_wrd,"중급");
							else if(dat.enemy ==12) wsprintf(prn_wrd,"상급");
							TextOut(DC1,324,375,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 단 강화",(dat.att-10)/2);
							TextOut(DC1,324,411,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d 단 강화",(dat.dif-10)/2);
							TextOut(DC1,324,447,prn_wrd,strlen(prn_wrd));
							stm=dat.utime;
							if(stm>=3600){
								tmh=stm/3600;
								tmm=(stm-tmh*3600)/60;
								tms=stm-tmh*3600-tmm*60;
							}else if(stm< 3600 && stm >= 60){
								tmh=0;
								tmm=(stm-tmh*3600)/60;
								tms=stm-tmh*3600-tmm*60;
							}else if(stm<60){
								tmh=0;
								tmm=0;
								tms=stm-tmh*3600-tmm*60;
							}	
							wsprintf(prn_wrd,"%d시간 %d분 %d초",tmh,tmm,tms);
							TextOut(DC1,324,483,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d/12단계",dat.map);
							TextOut(DC1,324,519,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d명",dat.pop);
							TextOut(DC1,324,555,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d개",dat.life);
							TextOut(DC1,725,375,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d가마",dat.food);
							TextOut(DC1,725,411,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d명",dat.farmer);
							TextOut(DC1,725,447,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d전",dat.umoney);
							TextOut(DC1,725,483,prn_wrd,strlen(prn_wrd));
							wsprintf(prn_wrd,"%d전",dat.money);
							TextOut(DC1,725,519,prn_wrd,strlen(prn_wrd));
							btm1=(HBITMAP)SelectObject(btmDC,btm_stampe);
							BitBlt(DC1,615,223,120,122,btmDC,ff*120,122,SRCPAINT);
							BitBlt(DC1,615,223,120,122,btmDC,ff*120,0,SRCAND);
						}
					}
				}
				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);
			}else if(sn==2){//성벽방어전
				snd_play[7]->Play(0,0,DSBPLAY_LOOPING);
				snd_play[3]->Stop();
				btm1=(HBITMAP)SelectObject(btmDC,btm_road);//배경
				BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCCOPY);

				btm1=(HBITMAP)SelectObject(btmDC,btm_g1re);
				BitBlt(DC1,uclx,11,196,78,btmDC,0,261,SRCCOPY);//윗구름
				BitBlt(DC1,dclx,91,158,56,btmDC,196,261,SRCCOPY);//아랫구름

				for(aa=0;aa<8;aa++){
					if(m1[aa].on==0){
						m1[aa].x=(rand()%983)+20;
						m1[aa].y=(rand()%1000)-1000;
						m1[aa].hp=50*dat.enemy/10;
						m1[aa].on=1;
						m1[aa].mv=rand()%4;
					}
					if(m2[aa].on==0){
						m2[aa].x=(rand()%983)+20;
						m2[aa].y=(rand()%800)-1000;
						m2[aa].hp=50*dat.enemy/10;
						m2[aa].on=1;
						m2[aa].mv=rand()%4;
					}
				}
				for(bb=0;bb<4;bb++){
					if(m3[bb].on==0 && dat.map >=6){
						m3[bb].x=(rand()%932)+46;
						m3[bb].y=(rand()%800)-1000;
						m3[bb].hp=300*dat.enemy/10;
						m3[bb].on=1;
						m3[bb].mv=rand()%4;
					}
					if(m4[bb].on==0 && dat.map >=9){
						m4[bb].x=(rand()%992)+16;
						m4[bb].y=(rand()%800)-1000;
						m4[bb].hp=200*dat.enemy/10;
						m4[bb].on=1;
						m4[bb].mv=rand()%4;
					}
				}

				for(dd=0;dd<8;dd++){//1,2번 적 움직임
						mdl[0][dd]++;
						mdl[1][dd]++;
						if(mdl[0][dd]>=1){
							m1[dd].y=m1[dd].y+3;
							mdl[0][dd]=0;
						}
						if(mdl[1][dd]>=1){
							m2[dd].y=m2[dd].y+2;
							mdl[1][dd]=0;
						}		
					if(m1[dd].y>=72 && m1[dd].y<=768 && m1[dd].on==1){
						StretchBlt(DC1,m1[dd].x,m1[dd].y,41,75,btmDC,400+31*m1[dd].mv,0,31,60,SRCPAINT);
						StretchBlt(DC1,m1[dd].x,m1[dd].y,41,75,btmDC,31*m1[dd].mv,0,31,60,SRCAND);
					}else if(m1[dd].y>768 && m1[dd].on==1){
						m1[dd].on=0;
						chp=chp-50;
					}

					if(m2[dd].y>=72 && m2[dd].y<=768 && m2[dd].on==1){
						StretchBlt(DC1,m2[dd].x,m2[dd].y,41,75,btmDC,524+31*m2[dd].mv,0,31,60,SRCPAINT);
						StretchBlt(DC1,m2[dd].x,m2[dd].y,41,75,btmDC,124+31*m2[dd].mv,0,31,60,SRCAND);
					}else if(m2[dd].y>768 && m2[dd].on==1){
						m2[dd].on=0;
						chp=chp-50;
					}
					mvn[0][dd]++;
					mvn[1][dd]++;
					if(mvn[0][dd]>=1){
						if(m1[dd].mv<4)
							m1[dd].mv++;
						if(m1[dd].mv>=4)
							m1[dd].mv=0;
						mvn[0][dd]=0;
					}
					if(mvn[1][dd]>=2){
						if(m2[dd].mv<4)
							m2[dd].mv++;
						if(m2[dd].mv>=4)
							m2[dd].mv=0;
						mvn[1][dd]=0;
					}
				}

				for(cc=0;cc<4;cc++){//3,4번 적 움직임
					mdl[2][cc]++;
					mdl[3][cc]++;
					if(mdl[2][cc]>=2){
						m3[cc].y=m3[cc].y+3;
						mdl[2][cc]=0;
					}
					if(mdl[3][cc]>=2){
						m4[cc].y=m4[cc].y+5;
						mdl[3][cc]=0;
					}
					if(m3[cc].y>=72 && m3[cc].y<=768 && m3[cc].on==1){
						StretchBlt(DC1,m3[cc].x,m3[cc].y,123,75,btmDC,400+92*m3[cc].mv,60,92,59,SRCPAINT);
						StretchBlt(DC1,m3[cc].x,m3[cc].y,123,75,btmDC,92*m3[cc].mv,60,92,59,SRCAND);
					}else if(m3[cc].y>768&& m3[cc].on==1){
						m3[cc].on=0;
						chp=chp-150;
					}
					if(m4[cc].y>=-3 && m4[cc].y<=768 && m4[cc].on==1){
						StretchBlt(DC1,m4[cc].x,m4[cc].y,43,150,btmDC,400+31*m4[cc].mv,119,32,121,SRCPAINT);
						StretchBlt(DC1,m4[cc].x,m4[cc].y,43,150,btmDC,0+31*m4[cc].mv,119,32,121,SRCAND);
					}else if(m4[cc].y>768&& m4[cc].on==1){
						m4[cc].on=0;
						chp=chp-100;
					}
					mvn[2][cc]++;
					mvn[3][cc]++;
					if(mvn[2][cc]>=3){
						if(m3[cc].mv<4)
							m3[cc].mv++;
						if(m3[cc].mv>=4)
							m3[cc].mv=0;
						mvn[2][cc]=0;
					}
					if(mvn[3][cc]>=2){
						if(m4[cc].mv<4)
							m4[cc].mv++;
						if(m4[cc].mv>=4)
							m4[cc].mv=0;
						mvn[3][cc]=0;
					}
				}
				if(g1wn==8){ //적 타격 검사
					snd_play[8]->Play(0,0,NULL);
					for(gg=0;gg<8;gg++){
						if(m1[gg].on==1 && m1[gg].x+40>=g1wx-(10+dat.att*2) && m1[gg].x<=g1wx+(10+dat.att*2))
							if(m1[gg].y+75>=g1wy-(10+dat.att*2) && m1[gg].y<=g1wy+(10+dat.att*2)){
								m1[gg].hp-=(20+dat.att*2);
								m1[gg].y-=10;
							}
						if(m2[gg].on==1 && m2[gg].x+40>=g1wx-(10+dat.att*2) && m2[gg].x<=g1wx+(10+dat.att*2))
							if(m2[gg].y+75>=g1wy-(10+dat.att*2) && m2[gg].y<=g1wy+(10+dat.att*2)){
								m2[gg].y-=10;
								m2[gg].hp-=(20+dat.att*2);
							}
						if(gg<=4){
							if(m3[gg].on==1 && m3[gg].x+123>=g1wx-(10+dat.att*2) && m3[gg].x<=g1wx+(10+dat.att))
								if(m3[gg].y+75>=g1wy-(10+dat.att*2) && m3[gg].y<=g1wy+(10+dat.att*2)){
									m3[gg].hp-=(20+dat.att*2);
									m3[gg].y-=10;
								}
							if(m4[gg].on==1 && m4[gg].x+43>=g1wx-(10+dat.att*2) && m4[gg].x<=g1wx+(10+dat.att*2))
								if(m4[gg].y+150>=g1wy-(10+dat.att*2) && m4[gg].y+100<=g1wy+(10+dat.att*2)){
									m4[gg].hp-=(20+dat.att*2);
									m4[gg].y-=10;
								}
							}
					}
				}
				for(hh=0;hh<8;hh++){
					if(m1[hh].on==1 && m1[hh].hp<0) m1[hh].on=0;
					if(m2[hh].on==1 && m2[hh].hp<0) m2[hh].on=0;
					if(hh<=6){
						if(m3[hh].on==1 && m3[hh].hp<0) m3[hh].on=0;
						if(m4[hh].on==1 && m4[hh].hp<0) m4[hh].on=0;
					}
				}
				
				barl = 379*chp/tchp;
				if(barl>0) barl = 379*chp/tchp;
				else if(barl <=0) barl=0;
				StretchBlt(DC1,g1wx-1,0,2,768,btmDC,798,0,2,2,SRCCOPY);//타격x
				StretchBlt(DC1,0,g1wy-1,1024,2,btmDC,798,0,2,2,SRCCOPY);//타격y
				BitBlt(DC1,g1wx-60,g1wy-60,120,120,btmDC,528,119,SRCPAINT);//타격원
				BitBlt(DC1,g1wx-60,g1wy-60,120,120,btmDC,128,119,SRCAND);
				BitBlt(DC1,3,3,450,40,btmDC,0,339,SRCCOPY);//체력바
				BitBlt(DC1,71,6,barl,34,btmDC,400,261,SRCCOPY);//체력
				BitBlt(DC1,0,612,1024,156,btmDC,0,556,SRCPAINT);//성벽
				BitBlt(DC1,0,612,1024,156,btmDC,0,400,SRCAND);
				btm1=(HBITMAP)SelectObject(btmDC,btm_g1we);//무기
				BitBlt(DC1,g1wx-144,475,292,314,btmDC,292*g1wn,314,SRCPAINT);
				BitBlt(DC1,g1wx-144,475,292,314,btmDC,292*g1wn,0,SRCAND);
		
				if(exg1==0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_g1exp1); //설명1
					BitBlt(DC1,0,0,1024,768,btmDC,0,768,SRCPAINT);
					BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_g1exp2); //설명2
					BitBlt(DC1,g1wx,g1wy-75,369,75,btmDC,0,75,SRCPAINT);
					BitBlt(DC1,g1wx,g1wy-75,369,75,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_exx);//설명버튼
					BitBlt(DC1,8,56,153,37,btmDC,0,37*exxon,SRCCOPY);
				}



				SetBkMode(DC1,TRANSPARENT);
				font1=CreateFont(0,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,0,0,0,DEFAULT_PITCH|FF_ROMAN,"궁서체");
				wsprintf(prn_wrd,"%d",100-gstm);
				TextOut(DC1,90,13,prn_wrd,strlen(prn_wrd));
				if(chp<=0){
					ton=1;
					if(tshow>0){
						btm1=(HBITMAP)SelectObject(btmDC,btm_lose);
						BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
						if(first==0){
							dat.life--;
							first=1;
							papx=129;
						}
					}
				}else if(chp >0){
					if(gstm>=100){
						ton=1;
						if(tshow>0){
							btm1=(HBITMAP)SelectObject(btmDC,btm_win);
							BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
							if(first==0){
								dat.life++;
								dat.money+=dat.map*1000;
								dat.map++;
								first=1;
								papx=129;
							}
						}
					}
				}
				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);			
				
			}else if(sn==3){//잔당처리전
				snd_play[9]->Play(0,0,DSBPLAY_LOOPING);
				snd_play[3]->Stop();
				btm1=(HBITMAP)SelectObject(btmDC,btm_g2map);//배경
				BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCCOPY);
				btm1=(HBITMAP)SelectObject(btmDC,btm_g2re);//모닥불
				BitBlt(DC1,630,0,150,200,btmDC,768+150*g2f,768,SRCCOPY);

				for(aa=1;aa<=6;aa++){
					if(aa<=3){
						if(m1[aa].on==0){ // 좌창병 생성
							m1[aa].x=(rand()%500)-596;
							m1[aa].y=(rand()%664)+104;
							m1[aa].hp=100*dat.enemy/10;
							m1[aa].on=1;
							m1[aa].mv=rand()%4;
						}
						if(m2[aa].on==0 && dat.map >=3){ //좌활병 생성
							m2[aa].x=(rand()%500)-596;
							m2[aa].y=(rand()%664)+104;
							m2[aa].hp=100*dat.enemy/10;
							m2[aa].on=1;
							m2[aa].mv=rand()%4;
						}
					}else if(aa>3){ // 우창병 생성
						if(m1[aa].on==0 && dat.map >=3){
							m1[aa].x=(rand()%500)+1024;
							m1[aa].y=(rand()%664)+104;
							m1[aa].hp=100*dat.enemy/10;
							m1[aa].on=1;
							m1[aa].mv=rand()%4;
						}
						if(m2[aa].on==0){ //우활병 생성
							m2[aa].x=(rand()%500)+1024;
							m2[aa].y=(rand()%664)+104;
							m2[aa].hp=100*dat.enemy/10;
							m2[aa].on=1;
							m2[aa].mv=rand()%4;
						}
					}
				}
				for(cc=1;cc<=4;cc++){
					if(cc<=2){ //좌자객 생성
						if(m3[cc].on==0 && dat.map >=5){
							m3[cc].x=(rand()%500)-500;
							m3[cc].y=(rand()%664)+104;
							m3[cc].hp=250*dat.enemy/10;
							m3[cc].on=1;
							m3[cc].mv=rand()%4;
						}
					}else if(cc>2){
						if(m3[cc].on==0 && dat.map >=5){//우좌객 생성
							m3[cc].x=(rand()%500)+1024;
							m3[cc].y=(rand()%664)+104;
							m3[cc].hp=250*dat.enemy/10;
							m3[cc].on=1;
						}
					}
				}
				if(m4[0].on==0 && dat.map >=8){//적장군 생성
					if(g2k==0){
						m4[0].x=(rand()%500)-500;
						m4[0].y=(rand()%664)+104;
						m4[0].hp=200*dat.enemy/10;
						m4[0].on=1;
						m4[0].mv=rand()%4;
						g2k=1;
					}else if(g2k==1){
						m4[0].x=(rand()%500)+1024;
						m4[0].y=(rand()%664)+104;
						m4[0].hp=200*dat.enemy/10;
						m4[0].on=1;
						m4[0].mv=rand()%4;
						g2k=0;
					}
				}

				for(bb=1;bb<=6;bb++){
					if(m1[bb].on==1){ //창병 움직임	
						if(m1[bb].x>g2x+80){
							m1[bb].x-=6;
							g2m1d[bb]=0;
						}else if(m1[bb].x+80<g2x){
							m1[bb].x+=6;
							g2m1d[bb]=1;
						}

						if(m1[bb].y>g2y) m1[bb].y-=1;
						else if(m1[bb].y<g2y) m1[bb].y+=1;
						if(m1[bb].y>g2y) m1[bb].y-=1;
						else if(m1[bb].y<g2y) m1[bb].y+=1;
						if(m1[bb].y>g2y) m1[bb].y-=1;
						else if(m1[bb].y<g2y) m1[bb].y+=1;

						if(m1[bb].y==g2y){
							if(m1[bb].x<=g2x+80 && m1[bb].x > g2x+48) g2m1d[bb]=2; 
							else if(m1[bb].x+80 >= g2x && m1[bb].x+48 <=g2x) g2m1d[bb]=3;
						}else{
							if(m1[bb].x<=g2x+80 && m1[bb].x > g2x+48) g2m1d[bb]=0; 
							else if(m1[bb].x+80 >= g2x && m1[bb].x+48 <=g2x) g2m1d[bb]=1;
						}
						mdl[1][bb]++;
						if(mdl[1][bb]>2){
							m1[bb].mv++;
							mdl[1][bb]=0;
						}
						if(m1[bb].mv>3){
							m1[bb].mv=0;
						}
						BitBlt(DC1,m1[bb].x,m1[bb].y,96,96,btmDC,768+384+96*m1[bb].mv,96*g2m1d[bb],SRCPAINT);
						BitBlt(DC1,m1[bb].x,m1[bb].y,96,96,btmDC,768+96*m1[bb].mv,96*g2m1d[bb],SRCAND);
					}
					if(m2[bb].on==1){ //활병 움직임	
						if(m2[bb].x>g2x+200){
							m2[bb].x-=6;
							g2m2d[bb]=0;
						}else if(m2[bb].x+200<g2x){
							m2[bb].x+=6;
							g2m2d[bb]=1;
						}

						if(m2[bb].y>g2y) m2[bb].y-=1;
						else if(m2[bb].y<g2y) m2[bb].y+=1;
						if(m2[bb].y>g2y) m2[bb].y-=1;
						else if(m2[bb].y<g2y) m2[bb].y+=1;
						if(m2[bb].y>g2y) m2[bb].y-=1;
						else if(m2[bb].y<g2y) m2[bb].y+=1;
						if(m2[bb].y>g2y) m2[bb].y-=1;
						else if(m2[bb].y<g2y) m2[bb].y+=1;
						if(m2[bb].y==g2y){
							if(m2[bb].x<=g2x+200 && m2[bb].x > g2x+48) g2m2d[bb]=2; 
							else if(m2[bb].x+200 >= g2x && m2[bb].x+48 <=g2x) g2m2d[bb]=3;
						}else{
							if(m2[bb].x<=g2x+200 && m2[bb].x > g2x+48) g2m2d[bb]=0;
							if(m2[bb].x+200 >= g2x && m2[bb].x+48 <=g2x) g2m2d[bb]=1;
						}

						mdl[2][bb]++;
						if(mdl[2][bb]>2){
							m2[bb].mv++;
							mdl[2][bb]=0;
						}
						if(m2[bb].mv>3){
							m2[bb].mv=0;
						}
						BitBlt(DC1,m2[bb].x,m2[bb].y,96,96,btmDC,384+96*m2[bb].mv,384+96*g2m2d[bb],SRCPAINT);
						BitBlt(DC1,m2[bb].x,m2[bb].y,96,96,btmDC,96*m2[bb].mv,384+96*g2m2d[bb],SRCAND);
					}
				}

				for(dd=1;dd<=4;dd++){
					if(m3[dd].on==1){ //자객 움직임	
						if(m3[dd].x>g2x+70){
							m3[dd].x-=7;
							g2m3d[dd]=0;
						}else if(m3[dd].x+70<g2x){
							m3[dd].x+=7;
							g2m3d[dd]=1;
						}
						if(mdl[3][dd]>1){
							m3[dd].mv++;
							mdl[3][dd]=0;
						}
						if(m3[dd].mv>3){
							m3[dd].mv=0;
						}
						if(m3[dd].y>g2y) m3[dd].y-=1;
						else if(m3[dd].y<g2y) m3[dd].y+=1;
						if(m3[dd].y>g2y) m3[dd].y-=1;
						else if(m3[dd].y<g2y) m3[dd].y+=1;
						if(m3[dd].y>g2y) m3[dd].y-=1;
						else if(m3[dd].y<g2y) m3[dd].y+=1;
						if(m3[dd].y>g2y) m3[dd].y-=1;
						else if(m3[dd].y<g2y) m3[dd].y+=1;

						
						if(m3[dd].y==g2y){
							if(m3[dd].x<=g2x+70 && m3[dd].x > g2x+48) g2m3d[dd]=2; 
							else if(m3[dd].x+70 >= g2x && m3[dd].x+48 <=g2x) g2m3d[dd]=3;
						}else{
							if(m3[dd].x<=g2x+70 && m3[dd].x > g2x+48) g2m3d[dd]=0; 
							else if(m3[dd].x+70 >= g2x && m3[dd].x+48 <=g2x) g2m3d[dd]=1;
						}

						mdl[3][dd]++;
						BitBlt(DC1,m3[dd].x,m3[dd].y,96,96,btmDC,768+384+96*m3[dd].mv,384+96*g2m3d[dd],SRCPAINT);
						BitBlt(DC1,m3[dd].x,m3[dd].y,96,96,btmDC,768+96*m3[dd].mv,384+96*g2m3d[dd],SRCAND);
					}
				}

				if(m4[0].on==1){ //적장군 움직임	
					if(m4[0].x > g2x+100){
						m4[0].x-=8;
						g2m4d=0;
					}else if(m4[0].x+100 < g2x){
					m4[0].x+=8;
						g2m4d=1;
					}
					mdl[4][0]++;
					if(mdl[4][0]>1){
						m4[0].mv++;
						mdl[4][0]=0;
					}
					if(m4[0].mv>3){
						m4[0].mv=0;
					}
					if(m4[0].y>g2y) m4[0].y-=1;
					else if(m4[0].y<g2y) m4[0].y+=1;
					if(m4[0].y>g2y) m4[0].y-=1;
					else if(m4[0].y<g2y) m4[0].y+=1;
					if(m4[0].y>g2y) m4[0].y-=1;
					else if(m4[0].y<g2y) m4[0].y+=1;
					if(m4[0].y>g2y) m4[0].y-=1;
					else if(m4[0].y<g2y) m4[0].y+=1;
					if(m4[0].y>g2y) m4[0].y-=1;
					else if(m4[0].y<g2y) m4[0].y+=1;

					if(m4[0].y==g2y){
						if(m4[0].x<=g2x+100 && m4[0].x > g2x+48) g2m4d=2; 
						else if(m4[0].x+100 >= g2x && m4[0].x+48 <=g2x) g2m4d=3;
					}else{
						if(m4[0].x<=g2x+100 && m4[0].x > g2x+48) g2m4d=0; 
						else if(m4[0].x+10 >= g2x && m4[0].x+48 <=g2x) g2m4d=1;
					}
					BitBlt(DC1,m4[0].x,m4[0].y,96,96,btmDC,384+96*m4[0].mv,768+96*g2m4d,SRCPAINT);
					BitBlt(DC1,m4[0].x,m4[0].y,96,96,btmDC,96*m4[0].mv,768+96*g2m4d,SRCAND);
				}

				if(g2at==1)
					g2am++;
					
				for(hh=0;hh<=6;hh++){
					if(g2m==2 && g2at==1 && g2am==1 && g2ma==2){
						snd_play[10]->Play(0,0,NULL);
						if(m1[hh].on==1 && m1[hh].y+20 >= g2y && m1[hh].y <=g2y+20 && m1[hh].x >= g2x- 130*dat.att/10 && m1[hh].x <= g2x+ 96){ //좌창병 타격검사
							m1[hh].hp -= 80*dat.att/10+30;
							m1[hh].x -= 30;
							m1[hh].mv=0;
						}
						if(m2[hh].on==1 && m2[hh].y+20 >= g2y && m2[hh].y <=g2y+20 && m2[hh].x >= g2x- 130*dat.att/10 && m2[hh].x <= g2x+ 96){ //좌활병 타격검사
							m2[hh].hp -= 80*dat.att/10+30;
							m2[hh].x -= 30;
							m2[hh].mv=0;
						}
						if(m3[hh].on==1 && m3[hh].y+20 >= g2y && m3[hh].y <=g2y+20 && m3[hh].x >= g2x- 130*dat.att/10 && m3[hh].x <= g2x+ 96){ //좌자객 타격검사
							m3[hh].hp -= 80*dat.att/10+30;
							m3[hh].x -= 30;
							m3[hh].mv=0;
						}
						if(m4[hh].on==1 && m4[hh].y+20 >= g2y && m4[hh].y <=g2y+20 && m4[hh].x >= g2x- 130*dat.att/10 && m4[hh].x <= g2x+ 96){ //좌적장군 타격검사
							m4[hh].hp -= 80*dat.att/10+30;
							m4[hh].x -= 30;
							m4[hh].mv=0;
						}
					}

					if(g2m==3 && g2at==1 && g2am==1 && g2ma==2){
						if(m1[hh].on==1 && m1[hh].y+20 >= g2y && m1[hh].y <=g2y+20 && m1[hh].x > g2x && m1[hh].x <= g2x +130*dat.att/10){ //우창병 타격검사
							m1[hh].hp -= 80*dat.att/10+30;
							m1[hh].x += 30;
							m1[hh].mv=0;
						}
						if(m2[hh].on==1 && m2[hh].y+20 >= g2y && m2[hh].y <=g2y+20 && m2[hh].x >= g2x && m2[hh].x <= g2x +130*dat.att/10){ //우활병 타격검사
							m2[hh].hp -= 80*dat.att/10+30;
							m2[hh].x += 30;
							m2[hh].mv=0;
						}
						if(m3[hh].on==1 && m3[hh].y+20 >= g2y && m3[hh].y <=g2y+20 && m3[hh].x >= g2x && m3[hh].x <= g2x +130*dat.att/10){ //우자객 타격검사
							m3[hh].hp -= 80*dat.att/10+30;
							m3[hh].x += 30;
							m3[hh].mv=0;
						}
						if(m4[hh].on==1 && m4[hh].y+20 >= g2y && m4[hh].y <=g2y+20 && m4[hh].x >= g2x && m4[hh].x <= g2x +130*dat.att/10){ //우적장군 타격검사
							m4[hh].hp -= 80*dat.att/10+30;
							m4[hh].x += 30;
							m4[hh].mv=0;
						}
					}

					if(m1[hh].on==1 && m1[hh].hp <=0){
						m1[hh].on=0;
						if(chp<tchp) chp+=10;
						g2ck++;
					}
					if(m2[hh].on==1 && m2[hh].hp <=0){
						m2[hh].on=0;
						if(chp<tchp) chp+=10;
						g2ck++;
					}
					if(m3[hh].on==1 && m3[hh].hp <=0){
						m3[hh].on=0;
						if(chp<tchp) chp+=20;
						g2ck++;
					}
					if(m4[hh].on==1 && m4[hh].hp <=0){
						m4[hh].on=0;
						if(chp<tchp) chp+=30;
						g2ck++;
					}
				}

				for(gg=0;gg<=6;gg++){ //적의 공격 검사
					if(m1[gg].on==1 && m1[gg].mv==3 && mdl[1][gg]==1 && (g2m1d[gg]==2||g2m1d[gg]==3)) chp -=60;
					if(m2[gg].on==1 && m2[gg].mv==3 && mdl[2][gg]==1 && (g2m2d[gg]==2||g2m2d[gg]==3)) chp -=50;
					if(m3[gg].on==1 && m3[gg].mv==3 && mdl[3][gg]==1 && (g2m3d[gg]==3||g2m3d[gg]==3)) chp -=60;
					if(m4[gg].on==1 && m4[gg].mv==3 && mdl[4][gg]==1 && (g2m4d==3||g2m4d==3)) chp -=80;
				}

				BitBlt(DC1,g2x,g2y,96,96,btmDC,384+g2ma*96,96*g2m,SRCPAINT);//장군
				BitBlt(DC1,g2x,g2y,96,96,btmDC,g2ma*96,96*g2m,SRCAND);//장군
				barl = 379*chp/tchp;
				if(barl>0) barl = 379*chp/tchp;
				else if(barl <=0) barl=0;
				BitBlt(DC1,3,3,450,40,btmDC,768,968,SRCCOPY);//체력바
				BitBlt(DC1,71,6,barl,34,btmDC,768,1008,SRCCOPY);//체력
				SetBkMode(DC1,TRANSPARENT);

	
				if(exg2==0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_g2exp1);//설명1
					BitBlt(DC1,0,0,1024,245,btmDC,0,245,SRCPAINT);
					BitBlt(DC1,0,0,1024,245,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_g2exp2);//설명2
					BitBlt(DC1,g2x-5,g2y-10,464,113,btmDC,0,113,SRCPAINT);
					BitBlt(DC1,g2x-5,g2y-10,464,113,btmDC,0,0,SRCAND);
				
					btm1=(HBITMAP)SelectObject(btmDC,btm_exx);//설명버튼
					BitBlt(DC1,3,46,153,37,btmDC,0,37*exxon,SRCCOPY);
				}

				wsprintf(prn_wrd,"%d",g2ck);
				TextOut(DC1,90,13,prn_wrd,strlen(prn_wrd));

				if(chp<=0){
					ton=1;
					if(tshow>0){
						btm1=(HBITMAP)SelectObject(btmDC,btm_lose);
						BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
						if(first==0){
							dat.life--;
							first=1;
							papx=129;
						}
					}
				}else if(chp >0){
					if(g2ck>=100){
						ton=1;
						if(tshow>0){
							btm1=(HBITMAP)SelectObject(btmDC,btm_win);
							BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
							if(first==0){
								dat.life++;
								dat.map++;
								dat.money+=dat.map*1000;
								first=1;
								papx=129;
							}
						}
					}
				}


				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);
			}else if(sn==4){//해상전
				snd_play[11]->Play(0,0,DSBPLAY_LOOPING);
				snd_play[3]->Stop();
				btm1=(HBITMAP)SelectObject(btmDC,btm_g3map);
				BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCCOPY);//맵

				btm1=(HBITMAP)SelectObject(btmDC,btm_g3re);

				if(g3x<g3chax+30){
					if(g3chax>40){
						g3chax-=25;
						g3chaw=2;
					}else
						g3chaw=0;
				}else if(g3x > g3chax+140){
					if(g3chax<824){
						g3chax+=25;
						g3chaw=1;
					}else
						g3chaw=0;
				}else if(g3x >= g3chax+30 && g3x <= g3chax+140){
					g3chaw=0;
				}

				BitBlt(DC1,0,g3road,56,768,btmDC,560+56,0,SRCPAINT); //좌땅1
				BitBlt(DC1,0,g3road,56,768,btmDC,560,0,SRCAND);
				BitBlt(DC1,0,g3road-768,56,768,btmDC,560+56,0,SRCPAINT); //좌땅2
				BitBlt(DC1,0,g3road-768,56,768,btmDC,560,0,SRCAND);
				BitBlt(DC1,968,g3road2,56,768,btmDC,672+56,0,SRCPAINT); //우땅1
				BitBlt(DC1,968,g3road2,56,768,btmDC,672,0,SRCAND);
				BitBlt(DC1,968,g3road2-768,56,768,btmDC,672+56,0,SRCPAINT); //우땅2
				BitBlt(DC1,968,g3road2-768,56,768,btmDC,672,0,SRCAND);



				if(g3mt>=50){//적선 생성
					for(bb=0;bb<7;bb++){
						g3ln++;
						if(g3ln>50) g3ln=0;
						m[g3ln].on=1;
						m[g3ln].x=22+140*bb;
						m[g3ln].y=-200;
						if(dat.map>=11) mk[g3ln]=rand()%4;
						else if(dat.map< 11 && dat.map >=10) mk[g3ln]=rand()%3;
						else if(dat.map< 10) mk[g3ln]=rand()%2;
						m[g3ln].mv=0;
						if(mk[g3ln]==0)m[g3ln].hp=100*dat.enemy/10;
						else if(mk[g3ln]==1)m[g3ln].hp=1000000*dat.enemy/10;
						else if(mk[g3ln]==2)m[g3ln].hp=200*dat.enemy/10;
						else if(mk[g3ln]==3)m[g3ln].hp=300*dat.enemy/10;
					}
					g3mt=0;
				}
				
				for(cc=0;cc<50;cc++){//적선 움직임
					if(m[cc].y<=768){
						m[cc].y+=8;
					}else if(m[cc].y>768) m[cc].on=0;
					if(m[cc].on==1){	
						BitBlt(DC1,m[cc].x,m[cc].y,140,180,btmDC,140*mk[cc],180,SRCPAINT);
						BitBlt(DC1,m[cc].x,m[cc].y,140,180,btmDC,140*mk[cc],0,SRCAND);
					}
				}
				
				for(dd=0;dd<170;dd++){
					for(ee=0;ee<50;ee++){//폭발 모션 생성
						if(g3poc[dd]==0 && g3bon[dd]==1 && m[ee].on==1){
							if(g3bx[dd]>m[ee].x+20 && g3bx[dd]+12 < m[ee].x+120){
								if(g3by[dd] < m[ee].y+175 && g3by[dd]>m[ee].y){
									g3poc[dd]=1;
									g3pocx[dd]=g3bx[dd]-34;
									g3pocy[dd]=g3by[dd]-34;
									g3bon[dd]=0;
									m[ee].hp-=20+dat.att;
								}
							}
						}
						if(m[ee].on==1 && m[ee].hp<0) {
							m[ee].on=0;
							g3cnt++;
							if(g3gage<20) g3gage++;
							snd_play[11]->Play(0,0,NULL);
						}
					}
				}


				for(gg=0;gg<170;gg++){
					if(g3poc[gg]==1){ //폭발 움직임
						if(g3pocm[gg]<=4){
							BitBlt(DC1,g3pocx[gg],g3pocy[gg],80,80,btmDC,80*g3pocm[gg],649+80,SRCPAINT);
							BitBlt(DC1,g3pocx[gg],g3pocy[gg],80,80,btmDC,80*g3pocm[gg],649,SRCAND);
							g3pocmm[gg]++;
							if(g3pocmm[gg]>1){
								g3pocm[gg]++;
								g3pocmm[gg]=0;
							}
						}else if(g3pocm[gg]>4){
							g3pocm[gg]=0;
							g3poc[gg]=0;
						}
					}
				}

				for(aa=0;aa<30;aa++){ //총알움직임
					if(g3bon[aa]==0){
						if(g3bt>=3){
							g3bon[aa]=1;
							g3bx[aa]=g3chax+74;
							g3by[aa]=516;
							g3bt=0;
						}
					}
				}
				for(jj=0;jj<170;jj++){
					if(g3bon[jj]==1){
						if(g3by[jj] > -20){
							g3by[jj]-=16;
						}else{
							g3bon[jj]=0;
						}
						BitBlt(DC1,g3bx[jj],g3by[jj],12,12,btmDC,12,809,SRCPAINT);
						BitBlt(DC1,g3bx[jj],g3by[jj],12,12,btmDC,0,809,SRCAND);
					}
				}

				for(hh=0;hh<50;hh++){
					if(m[hh].on==1 && m[hh].x+120>=g3chax+30 && m[hh].x+30<=g3chax+130){//거북선타격
						if(m[hh].on==1 &&m[hh].y+170<546 && m[hh].y+170>486){
							chp-=200*dat.dif/10;
							m[hh].on=0;
							g3poc[31]=1;
							g3pocx[31]=g3chax+40;
							g3pocy[31]=486;
						}else if(m[hh].on==1 &&m[hh].y+170>546 && m[hh].y+170<656){//3,4번 배 밀어내기
							if(mk[hh]!=1){
								m[hh].on=0;
								if(m[hh].x+120<g3chax+80){
									g3poc[32]=1;
									g3pocx[32]=m[hh].x+80;
									g3pocy[32]=m[hh].y+50;
									if(g3gage<20) g3gage+=1;
								}else if(m[hh].x>=g3chax+80){
									g3poc[33]=1;
									g3pocx[33]=m[hh].x-20;
									g3pocy[33]=m[hh].y+50;
									if(g3gage<20) g3gage+=1;
								}
							}else if(mk[hh]==1){
								m[hh].on=0;
								chp-=200*dat.dif/10;
								if(m[hh].x+120<g3chax+80){
									g3poc[32]=1;
									g3pocx[32]=m[hh].x+80;
									g3pocy[32]=m[hh].y+50;
								}else if(m[hh].x>=g3chax+80){
									g3poc[33]=1;
									g3pocx[33]=m[hh].x-20;
									g3pocy[33]=m[hh].y+50;
								}
							}
						}
					}
				}

				btm1=(HBITMAP)SelectObject(btmDC,btm_g3cha);
				BitBlt(DC1,g3chax,486,160,180,btmDC,160*g3cham,540+g3chaw*180,SRCPAINT);//거북선
				BitBlt(DC1,g3chax,486,160,180,btmDC,160*g3cham,g3chaw*180,SRCAND);

				btm1=(HBITMAP)SelectObject(btmDC,btm_g3re);

				if(g3p==1){//필살
					if(g3page==0){
						if(g3py>=558) g3py-=4;
						else if(g3py<558) g3page=1;
					}else if(g3page==1){
						if(g3lnk>=3){
							g3pa++;
							for(ii=0;ii<7;ii++){
								if(g3bon[20+7*g3pa+ii]==0){
									g3bon[20+7*g3pa+ii]=1;
									g3bx[20+7*g3pa+ii]=22+70-6+140*ii;
									g3by[20+7*g3pa+ii]=588;
									g3lnk=0;
								}
							}
							if(g3pa>20) g3page=2;
						}
					}else if(g3page==2){
						if(g3py<768) g3py+=4;
						else if(g3py>=768) {
							g3p=0;
							g3gage=0;
						}
					}
					for(kk=0;kk<7;kk++){
						BitBlt(DC1,22+140*kk,g3py,140,180,btmDC,140,360,SRCPAINT);
						BitBlt(DC1,22+140*kk,g3py,140,180,btmDC,0,360,SRCAND);
					}
				}


				barl = 370*chp/tchp;
				if(barl>0) barl = 370*chp/tchp;
				else if(barl <=0) barl=0;
				barg = g3gage * 37/2;
				BitBlt(DC1,3,3,450,59,btmDC,0,540,SRCCOPY);//체력바
				BitBlt(DC1,80,6,barl,40,btmDC,0,599,SRCCOPY);//피통
				BitBlt(DC1,80,49,barg,10,btmDC,0,639,SRCCOPY);//게이지통

				if(exg3==0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_g3exp1);//설명 1
					BitBlt(DC1,0,0,1024,249,btmDC,0,249,SRCPAINT);
					BitBlt(DC1,0,0,1024,249,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_g3exp2);//설명 2
					BitBlt(DC1,g3chax-213,292,609,476,btmDC,0,476,SRCPAINT);
					BitBlt(DC1,g3chax-213,292,609,476,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_exx);//설명버튼
					BitBlt(DC1,45,256,153,37,btmDC,0,37*exxon,SRCCOPY);
				}

				SetBkMode(DC1,TRANSPARENT);
				wsprintf(prn_wrd,"%d초 내로 %d척 격파",100-g3tm,50-g3cnt);
				TextOut(DC1,90,13,prn_wrd,strlen(prn_wrd));

				if(chp<=0 || (g3tm>100 && g3cnt<50)){
					ton=1;
					if(tshow>0){
						btm1=(HBITMAP)SelectObject(btmDC,btm_lose);
						BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
						if(first==0){
							dat.life--;
							first=1;
							papx=129;
						}
					}
				}else if(chp >0 && g3cnt>50){
					if(g2ck>=100){
						ton=1;
						if(tshow>0){
							btm1=(HBITMAP)SelectObject(btmDC,btm_win);
							BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
							if(first==0){
								dat.life++;
								dat.money+=dat.map*1000;
								first=1;
								dat.map++;
								papx=129;
							}
						}
					}
				}

				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);

			}else if(sn==5){ // 공성전
				snd_play[13]->Play(0,0,DSBPLAY_LOOPING);
				snd_play[3]->Stop();
				if(g4mvy<670){
					if(g4mv<=150 && g4bga >= 15)
						g4bga-=15;
					else if(g4mv>=874 && g4bga <= 461)
						g4bga+=15;
				}
				g4bbg=-g4bga;
				while(g4bbg<-150)
					g4bbg+=150;
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4sun);
				BitBlt(DC1,0,0,1024,370,btmDC,0,0,SRCCOPY);//해
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4bg);//산
				BitBlt(DC1,0,179,1024,491,btmDC,g4bga,491,SRCPAINT);
				BitBlt(DC1,0,179,1024,491,btmDC,g4bga,0,SRCAND);
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4re);
				BitBlt(DC1,0,670,1024,98,btmDC,0,370,SRCCOPY);//조종바
				BitBlt(DC1,-g4bga,434,370,201,btmDC,0,865,SRCPAINT);//적성
				BitBlt(DC1,-g4bga,434,370,201,btmDC,0,664,SRCAND);
				BitBlt(DC1,-g4bga+968,409,552,226,btmDC,400,730,SRCPAINT);//성
				BitBlt(DC1,-g4bga+968,409,552,226,btmDC,400,504,SRCAND);
				BitBlt(DC1,230,679,80,80,btmDC,320,504,SRCPAINT);//아이콘들
				BitBlt(DC1,320,679,80,80,btmDC,320,504,SRCPAINT);
				BitBlt(DC1,410,679,80,80,btmDC,320,504,SRCPAINT);
				BitBlt(DC1,500,679,80,80,btmDC,320,504,SRCPAINT);
				
				if(g4c1==1){
					g4k=g4c1cnt*4/5;
					BitBlt(DC1,230,679,80,g4k,btmDC,0,584,SRCAND);
					BitBlt(DC1,230,679+g4k,80,80-g4k,btmDC,0,504+g4k,SRCAND);
				}else
					BitBlt(DC1,230,679,80,80,btmDC,0,504,SRCAND);
				if(g4c2==1){
					g4k=g4c2cnt*2/3;
					BitBlt(DC1,320,679,80,g4k,btmDC,80,584,SRCAND);
					BitBlt(DC1,320,679+g4k,80,80-g4k,btmDC,80,504+g4k,SRCAND);
				}else
					BitBlt(DC1,320,679,80,80,btmDC,80,504,SRCAND);
				if(g4c3==1){
					g4k=g4c3cnt*2/5;
					BitBlt(DC1,410,679,80,g4k,btmDC,160,584,SRCAND);
					BitBlt(DC1,410,679+g4k,80,80-g4k,btmDC,160,504+g4k,SRCAND);
				}else
					BitBlt(DC1,410,679,80,80,btmDC,160,504,SRCAND);
				if(g4c4==1){
					g4k=g4c4cnt*4/15;
					BitBlt(DC1,500,679,80,g4k,btmDC,240,584,SRCAND);
					BitBlt(DC1,500,679+g4k,80,80-g4k,btmDC,240,504+g4k,SRCAND);
				}else
					BitBlt(DC1,500,679,80,80,btmDC,240,504,SRCAND);
				for(aa=0;aa<8;aa++){
					BitBlt(DC1,g4bbg+150*aa,615,150,55,btmDC,400,1011,SRCPAINT);//잔디
					BitBlt(DC1,g4bbg+150*aa,615,150,55,btmDC,400,956,SRCAND);
				}

				if(g4c1==1){
					g4c1cnt--;
					if(g4c1cnt<=0)
						g4c1=0;
				}
				if(g4c2==1){
					g4c2cnt--;
					if(g4c2cnt<=0)
						g4c2=0;
				}
				if(g4c3==1){
					g4c3cnt--;
					if(g4c3cnt<=0)
						g4c3=0;
				}
				if(g4c4==1){
					g4c4cnt--;
					if(g4c4cnt<=0)
						g4c4=0;
				}

				if(g4e1==1){
					g4e1cnt--;
					if(g4e1cnt<=0) g4e1=0;
				}
				if(g4e2==1){
					g4e2cnt--;
					if(g4e2cnt<=0) g4e2=0;
				}
				if(g4e3==1){
					g4e3cnt--;
					if(g4e3cnt<=0) g4e3=0;
				}
				if(g4e4==1){
					g4e4cnt--;
					if(g4e4cnt<=0) g4e4=0;
				}
				if(g4e1==0){
					g4e1=1;		
					do{
					g4en++;
					}while(g4eon[g4en]==1);
					if(g4en>100) g4en=0;
					g4eon[g4en]=1;
					g4ex[g4en]=0;
					g4et[g4en]=1;
					g4ehp[g4en]=15*(dat.enemy+g4s);
					g4e1cnt=130;
					g4emv[g4en]=0;
					g4emvv[g4en]=0;
				}
				if(g4e2==0){
					g4e2=1;
					do{
					g4en++;
					}while(g4eon[g4en]==1);
					if(g4en>100) g4en=0;
					g4eon[g4en]=1;
					g4ex[g4en]=0;
					g4et[g4en]=2;
					g4ehp[g4en]=8*(dat.enemy+g4s);
					g4e2cnt=150;
					g4em[g4en]=0;
					g4emv[g4en]=0;
					g4emvv[g4en]=0;
				}
				if(g4e3==0){
					g4e3=1;
					do{
					g4en++;
					}while(g4eon[g4en]==1);
					if(g4en>100) g4en=0;
					g4eon[g4en]=1;
					g4ex[g4en]=0;
					g4et[g4en]=3;
					g4ehp[g4en]=40*(dat.enemy+g4s);
					g4e3cnt=200;
					g4em[g4en]=0;
					g4emv[g4en]=0;
					g4emvv[g4en]=0;
				}
				if(g4e4==0){
					g4e4=1;
					do{
					g4en++;
					}while(g4eon[g4en]==1);
					if(g4en>100) g4en=0;
					g4eon[g4en]=1;
					g4ex[g4en]=0;
					g4et[g4en]=4;
					g4ehp[g4en]=40*(dat.enemy+g4s);
					g4e4cnt=250;
					g4em[g4en]=0;
					g4emv[g4en]=0;
					g4emvv[g4en]=0;
				}
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4cha);
				for(aa=0;aa<100;aa++){
					if(g4con[aa]==1){//아군 활창병
						if(g4ct[aa]==1 || g4ct[aa]==2){
							BitBlt(DC1,g4cx[aa]-g4bga,539,94,94,btmDC,(g4ct[aa]-1)*384+96*g4cmv[aa]+1,192+g4cm[aa]*96+1,SRCPAINT);
							BitBlt(DC1,g4cx[aa]-g4bga,539,94,94,btmDC,(g4ct[aa]-1)*384+96*g4cmv[aa]+1,g4cm[aa]*96+1,SRCAND);
						}
					}
					if(g4eon[aa]==1){
						if(g4et[aa]==1){//칼병
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,384+96*g4emv[aa]+1,768+g4em[aa]*96+1,SRCPAINT);
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,96*g4emv[aa]+1,768+g4em[aa]*96+1,SRCAND);
						}
						if(g4et[aa]==2){//총병
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,384+96*g4emv[aa]+1,576+g4em[aa]*96+1,SRCPAINT);
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,384+96*g4emv[aa]+1,384+g4em[aa]*96+1,SRCAND);
						}
						if(g4et[aa]==3){//적군 권총병
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,96*g4emv[aa]+g4em[aa]*384+1,1056+1,SRCPAINT);
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,96*g4emv[aa]+g4em[aa]*384+1,960+1,SRCAND);
						}
						if(g4et[aa]==4){//적군 장검병
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,96*g4emv[aa]+1,576+g4em[aa]*96+1,SRCPAINT);
							BitBlt(DC1,g4ex[aa]-g4bga,539,94,94,btmDC,96*g4emv[aa]+1,384+g4em[aa]*96+1,SRCAND);
						}
					}
				}
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4re);
				BitBlt(DC1,-g4bga+1350,409,140,226,btmDC,140,0,SRCPAINT);//성우측
				BitBlt(DC1,-g4bga+1350,409,140,226,btmDC,0,0,SRCAND);
				btm1=(HBITMAP)SelectObject(btmDC,btm_g4cha);
				for(bb=0;bb<100;bb++){
					if(g4con[bb]==1){//아군 신기전
						if(g4ct[bb]==3){
						BitBlt(DC1,g4cx[bb]-g4bga,499,126,154,btmDC,1280+128*g4cmv[bb]+1,624+g4cm[bb]*156+1,SRCPAINT);
						BitBlt(DC1,g4cx[bb]-g4bga,499,126,154,btmDC,768+128*g4cmv[bb]+1,624+g4cm[bb]*156+1,SRCAND);
						}
					}
				}
				for(cc=0;cc<100;cc++){
					if(g4con[cc]==1){
						if(g4ct[cc]==4){// 아군 천자총통
							BitBlt(DC1,g4cx[cc]-g4bga,510,126,154,btmDC,768+128*g4cmv[cc]+1,312+g4cm[cc]*156+1,SRCPAINT);
							BitBlt(DC1,g4cx[cc]-g4bga,510,126,154,btmDC,768+128*g4cmv[cc]+1,g4cm[cc]*156+1,SRCAND);
						}
						g4cmvv[cc]++;
						if(((g4ct[cc]==1 || g4ct[cc]==2) && g4cmvv[cc]>=3)||(g4ct[cc]==3 && g4cmvv[cc]>=4)||(g4ct[cc]==4 && g4cmvv[cc]>=5)){
							g4cmvv[cc]=0;
							g4cmv[cc]++;
						}
						if(g4ct[cc]==4 && g4cm[cc]==1){
							if(g4cmv[cc] >7)
								g4cmv[cc]=0;
						}else if(g4cmv[cc]>3)
							g4cmv[cc]=0;
					}
					if(g4eon[cc]==1){
						g4emvv[cc]++;
						if(((g4et[cc]==1 || g4et[cc]==2) && g4emvv[cc]>=3)||(g4et[cc]==3 && g4emvv[cc]>=3)||(g4et[cc]==4 && g4emvv[cc]>=4)){
							g4emvv[cc]=0;
							g4emv[cc]++;
						}
						if(g4et[cc]==3 && g4em[cc]==1){
							if(g4emv[cc] >7)
								g4emv[cc]=5;
						}else if(g4emv[cc]>3)
							g4emv[cc]=0;
					}
					g4ctch[cc]=0;
					g4etch[cc]=0;
				}
				for(dd=0;dd<100;dd++){
					for(ee=0;ee<100;ee++){
						if(g4con[dd]==1){
							if(g4ct[dd]==1){
								if((g4eon[ee]==1 && g4ex[ee] >= g4cx[dd] - 80 || 100 >= g4cx[dd] - 80)){
									g4ctch[dd]=1;
									g4cm[dd]=1;
									if(g4cmv[dd]==3 && g4cmvv[dd]==1 && g4ex[ee] >= g4cx[dd] - 80)
										g4ehp[ee] -=2*dat.att;
									if(g4cmv[dd]==3 && g4cmvv[dd]==1 && 100 >= g4cx[dd] - 80 && ee==10)
										g4ec-=2*dat.att;
								}
							}else if(g4ct[dd]==2){
								if((g4eon[ee]==1 && g4ex[ee] >= g4cx[dd] - 300 || 100 >= g4cx[dd] - 300) ){
									g4ctch[dd]=1;
									g4cm[dd]=1;
									if(g4cmv[dd]==3 && g4cmvv[dd]==1 && g4ex[ee] >= g4cx[dd] - 300)
										g4ehp[ee] -=15*dat.att/10;
									else if(g4cmv[dd]==3 && g4cmvv[dd]==1 && 100 >= g4cx[dd] - 300 && ee==10)
										g4ec -= 15*dat.att/10;
								}
							}else if(g4ct[dd]==3){
								if((g4eon[ee]==1 &&g4ex[ee] >= g4cx[dd] - 300 || 100 >= g4cx[dd] - 300) ){
									g4ctch[dd]=1;
									g4cm[dd]=1;
									if(g4cmv[dd]==3 && g4cmvv[dd]==1 && g4ex[ee] >= g4cx[dd] - 300)
										g4ehp[ee] -=2*dat.att;
									if(g4cmv[dd]==3 && g4cmvv[dd]==1 && 100 >= g4cx[dd] - 300&& ee==10)
										g4ec-=2*dat.att;
								}
							}else if(g4ct[dd]==4){
								if((g4eon[ee]==1 && g4ex[ee] >= g4cx[dd] - 200 || 100 >= g4cx[dd] - 200) ){
									g4ctch[dd]=1;
									g4cm[dd]=1;
									if(g4cmv[dd]==6 && g4cmvv[dd]==1 && g4ex[ee] >= g4cx[dd] - 200)
										g4ehp[ee] -=25*dat.att/10;
									if(g4cmv[dd]==6 && g4cmvv[dd]==1 && 100 >= g4cx[dd] - 200&& ee==10)
										g4ec-=25*dat.att/10;
								}
							}
						}
						if(g4eon[dd]==1){
							if(g4et[dd]==1){
								if((g4con[ee]==1 && g4cx[ee] <= g4ex[dd] +60) || g4ex[dd] +60 >= 1280){
									g4etch[dd]=1;
									g4em[dd]=1;
									if(g4emv[dd]==3 && g4emvv[dd]==1)
										g4chp[ee] -=2*(dat.enemy+g4s);
									if(g4emv[dd]==3 && g4emvv[dd]==1 && g4ex[dd] +60 >= 1280 && ee==10)
										chp-=2*(dat.enemy+g4s);
								}
							}else if(g4et[dd]==2){
								if(g4con[ee]==1 && g4cx[ee] <= g4ex[dd] + 300 || g4ex[dd] +300 >= 1280){
									g4etch[dd]=1;
									g4em[dd]=1;
									if(g4emv[dd]==3 && g4emvv[dd]==1)
										g4chp[ee] -=15*(dat.enemy+g4s)/10;
									if(g4emv[dd]==3 && g4emvv[dd]==1 && g4ex[dd] +300 >= 1280 && ee==10)
										chp-=15*(dat.enemy+g4s)/10;
								}
							}else if(g4et[dd]==3){
								if(g4con[ee]==1 && g4cx[ee] <= g4ex[dd] + 200 || g4ex[dd] +200 >= 1280){
									g4etch[dd]=1;
									g4em[dd]=1;
									if(g4emv[dd]==6 && g4emvv[dd]==1)
										g4chp[ee] -=15*(dat.enemy+g4s)/10;
									if(g4emv[dd]==3 && g4emvv[dd]==1 && g4ex[dd] +200 >= 1280 && ee==10)
										chp-=15*(dat.enemy+g4s)/10;
								}
							}else if(g4et[dd]==4){
								if(g4con[ee]==1 && g4cx[ee] <= g4ex[dd] + 95 || g4ex[dd] +95 >= 1280){
									g4etch[dd]=1;
									g4em[dd]=1;
									if(g4emv[dd]==3 && g4emvv[dd]==1)
										g4chp[ee] -=4*(dat.enemy+g4s);
									if(g4emv[dd]==3 && g4emvv[dd]==1 && g4ex[dd] +95 >= 1280 && ee==10)
										chp-=4*(dat.enemy+g4s);
								}
							}
						}
					}
					if(g4con[dd]==1 && g4ctch[dd]==0){
						if(g4ct[dd]==1){
							g4cx[dd]-=3;
							g4cm[dd]=0;
						}
						if(g4ct[dd]==2){
							g4cx[dd]-=3;
							g4cm[dd]=0;
						}
						if(g4ct[dd]==3){
							g4cx[dd]-=2;
							g4cm[dd]=0;
						}
						if(g4ct[dd]==4){
							g4cx[dd]-=1;
							g4cm[dd]=0;
						}
					}
					if(g4eon[dd]==1 && g4etch[dd]==0){
						if(g4et[dd]==1){
							g4ex[dd]+=3;
							g4em[dd]=0;
						}
						if(g4et[dd]==2){
							g4ex[dd]+=3;
							g4em[dd]=0;
						}
						if(g4et[dd]==3){
							g4ex[dd]+=4;
							g4em[dd]=0;
						}
						if(g4et[dd]==4){
							g4ex[dd]+=2;
							g4em[dd]=0;
						}
					}
				}

				for(ff=0;ff<100;ff++){
					if(g4chp[ff]<0) g4con[ff]=0;
					if(g4ehp[ff]<0) g4eon[ff]=0;
				}

				btm1=(HBITMAP)SelectObject(btmDC,btm_g4re);
				if(g4gage<g4gg-2){
					g4gage+=2;
				}else if(g4gage>g4gg-2){
					g4gage=1000;
				}
				barl = 336*chp/tchp;
				if(barl>0) barl = 336*chp/tchp;
				else if(barl <=0) barl=0;
				
				if(g4ec>0) ebar = 180*g4ec/g4e;
				else if(g4ec<=0) ebar=0;
				barg = g4gage*336/g4gg;
				BitBlt(DC1,666,679,barl,36,btmDC,0,468,SRCCOPY);//hp바
				BitBlt(DC1,666,725,barg,36,btmDC,336,468,SRCCOPY);//mp바
				BitBlt(DC1,39,702,ebar,20,btmDC,672,468,SRCCOPY);//적hp바

				if(exg4==0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_g4exp);//설명
					BitBlt(DC1,0,0,1024,768,btmDC,0,768,SRCPAINT);
					BitBlt(DC1,0,0,1024,768,btmDC,0,0,SRCAND);

					btm1=(HBITMAP)SelectObject(btmDC,btm_exx);//설명버튼
					BitBlt(DC1,15,0,153,37,btmDC,0,37*exxon,SRCCOPY);
				}

				if(chp<=0){
					ton=1;
					if(tshow>0){
						btm1=(HBITMAP)SelectObject(btmDC,btm_lose);
						BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
						if(first==0){
							dat.life--;
							first=1;
							papx=129;
						}
					}
				}else if(g4ec<=0){
					ton=1;
					if(tshow>0){
					btm1=(HBITMAP)SelectObject(btmDC,btm_win);
						BitBlt(DC1,212,234,600,300,btmDC,0,0,SRCCOPY);
						if(first==0){
							dat.life++;
							dat.money+=dat.map*1000;
							first=1;
							dat.map++;
							papx=129;
						}
					}
				}

				SelectObject(btmDC,btm1);
				DeleteDC(btmDC);
			}
			
			if(snm!=2) BitBlt(DC,0,0,1024,768,DC1,0,0,SRCCOPY);
			SelectObject(DC1,mbtm2);
			DeleteObject(mbtm1);
			DeleteDC(DC1);
			EndPaint(hWnd,&PS1);
			return 0;
		
		case WM_MOUSEMOVE:
			hdc=GetDC(hWnd);
			MoveToEx(hdc,x,y,NULL);
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			if(sn==0){
				if(difon==0){
					if(buth==437){
						if(x >=652 && x <=902){ //시작버튼 움직임
							if(y >=474 && y <=554){
								butn = 1;
							}else if(y >=573 && y <=653){
								butn = 2;
							}else{
								butn = 0;
							}
						}else{
								butn = 0;
						}
					}
				}else if(difon==1){
					if(x >=670 && x <=695){
						if(y >=262 && y <=287){ 
							difx=1;
						 }else
							 difx=0;
					}else
						difx=0;
						if(y >= 341 && y <= 471){ //난이도버튼 움직임
							if(x >= 332 && x<= 432){
								dif=1;
							}else if(x>=462 && x<= 562){
								dif=2;
							}else if(x>=593 && x<= 693){
								dif=3;
							}else
								dif=0;
					}
				}else if(difon==2){
					if(pwords==1){ // 책자 버튼
						if(x >= 750 && x <= 870){
							if(y >= 480 && y <= 602){
								aa=1;
							}else aa=0;
						}else aa= 0;
					}
				}
			}else if(sn==1){
				if(x >= 950 && x <= 1010){
					if(y >= 15 && y <= 55){	 // 지도 버튼
						mapix=1;
					}else mapix=0;
				}else mapix=0;
				if(ext==0){
					if(x >= 6 && x <= 159){
						if( y >= 81 && y <= 118){
							exxon=1;
						}else exxon=0;
					}else exxon=0;
				}
				if(maptype==1){
					if(mapbut==1){
						if(x >= 750 && x <= 870){
							if(y >= 480 && y <= 602){
								dd=1;
							}else dd=0;
						}else dd=0;
						if(flmo==1){
							if(x >= 525 && x <= 553 && y >= 508 && y<= 536){
								flsize[0]=35;
								flsize[7]=28;
								flsize[5]=28;
								chanum=6;
								minfo=1;
								wsprintf(warnam,"정암진 전투");
								wsprintf(wor,"곽재우 통솔 의병대");
								wnum=2;
								wsprintf(warex[1],"아군의 첫 승전");
								wsprintf(warex[2],"왜군의 전라도 진격을 저지");
							}else if(x >= 484 && x <= 484 +28 && y >= 456 && y<= 456 +28){
								flsize[1]=35;
								chanum=5;
								minfo=1;
								wsprintf(warnam,"웅치, 이치 전투");
								wsprintf(wor,"권율 통솔 관군");
								wnum=3;
								wsprintf(warex[1],"전주성 접근을 저지");
								wsprintf(warex[2],"한산도 대첩과 이 전투로");
								wsprintf(warex[3]," 인해 전투 상황이 역전");
							}else if(x >= 546 && x <= 546 +28 && y >= 544 && y<= 544 +28){
								flsize[2]=35;
								flsize[7]=28;
								chanum=1;
								minfo=1;
								wsprintf(warnam,"한산도 대첩");
								wsprintf(wor,"이순신 통솔 관군");
								wnum=3;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"학익진을 선보이며 대승을 거둠");
								wsprintf(warex[3],"이 전투로 남해의 재해권 장악");
							}else if(x >= 588 && x <= 588 +28 && y >= 456 && y<= 456 +28){
								flsize[3]=35;
								chanum=3;
								minfo=1;
								wsprintf(warnam,"영천성 전투");
								wsprintf(wor,"의병대");
								wnum=2;
								wsprintf(warex[1],"왜군 수급을 얻어 큰 수확을 거둠");
								wsprintf(warex[2],"왜군은 상주로 퇴각");
							}else if(x >= 479 && x <= 479 +28 && y >= 412 && y<= 412 +28){
								flsize[4]=35;
								chanum=3;
								minfo=1;
								wsprintf(warnam,"청주성 전투");
								wsprintf(wor,"의병대");
								wnum=2;
								wsprintf(warex[1],"곡식을 모두 태워 적의 재점거를");
								wsprintf(warex[2]," 불가능하게 함");
							}else if(x >= 525 && x <= 525 +28 && y >= 477 && y<= 477 +28){
								flsize[5]=35;
								flsize[0]=28;
								chanum=2;
								minfo=1;
								wsprintf(warnam,"거창 사랑암 조우전");
								wsprintf(wor,"김시민 통솔 관군");
								wnum=2;
								wsprintf(warex[1],"왜군의 전라도 진출을 다시한번");
								wsprintf(warex[2]," 저지");
							}else if(x >= 387 && x <= 387 +28 && y >= 296 && y<= 296 +28){
								flsize[6]=35;
								chanum=7;
								minfo=1;
								wsprintf(warnam,"연안 대첩");
								wsprintf(wor,"이정암 통솔 의병대");
								wnum=2;
								wsprintf(warex[1],"수적 열세가 컸으나 대승을 거둠");
								wsprintf(warex[2],"후퇴하는 왜군을 쳐 큰 수확을 거둠");
							}else if(x >= 520 && x <= 520 +28 && y >= 529 && y<= 529 +28){
								flsize[7]=35;
								flsize[0]=28;
								flsize[11]=28;
								flsize[2]=28;
								chanum=2;
								minfo=1;
								wsprintf(warnam,"진주 대첩");
								wsprintf(wor,"김시민, 곽재우 통솔 의병대");
								wnum=3;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"이마에 탄환을 맞고 김시민 전사");
								wsprintf(warex[3],"왜군의 병력에 엄청난 손실을 입힘");
							}else if(x >= 387 && x <= 387 +28 && y >= 240 && y<= 240 +28){
								flsize[8]=35;
								chanum=4;
								minfo=1;
								wsprintf(warnam,"평양성 전투");
								wsprintf(wor,"유성룡, 이여송 통솔 조명 연합군");
								wnum=2;
								wsprintf(warex[1],"조명 연합군의 첫 전투");
								wsprintf(warex[2],"왜군이 수세에 몰리는 결정적인 계기");
							}else if(x >= 446 && x <= 446 +28 && y >= 324 && y<= 324 +28){
								flsize[9]=35;
								chanum=5;
								minfo=1;
								wsprintf(warnam,"행주 대첩");
								wsprintf(wor,"권율 통솔 관군");
								wnum=6;
								wsprintf(warex[1],"임진왜란 3대대첩");
								wsprintf(warex[2],"사기가 최고인 3만 왜군을");
								wsprintf(warex[3]," 적은수로 물리침");
								wsprintf(warex[4],"이 전투에서 이기기 위해 여자들이");
								wsprintf(warex[5]," 긴 치마를 잘라 돌을 욺겼는데");
								wsprintf(warex[6]," 그래서 행주치마란 명칭이 생김");
							}else if(x >= 415 && x <= 415 +28 && y >= 570 && y<= 570 +28){
								flsize[10]=35;
								chanum=1;
								minfo=1;
								wsprintf(warnam,"명량 해전");
								wsprintf(wor,"이순신 통솔 관군");
								wnum=3;
								wsprintf(warex[1],"13척의 배로 133척의 왜군 배를 수장");
								wsprintf(warex[2],"이 싸움으로 조선의");
								wsprintf(warex[3]," 해상권을 다시 회복");
							}else if(x >= 500 && x <= 500 +28 && y >= 557 && y<= 557 +28){
								flsize[11]=35;
								flsize[7]=28;
								chanum=1;
								minfo=1;
								wsprintf(warnam,"노량 해전");
								wsprintf(wor,"이순신 통솔 관군");
								wnum=3;
								wsprintf(warex[1],"임진왜란의 마지막 전투");
								wsprintf(warex[2],"퇴각하는 쫒아 큰 피해를 입힘");
								wsprintf(warex[3],"이순신 장군이 이 전투에서 사망");
							}else{
								for(cc=0;cc<12;cc++)
									flsize[cc]=28;
								minfo=0;
								wsprintf(warnam,"");
								wsprintf(wor,"");
								for(aa=1;aa<7;aa++)
									wsprintf(warex[aa],"");
							}
						}
					}
				}else if(maptype==2){
					if(mapbut==1){
						if(x >= 475 && x <= 595){
							if(y >= 225 && y <= 347){
								dd=1;
							}else dd=0;
						}else dd=0;
						if(x >= 475 && x <= 595){
							if(y >= 360 && y <= 482){
								ee=1;
							}else ee=0;
						}else ee=0;
					}
				}else if(maptype==3){
					if(mapbut==1){
						if(x >= 610 && x <= 730){
							if(y >= 475 && y <= 597){
								dd=1;
							}else dd=0;
						}else dd=0;
						if(x >= 760 && x <= 880){
							if(y >= 475 && y <= 597){
								ee=1;
							}else ee=0;
						}else ee=0;
					}
				}else if(maptype==4){
					if(mapbut==1){
						if(y >= 245 && y <= 306){
							if(x >= 333 && x <= 393){
								dd=1;
							}else dd=0;
							if(x >= 784 && x <= 844){
								ee=1;
							}else ee=0;
						}else{
							ee=0;
							dd=0;
						}
						if(x >= 452 && x <= 572){
							if(y >= 456 && y <= 578){
								ff=1;
							}else ff=0;
						}else ff=0;
					}
				}else if(maptype==5){
					if(mapbut==1){
						if(x>=350 && x <= 410){
							if(y>=248 && y <= 309){
								dd=1;
							}else dd=0;
							if(y>=435 && y <= 496){
								ee=1;
							}else ee=0;
						}else{
							ee=0;
							dd=0;
						}
						if(x >= 728 && x<=948){
							if(y>= 442 && y <= 564){
								ff=1;
							}else ff=0;
						}else ff=0;
					}
				}else if(maptype==6){
					if(mapbut==1){
						if(y>=416 && y <= 477){
							if(x>=408 && x <= 468){
								dd=1;
							}else dd=0;
							if(x>=836 && x <= 896){
								ee=1;
							}else ee=0;
						}else{
							ee=0;
							dd=0;
						}
						if(x >= 428 && x<= 548){
							if(y>= 494 && y <= 616){
								ff=1;
							}else ff=0;
						}else ff=0;
					}
				}else if(maptype==7){
					if(mapbut==1){
						if(y>=223 && y <= 343){
							if(x>=615 && x <= 735){
								ff=1;
							}else ff=0;
						}else{
							ff=0;
						}
					}
				}
			}else if(sn==2){
				g1wx=x;
				g1wy=y;
				if(exg1==0){
					if(x >= 3 && x <= 3+153){
						if( y >= 46 && y <= 46+37){
							exxon=1;
						}else exxon=0;
					}else exxon=0;
				}
			}else if(sn==3){
				if(exg2==0){
					if(x >= 8 && x <= 8+153){
						if( y >= 56 && y <= 56+37){
							exxon=1;
						}else exxon=0;
					}else exxon=0;
				}
			}else if(sn==4){
				if(exg3==0){
					if(x >= 45 && x <= 45+153){
						if( y >= 256 && y <= 256+37){
							exxon=1;
						}else exxon=0;
					}else exxon=0;
				}
				g3x=x;
			}else if(sn==5){
				g4mv=x;
				g4mvy=y;
				if(exg4==0){
					if(x >= 15 && x <= 15+153){
						if( y >= 0 && y <= 37){
							exxon=1;
						}else exxon=0;
					}else exxon=0;
				}
			}

			return 0;
		case WM_LBUTTONDOWN:
			if(sn==0){
				if(difon==0){
					if(buth==437){
						if(x >=652 && x <=902){
							if(y >=474 && y <=554){ //시작버튼 클릭
								difon=1;
								butn = 0;
							}else if(y >=573 && y <=653){
								butn = 2;
							}else{
								butn = 0;
							}
						}else{
							butn = 0;
						}
						if(x >= 652 && x<=902){
							if(y >= 573 && y<=653){//게임불러오기
								if((input=fopen("data.out","r"))==NULL){
									petcnt=1;
									petk=2;
								}else{
									fscanf(input,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&dat.att,&dat.dif,&dat.enemy,&dat.farmer,&dat.food,&dat.life,&dat.map,&dat.money,&dat.pop,&dat.umoney,&dat.upop,&dat.utime);
									petcnt=1;
									petk=1;
									fclose(input);
								}
							}
						}
					}
				}else if(difon==1){
					if(y >=262 && y <=287){
						if(x >=670 && x <=695){
							butn=0;
							difon=0;
						 }
					}else if(y >= 341 && y <= 471){ //난이도창 클릭
						if(x >= 332 && x<= 432){
							dat.map=0;
							dat.umoney=0;
							dat.money=500;
							dat.pop=10;
							dat.upop=0;
							dat.utime=0;
							dat.life=3;
							dat.att=10;
							dat.dif=10;
							dat.enemy=8;
							dat.food=10;
							dat.farmer=5;
							dif=1;
							difon=2;
						}else if(x>=462 && x<= 562){
							dat.map=0;
							dat.umoney=0;
							dat.money=400;
							dat.pop=10;
							dat.upop=0;
							dat.utime=0;
							dat.life=3;
							dat.att=10;
							dat.dif=10;
							dat.enemy=10;
							dat.food=9;
							dat.farmer=4;
							dif=2;
							difon=2;
						}else if(x>=593 && x<= 693){
							dat.map=0;
							dat.umoney=0;
							dat.money=300;
							dat.pop=10;
							dat.upop=0;
							dat.utime=0;
							dat.life=3;
							dat.att=10;
							dat.dif=10;
							dat.enemy=12;
							dat.food=8;
							dat.farmer=3;
							dif=3;
							difon=2;
						}
					}
				}else if(difon==2){
					if(pwords==1){ // 책자 버튼
						if(x >= 750 && x <= 870){
							if(y >= 480 && y <= 602){
								snm=1;
							}
						}
					}
				}
			}else if(sn==1){
				if(ext==0){
					if(x >= 6 && x <= 159){
						if( y >= 81 && y <= 118){
							ext=1;
						}
					}
				}

				if(x >= 950 && x <= 1010){
					if(y >= 15 && y <= 55){	 // 지도 버튼
						mapon=1;
						maptype=1;
					}
				}
				if(maptype==1){
					if(mapbut==1){
						if(x >= 750 && x <= 870){
							if(y >= 480 && y <= 602){
								mapon=0;
								mapbut=0;
								maptype=0;
								papx=128;
							}
						}
					}
				}else if(maptype==2){
					if(mapbut==1){ //게임진행
						if(x >= 475 && x <= 595){
							if(y >= 225 && y <= 347 && dat.pop >= 10+2*dat.map){
								maptype=0;
								mapbut=0;
								dat.pop-=10+2*dat.map;
								if(gk==2){
									sn=2;
									tchp=1000*dat.dif/10;
									chp=1000*dat.dif/10;
									ton=0;
									tshow=0;
									gstm=0;
								}
								if(gk==3){
									sn=3;
									tchp=1000*dat.dif/10;
									chp=1000*dat.dif/10;
									g2x=(1024-96)/2;
									g2y=(768-96)/2;
									for(aa=0;aa<20;aa++){
										m1[aa].on=0;
										m2[aa].on=0;
										m3[aa].on=0;
										m4[aa].on=0;
									}
									g2k=0;
									g2ck=0;
									ton=0;
									tshow=0;
								}
								if(gk==4){
									sn=4;
									g3road= 0;
									g3road2= 384;
									g3chax= 432;
									g3bt=0;
									tchp=1000*dat.dif/10;
									chp=1000*dat.dif/10;
									for(aa=0;aa<170;aa++){
										g3bx[aa]=0;
										g3by[aa]=0;
										g3bon[aa]=0;
									}
									for(bb=0;bb<170;bb++){
										g3pocm[bb]=0;
										g3pocmm[bb]=0;
										g3poc[bb]=0;
									}
									g3gg=0;
									g3mt=0;
									g3ln=0;
									g3py=768;
									g3pa=0;
									ton=0;
									tshow=0;
									g3cnt=0;
									g3tm=0;
									g3tmm=0;
								}
								if(gk==5){
									sn=5;
									g4bga=0;
									for(aa=0;aa<100;aa++){
										g4cn=0;
										g4con[aa]=0;
										g4cx[aa]=0;
										g4ct[aa]=0;
										g4cmv[aa]=0;
									}
									g4c1=0;
									g4c2=0;
									g4c3=0;
									g4c4=0;
									g4gage=1000*dat.dif/10;
									g4gg=g4gage;
									tchp=1000*dat.dif/10;
									chp=1000*dat.dif/10;
									g4en=0;
									g4e1=0;
									g4e2=1;
									g4e3=1;
									g4e4=1;
									g4e1cnt=0;
									g4e2cnt=10;
									g4e3cnt=80;
									g4e4cnt=100;
									g4s+=1;
									g4ec=1000*(dat.enemy + g4s);
									g4e=g4ec;
									for(bb=0;bb<100;bb++){
										g4con[bb]=0;
										g4eon[bb]=0;
										g4cmv[bb]=0;
										g4cmvv[bb]=0;
										g4emv[bb]=0;
										g4emvv[bb]=0;
									}
								}
							}else if(y >= 225 && y <= 347 && dat.pop <= 10+2*dat.map){
								petcnt=1;
							}
						}
						if(x >= 475 && x <= 595){
							if(y >= 360 && y <= 482){
								mapon=0;
								mapbut=0;
								chay+=30;
								maptype=0;
								papx=128;
							}
						}
					}
				}else if(maptype==3){
					if(mapbut==1){ //게임저장
						if(x >= 610 && x <= 730){
							if(y >= 475 && y <= 597){
								input=fopen("data.out","w");
								fprintf(input,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",dat.att,dat.dif,dat.enemy,dat.farmer,dat.food,dat.life,dat.map,dat.money,dat.pop,dat.umoney,dat.upop,dat.utime);
								fclose(input);
								petcnt=1;
								petk=0;
							} 
						}
						if(x >= 760 && x <= 880){
							if(y >= 475 && y <= 597){
								mapon=0;
								mapbut=0;
								maptype=0;
								chay+=30;
								papx=128;
							}
						}
					}
				}else if(maptype==4){
					if(mapbut==1){
						if(y >= 245 && y <= 306){
							if(x >= 333 && x <= 393){
								if(dat.money >= 300){
									dat.food ++;
									dat.money -= 300;
									dat.umoney += 300;
									snd_play[4]->Play(0,0,NULL);
								}else{
									petcnt=1;
									mout=1;
								}
							}
							if(x >= 784 && x <= 844){
								if(dat.food >= 1){
									dat.food --;
									dat.money += 200;
									snd_play[4]->Play(0,0,NULL);
								}else{
									petcnt=1;
									cout=1;
								}
							}
						}
						if(x >= 452 && x <= 572){
							if(y >= 456 && y <= 578){
								mapon=0;
								mapbut=0;
								chax-=30;	
								maptype=0;
								papx=128;
							}
						}
					}
				}else if(maptype==5){
					if(mapbut==1){
						if(x>=350 && x <= 410){
							if(y>=248 && y <= 309){
								if(dat.pop>=1){
									dat.pop --;
									dat.farmer ++;
								}else{
									petcnt=1;
									pout=1;
								}
							}else if(y>=435 && y <= 496){
								if(dat.food>=2){
									dat.food-=2;
									dat.pop++;
								}else{
									petcnt=1;
									cout=1;
								}
							}
						}else if(x >= 728 && x<=948){
							if(y>= 442 && y <= 573){
								mapon=0;
								mapbut=0;
								chax+=30;
								maptype=0;
								papx=128;
							}
						}	
					}
				}else if(maptype==6){
					if(mapbut==1){
						if(y>= 416 && y <= 477){ //업그레이드
							if(x>= 408 && x <= 468){
								if(dat.money>=(dat.att-9)*(dat.att-9)*100 && (dat.att-10)/2<8){
									dat.money-=(dat.att-9)*(dat.att-9)*100;
									dat.umoney+=(dat.att-9)*(dat.att-9)*100;
									dat.att+=2;
									snd_play[5]->Play(0,0,NULL);
								}else{
									petcnt=1;
								}
							}
							if(x>= 836 && x <= 896){
								if(dat.money>=(dat.dif-9)*(dat.dif-9)*100 && (dat.dif-10)/2<8){
									dat.money-=(dat.dif-9)*(dat.dif-9)*100;
									dat.umoney+=(dat.dif-9)*(dat.dif-9)*100;
									dat.dif+=2;
									snd_play[5]->Play(0,0,NULL);
								}else{
									petcnt=1;
								}
							}
						}
						if(x >= 428 && x<= 548){
							if(y>= 494 && y <= 616){
								mapon=0;
								mapbut=0;
								chax-=30;	
								maptype=0;
								papx=128;
							}
						}
					}
				}else if(maptype==7){
					if(mapbut==1){
						if(y>=223 && y <= 343){
							if(x>=615 && x <= 735){
								PostQuitMessage(0);
								mapon=0;
								mapbut=0;
								maptype=0;
								papx=128;
							}

						}
					}
				}
				if(x>=0 && x <=50){
					if(y>=0 && y <= 50){
						dat.map++;
					}
				}
			}else if(sn==2){
				if(g1won==0)
					g1won=1;
				if(exg1==0){
					if(x >= 3 && x <= 3+153){
						if( y >= 46 && y <= 46+37){
							exg1=1;
						}
					}
				}
			}else if(sn==3){
				if(exg2==0){
					if(x >= 8 && x <= 8+153){
						if( y >= 56 && y <= 56+37){
							exg2=1;
						}
					}
				}
			}else if(sn==4){
				if(exg3==0){
					if(x >= 45 && x <= 45+153){
						if( y >= 256 && y <= 256+37){
							exg3=1;
						}
					}
				}

			}else if(sn==5){
				if(y>=679 && y<= 759){
					if(x>=230 && x<= 310 &&g4c1==0&& g4gage>=100){
						if(g4c1==0)
							g4gage-=100;
						snd_play[14]->Play(0,0,NULL);
						g4c1=1;
						g4c1cnt=100;
						do{
						g4cn++;
						}while(g4con[g4cn]==1);
						if(g4cn>99)
							g4cn=0;
						g4con[g4cn]=1;
						g4ct[g4cn]=1;
						g4cmv[g4cn]=0;
						g4chp[g4cn]=15*dat.dif;
						g4cx[g4cn]=1450;
					}
					if(x>=320 && x<= 400 && g4c2==0&& g4gage>=120){
						if(g4c2==0)
							g4gage-=120;
						snd_play[14]->Play(0,0,NULL);
						g4c2=1;
						g4c2cnt=120;
						do{
						g4cn++;
						}while(g4con[g4cn]==1);
						if(g4cn>99)
							g4cn=0;
						g4con[g4cn]=1;
						g4ct[g4cn]=2;
						g4cmv[g4cn]=0;
						g4chp[g4cn]=8*dat.dif;
						g4cx[g4cn]=1450;
					}
					if(x>=410 && x<= 490 && g4c3==0 && g4gage>=200){
						if(g4c3==0)
							g4gage-=200;
						snd_play[14]->Play(0,0,NULL);
						g4c3=1;
						g4c3cnt=200;
						do{
						g4cn++;
						}while(g4con[g4cn]==1);
						if(g4cn>99)
							g4cn=0;
						g4con[g4cn]=1;
						g4ct[g4cn]=3;
						g4cmv[g4cn]=0;
						g4chp[g4cn]=20*dat.dif;
						g4cx[g4cn]=1500;
					}
					if(x>=500 && x<= 580 && g4c4==0&& g4gage>=300){
						if(g4c4==0)
							g4gage-=300;
						snd_play[14]->Play(0,0,NULL);
						g4c4=1;
						g4c4cnt=300;
						do{
						g4cn++;
						}while(g4con[g4cn]==1);
						if(g4cn>99)
							g4cn=0;
						g4con[g4cn]=1;
						g4ct[g4cn]=4;
						g4cmv[g4cn]=0;
						g4chp[g4cn]=40*dat.dif;
						g4cx[g4cn]=1500;
					}
				}
				if(exg4==0){
					if(x >= 15 && x <= 15+153){
						if( y >= 0 && y <= 37){
							exg4=1;
						}
					}
				}
			}
			return 0;
		case WM_RBUTTONDOWN:
			if(sn==4){
				if(g3gage==20 && g3p==0){
					g3p=1;
					g3page=0;
					g3py=768;
					g3pa=0;
				}
			}
			return 0;
        case WM_DESTROY:
				DeleteObject(btm_bg);
                PostQuitMessage(0);
                return 0;

        }
        return(DefWindowProc(hWnd,iMsg,wParam,lParam));
}

void key_dwn(int dkey)
{
	if(sn==1){ // 마을 장군 움직임
		if(maptype==0){
			if(GetKeyState(VK_DOWN) & 0x8000){
				snd_play[6]->Play(0,0,NULL);
				if((chax >=405 && chay<=768-96) || (chax < 405 && chay<=475-96)){
					chad=0;
					chay+=6;
					cham++;
					if(GetKeyState(VK_LEFT) & 0x8000){
						if((chay<=349-96 && chax > 405)||(chay>349-96 && chay <=468-96 && chax >= 0)||(chay>475-96 && chax>405)){
							chad=1;
							chax-=6;
						}
					}else if(GetKeyState(VK_RIGHT) & 0x8000){
						if(chax<624-96){
							chad=2;
							chax+=6;
						}
					}
				}
			}else if(GetKeyState(VK_UP) & 0x8000){
				snd_play[6]->Play(0,0,NULL);
				if((chax >=405 && chay>=156-96) || (chax < 405&& chay>=359-96)){
					chad=3;
					chay-=6;
					cham++;
					if(GetKeyState(VK_LEFT) & 0x8000){
						if((chay<=349-96 && chax > 405)||(chay>349-96 && chay <=468-96 && chax >= 0)||(chay>475-96 && chax>405)){
							chax-=6;
						}
					}else if(GetKeyState(VK_RIGHT) & 0x8000){
						if(chax<624-96){
							chax+=6;
						}
					}
				}
			}else if(GetKeyState(VK_LEFT) & 0x8000){
				snd_play[6]->Play(0,0,NULL);
				if((chay<=349-96 && chax >= 405)||(chay>349-96 && chay <=468-96 && chax >= 0)||(chay>475-96 && chax>=405)){
					chad=1;
					chax-=6;
					cham++;
				}
			}else if(GetKeyState(VK_RIGHT) & 0x8000){
				snd_play[6]->Play(0,0,NULL);
				if(chax<=624-96){
					chad=2;
					chax+=6;
					cham++;
				}
			}else{
				cham=0;
				chac=0;
			}
			
			if(cham>=2){
				cham=0;
				chac++;
			}
			if(chac>3){
				chac=0;
			}
		}
	}else if(sn==3){ //게임3 장군 움직임
		 if(GetKeyState(VK_LEFT) & 0x8000){
			 if(g2x>0){
				g2x-=10;
				g2m=0;
				g2am++;
				g2at=0;
			 }
			 if(GetKeyState(VK_UP) & 0x8000){
				if(g2y>104){
					g2y-=6;
				}
			 }else if(GetKeyState(VK_DOWN) & 0x8000){
				if(g2y<768-96){
					g2y+=6;
				}
			}
		}else if(GetKeyState(VK_RIGHT) & 0x8000){
			 if(g2x<1024-96){
				g2x+=10;
				g2m=1;
				g2am++;
				g2at=0;
			 }
			if(GetKeyState(VK_UP) & 0x8000){
				if(g2y>104){
					g2y-=6;
				}
			 }else if(GetKeyState(VK_DOWN) & 0x8000){
				if(g2y<768-96){
					g2y+=6;
				}
			}
		}else if(GetKeyState(VK_UP) & 0x8000){
			if(g2y>104){
				g2y-=6;
				g2am++;
				g2at=0;
			}
		}else if(GetKeyState(VK_DOWN) & 0x8000){
			if(g2y<768-96){
				g2y+=6;
				g2am++;
				g2at=0;
			}
		}else if(GetKeyState(VK_SPACE) & 0x8000){
			if(g2m==0) g2m=2;
			else if(g2m==1) g2m=3;
			g2at=1;
		}else if(g2at!=1){
			g2am=0;
			g2ma=0;
		}
		if(g2am>1){
			g2ma++;
			g2am=0;
		}
		if(g2ma>3){
			g2ma=0;
			g2at=0;
		}
	}
}

int dsloadwave(int sndnum, char *FileName) // 소리
{
	WAVEFORMATEX waveformat;
	DSBUFFERDESC bufferdesc;

	HMMIO hWAV;
	MMCKINFO Parent, Child;

	UCHAR *WholeSndBuff, *PrimaryBuff=NULL, *SecondaryBuff=NULL; 
	DWORD PrimaryLength=0, SecondaryLength=0;

	Parent.ckid=(FOURCC)0;
	Parent.cksize=0;
	Parent.fccType=(FOURCC)0;
	Parent.dwDataOffset=0;
	Parent.dwFlags=0;
	Child=Parent;

	hWAV=mmioOpen(FileName, NULL, MMIO_READ | MMIO_ALLOCBUF);

	if(!hWAV) return 0;
	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if(mmioDescend(hWAV, &Parent, NULL, MMIO_FINDRIFF))
	{
		mmioClose(hWAV, 0);
		return 0;
	}

	Child.ckid=mmioFOURCC('f', 'm', 't', ' ');

	if(mmioDescend(hWAV, &Child, &Parent, 0))
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	if(mmioRead(hWAV,(char *)&waveformat,sizeof(waveformat))!=sizeof(waveformat))
	{
		mmioClose(hWAV, 0);
		return 0;
	}

	if(waveformat.wFormatTag!=WAVE_FORMAT_PCM)
	{
		mmioClose(hWAV, 0);
		return 0; 
	}

	if( mmioAscend(hWAV, &Child, 0) )
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	Child.ckid=mmioFOURCC('d', 'a', 't', 'a');

	if(mmioDescend(hWAV, &Child, &Parent, MMIO_FINDCHUNK))
	{
		mmioClose(hWAV, 0);
		return 0;  
	}

	WholeSndBuff = new UCHAR[Child.cksize];
	mmioRead(hWAV, (char *)WholeSndBuff, Child.cksize);
	mmioClose(hWAV, 0);

	memset(&waveformat, 0, sizeof(WAVEFORMATEX)); 
	waveformat.wFormatTag = WAVE_FORMAT_PCM; 
	waveformat.nChannels = 2; 
	waveformat.nSamplesPerSec = 44100; 
	waveformat.wBitsPerSample = 16; 
	waveformat.nBlockAlign = (waveformat.nChannels*waveformat.wBitsPerSample)/8; 
	waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec * waveformat.nBlockAlign;
	waveformat.cbSize = 0;

	memset(&bufferdesc, 0, sizeof(DSBUFFERDESC)); 
	bufferdesc.dwSize = sizeof(DSBUFFERDESC); 
	bufferdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | 
	DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_STICKYFOCUS | DSBCAPS_GETCURRENTPOSITION2; 
	bufferdesc.dwBufferBytes = Child.cksize; 
	bufferdesc.lpwfxFormat = &waveformat; 

	if (FAILED(ds->CreateSoundBuffer(&bufferdesc, &snd_play[sndnum], NULL))) 
	{ 
		delete[] WholeSndBuff;
		return 0;
	}

	snd_play[sndnum]->Lock(0, Child.cksize, (LPVOID*)&PrimaryBuff, &PrimaryLength, (LPVOID*)&SecondaryBuff, &SecondaryLength, DSBLOCK_FROMWRITECURSOR);
	memcpy(PrimaryBuff, WholeSndBuff, PrimaryLength);
	memcpy(SecondaryBuff, (WholeSndBuff+PrimaryLength), SecondaryLength);
	snd_play[sndnum]->Unlock(PrimaryBuff, PrimaryLength, SecondaryBuff, SecondaryLength);
	delete[] WholeSndBuff;

	return 1;
}