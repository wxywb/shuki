#include<string>
#include<iostream>
#include<GL/glew.h>
#ifndef SKYBOX_HPP
#define SKYBOX_HPP
#include <ImageMagick-6/Magick++.h>
class Skybox {
    enum 
    {
        CUBEMAP_RIGHT,
        CUBEMAP_LEFT,
        CUBEMAP_UP,
        CUBEMAP_DOWN,
        CUBEMAP_BACK,
        CUBEMAP_FRONT, 
    } typedown;
public:
    Skybox(const std::string &cubemap_right_path,
        const std::string &cubemap_left_path,
        const std::string &cubemap_up_path,
        const std::string &cubemap_down_path,
        const std::string &cubemap_back_path,
        const std::string &cubemap_front_path
        ){  
        map_paths[CUBEMAP_RIGHT] = cubemap_right_path;
        map_paths[CUBEMAP_LEFT]  = cubemap_left_path;
        map_paths[CUBEMAP_UP]    = cubemap_up_path;
        map_paths[CUBEMAP_DOWN]  = cubemap_down_path;
        map_paths[CUBEMAP_BACK]  = cubemap_back_path;
        map_paths[CUBEMAP_FRONT] = cubemap_front_path;
    }

    bool Load() {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        Magick::Image   image;
        Magick::Blob    blob;
        for (int i = CUBEMAP_RIGHT; i <= CUBEMAP_FRONT; i++) {
            try {
                image.read(map_paths[i]);
                image.write(&blob, "RGBA");
            }
            catch (Magick::Error& Error) {
                std::cout << "Error loading texture '" << map_paths[i] << "': " << Error.what() << std::endl;
                return false;
            }
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, image.columns(), image.rows(), 0, GL_RGB, GL_UNSIGNED_BYTE, blob.data()
            );
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(textureID, 0);
    }

private:
    std::string map_paths[6];
    GLuint textureID;
};

#endif