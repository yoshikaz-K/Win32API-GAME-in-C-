#include "Interface.h"

Status status;

/* シーケンス遷移 */
static bool logo = false;
static bool title = false;
static bool game = false;

/* PLAYER 座標　初期化 */
static int PlayerX = 1;
static int PlayerY = 1;

/* PLAYER 移動量　初期化 */
static int MoveX = 32;
static int MoveY = 32;

/* 簡易アニメーション */
static DWORD animation = 0; /* アニメ用変数　初期値はゼロ */
static DWORD muki = 0; /* キャラチップの向き　初期値ゼロ */

/* ウィンドウプロシジャ */
LRESULT CALLBACK _window_procedure(HWND hWnd, UINT messages, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect = {};

	/* Create 領域は捨てる */
	switch (messages)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;;
	case WM_DESTROY:
		CloseWindow(hWnd);
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
	{
			/* ロゴモードを最初に */
			logo = true;

			/* ボタンコントロール*/
			//int i;
			//int j = 10;
			//int bx = 0, by = 30;

			/* ↑ボタン定義 */
			MouseButton[0] = CreateWindow(
				TEXT("BUTTON"),
				TEXT(""),
				WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				760, 20,
				100, 30,
				hWnd, (HMENU)ID_BUTTON_0,
				((LPCREATESTRUCT)(lParam))->hInstance, NULL
			);

			/* ←ボタン定義 */
			MouseButton[1] = CreateWindow(
				TEXT("BUTTON"),
				TEXT(""),
				WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				710, 50,
				100, 30,
				hWnd, (HMENU)ID_BUTTON_1,
				((LPCREATESTRUCT)(lParam))->hInstance, NULL
			);

			/* →ボタン定義 */
			MouseButton[2] = CreateWindow(
				TEXT("BUTTON"),
				TEXT(""),
				WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				810, 50,
				100, 30,
				hWnd, (HMENU)ID_BUTTON_2,
				((LPCREATESTRUCT)(lParam))->hInstance, NULL
			);

			/* ↓ボタン定義 */
			MouseButton[3] = CreateWindow(
				TEXT("BUTTON"),
				TEXT(""),
				WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				760, 80,
				100, 30,
				hWnd, (HMENU)ID_BUTTON_3,
				((LPCREATESTRUCT)(lParam))->hInstance, NULL
			);

			/* ボタンを　９個　配列 for文で描画 */
			//for (i = 0; i < 9; i++)
			//{
			//	view.Button[i] = CreateWindow(
			//		TEXT("BUTTON"),
			//		view.szText[i],
			//		WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			//		560 + bx, 5 + by, //ボタンの位置
			//		100, 30,//ボタンの大きさ
			//		hWnd, (HMENU)j,
			//		((LPCREATESTRUCT)(lParam))->hInstance, NULL
			//	);
				/* ボタンのy位置　を更新 */
			//	by += 30;
			//	j++;
			//}
		}
		return 0;

	/* ボタンが　押されたら... */
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_0:
			//ボタンが押されたときの処理
			PlayerY -= MoveY;

			muki = 3;

			/* クリッピングリージョンの再描画 */
			//InvalidateRgn(hWnd, view.hRgn, FALSE);
			break;
		case ID_BUTTON_1:
			PlayerX -= MoveX;

			muki = 1;

			/* 再描画 */
			//InvalidateRgn(hWnd, view.hRgn, FALSE);
			break;
		case ID_BUTTON_2:
			PlayerX += MoveX;

			muki = 2;

			/* 再描画 */
			//InvalidateRgn(hWnd, view.hRgn, FALSE);
			break;
		case ID_BUTTON_3:
			PlayerY += MoveY;

			muki = 0;

			break;
		}
		/* クリッピングリージョンの再描画 */
		InvalidateRgn(hWnd, hRgn, FALSE);
		return 0;

		/* オーナー描画ボタン　色の設定 */
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;

		if (pDIS->CtlType == ODT_BUTTON)
		{
			// 背景色を設定
			//SetBkColor(pDIS->hDC, RGB(0, 0, 0));
			//FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(0, 0, 0)));

			/* 枠線を描画 */
			//FrameRect(pDIS->hDC, &pDIS->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));

			// テキストを描画
			//int i;
			//for (i = 0; i < 9; i++)
			//{
			//	SetTextColor(pDIS->hDC, RGB(255, 255, 255));
			//	DrawText(pDIS->hDC, view.szText[i], -1,
			//		&pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//}

			// 背景色を設定
			SetBkColor(pDIS->hDC, RGB(0, 0, 0));
			FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(0, 0, 0)));

			/* 枠線を描画 */
			FrameRect(pDIS->hDC, &pDIS->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));

			SetTextColor(pDIS->hDC, RGB(255, 255, 255));

			switch(pDIS->CtlID)
			{
			case ID_BUTTON_0:
				DrawText(pDIS->hDC, TEXT("↑"), -1,
					&pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case ID_BUTTON_1:
				DrawText(pDIS->hDC, TEXT("←"), -1,
					&pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case ID_BUTTON_2:
				DrawText(pDIS->hDC, TEXT("→"), -1,
					&pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case ID_BUTTON_3:
				DrawText(pDIS->hDC, TEXT("↓"), -1,
					&pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}
		break;
	}
	return 0;

	/* WM_PAINT 描画 */
	case WM_PAINT:
	{
		GetClientRect(hWnd, &rect);

		hdc = BeginPaint(hWnd, &ps);

		/********************************************/
		/* WM_PAINT は　画面全体を　書き換えてしまう*/
		/* 従って　メインの　画面は 別プロセス　にする */
		if (logo)_Method_Window_DrawLogoMode(hdc, rect.right, rect.bottom);
		else if (title)_Method_Window_DrawTitleMode(hdc, rect.right, rect.bottom);

		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_LBUTTONUP:
		/* クリック通知により　画面遷移を実行 */
		if (logo)
		{
			logo = false;
			title = true;
		}
		else if (title)
		{
			title = false;
			game = true;
		}
		else if (game)
		{
			game = false;
			logo = true;
		}
		/* WM_PAINT を　発行させ　再描画 */
		InvalidateRect(hWnd, NULL, TRUE); //ここはTRUE
		return 0;
	}
	return DefWindowProc(hWnd, messages, wParam, lParam);
}

/* 下記からゲームメイン　処理 */

/* 仮想ウィンドウ　定義 */
/* 画像処理 */
static HDC BackScreen;
static HBITMAP hBitmapScreen;

void _Method_Window_DrawLogoMode(HDC hdc, DWORD width, DWORD height)
{
	RECT rect = { 0 };

	/* ボタンを　不可視 */
	int i;
	for (i = 0; i < 4; i++)
	{
		if (IsWindowVisible(MouseButton[i])) 
			ShowWindow(MouseButton[i], SW_HIDE);
	}

	rect.right = width;
	rect.bottom = height;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 0, 0));
	DrawText(hdc, TEXT("ロゴモード"), -1, &rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void _Method_Window_DrawTitleMode(HDC hdc, DWORD width, DWORD height)
{
	RECT rect = { 0 };

	/* ボタンを　不可視 */
	int i;
	for (i = 0; i < 4; i++)
	{
		if (IsWindowVisible(MouseButton[i])) 
			ShowWindow(MouseButton[i], SW_HIDE);
	}

	rect.right = width;
	rect.bottom = height;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 255, 0));
	DrawText(hdc, TEXT("タイトルモード"), -1, &rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void _Method_Window_DrawGameMode(HWND hWnd, DWORD width, DWORD height)
{
	/* カウント　文字列 */
	TCHAR time_Text[255];

	static DWORD frames = 0;
	static DWORD beforeTime = 0;
	DWORD nowTime, progress;

	/* リージョンクリッピングを作成する */
	RECT rect;
	rect.right = width;
	rect.bottom = height;

	/* ボタンを for文で 連続 表示 */
	int i;
	for (i = 0; i < 4; i++)
	{
		/* ボタンを i個　表示 */
		ShowWindow(MouseButton[i], SW_SHOW);
	}

	/*******************************************************
	/* 画像処理を先に行う
	/*******************************************************
	/* 画像ファイル　ロード */
	HBITMAP hBitmap = (HBITMAP)LoadImage(
		NULL, TEXT("char1.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE
	);

	HBITMAP hMap = (HBITMAP)LoadImage(
		NULL,
		TEXT("G.bmp"),
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE
	);

	HBITMAP hMap2 = (HBITMAP)LoadImage(
		NULL,
		TEXT("map_grid.bmp"),
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE
	);

	/* 時間処理 */
	if (beforeTime == 0) beforeTime = timeGetTime();

	HDC hdc = GetDC(hWnd);

	GetClientRect(hWnd, &rect);

	// 重要　背景を塗りつぶす
	//FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 3));

	/* 仮想ウィンドウを作成 */
	BackScreen = CreateCompatibleDC(hdc);
	hBitmapScreen = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(BackScreen, hBitmapScreen);
	/* ビットマップ・メモリ上の仮想デバイスを選択 */
	HDC MemDC = CreateCompatibleDC(BackScreen);

	nowTime = timeGetTime();
	progress = nowTime - beforeTime;

	/**************************************************/
	/* MAP TILE 描画                                  */
	/**************************************************/

	/* SelectObject MAP data は　ここに記述する */
	SelectObject(MemDC, hMap);

	/* 裏画面へ転送 */
	BitBlt(
		BackScreen,
		0, /* マップスクロール 計算式 */
		0, /* マップスクロール 計算式 */
		800,
		600,
		MemDC,
		0,
		0,
		SRCCOPY
	);

	/* マップデータ画像　描画 */
	for (int i = 0; i <= MAX_WIDTH; i++)
	{
		for (int j = 0; j <= MAX_HEIGHT; j++)
		{
			if (MapData[j][i] == 0)
			{
				/* SelectObject MAP data は　ここに記述する */
				SelectObject(MemDC, hMap2);

				/* 裏画面へ転送 */
				TransparentBlt(
					BackScreen,
					i * CHIP_SIZE, /* マップスクロール 計算式 */
					j * CHIP_SIZE, /* マップスクロール 計算式 */
					CHIP_SIZE,
					CHIP_SIZE,
					MemDC,
					0,
					0,
					CHIP_SIZE,
					CHIP_SIZE,
					RGB(0, 0, 0)
				);
			}

			if (MapData[j][i] == 1)
			{
				/* PLAYER 描画 */
				SelectObject(MemDC, hBitmap);
				TransparentBlt(
					BackScreen,
					i + PlayerX + MoveX,
					j + PlayerY + MoveY,
					CHIP_SIZE,
					CHIP_SIZE,
					MemDC,
					PLAYER_CHIP_SIZE * animation, // 転送元wにアニメーションをかける
					PLAYER_CHIP_SIZE * muki, // 転送元hに向きをかける
					PLAYER_CHIP_SIZE,
					PLAYER_CHIP_SIZE,
					RGB(255, 255, 255)
				);
			}
		}
	}

	/**********************************************************/
	/* MAP TILE 描画　ここまで                                */
	/**********************************************************/
	//
	/*******************************************************
	/* 画像処理はここまで
	/*******************************************************/

	/* FPS　計測 */
	if (frames * (1000.0 / 60) > progress)
	{
		Sleep(frames * (1000.0 / 60) - progress);
	}

	if (progress >= 1000) /* １秒以上経過したら */
	{
		/* 時間更新 */
		beforeTime = nowTime;

		/* animation 変数をインクリメント */
		++animation;
		/* animation 変数が4のとき、animation変数を初期値へ戻す */
		if (animation == FRAME_COUNT) animation = 0;

		frames = 0;
	}
	frames++;

	/**************************************************************/
	/* FPS　表示(描画) */
	wsprintf(time_Text, TEXT("FRAME:%d"), frames);
	SetBkMode(BackScreen, TRANSPARENT);
	SetTextColor(BackScreen, RGB(255, 255, 255));
	TextOut(BackScreen, 10, 10, time_Text, lstrlen(time_Text));

	/* STATUS 表示（描画）*/
	status.StatusDraw(hWnd, hdc);
	/**/
	/**************************************************************/
	/* 最期に記述する */
	/* 一括で描画 */
	/* 仮想ウィンドウを表ウィンドウへ転送 */
	/* クリッピングリージョン　含む */
	/**************************************************************/
	/* リージョンクリッピング　を作成 */
	hRgn = CreateRectRgn(10, 10, 520, 340);
	/* リージョンクリッピング　を関連付け */
	SelectObject(hdc, hRgn);
	/* 表画面（フロントバッファへ一括転送） */
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, BackScreen, 0, 0, SRCCOPY);
	/**************************************************************/

	/* キー入力　判定 関数*/
	//CheckKey(hWnd);

	/* 仮想ウィンドウを解放 */
	DeleteDC(MemDC);
	DeleteDC(BackScreen);
	DeleteObject(hBitmapScreen);

	/* dc を　解放 */
	ReleaseDC(hWnd, hdc);

	/* リージョンを破棄 */
	DeleteObject(hRgn);

	/* 読み込んだ画像を破棄 */
	DeleteObject(hBitmap);
	DeleteObject(hMap);
	DeleteObject(hMap2);
}

/* Clears a window to black */
void clear_window(HWND hWnd, int win_width, int win_height)
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);

	SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0));

	Rectangle(hdc, 0, 0, win_width, win_height);

	EndPaint(hWnd, &ps);
}

/* Key and Mouse Push to command... */

/* STATUS 描画 */
void Status::StatusDraw(HWND hWnd, HDC hdc)
{
	//RECT rect = { 0 };

	hdc = GetDC(hWnd);

	/* STATUS 表示 (描画) */
	_stprintf_s(szBuffer, TEXT("NAME : Thelema"));
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 360, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("Lv : %d   "), Lv);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 400, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("HP : %d   "), HP);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 420, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("SP : %d   "), SP);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 440, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("STR : %d   "), STR);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 460, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("RDM : %d   "), RDM);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 480, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("MND : %d   "), MND);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 500, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("TEC : %d   "), TEC);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 520, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("HIT : %d   "), HIT);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 540, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("AGI : %d   "), AGI);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 560, szBuffer, lstrlen(szBuffer));

	_stprintf_s(szBuffer, TEXT("EXP : %d   "), EXP);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 580, szBuffer, lstrlen(szBuffer));

	/* 表画面（フロントバッファへ一括転送） */
	//BitBlt(hdc, 0, 0, rect.right, rect.bottom, BackScreen, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = _window_procedure;
	w.lpszClassName = TEXT("Sample Game in C++ MVC");
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&w);

	HWND window = CreateWindowEx(
		0,
		w.lpszClassName,
		TEXT("--ITHELEMA--"),
		/* ウィンドウサイズを　固定　する */
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr
	);

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);
	SetFocus(window);

	MSG msg = {};

	IsRunning = true;

	/* MessageLoop */
	/* Game Loop */
	while (IsRunning)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				IsRunning = false;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ここは 別プロセスで起動　<-- WM_PAINT の影響を受けるため!
			// （if文でTRUEの場合、表示)
			//
			/* MessageLoop で処理する場合、*/
			/* いちいちWM_PAINT を呼び出すとちらつく（特にコントロールが）*/
			/* 従って、InvalidateRect()関数はここでは使用しない */
			if (game)_Method_Window_DrawGameMode(window, 520, 340);
		}
	}
	return (int)msg.wParam;
}
