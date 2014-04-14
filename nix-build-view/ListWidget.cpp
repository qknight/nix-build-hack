#include "ListWidget.hpp"

ListWidget::ListWidget() {
    terminal_preprocess();
}

void ListWidget::splitString(std::vector<std::string> &v_str,const std::string &str,const char ch) {
    std::string sub;
    std::string::size_type pos = 0;
    std::string::size_type old_pos = 0;
    bool flag=true;

    while(flag)
    {
        pos=str.find_first_of(ch,pos);
        if(pos == std::string::npos)
        {
            flag = false;
            pos = str.size();
        }
        sub = str.substr(old_pos,pos-old_pos);  // Disregard the '.'
        v_str.push_back(sub);
        old_pos = ++pos;
    }
}

void ListWidget::terminal_preprocess() {
    // - render the text to a buffer
    // - do line-wrapping
    std::string s = m_logfile.str();

    {
        /////// BEGIN: trim end of each string!
        std::stringstream s_tmp;
        std::vector<std::string> tmp;
        splitString(tmp, s, '\n');

        for(int i=0; i < tmp.size(); ++i) {
            std::string::const_iterator it_b = tmp[i].begin();
            std::string::const_iterator it_e = tmp[i].end();
            std::string::const_iterator it_tmp = it_e-1;

            while(it_tmp < it_e && it_tmp >= it_b) {
                if (*it_tmp == ' ') {
                    --it_tmp;
                } else {
                    s_tmp << std::string(it_b, it_tmp+1);
                    break;
                }
            }
            if(i < tmp.size()-1)
                s_tmp << std::endl;
        }
        /////// END: trim end of each string!
        s = s_tmp.str();
    }


    //render the m_logfile into a terminal with width w
    m_terminal.clear();
    std::string tmp;
    for (int i=0; i <= s.size(); ++i) {
        if (tmp.size() == width()) {
            m_terminal.push_back(tmp);
            tmp="";
        }

        if (s[i] == '\n')  {
            tmp += std::string(width()-tmp.size(), ' ');
            m_terminal.push_back(tmp);
            tmp="";
            continue;
        }
        tmp += s[i];
    }
}

//FIXME buffer the result, only compute this stuff when the terminal width changes
//FIXME only scroll the view when m_line==0
//FIXME scrollback does scroll further than  m_terminal.size(), render needs to be fixed. however, the widget has to know it's current w and h, which is only known at render(...) currently
std::string ListWidget::render() {
    // - m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

//     if (m_width_last != width() && m_height_last != height()) {
//        m_width_last = width();
//        m_height_last = height();
//        terminal_preprocess();
//     }
    
    //copy the last h elements from terminal to the out buffer
    std::stringstream out;

    std::vector<std::string>::const_iterator it_b = m_terminal.begin();
    std::vector<std::string>::const_iterator it_e = m_terminal.end();

    if (it_e - height() - m_line >= it_b)
        it_b = it_e - height() - m_line;

    for(int i=0; i < height(); ++i) {
        if (it_b >= it_e)
            break;
        out << *it_b++;
    }

    return out.str();
}

void ListWidget::resize(int w, int h) {
    Widget::resize(w, h);
    update();
}

void ListWidget::append(std::string line) {
    // replace all \t with '        ' (8 spaces)
    // you can't use copy'n'paste from that terminal, so Makefiles for example will be broken when being copied this way
    std::stringstream buf;

    for(int i=0; i < line.size(); ++i) {
        if (line[i] == '\t')
            buf << "        ";
        else
            buf << line[i];
    }

    // add the new string
    m_logfile << buf.str();
    terminal_preprocess(); //FIXME optimization needed

    update();
}

void ListWidget::down() {
    if (m_line > 0)
        m_line -= 1;
    update();
}

void ListWidget::up() {
    m_line += 1;
    if (m_line > m_terminal.size())
        m_line = m_terminal.size();
    update();
}

void ListWidget::pgup() {
    m_line += 15;
    if (m_line > m_terminal.size())
        m_line = m_terminal.size();
    update();
}

void ListWidget::pgdown() {
    m_line -= 15;
    if (m_line < 0)
        m_line = 0;
    update();
}

void ListWidget::home() {
    m_line = m_terminal.size();
    update();
}

void ListWidget::end() {
    m_line = 0;
    update();
}
