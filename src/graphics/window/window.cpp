#include "window.h"

Window::Window() {
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"EVOLUTION");
    window.setFramerateLimit(60);
    // sf::Mouse::setPosition(sf::Vector2i(0,0), window);
}

void Window::run(){
    while (window.isOpen()) {
        process_events();
        update();
        render();
    }
}

void Window::render() {
    window.clear(BACKGROUND_DARK);
    draw();
    window.display();
}

void Window::draw() {
    Notify(window, Draw);
}

void Window::update() {

}

void Window::process_events(){
    sf::Event event;
    int key = event.key.code;
    if (window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            Notify(window, event.type);
            break;
        }
    }
    else Notify(window, CUSTOM_SFEV::Idle);  
}

