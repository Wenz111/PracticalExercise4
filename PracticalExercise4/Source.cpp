#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 4"

int question = 0;
int arm_move_up_down = 0;
int arm_rotate_left_right = 0;

float angleRotate = 0.0f;
float rotate_xaxis = 0.0f;
float rotate_yaxis = 0.0f;
float rotate_zaxis = 0.0f;

float arm_move_xaxis = 0.0f;
float arm_move_yaxis = 0.0f;
float arm_move_zaxis = 0.0f;
float inner_arm_rotate = 0.0f;
float inner_arm_move_xaxis = 0.0f;
float inner_arm_move_yaxis = 0.0f;
float inner_arm_move_zaxis = 0.0f;

float arm_angleRotate = 0.0f;
float arm_rotate_xaxis = 0.0f;
float arm_rotate_yaxis = 0.0f;
float arm_rotate_zaxis = 0.0f;

void drawPyramid() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(angleRotate, rotate_xaxis, rotate_yaxis, rotate_zaxis);

	glPushMatrix();
	glRotatef(-60.0f, 1.0f, 0.5f, 0.0f);
	
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
	glPopMatrix();
}

void drawRectangle() {
	glBegin(GL_LINE_STRIP);
	// Front Rectangle
	// Face 1 (Front)
	glVertex3f(0.0f, 0.0f, 0.20f);
	glVertex3f(0.5f, 0.0f, 0.20f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 (Top)
	glVertex3f(0.0f, 0.0f, 0.20f);
	glVertex3f(0.0f, 0.25f, 0.20f);
	glVertex3f(0.5f, 0.25f, 0.20f);
	glVertex3f(0.5f, 0.0f, 0.20f);

	// Face 3 (Right)
	glVertex3f(0.5f, 0.0f, 0.20f);
	glVertex3f(0.5f, 0.25f, 0.20f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);

	// Face 4 (Bottom)
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);

	// Face 5 (Back)
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.0f, 0.25f, 0.0f);
	glVertex3f(0.0f, 0.25f, 0.20f);
	glVertex3f(0.5f, 0.25f, 0.20f);
	glEnd();
}

void drawRobotArm() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();

	glPushMatrix();
	glRotatef(arm_angleRotate, arm_rotate_xaxis, arm_rotate_yaxis, arm_rotate_zaxis);

	glPushMatrix();
	glTranslatef(-0.5f, -0.1f, 0.0f);
	drawRectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-arm_move_xaxis, -arm_move_yaxis, arm_move_zaxis);
	glPushMatrix(); // Save Rotate
	glRotatef(inner_arm_rotate, inner_arm_move_xaxis, inner_arm_move_yaxis, inner_arm_move_zaxis);
	glPushMatrix();
	glTranslatef(0.0f, -0.1f, 0.0f);
	drawRectangle();
	glPopMatrix();
	glPopMatrix(); // End Save Rotate
	glPopMatrix();

	glPopMatrix(); // End of Rotate LEFT/RIGHT
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
			angleRotate = 0.01f;
			rotate_xaxis = 1.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 0.0f;
			break;
		}

		if (wParam == 0x59) {
			// Press key Y -> Rotate anticlockwise x-axis
			angleRotate = 0.01f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 1.0f;
			rotate_zaxis = 0.0f;
			break;
		}
		if (wParam == 0x5A) {
			// Press key Z -> Rotate anticlockwise x-axis
			angleRotate = 0.01f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 1.0f;
			break;
		}
		if (wParam == VK_SPACE) {
			// Space key press -> reset object to White and locate at centre
			angleRotate = 0.0f;
			rotate_xaxis = 0.0f;
			rotate_yaxis = 0.0f;
			rotate_zaxis = 0.0f;

			// Reset Arm Left Right
			arm_rotate_left_right = 0;
			arm_angleRotate = 0.0f;
			arm_rotate_xaxis = 0.0f;
			arm_rotate_yaxis = 0.0f;
			arm_rotate_xaxis = 0.0f;

			// Reset Arm Up Down
			arm_move_up_down = 0;
			arm_move_xaxis = 0.0f;
			arm_move_yaxis = 0.0f;
			arm_move_zaxis = 0.0f;
			inner_arm_rotate = 0.0f;
			inner_arm_move_xaxis = 0.0f;
			inner_arm_move_yaxis = 0.0f;
			inner_arm_move_zaxis = 0.0f;
			break;
		}
		if (wParam == 0x32) {
			// Press key 2 -> To display Question 2
			question = 2;
			break;
		}
		if (wParam == VK_UP) {
			// Press key UP ARROW -> Move Lower Arm Up
			arm_move_up_down = 1;
			inner_arm_move_xaxis = 0.0f;
			inner_arm_move_yaxis = 0.0f;
			inner_arm_move_zaxis = 1.0f;
			break;
		}
		if (wParam == VK_DOWN) {
			// Press key DOWN ARROW-> Move Lower Arm Down
			arm_move_up_down = 2;
			inner_arm_move_xaxis = 0.0f;
			inner_arm_move_yaxis = 0.0f;
			inner_arm_move_zaxis = 1.0f;
			break;
		}
		if (wParam == VK_LEFT) {
			// Press key LEFT ARROW -> Move Anti Clockwise Rotate Arm
			arm_rotate_left_right = 1;
			arm_rotate_xaxis = 1.0f;
			arm_rotate_yaxis = 1.0f;
			arm_rotate_xaxis = 1.0f;
			break;
		}
		if (wParam == VK_RIGHT) {
			// Press key RIGHT ARROW -> Move Clockwise Rotate Arm
			arm_rotate_left_right = 2;
			arm_rotate_xaxis = 1.0f;
			arm_rotate_yaxis = 1.0f;
			arm_rotate_xaxis = 1.0f;
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
	case 2:
		drawRobotArm();
		switch (arm_rotate_left_right)
		{
		case 1:
			arm_angleRotate += 0.01f;
			break;
		case 2:
			arm_angleRotate -= 0.01f;
			break;
		default:
			break;
		}

		switch (arm_move_up_down)
		{
		case 1:
			inner_arm_rotate += 0.01f;
			if (inner_arm_rotate > 40) {
				inner_arm_rotate = 40.0f;
			}
			arm_move_xaxis += 0.01f;
			if (arm_move_xaxis > 0.07f) {
				arm_move_xaxis = 0.07f;
			}
			arm_move_yaxis += 0.01f;
			if (arm_move_yaxis > 0.02f) {
				arm_move_yaxis = 0.02f;
			}
			break;
		case 2:
			inner_arm_rotate -= 0.01f;
			if (inner_arm_rotate < 1.0f) {
				inner_arm_rotate = 0.0f;
			}
			arm_move_xaxis -= 0.01f;
			if (arm_move_xaxis < 1.0f) {
				arm_move_xaxis = 0.0f;
			}
			arm_move_yaxis -= 0.01f;
			if (arm_move_yaxis < 1.0f) {
				arm_move_yaxis = 0.0f;
			}
			break;
		default:
			break;
		}
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