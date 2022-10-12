//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc, Vedaant Vyas
//Nov 17, 2021

GLuint death; //Textures
GLuint start;
GLuint selectCloud;
GLuint selectBadCloud;
LTexture gPlayerTexture;
LTexture gBGTexture;
LTexture gBadCloudTexture;
LTexture gGoodCloudTexture;
LTexture gAcidCloudTexture;
LTexture gBGTextureLater;
LTexture gBGTextureLater2;
LTexture gTextTexture;
LTexture gHighScoreText;
LTexture gPowerUp;
LTexture gLife;
LTexture gShield;
LTexture gFHealth;

int a = 210;
int b = 345; 
int c = 165;
int d = 265;

TTF_Font* gFont = NULL; //Font

void powerup::render(){ //render powerup
	gPowerUp.render(mPosX, mPosY); //show powerup
}

void character::render(){ //render player
	gPlayerTexture.render(mPosX, mPosY); //Show the player
}

void BadCloud::render(int attack){ //render cloud
	
	if(attack == 0){
		gGoodCloudTexture.render(mPosX, mPosY); //show the cloud
		//gGoodCloudTexture.render(mPosX + 300, mPosY);
	}
	else if(attack == 1){ //render bad cloud
		gBadCloudTexture.render(mPosX, mPosY); //show bad cloud
		//gBadCloudTexture.render(mPosX + 300, mPosY);
	}
	else{
		gAcidCloudTexture.render(mPosX, mPosY);
	}
	//gbadcloudtexture.render(mposx, mposy);
}
void loadTextures(){
	death = SOIL_load_OGL_texture(
		"images/deadEarth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    start = SOIL_load_OGL_texture(
		"images/liveEarth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    selectCloud = SOIL_load_OGL_texture(
		"images/clouds/cloud.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    selectBadCloud = SOIL_load_OGL_texture(
		"images/clouds/acidCloud.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
void loadTEXTTEXTURES(){//load text
	gTextTexture.render(10, 15);
	gHighScoreText.render(SCREEN_WIDTH - (gHighScoreText.getWidth() + 10), 15);
	gLife.render(400, 15);
    gShield.render(500, 15);
}
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Acid Rain Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize ttf
				if(TTF_Init() == -1){
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void disDeath(){ //Display death screen using glut and soil
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, death);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(640, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(640, 480);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 480);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Display Surviving Time
	string ST = "Your Survival Time: ";
	ST += to_string(timer);
	int len = ST.size();
	glRasterPos2f(250, 340);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}

	//Display Highest Surviving Time
	string SHT = "Highest Survival Time: ";
	SHT += to_string(survivehighscore);
	int len1 = SHT.size();
	glRasterPos2f( 250, 320);
	for(int i = 0; i < len1; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, SHT[i]);
	}
	if(timer > survivehighscore){
		//display acknowledgement of new high score
		string congratuation = "NEW HIGHSCORE!!";
		int len2 = congratuation.size();
		glRasterPos2f(250, 300);
		for(int i = 0; i < len2; i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, congratuation[i]);
		}
	}
    ST = "Play Game                                   Quit";
	len = ST.size();
	glRasterPos2f(200, 260);

	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}

	glFlush();
}

void disStart(){ //Display start screen using glut and soil
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, start);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(640, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(640, 480);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0, 480);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Display Surviving Time
	string ST = "Play Game";
	int len = ST.size();
	glRasterPos2f(250, 340);

	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}

    ST = "Quit";
	len = ST.size();
	glRasterPos2f(250, 300);
    
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ST[i]);
	}	
}

void disSelect(){
        disStart();

        glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, selectCloud);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);

		glBegin(GL_POLYGON);
        
		glTexCoord2d(0.0, 0.0);
		glVertex2d(a - 25, b - 20);

		glTexCoord2d(0.0, 1.0);
		glVertex2d(a - 25, b + 20);

		glTexCoord2d(1.0, 1.0);
		glVertex2d(a + 25, b + 20);

		glTexCoord2d(1.0, 0.0);
		glVertex2d(a + 25, b - 20);
		glEnd();
        glFlush();
}

void disSelect2(){
        disDeath();

        glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, selectBadCloud);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);

		glBegin(GL_POLYGON);
        
		glTexCoord2d(0.0, 0.0);
		glVertex2d(c - 25, d - 20);

		glTexCoord2d(0.0, 1.0);
		glVertex2d(c - 25, d + 20);

		glTexCoord2d(1.0, 1.0);
		glVertex2d(c + 25, d + 20);

		glTexCoord2d(1.0, 0.0);
		glVertex2d(c + 25, d - 20);
		glEnd();
        glFlush();
}

void close(){
	gPlayerTexture.free(); //Free loaded images
	gBGTexture.free();
    gBGTextureLater.free();
    gBGTextureLater2.free();
	gBadCloudTexture.free();
	gGoodCloudTexture.free();
    gAcidCloudTexture.free();
	gTextTexture.free();
	gPowerUp.free();
	gShield.free();
    gHighScoreText.free();
    gLife.free();

	TTF_CloseFont(gFont); //Font
	gFont = NULL;
	
	SDL_DestroyRenderer(gRenderer); //Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	IMG_Quit(); //Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
}
//if you want to initialize something in soil
void initializeSOIL(){
	//initialize soil variables
}
//Soil init function
void myInitSOIL(){
	//startup SOIL
	glClearColor(1.0, 4.0, 6.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	loadTextures();
	initializeSOIL();
}
//Glut Idle
void idleFunc(){
	//idle 
	glutPostRedisplay();
}
bool loadMedia(){
	//Loading success flag
	bool success = true;
	
    rain = Mix_LoadMUS("sounds/rain.wav");
    hit = Mix_LoadWAV( "sounds/acidHit.wav" );
    umbrella = Mix_LoadWAV( "sounds/umbrellaOpen.wav" );


	if(!gPowerUp.loadFromFile("images/umbrella.png")){//Load powerup texture
		printf("Failed to load powerup texture!\n");
		success = false;
	}
	//Load player texture
	if(!gPlayerTexture.loadFromFile("images/player/playerUp.png")){
		printf("Failed to load player texture!\n");
		success = false;
	}
	//Load background texture
	if(!gBGTexture.loadFromFile("images/ground/greenGrass.jpg")){
		printf("Failed to load good background texture!\n");
		success = false;
	}
	//Load background texture
	if(!gBGTextureLater.loadFromFile("images/ground/dyingGrass.jpg")){
		printf("Failed to load bad background texture!\n");
		success = false;
	}
    if(!gBGTextureLater2.loadFromFile("images/ground/dirt.jpg")){
		printf("Failed to load bad background texture!\n");
		success = false;
	}
	//Loud Warning Cloud
	if(!gBadCloudTexture.loadFromFile("images/clouds/rainCloud.png")){
		printf("Failed to load Warning cloud texture!\n");
		success = false;
	}
	//Load good cloud
	if(!gGoodCloudTexture.loadFromFile("images/clouds/cloud.png")){
		printf("Failed to load goodcloud texture!\n");
		success = false;
	}
	//load acid cloud
	if(!gAcidCloudTexture.loadFromFile("images/clouds/acidCloud.png")){
		printf("Failed to load acid rain texture!\n");
		success = false;
	}
	
	//load font
	gFont = TTF_OpenFont("images/gameFONT.ttf",20);
	if(gFont == NULL){
		printf("Failed to load font: %s\n", TTF_GetError());
		success = false;
	}
	else{
		SDL_Color textcolor = { 0,0,0 };
		string s = to_string(timer);
		if(!gTextTexture.loadFromRenderedText(s, textcolor)){
			printf("Failed to render game timer");
			success = false;
		}
	}
	return success;
}
//void glutLeaveMainLoop(void);
void keyFunc(unsigned char k, int x, int y){
	if(k == 13){ //end screen keyboard input
        if(b == 345){
            SOILRender(2);
        }
        else if(b == 305){
            exit(0);
        }
	}
}

void keyFunc2(unsigned char k, int x, int y){
    if(k == 13){
        if(c == 165){
            SOILRender(0);
        }
        else if(c == 355){
            exit(0);
        }
    }
}

void startFunc(int k, int x, int y){
    if(k == GLUT_KEY_UP){
        if(b >= 345){
            b = 305;
        }
        else{
            b += 40;
        } 
    }
    if(k == GLUT_KEY_DOWN){
        if(b <= 305){
            b = 345;
        }
        else{
            b -= 40;
        } 
    }
}

void endFunc(int k, int x, int y){
	if(k == GLUT_KEY_RIGHT){
        if(c == 355){
            c = 165;
        }
        else{
            c += 190;
        } 
    }
    if(k == GLUT_KEY_LEFT){
        if(c <= 165){
            c = 355;
        }
        else{
            c -= 190;
        } 
    }
}
