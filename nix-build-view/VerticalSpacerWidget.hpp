#ifndef VerticalSpacerWidget__HPP
#define VerticalSpacerWidget__HPP

#include "Widget.hpp"

class VerticalSpacerWidget : public Widget
{
    AdvancedStringContainer render(unsigned int width, unsigned int height);

    int type() const;

    unsigned int rowsWantedByWidget();
};

#endif // VerticalSpacerWidget__HPP
