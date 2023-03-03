#include <SFML/Graphics.hpp>
#include <string>
#include "utils/event_manager.hpp"
#include "utils/binary_io.hpp"
#include "async_renderer.hpp"
#include "config.hpp"

int main()
{
    const sf::Vector2u window_size{2560, 1440};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Fractal", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);

    sfev::EventManager event_manager{window, true};
    event_manager.addKeyReleasedCallback(sf::Keyboard::Escape, [&window](sfev::CstEv) {
        window.close();
    });
    event_manager.addEventCallback(sf::Event::Closed, [&window](sfev::CstEv) {
        window.close();
    });

    const Config::FloatType        zoom_factor {1.005};
    const Config::FloatType        speed       {1.0};
    Config::FloatType              zoom        {400.0};
    sf::Vector2<Config::FloatType> center      {0.0, 0.0};

    AsyncRenderer<Config::FloatType> renderer{window_size.x, window_size.y, zoom};

    bool zoom_in  = false;
    bool zoom_out = false;
    bool left     = false;
    bool right    = false;
    bool up       = false;
    bool down     = false;

    event_manager.addKeyPressedCallback(sf::Keyboard::A,      [&](sfev::CstEv) { zoom_in  = true;  });
    event_manager.addKeyPressedCallback(sf::Keyboard::E,      [&](sfev::CstEv) { zoom_out = true;  });
    event_manager.addKeyReleasedCallback(sf::Keyboard::A,     [&](sfev::CstEv) { zoom_in  = false; });
    event_manager.addKeyReleasedCallback(sf::Keyboard::E,     [&](sfev::CstEv) { zoom_out = false; });
    event_manager.addKeyPressedCallback(sf::Keyboard::Left,   [&](sfev::CstEv) { left     = true;  });
    event_manager.addKeyPressedCallback(sf::Keyboard::Right,  [&](sfev::CstEv) { right    = true;  });
    event_manager.addKeyPressedCallback(sf::Keyboard::Up,     [&](sfev::CstEv) { up       = true;  });
    event_manager.addKeyPressedCallback(sf::Keyboard::Down,   [&](sfev::CstEv) { down     = true;  });
    event_manager.addKeyReleasedCallback(sf::Keyboard::Left,  [&](sfev::CstEv) { left     = false; });
    event_manager.addKeyReleasedCallback(sf::Keyboard::Right, [&](sfev::CstEv) { right    = false; });
    event_manager.addKeyReleasedCallback(sf::Keyboard::Up,    [&](sfev::CstEv) { up       = false; });
    event_manager.addKeyReleasedCallback(sf::Keyboard::Down,  [&](sfev::CstEv) { down     = false; });

    event_manager.addKeyReleasedCallback(sf::Keyboard::W, [&](sfev::CstEv) {
        BinaryWriter writer{"center.bin"};
        writer.write(center);
    });
    event_manager.addKeyReleasedCallback(sf::Keyboard::R, [&](sfev::CstEv) {
        BinaryReader reader{"center.bin"};
        reader.readInto(center);
    });

    BinaryReader reader{"center.bin"};
    if (reader) {
        reader.readInto(center);
    }

    while (window.isOpen())
    {
        event_manager.processEvents();

        const Config::FloatType offset = speed / zoom;
        //zoom = zoom_in ? zoom * zoom_factor : (zoom_out ? zoom / zoom_factor : zoom);
        zoom *= 1.0012;
        center.x += left ? -offset : (right ? offset : 0.0);
        center.y += up   ? -offset : (down  ? offset : 0.0);

        window.clear(sf::Color::Black);
        renderer.render(zoom, center, window);
        window.display();
    }

    return 0;
}
