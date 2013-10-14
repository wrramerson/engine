#ifdef _WIN32

#pragma once

#include <Windows.h>
#include "BaseGame.h"
#include "Context.h"

namespace star
{
	class TimeManager;
	class TextureManager;

	class Window final
	{
	public:
		static Window * GetInstance();

		~Window(void);

		void Initialize(HINSTANCE instance, BaseGame * pBaseGame);

		void WindowInactiveUpdate(bool inactive);
		const tstring & GetAssetRoot() const;
		const HDC & GetHDC() const;
		const HWND & GetHandle() const;
		void CalculateRect(RECT & rect);
		void SetClipRect(const RECT & rect);

		bool IsInitialized() const { return m_IsInitialized; }
		bool IsCursorClipped() const;
		bool IsFullScreen() const { return m_IsFullScreen; }
		bool CanGoFullScreen() const { return m_CanGoFullScreen; }
		bool IsActive() const { return m_IsActive; }
		bool UpdateGameWhenInactive() const { return m_UpdateGameWhenInactive; }
		bool ChangeResolutionWhenGoingFullScreen() const { return m_ManipulateWindowResolution; }

		void ToggleFullScreen(HWND hWnd);
		void SetFullScreen(HWND hWnd, bool fullscreen);
		void UpdateClippingIfNeeded();
		void SetWindowMoved();
		void SetWindowActive(bool active);

		void SetResolution(int width, int height);

	private:
		Window();

		HWND GetConsoleHWND();
		void SetWindowsTitle() const;

		static Window *m_pInstance;

		bool m_IsInitialized;
		bool m_IsFullScreen;
		bool m_CanGoFullScreen;
		bool m_WindowMoved;
		bool m_IsActive;
		bool m_UpdateGameWhenInactive;
		bool m_ManipulateWindowResolution;

		struct WindowState
		{
			BOOL Maximized;
			long Style, ExStyle;
			RECT WinRect;
		};

		WindowState m_SavedWindowState;

		BaseGame* mGamePtr;
		TimeManager* mTimeManager;
		Context mContext;

		HWND mHandle;
		HGLRC mOGLContext;
		HDC mHDC;
		RECT mClipRect;
		tstring mAssetsRoot;

		static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

		static const uint32 CLASS_STYLES_COUNT = 5;
		static const uint32 WINDOW_STYLES_COUNT = 28;

		typedef std::pair<tstring, uint32> psip;
		static const psip CLASS_STYLES[];
		static const psip WINDOW_STYLES[];

		int CastStringToClassStyle(const tstring & style);
		int CastStringToWinStyle(const tstring & style);

		Window & operator=(const Window&);
		Window(const Window&);
		Window(Window&&);
	};

	void UpdateWindowClipping(HWND hWnd);
}
#endif
