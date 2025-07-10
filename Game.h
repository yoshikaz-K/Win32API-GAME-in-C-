/************************************************************************************/
/*     製作者　義和　                                                               */
/*    2025 / 07 / 06                                                                */
/************************************************************************************/

#pragma once
//#ifndef INCLUDED_Interface
//#define INCLUDED_Interface

#define NOMINMAX //max 予約語を使えるように設定
#pragma warning(disable:4996)

#include <Windows.h>
#include <windowsx.h>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <mmsystem.h>
#include <locale.h>
#include <string>

/* 透過処理を行う */
#pragma comment(lib, "Msimg32.lib")

/* 時間測定ライブラリ追加 */
#pragma comment(lib, "Winmm.lib")

/* std　名前空間 (C++)*/
using namespace std;

/* ウィンドウサイズ　定義 */
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 600

/* ボタンID　定義 */
#define ID_BUTTON_0 0
#define ID_BUTTON_1 1
#define ID_BUTTON_2 2
#define ID_BUTTON_3 3

/* チップ（グリッドサイズ）*/
#define CHIP_SIZE 32

/* プレイヤーチップサイズ */
#define PLAYER_CHIP_SIZE 64

/* キャラクター　フレームカウント */
#define FRAME_COUNT 4

/* MAP 定義 */
#define MAX_WIDTH 30
#define MAX_HEIGHT 30

/* ボタン　コントロール */
HWND MouseButton[4];
HWND Button[9];

/* ゲームループ用　変数フラグ */
bool IsRunning;

static int MapData[MAX_HEIGHT][MAX_WIDTH] = 
{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/* 各メンバ メソッド */
/* ウィンドウプロシジャ関連 */
LRESULT CALLBACK _window_procedure(HWND hWnd, UINT messages, WPARAM wParam, LPARAM lParam);
/* 各モード（メインゲームモード　含む) */
void _Method_Window_DrawLogoMode(HDC hdc, DWORD width, DWORD height);
void _Method_Window_DrawTitleMode(HDC hdc, DWORD width, DWORD height);
void _Method_Window_DrawGameMode(HWND hWnd, DWORD width, DWORD height);
/* Clears a window to black */
static void clear_window(HWND hWnd, int win_width, int win_height);

/*
LPCWSTR szText[9] = 
{
		TEXT("戦術行動")
		/*TEXT(" "),
		TEXT(" "),
		TEXT(" "),
		TEXT(" "),
		TEXT(" "),
		TEXT(" "),
		TEXT(" "),
		TEXT(" ")
};
*/

/* リージョンクリッピング　コントロール */
static HRGN hRgn = {};

/* ステータス　クラス */
class Status
{
private:
	/* 文字列のバッファ　確保 */
	TCHAR szBuffer[40] = {};

public:
	//TCHAR name[12] = TEXT("Thelema"); //名前

	/* 各ステータス 定義 */
	int Lv = 1; //LEVEL
	int HP = 10; //HIT POINT
	int SP = 5; // SKILL POINT
	int STR = 1; // 攻撃力
	int RDM = 1; // 防御力
	int MND = 1; // 精神力
	int TEC = 1; // 技術力
	int HIT = 1; // 命中力
	int AGI = 0; // 回避力
	int EXP = 0; // 経験値

	/* ステータス　表示メソッド */
	void StatusDraw(HWND hWnd, HDC hdc);
};

//#endif
