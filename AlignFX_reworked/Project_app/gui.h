#pragma once


#include <d3d9.h>


namespace gui {

	//Const to hold window sizes

	constexpr int WIDTH = 500;
	constexpr int HIGHT = 300;

	inline bool exit = true;


	//winapi window vars
	inline HDWP window = nullptr;
	inline WNDCLASSEXA windowClass = { };

	// points to move window

	inline POINTS position = { };


	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

}