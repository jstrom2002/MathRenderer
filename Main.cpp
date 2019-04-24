#include "stdafx.h"

#define RADPERDEG 0.0174533

#define IDC_BROWSE			1
#define IDC_EDIT			2
#define IDC_HELP_ABOUT		3
#define IDC_OKOK			4

//GLOBAL VARIABLES 
//================
HDC hdc;
HWND hWnd;			// Main window handle.
HWND sub;
HWND hWndedit;
HWND hWndtext;
PAINTSTRUCT ps;
HGLRC hrc;
GLfloat xpos, ypos, zpos, ang1,ang2,ang3;	//variables that store coordinates of onscreen object
bool fullscreen;
bool showAxes;
bool showGrid;
bool flipSide;
bool showNormals;
bool showHorizTangents;
bool showVertTangents;
bool showTangentBundle;
bool showNormalpoint;
bool showHorizTangentPoint;
bool showVertTangentPoint;
bool showTangentBundlePoint;
bool unitize;
bool openFile;
float graphPointx;
float graphPointy;
bool colorCode;
bool zeroNormal;
unsigned int colorMapNumber;
float gridSize;
float gridWidth;
bool isAnimated;
bool orientation;
float granularity;
float zoom;
std::vector<std::vector<float>> domain;
std::vector<float> range;
std::vector<float> XVecNorm;
std::vector<float> YVecNorm;
std::vector<float> ZVecNorm;

std::vector<std::vector<GLfloat>> colorArray;
std::string graphAs;
float funct1(float x, float y);
std::vector<std::vector<float>> vec1;
long long unsigned int timeStep = 0;
long long unsigned int maxTimeStep = 0;
unsigned int functionSelection;
float period;
float parametricFunctBound;
float ubound;
float vbound;
unsigned int nBound;
float uStep;
float vStep;
float vectorFunctBound;
float colorBound;
float animSpeed = 0.01;
std::vector<float> zeroNorm_i;
std::vector<float> zeroNorm_j;
float volume;
float surfaceArea;

//FUNCTION PROTOTYPES
//===================
int CreateGraphWindow(char szAppName[], char szTitle[], HINSTANCE hInstance);
int CreateSubWindow(char szAppName[], char szTitle[], HINSTANCE hInstance);
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);//Window procedure
LONG WINAPI SubWndProc(HWND hWnd2, UINT msg, WPARAM wParam, LPARAM lParam);//subwindow procedure
HGLRC SetUpOpenGL(HWND hwnd);//Initialize OpenGL
void drawAxes(GLfloat length);
void Arrow(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat D);
void DrawPoints(float x, float y, float z,float angle1, float angle2, float angle3);
void graph3DFunction();
void graph3DParametricFunction();
void graph3DParametricSurface();
void graphRiemannSurface();
void graph2DFunction();
float funct2(float x);
float funct1(float x, float y);
void DrawVectors(float x, float y, float z, float angle1, float angle2, float angle3);
void Draw2DVectorField(float x, float y, float z, float angle1, float angle2, float angle3);
void Draw3DVectorField(float x, float y, float z, float angle1, float angle2, float angle3);
float funct3(float x, float y, float z);
float funct4(float x, float y, float z);
float funct5(float x, float y, float z);
std::vector<float> functParametric(float t);
void animateParametricFunction();
void animateVectorField(float x, float y, float z,float angle1, float angle2, float angle3);
void DrawGrid();
bool toggleState(bool A);
std::string toggleGraphAs(std::string A);
std::vector<float> functParametricSurface(float t, float v);
void graph3DParametricSurfaceNormals();
std::vector<float> functParametricSurfaceDu(float u, float v);
std::vector<float> functParametricSurfaceDv(float u, float v);
std::vector<float> functRiemannSurface(float u, float v);
std::vector<float> calcNormals(float u, float v);
template <typename T> int sgn(T val);
void graph3DParametricHorizSurfaceTangents();
void graph3DParametricVertSurfaceTangents();
void graph3DParametricTangentBundle();
void graphNormalpoint(double i, double j);
void graphHorizTangentpoint(double i, double j);
void graphVertTangentpoint(double i, double j);
void graphTangentBundlepoint(double i, double j);
void getTxtPointcloud(std::string filename);
void getTxtColorcloud(std::string filename);
void getPlyPointcloud(std::string filename);

 //			MAIN ENTRY POINT
//=======================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	char szAppName[] = "Function Grapher";
	char szAppName2[] = "Sub Window";
	char szTitle[] = "Graph Window";
	WNDCLASS wc;   // windows class structs
	WNDCLASSEX wc2; 
	MSG      msg;  // message struct 
	HWND	 hWndtext;

	wc.style = CS_HREDRAW | CS_VREDRAW;		     // Class style(s).
	wc.lpfnWndProc = (WNDPROC)WndProc;         // Window Procedure
	wc.cbClsExtra = 0;				    // No per-class extra data.
	wc.cbWndExtra = 0;				   // No per-window extra data.
	wc.hInstance = hInstance;				 // Owner of this class
	wc.hIcon = NULL;						 		   // Icon name 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		      // Cursor
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Default color
	wc.lpszMenuName = NULL;						   // Menu from .RC
	wc.lpszClassName = szAppName;            // Name to register as
	RegisterClass(&wc);					// Register the window class

	
	/*
	//EXPERIMENTING WITH SUB WINDOW
	char szTitle2[] = "Sub Window";
	wc2.cbSize = sizeof(WNDCLASSEX);
	wc2.style = CS_HREDRAW | CS_VREDRAW;
	wc2.lpfnWndProc = SubWndProc;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = hInstance;
	wc2.hIcon = NULL;
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = szAppName2;
	wc2.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	RegisterClassEx(&wc2);					// Register the window class
	*/

	//SET UP SUBWINDOW
	//================
	// Create text object						
	hWndtext = CreateWindowEx(0,
		"STATIC", "First directory",
		WS_CHILD | WS_VISIBLE,
		5, 10, 200, 20,
		sub, NULL, NULL, 0);

	hWndtext = CreateWindowEx(0,
		"STATIC", "Directory: ",
		WS_CHILD | WS_VISIBLE,
		5, 30, 200, 20,
		sub, NULL, NULL, 0);


	// Create the edit object
	hWndedit = CreateWindow("EDIT", "",
		WS_CHILD | WS_VISIBLE | ES_LEFT |
		ES_MULTILINE | ES_AUTOVSCROLL | WS_BORDER,
		5, 50, 150, 36,
		sub, (HMENU)IDC_EDIT, hInstance, NULL);

	// Create button object
	HWND button = CreateWindowEx(0,
		"BUTTON", "Browse",
		WS_CHILD | WS_VISIBLE, 5, 90, 60, 20,
		sub, (HMENU)IDC_BROWSE, NULL, 0);

	// Display the window to the user
	ShowWindow(sub, SW_SHOWNORMAL);
	UpdateWindow(sub);
	//==================


	//initialize variables for grpah
	fullscreen = true;
	showAxes = true;
	showGrid = true;
	isAnimated = false;	//controls the animation of the vectors in a vector field
	flipSide = false;
	showNormals = false;
	showHorizTangents = false;
	showVertTangents = false;
	showTangentBundle = false;
	showNormalpoint = false;
	showHorizTangentPoint = false;
	showVertTangentPoint = false;
	showTangentBundlePoint = false;
	unitize = false;
	zeroNormal = false;
	colorCode = true;
	orientation = 1;
	CreateGraphWindow(szAppName,szTitle,hInstance);	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//CreateSubWindow(szAppName, szTitle2, hInstance	);
	GLfloat val = 0.022;	//determines how fast the camera moves
	GLfloat angSpeed = 1.2f;	//adjust how fast the camera rotates
	gridSize = 4;
	gridWidth = 4;
	parametricFunctBound = 15;
	vectorFunctBound = 0.8;
	maxTimeStep = 500;
	graphAs = "points";
	ubound = 1;
	vbound = 1;
	nBound = 0;
	uStep = 0.01;
	vStep = 0.01;
	period = 1;
	granularity = 0.01;
	zoom = 1;
	colorBound = 1;
	colorMapNumber = 1;
	functionSelection = 1;
	volume = 0;
	surfaceArea = 0;
	openFile = true;

	//choose starting coordinates
	float startingCoordinate[6] = { 	//default is 0 vector
		0.0, 0.0, 0.0, //<x,y,z> position
		0.0, 0.0, 0.0  //<roll,pitch,yaw> position
	};
	xpos = startingCoordinate[0];
	ypos = startingCoordinate[1];
	zpos = startingCoordinate[2];
	ang1 = startingCoordinate[3];
	ang2 = startingCoordinate[4];
	ang3 = startingCoordinate[5];
	
	//choose single point (u,v) at which to graph normals/tangents
	graphPointx = graphPointy = 1.0f;

	//if opening a pointcloud file, do that
	if (openFile == true) {//import a pointcloud into the environment
		getTxtPointcloud("points.txt");
		getTxtColorcloud("colors.txt");
		//getPlyPointcloud("out.ply");
	}

	//MAIN LOOP - GET USER INPUT
	//==========================
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg); // Translates messages
		DispatchMessage(&msg);  // then dispatches
		timeStep++;

		//Handle zoom/rotation of axes
		if (GetAsyncKeyState(VK_LEFT) < 0) { xpos-=val; 	InvalidateRect(hWnd, NULL, NULL);}//move view left
		if (GetAsyncKeyState(VK_RIGHT) < 0) { xpos+= val; 	InvalidateRect(hWnd, NULL, NULL);}//move view right
		if (GetAsyncKeyState(VK_UP) < 0) { ypos+= val; 	InvalidateRect(hWnd, NULL, NULL);}//move view up
		if (GetAsyncKeyState(VK_DOWN) < 0) { ypos-= val; 	InvalidateRect(hWnd, NULL, NULL);}//move view down
		if (GetAsyncKeyState(VK_OEM_MINUS) < 0) { zpos -= val; 	InvalidateRect(hWnd, NULL, NULL); }//zoom out slowly
		if (GetAsyncKeyState(VK_OEM_PLUS) < 0) { zpos += val; 	InvalidateRect(hWnd, NULL, NULL); }//zoom in slowly
		if (GetAsyncKeyState('T') < 0) { ang1 += angSpeed; 	InvalidateRect(hWnd, NULL, NULL); }//roll left
		if (GetAsyncKeyState('Y') < 0) { ang1 -= angSpeed; 	InvalidateRect(hWnd, NULL, NULL); }//roll right
		if (GetAsyncKeyState('G') < 0) { ang2 += angSpeed/5; 	InvalidateRect(hWnd, NULL, NULL); }//yaw left
		if (GetAsyncKeyState('H') < 0) { ang2 -= angSpeed/5; 	InvalidateRect(hWnd, NULL, NULL); }//yaw right
		if (GetAsyncKeyState('J') < 0) { Sleep(150);ang2 -= 90; 	InvalidateRect(hWnd, NULL, NULL); }//turn left
		if (GetAsyncKeyState('K') < 0) { Sleep(150);ang2 += 90; 	InvalidateRect(hWnd, NULL, NULL); }//turn right
		if (GetAsyncKeyState('B') < 0) { ang3 += angSpeed/5; 	InvalidateRect(hWnd, NULL, NULL); }//pitch up
		if (GetAsyncKeyState('N') < 0) { ang3 -= angSpeed/5; 	InvalidateRect(hWnd, NULL, NULL); }//pitch down
		if (GetAsyncKeyState('M') < 0) { Sleep(150); ang3 -= 90; 	InvalidateRect(hWnd, NULL, NULL); }//turn left
		if (GetAsyncKeyState('O') < 0) { Sleep(150); graphPointy -=0.1; UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }
		if (GetAsyncKeyState('P') < 0) { Sleep(150); graphPointy +=0.1; UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }

		if (GetAsyncKeyState(VK_OEM_COMMA) < 0) { Sleep(150); ang3 += 90; 	InvalidateRect(hWnd, NULL, NULL); }//turn right

		//Handle view controls
		if (GetAsyncKeyState(VK_RETURN) < 0) { timeStep=xpos = ypos = zpos = ang1 = ang2 = ang3 = 0; 	InvalidateRect(hWnd, NULL, NULL); }	//center view on axes
		if (GetAsyncKeyState(VK_ESCAPE) < 0) { PostQuitMessage(0); 	InvalidateRect(hWnd, NULL, NULL);}//exit program
		if (GetAsyncKeyState(VK_DELETE) < 0) { showGrid = toggleState(showGrid);	InvalidateRect(hWnd, NULL, NULL); Sleep(250); }//toggle 3d grid
		if (GetAsyncKeyState(VK_INSERT) < 0) { showAxes = toggleState(showAxes);	InvalidateRect(hWnd, NULL, NULL); Sleep(250); }//toggle 3d axes
		if (GetAsyncKeyState(VK_HOME) < 0) { Sleep(150); flipSide = toggleState(flipSide); ang2 = 180 * flipSide; InvalidateRect(hWnd, NULL, NULL); }	//turn camera around
		if (GetAsyncKeyState(VK_END) < 0) { timeStep = 0; vec1.clear();Sleep(150); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  isAnimated = toggleState(isAnimated); InvalidateRect(hWnd, NULL, NULL); } //toggle animate parametric function/surface
		if (GetAsyncKeyState(VK_MBUTTON) < 0) { vec1.clear(); xpos = ypos = zpos = ang1 = ang2 = ang3 =  0; InvalidateRect(hWnd, NULL, NULL); }
		if (GetAsyncKeyState(VK_PRIOR) < 0) {  zpos += 1.5;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//zoom in greatly
		if (GetAsyncKeyState(VK_NEXT) < 0) { zpos -= 1.5;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//zoom out greatly
		if (GetAsyncKeyState(VK_OEM_4) < 0) { gridSize -= 2; gridWidth -= 2; InvalidateRect(hWnd, NULL, NULL);Sleep(150);}//increase 3d grid size
		if (GetAsyncKeyState(VK_OEM_6) < 0) {  gridSize += 2; gridWidth += 2; InvalidateRect(hWnd, NULL, NULL);Sleep(150); }//decrease 3d grid size
		if (GetAsyncKeyState(VK_F1) < 0) { animSpeed += 0.001; Sleep(100);}//increase speed of animation
		if (GetAsyncKeyState(VK_F2) < 0) { animSpeed -= 0.001; Sleep(100); }//decrease speed of animation
		if (GetAsyncKeyState(VK_F3) < 0) { maxTimeStep++; Sleep(100);}//increase max animation timeframe
		if (GetAsyncKeyState(VK_F4) < 0) { maxTimeStep--; Sleep(100);}//decrease max animation timeframe
		if (GetAsyncKeyState(VK_F5) < 0) { timeStep=0; Sleep(100);}//reset animation time
		if (GetAsyncKeyState(VK_F6) < 0) { vectorFunctBound += 0.1; Sleep(100); }//increase speed of animation
		if (GetAsyncKeyState(VK_F7) < 0) { vectorFunctBound -= 0.1; Sleep(100); }//decrease speed of animation
		if (GetAsyncKeyState(VK_F8) < 0) { Sleep(150); orientation = toggleState(orientation); InvalidateRect(hWnd, NULL, NULL); }//change orientation of normal vectors
		if (GetAsyncKeyState(VK_F9) < 0) { Sleep(250); graphAs = toggleGraphAs(graphAs); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle graphAs variable
		if (GetAsyncKeyState(VK_F10) < 0) { colorBound -= 0.3; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//colorBound -
		if (GetAsyncKeyState(VK_F11) < 0) { colorBound += 0.3; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//colorBound +
		if (GetAsyncKeyState(VK_OEM_3) < 0) { Sleep(250); showNormals = toggleState(showNormals); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showNormals variable
		if (GetAsyncKeyState('1') < 0) { Sleep(250); showHorizTangents = toggleState(showHorizTangents); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showHorizTangents variable
		if (GetAsyncKeyState('2') < 0) { Sleep(250); showVertTangents = toggleState(showVertTangents); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showVertTangents
		if (GetAsyncKeyState('3') < 0) { Sleep(250); showTangentBundle = toggleState(showTangentBundle); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showVertTangents
		if (GetAsyncKeyState('4') < 0) { Sleep(250); showNormalpoint = toggleState(showNormalpoint); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showHorizTangents variable
		if (GetAsyncKeyState('5') < 0) { Sleep(250); showHorizTangentPoint = toggleState(showHorizTangentPoint); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showVertTangents
		if (GetAsyncKeyState('6') < 0) { Sleep(250); showVertTangentPoint = toggleState(showVertTangentPoint); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showVertTangents
		if (GetAsyncKeyState('7') < 0) { Sleep(250); showTangentBundlePoint = toggleState(showTangentBundlePoint); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }//toggle showVertTangents
		if (GetAsyncKeyState('8') < 0) { Sleep(250); unitize = toggleState(unitize); UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }
		if (GetAsyncKeyState('9') < 0) { Sleep(250); graphPointx -= 0.1; UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }
		if (GetAsyncKeyState('0') < 0) { Sleep(250); graphPointx += 0.1; UpdateWindow(hWnd); InvalidateRect(hWnd, NULL, NULL); }
		if (GetAsyncKeyState(VK_MULTIPLY) < 0) { Sleep(150); ubound += 0.1;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//ubound +
		if (GetAsyncKeyState(VK_DIVIDE) < 0) { Sleep(150); ubound -= 0.1;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//ubound -
		if (GetAsyncKeyState(VK_ADD) < 0) { Sleep(150);vbound += 0.1;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//vbound +
		if (GetAsyncKeyState(VK_SUBTRACT) < 0) { Sleep(150); vbound -= 0.1;	InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//vbound -
		if (GetAsyncKeyState(VK_NUMPAD0) < 0) { if (uStep - granularity <= 0) { granularity /= 10; } uStep -= granularity; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//uStep -
		if (GetAsyncKeyState(VK_NUMPAD1) < 0) {uStep += granularity; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//uStep +
		if (GetAsyncKeyState(VK_NUMPAD2) < 0) {	if (vStep - granularity <= 0) { granularity /= 10; } vStep -= granularity; InvalidateRect(hWnd, NULL, NULL); Sleep(100);}//vStep -
		if (GetAsyncKeyState(VK_NUMPAD3) < 0) {vStep += granularity; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//vStep +
		if (GetAsyncKeyState(VK_NUMPAD4) < 0) { if (nBound > 0) { --nBound; }InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//nBound -
		if (GetAsyncKeyState(VK_NUMPAD5) < 0) { ++nBound; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//nBound +
		if (GetAsyncKeyState(VK_NUMPAD6) < 0) { 
			if (colorCode == true) {
				++colorMapNumber;
				colorMapNumber %= 3;
				if (colorMapNumber == 0) { ++colorMapNumber; colorCode = toggleState(colorCode);}
			}
			else { colorCode = toggleState(colorCode); }
			InvalidateRect(hWnd, NULL, NULL); Sleep(150); }//toggle color codeing function
		if (GetAsyncKeyState(VK_NUMPAD7) < 0) { zoom -= 0.1; gridWidth = 6 * zoom; gridSize = 6 * zoom; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//zoom -
		if (GetAsyncKeyState(VK_NUMPAD8) < 0) { zoom += 0.1; gridWidth = 6 * zoom; gridSize = 6 * zoom; InvalidateRect(hWnd, NULL, NULL); Sleep(100); }//zoom +
		if (GetAsyncKeyState(VK_NUMPAD9) < 0) {	++functionSelection; if (functionSelection > 19) { functionSelection = 1; } InvalidateRect(hWnd, NULL, NULL); Sleep(150);}//switch between functions
		if (timeStep > maxTimeStep) { timeStep = 0; }
		if (isAnimated == true) { InvalidateRect(hWnd, NULL, NULL); }
	}//=================================================================
	return(msg.wParam);
}//=====================================================================


int CreateGraphWindow(char szAppName[], char szTitle[], HINSTANCE hInstance){
HMONITOR hmon = MonitorFromWindow(hWnd,	MONITOR_DEFAULTTONEAREST);
MONITORINFO mi = { sizeof(mi) };
if (!GetMonitorInfo(hmon, &mi)) return NULL;
hWnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 
	mi.rcMonitor.left,
	mi.rcMonitor.top,
	mi.rcMonitor.right - mi.rcMonitor.left,
	mi.rcMonitor.bottom - mi.rcMonitor.top,
	NULL, NULL, hInstance, 0);

if (fullscreen == true) {
	DEVMODE fullscreenSettings;
	HDC windowHDC = GetDC(hWnd);
	unsigned int fullscreenWidth = GetDeviceCaps(windowHDC, HORZRES);
	unsigned int fullscreenHeight = GetDeviceCaps(windowHDC, VERTRES);
	unsigned int colourBits = GetDeviceCaps(windowHDC, BITSPIXEL);
	unsigned int refreshRate = GetDeviceCaps(windowHDC, VREFRESH);

	EnumDisplaySettings(NULL, 0, &fullscreenSettings);
	fullscreenSettings.dmPelsWidth = fullscreenWidth;
	fullscreenSettings.dmPelsHeight = fullscreenHeight;
	fullscreenSettings.dmBitsPerPel = colourBits;
	fullscreenSettings.dmDisplayFrequency = refreshRate;
	fullscreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
	ChangeDisplaySettings(&fullscreenSettings, CDS_FULLSCREEN);
	ShowWindow(hWnd, SW_MAXIMIZE);
	}
return 1;
}

int CreateSubWindow(char szAppName[], char szTitle[], HINSTANCE hInstance) {
	HMONITOR hmon = MonitorFromWindow(sub, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	if (!GetMonitorInfo(hmon, &mi)) return NULL;
	sub = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		mi.rcMonitor.left,
		mi.rcMonitor.top,
		mi.rcMonitor.right - mi.rcMonitor.left,
		mi.rcMonitor.bottom - mi.rcMonitor.top,
		NULL, NULL, hInstance, 0);
	ShowWindow(sub, SW_SHOWNORMAL);
	return 1;
}

LONG WINAPI WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	static HGLRC hRC; // Note this is STATIC!
	PAINTSTRUCT ps;
	GLfloat gldAspect;
	GLsizei glnWidth, glnHeight;

	switch (msg)
	{
	case WM_CREATE:
		hRC = SetUpOpenGL(hWnd);	// Select a pixel format and thencreate a rendering context from it.
		return 0;

	case WM_SIZE:
		hDC = GetDC(hWnd);					// Redefine the viewing volume and viewport when the window size changes.
		wglMakeCurrent(hDC, hRC);			// Make the RC current since we're going t omake an OpenGL call here...
		glnWidth = (GLsizei)LOWORD(lParam);			// get the new size of the client window. note that we size according to the height, not the smaller of the height or width.
		glnHeight = (GLsizei)HIWORD(lParam);
		gldAspect = (GLdouble)glnWidth / (GLdouble)glnHeight;
		glMatrixMode(GL_PROJECTION);		// set up a projection matrix to fill the client window
		glLoadIdentity();
		gluPerspective(			// a perspective-view matrix...
			30.0,   // Field-of-view angle
			gldAspect, // Aspect ratio of view volume
			1.0,   // Distance to near clipping plane
			10.0); // Distance to far clipping plane
		glViewport(0, 0, glnWidth, glnHeight);
		wglMakeCurrent(NULL, NULL);
		ReleaseDC(hWnd, hDC);

		return 0;

	case WM_PAINT:
		// GRAPHICS RENDERING PIPELINE
		// ===========================
		hDC = BeginPaint(hWnd, &ps);
		wglMakeCurrent(hDC, hRC);			// Get a DC, then make the RC current and associate with this DC
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear previous images
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1, 1, -1, 1, 1, 200);
		//graph3DFunction();
		//graph2DFunction();
		//graph3DParametricFunction();
		//graph3DParametricSurface();

		//graphRiemannSurface(); // --> main funct for Riemann Surface rendering		
		
		//fillVec1();
		//Draw2DVectorField(xpos, ypos, zpos,  ang1, ang2, ang3);
		//if (isAnimated == false) { Draw3DVectorField(xpos, ypos, zpos, ang1, ang2, ang3); }
		//DrawVectors(xpos, ypos, zpos, ang1, ang2, ang3);
		if (isAnimated == true) {
			//animateParametricFunction(); 
			//animateVectorField(xpos, ypos, zpos, ang1, ang2, ang3);
		}

		if (showNormals == true) { graph3DParametricSurfaceNormals(); }
		if (showNormalpoint == true) { graphNormalpoint(graphPointx, graphPointy); }

		if (showHorizTangents == true) { graph3DParametricHorizSurfaceTangents(); }
		if (showHorizTangentPoint == true) { graphHorizTangentpoint(graphPointx, graphPointy); }

		if (showVertTangents == true) { graph3DParametricVertSurfaceTangents(); }
		if (showVertTangentPoint == true) { graphVertTangentpoint(graphPointx, graphPointy); }

		if (showTangentBundle == false) { DrawPoints(xpos, ypos, zpos, ang1, ang2, ang3); }
		if (showGrid == TRUE) { DrawGrid(); }
		if (showAxes == TRUE) { drawAxes(1); }
		if (showTangentBundle == true) { graph3DParametricTangentBundle(); };
		if (showTangentBundlePoint == true) { graphTangentBundlepoint(graphPointx, graphPointy); }

		if (openFile == false) {
			domain[0].clear();
			domain[1].clear();
			domain.clear();
			range.clear();
		}
		wglMakeCurrent(NULL, NULL);			//Deselect RC
		EndPaint(hWnd, &ps);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//clear previous images
		glMatrixMode(GL_MODELVIEW);		// Clear the modelview transformation.
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);		// Clear the projection transformation.
		glLoadIdentity();
		return 0;

	case WM_DESTROY:
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);	// Handle any messages that we didn't.
}

LONG WINAPI SubWndProc(HWND hWnd2, UINT msg,WPARAM wParam, LPARAM lParam){
	switch (msg){
		PAINTSTRUCT Ps;

	case WM_COMMAND:
		switch (LOWORD(wParam))		{

		default:
			break;

		}

	case WM_CREATE:

		break;

	case WM_SHOWWINDOW:
		break;

	case WM_ACTIVATE:
		break;

		// If the user wants to close the application
	case WM_DESTROY:
		// then close it
		PostQuitMessage(WM_QUIT);
		break;

	default:
		// Process the left-over messages
		return DefWindowProc(hWnd2, msg, wParam, lParam);
	}
	return 0;
}


/////////////////////////////////////////////////////////
//  SetUpOpenGL sets the pixel format and a rendering
//  context then returns the RC
/////////////////////////////////////////////////////////
HGLRC SetUpOpenGL(HWND hWnd)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // strcut size 
		1,                              // Version number
		PFD_DRAW_TO_WINDOW |    // Flags, draw to a window,
		PFD_SUPPORT_OPENGL,		// use OpenGL
		PFD_TYPE_RGBA,          // RGBA pixel values
		24,                     // 24-bit color
		0, 0, 0,                // RGB bits & shift sizes.
		0, 0, 0,                // Don't care about them
		0, 0,                   // No alpha buffer info
		0, 0, 0, 0, 0,          // No accumulation buffer
		32,                     // 32-bit depth buffer
		0,                      // No stencil buffer
		0,                      // No auxiliary buffers
		PFD_MAIN_PLANE,         // Layer type
		0,                      // Reserved (must be 0)
		0,                      // No layer mask
		0,                      // No visible mask
		0                       // No damage mask
	};
	int nMyPixelFormatID;
	HDC hDC;
	HGLRC hRC;
	hDC = GetDC(hWnd);
	nMyPixelFormatID = ChoosePixelFormat(hDC, &pfd);
	// catch errors here.  If nMyPixelFormat is zero, then there's something wrong... most likely the window's style bits are incorrect (in CreateWindow() ) or OpenGl isn't installed on this machine
	SetPixelFormat(hDC, nMyPixelFormatID, &pfd);
	hRC = wglCreateContext(hDC);
	ReleaseDC(hWnd, hDC);
	return hRC;
}

void Arrow(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat D)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float z = z2 - z1;
	float L = sqrt(x*x + y*y + z*z);

	GLUquadricObj *quadObj;

	glPushMatrix();
	glTranslated(x1, y1, z1);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y*y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z<0) {
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);
	
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D+.01, 0.0, 4 * D+.01, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D+.01, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);
	
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1.5);
	gluDeleteQuadric(quadObj);

	glPopMatrix();
}

void DrawVectors(float x, float y, float z, float angle1, float angle2, float angle3) {

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(angle1, 0, 0, 0.000000001);	//rotate around x axis
	glRotatef(angle2, 0, 0.000000001, 0);	//y axis
	glRotatef(angle3, 0.000000001, 0, 0);	//and now z axis
	glTranslatef(0.0f + x, 0.0f + y, -2.0f + z);	// move the viewpoint out to where we can see everything

	for (int i = 0; i < vec1.size(); i++) {
		Arrow(0, 0, 0, vec1[i][1], vec1[i][1], vec1[i][2], 0.005);
	}
}

void Draw2DVectorField(float x, float y, float z,float angle1, float angle2, float angle3) {
	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(angle1, 0, 0, 0.000000001);	//rotate around x axis
	glRotatef(angle2, 0, 0.000000001, 0);	//y axis
	glRotatef(angle3, 0.000000001, 0, 0);	//and now z axis
	glTranslatef(0.0f + x, 0.0f + y, -2.0f + z);	// move the viewpoint out to where we can see everything
	glColor3f(0.0f, 1.0f, 0);

	float xbound = 2;
	float ybound = 2;
	float distanceBetweenPoints = 0.2;
	float temp1, temp2;

	std::vector<float> tempVec;
	for (float j = 0;j < ybound; j += distanceBetweenPoints) {
		for (float i = 0;i < xbound; i += distanceBetweenPoints) {
			//graph 4 divergent vectors from this one point (i,j,k)
			temp1 = funct3(i, j, 0.001);
			temp2 = funct4(i, j, 0.001);
			tempVec.clear();
			tempVec.push_back(i);
			tempVec.push_back(j);
			tempVec.push_back(0.001);
			tempVec.push_back(i+temp1 - .00002);
			tempVec.push_back(j+temp2 - .00002);
			tempVec.push_back(0.001);
			vec1.push_back(tempVec);
		}
	}
	for (float j = 0;j > -ybound; j -= distanceBetweenPoints) {
		for (float i = 0;i >-xbound; i -= distanceBetweenPoints) {
			//graph 4 divergent vectors from this one point (i,j,k)
			temp1 = funct3(i, j, 0.001);
			temp2 = funct4(i, j, 0.001);
			tempVec.clear();
			tempVec.push_back(i);
			tempVec.push_back(j);
			tempVec.push_back(0.001);
			tempVec.push_back(i+temp1 + .00002);
			tempVec.push_back(j+temp2 + .00002);
			tempVec.push_back(0.001);
			vec1.push_back(tempVec);
		}
	}
	for (float j = 0;j < ybound; j += distanceBetweenPoints) {
		for (float i = 0;i >-xbound; i -= distanceBetweenPoints) {
			//graph 4 divergent vectors from this one point (i,j,k)
			temp1 = funct3(i, j, 0.001);
			temp2 = funct4(i, j, 0.001);
			tempVec.clear();
			tempVec.push_back(i);
			tempVec.push_back(j);
			tempVec.push_back(0.001);
			tempVec.push_back(i+temp1 + .00002);
			tempVec.push_back(j+temp2 - .00002);
			tempVec.push_back(0.001);
			vec1.push_back(tempVec);
		}
	}
	for (float j = 0;j >-ybound; j -= distanceBetweenPoints) {
		for (float i = 0;i < xbound; i += distanceBetweenPoints) {
			//graph 4 divergent vectors from this one point (i,j,k)
			temp1 = funct3(i, j, 0.001);
			temp2 = funct4(i, j, 0.001);
			tempVec.clear();
			tempVec.push_back(i);
			tempVec.push_back(j);
			tempVec.push_back(0.001);
			tempVec.push_back(i+temp1 - .00002);
			tempVec.push_back(j+temp2 + .00002);
			tempVec.push_back(0.001);
			vec1.push_back(tempVec);
		}
	}
	
	//Draw vectors
	if (vec1.size() >= 1) {
		for (int i = 0; i < vec1.size(); i++) {
			if (i < vec1.size()) { Arrow(vec1[i][0], vec1[i][1], 0.001, vec1[i][3],vec1[i][4],0.001,0.005); }
		}
	}
	//end
}

void Draw3DVectorField(float x, float y, float z, float angle1, float angle2, float angle3) {
	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(angle1, 0, 0, 0.000000001);	//rotate around x axis
	glRotatef(angle2, 0, 0.000000001, 0);	//y axis
	glRotatef(angle3, 0.000000001, 0, 0);	//and now z axis
	glTranslatef(0.0f + x, 0.0f + y, -2.0f + z);	// move the viewpoint out to where we can see everything
	glColor3f(0.0f, 1.0f, 0);

	float xbound = 0.8;
	float ybound = 0.8;
	float zbound = 0.8;
	float distanceBetweenPoints = 0.2;
	float temp1, temp2, temp3;
	std::vector<float> tempVec;
	for (float k = 0;k < zbound; k += distanceBetweenPoints) {
		for (float j = 0;j < ybound; j += distanceBetweenPoints) {
			for (float i = 0;i < xbound; i += distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 - .00002);
				tempVec.push_back(j + temp2 - .00002);
				tempVec.push_back(k + temp3 - .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k < zbound; k += distanceBetweenPoints) {
		for (float j = 0;j < ybound; j += distanceBetweenPoints) {
			for (float i = 0;i > -xbound; i -= distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 + .00002);
				tempVec.push_back(j + temp2 - .00002);
				tempVec.push_back(k + temp3 - .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k < zbound; k += distanceBetweenPoints) {
		for (float j = 0;j >-ybound; j -= distanceBetweenPoints) {
			for (float i = 0;i < xbound; i += distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 - .00002);
				tempVec.push_back(j + temp2 + .00002);
				tempVec.push_back(k + temp3 - .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k > -zbound; k -= distanceBetweenPoints) {
		for (float j = 0;j < ybound; j += distanceBetweenPoints) {
			for (float i = 0;i < xbound; i += distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 - .00002);
				tempVec.push_back(j + temp2 - .00002);
				tempVec.push_back(k + temp3 + .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k < zbound; k += distanceBetweenPoints) {
		for (float j = 0;j > -ybound; j -= distanceBetweenPoints) {
			for (float i = 0;i > -xbound; i -= distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 + .00002);
				tempVec.push_back(j + temp2 + .00002);
				tempVec.push_back(k + temp3 - .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k > -zbound; k -= distanceBetweenPoints) {
		for (float j = 0;j > -ybound; j -= distanceBetweenPoints) {
			for (float i = 0;i < xbound; i += distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 - .00002);
				tempVec.push_back(j + temp2 + .00002);
				tempVec.push_back(k + temp3 + .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k > -zbound; k -= distanceBetweenPoints) {
		for (float j = 0;j < ybound; j += distanceBetweenPoints) {
			for (float i = 0;i > -xbound; i -= distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 + .00002);
				tempVec.push_back(j + temp2 - .00002);
				tempVec.push_back(k + temp3 + .00002);
				vec1.push_back(tempVec);
			}
		}
	}

	for (float k = 0;k > -zbound; k -= distanceBetweenPoints) {
		for (float j = 0;j > -ybound; j -= distanceBetweenPoints) {
			for (float i = 0;i > -xbound; i -= distanceBetweenPoints) {
				//graph 4 divergent vectors from this one point (i,j,k)
				temp1 = funct3(i, j, k);
				temp2 = funct4(i, j, k);
				temp3 = funct5(i, j, k);
				tempVec.clear();
				tempVec.push_back(i);
				tempVec.push_back(j);
				tempVec.push_back(k);
				tempVec.push_back(i + temp1 + .00002);
				tempVec.push_back(j + temp2 + .00002);
				tempVec.push_back(k + temp3 + .00002);
				vec1.push_back(tempVec);
			}
		}
	}
	//Draw vectors
	for (int i = 0; i < vec1.size(); i++) {
		Arrow(vec1[i][0], vec1[i][1], vec1[i][2], vec1[i][3], vec1[i][4], vec1[i][5], 0.005); }
	tempVec.clear();
	//end
}

//Vector Field variables
//======================
float funct3(float x, float y, float z) {
	return x*x;	//vector field F(x,y,z) = <x^2, y^2, sin(z)>
}
float funct4(float x, float y, float z) {
	return y*y;
}float funct5(float x, float y, float z) {
	return sin(z);
}

void drawAxes(GLfloat length){
	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glTranslatef(-length*zoom, 0, 0);
	Arrow(0, 0, 0, 2 * length*zoom, 0, 0, 0.006);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -length*zoom, 0);
	Arrow(0, 0, 0, 0, 2 * length*zoom, 0, 0.006);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -length*zoom);
	Arrow(0, 0, 0, 0, 0, 2 * length*zoom, 0.006);
	glPopMatrix();
}

void DrawPoints(float x, float y, float z, float angle1, float angle2, float angle3) {//Actual Drawing code
	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(angle1, 0, 0, 0.00000001);	//rotate around x axis
	glRotatef(angle2, 0, 0.0000000000001, 0);	//y axis
	glRotatef(angle3, 0.0000000000001, 0, 0);	//and now z axis
	glTranslatef(0.0f + x, 0.0f + y, -2.0f + z);	// move the viewpoint out to where we can see everything

	if (graphAs == "triangles") { glBegin(GL_TRIANGLE_STRIP); }
	if (graphAs == "squares") { glBegin(GL_QUADS); }
	if (graphAs == "lines") { glBegin(GL_LINE_LOOP); }
	if (graphAs == "points") { 
		if (isAnimated == false) { 
			glPointSize(2.0f); 
		} 
		glBegin(GL_POINTS); }
	if (graphAs == "polygon") {	
		// Turn on wireframe mode
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

		// Draw
		glBegin(GL_POLYGON);

		// Turn off wireframe mode
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	if (colorCode == false) { glColor3f(1, 0, 0); }
	if (domain.size() > 0 && domain[0].size() > 0) {
		for (int i = 0; i < domain[0].size(); i++) {
			if (colorCode == true && i < colorArray.size()) { 
				glColor3f(colorArray[i][0], colorArray[i][1], colorArray[i][2]); 
				//colorArray[i].clear();
			}
			glVertex3f((GLfloat)domain[0][i], (GLfloat)domain[1][i], (GLfloat)range[i]);
		}
	}
	//colorArray.clear();
/*	domain[0].clear();
	domain[1].clear();
	range.clear();
*/	glEnd();
	glFlush();
}

void graph3DFunction() {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;

	float xbound = 4;
	float ybound = 4;
	float distanceBetweenPoints = 0.03;
		for (float i = 0;i < xbound; i += distanceBetweenPoints) {
			for (float j = 0;j < ybound; j += distanceBetweenPoints) {
				float temp = funct1(i, j);		
				XVec.push_back(i);
				YVec.push_back(j);
				ZVec.push_back(temp);

				float tempi = -i;
				float tempj = -j;
				temp = funct1(tempi, tempj);
				XVec.push_back(tempi);
				YVec.push_back(tempj);
				ZVec.push_back(temp);

				tempi = i;
				tempj = -j;
				temp = funct1(tempi, tempj);
				XVec.push_back(tempi);
				YVec.push_back(tempj);
				ZVec.push_back(temp);

				tempi = -i;
				tempj = j;
				temp = funct1(tempi, tempj);
				XVec.push_back(tempi);
				YVec.push_back(tempj);
				ZVec.push_back(temp);
		}
	}
}

void graph3DParametricFunction() {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;

	float timeStep = 0.005;
	std::vector<float> temp;
	if (graphAs == "points") {
		for (float i = -parametricFunctBound; i < parametricFunctBound; i += timeStep) {
				temp = functParametric(i);		
				XVec.push_back(temp[0]);
				YVec.push_back(temp[1]);
				ZVec.push_back(temp[2]);
		}
	}
	domain.push_back(YVec);
	domain.push_back(ZVec);
	range = XVec;
	XVec.clear();
	YVec.clear();
	ZVec.clear();
}

void animateParametricFunction() {
	if (timeStep >= range.size()) { timeStep == 0; }

	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;

	std::vector<float> temp;
	glPointSize(5.0f);
	temp = functParametric(-parametricFunctBound + (animSpeed*timeStep));		
	XVec.push_back(temp[0]);
	YVec.push_back(temp[1]);
	ZVec.push_back(temp[2]);
	temp.clear();
	domain.push_back(YVec);
	domain.push_back(ZVec);
	range = XVec;
}

void graphNormalpoint(double i, double j) {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;
	std::vector<float> temp;
	float tempNorm = 1.0f;
	std::vector<float> D = functRiemannSurface(i, j);	//<y,z,x>

	temp = calcNormals(i, j);
	//if (unitize == true) { tempNorm = arrNorm(temp); }
	if (temp.size() != NULL) {
				XVecNorm.push_back(temp[0]/tempNorm);
				YVecNorm.push_back(temp[1]/tempNorm);
				ZVecNorm.push_back(temp[2]/tempNorm);
	}	
	temp.clear();

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(0.0f, 1.0f, 0.4f);
	if (zeroNormal == true && D[1] == zeroNorm_i[0] && D[2] == zeroNorm_j[0]) {
		glColor3f(1.0f, 1.0f, 1.0f);
		Arrow(D[1], D[2], D[0], 3.5 + D[1], 3.5 + D[2], 3.5 + D[0], 0.006);
	}
	else {
		Arrow(D[1], D[2], D[0], YVecNorm[0] + D[1], ZVecNorm[0] + D[2], XVecNorm[0] + D[0], 0.003);
	}

	if (zeroNormal == true && D[1] == zeroNorm_i[0] && D[2] == zeroNorm_j[0]) {
		glColor3f(0.0f, 0.1f, 1.0f);
		zeroNorm_i.erase(zeroNorm_i.begin());
		zeroNorm_j.erase(zeroNorm_j.begin());
	}

	zeroNormal = false;
	zeroNorm_i.clear();
	zeroNorm_j.clear();
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	D.clear();
}

void graph3DParametricSurfaceNormals() {
	std::vector<float> temp;

	for (float j = 0; j < vbound; j += vStep) {
		for (float i = 0; i < ubound; i += uStep) {
			if(i==0 && j==0){
				temp = calcNormals(i, j);
				if (temp.size() != NULL) {
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);
				}
			}
			else {
				temp = calcNormals(i, j);
				if (temp.size() != NULL) {
					XVecNorm.push_back(temp[0]);
					YVecNorm.push_back(temp[1]);
					ZVecNorm.push_back(temp[2]);
				}

				temp = calcNormals(-i, -j);
				if (temp.size() != NULL) {
					XVecNorm.push_back(temp[0]);
					YVecNorm.push_back(temp[1]);
					ZVecNorm.push_back(temp[2]);
				}

				temp = calcNormals(-i, j);
				if (temp.size() != NULL) {
					XVecNorm.push_back(temp[0]);
					YVecNorm.push_back(temp[1]);
					ZVecNorm.push_back(temp[2]);
				}

				temp = calcNormals(i, -j);
				if (temp.size() != NULL) {
					XVecNorm.push_back(temp[0]);
					YVecNorm.push_back(temp[1]);
					ZVecNorm.push_back(temp[2]);
				}
			}
		}
	}
	temp.clear();

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(0.0f, 1.0f, 0.4f);
	for (int i = 0; i < XVecNorm.size(); i+=7) {
		if (zeroNormal == true && domain[0][i] == zeroNorm_i[0] && domain[1][i] == zeroNorm_j[0]) { 
			glColor3f(1.0f, 1.0f, 1.0f); 
			Arrow(domain[0][i], domain[1][i], range[i], 3.5 + domain[0][i], 3.5 + domain[1][i], 3.5 + range[i], 0.006);
		}
		else {
			Arrow(domain[0][i], domain[1][i], range[i], YVecNorm[i] + domain[0][i], ZVecNorm[i] + domain[1][i], XVecNorm[i] + range[i], 0.003);
			volume += (YVecNorm[i]*domain[0][i] + ZVecNorm[i]*domain[1][i] + XVecNorm[i]*range[i])*(uStep*vStep);	//volume = sum(dot product(f(u,v)*normal(u,v)*du*dv)
			surfaceArea += sqrt(XVecNorm[i]*XVecNorm[i]+YVecNorm[i]*YVecNorm[i]+ZVecNorm[i]*ZVecNorm[i])*(uStep*vStep);	//surfaceArea = norm(cross product(r_du x r_dv)) * du * dv
		}

		if (zeroNormal == true && domain[0][i] == zeroNorm_i[0] && domain[1][i] == zeroNorm_j[0]) { 
			glColor3f(0.0f, 0.4f, 0.7f); 
			zeroNorm_i.erase(zeroNorm_i.begin());
			zeroNorm_j.erase(zeroNorm_j.begin());
		}
	}
	volume = 0;
	surfaceArea = 0;
	zeroNormal = false;
	zeroNorm_i.clear();
	zeroNorm_j.clear();
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
}

void graphHorizTangentpoint(double i, double j) {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;
	std::vector<float> temp;
	float tempNorm = 1.0f;
	std::vector<float> D = functRiemannSurface(i, j);

	temp = functParametricSurfaceDu(i, j);
	//if (unitize == true) { tempNorm = arrNorm(temp); }
	if (temp.size() != NULL) {
		XVecNorm.push_back(temp[0]/tempNorm);
		YVecNorm.push_back(temp[1]/tempNorm);
		ZVecNorm.push_back(temp[2]/tempNorm);
	}
	


	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(0.7f, 1.0f, 0.0f);
	Arrow(D[1], D[2], D[0], YVecNorm[0] + D[1], ZVecNorm[0] + D[2], XVecNorm[0] + D[0], 0.003);
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	temp.clear();
	D.clear();
}


void graph3DParametricHorizSurfaceTangents() {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;
	std::vector<float> temp;
	float tempNorm = 0;

	for (float j = 0; j <= vbound; j += vStep) {
		for (float i = 0; i <= ubound; i += uStep) {
			if (i == 0 && j == 0) {
				temp = functParametricSurfaceDu(i, j);
				if (temp.size() != NULL) {				
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
			}
			else {
				temp = functParametricSurfaceDu(i, j);
				if (temp.size() != NULL) {					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}

				temp = functParametricSurfaceDu(-i, -j);
				if (temp.size() != NULL) {					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}

				temp = functParametricSurfaceDu(-i, j);
				if (temp.size() != NULL) {					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}

				temp = functParametricSurfaceDu(i, -j);
				if (temp.size() != NULL) {				
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
			}
		}
	}

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(0.6f, 1.0f, 0.0f);
	for (int i = 0; i < XVecNorm.size(); i++) {
		Arrow(domain[0][i], domain[1][i], range[i], YVecNorm[i] + domain[0][i], ZVecNorm[i] + domain[1][i], XVecNorm[i] + range[i], 0.003);
	}
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	temp.clear();
}

void graphTangentBundlepoint(double i, double j) {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;

	std::vector<float> XVecNorm2;
	std::vector<float> YVecNorm2;
	std::vector<float> ZVecNorm2;

	std::vector<float> temp;
	float tempNorm = 1;

	std::vector<float> D = functRiemannSurface(i, j);

	temp = functParametricSurfaceDu(i, j);
		if (temp.size() != NULL) {
				//if(unitize==true){tempNorm = arrNorm(temp);}
				XVecNorm.push_back(temp[0]/tempNorm);
				YVecNorm.push_back(temp[1]/tempNorm);
				ZVecNorm.push_back(temp[2]/tempNorm);
		}
	temp = functParametricSurfaceDv(i, j);
		if (temp.size() != NULL) {
				//if(unitize==true){tempNorm = arrNorm(temp);}
				XVecNorm2.push_back(temp[0]/tempNorm);
				YVecNorm2.push_back(temp[1]/tempNorm);
				ZVecNorm2.push_back(temp[2]/tempNorm);
		}

	temp.clear();

/*	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(1.0f, 1.0f, 0.0f);*/

/*	if (graphAs == "triangles") { glBegin(GL_TRIANGLE_STRIP); }
	if (graphAs == "squares") { glBegin(GL_QUADS); }
	if (graphAs == "lines") { glBegin(GL_LINE_STRIP); }
	if (graphAs == "points") { if (isAnimated == false) { glPointSize(1.0f); } glBegin(GL_POINTS); }
	if (graphAs == "polygon") { glBegin(GL_POLYGON); }*/

	glColor3f(1.0f, 1.0f, 0.0f);
	if (D.size() > 0 && XVecNorm.size() > 0) {
		for (int m = 0; m < XVecNorm.size(); ++m) {
			for (float k = -1; k <= 1; k += 0.2) {
				for (float l = -1; l <= 1; l += 0.2) {
					//display as point
					//std::vector<GLfloat> tempvec;
					//tempvec.push_back((GLfloat)(D[1] + (YVecNorm[i] * k + (YVecNorm2[i] * l))));
					//tempvec.push_back((GLfloat)(D[2] + (ZVecNorm[i] * k + (ZVecNorm2[i] * l))));
					//tempvec.push_back((GLfloat)(D[0] + (XVecNorm[i] * k + (XVecNorm2[i] * l))));
					//glVertex3f(tempvec[0], tempvec[1], tempvec[2]);	

					//display as vector
					Arrow(D[1], D[2], D[0],	(((YVecNorm[m] * k) + (YVecNorm2[m] * l)) + D[1]), (((ZVecNorm[m] * k) + (ZVecNorm2[m] * l)) + D[2]), (((XVecNorm[m] * k) + (XVecNorm2[m] * l)) + D[0]),0.003);	
				}
			}
		}
	}
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	XVecNorm2.clear();
	YVecNorm2.clear();
	ZVecNorm2.clear();
	D.clear();
	glEnd();
	glFlush();
}

void graph3DParametricTangentBundle() {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;

	std::vector<float> XVecNorm2;
	std::vector<float> YVecNorm2;
	std::vector<float> ZVecNorm2;

	std::vector<std::vector<float>> domain2;
	std::vector<float> range2;
	std::vector<std::vector<float>> domain3;
	std::vector<float> range3;

	std::vector<float> temp;
	float tempNorm = 0;

	for (float j = 0; j <= vbound; j += vStep) {
		for (float i = 0; i <= ubound; i += uStep) {
			if (i == 0 && j == 0) {
				temp = functParametricSurfaceDu(i, j);
				if (temp.size() != NULL) {
					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
				temp = functParametricSurfaceDv(i, j);
				if (temp.size() != NULL) {
					
					XVecNorm2.push_back(temp[0] );
					YVecNorm2.push_back(temp[1] );
					ZVecNorm2.push_back(temp[2] );
				}
			}
			else {
				temp = functParametricSurfaceDu(i, j);
				if (temp.size() != NULL) {
					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
				temp = functParametricSurfaceDv(i, j);
				if (temp.size() != NULL) {
					
					XVecNorm2.push_back(temp[0] );
					YVecNorm2.push_back(temp[1] );
					ZVecNorm2.push_back(temp[2] );
				}

				temp = functParametricSurfaceDu(-i, -j);
				if (temp.size() != NULL) {
					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
				temp = functParametricSurfaceDv(-i, -j);
				if (temp.size() != NULL) {
					
					XVecNorm2.push_back(temp[0] );
					YVecNorm2.push_back(temp[1] );
					ZVecNorm2.push_back(temp[2] );
				}

				temp = functParametricSurfaceDu(-i, j);
				if (temp.size() != NULL) {
					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
				temp = functParametricSurfaceDv(-i, j);
				if (temp.size() != NULL) {
					
					XVecNorm2.push_back(temp[0] );
					YVecNorm2.push_back(temp[1] );
					ZVecNorm2.push_back(temp[2] );
				}
				
				temp = functParametricSurfaceDu(i, -j);
				if (temp.size() != NULL) {
					
					XVecNorm.push_back(temp[0] );
					YVecNorm.push_back(temp[1] );
					ZVecNorm.push_back(temp[2] );
				}
				temp = functParametricSurfaceDv(i, -j);
				if (temp.size() != NULL) {
					
					XVecNorm2.push_back(temp[0] );
					YVecNorm2.push_back(temp[1] );
					ZVecNorm2.push_back(temp[2] );
				}
			}
		}
	}
	temp.clear();

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(1.0f, 1.0f, 0.0f);


	if (graphAs == "triangles") { glBegin(GL_TRIANGLE_STRIP); }
	if (graphAs == "squares") { glBegin(GL_QUADS); }
	if (graphAs == "lines") { glBegin(GL_LINE_STRIP); }
	if (graphAs == "points") { if (isAnimated == false) { glPointSize(1.0f); } glBegin(GL_POINTS); }
	if (graphAs == "polygon") { glBegin(GL_POLYGON); }

	if (domain.size() > 0 && domain[0].size() > 0) {
		for (int i = 0; i < domain[0].size(); ++i) {
			for (float k = -1; k <= 1; k+=0.2) {
				for (float l = -1; l <= 1; l+=0.2) {
					std::vector<GLfloat> tempvec;
					tempvec.push_back((GLfloat)(domain[0][i] + (YVecNorm[i] * k + (YVecNorm2[i] * l))));
					tempvec.push_back((GLfloat)(domain[1][i] + (ZVecNorm[i] * k + (ZVecNorm2[i] * l))));
					tempvec.push_back((GLfloat)(range[i]     + (XVecNorm[i] * k + (XVecNorm2[i] * l))));
					glVertex3f(tempvec[0], tempvec[1], tempvec[2]);
				}
			}
		}
	}
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	XVecNorm2.clear();
	YVecNorm2.clear();
	ZVecNorm2.clear();
	glEnd();
	glFlush();
}

void graphVertTangentpoint(double i, double j) {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;
	std::vector<float> temp;
	float tempNorm = 1;

	std::vector<float> D = functRiemannSurface(i, j);

	temp = functParametricSurfaceDv(i, j);
	//if (unitize == true) { tempNorm = arrNorm(temp); }
		XVecNorm.push_back(temp[0]/tempNorm);
		YVecNorm.push_back(temp[1]/tempNorm);
		ZVecNorm.push_back(temp[2]/tempNorm);

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(1.0f, 0.0f, 0.8f);
	Arrow(D[1], D[2], D[0], YVecNorm[0] + D[1], ZVecNorm[0] + D[2], XVecNorm[0] + D[0], 0.003);
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
	D.clear();
}

void graph3DParametricVertSurfaceTangents() {
	std::vector<float> XVecNorm;
	std::vector<float> YVecNorm;
	std::vector<float> ZVecNorm;
	std::vector<float> temp;
	float tempNorm = 0;

	for (float j = 0; j <= vbound; j += vStep) {
		for (float i = 0; i <= ubound; i += uStep) {
			if (i == 0 && j == 0) {
				temp = functParametricSurfaceDv(i, j);
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);
			}
			else {
				temp = functParametricSurfaceDv(i, j);
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);

				temp = functParametricSurfaceDv(-i, -j);
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);

				temp = functParametricSurfaceDv(-i, j);
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);

				temp = functParametricSurfaceDv(i, -j);
				XVecNorm.push_back(temp[0]);
				YVecNorm.push_back(temp[1]);
				ZVecNorm.push_back(temp[2]);
			}
		}
	}

	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < XVecNorm.size(); i++) {
		Arrow(domain[0][i], domain[1][i], range[i], YVecNorm[i] + domain[0][i], ZVecNorm[i] + domain[1][i], XVecNorm[i] + range[i], 0.003);
	}
	XVecNorm.clear();
	YVecNorm.clear();
	ZVecNorm.clear();
}

std::vector<float> functParametricSurfaceDu(float u, float v) {
	std::vector<float> answer1;
	std::vector<float> answer2;
	std::vector<float> answer;
	float dx = 0.0001;
	//answer1 = functParametricSurface(u + dx, v);
	//answer2 = functParametricSurface(u, v);
	answer1 = functRiemannSurface(u + dx, v);
	answer2 = functRiemannSurface(u, v);
	if (answer1.size() == 0 || answer2.size() == 0) { return answer; }//return null vector if not analytic
	answer.push_back((answer1[0] - answer2[0]) / dx);
	answer.push_back((answer1[1] - answer2[1]) / dx);
	answer.push_back((answer1[2] - answer2[2]) / dx);
	answer1.clear();
	answer2.clear();
	return answer;
}

std::vector<float> functParametricSurfaceDv(float u, float v) {
	std::vector<float> answer1, answer2, answer;
	float dx = 0.0001;
	//answer1 = functParametricSurface(u, v + dx);
	//answer2 = functParametricSurface(u, v);
	answer1 = functRiemannSurface(u, v + dx);
	answer2 = functRiemannSurface(u, v);
	if (answer1.size() == 0 || answer2.size() == 0) { return answer; }//return null vector if not analytic
	answer.push_back((answer1[0] - answer2[0]) / dx), answer.push_back((answer1[1] - answer2[1]) / dx),	answer.push_back((answer1[2] - answer2[2]) / dx);
	answer1.clear();
	answer2.clear();
	return answer;
}

std::vector<float> calcNormals(float u, float v) {			//surface normal = r_u x r_v / norm(r_u x r_v)
	std::vector<float> answer1 = functParametricSurfaceDu(u, v);
	std::vector<float> answer2 = functParametricSurfaceDv(u, v);
	std::vector<float> answer;
	if (answer1.size() == 0 || answer2.size() == 0) { return answer; }//return null vector if not analytic

	if (orientation == false) {	//if surface is oriented inwards, take cross-product of vectors in reverse order
		std::vector<float> temp = answer2;
		answer2 = answer1;
		answer1 = temp;
		temp.clear();
	}

	//Cross Product calculation -- r_u x r_v = i*det(minor A_1) - j*det(minor A_2) + k*det(minor A-3) in 3D
	answer.push_back(( (answer1[1] * answer2[2]) - (answer1[2] * answer2[1]) ));
	answer.push_back((-1) * ( (answer1[0] * answer2[2]) - (answer1[2] * answer2[0]) ));
	answer.push_back( (answer1[0] * answer2[1]) - (answer1[1] * answer2[0]) );
	float divisor = sqrt( pow(answer[0], 2) + pow(answer[1], 2) + pow(answer[2],2) );
	if (divisor < 0.000000001 && divisor > -0.000000001) { // case: a x b = 0
		zeroNorm_i.push_back(u); 
		zeroNorm_j.push_back(v);
		zeroNormal = true; 
		return answer; 
	}	
	answer[0];
	answer[1];
	answer[2];
	return answer;
}

void animateVectorField(float x, float y, float z, float angle1, float angle2, float angle3) {
	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(angle1, 0, 0, 0.000000001);	//rotate around x axis
	glRotatef(angle2, 0, 0.000000001, 0);	//y axis
	glRotatef(angle3, 0.000000001, 0, 0);	//and now z axis
	glTranslatef(0.0f + x, 0.0f + y, -2.0f + z);	// move the viewpoint out to where we can see everything
	glColor3f(0.0f, 1.0f, 0);
	
	float timeStepHolder = maxTimeStep;
	maxTimeStep = 20;
	vec1.clear();
	float distanceBetweenPoints = 0.2;

		float xbound = vectorFunctBound + (animSpeed*timeStep);
		float ybound = vectorFunctBound + (animSpeed*timeStep);
		float zbound = vectorFunctBound + (animSpeed*timeStep);
		float temp1, temp2, temp3;

		std::vector<float> tempVec;

		for (float k = animSpeed*timeStep;k < zbound; k += distanceBetweenPoints) {
			for (float j = animSpeed*timeStep;j < ybound; j += distanceBetweenPoints) {
				for (float i = animSpeed*timeStep;i < xbound; i += distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 - .00002);
					tempVec.push_back(j + temp2 - .00002);
					tempVec.push_back(k + temp3 - .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = animSpeed*timeStep;k < zbound; k += distanceBetweenPoints) {
			for (float j = animSpeed*timeStep;j < ybound; j += distanceBetweenPoints) {
				for (float i = -1*animSpeed*timeStep;i > -xbound; i -= distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 + .00002);
					tempVec.push_back(j + temp2 - .00002);
					tempVec.push_back(k + temp3 - .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = animSpeed*timeStep;k < zbound; k += distanceBetweenPoints) {
			for (float j = -1* animSpeed*timeStep;j >-ybound; j -= distanceBetweenPoints) {
				for (float i = animSpeed*timeStep;i < xbound; i += distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 - .00002);
					tempVec.push_back(j + temp2 + .00002);
					tempVec.push_back(k + temp3 - .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = -1* animSpeed*timeStep;k > -zbound; k -= distanceBetweenPoints) {
			for (float j = animSpeed*timeStep;j < ybound; j += distanceBetweenPoints) {
				for (float i = animSpeed*timeStep;i < xbound; i += distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 - .00002);
					tempVec.push_back(j + temp2 - .00002);
					tempVec.push_back(k + temp3 + .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = animSpeed*timeStep;k < zbound; k += distanceBetweenPoints) {
			for (float j = -1* animSpeed*timeStep;j > -ybound; j -= distanceBetweenPoints) {
				for (float i = -1* animSpeed*timeStep;i > -xbound; i -= distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 + .00002);
					tempVec.push_back(j + temp2 + .00002);
					tempVec.push_back(k + temp3 - .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = -1* animSpeed*timeStep;k > -zbound; k -= distanceBetweenPoints) {
			for (float j = -1* animSpeed*timeStep;j > -ybound; j -= distanceBetweenPoints) {
				for (float i = animSpeed*timeStep;i < xbound; i += distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 - .00002);
					tempVec.push_back(j + temp2 + .00002);
					tempVec.push_back(k + temp3 + .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = -1* animSpeed*timeStep;k > -zbound; k -= distanceBetweenPoints) {
			for (float j = animSpeed*timeStep;j < ybound; j += distanceBetweenPoints) {
				for (float i = -1* animSpeed*timeStep;i > -xbound; i -= distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 + .00002);
					tempVec.push_back(j + temp2 - .00002);
					tempVec.push_back(k + temp3 + .00002);
					vec1.push_back(tempVec);
				}
			}
		}

		for (float k = -1* animSpeed*timeStep;k > -zbound; k -= distanceBetweenPoints) {
			for (float j = -1 * animSpeed*timeStep;j > -ybound; j -= distanceBetweenPoints) {
				for (float i = -1 * animSpeed*timeStep;i > -xbound; i -= distanceBetweenPoints) {
					//graph 4 divergent vectors from this one point (i,j,k)
					temp1 = funct3(i, j, k);
					temp2 = funct4(i, j, k);
					temp3 = funct5(i, j, k);
					tempVec.clear();
					tempVec.push_back(i);
					tempVec.push_back(j);
					tempVec.push_back(k);
					tempVec.push_back(i + temp1 + .00002);
					tempVec.push_back(j + temp2 + .00002);
					tempVec.push_back(k + temp3 + .00002);
					vec1.push_back(tempVec);
				}
			}
		}

	//Draw vectors
	for (int i = 0; i < vec1.size(); i++) {
		Arrow(vec1[i][0], vec1[i][1], vec1[i][2], vec1[i][3], vec1[i][4], vec1[i][5], 0.005);
		vec1[i].clear();
	}
	vec1.clear();
	maxTimeStep = timeStepHolder;
	//end
}

void graph3DParametricSurface() {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;
	std::vector<float> temp;

	for (float j = 0; j <= vbound; j += vStep) {
			for (float i = 0; i <= ubound; i += uStep) {
				
				temp = functParametricSurface(i,j);		
				if (temp.size() != NULL) {
					XVec.push_back(temp[0]);
					YVec.push_back(temp[1]);
					ZVec.push_back(temp[2]);
				}

				temp = functParametricSurface(-i, -j);		
				if (temp.size() != NULL) {
					XVec.push_back(temp[0]);
					YVec.push_back(temp[1]);
					ZVec.push_back(temp[2]);
				}

				temp = functParametricSurface(-i, j);		
				if (temp.size() != NULL) {
					XVec.push_back(temp[0]);
					YVec.push_back(temp[1]);
					ZVec.push_back(temp[2]);
				}

				temp = functParametricSurface(i, -j);		
				if (temp.size() != NULL) {
					XVec.push_back(temp[0]);
					YVec.push_back(temp[1]);
					ZVec.push_back(temp[2]);
				}
			}
		}
	temp.clear();
	domain.push_back(YVec);
	domain.push_back(ZVec);
	range = XVec;
}

std::vector<float> functRiemannSurface(float u, float v) {
	std::vector<float> answer;
	std::vector<float> tp1;
	
	if (functionSelection == 1) {
		//Complex Power Function
		//======================
		float n = (2.0);		//integer power
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*(u*u - v*v));
		if (colorCode == true) {
			tp1.push_back(2 * u*v);
		}
	}

	if (functionSelection == 2) {
		float n = (0.5);		//non-integer power
		answer.push_back(zoom*abs(u)*cos(v));
		answer.push_back(zoom*abs(u)*sin(v));
		answer.push_back(zoom*pow(abs(u), n)*(cos(v*n)));
		if (colorCode == true) {
			tp1.push_back((pow(abs(u), n)*sin(v*n)));
		}
	}

	if (functionSelection == 3) {
		//Complex Exponential function
		//============================				
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*(exp(u)*cos(v)));
		if (colorCode == true) {
			tp1.push_back((exp(u)*sin(v)));
		}
	}

	if (functionSelection == 4) {
		/*log(z) function
		=================
		Uses the trick that for complex variables w,z, w = ln(z).  then, e^w = z.
		From this, we can apply values of w as the x-y axis, use z.Re for the z-axis,
		and use u as the imaginary value for coloration.  The plot will come out perfectly.*/
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*log(hypot(u,v)));
		if (colorCode == true) { 
			for (int p = 0; p <= nBound; ++p) {
				tp1.push_back(atan2(v,u));
			}
		}
	}

	if (functionSelection == 5) {
		//arg(z) function
		//===============
		period = 2.0f;
		double r = zoom*sqrt(u*u+v*v);
		double theta = zoom*atan2(v, u);
			answer.push_back(r*cos(theta));
			answer.push_back(r*sin(theta));
			answer.push_back(theta);
			tp1.push_back(1.0f);
	}

	if(functionSelection==6){
		//cos(z) function
		//===============
		answer.push_back(zoom*0.5*v);
		answer.push_back(zoom*0.5*u);
		answer.push_back(zoom*0.5*cos(u)*cosh(v));
		if (colorCode == true) { tp1.push_back(-sin(u)*sinh(v)); }

		//alt definition:
		/*answer[0] = zoom*v;
		answer[1] = zoom*u;
		answer[2] = zoom*0.5*(exp(v)+exp(-v))*cos(u);
		if (colorCode == true) { tp1 = 0.5*(exp(-v)-exp(v))*sin(u); }*/
	}

	if (functionSelection == 7) {
		//sin(z) function
		//===============
		answer.push_back(zoom*0.5*v);
		answer.push_back(zoom*0.5*u);
		answer.push_back(zoom*0.5*sin(u)*cosh(v));
		if (colorCode == true) { tp1.push_back(cos(u)*sinh(v)); }

		//alt definition:
		/*answer[0] = zoom*v;
		answer[1] = zoom*u;
		answer[2] = zoom*0.5*(exp(v)-exp(-v))*cos(u);
		if (colorCode == true) { tp1 = -0.5*(exp(v)+exp(-v))*sin(u); }*/
	}

	if (functionSelection == 8) {
		//cosh(z) function
		//================
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*cosh(u)*cos(v));
		if (colorCode == true) { tp1.push_back(sinh(u)*sin(v)); }
	}

	if (functionSelection == 9) {
		//sinh(z) function
		//================
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*sinh(u)*cos(v));
		if (colorCode == true) { tp1.push_back(cosh(u)*sin(v)); }
	}

	if (functionSelection == 10) {
		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*u*v);
		if (colorCode == true) {
			tp1.push_back(u*v);
		}
	}

	if (functionSelection == 11) {
		//sqrt((z-1)(z-2)) function
		//================
		float a = ((u*u) - (3 * u) + 2 - (v*v));
		float b = v*((2 * u) - 3);
		float mod = hypot(a, b);
		float arg = atan2(b, a);

		answer.push_back(zoom*u);
		answer.push_back(zoom*v);
		answer.push_back(zoom*sqrt(mod));
		if (colorCode == true) {
			tp1.push_back(exp(0.5*arg));
		}
	}

	if (functionSelection == 12) {
		//arcsin(z) function
		//================
		//Uses f(z) = -i( ln(iz + sqrt(1-z^2) ) which, with some substitution,
		//breaks into f(w) = arg(w) - i * log|w|, where w is a complex number comprised of
		//many substituted terms from the original f(z) function.
		period = 2.0f;
		double x1 = 1 - (u*u) + (v*v);
		double y1 = -2 * u*v;
		double mod1 = sqrt((x1*x1) + (y1*y1));
		double arg1 = atan2(y1, x1);
		double arg2 = arg1 + (2 * PI);
		double x2 = -v + sqrt(mod1)*cos(0.5*arg1);
		double y2 = u + sqrt(mod1)*sin(0.5*arg1);
		double x2_2 = -v + sqrt(mod1)*cos(0.5*arg2);
		double y2_2 = u + sqrt(mod1)*sin(0.5*arg2);

		answer.push_back(zoom *-u);
		answer.push_back(zoom *v);
		answer.push_back(atan2(zoom*y2, zoom*x2));

		answer.push_back(zoom *-u);
		answer.push_back(zoom *v);
		answer.push_back((atan2(zoom*y2_2, zoom*x2_2)));
		if (colorCode == true) {
			for (int p = 0; p <= nBound; ++p) {
				tp1.push_back(-log(hypot(x2, y2)));
				tp1.push_back(-log(hypot(x2_2, y2_2)));
			}
		}
	}

	if (functionSelection == 13) {
		// Moebius strip
		// =============
		float R1 = 2;
		float R2 = 2;
		answer.push_back(zoom * u*cos(v*0.5));
		answer.push_back(zoom * (R1 + (0.5*u*sin(v*0.5)))*cos(v));
		answer.push_back(zoom * (R2 + (0.5*u*sin(v*0.5)))*sin(v));
		tp1.push_back(1.0f);
	}

	if (functionSelection == 14) {
		// Boy's Surface
		// =============
		float x = cos(u)*sin(v);
		float y = sin(u)*sin(v);
		float z = cos(v);
		float R = 4;
		answer.push_back(zoom*R * zoom * 0.5 *(((2 * x*x - y*y - z*z) * (x*x + y*y + z*z)) + ((2 * y*z)*(y*y - z*z)) + (z*x*(x*x - z*z)) + (x*y*(y*y - x*x))));
		answer.push_back(zoom*R * zoom * (sqrt(3)*0.5) * (((y*y - z*z)*(x*x + y*y + z*z)) + (z*x*(z*z - x*x) + x*y*(y*y - x*x))));
		answer.push_back(zoom*R * zoom * ((1 / 8.0)*(x + y + z)) * ((pow(x + y + z, 3)) + (4 * (y - x)*(z - y)*(x - z))));
		tp1.push_back(1.0f);
	}

	if (functionSelection == 15) {
		// Paraboloid	(V = 0.5*PI*h*r^2)
		// ==========
		float r = 1;	//radius = 1
		float h = 1;   //height = 1
		answer.push_back(zoom*r * sqrt(u/h) *cos(v));
		answer.push_back(zoom*r * sqrt(u/h) *sin(v));
		answer.push_back(zoom*u);
		tp1.push_back(1.0f);
	}

	if (functionSelection == 16) {
		// Sphere
		// ======
		float R = 2;
		answer.push_back(zoom*R*cos(u)*cos(v));
		answer.push_back(zoom*R*sin(u)*cos(v));
		answer.push_back(zoom*R*1.5708*sin(v));
		tp1.push_back(1.0f);
	}

	if (functionSelection == 17) {
		// Dini's Surface
		// ============
		float a = 1;
		float b = 0.2;
		answer.push_back(zoom*a*cos(u)*sin(v));
		answer.push_back(zoom*a*sin(u)*sin(v));
		answer.push_back(zoom*(a*(cos(v)+ log(tan(0.5*v))) + (b*u)) );
		tp1.push_back(1.0f);
	}

	if (functionSelection == 18) {
		// Torus
		// =====
		float c = 2;	//distance from center of torus to ring
		float a = 1;	//width of ring
		answer.push_back(zoom*a*sin(v));
		answer.push_back(zoom*(c + a*cos(v))*cos(u));
		answer.push_back(zoom*(c + a*cos(v))*sin(u));
		tp1.push_back(1.0f);
	}

	if (functionSelection == 19) {
		// Breather Surface
		// ================
		float c = 0.9;
		float psi = -u / sqrt(c + 1) + atan(tan(u)*sqrt(c + 1));
		float a = 2.0/(c + 1 - c*pow(sin(v),2)*cos(u));
		float r = a*sqrt((c + 1)*(1 + c*pow(sin(u),2)))*sin(v)/sqrt(c);
		answer.push_back(zoom*(log(tan(v / 2.0)) + a*(c + 1)*cos(v) / sqrt(c)));
		answer.push_back(zoom*r*cos(psi));
		answer.push_back(zoom*r*sin(psi));
		tp1.push_back(1.0f);
	}

	if (functionSelection == 20) {

		//BLANK
		answer.push_back(u);
		answer.push_back(v);
		answer.push_back(v+u);
		tp1.push_back(1.0f);
	}

	//=============================================================================

	//End of pipeline -- fill colorArray if necesary
	if (colorCode == true) {
		if (tp1[0] != tp1[0] || abs(tp1[0]) > 9E36) {//discontinuity in f(z).Im
				std::vector<GLfloat> tp2;
				tp2.push_back(0.0f);
				tp2.push_back(0.0f);
				tp2.push_back(0.0f);
				colorArray.push_back(tp2);
				tp2.clear();
				tp1.erase(tp1.begin());
		}
		else if (tp1 == tp1) {
			while (tp1.size() > 0) {
				std::vector<GLfloat> tp2;
				if (colorMapNumber == 1) { tp2 = jetColormap(tp1[0], colorBound); }
				if (colorMapNumber == 2) { tp2 = dec2RGB(tp1[0], colorBound); }
				colorArray.push_back(tp2);
				tp2.clear();
				tp1.erase(tp1.begin());
			}
		}
	}
	return answer;
}

void graphRiemannSurface() {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;
	std::vector<float> temp;
	
		for (float j = 0; j <= vbound; j += vStep) {
			for (float i = 0; i <= ubound; i += uStep) {
				
				//establish bounds
				//================
				double r = hypot(i, j);
				double theta = atan2(j, i);
				//if (r <= 1 && r >= 0 && theta >= 0 && theta <= PI) {
				if(r<=1){

					if (i == 0 && j == 0) {
						temp = functRiemannSurface(i, j);
						if (temp.size() != NULL) {
							while (temp.size() >= 3) {
								for (int p = 0; p <= nBound; ++p) {
									XVec.push_back(temp[0]);
									YVec.push_back(temp[1]);
									ZVec.push_back(temp[2] + p*period*PI);
								}
								temp.erase(temp.begin());
								temp.erase(temp.begin());
								temp.erase(temp.begin());
							}
						}
					}

					else {
						temp = functRiemannSurface(i, j);
						if (temp.size() != NULL) {
							while (temp.size() >= 3) {
								for (int p = 0; p <= nBound; ++p) {
									XVec.push_back(temp[0]);
									YVec.push_back(temp[1]);
									ZVec.push_back(temp[2] + p*period*PI);
								}
								temp.erase(temp.begin());
								temp.erase(temp.begin());
								temp.erase(temp.begin());
							}
						}
						temp = functRiemannSurface(-i, -j);
						if (temp.size() != NULL) {
							while (temp.size() >= 3) {
								for (int p = 0; p <= nBound; ++p) {
									XVec.push_back(temp[0]);
									YVec.push_back(temp[1]);
									ZVec.push_back(temp[2] + p*period*PI);
								}
								temp.erase(temp.begin());
								temp.erase(temp.begin());
								temp.erase(temp.begin());
							}
						}
						temp = functRiemannSurface(-i, j);
						if (temp.size() != NULL) {
							while (temp.size() >= 3) {
								for (int p = 0; p <= nBound; ++p) {
									XVec.push_back(temp[0]);
									YVec.push_back(temp[1]);
									ZVec.push_back(temp[2] + p*period*PI);
								}
								temp.erase(temp.begin());
								temp.erase(temp.begin());
								temp.erase(temp.begin());
							}
						}
						temp = functRiemannSurface(i, -j);
						if (temp.size() != NULL) {
							while (temp.size() >= 3) {
								for (int p = 0; p <= nBound; ++p) {
									XVec.push_back(temp[0]);
									YVec.push_back(temp[1]);
									ZVec.push_back(temp[2] + p*period*PI);
								}
								temp.erase(temp.begin());
								temp.erase(temp.begin());
								temp.erase(temp.begin());
							}
						}
					}
				}
			}
		}

	temp.clear();
	domain.push_back(YVec);
	domain.push_back(ZVec);
	range = XVec;
}

std::vector<float> functParametric(float t) {
	std::vector<float> answer;
	answer.push_back(sin(2.3*t));
	answer.push_back(sin(1.1*t));
	answer.push_back(t/8);
	return answer;
}

std::vector<float> functParametricSurface(float u, float v) {
	std::vector<float> answer;
	answer.push_back(-sqrt(1 / tgamma(u)));
	answer.push_back(2*(cos(u)/tgamma(v)));
	answer.push_back(u * sin(v / 2));
	return answer;
}

void graph2DFunction() {
		std::vector<std::vector<float>> xyz;
		std::vector<float> XVec;
		std::vector<float> YVec;
		std::vector<float> ZVec;

		float xbound = 15;
		float distanceBetweenPoints = 0.003;
		if (graphAs == "points") {
			for (float i = -xbound; i < xbound; i += distanceBetweenPoints) {
				float temp = funct2(i);		
				XVec.push_back(i);
				YVec.push_back(temp);
				ZVec.push_back(0.0000001);
			}
		}

	domain.push_back(XVec);
	domain.push_back(YVec);
	range = ZVec;
}

float funct2(float x) {
			return tan(x)+atan(x);
		}

float funct1(float x, float y) {
	return sqrt(pow((sin(cos(tan(acos(y / x))))),2));	//paraboloid
}

void DrawGrid() {
	glMatrixMode(GL_MODELVIEW);		// Define the modelview transformation.
	glLoadIdentity();
	glRotatef(ang1, 0.0f, 0.0f, 0.000000001f);	//rotate around x axis
	glRotatef(ang2, 0.0f, 0.000000001f, 0.0f);	//y axis
	glRotatef(ang3, 0.000000001f, 0.0f, 0.0f);	//and now z axis
	glTranslatef(xpos, ypos, -2.0f + zpos);	// move the viewpoint out to where we can see everything
	float inc = 1;
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_LINE_LOOP);
	for (float i = -2*gridSize; i <= 2*gridSize; i += zoom*(inc+1)) {
		glVertex3i(-gridWidth, i, -gridWidth);
		glVertex3i(-gridWidth, i, gridWidth);
		glVertex3i(-gridWidth, i, gridWidth);
		glVertex3i(gridWidth, i, gridWidth);
		glVertex3i(gridWidth, i, -gridWidth);
		glVertex3i(-gridWidth, i, -gridWidth);
	}
	glVertex3i(-gridWidth, -2*gridWidth, -gridWidth);
	for (float i = -gridSize; i <= gridSize; i += zoom*(inc)) {
		glVertex3i(i, -2*gridWidth, -gridWidth);
		glVertex3i(i, 2*gridWidth, -gridWidth);
		glVertex3i(i, 2*gridWidth, gridWidth);
		glVertex3i(i, -2*gridWidth, gridWidth);
		glVertex3i(i, -2*gridWidth, -gridWidth);
		glVertex3i(i, -2*gridWidth, -gridWidth);
	}
	glVertex3i(-gridWidth, -2*gridWidth, -gridWidth);
	for (float i = -gridSize; i < gridSize; i += zoom*(inc)) {
		glVertex3i(-gridWidth, -2*gridWidth, i);
		glVertex3i(-gridWidth, 2*gridWidth, i);
		glVertex3i(gridWidth, 2*gridWidth, i);
		glVertex3i(gridWidth, -2*gridWidth, i);
		glVertex3i(-gridWidth, -2*gridWidth, i);
		glVertex3i(-gridWidth, -2*gridWidth, i);
	}
	glVertex3i(-gridWidth, -2*gridWidth, -gridWidth);
	glEnd();
	glFlush();
}

bool toggleState(bool A) {
	if (A == false) { return true; }
	else { return false; }
}

std::string toggleGraphAs(std::string A) {
	std::string temp = "";
	if (A == "points") { temp = "lines"; return temp; }
	if (A == "lines") { temp = "squares"; return temp;}
	if (A == "squares") { temp = "triangles"; return temp;}
	if (A == "triangles") { temp = "polygon"; return temp;}
	if (A == "polygon") { temp = "points"; return temp; }
	else { return temp; }
}

void getTxtPointcloud(std::string filename) {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;

	float scale = 2.0;

	std::vector<double> vec = readTxtFile(filename);
	for (int i = 0; i < vec.size(); i+=3) {
		XVec.push_back(vec[i]/scale);
		YVec.push_back(vec[i+1]/scale);
		ZVec.push_back(vec[i+2]/scale);
	}

	domain.push_back(XVec);
	domain.push_back(YVec);
	range = ZVec;
}

void getTxtColorcloud(std::string filename) {
	std::vector<double> vec = readTxtFile(filename);
	for (int i = 0; i < vec.size(); i += 3) {
		std::vector<GLfloat> tempVec;
		tempVec.push_back(vec[i]);
		tempVec.push_back(vec[i + 1]);
		tempVec.push_back(vec[i + 2]);
		colorArray.push_back(tempVec);
	}
}

void getPlyPointcloud(std::string filename) {
	std::vector<float> XVec;
	std::vector<float> YVec;
	std::vector<float> ZVec;

	int numVerts = model.entry(filename);

	for (int i = 0; i < count_vertex; ++i) {
		readPly rp = vertices[i];
		float x, y, z;
		x = (float)(rp.getter(0));
		y = (float)(rp.getter(0));
		z = (float)(rp.getter(0));

		//shrink scale
		float scale = 1.0;
		x /= scale;
		y /= scale;
		z /= scale;

		if (x == 0 && y == 0 && z == 0) {// numVerts = -1;
	}//not a valid point
		else {
			XVec.push_back(x);
			YVec.push_back(y);
			ZVec.push_back(z);
		}
	}

	domain.push_back(YVec);
	domain.push_back(ZVec);
	range = XVec;
}

void writeVertices(std::string filename) {
	std::wstring str = L"";
	std::wofstream outf2(filename, std::ios_base::out);//open .txt file to write
	for (int i = 0; i < domain.size(); ++i) {
		str = L"v ";
		str.append(to_stringPrecision(domain[0][i]));
		str.append(to_stringPrecision(domain[1][i]));
		str.append(to_stringPrecision(range[i]));
		str.append(L"\n");
		outf2 << str;
		str.clear();
	}
	for (int i = 0; i < XVecNorm.size(); ++i) {
		str = L"vn ";
		str.append(to_stringPrecision(XVecNorm[i]));
		str.append(to_stringPrecision(YVecNorm[i]));
		str.append(to_stringPrecision(ZVecNorm[i]));
		str.append(L"\n");
		outf2 << str;
		str.clear();
	}
	outf2.close();
}