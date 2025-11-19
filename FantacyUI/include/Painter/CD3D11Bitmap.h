#ifndef __CD3D11BITMAP_H__
#define __CD3D11BITMAP_H__

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>


using namespace DirectX;

class CD3D11Bitmap
{ 
public:
	CD3D11Bitmap();
    ~CD3D11Bitmap();

    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
    };

private:
    ID3D11Texture2D* m_pTexture;
};

#endif // !__CD3D11BITMAP_H__
