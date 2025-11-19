#ifndef __CD3D11Device_H__
#define __CD3D11Device_H__

#include "PlatformDef.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

class CD3D11Device
{
public:
	CD3D11Device();
	~CD3D11Device();

	bool init(HWND hWnd);

	void clear(float r, float g, float b, float a);

	void resize(int width, int height);

	void swapBuffer();

	void release();
private:
	ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pDeviceContext;
    IDXGISwapChain* m_pSwapChain;
    ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11VertexShader* g_pVertexShader;
	ID3D11PixelShader* g_pPixelShader;
};

#endif // !__CD3D11Device_H__
