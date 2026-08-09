#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <cstdio>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

static int probe(D3D_DRIVER_TYPE type, const wchar_t* label) {
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0};
    ID3D11Device* dev=nullptr; ID3D11DeviceContext* ctx=nullptr; D3D_FEATURE_LEVEL selected{};
    HRESULT hr=D3D11CreateDevice(nullptr,type,nullptr,0,levels,ARRAYSIZE(levels),D3D11_SDK_VERSION,&dev,&selected,&ctx);
    if (FAILED(hr)) { std::wprintf(L"D3D11_%ls_UNAVAILABLE hr=0x%08lx\n",label,(unsigned long)hr); return 1; }
    IDXGIDevice* dxgi=nullptr; IDXGIAdapter* ad=nullptr; DXGI_ADAPTER_DESC desc{};
    hr=dev->QueryInterface(__uuidof(IDXGIDevice),(void**)&dxgi); if(SUCCEEDED(hr)) hr=dxgi->GetAdapter(&ad); if(SUCCEEDED(hr)) hr=ad->GetDesc(&desc);
    if(SUCCEEDED(hr)) std::wprintf(L"D3D11_OK driver=%ls feature=0x%04x adapter=%ls vendor=0x%04x device=0x%04x vram=%llu\n",label,(unsigned)selected,desc.Description,desc.VendorId,desc.DeviceId,(unsigned long long)desc.DedicatedVideoMemory);
    if(ad)ad->Release(); if(dxgi)dxgi->Release(); ctx->Release(); dev->Release(); return SUCCEEDED(hr)?0:2;
}
int wmain(){ if(probe(D3D_DRIVER_TYPE_HARDWARE,L"HARDWARE")==0) return 0; return probe(D3D_DRIVER_TYPE_WARP,L"WARP"); }
