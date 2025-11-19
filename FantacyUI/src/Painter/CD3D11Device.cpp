#include "Painter/CD3D11Device.h"


// D3D11最新教程
// https://www.rastertek.com/tutdx11win10.html
// 
// 
// 顶点着色器代码
const char* g_vsCode = R"(
struct VS_INPUT {
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PS_INPUT {
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

PS_INPUT main(VS_INPUT input) {
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0f);
    output.tex = input.tex;
    return output;
}
)";

// 像素着色器代码
const char* g_psCode = R"(
Texture2D tex : register(t0);
SamplerState sam : register(s0);

struct PS_INPUT {
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 main(PS_INPUT input) : SV_Target {
    return tex.Sample(sam, input.tex);
}
)";


CD3D11Device::CD3D11Device()
{
}

CD3D11Device::~CD3D11Device()
{
}

bool CD3D11Device::init(HWND hWnd)
{
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
	// 创建设备和交换链
	DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);
    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        featureLevels,
        numFeatureLevels,
        D3D11_SDK_VERSION,
        &sd,
        &m_pSwapChain,
        &m_pDevice,
        nullptr,
        &m_pDeviceContext
    );
    if (FAILED(hr))
    {
        return false;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        return false;
    }

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    // 设置视口
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pDeviceContext->RSSetViewports(1, &vp);
    // 编译着色器
    ID3DBlob* pVSBlob = nullptr;
    hr = D3DCompile(g_vsCode, strlen(g_vsCode), nullptr, nullptr, nullptr, "main", "vs_4_0", 0, 0, &pVSBlob, nullptr);
    if (FAILED(hr))
    {
        return false;
    }
    hr = m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    if (FAILED(hr)) {
        pVSBlob->Release();
        return false;
    }
    ID3DBlob* pPSBlob = nullptr;
    hr = D3DCompile(g_psCode, strlen(g_psCode), nullptr, nullptr, nullptr, "main", "ps_4_0", 0, 0, &pPSBlob, nullptr);
    if (FAILED(hr)) {
        pVSBlob->Release();
        return false;
    }
    hr = m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
    if (FAILED(hr)) {
        pVSBlob->Release();
        pPSBlob->Release();
        return false;
    }
	return true;
}

void CD3D11Device::clear(float r, float g, float b, float a)
{
    float ClearColor[4] = { r, g, b, a };
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
}

void CD3D11Device::resize(int width, int height)
{
    m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
}

void CD3D11Device::swapBuffer()
{
    m_pSwapChain->Present(0, 0);
}

void CD3D11Device::release()
{
    m_pDevice->Release();
    m_pDeviceContext->Release();
    m_pSwapChain->Release();
    m_pRenderTargetView->Release();
    g_pVertexShader->Release();
    g_pPixelShader->Release();
}
