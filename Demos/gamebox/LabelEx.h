#ifndef __LABELEX_H__
#define __LABELEX_H__

namespace DuiLib {
class CLabelIconUI : public DuiLib::CLabelUI
{
    DECLARE_DUICONTROL(CLabelIconUI)
public:
    CLabelIconUI()
    {
        m_hIcon = NULL;
    }
    ~CLabelIconUI(void)
    {
        if (m_hIcon != NULL)
            ::DestroyIcon(m_hIcon);
    }

public:
    virtual void PaintStatusImage(HDC hDC)
    {
        CLabelUI::PaintStatusImage(hDC);
        if (m_hIcon != NULL) {
            ICONINFO ii;
            if (::GetIconInfo(m_hIcon, &ii)) {
                BITMAP bmp;
                if (::GetObject(ii.hbmColor, sizeof(bmp), &bmp))
                    ::DrawIcon(hDC, m_rcItem.left + (m_rcItem.right - m_rcItem.left - bmp.bmWidth) / 2, m_rcItem.top + 4, m_hIcon);
                ::DeleteObject(ii.hbmColor);
                ::DeleteObject(ii.hbmMask);
            }
        }
    }

public:
    void SetIcon(HICON hIcon)
    {
        m_hIcon = hIcon;
    }

private:
    HICON m_hIcon;
};

class CLabelMutilineUI : public CLabelUI
{
    DECLARE_DUICONTROL(CLabelMutilineUI)
public:
    void PaintText(HDC hDC)
    {
        if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
        if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

        CDuiString sText = GetText();
        if (sText.IsEmpty()) return;
        int nLinks = 0;
        RECT rc = m_rcItem;
        rc.left += m_rcTextPadding.left;
        rc.right -= m_rcTextPadding.right;
        rc.top += m_rcTextPadding.top;
        rc.bottom -= m_rcTextPadding.bottom;
        if (IsEnabled()) {
            if (m_bShowHtml)
                CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, sText, m_dwTextColor, \
                    NULL, NULL, nLinks, m_iFont, m_uTextStyle);
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwTextColor, \
                    m_iFont, m_uTextStyle);
        } else {
            if (m_bShowHtml)
                CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
                    NULL, NULL, nLinks, m_iFont, m_uTextStyle);
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
                    m_iFont, m_uTextStyle);
        }
    }
};
}

#endif __LABELEX_H__
