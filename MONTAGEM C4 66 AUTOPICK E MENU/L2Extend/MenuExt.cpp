#include "MenuExt.h"

#define ID_NEWMENU_OPTIONS 2025



bool CALLBACK MenuExt::HandleCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM Lparam)
{
	switch(message)
	{
	case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case ID_NEWMENU_OPTIONS:
					MessageBox(hWnd, "Menu item clicked","Debug",NULL);
					return TRUE;
			}
	}
	return DefWindowProc(hWnd,message,wParam,Lparam);
}


bool MenuExt::ShoWindowHook(HWND hWnd, int nCmdShow)
{
	HMENU hOriginalMenu = GetMenu(hWnd);
	HMENU hExtMenu = CreateMenu();
	AppendMenu(hExtMenu,0,ID_NEWMENU_OPTIONS,"Options");
	
	InsertMenu(hOriginalMenu,-1,MF_BYPOSITION|MF_POPUP,(UINT_PTR)hExtMenu,"L2BRASILIA");
	return ShowWindow(hWnd,nCmdShow);
}
void MenuExt::Install(){
	WriteInstruction(0x63FB68,(INT32)MenuExt::HandleCommand,1,0xE8);
	WriteInstruction(0x64438E,(INT32)MenuExt::ShoWindowHook,1,0xE8);
}