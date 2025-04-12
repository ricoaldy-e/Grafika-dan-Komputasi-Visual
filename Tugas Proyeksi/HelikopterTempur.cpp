// Nama	: Rico Aldy Kusuma
// NIM	: 24060123120041
// Grafika dan Komputasi Visual E

#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// --------------------------- Variabel Global ---------------------------
static float sudutBadanHeli = 0.0f;    
static float sudutRotorUtama = 0.0f;   
static float sudutRotorEkor = 0.0f;    
static float posisiHeliX = 0.0f;       
static float posisiHeliY = 0.0f;       
static float posisiHeliZ = 0.0f;       
static float sudutSenjata = 0.0f;      
static bool roketDitembakkan = false;  
static float posisiRoketX = 0.0f;      
static float posisiRoketY = 0.0f;
static float posisiRoketZ = 0.0f;
static float kecepatanRoket = 0.5f;    
static float kecepatanHeli = 0.0f;     
static float sudutTerbang = 0.0f;      
static float gravitasi = 0.001f;       
static float dayaAngkat = 0.0f;        

int modeProyeksi = 9;  
int lebarJendela = 800, tinggiJendela = 600;

void gambarBadanHelikopter() {
    GLfloat matMetallic[] = {0.8f, 0.8f, 0.85f, 1.0f};
    GLfloat matShininess[] = {90.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matMetallic);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glPushMatrix();
        // Kokpit
        glColor3f(0.55f, 0.65f, 0.35f);
        glPushMatrix();
            glTranslatef(0.0f, 1.0f, 2.0f);
            glScalef(2.0f, 2.0f, 4.0f);
            glutSolidSphere(0.7, 32, 32);
        glPopMatrix();

        // Kaca kokpit
        GLfloat matGlass[] = {0.5f, 0.7f, 0.9f, 0.7f};
        GLfloat matGlassShine[] = {150.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matGlass);
        glMaterialfv(GL_FRONT, GL_SHININESS, matGlassShine);
        glColor4f(0.5f, 0.7f, 0.9f, 0.7f);
        glPushMatrix();
            glTranslatef(0.0f, 1.5f, 3.0f);
            glRotatef(-20, 1.0f, 0.0f, 0.0f);
            glScalef(1.8f, 1.2f, 2.0f);
            glutSolidSphere(0.5, 32, 32);
        glPopMatrix();

        // Badan belakang
        glColor3f(0.50f, 0.55f, 0.35f);
        glPushMatrix();
            glTranslatef(0.0f, 1.0f, -2.0f);
            glScalef(1.5f, 1.5f, 4.0f);
            glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

void gambarRotorUtama() {
    glPushMatrix();
        glTranslatef(0.0f, 3.0f, 0.0f);
        glRotatef(sudutRotorUtama, 0.0f, 1.0f, 0.0f);
        
        // Hub rotor
        glColor3f(0.7f, 0.7f, 0.75f);
        glutSolidSphere(0.3, 16, 16);

        // Bilah rotor
        glColor3f(0.9f, 0.9f, 0.95f);
        for(int i = 0; i < 4; i++) {
            glPushMatrix();
                glRotatef(i * 90, 0.0f, 1.0f, 0.0f);
                glTranslatef(4.0f, 0.0f, 0.0f);
                glScalef(8.0f, 0.1f, 0.4f);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    glPopMatrix();
}

void gambarRotorEkor() {
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, -6.0f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(sudutRotorEkor, 0.0f, 1.0f, 0.0f);
        
        // Hub rotor ekor
        glColor3f(0.7f, 0.7f, 0.75f);
        glutSolidSphere(0.2, 16, 16);

        // Bilah rotor ekor
        glColor3f(0.9f, 0.9f, 0.95f);
        for(int i = 0; i < 4; i++) {
            glPushMatrix();
                glRotatef(i * 90, 0.0f, 0.0f, 1.0f);
                glTranslatef(1.0f, 0.0f, 0.0f);
                glScalef(2.0f, 0.05f, 0.2f);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    glPopMatrix();
}

void gambarEkorHelikopter() {
    glPushMatrix();
        // Boom ekor
        glColor3f(0.45f, 0.55f, 0.65f);
        glPushMatrix();
            glTranslatef(0.0f, 1.5f, -4.0f);
            glRotatef(-5, 1.0f, 0.0f, 0.0f);
            glScalef(0.5f, 0.5f, 4.0f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Sirip 
        glColor3f(0.5f, 0.6f, 0.7f);
        glPushMatrix();
            glTranslatef(0.0f, 2.5f, -6.0f);
            glScalef(0.1f, 1.5f, 1.0f);
            glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

void gambarKakiPendaratan() {
    glColor3f(0.5f, 0.5f, 0.55f);
    
    // Kaki kiri
    glPushMatrix();
        glPushMatrix();
            glTranslatef(-1.0f, -0.5f, 1.0f);
            glRotatef(20, 0.0f, 0.0f, 1.0f);
            glScalef(0.1f, 2.0f, 0.1f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.0f, -0.5f, -1.0f);
            glRotatef(20, 0.0f, 0.0f, 1.0f);
            glScalef(0.1f, 2.0f, 0.1f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.2f, -1.5f, 0.0f);
            glScalef(0.2f, 0.1f, 3.0f);
            glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();

    // Kaki kanan
    glPushMatrix();
        glPushMatrix();
            glTranslatef(1.0f, -0.5f, 1.0f);
            glRotatef(-20, 0.0f, 0.0f, 1.0f);
            glScalef(0.1f, 2.0f, 0.1f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.0f, -0.5f, -1.0f);
            glRotatef(-20, 0.0f, 0.0f, 1.0f);
            glScalef(0.1f, 2.0f, 0.1f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.2f, -1.5f, 0.0f);
            glScalef(0.2f, 0.1f, 3.0f);
            glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

void gambarSenjata() {
    glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.65f);
        for(int side = -1; side <= 1; side += 2) {
            glPushMatrix();
                glTranslatef(side * 2.0f, 0.0f, 1.0f);
                
                glPushMatrix();
                    glColor3f(0.55f, 0.55f, 0.6f);
                    glScalef(0.3f, 0.3f, 1.0f);
                    glutSolidCube(1.0);
                glPopMatrix();
                
                glPushMatrix();
                    glColor3f(0.65f, 0.65f, 0.7f);
                    glRotatef(sudutSenjata, 1.0f, 0.0f, 0.0f);
                    glTranslatef(0.0f, -0.2f, 0.0f);
                    glScalef(0.2f, 0.2f, 1.5f);
                    glutSolidCube(1.0);
                glPopMatrix();
            glPopMatrix();
        }
    glPopMatrix();
}

void gambarRoket() {
    if (roketDitembakkan) {
        glPushMatrix();
            glTranslatef(posisiRoketX, posisiRoketY, posisiRoketZ);
            glRotatef(sudutSenjata, 0.0f, 1.0f, 0.0f);
            
            // Badan roket
            glColor3f(0.8f, 0.8f, 0.85f);
            glPushMatrix();
                glScalef(0.15f, 0.15f, 0.6f);
                glutSolidCube(1.0);
            glPopMatrix();
            
            // Hidung roket
            glColor3f(0.7f, 0.7f, 0.75f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 0.3f);
                glutSolidCone(0.075, 0.15, 12, 12);
            glPopMatrix();
            
            // Sirip roket
            glColor3f(0.75f, 0.75f, 0.8f);
            for(int i = 0; i < 4; i++) {
                glPushMatrix();
                    glRotatef(i * 90, 0.0f, 0.0f, 1.0f);
                    glTranslatef(0.075f, 0.0f, -0.15f);
                    glScalef(0.15f, 0.02f, 0.15f);
                    glutSolidCube(1.0);
                glPopMatrix();
            }

            // Efek api
            glColor3f(1.0f, 0.3f, 0.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -0.4f);
                glutSolidCone(0.05, 0.2, 8, 8);
            glPopMatrix();
            
            glColor3f(1.0f, 0.9f, 0.0f);
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -0.3f);
                glutSolidCone(0.03, 0.15, 8, 8);
            glPopMatrix();
        glPopMatrix();
    }
}

void gambarDetailTambahan() {
    glColor3f(0.5f, 0.5f, 0.55f);
    glPushMatrix();
        glTranslatef(0.0f, 2.5f, -1.0f);
        glRotatef(-45, 1.0f, 0.0f, 0.0f);
        glScalef(0.08f, 0.08f, 0.7f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 3.0f);
        glColor3f(0.2f, 0.2f, 0.25f);
        glutSolidSphere(0.4, 20, 20);
        
        glColor3f(0.3f, 0.5f, 0.9f);
        glPushMatrix();
            glTranslatef(0.0f, -0.2f, 0.2f);
            glutSolidSphere(0.15, 16, 16);
        glPopMatrix();
    glPopMatrix();
}

void gambarHelikopter() {
    glPushMatrix();
        glTranslatef(posisiHeliX, posisiHeliY, posisiHeliZ);
        glRotatef(sudutBadanHeli, 0.0f, 1.0f, 0.0f);
        glRotatef(sudutTerbang, 0.0f, 0.0f, 1.0f);
        gambarBadanHelikopter();
        gambarRotorUtama();
        gambarEkorHelikopter();
        gambarRotorEkor();
        gambarKakiPendaratan();
        gambarSenjata();
        gambarDetailTambahan();
    glPopMatrix();
    gambarRoket();
}

void aturProyeksi(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspek = (float)w / (float)h;
    if (modeProyeksi <= 6) {
        glOrtho(-15, 15, -15, 15, -50, 50);
    } else {
        gluPerspective(45.0, aspek, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void aturKamera() {
    glLoadIdentity();
    switch (modeProyeksi) {
        case 1: // Tampak atas
            gluLookAt(0.0, 20.0, 0.0,  0.0, 0.0, 0.0,  0.0, 0.0, -1.0);
            break;
        case 2: // Tampak depan
            gluLookAt(0.0, 0.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 3: // Tampak samping
            gluLookAt(20.0, 0.0, 0.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 4: // Isometrik
            gluLookAt(20.0, 20.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 5: // Dimetrik
            gluLookAt(0.0, 20.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 6: // Trimetrik
            gluLookAt(20.0, 10.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 7: // Perspektif 1 titik hilang
            gluLookAt(0.0, 8.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 8: // Perspektif 2 titik hilang
            gluLookAt(20.0, 8.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        case 9: // Perspektif 3 titik hilang
            gluLookAt(20.0, 20.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
        default:
            gluLookAt(0.0, 8.0, 20.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            break;
    }
}

void tampilan() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    aturKamera();
    gambarHelikopter();
    glutSwapBuffers();
}

void ubahUkuran(int w, int h) {
    if (h == 0) h = 1;
    lebarJendela = w;
    tinggiJendela = h;
    glViewport(0, 0, w, h);
    aturProyeksi(w, h);
}

void keyboard(unsigned char tombol, int x, int y) {
    float sudutRadian = sudutBadanHeli * M_PI / 180.0f;
    switch(tombol) {
        case 'w': case 'W': 
            dayaAngkat += 0.001f; 
            if(dayaAngkat > 0.01f) dayaAngkat = 0.01f;
            break;
        case 's': case 'S': 
            dayaAngkat -= 0.001f;
            if(dayaAngkat < -0.01f) dayaAngkat = -0.01f;
            break;
        case 'a': case 'A': 
            sudutBadanHeli += 2.0f; 
            if(kecepatanHeli > 0.01f) sudutTerbang = 15.0f;
            break;
        case 'd': case 'D': 
            sudutBadanHeli -= 2.0f; 
            if(kecepatanHeli > 0.01f) sudutTerbang = -15.0f;
            break;
        case 'q': case 'Q': 
            kecepatanHeli += 0.01f;
            if(kecepatanHeli > 0.5f) kecepatanHeli = 0.5f;
            break;
        case 'e': case 'E': 
            kecepatanHeli -= 0.01f;
            if(kecepatanHeli < -0.5f) kecepatanHeli = -0.5f;
            break;
        case ' ':
            if(!roketDitembakkan) {
                roketDitembakkan = true;
                posisiRoketX = posisiHeliX;
                posisiRoketY = posisiHeliY;
                posisiRoketZ = posisiHeliZ;
                sudutSenjata = sudutBadanHeli;
            }
            break;
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            modeProyeksi = tombol - '0';
            ubahUkuran(lebarJendela, tinggiJendela);
            break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void idle() {
    sudutRotorUtama += 5.0f + (abs(kecepatanHeli) * 100.0f);
    sudutRotorEkor += 15.0f + (abs(kecepatanHeli) * 100.0f);
    if(sudutRotorUtama >= 360.0f) sudutRotorUtama = 0.0f;
    if(sudutRotorEkor >= 360.0f) sudutRotorEkor = 0.0f;

    float sudutRadian = sudutBadanHeli * M_PI / 180.0f;
    posisiHeliX += sin(sudutRadian) * kecepatanHeli;
    posisiHeliZ += cos(sudutRadian) * kecepatanHeli;
    
    posisiHeliY += dayaAngkat;
    
    if(sudutTerbang > 0) sudutTerbang -= 0.5f;
    if(sudutTerbang < 0) sudutTerbang += 0.5f;
    if(abs(sudutTerbang) < 0.5f) sudutTerbang = 0.0f;
    
    kecepatanHeli *= 0.99f;
    dayaAngkat *= 0.99f;
    
    if(roketDitembakkan) {
        float roketRadian = sudutSenjata * M_PI / 180.0f;
        posisiRoketX += sin(roketRadian) * kecepatanRoket;
        posisiRoketZ += cos(roketRadian) * kecepatanRoket;
        
        if(sqrt(pow(posisiRoketX - posisiHeliX, 2) + 
                pow(posisiRoketZ - posisiHeliZ, 2)) > 100.0f) {
            roketDitembakkan = false;
        }
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(lebarJendela, tinggiJendela);
    glutCreateWindow("Helikopter Tempur Call Of Duty 3D");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    
    GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glutDisplayFunc(tampilan);
    glutReshapeFunc(ubahUkuran);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
