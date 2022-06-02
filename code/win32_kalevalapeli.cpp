/*------------------------------------------------------------------------------
Oskari Perikangas
oskari.perikangas@gmail.com
 ------------------------------------------------------------------------------*/
#include <windows.h>

#define localPersist static;
#define globalVariable static;
#define internal static;

// TODO: Change these globals to not-globals
globalVariable bool running;
globalVariable BITMAPINFO BitmapInfo;
globalVariable void *BitmapMemory;
globalVariable HBITMAP BitmapHandle;
globalVariable HDC BitmapDeviceContext;

internal void win32ResizeDIBSection(int width, int height)
{
	// TODO: Maybe don't free first
	if(BitmapHandle)
	{
		DeleteObject(BitmapHandle);
	}
	if(!BitmapDeviceContext)
	{
		BitmapDeviceContext = CreateCompatibleDC(0);
	}
	
	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = width;
	BitmapInfo.bmiHeader.biHeight = height;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	BitmapHandle = CreateDIBSection(
		BitmapDeviceContext,
		&BitmapInfo,
		DIB_RGB_COLORS,
		&BitmapMemory,
		0, 0);
}

internal void win32UpdateWindow(HDC DeviceContext, int x, int y, int width, int height)
{
	StretchDIBits(DeviceContext,
				  x, y, width, height, // This is the target DIB
				  x, y, width, height, // This is the source DIB
				  BitmapMemory,
				  &BitmapInfo,
				  DIB_RGB_COLORS,
				  SRCCOPY);

}

LRESULT win32MainWindowCallback(
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
			RECT clientRect;
			GetClientRect(window, &clientRect);
			int width = clientRect.right - clientRect.left;
			int height = clientRect.bottom - clientRect.top;
			win32ResizeDIBSection(width, height);
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
			int width  = Paint.rcPaint.right - Paint.rcPaint.left ;
			int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			win32UpdateWindow(DeviceContext, x, y, width, height);
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
	WindowClass.lpfnWndProc = win32MainWindowCallback;
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


