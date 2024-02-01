#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#ifdef ANDROID
#include <android/log.h>
#endif

int main(int argc, char* argv[])
{
    auto videoMode = sf::VideoMode(sf::Vector2u(360, 640));
#ifdef ANDROID
    videoMode = sf::VideoMode::getDesktopMode();
#endif

    sf::VideoMode screen(videoMode);
    sf::RenderWindow window(screen, "");
    window.setFramerateLimit(30);

    auto fontPath = "assets/tuffy.ttf";
#ifdef ANDROID
        __android_log_print(ANDROID_LOG_INFO, "YourApp", "HERE I AM! ALIVE");
#endif

    sf::Font font;
    auto fontPossiblePaths = {"tuffy.ttf", "assets/tuffy.ttf", "../assets/tuffy.ttf"};
    auto isFontLoaded = false;
    for (auto path : fontPossiblePaths)
    {
        isFontLoaded = font.loadFromFile(path);
    }
    
    if (!isFontLoaded)
        return EXIT_FAILURE;

    sf::Text text(font, "Hello", 64);
    text.setFillColor(sf::Color::Black);
    text.setPosition({10, 10});

    sf::View view = window.getDefaultView();

    sf::Color background = sf::Color::White;

    // We shouldn't try drawing to the screen while in background
    // so we'll have to track that. You can do minor background
    // work, but keep battery life in mind.
    bool active = true;

    while (window.isOpen())
    {
        for (sf::Event event; active ? window.pollEvent(event) : window.waitEvent(event);)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Key::Escape)
                        window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(sf::Vector2f(event.size.width, event.size.height));
                    view.setCenter(sf::Vector2f(event.size.width, event.size.height) / 2.f);
                    window.setView(view);
                    break;
                case sf::Event::LostFocus:
                    background = sf::Color::Black;
                    break;
                case sf::Event::GainedFocus:
                    background = sf::Color::White;
                    break;

                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
                case sf::Event::MouseLeft:
                    active = false;
                    break;
                case sf::Event::MouseEntered:
                    active = true;
                    break;
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        // image.setPosition({static_cast<float>(event.touch.x), static_cast<float>(event.touch.y)});
                    }
                    break;
                default:
                    break;
            }
        }

        if (active)
        {
            window.clear(background);
            // window.draw(image);
            window.draw(text);
            window.display();
        }
        else
        {
            sf::sleep(sf::milliseconds(100));
        }
    }
}
