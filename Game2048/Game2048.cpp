// Game2048.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <SFML/Graphics.hpp>

#include <iostream>
#include <thread>
#include <atomic>
#include <shared_mutex>

#include "PrettySet.h"
#include "BasicValues.h"
#include "Game.h"

#define BREAK(LABLE) goto LABLE

#define GAME_ANTIALISING_LEVEL 8
#define GAME_FPS_LIMIT 30

Game* game;
//std::shared_mutex mtx;
//std::mutex mtx;

std::atomic_flag renderingThread_runningFlag = ATOMIC_FLAG_INIT;
std::atomic_flag renderingThread_lostFocusFlag = ATOMIC_FLAG_INIT;

void renderingThread(sf::RenderWindow* window) {
    
    // activate the window's context
    window->setActive(true);

    // the rendering loop
    while (window->isOpen() && renderingThread_runningFlag.test(std::memory_order::relaxed))
    {
        //std::shared_lock<std::shared_mutex> lock(mtx, std::defer_lock);
        //std::lock_guard<std::mutex> lock(mtx);

        if (renderingThread_lostFocusFlag.test(std::memory_order::acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        //lock.lock();
        game->loop();
    }

    window->setActive(false);
    window->close();
}

int launchWindow() {
    int isResize = 0;
    //std::unique_lock<std::mutex> lock0(mtx, std::defer_lock);

    sf::ContextSettings settings(0, 0, GAME_ANTIALISING_LEVEL);

    // create the window in the main thread due to OS limitations
    sf::RenderWindow window(sf::VideoMode(BasicValues::WINDOW_width, BasicValues::WINDOW_height), "2048", sf::Style::Titlebar | sf::Style::Close, settings);

    // deactivate context to change thread
    window.setActive(false);

    //lock0.lock();
    game = new Game(GAME_FPS_LIMIT, &window);
    //lock0.unlock();

    renderingThread_runningFlag.test_and_set(std::memory_order::release);
    renderingThread_lostFocusFlag.clear(std::memory_order::release);

    // launch the rendering thread
    std::thread renderingThreadObj(&renderingThread, &window);

    bool leftButtonFree = true;
    bool rightButtonFree = true;
    bool upButtonFree = true;
    bool downButtonFree = true;
    // the event loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: {
                renderingThread_runningFlag.clear(std::memory_order::release);
                BREAK(LABLE_CLOSE_WINDOW);
            }

            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Key::Left) {
                    if (leftButtonFree) {
                        //std::shared_lock<std::shared_mutex> lock(mtx);
                        //std::lock_guard<std::mutex> lock(mtx);
                        game->onKeyboard(sf::Keyboard::Key::Left);
                        leftButtonFree = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::Key::Right) {
                    if (rightButtonFree) {
                        //std::shared_lock<std::shared_mutex> lock(mtx);
                        //std::lock_guard<std::mutex> lock(mtx);
                        game->onKeyboard(sf::Keyboard::Key::Right);
                        rightButtonFree = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::Key::Up) {
                    if (upButtonFree) {
                        //std::shared_lock<std::shared_mutex> lock(mtx);
                        //std::lock_guard<std::mutex> lock(mtx);
                        game->onKeyboard(sf::Keyboard::Key::Up);
                        upButtonFree = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::Key::Down) {
                    if (downButtonFree) {
                        //std::shared_lock<std::shared_mutex> lock(mtx);
                        //std::lock_guard<std::mutex> lock(mtx);
                        game->onKeyboard(sf::Keyboard::Key::Down);
                        downButtonFree = false;
                    }
                }
                break;
            }

            case sf::Event::KeyReleased: {
                if (event.key.code == sf::Keyboard::Key::Left) {
                    leftButtonFree = true;
                }
                else if (event.key.code == sf::Keyboard::Key::Right) {
                    rightButtonFree = true;
                }
                else if (event.key.code == sf::Keyboard::Key::Up) {
                    upButtonFree = true;
                }
                else if (event.key.code == sf::Keyboard::Key::Down) {
                    downButtonFree = true;
                }
                break;
            }

            case sf::Event::LostFocus: {
                renderingThread_lostFocusFlag.test_and_set(std::memory_order::release);
                break;
            }

            case sf::Event::GainedFocus: {
                renderingThread_lostFocusFlag.clear(std::memory_order::release);
                break;
            }

            case sf::Event::Resized: {
                isResize = 1;
                window.close();
                break;
            }

            default:
                break;
            }
        }
    }

LABLE_CLOSE_WINDOW:
    renderingThreadObj.join();

    delete game;

    return isResize;
}

int main() {
    srand(time(0));

    PrettySet::loadFont();
    PrettySet::loadTexture();

    // if resize relaunch window
    int isResized = 0;
    do {
        BasicValues::resizeValues();
        isResized = launchWindow();
    } while (isResized == 1);

    return 0;
}