#include "Sprite2D.h"


Sprite2D::Sprite2D(void)
{
}

Sprite2D::Sprite2D( const char* pFilename )
{ 
  loadTexture(pFilename);
}

Sprite2D* Sprite2D::create()
{
  Sprite2D* temp = new Sprite2D();
  return temp;
}

Sprite2D* Sprite2D::create( const char* pFilename )
{
  Sprite2D* temp = new Sprite2D(pFilename);
  return temp;
}


void Sprite2D::initWithFile( const char* pFilename )
{
  mOpacity = 255;
  mAnchor.x = mAnchor.y = 0.5;
  loadTexture(pFilename);
}

void Sprite2D::loadTexture(const char *pszFilename)
{
  int width, height;
  unsigned char* img = SOIL_load_image(pszFilename, &width, &height, &channel, SOIL_LOAD_RGBA);

  size.width = width;
  size.height = height;

  texID = SOIL_load_OGL_texture(
    pszFilename,
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  //cout << pszFilename << ' ' << texID << endl;
  if( 0 != texID )
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }

  SOIL_free_image_data(img);
}

void Sprite2D::drawImg( Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4 )
{
  glPushMatrix();
  glTranslatef(mPos.x-mAnchor.x*size.width, mPos.y-mAnchor.y*size.height, 0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D,texID);
  glBegin(GL_QUADS); 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x, v1.y, v1.z); 
  glTexCoord2f(1.0f, 0.0f); glVertex3f(v2.x, v2.y, v2.z); 
  glTexCoord2f(1.0f, 1.0f); glVertex3f(v3.x, v3.y, v3.z); 
  glTexCoord2f(0.0f, 1.0f); glVertex3f(v4.x, v4.y, v4.z);
  glEnd(); 

  glDisable(GL_BLEND);
  glPopMatrix();
}

void Sprite2D::drawImg()
{
  drawImg(Vector3(-size.width/2, -size.height/2, 0),
          Vector3( size.width/2, -size.height/2, 0),
          Vector3( size.width/2,  size.height/2, 0),
          Vector3(-size.width/2,  size.height/2, 0));  
}

Rect Sprite2D::boundingBox()
{
  Vector2 midPointRect(mPos.x-mAnchor.x*size.width, mPos.y-mAnchor.y*size.height);
  return Rect(midPointRect.x - size.width/2,
              midPointRect.y - size.height/2,
              size.width,
              size.height);
}

Sprite2D::~Sprite2D(void)
{
  glDeleteTextures( 1, &texID );
}
