
extern "C"{
#include <ugui.h>
}

#include <iostream>
using namespace std;

#include <TApplication.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TColor.h>


#define WIN_WIDTH  1024
#define WIN_HEIGHT 600

void DrawPixel(UG_S16 x, UG_S16 y, UG_COLOR c)
{
	Int_t r = (c>>16) & 0xFF;
	Int_t g = (c>>8 ) & 0xFF;;
	Int_t b = (c>>0 ) & 0xFF;

	Float_t fx = (Float_t)x/(Float_t)WIN_WIDTH;
	Float_t fy = ((Float_t)WIN_HEIGHT - (Float_t)y)/(Float_t)WIN_HEIGHT;
	TLine *lin = new TLine(fx, fy, fx+1.0/(Float_t)WIN_WIDTH, fy);
	lin->SetLineColor( TColor::GetColor(r, g, b) );
	lin->SetLineWidth(1);
	lin->Draw();
}

void WindowCallback(UG_MESSAGE *mess)
{
	
}

int main(int narg, char *argv[])
{

	// This creates a minimal ROOT application that opens a window
	// so the DrawPixel routine can draw in it.
	TApplication *app = new TApplication("TApplication", &narg, argv);
	TCanvas *c1 = new TCanvas("c1", "", WIN_WIDTH, WIN_HEIGHT);
	c1->Draw();

	// Use uGui to draw an interface
	UG_GUI g;
	UG_Init( &g, DrawPixel, WIN_WIDTH, WIN_HEIGHT );
	UG_SelectGUI( &g );
	UG_FontSelect( &FONT_12X20 );
	UG_SetForecolor(C_OLIVE);
	UG_SetBackcolor(C_WHITE);

	UG_PutString( 20, 50, (char*)"Hello There");
	
	#define MAX_OBJS 64
	UG_WINDOW wnd;
	UG_OBJECT objs[MAX_OBJS];
	UG_WindowCreate( &wnd, objs, MAX_OBJS, WindowCallback );
	UG_WindowResize( &wnd, 200, 100, 800, 500);
	UG_WindowShow(&wnd);


	UG_BUTTON btn;
	UG_ButtonCreate(&wnd, &btn, BTN_ID_0, 20, 50, 140, 90 );
	UG_ButtonSetFont(&wnd, BTN_ID_0, &FONT_10X16);
	UG_ButtonSetText(&wnd, BTN_ID_0, (char*)"Push Me");
	UG_ButtonShow(&wnd, BTN_ID_0);

	UG_CHECKBOX cbx;
	UG_CheckboxCreate(&wnd, &cbx, CHB_ID_0, 20, 100, 140, 150 );
	UG_CheckboxSetFont(&wnd, CHB_ID_0, &FONT_10X16);
	UG_CheckboxSetText(&wnd, CHB_ID_0, (char*)"Check Me");
	UG_CheckboxSetCheched(&wnd, CHB_ID_0, CHB_STATE_PRESSED);
	UG_CheckboxShow(&wnd, CHB_ID_0);


	UG_Update();
	
	
	app->Run();

	return 0;
}



