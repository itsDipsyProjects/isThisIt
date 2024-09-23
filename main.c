#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Helper function to set up the OpenGL rendering context
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    // Get the device context (DC)
    *hDC = GetDC(hWnd);

    // Set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    // Create and enable the OpenGL rendering context (RC)
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

// Helper function to clean up the OpenGL rendering context
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL quit = FALSE;
    float theta = 0.0f;

    // Register window class
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "OpenGLWinClass";
    RegisterClass(&wc);

    // Create the window
    hWnd = CreateWindow(
        "OpenGLWinClass", "OpenGL Window",
        WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
        100, 100, 640, 480,
        NULL, NULL, hInstance, NULL);

    // Enable OpenGL for the window
    EnableOpenGL(hWnd, &hDC, &hRC);

    // Program main loop
    while (!quit) {
        // Check for messages
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            // Handle or dispatch messages
            if (msg.message == WM_QUIT) {
                quit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            // OpenGL rendering code here
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Rotate a simple triangle
            glPushMatrix();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.5f, -0.5f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(0.5f, -0.5f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex2f(0.0f, 0.5f);
            glEnd();
            glPopMatrix();

            SwapBuffers(hDC);

            // Update rotation angle
            theta += 1.0f;
            Sleep(10);
        }
    }

    // Shutdown OpenGL
    DisableOpenGL(hWnd, hDC, hRC);

    // Destroy the window explicitly
    DestroyWindow(hWnd);

    return msg.wParam;
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_DESTROY:
            return 0;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
