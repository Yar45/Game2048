// Game2048.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <SFML/Graphics.hpp> // SFML библиотека для графики

#include <iostream>         // Ввод/вывод
#include <thread>           // Многопоточность
#include <atomic>           // Многопоточность
#include <shared_mutex>     // Мьютексы

#include "PrettySet.h"      // Пользовательский класс для графических ресурсов
#include "BasicValues.h"    // Пользовательский класс для констант игры
#include "Game.h"

#define BREAK(LABLE) goto LABLE     // Макрос для перехода по метке
#define GAME_ANTIALISING_LEVEL 8    // Уровень сглаживания
#define GAME_FPS_LIMIT 30           // Ограничение FPS

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

    sf::Image icon;
    if (!icon.loadFromFile("assets/2048.png"))
    {
        return 0;
    }
    window.setIcon(128, 128, icon.getPixelsPtr());

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

    if (PrettySet::loadFont() == -1 || PrettySet::loadTexture() == -1) {
        std::ofstream file("log.txt");
        file << "Error loading font or texture";
        file.close();
        return 0;
    }

    // if resize relaunch window
    int isResized = 0;
    do {
        BasicValues::resizeValues();
        isResized = launchWindow();
    } while (isResized == 1);

    return 0;
}