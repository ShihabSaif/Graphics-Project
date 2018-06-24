#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
//#include <G:\CodeBlocks\MinGW\include\GL\glut.h>
#include<GL/glut.h>
#include<math.h>
#include<fstream>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include<windows.h>
#include<mmsystem.h>
#include <cmath>
using namespace std;

///////////////////For loading texture //////////////////////
GLuint base_tex,tower_f;
GLUquadric *quad;

int stop = 0;
float startj=1;
float startk=0;

typedef uint16_t WORD;
typedef uint8_t BYTE;
int num_texture=-1;
float dx,dy,dz,ox1,ox2,oy1,oy2,oz1,oz2;

void init(void)
{
   GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { 0.0, 3.0, 3.0, 0.0 };
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 0.0 };

   glClearColor(0.0, 0.1, 0.1, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

float angle = 0.0f, angleWheel = 0.0f, angleCar = -700.0f, angleCarZ = -1000.0f, angleCar2 = -800.0f,
        angleCar3 = 1100.0f, angleCar4 = 1200.0f, angleCarZ2 = -1100.0f, angleCarZ3 = 1100.0f, angleCarZ4 = 1200.0f;

int LoadTexture(char *filename, int width, int height)
{
    int i,j=0;
    FILE *l_file;
    unsigned char *l_texture;
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;
    if((l_file=fopen(filename,"rb"))==NULL)return(-1);

    infoheader.biWidth = width;
    infoheader.biHeight = height;

    l_texture=(unsigned char*)malloc(infoheader.biWidth*infoheader.biHeight*4);

    memset(l_texture,0,infoheader.biWidth * infoheader.biHeight*4);
    for(i=0;i<infoheader.biWidth*infoheader.biHeight;i++)
    {
        fread(&rgb,sizeof(rgb),1,l_file);
        l_texture[j+0]=rgb.rgbtRed;
        l_texture[j+1]=rgb.rgbtGreen;
        l_texture[j+2]=rgb.rgbtBlue;
        l_texture[j+3]=255;
        j+=4;
    }
    fclose(l_file);
    glBindTexture(GL_TEXTURE_2D,num_texture);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,0,4,infoheader.biWidth,infoheader.biHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,infoheader.biWidth,infoheader.biHeight,GL_RGBA,GL_UNSIGNED_BYTE,l_texture);
    free(l_texture);
    return(num_texture);
}
void FreeCreatedTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}


GLuint textureGeneral,textureGate1,textureGate,textureTree,textureLeaf,textureFootpath,textureBoundaryWall,textureTrafficlight,textureFloor,textureParking,textureRoad,textureTinshade,textureNight,textureStick,textureRed,textureBrick,textureGrass,textureStand,textureSky1,textureSky2,textureSky3,textureSky4,textureSky5,textureWall,textureSky;
GLuint textureFrontBuilding,textureMiddleBuilding,textureRightBuilding,textureRightBuildingRightSide,textureMainShop,textureShopLogo,textureSportsLeftSide;


void func(){
 textureGrass = LoadTexture("Images/grass7.bmp",500,500);
 textureGate= LoadTexture("Images/gate.bmp",460,954);
 textureGate1= LoadTexture("Images/gate1.bmp",447,949);
 textureTree= LoadTexture("Images/gach.bmp",800,616);
 textureLeaf= LoadTexture("Images/leaf.bmp",1000,750);
 textureFootpath= LoadTexture("Images/footpath.bmp",1080,1920);
 textureBoundaryWall=LoadTexture("Images/boundary1.bmp",128,128);
 textureTrafficlight= LoadTexture("Images/tlight.bmp",112,338);
 textureParking= LoadTexture("Images/parking.bmp",852,480);
 textureFloor = LoadTexture("Images/floor.bmp",300,300);
 textureRoad = LoadTexture("Images/rod.bmp",800,800);
 textureNight = LoadTexture("Images/night1.bmp",1920,1080);
 textureTinshade = LoadTexture("Images/tinerChal1.bmp",1024/2,1024/2);
 textureStand = LoadTexture("Images/download.bmp",256,256);
 textureSky1= LoadTexture("Images/sky1.bmp",1024,1024);
 //textureSky2= LoadTexture("Images/sky2.bmp",1024,1024);
 //textureSky3= LoadTexture("Images/sky3.bmp",1024,1024);
 //textureSky4= LoadTexture("Images/sky4.bmp",1024,1024);
 textureWall= LoadTexture("Images/wall.bmp",256,256);
 textureBrick= LoadTexture("Images/brick.bmp",512,512);
 textureSky= LoadTexture("Images/s.bmp",1024,1024);
 //textureRed=LoadTexture("red.bmp",512,512);
 textureGeneral=textureSky;

        //textureBuilding1 = LoadTexture("building1.bmp",256,256);
        textureFrontBuilding = LoadTexture("Images/FrontSideBuilding.bmp",1024,1024);
        textureMiddleBuilding = LoadTexture("Images/middleBuilding.bmp",1024,1024);
        textureRightBuilding = LoadTexture("Images/textureBuild1.bmp",800,800);
        textureRightBuildingRightSide = LoadTexture("Images/textureBuild1.bmp",800,800);


            textureShopLogo = LoadTexture("Images/sportsLogo.bmp",800,100);
            textureMainShop = LoadTexture("Images/sports.bmp",500,250);
            textureSportsLeftSide = LoadTexture("Images/sportsLeftSide.bmp",512,512);
}

float objx,objy,objz;

float gate;

float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=270.0f, z=600.0f;
float upDown=0.0f;
float y=20.0f;
float upangle=0.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
float Vangle=0.000f;
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window   of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 4000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);


}


 bool collision(float Objx,float Objy,float Objz)
 {
     if(abs(x-Objx)==0||abs(y-Objy)==0||abs(z-Objz)==0)
        return true;
        return false;
 }


float dist;float distGate;float wallDist;float wallX,wallZ;float wx1,wz1;

void computePos(float deltaMove) {
    dx=abs(ox1-(x+deltaMove*lx*0.1f));
    dz=abs(oz1-(z+deltaMove*lz*0.1f));
    dist = sqrt(dx*dx + dz*dz);
    float dx1=abs(objx-(x+deltaMove*lx*0.1f));
    float dz1=abs(objz-(z+deltaMove*lz*0.1f));
    distGate=sqrt(dx1*dx1 + dz1*dz1);
    wx1=1220-(x+deltaMove*lx*0.1f);
    wz1=-1000-(z+deltaMove*lz*0.1f);
    wallDist=abs(wx1)+abs(wz1);

if(x+deltaMove*lx*0.1f<1100&&x+deltaMove*lx*0.1f>-700)

        if(dist>20&&wx1>730||wz1<-830||gate==1)

            {
                    if(distGate>80&&gate==1&&x+deltaMove*lx*0.1f<1100&&x+deltaMove*lx*0.1f>-700)
                    {
                        if((wx1<630||wz1<-850)&&x+deltaMove*lx*0.1f<1100&&x+deltaMove*lx*0.1f>-700)
                            {x += deltaMove * lx * 0.1f;
                            gate-0;
                            }

                    }
                    else
                    x += deltaMove * lx * 0.1f;
            }


            if(z+deltaMove*lz*0.1f<900&&z+deltaMove*lz*0.1f>-900)

                if(dist>20&&wx1>730||wz1<-830||gate==1)
                {
                            if(distGate>80&&gate==1&&z+deltaMove*lz*0.1f<900&&z+deltaMove*lz*0.1f>-900)
                            {
                                if((wz1>-750||wz1<-850||wx1>630)&&z+deltaMove*lz*0.1f<900&&z+deltaMove*lz*0.1f>-900)
                                    {z += deltaMove * lz * 0.1f;
                                    gate==0;}
                            }
                    else
                 z += deltaMove * lz * 0.1f;
                }

    //if(distGate>80)
      //  gate=0;
  }

void computeUp(float upDown){
 if((y+upDown-5)>0.0&&(y+upDown-5)<800.0)
  y+=upDown*0.1f;
  }

void computeUPangle(float ua){
    upangle+=ua;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void makeTree(){
glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glColor4f(1,0.82,0.7,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureTree);
    glPushMatrix();
    glTranslatef(0,25,0);
    glRotatef(-90,1,0,0);
    gluCylinder(quad,10,10,30,7,7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(quad,25,10,30,7,7);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(0,55,0);
    glRotatef(-90,1,0,0);
    gluCylinder(quad,10,20,20,7,7);
    glPopMatrix();

    //glEnable(GL_TEXTURE_2D);
    //GLUquadric *qobj1 = gluNewQuadric();

    //gluQuadricTexture(qobj1,GL_TRUE);

    glBindTexture(GL_TEXTURE_2D,textureLeaf);
    ///majhkhanerta
     glPushMatrix();
    glTranslatef(0,100,0);
    glRotatef(-90,1,0,0);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///makjkhaner samnerta
    glPushMatrix();
    glTranslatef(0,100,50);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///majhkhaner picherta
    glPushMatrix();
    glTranslatef(0,100,-50);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///right sider er picher ta
    glPushMatrix();
    glTranslatef(50,100,-40);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///right side er samner ta
    glPushMatrix();
    glTranslatef(50,100,40);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///right side er majherta
    glPushMatrix();
    glTranslatef(50,100,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///left side samnerta
    glPushMatrix();
    glTranslatef(-50,100,40);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

    ///leftside picher ta
    glPushMatrix();
    glTranslatef(-50,100,-40);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();
    ///leftside majherta
    glPushMatrix();
    glTranslatef(-50,100,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();

        ///leftside uporer ta
    glPushMatrix();
    glTranslatef(-50,140,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();
    ///majhkhanuporer ta
    glPushMatrix();
    glTranslatef(0,140,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();
    ///right side uporer ta
    glPushMatrix();
    glTranslatef(50,140,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,30,10,10);
    glPopMatrix();
    ///sobar uporer ta
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textureLeaf);
        //glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    //glEnable(GL_TEXTURE_GEN_T);
    glTranslatef(0,180,0);
    glRotatef(-90,1,0,0);
    gluSphere(quad,50,10,10);
    //glDisable(GL_TEXTURE_GEN_S);
    //glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void lampPost()
{
    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, textureStand);
    glPushMatrix();
    glTranslatef(325,35,-100);
    glScalef(0.05,0.7,0.05);
    glutSolidCube(150);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(323,78,-90);
    glRotatef(90,1,0,0);
    glScalef(0.05,0.7,0.05);
    glutSolidCube(50);
    glPopMatrix();


    ///lightholder
    glPushMatrix();
    glTranslatef(261.5,8,-80);
    glPushMatrix();
    glRotatef(30,0,0,1);
    glTranslatef(90,0,0);
    glScalef(0.4,0.4,0.4);
    glBegin(GL_QUADS);
    glVertex3f(0,50,0);
    glVertex3f(0,70,0);
    glVertex3f(0,70,20);
    glVertex3f(0,50,20);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-30,0,0,1);
    glScalef(0.4,0.4,0.4);
    glTranslatef(40,153,0);
    glBegin(GL_QUADS);
    glVertex3f(0,50,0);
    glVertex3f(0,70,0);
    glVertex3f(0,70,20);
    glVertex3f(0,50,20);
    glEnd();
    glPopMatrix();

     glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, textureTinshade);
     glTranslatef(5,0,0);
;
    glBegin(GL_QUADS);
    glVertex3f(49,62,0);
    glVertex3f(63,62,0);
    glVertex3f(59,69,0);
    glVertex3f(53.5,69,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, textureTinshade);
     glTranslatef(5,0,8);
    glBegin(GL_QUADS);
    glVertex3f(49,62,0);
    glVertex3f(63,62,0);
    glVertex3f(59,69,0);
    glVertex3f(53.5,69,0);
    glEnd();
    glPopMatrix();
    glPopMatrix();


    glPopMatrix();
}

void allStreetLightsStand()
{
    int lamp=-990;float lamp1=-600;float lamp2=-370;float lamp3=570;
        for(int i=0;i<10;i++)
        {
            ///horizontal up street light
            if(i<8)
            {
                if(i==4)
                {
                 lamp+=80;
                }
                 if(i==3)
                {
                 goto C;
                }
                glPushMatrix();
                glTranslatef(lamp,0,-30);
                lampPost();

                glPopMatrix();
                C:
                lamp=lamp+180;
            }
            ///vertical left street light
            if(i<10)
            {
                if(i==5)
                lamp1+=220;
            glPushMatrix();
            glTranslatef(-20,0,lamp1);
            glRotatef(90,0,1,0);
            lampPost();
            glPopMatrix();
            lamp1+=170;
            }
            ///horizontal down street light
            if(i<8)
            {

                    if(i==4)
                                    lamp2+=170;
                               glPushMatrix();
                            glTranslatef(lamp2,0,20);
                            glRotatef(180,0,1,0);
                            lampPost();
                            glPopMatrix();
                             lamp2+=180;
            }

            if(i<10)
            {
                   glPushMatrix();

                        if(i==5)
                        {
                          lamp3-=100;
                          goto A;
                        }
                        if(i==4)
                            goto A;
                        glTranslatef(20,0,lamp3);
                        glRotatef(-90,0,1,0);
                        lampPost();
                        A:
                        glPopMatrix();
                        lamp3-=180;
            }

        }
}


void allStreetBulbs()
{
            float  light=-467;float light1=-493;float light2=826;float light3=892;
    //float tree=600;float tree1=-900;

    for(int i=0;i<10;i++)
    {
        if(i<8)
        {
                        if(i==4)
                            {
                             light+=80;
                            }
                             if(i==3)
                            {
                             goto B;
                            }
                    glPushMatrix();
                    glTranslatef(light,5,-105);
                    glRotatef(-90,1,0,0);
                    glutSolidCone(50,70,10,10);
                    glPopMatrix();

                    glPopMatrix();
                    B:
                    light=light+180;
        }

        if(i<8)
        {
                    if(i==4)
                        light1+=170;
                    glPushMatrix();
                    glTranslatef(light1,7,96);
                    glRotatef(-90,1,0,0);
                    glutSolidCone(50,70,10,10);
                    glPopMatrix();

                 light1=light1+180;
        }

        if(i<10)
        {
                            if(i==5)
                            light2-=220;
                    glPushMatrix();
                    glTranslatef(103,7,light2);
                    glRotatef(-90,1,0,0);
                    glutSolidCone(50,70,10,10);
                    glPopMatrix();
                    light2-=170;
        }
        if(i<10)
        {
            glPushMatrix();

                            if(i==5)
                            {
                              light3-=100;
                              goto A1;
                            }
                            if(i==4)
                                goto A1;
                            glTranslatef(296.5,7,light3);
                            glRotatef(-90,1,0,0);
                            glutSolidCone(50,70,10,10);
                            A1:
                            glPopMatrix();
                            light3-=180;
        }

    }
}

void TrafficLight(int x,int y,int z,int startj1,int startk1)
{
    glPushMatrix();

        glTranslatef(x,y,z);
                                    glPushMatrix();
                                    if(startj1==0||(startj1==1&&startk1==1))
                                    glColor4f(1,0,0,0.1);
                                    else
                                        glColor4f(1,0,0,1);

                                    glTranslatef(0,100,0);
                                    glRotatef(90,0,1,0);
                                    glutSolidSphere(8,10,10);
                                    glPopMatrix();
                                    glPushMatrix();
                                    if(startj1==1&&startk1==1)
                                    glColor4f(1,1,0,1);
                                    else
                                        glColor4f(1,1,0,0.1);
                                    glTranslatef(20,100,0);
                                    glRotatef(90,0,1,0);
                                    glutSolidSphere(8,10,10);
                                    glPopMatrix();

                                    glPushMatrix();
                                    if(startk1==0||(startj1==1&&startk1==1))
                                    glColor4f(0,1,0,0.1);
                                    else
                                        glColor4f(0,1,0,1);

                                    glTranslatef(40,100,0);
                                    glRotatef(90,0,1,0);
                                    glutSolidSphere(8,10,10);
                                    glPopMatrix();

                                    glColor4f(0.5,0.5,0.5,1);
                                    glPushMatrix();
                                    glTranslatef(-20,50,0);
                                    //glRotatef(90,0,1,0);
                                    glScalef(0.03,1,0.03);
                                    glutSolidCube(120);
                                    glPopMatrix();

                                    glPushMatrix();
                                    glTranslatef(0,100,0);
                                    glRotatef(90,0,1,0);
                                    glScalef(0.02,0.02,0.7);
                                    glutSolidCube(120);
                                    glPopMatrix();


    glPopMatrix();
}

void waitingShade1()
{
                                     glPushMatrix();///push4
                                    glTranslatef(50,0,-150);
                                    glScalef(0.5,0.5,0.5);
     glBindTexture(GL_TEXTURE_2D, textureFloor);
     glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);
    glTexCoord2f(0,0);glVertex3f(250,1,-300);
    glTexCoord2f(1,0);glVertex3f(350,1,-300);
    glTexCoord2f(1,1);glVertex3f(350,20,-300);
    glTexCoord2f(0,1);glVertex3f(250,20,-300);
    glEnd();

    ///right
    glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(350,20,-300);
    glTexCoord2f(1,0);glVertex3f(350,1,-300);
    glTexCoord2f(1,1);glVertex3f(350,1,-550);
    glTexCoord2f(0,1);glVertex3f(350,20,-550);

    glEnd();

    ///left
        glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-300);
    glTexCoord2f(1,0);glVertex3f(250,1,-300);
    glTexCoord2f(1,1);glVertex3f(250,1,-550);
    glTexCoord2f(0,1);glVertex3f(250,20,-550);

    glEnd();

    ///back
      glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-550);
    glTexCoord2f(1,0);glVertex3f(250,1,-550);
    glTexCoord2f(1,1);glVertex3f(350,1,-550);
    glTexCoord2f(0,1);glVertex3f(350,20,-550);

    glEnd();

    ///lower part upside
          glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-300);
    glTexCoord2f(1,0);glVertex3f(350,20,-300);
    glTexCoord2f(1,1);glVertex3f(350,20,-550);
    glTexCoord2f(0,1);glVertex3f(250,20,-550);

    glEnd();

    ///samner brick
    glBindTexture(GL_TEXTURE_2D, textureStand);
    glPushMatrix();///push5
    glTranslatef(300,95,-340);
    glScalef(0.05,1,0.05);
    glutSolidCube(150);
    glPopMatrix();///pop5

    ///pechoner brick
    glPushMatrix();///push6
    glTranslatef(300,95,-500);
    glScalef(0.05,1,0.05);
    glutSolidCube(150);
    glPopMatrix();///pop6


    glPushMatrix();///push7
    glBindTexture(GL_TEXTURE_2D, textureTinshade);
    glTranslatef(-50,22,10);

    ///
    ///
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3f(280,100,-300);
    glTexCoord2f(1,0);glVertex3f(350,150,-300);
    glTexCoord2f(1,1);glVertex3f(350,150,-550);
    glTexCoord2f(0,1);glVertex3f(280,100,-550);
    glEnd();

    glBegin(GL_QUADS);
    ///glVertex3f(280,100,-300);
    glTexCoord2f(0,0);glVertex3f(350,150,-300);
    glTexCoord2f(1,0);glVertex3f(420,100,-300);
    glTexCoord2f(1,1);glVertex3f(420,100,-550);
    glTexCoord2f(0,1);glVertex3f(350,150,-550);
    glEnd();
    glPopMatrix();///pop7

                                                glPopMatrix();///push4
}


void waitingShade2()
{
                                 glPushMatrix();///push8
                                    glTranslated(-350,0,800);
                                    glScalef(0.5,0.5,0.5);
     glBindTexture(GL_TEXTURE_2D, textureFloor);
     glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);
    glTexCoord2f(0,0);glVertex3f(250,1,-300);
    glTexCoord2f(1,0);glVertex3f(350,1,-300);
    glTexCoord2f(1,1);glVertex3f(350,20,-300);
    glTexCoord2f(0,1);glVertex3f(250,20,-300);
    glEnd();

    ///right
    glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(350,20,-300);
    glTexCoord2f(1,0);glVertex3f(350,1,-300);
    glTexCoord2f(1,1);glVertex3f(350,1,-550);
    glTexCoord2f(0,1);glVertex3f(350,20,-550);

    glEnd();

    ///left
        glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-300);
    glTexCoord2f(1,0);glVertex3f(250,1,-300);
    glTexCoord2f(1,1);glVertex3f(250,1,-550);
    glTexCoord2f(0,1);glVertex3f(250,20,-550);

    glEnd();

    ///back
      glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-550);
    glTexCoord2f(1,0);glVertex3f(250,1,-550);
    glTexCoord2f(1,1);glVertex3f(350,1,-550);
    glTexCoord2f(0,1);glVertex3f(350,20,-550);

    glEnd();

    ///lower part upside
          glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);

    glTexCoord2f(0,0);glVertex3f(250,20,-300);
    glTexCoord2f(1,0);glVertex3f(350,20,-300);
    glTexCoord2f(1,1);glVertex3f(350,20,-550);
    glTexCoord2f(0,1);glVertex3f(250,20,-550);

    glEnd();

    ///samner brick
    glBindTexture(GL_TEXTURE_2D, textureStand);
    glPushMatrix();///push9
    glTranslatef(300,95,-340);
    glScalef(0.05,1,0.05);
    glutSolidCube(150);
    glPopMatrix();///pop9

    ///pechoner brick
    glPushMatrix();///push10
    glTranslatef(300,95,-500);
    glScalef(0.05,1,0.05);
    glutSolidCube(150);
    glPopMatrix();///pop10


    glPushMatrix();///push11
    glBindTexture(GL_TEXTURE_2D, textureTinshade);
    glTranslatef(-50,22,10);

    ///
    ///
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3f(280,100,-300);
    glTexCoord2f(1,0);glVertex3f(350,150,-300);
    glTexCoord2f(1,1);glVertex3f(350,150,-550);
    glTexCoord2f(0,1);glVertex3f(280,100,-550);
    glEnd();

    glBegin(GL_QUADS);
    ///glVertex3f(280,100,-300);
    glTexCoord2f(0,0);glVertex3f(350,150,-300);
    glTexCoord2f(1,0);glVertex3f(420,100,-300);
    glTexCoord2f(1,1);glVertex3f(420,100,-550);
    glTexCoord2f(0,1);glVertex3f(350,150,-550);
    glEnd();
    glPopMatrix();///pop11
                                                glPopMatrix();///pop8

}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////Shihaber Part
/////////////////////////////////////////////////////

void drawLeftBuilding()
{
    //draw building
	//boundary part
	glPushMatrix();
	   glTranslatef(300,0,100);
	   glScalef(1.5,2,1.5);
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, textureFrontBuilding);
                glBegin(GL_QUADS);

                glTexCoord2f(0,1); glVertex3f(-800, 200, -500);
                glTexCoord2f(1,1); glVertex3f(-680, 200, -500);
                glTexCoord2f(1,0); glVertex3f(-680, 0, -500);
                glTexCoord2f(0,0); glVertex3f(-800, 0, -500);
                glEnd();
                glPopMatrix();

                //right side view
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, textureFrontBuilding);
                glBegin(GL_QUADS);
                glTexCoord2f(0,0); glVertex3f(-680, 0, -500);
                glTexCoord2f(1,0); glVertex3f(-680, 0, -700);
                glTexCoord2f(1,1); glVertex3f(-680, 200, -700);
                glTexCoord2f(0,1); glVertex3f(-680, 200, -500);
                glEnd();
                glPopMatrix();

                //left side view
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, textureFrontBuilding);
                glBegin(GL_QUADS);
                glTexCoord2f(1,1); glVertex3f(-800, 200, -500);
                glTexCoord2f(0,1); glVertex3f(-800, 200, -700);
                glTexCoord2f(0,0); glVertex3f(-800, 0, -700);
                glTexCoord2f(1,0); glVertex3f(-800, 0, -500);
                glEnd();
                glPopMatrix();

                //back side view
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, textureFrontBuilding);
                glBegin(GL_QUADS);
                glTexCoord2f(0,1); glVertex3f(-800, 200, -700);
                glTexCoord2f(1,1); glVertex3f(-680, 200, -700);
                glTexCoord2f(1,0); glVertex3f(-680, 0, -700);
                glTexCoord2f(0,0); glVertex3f(-800, 0, -700);
                glEnd();
                glPopMatrix();

                //rooftop view
                glPushMatrix();
                glBegin(GL_QUADS);
                glVertex3f(-800, 200, -700);
                glVertex3f(-800, 200, -500);
                glVertex3f(-680, 200, -500);
                glVertex3f(-680, 200, -700);
                glEnd();
                glPopMatrix();

    glPopMatrix();
}

void drawMiddleBuilding()
{
    //middle building
    //front view
    glPushMatrix();
    glTranslatef(220,0,100);
    glScalef(1.5,1.5,1.5);
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureMiddleBuilding);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(-600, 180, -500);
                    glTexCoord2f(1,1); glVertex3f(-450, 180, -500);
                    glTexCoord2f(1,0); glVertex3f(-450, 0, -500);
                    glTexCoord2f(0,0); glVertex3f(-600, 0, -500);
                    glEnd();
                    glPopMatrix();

                    //right side view
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureMiddleBuilding);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(-450, 180, -500);
                    glTexCoord2f(0,0); glVertex3f(-450, 0, -500);
                    glTexCoord2f(1,0); glVertex3f(-450, 0, -650);
                    glTexCoord2f(1,1); glVertex3f(-450, 180, -650);
                    glEnd();
                    glPopMatrix();

                    //left side view
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureMiddleBuilding);
                    glBegin(GL_QUADS);
                    glTexCoord2f(1,0); glVertex3f(-600, 0, -500);
                    glTexCoord2f(1,1); glVertex3f(-600, 180, -500);
                    glTexCoord2f(0,1); glVertex3f(-600, 180, -650);
                    glTexCoord2f(0,0); glVertex3f(-600, 0, -650);
                    glEnd();
                    glPopMatrix();

                    //back side view
                    glPushMatrix();
                    glBegin(GL_QUADS);
                    glVertex3f(-600, 180, -650);
                    glVertex3f(-450, 180, -650);
                    glVertex3f(-450, 0, -650);
                    glVertex3f(-600, 0, -650);
                    glEnd();
                    glPopMatrix();

                    //rooftop view
                    glPushMatrix();
                    glBegin(GL_QUADS);
                    glVertex3f(-600, 180, -500);
                    glVertex3f(-450, 180, -500);
                    glVertex3f(-450, 180, -650);
                    glVertex3f(-600, 180, -650);
                    glEnd();
                    glPopMatrix();

        glPopMatrix();
}

void drawRightBuilding()
{
    //--------rightmost building-----------//
    //front view
    glPushMatrix();///1
    glScalef(1.5,1.5,1.5);
    glTranslatef(130,0,80);
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureRightBuilding);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(-400, 230, -500);
                    glTexCoord2f(1,1); glVertex3f(-230, 230, -500);
                    glTexCoord2f(1,0); glVertex3f(-230, 0, -500);
                    glTexCoord2f(0,0); glVertex3f(-400, 0, -500);
                    glEnd();
                    glPopMatrix();

                    //right side view
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureRightBuildingRightSide);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(-230, 230, -500);
                    glTexCoord2f(0,0); glVertex3f(-230, 0, -500);
                    glTexCoord2f(1,0); glVertex3f(-230, 0, -700);
                    glTexCoord2f(1,1); glVertex3f(-230, 230, -700);
                    glEnd();
                    glPopMatrix();

                    //left view
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureRightBuildingRightSide);
                    glBegin(GL_QUADS);
                    glTexCoord2f(1,0); glVertex3f(-400, 0, -500);
                    glTexCoord2f(1,1); glVertex3f(-400, 230, -500);
                    glTexCoord2f(0,1); glVertex3f(-400, 230, -700);
                    glTexCoord2f(0,0); glVertex3f(-400, 0, -700);
                    glEnd();
                    glPopMatrix();

                    //back view
                    glPushMatrix();
                    glBegin(GL_QUADS);
                    glVertex3f(-400, 230, -700);
                    glVertex3f(-230, 230, -700);
                    glVertex3f(-230, 0, -700);
                    glVertex3f(-400, 0, -700);
                    glEnd();
                    glPopMatrix();

                    //rooftop view
                    glPushMatrix();
                    glBegin(GL_QUADS);
                    glVertex3f(-400, 230, -500);
                    glVertex3f(-230, 230, -500);
                    glVertex3f(-230, 230, -700);
                    glVertex3f(-400, 230, -700);
                    glEnd();
                    glPopMatrix();

        glPopMatrix();
}

void drawSuperShop()
{
    //front view of the shop

        glPushMatrix();
        glTranslatef(1000,0,300);
        glRotatef(-110,0,1,0);
        glScalef(1.5,1.5,1.5);
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureMainShop);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(130, 90, 380);
                    glTexCoord2f(0,0); glVertex3f(130, 4, 380);
                    glTexCoord2f(1,0); glVertex3f(400, 1, 380);
                    glTexCoord2f(1,1); glVertex3f(400, 100, 380);
                    glEnd();
                    glPopMatrix();

                    //right side view of the shop
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureSportsLeftSide);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,0); glVertex3f(400, 1, 380);
                    glTexCoord2f(0,1); glVertex3f(400, 100, 380);
                    glTexCoord2f(1,1); glVertex3f(400, 100, 180);
                    glTexCoord2f(1,0); glVertex3f(400, 1, 180);
                    glEnd();
                    glPopMatrix();

                    //left side view of the shop
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureSportsLeftSide);
                    glBegin(GL_QUADS);
                    glTexCoord2f(1,0); glVertex3f(130, 4, 380);
                    glTexCoord2f(1,1); glVertex3f(130, 90, 380);
                    glTexCoord2f(0,1); glVertex3f(130, 90, 180);
                    glTexCoord2f(0,0); glVertex3f(130, 4, 180);
                    glEnd();
                    glPopMatrix();

                    //back side view of the shop
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureMainShop);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0,1); glVertex3f(130, 90, 180);
                    glTexCoord2f(0,0); glVertex3f(130, 4, 180);
                    glTexCoord2f(1,0); glVertex3f(400, 1, 180);
                    glTexCoord2f(1,1); glVertex3f(400, 100, 180);
                    glEnd();
                    glPopMatrix();

                    //rooftop view of the shop
                    glPushMatrix();
                    glBegin(GL_QUADS);
                    glVertex3f(400, 100, 380);
                    glVertex3f(130, 90, 380);
                    glVertex3f(130, 90, 180);
                    glVertex3f(400, 100, 180);
                    glEnd();
                    glPopMatrix();

                    //signboard portion of the shop
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, textureShopLogo);
                    glBegin(GL_QUADS);
                    glTexCoord2f(1,0); glVertex3f(400, 100, 380);
                    glTexCoord2f(0,0); glVertex3f(130, 90, 380);
                    glTexCoord2f(0,1); glVertex3f(130, 110, 380);
                    glTexCoord2f(1,1); glVertex3f(400, 120, 380);
                    glEnd();
                    glPopMatrix();

        glPopMatrix();
}

///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////   Shihaber Part Ends
/////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                ///Meghla's Part Start
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void car(int x, int y, int z){
    int h = 25;
//car upper part starts
    int upperXright = 15, upperXleft = 30;
    int upperYup = 40, upperYdown = 20;

    glBindTexture(GL_TEXTURE_2D,textureWall);
    //car front
    glBegin(GL_POLYGON);

    //glColor3ub(234, 56, 78);

	glVertex3f(x+upperXright, y+upperYup, z);
	glVertex3f(x+upperXleft, y+upperYdown, z);
	glVertex3f(x-upperXleft, y+upperYdown, z);
	glVertex3f(x-upperXright, y+upperYup, z);

	glEnd();

	//car right
	glBegin(GL_POLYGON);

    //glColor3ub(34, 56, 78);

	glVertex3f(x+upperXright, y+upperYup, z);
	glVertex3f(x+upperXleft, y+upperYdown, z);
	glVertex3f(x+upperXleft, y+upperYdown, z+h);
	glVertex3f(x+upperXright, y+upperYup, z+h);

	glEnd();

	//car back
	glBegin(GL_POLYGON);

    //glColor3ub(34, 56, 178);

	glVertex3f(x+upperXright, y+upperYup, z+h);
	glVertex3f(x+upperXleft, y+upperYdown, z+h);
	glVertex3f(x-upperXleft, y+upperYdown, z+h);
	glVertex3f(x-upperXright, y+upperYup, z+h);

	glEnd();

	//car left
	glBegin(GL_POLYGON);

    //glColor3ub(34, 219, 78);

	glVertex3f(x-upperXright, y+upperYup, z);
	glVertex3f(x-upperXleft, y+upperYdown, z);
	glVertex3f(x-upperXleft, y+upperYdown, z+h);
	glVertex3f(x-upperXright, y+upperYup, z+h);


	glEnd();

	//car roof
	glBegin(GL_POLYGON);

    //glColor3ub(34, 19, 78);

	glVertex3f(x-upperXright, y+upperYup, z);
	glVertex3f(x+upperXright, y+upperYup, z);
	glVertex3f(x+upperXright, y+upperYup, z+h);
	glVertex3f(x-upperXright, y+upperYup, z+h);

	glEnd();

	///car upper part ends


	///car lower part starts

	glBindTexture(GL_TEXTURE_2D, textureSky1);

	int lowerXright = 40, lowerXleft = 42;
    int lowerYup = 16, lowerYdown = 8;

    glBegin(GL_POLYGON);

    //lower front
    //glColor3ub(24, 56, 78);

	glVertex3f(x+upperXleft, y+upperYdown, z);
	glVertex3f(x+lowerXright, y+lowerYup, z);
	glVertex3f(x+lowerXleft, y+lowerYdown, z);
	glVertex3f(x-lowerXleft, y+lowerYdown, z);
	glVertex3f(x-lowerXright, y+lowerYup, z);
	glVertex3f(x-upperXleft, y+upperYdown, z);

	glEnd();

	glBegin(GL_POLYGON);

    //lower right
    //glColor3ub(124, 56, 78);

	glVertex3f(x+lowerXright, y+lowerYup, z);
	glVertex3f(x+lowerXleft, y+lowerYdown, z);
	glVertex3f(x+lowerXleft, y+lowerYdown, z+h);
	glVertex3f(x+lowerXright, y+lowerYup, z+h);

	glEnd();

	glBegin(GL_POLYGON);

    //lower left
    //glColor3ub(124, 56, 78);

	glVertex3f(x-lowerXright, y+lowerYup, z);
	glVertex3f(x-lowerXleft, y+lowerYdown, z);
	glVertex3f(x-lowerXleft, y+lowerYdown, z+h);
	glVertex3f(x-lowerXright, y+lowerYup, z+h);
	glEnd();

	glBegin(GL_POLYGON);

    //lower back
    //glColor3ub(14, 56, 208);

	glVertex3f(x+upperXleft, y+upperYdown, z+h);
	glVertex3f(x+lowerXright, y+lowerYup, z+h);
	glVertex3f(x+lowerXleft, y+lowerYdown, z+h);
	glVertex3f(x-lowerXleft, y+lowerYdown, z+h);
	glVertex3f(x-lowerXright, y+lowerYup, z+h);
	glVertex3f(x-upperXleft, y+upperYdown, z+h);

	glEnd();

	glBegin(GL_POLYGON);

    //lower right roof
    //glColor3ub(124, 56, 178);

	glVertex3f(x+upperXleft, y+upperYdown, z);
	glVertex3f(x+lowerXright, y+lowerYup, z);
	glVertex3f(x+lowerXright, y+lowerYup, z+h);
	glVertex3f(x+upperXleft, y+upperYdown, z+h);

	glEnd();

	glBegin(GL_POLYGON);

    //lower left roof
    //glColor3ub(124, 56, 178);

	glVertex3f(x-upperXleft, y+upperYdown, z);
	glVertex3f(x-lowerXright, y+lowerYup, z);
	glVertex3f(x-lowerXright, y+lowerYup, z+h);
	glVertex3f(x-upperXleft, y+upperYdown, z+h);

	glEnd();

	glBegin(GL_POLYGON);

    //lower roof
    //glColor3ub(24, 156, 18);

	glVertex3f(x-lowerXright, y+lowerYdown, z);
	glVertex3f(x+lowerXright, y+lowerYdown, z);
	glVertex3f(x+lowerXright, y+lowerYdown, z+h);
	glVertex3f(x-lowerXright, y+lowerYdown, z+h);

	glEnd();

	///car lower part ends


	///car wheel

	glBindTexture(GL_TEXTURE_2D,textureWall);

	glBegin(GL_POLYGON);

	//wheel front left
	//glColor3ub(24, 156, 18);
    glColor4f(0,0,0,1);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(x+cx+upperXleft-10, y+cy+lowerYdown, z-1.05);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel front right
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(x-cx-upperXleft+10, y+cy+lowerYdown, z-1.05);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel back left
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(x+cx+upperXleft-10, y+cy+lowerYdown, z+h+1.05);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel back right
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(x-cx-upperXleft+10, y+cy+lowerYdown, z+h+1.05);
	}
	glEnd();
	glColor4f(1,1,1,1);
}

void carZ(int z, int y, int x){
    int h = 25;
//car upper part starts
    int upperXright = 15, upperXleft = 30;
    int upperYup = 40, upperYdown = 20;

    glBindTexture(GL_TEXTURE_2D,textureWall);
    //car front
    glBegin(GL_POLYGON);

    //glColor3ub(234, 56, 78);

    glVertex3f(z, y+upperYup, x+upperXright);
	glVertex3f(z, y+upperYdown, x+upperXleft);
	glVertex3f(z, y+upperYdown, x-upperXleft);
	glVertex3f(z, y+upperYup, x-upperXright);

	glEnd();

	//car right
	glBegin(GL_POLYGON);

    //glColor3ub(34, 56, 78);

	glVertex3f(z, y+upperYup, x+upperXright);
	glVertex3f(z, y+upperYdown, x+upperXleft);
	glVertex3f(z+h, y+upperYdown, x+upperXleft);
	glVertex3f(z+h, y+upperYup, x+upperXright);

	glEnd();

	//car back
	glBegin(GL_POLYGON);

    //glColor3ub(34, 56, 178);

	glVertex3f(z+h, y+upperYup, x+upperXright);
	glVertex3f(z+h, y+upperYdown, x+upperXleft);
	glVertex3f(z+h, y+upperYdown, x-upperXleft);
	glVertex3f(z+h, y+upperYup, x-upperXright);

	glEnd();

	//car left
	glBegin(GL_POLYGON);

    //glColor3ub(34, 219, 78);

	glVertex3f(z, y+upperYup, x-upperXright);
	glVertex3f(z, y+upperYdown, x-upperXleft);
	glVertex3f(z+h, y+upperYdown, x-upperXleft);
	glVertex3f(z+h, y+upperYup, x-upperXright);


	glEnd();

	//car roof
	glBegin(GL_POLYGON);

    //glColor3ub(34, 19, 78);

	glVertex3f(z, y+upperYup, x-upperXright);
	glVertex3f(z, y+upperYup, x+upperXright);
	glVertex3f(z+h, y+upperYup, x+upperXright);
	glVertex3f(z+h, y+upperYup, x-upperXright);

	glEnd();

	///car upper part ends


	///car lower part starts

	glBindTexture(GL_TEXTURE_2D, textureSky1);

	int lowerXright = 40, lowerXleft = 42;
    int lowerYup = 16, lowerYdown = 8;

    glBegin(GL_POLYGON);

    //lower front
    //glColor3ub(24, 56, 78);

	glVertex3f(z, y+upperYdown, x+upperXleft);
	glVertex3f(z, y+lowerYup, x+lowerXright);
	glVertex3f(z, y+lowerYdown, x+lowerXleft);
	glVertex3f(z, y+lowerYdown, x-lowerXleft);
	glVertex3f(z, y+lowerYup, x-lowerXright);
	glVertex3f(z, y+upperYdown, x-upperXleft);

	glEnd();

	glBegin(GL_POLYGON);

    //lower right
    //glColor3ub(124, 56, 78);

	glVertex3f(z, y+lowerYup, x+lowerXright);
	glVertex3f(z, y+lowerYdown, x+lowerXleft);
	glVertex3f(z+h, y+lowerYdown, x+lowerXleft);
	glVertex3f(z+h, y+lowerYup, x+lowerXright);

	glEnd();

	glBegin(GL_POLYGON);

    //lower left
    //glColor3ub(124, 56, 78);

	glVertex3f(z, y+lowerYup, x-lowerXright);
	glVertex3f(z, y+lowerYdown, x-lowerXleft);
	glVertex3f(z+h, y+lowerYdown, x-lowerXleft);
	glVertex3f(z+h, y+lowerYup, x-lowerXright);
	glEnd();

	glBegin(GL_POLYGON);

    //lower back
    //glColor3ub(14, 56, 208);

	glVertex3f(z+h, y+upperYdown, x+upperXleft);
	glVertex3f(z+h, y+lowerYup, x+lowerXright);
	glVertex3f(z+h, y+lowerYdown, x+lowerXleft);
	glVertex3f(z+h, y+lowerYdown, x-lowerXleft);
	glVertex3f(z+h, y+lowerYup, x-lowerXright);
	glVertex3f(z+h, y+upperYdown, x-upperXleft);

	glEnd();

	glBegin(GL_POLYGON);

    //lower right roof
    //glColor3ub(124, 56, 178);

	glVertex3f(z, y+upperYdown, x+upperXleft);
	glVertex3f(z, y+lowerYup, x+lowerXright);
	glVertex3f(z+h, y+lowerYup, x+lowerXright);
	glVertex3f(z+h, y+upperYdown, x+upperXleft);

	glEnd();

	glBegin(GL_POLYGON);

    //lower left roof
    //glColor3ub(124, 56, 178);

	glVertex3f(z, y+upperYdown, x-upperXleft);
	glVertex3f(z, y+lowerYup, x-lowerXright);
	glVertex3f(z+h, y+lowerYup, x-lowerXright);
	glVertex3f(z+h, y+upperYdown, x-upperXleft);

	glEnd();

	glBegin(GL_POLYGON);

    //lower roof
    //glColor3ub(24, 156, 18);

	glVertex3f(z, y+lowerYdown, x-lowerXright);
	glVertex3f(z, y+lowerYdown, x+lowerXright);
	glVertex3f(z+h, y+lowerYdown, x+lowerXright);
	glVertex3f(z+h, y+lowerYdown, x-lowerXright);

	glEnd();

	///car lower part ends

	///car wheel

	glBindTexture(GL_TEXTURE_2D,textureWall);

	glBegin(GL_POLYGON);

	//wheel front left
	//glColor3ub(24, 156, 18);
    glColor4f(0,0,0,1);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(z-1.05, y+cy+lowerYdown, x+cx+upperXleft-10);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel front right
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(z-1.05, y+cy+lowerYdown, x-cx-upperXleft+10);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel back left
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(z+h+1.05, y+cy+lowerYdown, x+cx+upperXleft-10);
	}
	glEnd();

	glBegin(GL_POLYGON);

	//wheel back right
	//glColor3ub(24, 156, 18);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float r=6;
		float cx = r * cos(A);
		float cy = r * sin(A);
		glVertex3f(z+h+1.05, y+cy+lowerYdown, x-cx-upperXleft+10);
	}
	glEnd();
	glColor4f(1,1,1,1);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                ///Meghla's Part End
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myCar()
{
    glPushMatrix();
                                    glScalef(0.5,0.5,0.5);
                                glPushMatrix();
                                            glPushMatrix();
                                            glTranslatef(200,50,0);
                                            glBegin(GL_QUADS);
                                            glVertex3f(0,10,0);
                                            glVertex3f(30,10,0);
                                            glVertex3f(30,25,0);
                                            glVertex3f(0,25,0);
                                            glEnd();

                                             glBegin(GL_TRIANGLES);
                                            glVertex3f(0,10,0);
                                            glVertex3f(0,25,0);
                                            glVertex3f(-20,10,0);
                                            glEnd();

                                            glBegin(GL_TRIANGLES);
                                            glVertex3f(30,10,0);
                                            glVertex3f(30,25,0);
                                            glVertex3f(50,10,0);
                                            glEnd();

                                            glBegin(GL_POLYGON);
                                            glVertex3f(-50,10,0);
                                            glVertex3f(-65,0,0);
                                            glVertex3f(-65,-15,0);
                                            glVertex3f(95,-15,0);
                                            glVertex3f(95,0,0);
                                            glVertex3f(80,10,0);
                                            glEnd();

                                            glPopMatrix();
                                glPopMatrix();


                                        glPushMatrix();
                                        glTranslatef(0,0,50);
                                                glPushMatrix();
                                                glTranslatef(200,50,0);
                                                    glBegin(GL_QUADS);
                                                    glVertex3f(0,10,0);
                                                    glVertex3f(30,10,0);
                                                    glVertex3f(30,25,0);
                                                    glVertex3f(0,25,0);
                                                    glEnd();

                                                     glBegin(GL_TRIANGLES);
                                                    glVertex3f(0,10,0);
                                                    glVertex3f(0,25,0);
                                                    glVertex3f(-20,10,0);
                                                    glEnd();

                                                    glBegin(GL_TRIANGLES);
                                                    glVertex3f(30,10,0);
                                                    glVertex3f(30,25,0);
                                                    glVertex3f(50,10,0);
                                                    glEnd();

                                                    glBegin(GL_POLYGON);
                                                    glVertex3f(-50,10,0);
                                                    glVertex3f(-65,0,0);
                                                    glVertex3f(-65,-15,0);
                                                    glVertex3f(95,-15,0);
                                                    glVertex3f(95,0,0);
                                                    glVertex3f(80,10,0);
                                                    glEnd();

                                                glPopMatrix();
                                glPopMatrix();

                                glPushMatrix();
                                            glTranslatef(200,50,0);
                                            glBegin(GL_QUADS);
                                            glVertex3f(95,-15,0);
                                            glVertex3f(95,-15,50);
                                            glVertex3f(95,0,50);
                                            glVertex3f(95,0,0);
                                            glEnd();

                                             glBegin(GL_QUADS);
                                            glVertex3f(95,0,0);
                                            glVertex3f(95,0,50);
                                            glVertex3f(80,10,50);
                                            glVertex3f(80,10,0);
                                            glEnd();

                                            glBegin(GL_QUADS);
                                            glVertex3f(80,10,0);
                                            glVertex3f(80,10,50);
                                            glVertex3f(50,10,50);
                                            glVertex3f(50,10,0);
                                            glEnd();

                                            glBegin(GL_QUADS);
                                            glVertex3f(50,10,0);
                                            glVertex3f(50,10,50);
                                            glVertex3f(30,25,50);
                                            glVertex3f(30,25,0);
                                            glEnd();

                                             glBegin(GL_QUADS);
                                            glVertex3f(0,25,0);
                                            glVertex3f(0,25,50);
                                            glVertex3f(30,25,50);
                                            glVertex3f(30,25,0);
                                            glEnd();

                                            glBegin(GL_QUADS);
                                            glVertex3f(0,25,0);
                                            glVertex3f(0,25,50);
                                            glVertex3f(-20,10,50);
                                            glVertex3f(-20,10,0);
                                            glEnd();

                                            glBegin(GL_QUADS);
                                            glVertex3f(0,10,0);
                                            glVertex3f(0,10,50);
                                            glVertex3f(-50,10,50);
                                            glVertex3f(-50,10,0);
                                            glEnd();
                                            //glBindTexture(GL_TEXTURE_2D,textureCarFrontLight);
                                            glBegin(GL_QUADS);
                                            //glTexCoord2f(0,0);
                                            glVertex3f(-50,10,0);
                                            //glTexCoord2f(1,0);
                                            glVertex3f(-50,10,50);
                                            //glTexCoord2f(1,1);
                                            glVertex3f(-65,0,50);
                                            //glTexCoord2f(0,1);
                                            glVertex3f(-65,0,0);
                                            glEnd();
                                            //glBindTexture(GL_TEXTURE_2D,textureCarFrontLight);
                                            glBegin(GL_QUADS);
                                            glVertex3f(-65,0,0);
                                            glVertex3f(-65,0,50);
                                            glVertex3f(-65,-15,50);
                                            glVertex3f(-65,-15,0);
                                            glEnd();
                                                                    ///chaka
                                                                    glPushMatrix();
                                                                    glColor4f(0,0,0,1);
                                                                    glTranslatef(5,0,0);
                                                                                glPushMatrix();
                                                                                glTranslatef(50,-20,0);
                                                                                glutSolidTorus(4,10,20,20);
                                                                                            glPushMatrix();
                                                                                            glColor4f(0.5,0.5,0.5,1);
                                                                                            glScalef(1,1,0.5);
                                                                                            gluSphere(quad,10,10,10);
                                                                                            glColor4f(1,1,1,1);
                                                                                            glPopMatrix();
                                                                                            glColor4f(1,1,1,1);
                                                                                glPopMatrix();

                                                                                glPushMatrix();
                                                                                glColor4f(0,0,0,1);
                                                                                glTranslatef(50,-20,47);
                                                                                glutSolidTorus(4,10,20,25);
                                                                                            glPushMatrix();
                                                                                            glColor4f(0.5,0.5,0.5,1);
                                                                                            glScalef(1,1,0.5);
                                                                                            gluSphere(quad,10,10,10);
                                                                                            glColor4f(1,1,1,1);
                                                                                            glPopMatrix();
                                                                                            glColor4f(1,1,1,1);
                                                                                glPopMatrix();
                                                                    glPopMatrix();


                                                                    glPushMatrix();
                                                                    glColor4f(0,0,0,1);
                                                                    glTranslatef(-75,0,0);
                                                                                glPushMatrix();
                                                                                glTranslatef(50,-20,0);
                                                                                glutSolidTorus(4,10,20,20);
                                                                                            glPushMatrix();
                                                                                            glColor4f(0.5,0.5,0.5,1);
                                                                                            glScalef(1,1,0.5);
                                                                                            gluSphere(quad,10,10,10);
                                                                                            glColor4f(1,1,1,1);
                                                                                            glPopMatrix();
                                                                                            glColor4f(1,1,1,1);
                                                                                glPopMatrix();

                                                                                glPushMatrix();
                                                                                glColor4f(0,0,0,1);
                                                                                glTranslatef(50,-20,47);
                                                                                glutSolidTorus(4,10,20,25);
                                                                                            glPushMatrix();
                                                                                            glColor4f(0.5,0.5,0.5,1);
                                                                                            glScalef(1,1,0.5);
                                                                                            gluSphere(quad,10,10,10);
                                                                                            glColor4f(1,1,1,1);
                                                                                            glPopMatrix();
                                                                                            glColor4f(1,1,1,1);
                                                                                glPopMatrix();
                                                                    glPopMatrix();




                                glPopMatrix();

    glPopMatrix();
}

void myCar2()
{
    glPushMatrix();
    glTranslatef(80,0,0);
    glRotatef(90,0,1,0);
                            //myCar1();
                                    glPushMatrix();

    glTranslatef(0,-10,50);
    myCar();
        glPopMatrix();
    glPopMatrix();
}



void renderScene(void) {


	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);
    if(upDown)
        computeUp(upDown);
	if(Vangle)
        computeUPangle(Vangle);


	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	// Set the camera
	gluLookAt(	x, y+upangle, z,
				x+lx, y,  z+lz,
				0.0f, 1.0f,  0.0f);

// Draw ground
 quad = gluNewQuadric();
        gluQuadricNormals(quad,GLU_SMOOTH);
        gluQuadricTexture(quad, GLU_TRUE);
        gluQuadricTexture(quad, 500);
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, textureGrass);


     GLUquadric *qobj = gluNewQuadric();

    gluQuadricTexture(qobj,GL_TRUE);

    glBindTexture(GL_TEXTURE_2D,textureGeneral);

    glPushMatrix();///push1

    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(90,0,0,1);
    gluSphere(qobj,1600,200,200);
    gluDeleteQuadric(qobj);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();///pop1
    if(textureSky!=textureGeneral)
        //glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glColor3f(0.5,0.5,0.5);
    //////////////////////////////////////////
    ////////////////////////////////////////
    /////////////////////////////////////////
    glPushMatrix();///push2
    glTranslatef(200,1,0);

     glBindTexture(GL_TEXTURE_2D, textureParking);
    glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-1000, 1.0f, 1000);
		glTexCoord2f(1,0);glVertex3f(-350, 1.0f,  1000);
		glTexCoord2f(1,1);glVertex3f(-350, 1.0f,  200);
		glTexCoord2f(0,1);glVertex3f(-1000, 1.0f, 200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureGrass);
        for(float i=-1000;i<751;i+=250)
        {
            for(float j=-1000;j<751;j+=250)
            {glBegin(GL_QUADS);
                    glTexCoord2f(0,0);glVertex3f(j, 0.0f,i);
                    glTexCoord2f(1,0);glVertex3f(j+250, 0.0f,i);
                    glTexCoord2f(1,1);glVertex3f(j+250, 0.0f,i+250);
                    glTexCoord2f(0,1);glVertex3f(j, 0.0f,i+250);
             glEnd();
            }
        }

	    glBindTexture(GL_TEXTURE_2D, textureRoad);

	    ///vertical
	    for(int i=-1000;i<601;i+=400)

    {
        glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);
    glTexCoord2f(0,0);glVertex3f(-100,3,i);
    glTexCoord2f(1,0);glVertex3f(100,3,i);
    glTexCoord2f(1,1);glVertex3f(100,3,i+400);
    glTexCoord2f(0,1);glVertex3f(-100,3,i+400);
    glEnd();

    ///horizontal
    glPushMatrix();///push3
    glTranslatef(0,1,0);
      glBindTexture(GL_TEXTURE_2D, textureRoad);
    glBegin(GL_QUADS);
    //glColor3f(0.5,0.3,0);
    glTexCoord2f(0,0);glVertex3f(i,4,-100);
    glTexCoord2f(1,0);glVertex3f(i,4,100);
    glTexCoord2f(1,1);glVertex3f(i+400,4,100);
    glTexCoord2f(0,1);glVertex3f(i+400,4,-100);
    glEnd();
    glPopMatrix();///pop3
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
                glPushMatrix();
                        drawLeftBuilding();

                        //glBindTexture(GL_TEXTURE_2D, textureGray9);
                        drawMiddleBuilding();

                        //glBindTexture(GL_TEXTURE_2D, textureSky4);
                        drawRightBuilding();
                glPopMatrix();

                glPushMatrix();
                         glTranslatef(0,0,400);
                                //drawLeftBuilding();
                                glPushMatrix();
                                glTranslatef(-200,0,0);
                                drawRightBuilding();
                                glPopMatrix();

                                //glBindTexture(GL_TEXTURE_2D, textureGray9);
                                glPushMatrix();
                                glTranslatef(-200,0,0);
                                drawMiddleBuilding();
                                glPopMatrix();

                                //glBindTexture(GL_TEXTURE_2D, textureSky4);
                                //drawRightBuilding();
                                glPushMatrix();
                                glTranslatef(580,0,0);
                                drawLeftBuilding();
                                glPopMatrix();
                 glPopMatrix();
                 drawSuperShop();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///Waiting Shade1
    ///front
    waitingShade1();
    glPushMatrix();
    glTranslatef(0,0,-150);
    waitingShade1();
    glPopMatrix();

        ///waitingshade2
        ///Waiting Shade2
    ///front
    waitingShade2();
    glPushMatrix();
    glTranslatef(0,0,-150);
    waitingShade2();
    glPopMatrix();



        //lampPost();
        /////////////////////////////////////
        ////////////////////////////////
        /////////////////////////////////
        ///All Street Lights
        allStreetLightsStand();

    ///traffic light1
 {
        /*glPushMatrix();
        glTranslatef(120,0,130);
        glRotatef(180,0,1,0);
        float j=0;
        for(float i=0;i<70;i+=0.5)
        {

        glPushMatrix();
        if(i>55)
        {
            j+=0.3;
            glTranslatef(j,i,0);
        }
        else
        {
            glTranslatef(0,i,0);}
        glRotatef(-90,1,0,0);
        glutSolidTorus(0.9,1,25,25);
        glPopMatrix();
        }
        glPushMatrix();
        glutSolidCube(15);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(23,87,0);
        glRotatef(-35,0,0,1);
        glScalef(0.15,0.5,0.05);
        glutSolidCube(100);
        glPopMatrix();

        glPopMatrix();*/
}



        ///traffic light2
 {

        /*glPushMatrix();
        glTranslatef(-120,0,-130);
        glRotatef(-90,0,1,0);
//        float j=0;
                j=0;
        for(float i=0;i<70;i+=0.5)
        {
        glPushMatrix();
        if(i>55)
        {
            j+=0.3;
            glTranslatef(j,i,0);
        }
        else
        {glTranslatef(0,i,0);}
        glRotatef(-90,1,0,0);
        glutSolidTorus(0.9,1,25,25);
        glPopMatrix();
        }
        glPushMatrix();
        glutSolidCube(15);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(23,87,0);
        glRotatef(-35,0,0,1);
        glScalef(0.15,0.5,0.05);
        glutSolidCube(100);
        glPopMatrix();

        glPopMatrix();*/
}

        glPushMatrix();///push12
        glBindTexture(GL_TEXTURE_2D, textureBoundaryWall);
        glTranslatef(422,0,-200);
        glScalef(1,0.8,0.095);
        glutSolidCube(200);
        glPopMatrix();///pop12

        glPushMatrix();///push12.1
        glBindTexture(GL_TEXTURE_2D, textureBoundaryWall);
        glTranslatef(822,0,-200);
        glScalef(1,0.457,0.054);
        glutSolidCube(350);
        glPopMatrix();///pop12.1


                        int oC=0;
                        glPushMatrix();///push12.2
                        glTranslatef(520,0,-200.5);
                        if(gate==1)
                        {
                            for(float i=0;i<40;i+=0.01)
                            {
                                glRotatef(0+i,0,1,0);
                            }
                        }
                        if(gate==0)
                        {
                                glRotatef(0,0,1,0);
                                //gate=0;
                        }

                        glBindTexture(GL_TEXTURE_2D, textureGate);
                        glBegin(GL_QUADS);
                        glTexCoord2f(0,0);glVertex3f(0,0,0);
                        glTexCoord2f(1,0);glVertex3f(65,0,0);
                        glTexCoord2f(1,1);glVertex3f(65,100,0);
                        glTexCoord2f(0,1);glVertex3f(0,100,0);
                        glEnd();
                        glPopMatrix();///pop12.2

                        glPushMatrix();///push12.3
                        glTranslatef(645,0,-200.5);
                        if(gate==1&&distGate<80)
                        {
                            for(float i=0;i<40;i+=0.01)
                                glRotatef(180-i,0,1,0);
                        }
                        else
                        glRotatef(180,0,1,0);///minus
                        glBindTexture(GL_TEXTURE_2D, textureGate);
                        glBegin(GL_QUADS);
                        glTexCoord2f(0,0);glVertex3f(0,0,0);
                        glTexCoord2f(1,0);glVertex3f(65,0,0);
                        glTexCoord2f(1,1);glVertex3f(65,100,0);
                        glTexCoord2f(0,1);glVertex3f(0,100,0);
                        glEnd();
                        glPopMatrix();///pop12.3



        glPushMatrix();///push13


        glBindTexture(GL_TEXTURE_2D,textureBoundaryWall);
        glTranslatef(330,2,-600);
        glRotatef(-90,0,1,0);
        glScalef(1,0.2,0.02);
        glutSolidCube(800);
        glPopMatrix();///pop13

    glPopMatrix();///pop2

    ////////////////////////////////
    ///////////ENDDDDDDDDDD OFFFFFFFFFFFF POPPPPPPP2222222222222222222
    ////////////////////////////////////////////////////



/////////////////////////////////////////////////
/////////////////////////////////////////////////
//////////////////////////////////////////////////
    glDisable(GL_TEXTURE_2D);

    if(textureGeneral!=textureSky){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,0.82,0.7,0.3);
    float  light=-467;float light1=-493;float light2=826;float light3=892;
    //float tree=600;float tree1=-900;
    allStreetBulbs();


       glDisable(GL_BLEND);
    glColor4f(1,1,1,1);

    }

    //////////////////////////////////////////
    ///////////////////////////////////////////////
    ////////////////////////////////////////////////
    float tree=600;float tree1=-900;
                for(int i=0;i<7;i++){
                        if(textureGeneral==textureNight)
                        glColor3f(0.5,0.5,0.5);
                glPushMatrix();///push18
                if(i>=3)
                    {glTranslatef(tree,0,tree1);
                        makeTree();
                    tree1+=190;
                    }
                    else
                {glTranslatef(tree,0,-900);
                makeTree();
                tree+=190;}

                glPopMatrix();///pop18
                }

                tree=600;tree1=-800;
            for(int i=0;i<5;i++)
            {
                if(textureGeneral==textureNight)
                        glColor3f(0.5,0.5,0.5);

           glPushMatrix();
           if(i>=2)
                    {glTranslatef(tree,0,tree1);
                        makeTree();
                    tree1+=190;
                    }
                    else
                {glTranslatef(tree,0,-800);
                makeTree();
                tree+=190;}

           glPopMatrix();
            }
    glColor3f(1,1,1);

    //glPushMatrix();
    //glutSolidCube(10);
    //glPopMatrix();

    glDisable(GL_BLEND);
    glColor4f(1,1,1,1);





    glPushMatrix();
    glTranslatef(522,0,-190);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureBoundaryWall);
    for(float i=-1;i<102;i+=102)
    {
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3f(i,0,3);
    glTexCoord2f(1,0);glVertex3f(i+100,0,3);
    glTexCoord2f(1,1);glVertex3f(i+100,80,3);
    glTexCoord2f(0,1);glVertex3f(i,80,3);
    glEnd();
    }

        for(float i=325;i<570;i+=116.67)
    {
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3f(i,0,3);
    glTexCoord2f(1,0);glVertex3f(i+116.67,0,3);
    glTexCoord2f(1,1);glVertex3f(i+116.67,80,3);
    glTexCoord2f(0,1);glVertex3f(i,80,3);
    glEnd();
    }
    for(float i=3;i>-703;i-=117.14)
    {
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glVertex3f(-1,0,i);
    glTexCoord2f(1,0);glVertex3f(-1,82,i);
    glTexCoord2f(1,1);glVertex3f(-1,82,i-117.14);
    glTexCoord2f(0,1);glVertex3f(-1,0,i-117.14);
    glEnd();
    }
            glPushMatrix();
            glBegin(GL_QUADS);
            glTexCoord2f(0,0);glVertex3f(201,0,3);
            glTexCoord2f(1,0);glVertex3f(201,0,-20);
            glTexCoord2f(1,1);glVertex3f(201,80,-20);
            glTexCoord2f(0,1);glVertex3f(201,80,3);
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(123,0,0);
            glBegin(GL_QUADS);
            glTexCoord2f(0,0);glVertex3f(201,0,3);
            glTexCoord2f(1,0);glVertex3f(201,0,-25);
            glTexCoord2f(1,1);glVertex3f(201,80,-25);
            glTexCoord2f(0,1);glVertex3f(201,80,3);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
    glPopMatrix();


    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    glEnable(GL_TEXTURE_2D);
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(angleCar-150, 0.0, -65.0);

    //car(0, 0, -60);
    glColor4f(0,0,0.4,1);
    myCar();
    glColor4f(1,1,1,1);
    glPopMatrix();


    glPushMatrix(); //Save the current state of transformations
    glTranslatef(angleCar2-150, 0.0, -45.0);

    //car(0, 0, -60);
    myCar();

    glPopMatrix();

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(angleCar3, 5.0, 0.0);
    car(0, 0, 20);
    glPopMatrix();


    glPushMatrix(); //Save the current state of transformations
    glTranslatef(angleCar4, 5.0, 40);

    car(0, 0, 20);

    glPopMatrix();

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(0.0, 5.0, angleCarZ);

    carZ(240, 0, 0);

    glPopMatrix();

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(0.0, 5.0, angleCarZ2);

    carZ(240, 0, 0);

    glPopMatrix();

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(0.0, 5.0, angleCarZ3+130);

    //carZ(160, 0, 0);
    glColor4f(0,0,0,1);
    myCar2();
    glColor4f(1,1,1,1);
    glPopMatrix();

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(40.0, 5.0, angleCarZ4+160);

    //carZ(160, 0, 0);
    glColor4f(0.4,0,0.2,1);
            myCar2();
            glColor4f(1,1,1,1);

    glPopMatrix();



    ////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(80,0,90);
    glRotatef(90,0,1,0);
    TrafficLight(0,0,0,startj,startk);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300,0,-130);
    glRotatef(180,0,1,0);
    TrafficLight(0,0,0,startk,startj);
    glPopMatrix();

    objx=780;objz=-200;
    wallX=1220;wallZ=-1000;

    if(textureGeneral==textureSky)
    glColor4f(0,0,0,1);
    else
        glColor4f(1,1,1,1);
    glRasterPos3f(200,450+20,-600);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'w');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'u');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'p');

     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');



     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'j');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'V');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');

    glRasterPos3f(200,430,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'w');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');

     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');


     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'k');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'H');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'z');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');

     glRasterPos3f(200,410-20,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'R');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'u');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'p');

glRasterPos3f(200,350,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'q');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'R');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'w');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glRasterPos3f(200,310,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');
     glRasterPos3f(200,270,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'g');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'h');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glRasterPos3f(200,230,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'-');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'>');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'R');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'g');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'h');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glRasterPos3f(200,190,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'<');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'-');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'R');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'f');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
    glRasterPos3f(200,150,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'k');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'u');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'p');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'f');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
    glRasterPos3f(200,110,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'k');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'w');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'b');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'k');

     /*glRasterPos3f(200,70,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'j');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'V');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');*/
     /*glRasterPos3f(200,30,-600);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'k');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'H');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'i');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'z');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'t');*/



    glRasterPos3f(750,50,-150);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'p');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'n');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');


     glRasterPos3f(750,30,-150);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'d');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');







    glColor4f(1,1,1,1);
     glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);




    //glPushMatrix();
        ox1=320;oz1=130;
        //glTranslatef(ox1,0,oz1);
        //glutSolidSphere(20,20,20);
        //glPopMatrix();
    //cout<<wx1<<"  "<<wz1<<"  "<<distGate<<"  "<<gate<<endl;
   // cout<<abs(angleCarZ-angleCarZ2)<<endl;
	glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

		switch (key){
		case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 20.0f; break;
		case GLUT_KEY_DOWN :deltaMove = -20.0f; break;

	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0.0f;break;
	}
}
void update(int v){
 angleWheel += 1.0f;
	if (angleWheel > 360) {
		angleWheel -= 360;
	}

    if(stop==1){
        angleCar += 7.0f;
        if (angleCar > 1100) {
            angleCar = -700;
        }
	}else{
        if(angleCar > 100){
            angleCar += 7.0f;
            if (angleCar > 1100) {
                angleCar = -700;
            }
        }
        else{
            if(angleCar < 50){
                if(abs(angleCar-angleCar2)>=100){
                    angleCar += 7.0f;
                }
            }
        }
	}

	if(stop==1){
        //if(angleCar>angleCar2 || angleCar+1100>angleCar2){
            angleCar2 += 5.0f;
            if (angleCar2 > 1100) {
                angleCar2 = -800;
            }
        //}
	}else{
	    //if(angleCar-100>angleCar2 && angleCar<50){
            if(angleCar2 > 100){
                angleCar2 += 5.0f;
                if (angleCar2 > 1100) {
                    angleCar2 = -800;
                }
            }
            else{
                if(angleCar2 < 50){
                    //if(angleCar-100>angleCar2){
                    if(abs(angleCar-angleCar2)>=100){
                    angleCar2 += 5.0f;
                }
            }
        }
	}

	if(stop==1){
        angleCar3 -= 7.0f;
        if (angleCar3 < -700) {
            angleCar3 = 1100;
        }
	}else{
        if(angleCar3 < 300){
            angleCar3 -= 7.0f;
            if (angleCar3 < -700) {
                angleCar3 = 1100;
            }
        }
        else{
            if(angleCar3 > 350){
                if(abs(angleCar3-angleCar4)>=100){
                    angleCar3 -= 7.0f;
                }
            }
        }
	}

	if(stop==1){
        angleCar4 -= 5.0f;
        if (angleCar4 < -700) {
            angleCar4 = 1100;
        }
	}else{
        if(angleCar4 < 300){
            angleCar4 -= 5.0f;
            if (angleCar4 < -700) {
                angleCar4 = 1100;
            }
        }
        else{
            if(angleCar4 > 350){
                if(abs(angleCar3-angleCar4)>=100){
                    angleCar4 -= 5.0f;
                }
            }
        }
	}

	if(stop==0){
        angleCarZ += 5.0f;
        if (angleCarZ > 1100) {
            angleCarZ = -1000;
        }
	}else{
        if(angleCarZ > -100){
            angleCarZ += 5.0f;
            if (angleCarZ > 1100) {
                angleCarZ = -1000;
            }
        }
        else{
            if(angleCarZ < -150){
                if(abs(angleCarZ-angleCarZ2)>=100){
                    angleCarZ += 5.0f;
                }
            }
        }
	}

	if(stop==0){
        angleCarZ2 += 7.0f;
        if (angleCarZ2 > 1100) {
            angleCarZ2 = -1000;
        }
	}else{
        if(angleCarZ2 > -100){
            angleCarZ2 += 7.0f;
            if (angleCarZ2 > 1100) {
                angleCarZ2 = -1000;
            }
        }
        else{
            if(angleCarZ2 < -150){
                if(abs(angleCarZ-angleCarZ2)>=100){
                    angleCarZ2 += 5.0f;
                }
            }
        }
	}

	if(stop==0){
        angleCarZ3 -= 7.0f;
        if (angleCarZ3 < -1000) {
            angleCarZ3 = 1100;
        }
	}else{
        if(angleCarZ3 < 100){
            angleCarZ3 -= 7.0f;
            if (angleCarZ3 < -1000) {
            angleCarZ3 = 1100;
        }
        }
        else{
            if(angleCarZ3 > 150){
                if(abs(angleCarZ3-angleCarZ4)>=100){
                    angleCarZ3 -= 5.0f;
                }
            }
        }
	}

	if(stop==0){
        angleCarZ4 -= 5.0f;
        if (angleCarZ4 < -1000) {
            angleCarZ4 = 1100;
        }
	}else{
        if(angleCarZ4 < 100){
            angleCarZ4 -= 5.0f;
            if (angleCarZ4 < -1000) {
            angleCarZ4 = 1100;
        }
        }
        else{
            if(angleCarZ4 > 150){
                if(abs(angleCarZ3-angleCarZ4)>=100){
                    angleCarZ4 -= 5.0f;
                }
            }
        }
	}

    glutPostRedisplay();
glutTimerFunc(25,update,0);
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 'w':upDown=10.0; break;
      case 's':  upDown=-10.0; break;
      case 'q':Vangle=0.01; break;
      case 'a':Vangle=-0.01; break;
      case 'n':textureGeneral=textureNight;glutPostRedisplay();break;
      case 'd':textureGeneral=textureSky;glutPostRedisplay();break;
      case 'o':if(distGate<80)gate=1;glutPostRedisplay();break;
      case 'c':if(wx1>630||wz1<-740&&distGate<80)gate=0;glutPostRedisplay();break;
      case 'j':
        //shoulder = (shoulder + 5) % 360;
        stop = 0;startj=1;startk=0;
        glutPostRedisplay();
        break;
      case 'k':
        //shoulder = (shoulder - 5) % 360;
        stop = 1;startj=0;startk=1;
        glutPostRedisplay();
        break;

   }
}
void keyboardUp(unsigned char key, int x, int y) {
   switch (key) {
      case 'w':upDown=0.0f; break;
      case 's':upDown=0.0f; break;
      case 'q':Vangle=0.0; break;
      case 'a':Vangle=0.0; break;
   }
}




int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("Traffic Control");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialFunc(pressKey);
    func();
	// here are the new entries

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	//init();
    sndPlaySound("Sound/videoplayback.wav",SND_ASYNC|SND_LOOP);
//    PlaySound(TEXT("Untitled.wav"), NULL, SND_ASYNC)|SND_FILENAME|SND_LOOP);
    glutTimerFunc(5,update,0);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}


