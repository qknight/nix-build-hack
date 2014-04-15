#ifndef WIDGET__HPP
#define WIDGET__HPP

#include "WindowManager.hpp"

#include <string>


class Widget {
public:
    virtual std::string render() = 0;
    void update() {
      //FIXME tell the WM to update(this)!
        WindowManager::Instance()->update();
    };
    unsigned int width()  {
        return m_width;
    };
    unsigned int height() {
        return m_height;
    };
    void hide() {
      m_visible = false;
    }
    void show() {
      m_visible = true;
    }  
    virtual void resize(unsigned int width, unsigned int height) {
        m_width = width;
        m_height = height;
    }
private:
    unsigned int m_width = 0;
    unsigned int m_height = 1;
    bool m_visible = true;
};

#endif
