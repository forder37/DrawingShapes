// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "DrawingShapes.h"


struct Shape
{
    virtual ~Shape() {}
    virtual void draw(HDC hdc)
    {
    }
};
struct Point
{
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_)
    {
    }
    int x;
    int y;
};
struct Rectangle_ : Shape
{
    Rectangle_(Point LeftTopPoint_, int width_, int height_) : LeftTopPoint(LeftTopPoint_), width(width_), height(height_)
    {
    }
    Rectangle_(int xLeftTop, int yLeftTop, int width_, int height_) : LeftTopPoint(xLeftTop, yLeftTop), width(width_), height(height_)
    {        
    }
    void draw(HDC hdc)
    {
        MoveToEx(hdc, LeftTopPoint.x, LeftTopPoint.y, 0);
        LineTo(hdc, LeftTopPoint.x + width, LeftTopPoint.y);
        LineTo(hdc, LeftTopPoint.x + width, LeftTopPoint.y + height);
        LineTo(hdc, LeftTopPoint.x, LeftTopPoint.y + height);
        LineTo(hdc, LeftTopPoint.x, LeftTopPoint.y);
    }
private:
    Point LeftTopPoint;
    int width;
    int height;
};
struct Triangle_ : Shape
{
    Triangle_(Point point1_, Point point2_, Point point3_) : point1(point1_), point2(point2_), point3(point3_)
    {
    }
    Triangle_(int x1, int y1, int x2, int y2, int x3, int y3) : point1(x1, y1), point2(x2, y2), point3(x3, y3)
    {
    }
    void draw(HDC hdc)
    {
        MoveToEx(hdc, point1.x, point1.y, 0);
        LineTo(hdc, point2.x, point2.y);
        LineTo(hdc, point3.x, point3.y);
        LineTo(hdc, point1.x, point1.y);
    }
private:
    Point point1;
    Point point2;
    Point point3;
};
struct Square_ : Shape
{
    Square_(Point LeftTopPoint_, int lenght_) : LeftTopPoint(LeftTopPoint_), length(lenght_)
    {
    }
    Square_(int xLeftTop, int yLeftTop, int length_ ) : LeftTopPoint(xLeftTop, yLeftTop), length(length_)
    {
    }
    void draw(HDC hdc)
    {
        MoveToEx(hdc, LeftTopPoint.x, LeftTopPoint.y, 0);
        LineTo(hdc, LeftTopPoint.x + length, LeftTopPoint.y);
        LineTo(hdc, LeftTopPoint.x + length, LeftTopPoint.y + length);
        LineTo(hdc, LeftTopPoint.x, LeftTopPoint.y + length);
        LineTo(hdc, LeftTopPoint.x, LeftTopPoint.y);
    }

private:
    Point LeftTopPoint;
    int length;
};
struct Circle_ : Shape
{
    Circle_(Point Center_, int Radius_) : Center(Center_), Radius(Radius_)
    {
    }
    Circle_(int xCenter, int yCenter, int Radius_) : Center(xCenter, yCenter), Radius(Radius_)
    {
    }
    void draw(HDC hdc)
    {
        Ellipse(hdc, Center.x - Radius, Center.y - Radius, Center.x + Radius, Center.y + Radius);
    }
private:
    Point Center;
    int Radius;

};
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...   
            Shape* object[8];
            int N_obj = 8;
            object[0] = new Rectangle_(20, 200, 170, 30);
            object[1] = new Triangle_(0, 0, 300, 300, 150, 20);
            object[2] = new Square_(300, 100, 200);
            object[3] = new Circle_(400, 200, 50);
            object[4] = new Circle_(700, 300, 200);
            object[5] = new Triangle_(400, 200, 50, 200, 70, 130);
            object[6] = new Square_(100, 200, 350);
            object[7] = new Rectangle_(100, 20, 500, 40);
            for (int i = 0; i < N_obj; ++i)
            {
                object[i]->draw(hdc);
                delete object[i];
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
