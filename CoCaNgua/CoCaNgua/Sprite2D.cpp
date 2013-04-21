#include "Sprite2D.h"


Sprite2D::Sprite2D(void)
{
}

Sprite2D::Sprite2D( const char* pFilename )
{ 
  loadTexture(pFilename);
}

void Sprite2D::initWithFile( const char* pFilename )
{
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

  if( 0 != texID )
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }

  SOIL_free_image_data(img);
}

void Sprite2D::drawImg()
{
  glPushMatrix();
  glTranslatef(mPos.x-mAnchor.x*size.width, mPos.y-mAnchor.y*size.height, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D,texID);
  glBegin(GL_QUADS); 
  glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.width/2, -size.height/2); 
  glTexCoord2f(1.0f, 0.0f); glVertex2f(size.width/2 , -size.height/2); 
  glTexCoord2f(1.0f, 1.0f); glVertex2f(size.width/2 ,  size.height/2); 
  glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.width/2,  size.height/2);
  glEnd(); 

  glDisable(GL_BLEND);
  glPopMatrix();
}

Rect Sprite2D::boundingBox()
{
  Vector2 midPointRect(mPos.x-mAnchor.x*size.width, mPos.y-mAnchor.y*size.height);
  return Rect(midPointRect.x - size.width/2,
              midPointRect.y - size.height/2,
              midPointRect.x + size.width/2,
              midPointRect.y + size.height/2);
}

Sprite2D::~Sprite2D(void)
{
}
