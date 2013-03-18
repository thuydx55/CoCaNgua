#include "Model.h"


Model::Model(void)
{
}

void Model::DrawModelUsingFixedFuncPipeline()
{
  const ModelOBJ::Mesh *pMesh = 0;
  const ModelOBJ::Material *pMaterial = 0;
  const ModelOBJ::Vertex *pVertices = 0;
  //ModelTextures::const_iterator iter;

  for (int i = 0; i < getNumberOfMeshes(); ++i)
  {
    pMesh = &getMesh(i);
    pMaterial = pMesh->pMaterial;
    pVertices = getVertexBuffer();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

    /*if (g_enableTextures)
    {
    iter = g_modelTextures.find(pMaterial->colorMapFilename);

    if (iter == g_modelTextures.end())
    {
    glDisable(GL_TEXTURE_2D);
    }
    else
    {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, iter->second);
    }
    }
    else*/
    {
      glDisable(GL_TEXTURE_2D);
    }

    if (hasPositions())
    {
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, getVertexSize(),
        getVertexBuffer()->position);
    }

    if (hasTextureCoords())
    {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, getVertexSize(),
        getVertexBuffer()->texCoord);
    }

    if (hasNormals())
    {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT, getVertexSize(),
        getVertexBuffer()->normal);
    }

    glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
      getIndexBuffer() + pMesh->startIndex);

    if (hasNormals())
      glDisableClientState(GL_NORMAL_ARRAY);

    if (hasTextureCoords())
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    if (hasPositions())
      glDisableClientState(GL_VERTEX_ARRAY);
  }

  glPopMatrix();
}

void Model::drawModel()
{
  float x, y, z;
  getCenter(x, y, z);
  glTranslatef(-x, -y, -z);

  glPushMatrix();

  glTranslated(mPos.x, mPos.y, mPos.z);

  DrawModelUsingFixedFuncPipeline();

  glPopMatrix();
}

Model::~Model(void)
{
}
