#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <windows.h>
#include <dwmapi.h>
#include "../include/gifController.hpp"

void popupMenu(HWND hwnd) {
    HMENU hmenu = CreatePopupMenu();
    AppendMenuW(hmenu, MF_POPUP, 2, L"Close");
    SetMenu(hwnd, hmenu);
}


int main()
{
    alya::GifController gifController("../../images/nun/");
    auto window = sf::RenderWindow(sf::VideoMode(gifController.getGifSize()), "Giffy", sf::Style::None);
    window.setFramerateLimit(144);

    MARGINS margins;
    margins.cxLeftWidth = -1;
    SetWindowLong(window.getNativeHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    DwmExtendFrameIntoClientArea(window.getNativeHandle(), &margins);

    sf::Clock clock;
    bool isGrabbed = false;
    sf::Vector2i grabbedDelta;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    isGrabbed = true;
                    grabbedDelta = window.getPosition() - sf::Mouse::getPosition();
                }
                // if (mouseButtonPressed->button == sf::Mouse::Button::Middle) {
                //     std::cout << "context menu pos: ";
                //     std::cout << menuPosition.x << ' ' << menuPosition.y << '\n';
                // }
            }
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    isGrabbed = false;
                }
                if (mouseButtonReleased->button == sf::Mouse::Button::Right) {
                    HWND hwnd = window.getNativeHandle();
                    popupMenu(hwnd);
                }
            }
            if (event->is<sf::Event::MouseMoved>() && isGrabbed)
            {
                window.setPosition(sf::Mouse::getPosition() + grabbedDelta);
            }
        }
        if (clock.getElapsedTime().asMilliseconds() > 100)
        {
            gifController.nextTexture();
            clock.restart();
        }
        window.clear(sf::Color::Transparent);
        window.draw(gifController.getCurrentSprite());
        window.display();
    }
}