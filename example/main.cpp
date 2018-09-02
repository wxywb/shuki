
#include<ShukiShader.h>
#include<ShukiModel.h>
#include<ShukiTexture.h>
#include<ShukiCamera.h>
#include<Shuki.h>
#include<ShukiTechnique.h>

#include<map>
#include<callbacks_impl.h>

#include<cmath>
#include <stdio.h>
#include <string.h>
#include<vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ShukiMath.h>
#include<skybox.hpp>

using namespace std;
using namespace Assimp;
constexpr double pi = 3.1415926535898;


shuki::Model            *   global_model;
shuki::Model            *   global_canvas;
shuki::Camera           *   gCamera;
shuki::ShaderManger     *   global_sm;
shuki::ShaderManger     *   global_sm2;
shuki::ShaderManger     *   global_sm3;
shuki::App              *   global_app;

class GlobalGetter {
    std::map<string, GLuint> map_;
public:
    void set(std::string name, GLuint value) {
        map_[name] = value;
    }
    GLuint get(std::string name) {
        return map_[name];
    }
};

static GlobalGetter * GlobalDB() {
    static GlobalGetter _globalgetter;
    return &_globalgetter;
}

#define SET_NAME(name, value)\
    GlobalDB()->set(#name,value);\

#define GET_NAME(var,name)\
    var = GlobalDB()->get(#name);\



GLuint VBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

GLuint global_framebuffer;
GLuint global_textureColorbuffer;
GLuint global_textureColorbuffer2;

void RenderSceneCB();

static void InitializeGlutCallbacks()
{

    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vector3f f; f[0] = 1.0f; f[1] = 2.0f; f[2] = 3.0f;
    //VectorProtype<float, 3> temp(f);
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

int main(int argc, char** argv)
{

    shuki::App application(800, 600, 100, 100);
    global_app = &application;

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(global_app->_width, global_app->_height);
    glutInitWindowPosition(global_app->_pos_x, global_app->_pos_y);
    glutCreateWindow("Tutorial 04");
    glutSpecialFunc(SpecialKeys);
    glutPassiveMotionFunc(PassiveMouseCB);
    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    printf("GL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

    shuki::ShaderManger sm;

    shuki::ShaderManger sm2;

    sm2.setVSFile("D:/shit/shuki/shaders/shader.vs");
    sm2.setFSFile("D:/shit/shuki/shaders/shaderkernel.fs");

    sm.setVSFile("D:/shit/shuki/shaders/SSR1.vs");
    sm.setFSFile("D:/shit/shuki/shaders/SSR1.fs");

    sm2.initialize();
    sm2.attach_shaders();
    sm2.init_program();

    global_sm2 = &sm2;
    sm.initialize();
    sm.init_program();
    sm.attach_shaders();
    sm.use();

    shuki::ShaderManger fusionshader;
    fusionshader.setVSFile("D:/shit/shuki/shaders/SSR2.vs");
    fusionshader.setFSFile("D:/shit/shuki/shaders/SSR2.fs");
    fusionshader.initialize();
    fusionshader.init_program();
    fusionshader.attach_shaders();

    global_sm3 = &fusionshader;

    GLint tex1_loc = glGetUniformLocation(sm.getprogram(), "diffuse_texture");
    glUniform1i(tex1_loc, COLOR_TEXTURE_UNIT_INDEX);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1_loc);

    GLint tex2_loc = glGetUniformLocation(sm.getprogram(), "normal_texture");
    glUniform1i(tex2_loc, NORMAL_TEXTURE_UNIT_INDEX);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2_loc);




    fusionshader.use();
    GLint convolutional_image_loc = glGetUniformLocation(fusionshader.getprogram(), "convolutional_image");
    GLint original_image_loc = glGetUniformLocation(fusionshader.getprogram(), "original_image");

    glUniform1i(convolutional_image_loc, 0);
    glUniform1i(original_image_loc, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, convolutional_image_loc);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, original_image_loc);

    sm.use();
    global_sm = &sm;
    // sm2.use();
    Assimp::Importer impoter;

    //string Filename("D:/proj/ogldev-source/Content/tex/nanosuit2.obj");
    string Filename("D:/proj/ogldev-source/Content/tex/nanosuit2.obj");
    shuki::Model m(Filename);
    global_model = &m;

    shuki::Model canvas(std::string("D:/proj/ogldev-source/Content/quad.obj"));
    global_canvas = &canvas;

    auto floor = new shuki::Model (std::string("D:/proj/ogldev-source/Content/floor.obj"));
    SET_NAME(floor, GLuint(floor))
    

    GLint mimoriLoc = glGetUniformLocation(sm.getprogram(), "mimori");
    glUniform1f(mimoriLoc, 1.0f);
    GLint WordMatLoc = glGetUniformLocation(sm.getprogram(), "WordMat");
    GLint ProjMatLoc = glGetUniformLocation(sm.getprogram(), "ProjMat");
    GLint vectorLoc = glGetUniformLocation(sm.getprogram(), "Vector");
    GLint CameraLoc = glGetUniformLocation(sm.getprogram(), "CameraMat");
    GLint MatLoc = glGetUniformLocation(sm.getprogram(), "none");

    vmath::mat4 transmat = vmath::translate(0.0f, 0.0f, 0.2f);

    transmat.identity();


    shuki::Camera player(vec3(0.0f, 5.0f, 10.0f), 0, 0, 0.5f);

    gCamera = &player;
    vmath::mat4 projmat = vmath::perspective_red(0.2, 0.2, -0.2, -1000.0);

    float v[4];
    auto camera_proj = gCamera->getMatirxMatrix();
    for (int i = 0; i < 4; i++) v[i] = 1.0f;
    glUniformMatrix4fv(WordMatLoc, 1, false, transmat);
    glUniformMatrix4fv(ProjMatLoc, 1, true, projmat);
    glUniformMatrix4fv(CameraLoc, 1, false, projmat);
    glUniform4f(vectorLoc, 0.25f, 0.50f, 0.75f, 1.0f);
    m.Init();
    canvas.Init();
    floor->Init();
    // glutSetCursor(GLUT_CURSOR_NONE);





    Skybox skybox(std::string("D:/proj/ogldev-source/Content/cubemap/sea_rt.JPG"),
        std::string("D:/proj/ogldev-source/Content/cubemap/sea_lf.JPG"),
        std::string("D:/proj/ogldev-source/Content/cubemap/sea_up.JPG"),
        std::string("D:/proj/ogldev-source/Content/cubemap/sea_dn.JPG"),
        std::string("D:/proj/ogldev-source/Content/cubemap/sea_bk.JPG"),
        std::string("D:/proj/ogldev-source/Content/cubemap/sea_ft.JPG"));
    skybox.Load();
    //skybox.Bind();
    cout << sin(30 * pi / 180) << endl;
    cout << cos(0 * pi / 180) << endl;

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    global_framebuffer = framebuffer;
    GLuint textureColorbuffer = generateAttachmentTexture(false, false);

    GLuint textureColorbuffer2 = generateAttachmentTexture(false, false);
    global_textureColorbuffer = textureColorbuffer;
    global_textureColorbuffer2 = textureColorbuffer2;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, textureColorbuffer2, 0);


    GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, global_app->_width, global_app->_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint convolutinoal_framebuffer;
    glGenFramebuffers(1, &convolutinoal_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, convolutinoal_framebuffer);
    GLuint convolutionao_fb_texture = generateAttachmentTexture(false, false);
    SET_NAME(convolutinoal_framebuffer, convolutinoal_framebuffer)
    SET_NAME(convolutionao_fb_texture, convolutionao_fb_texture)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, convolutionao_fb_texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    system("pause");



    return 0;

}


GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
    // What enum to use?
    GLenum attachment_type;
    if (!depth && !stencil)
        attachment_type = GL_RGB;
    else if (depth && !stencil)
        attachment_type = GL_DEPTH_COMPONENT;
    else if (!depth && stencil)
        attachment_type = GL_STENCIL_INDEX;

    //Generate texture ID and load texture data 
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int screenWidth = global_app->_width;
    int screenHeight = global_app->_height;
    if (!depth && !stencil)
        glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, screenWidth, screenHeight, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
    else // Using both a stencil and depth test, needs special format arguments
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}



static void RenderSceneCB()
{
    using namespace std;
    glBindFramebuffer(GL_FRAMEBUFFER, global_framebuffer);
	//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    global_sm->use();


    UpdateCameraProjMat();
    global_model->Render();
   // global_canvas->RenderwithoutTexture();
    shuki::Model *floor;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    global_sm3->use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, global_textureColorbuffer);
    // global_model->Render();
    global_canvas->RenderwithoutTexture();

    /*    unsigned int ui_floor;
    GET_NAME(ui_floor, floor)
    floor = (shuki::Model *)ui_floor;
    glBindTexture(GL_TEXTURE_2D, global_textureColorbuffer);
    global_sm3->use();

    floor->RenderwithoutTexture();
    POINT mousePos;
    GetCursorPos(&mousePos);
  */ 
    //global_sm3->use();
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
   // glBindTexture(GL_TEXTURE_2D, global_textureColorbuffer);
    //global_canvas->RenderwithoutTexture();
    glutSwapBuffers();
}


