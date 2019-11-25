#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 4"

int question = 0;
float angleRotate = 0.0f;
float rotate_xaxis = 0.0f;
float rotate_yaxis = 0.0f;
float rotate_zaxis = 0.0f;

void drawPyramid() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(angleRotate, rotate_xaxis, rotate_yaxis, rotate_zaxis);
	
	glBegin(GL_LINE_LOOP);
	// Bottom (ABCD)
	glVertex3f(-1.0f / 5, 0.0f / 5, 0.0f / 5); // A
	glVertex3f(0.0f / 5, -1.0f / 5, 0.0f / 5); // B
	glVertex3f(1.0f / 5, 0.0f / 5, 0.0f / 5); // C
	glVertex3f(0.0f / 5, 1.0f / 5, 0.0f / 5); //D

	// Front (ABE)
	glVertex3f(-1.0f / 5, 0.0f / 5, 0.0f / 5); // A
	glVertex3f(0.0f / 5, -1.0f / 5, 0.0f / 5); // B
	glVertex3f(0.0f / 5, 0.0f / 5, 2.0f / 5); // E

	// Front Right (BCE)
	glVertex3f(0.0f / 5, -1.0f / 5, 0.0f / 5); // B
	glVertex3f(1.0f / 5, 0.0f / 5, 0.0f / 5); // C
	glVertex3f(0.0f / 5, 0.0f / 5, 2.0f / 5); // E

	// Back Front (CDE)
	glVertex3f(1.0f / 5, 0.0f / 5, 0.0f / 5); // C
	glVertex3f(0.0f / 5, 1.0f / 5, 0.0f / 5); //D
	glVertex3f(0.0f / 5, 0.0f / 5, 2.0f / 5); // E

	// Front Left (DAE)
	glVertex3f(0.0f / 5, 1.0f / 5, 0.0f / 5); //D
	glVertex3f(-1.0f / 5, 0.0f / 5, 0.0f / 5); // A
	glVertex3f(0.0f / 5, 0.0f / 5, 2.0f / 5); // E

	glEnd();
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			break;
		}
		if (wParam == 0x31) {
			// Press key 1 -> display question 1
			question = 1;
			angleRotate = 0.0f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 0.0f;
			break;
		}
		if (wParam == 0x58) {
			// Press key X -> Rotate anticlockwise x-axis
			angleRotate = -0.01f;
			rotate_xaxis = 1.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 0.0f;
			break;
		}

		if (wParam == 0x59) {
			// Press key Y -> Rotate anticlockwise x-axis
			angleRotate = -0.01f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 1.0f;
			rotate_zaxis = 0.0f;
			break;
		}
		if (wParam == 0x5A) {
			// Press key Z -> Rotate anticlockwise x-axis
			angleRotate = -0.01f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 1.0f;
			break;
		}
		if (wParam == VK_SPACE) {
			// Space key press -> reset object to White and locate at centre
			glLoadIdentity();
			angleRotate = 0.0f;
			break;
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (question)
	{
	case 1:
		drawPyramid();
		break;
	default:
		break;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------