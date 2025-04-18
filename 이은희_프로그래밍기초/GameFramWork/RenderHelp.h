#pragma once
#include "INC_Windows.h"

namespace renderHelp
{
    struct WICInitializer;

    class BitmapInfo
    {
    public:
        HBITMAP GetBitmapHandle() const { return m_hBitmap; }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }

    private:
        friend struct WICInitializer; // WICInitializer를 통해서만 bitmap을 생성,로드 할 수 있도록 함
        //한군데서만 생성 로드 삭제를 하도록 의도함.....

        BitmapInfo() = default;

        BitmapInfo(HBITMAP hBitmap)
        {
            m_hBitmap = hBitmap;
            BITMAP bitmap;
            GetObject(hBitmap, sizeof(BITMAP), &bitmap);
            m_width = bitmap.bmWidth;
            m_height = bitmap.bmHeight;
        }

        ~BitmapInfo()
        {
            if (m_hBitmap)
            {
                DeleteObject(m_hBitmap);
                m_hBitmap = nullptr;
            }
        }

    private:
        HBITMAP m_hBitmap = nullptr;
        BitmapInfo* m_pPrevLink = nullptr;

        int m_width = 0;
        int m_height = 0;

        BitmapInfo(const BitmapInfo&) = delete;
        BitmapInfo& operator=(const BitmapInfo&) = delete;
    };

    BitmapInfo* CreateBitmapInfo(LPCWSTR filename);

    BitmapInfo* CreateFlippedBitmap(BitmapInfo* pBitmapInfo);
}