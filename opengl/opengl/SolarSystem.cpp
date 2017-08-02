
#include <GL\glew.h> //open gl library
#include <GL\freeglut.h> //open gl library
#include <windows.h> //library for image viewer
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <time.h> //rotation of the moons around the planets according to time
#include <string>
#include <iostream>
#include <fstream> //to read images from the folder
#include <assert.h>


using namespace std;

const GLfloat PI = 3.1415926535;
const GLfloat TO_RADIANS = PI / 180.0;

//window position/resizing constants
const GLint INIT_WINDOW_POSITION[2] = { 100, 100 };
const GLfloat ASPECT_RATIO = 1.5;

//lighting constants
const GLfloat LIGHT_0_POSITION[] = { 1.0, 0.0, 0.0, 0.0 };
const GLfloat LIGHT_1_POSITION[] = { -1.0, 0.0, 0.0, 0.0 };
const GLfloat LIGHT_2_POSITION[] = { 0.0, 0.0, 1.0, 0.0 };
const GLfloat LIGHT_3_POSITION[] = { 0.0, 0.0, -1.0, 0.0 };
const GLfloat LIGHT_AMBIENT[] = { 0.8, 0.8, 0.8, 1.0 };
const GLfloat LIGHT_DIFFUSE[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat LIGHT_SPECULAR[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat LIGHT_MODEL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0 };

//earth & moon constants
const char EARTH_BMP_FILENAME[] = "Bitmaps/earthmap.bmp";
const char MOON_BMP_FILENAME[] = "Bitmaps/moonmap.bmp";
const GLfloat EARTH_RADIUS = 0.18;
const GLfloat MOON_RADIUS = 0.08;
const GLfloat MOON_ORBIT_RADIUS = 0.50;
const GLfloat EARTH_ROTATION = 1.00;
const GLfloat LUNAR_CYCLE = 20.0;

//viewer positioning constants
const GLfloat MAXIMUM_VIEWER_DISTANCE = 20;
const GLfloat MINIMUM_VIEWER_DISTANCE = 2;
const GLfloat INITIAL_VIEWER_DISTANCE = 10;
const GLfloat VIEWER_DISTANCE_INCREMENT = 0.1;
const GLfloat INITIAL_VIEWER_AZIMUTH = 0.0;
const GLfloat INITIAL_VIEWER_ZENITH = PI / 2.0;
const GLfloat VIEWER_ANGLE_INCREMENT = PI / 60.0;
const GLfloat LOOK_AT_POSITION[] = { 0.0, 0.0, 0.0 };

//additional planets constants for bitmap files
const char MERCURY_BMP_FILENAME[] = "Bitmaps/mercurymap.bmp";
const char VENUS_BMP_FILENAME[] = "Bitmaps/venusmap.bmp";
const char MARS_BMP_FILENAME[] = "Bitmaps/marsmap.bmp";
const char JUPITER_BMP_FILENAME[] = "Bitmaps/jupitermap.bmp";
const char SATURN_BMP_FILENAME[] = "Bitmaps/saturnmap.bmp";
const char URANUS_BMP_FILENAME[] = "Bitmaps/uranusmap.bmp";
const char NEPTUNE_BMP_FILENAME[] = "Bitmaps/neptunemap.bmp";
const char PLUTO_BMP_FILENAME[] = "Bitmaps/plutomap.bmp";
const char RING_BMP_FILENAME[] = "Bitmaps/saturnringmap.bmp";
const char SUN_BMP_FILENAME[] = "Bitmaps/sunmap.bmp";

//additional planets constants for planet radiuses
const GLfloat MERCURY_RADIUS = 0.1;
const GLfloat VENUS_RADIUS = 0.18;
const GLfloat MARS_RADIUS = 0.25;
const GLfloat JUPITER_RADIUS = 0.4;
const GLfloat SATURN_RADIUS = 0.45;
const GLfloat URANUS_RADIUS = 0.5;
const GLfloat NEPTUNE_RADIUS = 0.3;
const GLfloat PLUTO_RADIUS = 0.05;
const GLfloat SUN_RADIUS = 0.5;

//additional planets constants for orbit radius
const GLfloat MERCURY_ORBIT_RADIUS = 0.9;
const GLfloat VENUS_ORBIT_RADIUS = 1.3;
const GLfloat MARS_ORBIT_RADIUS = 2.7;
const GLfloat JUPITER_ORBIT_RADIUS = 3.7;
const GLfloat SATURN_ORBIT_RADIUS = 5.0;
const GLfloat URANUS_ORBIT_RADIUS = 6.5;
const GLfloat NEPTUNE_ORBIT_RADIUS = 7.5;
const GLfloat PLUTO_ORBIT_RADIUS = 8.0;
const GLfloat EARTH_ORBIT_RADIUS = 2.0;

//additional planets constants for orbit duration
const GLfloat MERCURY_ORBIT_DUR = 88;
const GLfloat VENUS_ORBIT_DUR = 225;
const GLfloat EARTH_ORBIT_DUR = 7.3;
const GLfloat MARS_ORBIT_DUR = 13.72;
const GLfloat JUPITER_ORBIT_DUR = 433;
const GLfloat SATURN_ORBIT_DUR = 1075;
const GLfloat URANUS_ORBIT_DUR = 3068;
const GLfloat NEPTUNE_ORBIT_DUR = 6019;
const GLfloat PLUTO_ORBIT_DUR = 9080;

//additional planets constants for rotation duration
const GLfloat MERCURY_ROTATION_DUR = 29;
const GLfloat VENUS_ROTATION_DUR = -243;
const GLfloat MARS_ROTATION_DUR = 1;
const GLfloat JUPITER_ROTATION_DUR = 0.4;
const GLfloat SATURN_ROTATION_DUR = 0.4;
const GLfloat URANUS_ROTATION_DUR = -0.7;
const GLfloat NEPTUNE_ROTATION_DUR = 0.7;
const GLfloat PLUTO_ROTATION_DUR = -6;

//additional planets constants for inclination
const GLfloat MERCURY_INCLINATION = 7;
const GLfloat VENUS_INCLINATION = 3;
const GLfloat MARS_INCLINATION = 2;
const GLfloat JUPITER_INCLINATION = 1;
const GLfloat SATURN_INCLINATION = 2;
const GLfloat URANUS_INCLINATION = 1;
const GLfloat NEPTUNE_INCLINATION = 2;
const GLfloat PLUTO_INCLINATION = 1;
const GLfloat EARTH_INCLINATION = 7;

//particle system constants
const char PARTICLE_BMP_FILENAME[] = "Bitmaps/Particle.bmp";



const int NUMBER_OF_PARTICLES = 3000;
const float MAX_ROTATION = 360;
const float MIN_ROTATION = 0;
const float MIN_TRANS = .005;
const float MAX_TRANS = .03;
const float MIN_DELTA_ROTATION = 0.5;
const float MAX_DELTA_ROTATION = 3.0;
const float MIN_DELTA_SURFACE = .005;
const float MAX_DELTA_SURFACE = .01;
const int MIN_LIFETIME = 10;
const int MAX_LIFETIME = 25;
const int DELTA_LIFETIME = 1;



class IntPoint //inpoint class
{
//for 2D points with integer coordinates
public:
	int x, y;
	void set(int dx, int dy) { x = dx; y = dy; }
	void set(IntPoint& p) { x = p.x; y = p.y; }
	IntPoint(int xx, int yy) { x = xx; y = yy; }
	IntPoint() { x = y = 0; }
};


class Point2 //point2 class
{
public: //for 2D points with real coordinates
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2& p) { x = p.x; y = p.y; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }
};


class PolyLine //polyLine (num + array of points)
{
public:
	int num;
	Point2 pt[80]; //may need larger arrays in some circumstances
	PolyLine() { num = 0; }
};


class IntRect //inrect class
{
	
public: //rectangle with integer border values
	int left, top, right, bott;
	IntRect() { left = top = right = bott = 0; }
	IntRect(int l, int t, int r, int b)
	{
		left = l; top = t; right = r; bott = b;
	}
	void set(int l, int t, int r, int b)
	{
		left = l; top = t; right = r; bott = b;
	}
	void set(IntRect& r)
	{
		left = r.left; top = r.top; right = r.right; bott = r.bott;
	}
};

// RGBpixmap.h: a class to support working with RGB pixmaps.

typedef unsigned char uchar;

class mRGB //mRGB because the name RGB is already used by Windows
{
public: uchar r, g, b, a;
		mRGB() { r = g = b = 0; a = 255; }
		mRGB(mRGB& p) { r = p.r; g = p.g; b = p.b; a = p.a; }
		mRGB(uchar rr, uchar gg, uchar bb) {
			r = rr; g = gg; b = bb;
			if ((r == 255) && (g == 255) && (b == 255)) a = 0; else a = 255;
		}
		mRGB(uchar rr, uchar gg, uchar bb, uchar aa) { r = rr; g = gg; b = bb; a = aa; }
		void set(uchar rr, uchar gg, uchar bb) {
			r = rr; g = gg; b = bb;
			if ((r == 255) && (g == 255) && (b == 255)) a = 0; else a = 255;
		}
		void set(uchar rr, uchar gg, uchar bb, uchar aa) { r = rr; g = gg; b = bb; a = aa; }
};


class RGBpixmap //RGBPixmap class
{
private:
	mRGB* pixel; //array of pixels

public:
	int nRows, nCols; //dimensions of the pixmap
	RGBpixmap() { nRows = nCols = 0; pixel = 0; }
	RGBpixmap(int rows, int cols) //constructor
	{
		nRows = rows;
		nCols = cols;
		pixel = new mRGB[rows*cols];
	}

	int readBMPFile(string fname, bool hasAlpha); //to read the BMP file into this pixmap
	void setTexture(GLuint textureName);

	void freeIt() //give back memory for this pixmap
	{
		delete[]pixel; nRows = nCols = 0;
	}

	//copy
	void copy(IntPoint from, IntPoint to, int x, int y, int width, int height)
	{
		// copy a region of the display back onto the display
		if (nRows == 0 || nCols == 0) return;
		glCopyPixels(x, y, width, height, GL_COLOR);
	}

	//draw
	void draw()
	{
		//draw this pixmap at current raster position
		if (nRows == 0 || nCols == 0) return;

		//instructing OpenGL to not align pixels to 4 byte boundaries in memory
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glDrawPixels(nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	}

	//read
	int read(int x, int y, int wid, int ht)
	{
		// read a rectangle of pixels into this pixmap
		nRows = ht;
		nCols = wid;
		pixel = new mRGB[nRows *nCols];
		if (!pixel) return -1;

		//instructing OpenGL to not align pixels to 4 byte boundaries in memory
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(x, y, nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
		return 0;
	}

	//read from intrect
	int read(IntRect r)
	{
		//read a rectangle of pixels into this pixmap
		nRows = r.top - r.bott;
		nCols = r.right - r.left;
		pixel = new mRGB[nRows *nCols];
		if (!pixel) return -1;

		//instructing OpenGL to not align pixels to 4 byte boundaries in memory
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(r.left, r.bott, nCols, nRows, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
		return 0;
	}

	//setPixel
	void setPixel(int x, int y, mRGB color)
	{
		if (x >= 0 && x <nCols && y >= 0 && y < nRows)
			pixel[nCols * y + x] = color;
	}

	//getPixel
	mRGB getPixel(int x, int y)
	{
		mRGB bad(255, 255, 255);
		assert(x >= 0 && x < nCols);
		assert(y >= 0 && y < nRows);
		return pixel[nCols * y + x];
	}
}; //end of class RGBpixmap


typedef unsigned short ushort;
typedef unsigned long ulong;
fstream inf; //global in this file for convenience


//getShort
ushort getShort() //helper function
{ //BMP format uses little-endian integer types
  //get a 2-byte integer stored in little-endian form
	char ic;
	ushort ip;
	inf.get(ic); ip = ic;  //first byte is little one 
	inf.get(ic);  ip |= ((ushort)ic << 8); //or in high order byte
	return ip;
}
//getLong
ulong getLong() //helper function
{  //BMP format uses little-endian integer types
   //get a 4-byte integer stored in little-endian form
	ulong ip = 0;
	char ic = 0;
	unsigned char uc = ic;
	inf.get(ic); uc = ic; ip = uc;
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 8);
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 16);
	inf.get(ic); uc = ic; ip |= ((ulong)uc << 24);
	return ip;
}
//RGBPixmap:: readBmpFile
int RGBpixmap::readBMPFile(string fname, bool hasAlpha)
{
	//read into memory an mRGB image from
	//an uncompressed BMP file.
	//return 0 on failure, 1 on success
	inf.open(fname.c_str(), ios::in | ios::binary); //read binary char's
	if (!inf) { cout << " can't open file: " << fname << endl; return 0; }
	int k, row, col, numPadBytes, nBytesInRow;

	//read the file header information
	char ch1, ch2;
	inf.get(ch1);
	inf.get(ch2);	//type: always 'BM'
	ulong fileSize = getLong();
	ushort reserved1 = getShort();	//always 0
	ushort reserved2 = getShort();	//always 0 
	ulong offBits = getLong();	//offset to image - unreliable
	ulong headerSize = getLong();	//always 40
	ulong numCols = getLong();	//number of columns in image
	ulong numRows = getLong();	//number of rows in image
	ushort planes = getShort();	//always 1 
	ushort bitsPerPixel = getShort();	//8 or 24; allow 24 here
	ulong compression = getLong();	//must be 0 for uncompressed 
	ulong imageSize = getLong();	// total bytes in image 
	ulong xPels = getLong();	// always 0 
	ulong yPels = getLong();	// always 0 
	ulong numLUTentries = getLong();	// 256 for 8 bit, otherwise 0 
	ulong impColors = getLong();	// always 0 

	if (bitsPerPixel != 24)
	{
		//error - must be a 24 bit uncompressed image
		cout << "not a 24 bit/pixelimage, or is compressed!\n";
		inf.close();
		return 0;
	}

	//Add bytes at end of each row so total # is a multiple of 4 round up 3*numCols to next mult. of 4
	nBytesInRow = ((3 * numCols + 3) / 4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols; //it needs this many
	nRows = numRows; //set class' data members
	nCols = numCols;
	pixel = new mRGB[nRows * nCols]; //make space for array
	if (!pixel)
		return 0; //out of memory

	long count = 0;
	char dum;
	for (row = 0; row < nRows; row++) //read pixel values
	{
		for (col = 0; col < nCols; col++)
		{
			char r, g, b;
			inf.get(b);
			inf.get(g);
			inf.get(r); //read bytes
			pixel[count].r = r; //place them in colors
			pixel[count].g = g;
			pixel[count].b = b;
			if ((hasAlpha) && (r == -1) && (g == -1) && (b == -1))
				pixel[count++].a = 0;
			else
				pixel[count++].a = 255;
		}
		for (k = 0; k < numPadBytes; k++) //skip pad bytes at rows end
			inf >> dum;
	}
	inf.close();
	return 1; //success
}

void RGBpixmap::setTexture(GLuint textureName)
{
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nCols, nRows, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
}

struct Particle {
	//used for randomizingt the initial position of the particle
	float azimuthRoation, zenithRotation, surfaceTranslationFactor;

	//used for randomizing the delta or change in position of each particle
	float deltaAz, deltaZe, deltaSurface;

	//lifetime in "refreshes"
	int lifetime;
};

class ParticleSystem {

public:
	//gets the next particle in the array
	Particle getNextParticle();
	//modify all particles by their deltas, destroy old ones and create new ones
	void updateAll();
	int getNumberOfParticles();
	ParticleSystem();


private:
	//marker used by getNextParticle to keep track of position.
	int currentParticle;

	//array of all particle structs
	Particle particles[NUMBER_OF_PARTICLES];

	//this is the random number generator from the last program
	float generateRandomNumber(float lower, float upper);

	//to get a new particle struct with new randomized values
	Particle generateNewParticle();

};

ParticleSystem::ParticleSystem() {
	currentParticle = 0;
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) {
		particles[i] = generateNewParticle();
	}
}

Particle ParticleSystem::generateNewParticle() {
	Particle newPart;
	newPart.azimuthRoation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
	newPart.zenithRotation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
	newPart.surfaceTranslationFactor = generateRandomNumber(MIN_TRANS, MAX_TRANS);
	newPart.deltaAz = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
	newPart.deltaZe = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
	newPart.deltaSurface = generateRandomNumber(MIN_DELTA_SURFACE, MAX_DELTA_SURFACE);
	newPart.lifetime = (int)generateRandomNumber(MIN_LIFETIME, MAX_LIFETIME);
	return newPart;
}

Particle ParticleSystem::getNextParticle() {
	currentParticle = (currentParticle == NUMBER_OF_PARTICLES) ? 0 : currentParticle;
	return particles[currentParticle++];
}

int ParticleSystem::getNumberOfParticles() {
	return NUMBER_OF_PARTICLES;
}

float ParticleSystem::generateRandomNumber(float lower, float upper) {
	static bool firstTime = true;
	time_t randomNumberSeed;

	if (firstTime) {
		time(&randomNumberSeed);
		srand(randomNumberSeed);
		firstTime = false;
	}
	return (lower + ((upper - lower) * (float(rand()) / RAND_MAX)));
}

void ParticleSystem::updateAll() {
	//if the particle's lifetime is over, replace it with another otherwise update all the appropriate values
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) {
		if (particles[i].lifetime == 0) {
			particles[i] = generateNewParticle();
		}
		else {
			particles[i].azimuthRoation += particles[i].deltaAz;
			particles[i].zenithRotation += particles[i].deltaZe;
			particles[i].surfaceTranslationFactor += particles[i].deltaSurface;
			particles[i].lifetime -= DELTA_LIFETIME;
		}
	}
}

// viewer positioning angles
GLfloat viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
GLfloat viewerZenith = INITIAL_VIEWER_ZENITH;

//ID numbers for all texture maps
GLuint ParticleTextureName = -1;
GLuint EarthTextureName = 3;
GLuint MoonTextureName = 4;
GLuint SunTextureName = 0;
GLuint MercuryTextureName = 1;
GLuint VenusTextureName = 2;
GLuint MarsTextureName = 5;
GLuint JupiterTextureName = 6;
GLuint SaturnTextureName = 7;
GLuint UranusTextureName = 8;
GLuint NeptuneTextureName = 9;
GLuint PlutoTextureName = 10;
GLuint RingTextureName = 11;


//variables to keep track of current day status
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysTranspired = 0.00;
GLfloat EarthDayIncrement = 0.01;
GLfloat CurrentMRotation = 0.00;
GLfloat MDaysTranspired = 0.00;
GLfloat MDayIncrement = 0.01;

//the initial window and viewport sizes (in pixels), set to ensure that the aspect ration for the viewport, will be a constant. If the window is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint currWindowSize[2] = { 750, 750 / ASPECT_RATIO };
GLint currViewportSize[2] = {750, 750 / ASPECT_RATIO };

GLfloat ViewerDistance = INITIAL_VIEWER_DISTANCE;

ParticleSystem particles;
bool particleFlag = true;
bool blendFlag = true;

//function prototypes
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void KeyboardPress1(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void TimerFunction1(int value);
void Display();

void MakeAllImages();
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha);

void SetLights();
void UpdateLight();

void ResizeWindow(GLsizei w, GLsizei h);

void drawEarthAndMoon();

void drawMarsAndMoon();
void drawSun();
void drawAllOrbits();
void DrawCircle();
void drawSaturnRing();
void drawAllPlanets();
void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
void drawParticle(Particle currParticle);
void drawAllParticles();

//function implementations
//the main function sets up the data and the environment to display the textured objects
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//set up the display window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
	glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
	glutCreateWindow("Solar System");

	//specify the resizing and refreshing routines
	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardPress);
	glutSpecialFunc(NonASCIIKeyboardPress);
	glutDisplayFunc(Display);
	glutTimerFunc(20, TimerFunction, 1);
	glutTimerFunc(20, TimerFunction1, 1);
	glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

	//set up standard lighting, shading, and depth testing
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);				
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_NORMALIZE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	SetLights();

	//set up all texture maps and texture-mapped objects
	MakeAllImages();
	glutMainLoop();
	return 0;
}

//function to react to ASCII keyboard keys pressed by the user
//+/- keys are used to accelerate/decelerate the solar system
//z/Z keys are used to zoom in and out of the solar system
void KeyboardPress1(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch (pressedKey)
	{
	case '+': {
		MDayIncrement *= 2.0;
		if (MDayIncrement > 10.0)
			MDayIncrement = 10.0;
		break;
	}
	case '-': {
		MDayIncrement *= 0.5;
		if (MDayIncrement < 0.01)
			MDayIncrement = 0.01;
		break;
	}
	case 'z': {
		ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
		if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
			ViewerDistance = MINIMUM_VIEWER_DISTANCE;
		break;
	}
	case 'Z': {
		ViewerDistance += VIEWER_DISTANCE_INCREMENT;
		if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
			ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
		break;
	}
//enable and disable the particle system
	case 'p': {
		particleFlag = !particleFlag;
		break;
	}
//enable and disable the blending function
	case 'b': {
		blendFlag = !blendFlag;
		break;
	}
	}
}

void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch (pressedKey)
	{
	case '+': {
		EarthDayIncrement *= 2.0;
		if (EarthDayIncrement > 10.0)
			EarthDayIncrement = 10.0;
		break;
	}
	case '-': {
		EarthDayIncrement *= 0.5;
		if (EarthDayIncrement < 0.01)
			EarthDayIncrement = 0.01;
		break;
	}
	case 'z': {
		ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
		if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
			ViewerDistance = MINIMUM_VIEWER_DISTANCE;
		break;
	}
	case 'Z': {
		ViewerDistance += VIEWER_DISTANCE_INCREMENT;
		if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
			ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
		break;
	}
//enable and disable the particle system
	case 'p': {
		particleFlag = !particleFlag;
		break;
	}
//enable and disable the blending function
	case 'b': {
		blendFlag = !blendFlag;
		break;
	}
	}
}

//unction to react to non-ASCII keyboard keys pressed by the user
//used to alter spherical coordinates of the viewer's position
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch (pressedKey)
	{
	case GLUT_KEY_RIGHT: {
		viewerAzimuth += VIEWER_ANGLE_INCREMENT;
		if (viewerAzimuth > 2 * PI)
			viewerAzimuth -= 2 * PI;
		break;
	}
	case GLUT_KEY_LEFT: {
		viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
		if (viewerAzimuth < 0.0)
			viewerAzimuth += 2 * PI;
		break;
	}
	case GLUT_KEY_UP: {
		viewerZenith -= VIEWER_ANGLE_INCREMENT;
		if (viewerZenith < VIEWER_ANGLE_INCREMENT)
			viewerZenith = VIEWER_ANGLE_INCREMENT;
		break;
	}
	case GLUT_KEY_DOWN: {
		viewerZenith += VIEWER_ANGLE_INCREMENT;
		if (viewerZenith > PI - VIEWER_ANGLE_INCREMENT)
			viewerZenith = PI - VIEWER_ANGLE_INCREMENT;
		break;
	}
	}
}

//the EarthDayIncrement represents the fraction of an Earth day being added to the scene in one screen update
void TimerFunction(int value)
{
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysTranspired += EarthDayIncrement;
	if (EarthDaysTranspired == EARTH_ORBIT_DUR)
		EarthDaysTranspired = 0;
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

void TimerFunction1(int value)
{
	CurrentMRotation += MDayIncrement;
	MDaysTranspired += MDayIncrement;
	if (MDaysTranspired == MARS_ORBIT_DUR)
		MDaysTranspired = 0;
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction1, 1);
}

// Principal display routine: sets up material, lighting, and camera properties, clears the frame buffer, and draws all texture-mapped objects within the window
void Display()
{
	//initialize lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);
	glEnable(GL_LIGHTING);

	//sets up the properties of the viewing camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//position and orient viewer
	gluLookAt(LOOK_AT_POSITION[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth),
		LOOK_AT_POSITION[1] + ViewerDistance * cos(viewerZenith),
		LOOK_AT_POSITION[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
		LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
		0.0, 1.0, 0.020);

	//render scene
	UpdateLight();
	drawAllOrbits();

	drawEarthAndMoon();
	drawMarsAndMoon();
	drawSun();
	drawAllPlanets();
	drawSaturnRing();

	if (blendFlag) { //if the user has selected blending, enable it
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_COLOR, GL_ONE);
	}
	if (particleFlag)
		drawAllParticles();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	glFlush();
}

//create the textures associated with all texture-mapped objects being displayed
void MakeAllImages()
{
	MakeImage(EARTH_BMP_FILENAME, EarthTextureName, false);
	MakeImage(MOON_BMP_FILENAME, MoonTextureName, false);
	MakeImage(SUN_BMP_FILENAME, SunTextureName, false);
	MakeImage(MERCURY_BMP_FILENAME, MercuryTextureName, false);
	MakeImage(VENUS_BMP_FILENAME, VenusTextureName, false);
	MakeImage(PARTICLE_BMP_FILENAME, ParticleTextureName, false);
	MakeImage(MARS_BMP_FILENAME, MarsTextureName, false);
	MakeImage(JUPITER_BMP_FILENAME, JupiterTextureName, false);
	MakeImage(SATURN_BMP_FILENAME, SaturnTextureName, false);
	MakeImage(URANUS_BMP_FILENAME, UranusTextureName, false);
	MakeImage(NEPTUNE_BMP_FILENAME, NeptuneTextureName, false);
	MakeImage(PLUTO_BMP_FILENAME, PlutoTextureName, false);
	MakeImage(RING_BMP_FILENAME, RingTextureName, false);
	return;
}

void drawAllPlanets() {
	drawGenericPlanet(MERCURY_INCLINATION, MERCURY_ORBIT_DUR/50, MERCURY_ORBIT_RADIUS,
		MERCURY_ROTATION_DUR, MercuryTextureName, MERCURY_RADIUS);
	drawGenericPlanet(VENUS_INCLINATION, VENUS_ORBIT_DUR/50, VENUS_ORBIT_RADIUS,
		VENUS_ROTATION_DUR, VenusTextureName, VENUS_RADIUS);
	drawGenericPlanet(JUPITER_INCLINATION, JUPITER_ORBIT_DUR/50, JUPITER_ORBIT_RADIUS,
		JUPITER_ROTATION_DUR, JupiterTextureName, JUPITER_RADIUS);
	drawGenericPlanet(SATURN_INCLINATION, SATURN_ORBIT_DUR/50, SATURN_ORBIT_RADIUS,
		SATURN_ROTATION_DUR, SaturnTextureName, SATURN_RADIUS);
	drawGenericPlanet(URANUS_INCLINATION, URANUS_ORBIT_DUR/50, URANUS_ORBIT_RADIUS,
		URANUS_ROTATION_DUR, UranusTextureName, URANUS_RADIUS);
	drawGenericPlanet(NEPTUNE_INCLINATION, NEPTUNE_ORBIT_DUR/50, NEPTUNE_ORBIT_RADIUS,
		NEPTUNE_ROTATION_DUR, NeptuneTextureName, NEPTUNE_RADIUS);
	drawGenericPlanet(PLUTO_INCLINATION, PLUTO_ORBIT_DUR/50, PLUTO_ORBIT_RADIUS,
		PLUTO_ROTATION_DUR, PlutoTextureName, PLUTO_RADIUS);

}

//convert the bitmap with the parameterized name into an OpenGL texture
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha)
{
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}


//sets the two lights to illuminate the scene
void SetLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);

	glLightfv(GL_LIGHT2, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

	glLightfv(GL_LIGHT3, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
}


//enable the scene's lighting
void UpdateLight()
{
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
	glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

//window-reshaping callback, adjusting the viewport to be as large as possible within the window, without changing its aspect ratio
void ResizeWindow(GLsizei w, GLsizei h)
{
	currWindowSize[0] = w;
	currWindowSize[1] = h;
	if (ASPECT_RATIO > w / h)
	{
		currViewportSize[0] = w;
		currViewportSize[1] = w / ASPECT_RATIO;
	}
	else
	{
		currViewportSize[1] = h;
		currViewportSize[0] = h * ASPECT_RATIO;
	}

	glViewport(0.5*(w - currViewportSize[0]), 0.5*(h - currViewportSize[1]), currViewportSize[0], currViewportSize[1]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void drawMarsAndMoon()
{
	
	GLfloat MoonRevolution1 = MDaysTranspired / LUNAR_CYCLE;
	GLUquadricObj* quadro = gluNewQuadric();
	GLUquadricObj* quadro1 = gluNewQuadric();

	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(MARS_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (MDaysTranspired / MARS_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(MARS_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * CurrentMRotation, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MarsTextureName);
	gluSphere(quadro, MARS_RADIUS, 48, 48);
	//gluSphere(quadro1, MARS_RADIUS, 48, 48);

	glPopMatrix();
	glRotatef(MARS_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (MDaysTranspired / MARS_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(MARS_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * MoonRevolution1, 0.0, 1.0, 0.0);
	glTranslatef(MOON_ORBIT_RADIUS, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MoonTextureName);
	gluSphere(quadro, MOON_RADIUS, 48, 48);
	glRotatef(MARS_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * MoonRevolution1, 0.0, 1.0, 0.0);
	glTranslatef(MOON_ORBIT_RADIUS, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MoonTextureName);
	gluSphere(quadro, MOON_RADIUS, 48, 48);
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
	//gluDeleteQuadric(quadro1);
}

//draws the texture-mapped earth and moon
void drawEarthAndMoon()
{
	GLfloat MoonRevolution = EarthDaysTranspired / LUNAR_CYCLE;
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, EarthTextureName);
	gluSphere(quadro, EARTH_RADIUS, 48, 48);
	glPopMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * MoonRevolution, 0.0, 1.0, 0.0);
	glTranslatef(MOON_ORBIT_RADIUS, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MoonTextureName);
	gluSphere(quadro, MOON_RADIUS, 48, 48);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

//dunction to draw and texture map the sun at the origin
void drawSun()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, SunTextureName);
	gluSphere(quadro, SUN_RADIUS, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

//draw Orbit
void DrawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);	//get the current angle 
		float x = r * cosf(theta);	//calculate the x component 
		float y = r * sinf(theta);	//calculate the y component 
		glVertex3f(x + cx, 0.0, y + cy);	//output vertex 
		//glRotatef(EARTH_INCLINATION, 1.0, 0.0, 0.0);
	}
	glEnd();
}

//draw all orbits
void drawAllOrbits()
{
	glPushMatrix();
	glRotatef(MERCURY_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, MERCURY_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(VENUS_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, VENUS_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, EARTH_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(MARS_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, MARS_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(JUPITER_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, JUPITER_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, SATURN_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(URANUS_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, URANUS_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(NEPTUNE_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, NEPTUNE_ORBIT_RADIUS, 2000);
	glPopMatrix();

	glPushMatrix();
	glRotatef(PLUTO_INCLINATION, 0.0, 0.0, 1.0);
	DrawCircle(0.0, 0.0, PLUTO_ORBIT_RADIUS, 2000);
	glPopMatrix();
}

//draw rings
void drawSaturnRing()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / 21.5), 0.0, 1.0, 0.0);
	glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, RingTextureName);
	glScalef(1, 1, .02);
	gluSphere(quadro, SATURN_RADIUS * 1.2, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

//given parameters about the planets dimension, orbit, radius etc, this function will draw a texture mapped planet
//used to draw everything except the sun, earth/moon. and saturns rings, as they are special cases of this function
void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius)
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(inclination, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / orbitDuration), 0.0, 1.0, 0.0);
	glTranslatef(orbitRadius, 0.0, 0.0);
	glRotatef(360.0 * (CurrentEarthRotation / rotationDuration), 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texturename);
	gluSphere(quadro, radius, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

//cycles through each particle in the particle system and passes it to the draw function
void drawAllParticles() {
	particles.updateAll();
	for (int i = 0; i < particles.getNumberOfParticles(); i++)
		drawParticle(particles.getNextParticle());

}

//draws one individual particle, given a particle struct from the particle system object
void drawParticle(Particle currParticle)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glRotatef(currParticle.azimuthRoation, 0, 1, 0);
	glRotatef(currParticle.zenithRotation, 0, 0, 1);
	glTranslatef(SUN_RADIUS + currParticle.surfaceTranslationFactor, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.5, .5, 1.0);
	glBindTexture(GL_TEXTURE_2D, ParticleTextureName);

	//logo facing earth
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(1, 1);
	glVertex3f(0.5f, 0.5f, 0.0f);	//top right
	glTexCoord2d(0, 1);
	glVertex3f(-0.5f, 0.5f, 0.0f);	//top left
	glTexCoord2d(1, 0);
	glVertex3f(0.5f, -0.5f, 0.0f);	//bottom right
	glTexCoord2d(0, 0);
	glVertex3f(-0.5f, -0.5f, 0.0f);	//bottom left
	glEnd();

	//logo facing away from earth
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(1, 1);
	glVertex3f(-0.5f, 0.5f, 0.0f);	//top right
	glTexCoord2d(0, 1);
	glVertex3f(0.5f, 0.5f, 0.0f);	//top left
	glTexCoord2d(1, 0);
	glVertex3f(-0.5f, -0.5f, 0.0f);	//bottom right
	glTexCoord2d(0, 0);
	glVertex3f(0.5f, -0.5f, 0.0f);	//bottom left
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

