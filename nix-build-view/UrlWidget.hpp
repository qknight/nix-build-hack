#ifndef URLWIDGET__HPP
#define URLWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class UrlWidget : public Widget {
public:
    UrlWidget(std::string url, float percent, int bits_per_sec);
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    int type();
private:
    std::string m_url;
    float m_percent;
    int m_bits_per_sec;
};

#endif
