#include "CreditsScreen.h"
#include "StartMenuScreen.h"
#include "OptionsScreen.h"
#include "../../Minecraft.h"
#include "../components/Button.h"
#include "../components/ImageButton.h"

CreditsScreen::CreditsScreen()
: bHeader(NULL), btnBack(NULL)
{}
CreditsScreen::~CreditsScreen() {
    if (bHeader) delete bHeader;
    if (btnBack) delete btnBack;
}

void CreditsScreen::init() {
    bHeader = new Touch::THeader(0, "Credits");
    btnBack = new ImageButton(1, "");
    {
        ImageDef def;
        def.name = "gui/touchgui.png";
        def.width = 34;
        def.height = 26;
        def.setSrc(IntRectangle(150, 0, (int)def.width, (int)def.height));
        btnBack->setImageDef(def, true);
    }
    buttons.push_back(bHeader);
    buttons.push_back(btnBack);

    // prepare text lines
    _lines.clear();
    _lines.push_back("Minecraft: Pocket Edition");
    _lines.push_back("Original game by Mojang");
    _lines.push_back("Programmers:\nmschiller890\nInviseDivine\nKolyah35");
    _lines.push_back("[Gold color tag]Join our Discord server:[/Gold color tag] [Green color tag]url.....[/Green color tag]");
    _scrollSpeed = 0.5f;
    _scrollY = height; // start below screen
}

void CreditsScreen::setupPositions() {
    int buttonHeight = btnBack->height;
    btnBack->x = width - btnBack->width;
    btnBack->y = 0;
    if (bHeader) {
        bHeader->x = 0;
        bHeader->y = 0;
        bHeader->width = width - btnBack->width;
        bHeader->height = btnBack->height;
    }

    // reset scroll starting position when screen size changes
    _scrollY = height;
}

void CreditsScreen::tick() {
    // move text upward
    _scrollY -= _scrollSpeed;
    // if text has scrolled off the top, restart
    float totalHeight = _lines.size() * (minecraft->font->lineHeight + 8);
    if (_scrollY + totalHeight < 0) {
        _scrollY = height;
    }
}

void CreditsScreen::render(int xm, int ym, float a) {
    renderBackground();
    super::render(xm, ym, a);
    int w = width;
    Font* font = minecraft->font;
    float y = _scrollY;
    const float lineHeight = font->lineHeight + 8;
    for (size_t i = 0; i < _lines.size(); ++i) {
        const std::string& line = _lines[i];
        // use color-tag-aware drawing, centre by total width
        float lineWidth = Gui::getColoredWidth(font, line);
        Gui::drawColoredString(font, line, w/2 - lineWidth/2, (int)y, 255);
        y += lineHeight;
    }
}

void CreditsScreen::buttonClicked(Button* button) {
    if (button->id == 1) {
        minecraft->setScreen(new OptionsScreen());
    }
}
