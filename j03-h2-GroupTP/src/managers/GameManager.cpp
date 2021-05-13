//
// Created by gdemers on 12/7/2020.
//

#include "GameManager.h"

bool keyPressed = false;

GameManager::GameManager() {
    window = nullptr;
    context = nullptr;
    isRunning = false;
    state = nullptr;
    m_player = nullptr;
    isColliding = false;
    m_skybox = nullptr;
    uiManager = nullptr;
}

GameManager::~GameManager() {
    delete m_player;
    delete m_skybox;
    delete uiManager;
}

void
GameManager::initialize(const char *_windowTitle, int _windowPosX, int _windowPosY, int _screenWidth, int _screenHeight,
                        bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init Failed : ", SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        SDL_Log("IMG_Init Failed : ", IMG_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    GameManager::window = SDL_CreateWindow(_windowTitle, _windowPosX, _windowPosY, _screenWidth, _screenHeight,
                                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window is NULL");
    }
    GameManager::context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        SDL_Log("Context is NULL");
    }
    if (!TTF_WasInit() && TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_WarpMouseInWindow(window, _screenWidth / 2, _screenHeight / 2);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    TextureManager::init();
    MapManager::init();
    SoundManager::init();

    gluPerspective(70, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 500);

    uiManager = new UiManager();
    uiManager->init();
    m_player = new Player(25, -25);
    m_skybox = new Skybox();

    Mix_Music *music = SoundManager::getMusic("03 - Get Them Before They Get You E1M1");
    if (music != nullptr) {
        Mix_PlayMusic(music, 1);
    }
    GameManager::isRunning = true; // start game loop
}

void GameManager::handleEvents() {
    while (SDL_PollEvent(&(GameManager::event))) {
        if (GameManager::event.type == SDL_MOUSEBUTTONDOWN) {
            if (GameManager::event.button.button == SDL_BUTTON_LEFT) {
                if(m_player->getAmmo() >= 1){
                    // maybe add a rate of fire for the player
                    m_player->fire();
                    m_player->setAmmo(-1);
                    UiManager::hasFired = true;
                }
            }
        }
    }

    GameManager::state = SDL_GetKeyboardState(NULL);
    SDL_GetRelativeMouseState(&dxMouse, &dyMouse);

    float oldPlayerXpos = m_player->getCamX();
    float oldPlayerZpos = m_player->getCamZ();
    float oldPlayerRefX = m_player->getRefX();
    float oldPlayerRefZ = m_player->getRefZ();

    for (int i = 0; i < WallManager::getWalls().size(); ++i) {
        isColliding = CollisionManager::checkSphereCollisions(m_player->getSphereCollider(),
                                                              WallManager::getWalls()[i]->getSphereCollider());
        if (isColliding) {
            break;
        }
    }
    // check enemies collision with walls, if collided change orientation and go the other way
    EnemyManager::checkCollision();

    m_player->move(ROTATE, dxMouse);

    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        m_player->move(Direction::FORWARD, -1);
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        m_player->move(Direction::BACKWARD, -1);
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        m_player->move(Direction::LEFT, -1);
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        m_player->move(Direction::RIGHT, -1);
    }
    if (state[SDL_SCANCODE_SPACE]) {
        //m_player->move(Direction::UP, -1);
    }
    if (state[SDL_SCANCODE_C]) {
        //m_player->move(Direction::DOWN, -1);
    }

    if (isColliding) {
        m_player->setCamX(oldPlayerXpos);
        m_player->setCamZ(oldPlayerZpos);
        m_player->setRefX(oldPlayerRefX);
        m_player->setRefZ(oldPlayerRefZ);
    }
    PassiveManager::checkCollision(m_player);
}

void GameManager::update() {
    // avoid memory leak
    m_player->deleteInGameBullets();
    // update bullets translation
    m_player->updateBulletTrajectory();
    // need this check otherwise it is doing a collision check with instances of enemy that do not exist
    if (EnemyManager::checkIsInitialized()) {
        for (auto it = EnemyManager::s_enemies.begin(); it != EnemyManager::s_enemies.end(); it++) {
            EnemyManager::checkCollisionBetweenEnemiesAndPlayerBullets(m_player, it->second);
        }
    }
    uiManager->update(m_player);
}

void GameManager::render() {
    glClearColor(0.f, 0.f, 0.75f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, SCREEN_HEIGHT / 6.f, SCREEN_WIDTH, SCREEN_HEIGHT - (SCREEN_HEIGHT / 6.f));

    EnemyManager::initialize();
    MapManager::generateWalls();
    m_player->cameraPos(); // position de la camera

    m_skybox->draw();
    MapManager::drawPlane();
    WallManager::drawWalls();

    m_player->drawBullets();
    // Enemies update and draw
    EnemyManager::update(m_player);

    PassiveManager::draw();

    glMatrixMode(GL_PROJECTION_MATRIX);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-6, 25, -1.2, 30, 0, 125);
    uiManager->render();
    glPopMatrix();


    glFlush();
    SDL_GL_SwapWindow(window);
    SDL_Delay(15);
}

void GameManager::quit() {
    m_player->clear();
    EnemyManager::clear();
    TextureManager::clear();
    WallManager::destructor();
    MapManager::destructor();
    PassiveManager::destructor();
    SoundManager::clear();
    uiManager->quit();
    SDL_GL_DeleteContext(context);
    context = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

bool GameManager::getIsRunning() const {
    return isRunning;
}
