#include "UiManager.h"

GLuint UiManager::m_barTextureId = 0;
GLuint UiManager::m_weaponTextureId = 0;
std::vector<GLuint> UiManager::m_weaponTextureIds;
bool UiManager::hasFired = false;

UiManager::UiManager() {
    health = 0;
    ammo = 0;
}

UiManager::~UiManager() {

}

void UiManager::init() {
    font = TTF_OpenFont("assets/fonts/JetBrainsMono-Light.ttf", 20);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    m_barTextureId = loadTexture("assets/textures/ui/bar.png", false);

    if (m_barTextureId == 0) {
        std::cout << "Unable to load texture" << std::endl;
    }
}

void UiManager::renderBar(const double& X, const double& Y, const double& Z, const double& width, const double& height) {

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, m_barTextureId);

    glTranslatef(X, Y, Z);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1*width, -1*height, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1*width, -1*height, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1*width, 1*height, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1*width, 1*height, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void UiManager::update(Player *_player) {
    setHealth(_player->getHP());
    setAmmo(_player->getAmmo());
}

void UiManager::renderText(const TTF_Font *Font, const GLubyte &R, const GLubyte &G, const GLubyte &B, const double &X,
                           const double &Y, const double &Z, const std::string &Text) {
    glPushMatrix();
    SDL_Color Color = {R, G, B};
    SDL_Surface *Message = TTF_RenderText_Blended(const_cast<TTF_Font *>(Font), Text.c_str(), Color);
    unsigned Texture = 0;

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 Message->pixels);

    glRotated(180, 1, 0, 0);
    glBegin(GL_QUADS);

    glTexCoord2d(0, 0);
    glVertex3d(X, Y, Z);
    glTexCoord2d(1, 0);
    glVertex3d(X + Message->w * 0.24f, Y, Z);
    glTexCoord2d(1, 1);
    glVertex3d(X + Message->w * 0.24f, Y + Message->h * 0.5f, Z);
    glTexCoord2d(0, 1);
    glVertex3d(X, Y + Message->h * 0.5f, Z);

    glEnd();
    glPopMatrix();

    glDeleteTextures(1, &Texture);
    SDL_FreeSurface(Message);
}

void UiManager::render() {
    renderWeapon();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/6.f); // bar
    renderBar(9.5f, 14, 0, 11, 12);

    glViewport(0, 0, SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 6.f); // health
    renderText(font, 150, 150, 150, 3, -18, 0, to_string(health));

    glViewport((SCREEN_WIDTH / 4.f) * 2.9f, 0, SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 6.f); // ammo
    renderText(font, 150, 150, 150, 12, -18, 0, to_string(ammo));
}

void UiManager::renderWeapon() {
    glPushMatrix();
    if (hasFired) {
        glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID("pistol_2"));
        hasFired = false;
    } else {
        glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID("pistol_1"));
    }

    glScaled(10, 10, 10);
    glTranslatef(1, 1, 1);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void UiManager::quit() {
    TTF_CloseFont(font);
}

void UiManager::setHealth(int value) {
    this->health = value;
}

void UiManager::setAmmo(int value) {
    this->ammo = value;
}

int UiManager::getHealth() {
    return this->health;
}

int UiManager::getAmmo() {
    return this->ammo;
}
