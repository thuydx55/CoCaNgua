#include "Sprite2D.h"


Sprite2D::Sprite2D(void)
{
  width = height = 0;
  mAnchor.x = mAnchor.y = 0.5;
}

Sprite2D::Sprite2D( const char* pFilename )
{
  width = height = 0;
  mAnchor.x = mAnchor.y = 0.5;
  loadTexture(pFilename);
}

void Sprite2D::initWithFile( const char* pFilename )
{
  loadTexture(pFilename);
}

void Sprite2D::loadTexture(const char *pszFilename)
{
  unsigned char* img = SOIL_load_image(pszFilename, &width, &height, &channel, SOIL_LOAD_RGBA);

  cout << width << ' ' << height << endl;

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
  Vector2 botLeft (mPos.x-mAnchor.x*width, mPos.y-mAnchor.y*height);
  Vector2 botRight(mPos.x+(1-mAnchor.x)*width, mPos.y-mAnchor.y*height);
  Vector2 topLeft (mPos.x-mAnchor.x*width, mPos.y+(1-mAnchor.y)*height);
  Vector2 topRight(mPos.x+(1-mAnchor.x)*width, mPos.y+(1-mAnchor.y)*height);

  //cout << botLeft.toString() << botRight.toString() << topLeft.toString() << topRight.toString();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D,texID);
  glBegin(GL_QUADS); 
  glTexCoord2f(0.0f, 0.0f); glVertex2f(botLeft.x,  botLeft.y ); 
  glTexCoord2f(1.0f, 0.0f); glVertex2f(botRight.x, botRight.y); 
  glTexCoord2f(1.0f, 1.0f); glVertex2f(topRight.x, topRight.y); 
  glTexCoord2f(0.0f, 1.0f); glVertex2f(topLeft.x,  topLeft.y );
  glEnd(); 

  glDisable(GL_BLEND);
}

Sprite2D::~Sprite2D(void)
{
}
