/*------------------------------------------------------------------------------
Oskari Perikangas
oskari.perikangas@gmail.com
 ------------------------------------------------------------------------------*/
#include <windows.h>

#define localPersist static;
#define globalVariable static;
#define internal static;

// TODO: Change this later to not global.
globalVariable bool running;

internal void ResizeDIBSection()
{
}

LRESULT  MainWindowCallback(
						   HWND window,
						   UINT message ,
						   WPARAM wParam,
						   LPARAM lParam)

{
	LRESULT result = 0;
	
	switch(message)
	{
	    case WM_SIZE :
		{
			OutputDebugString("WM_SIZE\n");
		}break;

	    case WM_DESTROY:
		{
			//TODO: update flag.
			running = false;
		} break;

	    case WM_CLOSE:
		{
			//TODO: update flag.
			running = false;
		}break;

	    case WM_ACTIVATEAPP:
		{
			OutputDebugString("WM_ACTIVATEAPP\n");
		}break;

		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext =  BeginPaint(window, &Paint);
			int x      = Paint.rcPaint.left;
			int y      = Paint.rcPaint.top;
			int width  = Paint.rcPaint.right;
			int height = Paint.rcPaint.bottom;
			localPersist DWORD Operation = WHITENESS;
			PatBlt(DeviceContext, x, y, width, height, Operation);
			if (Operation == WHITENESS)
			{
				Operation = BLACKNESS;
			}
			else
			{
				Operation = WHITENESS;
			}
			EndPaint(window, &Paint);
		}break;
		
		default:
		{
			OutputDebugString("WM_DEFAULT\n");
			result = DefWindowProc(window, message, wParam, lParam);
		}break;
	}
	
	return result;
}

int WINAPI
wWinMain(HINSTANCE  hInstance,
		 HINSTANCE  hPrevInstance,
	     PWSTR      pCmdLine,
 		 int        nCmdShow)
{ 
    WNDCLASS WindowClass = {};

	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = hInstance;
//	WindowClass.hIcon;
	WindowClass.lpszClassName = "KalevalapeliWindowClass";

	if(RegisterClass(&WindowClass))
	{
		HWND WindowHandle =  CreateWindowEx(
			   0,
			   WindowClass.lpszClassName,
			   "Kalevala peli",
			   WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			   CW_USEDEFAULT,
			   CW_USEDEFAULT,
			   CW_USEDEFAULT,
			   CW_USEDEFAULT,
			   0,
			   0,
			   hInstance,
			   0);
		
		if(WindowHandle)
		{
			running = true;
			while (running)
			{
				MSG Message;
				BOOL MessageResult = GetMessage(&Message,0,0,0);
				if (MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}	
	   	}
		else
		{
			// TODO: Error logging
		}
	}
	else
	{
        // TODO: Error logging
	}
	
  return 0;
  
}


