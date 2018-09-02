#pragma once
#ifndef SHUKIAPP_H
#define SHUKIAPP_H

namespace shuki {
struct App {
    App() {
        _width = 1024;
        _height = 768;
        _pos_x = 100;
        _pos_y = 100;
    }
    App(int width, int height, int pos_x, int pos_y) {
        _width = width;
        _height = height;
        _pos_x = pos_x;
        _pos_y = pos_y;
    }
    int _width;
    int _height;
    int _pos_x;
    int _pos_y;
};
}
#endif