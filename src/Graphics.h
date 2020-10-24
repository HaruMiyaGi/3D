#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <memory>
#include "Gui.h"

#include <DirectXMath.h>
//#include <cmath>

#include "Camera.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;

class Graphics
{
public:
	Graphics(HWND hwnd, int width, int height)
	{
		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.BufferDesc.Width = 0;
		scd.BufferDesc.Height = 0;
		scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = 0;

		D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, 0, nullptr, 0,
			D3D11_SDK_VERSION,
			&scd, &pSwapChain, &pDevice, nullptr, &pContext
		);

		// Backbuffer
		ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);

		// Depth
		D3D11_DEPTH_STENCIL_DESC dsd = { 0 };
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		ComPtr<ID3D11DepthStencilState> pDSState = nullptr;
		pDevice->CreateDepthStencilState(&dsd, &pDSState);
		pContext->OMSetDepthStencilState(pDSState.Get(), 1);

		// Depth stensil texture
		ComPtr<ID3D11Texture2D> pDepthStencil = nullptr;
		D3D11_TEXTURE2D_DESC descDepth = { 0 };
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV);

		// Bind for back buffer and depth buffer
		pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), pDSV.Get());

		D3D11_VIEWPORT vp = { 0 };
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		pContext->RSSetViewports(1, &vp);

		gui.Init(hwnd, pDevice.Get(), pContext.Get());
	}
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
public:
	Gui gui;
	Camera camera;
	void StartFrame(float r, float g, float b)
	{
		gui.StartFrame();
		const float color[] = { r, g, b, 1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), color);
		pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
	}
	void EndFrame()
	{
		gui.EndFrame();
		pSwapChain->Present(1, 0);
	}
	void Shape(bool boolean)
	{
		// [x] Data for Vertex Buffer
		// [x] Vertex Buffer
		// [x] Data for Index Buffer
		// [x] Index Buffer
		// [x] Data for Constant Buffer/s
		// [x] Constant Buffer/s
		// [x] Pixel Shader
		// [x] Vertex Shader
		// [x] Input Layout
		// [x] Topology
		// [x] Draw Call


		/// Data for Vertex Buffer
		struct Vertex {
			float x, y, z;
		};

		//const Vertex vertices[] = {
		//	{  0.0f,  0.5f},
		//	{  0.5f, -0.5f},
		//	{ -0.5f, -0.5f}
		//}; // Triangle
		const Vertex vertices[] = {
			{ -1.0f,  1.0f,  1.0 },
			{  1.0f,  1.0f,  1.0 },
			{  1.0f, -1.0f,  1.0 },
			{ -1.0f, -1.0f,  1.0 },
			{ -1.0f,  1.0f, -1.0 },
			{  1.0f,  1.0f, -1.0 },
			{  1.0f, -1.0f, -1.0 },
			{ -1.0f, -1.0f, -1.0 }
		}; // Cube

		/// Vertex Buffer
		ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
		D3D11_BUFFER_DESC vbd = { 0 };
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.ByteWidth = sizeof(vertices);
		vbd.StructureByteStride = sizeof(Vertex);
		D3D11_SUBRESOURCE_DATA vsd = { 0 };
		vsd.pSysMem = vertices;
		pDevice->CreateBuffer(&vbd, &vsd, pVertexBuffer.GetAddressOf());
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		pContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);


		/// Data for Index Buffer
		//const unsigned short indicies[] = {
		//	0, 1, 2
		//}; // Triangle
		const unsigned short indicies[] = {
			4, 5, 6, 4, 6, 7,
			0, 4, 7, 0, 7, 3,
			5, 1, 2, 5, 2, 6,
			3, 2, 1, 3, 1, 0,
			0, 1, 5, 0, 5, 4,
			7, 6, 2, 7, 2, 3
		}; // Cube

		/// Index Buffer
		ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;
		D3D11_BUFFER_DESC ibd = { 0 };
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.ByteWidth = sizeof(indicies);
		ibd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA isd = { 0 };
		isd.pSysMem = indicies;
		pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);
		pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		/// Data for Vertex Constant Buffer
		struct ConstantBuffer
		{
			//float element[4][4];
			DirectX::XMMATRIX transform;
		};

		float distance = camera.GetDistance() + 4.0f;
		float x = camera.GetX(), y = camera.GetY(), z = camera.GetZ();
		if (boolean)
		{
			distance = 4.0f;
			x = 1.0f;
			y = 2.0f;
			z = 0.0f;
		}


		const ConstantBuffer cb = {
			{
				DirectX::XMMatrixTranspose(
					DirectX::XMMatrixRotationX(x) *
					DirectX::XMMatrixRotationY(y) *
					DirectX::XMMatrixRotationZ(z) *
					DirectX::XMMatrixTranslation(0.0f, 0.0f, distance) *
					DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 100.0f)
				)
				/*1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f*/
			}
		};

		/// Vertex Constant Buffer
		ComPtr<ID3D11Buffer> pConstantBuffer = nullptr;
		D3D11_BUFFER_DESC cbd = { 0 };
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.ByteWidth = sizeof(cb);
		cbd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA csd = { 0 };
		csd.pSysMem = &cb;
		pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);
		pContext->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());



		/// Data for Pixel Constant Buffer
		struct ConstantBuffer2
		{
			struct
			{
				float rgba[4];
			} face_color[6];
		};
		const ConstantBuffer2 cb2 = {
			{
				{ 1.0f, 0.0f, 0.0f, 1.0f },
				{ 1.0f, 0.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f, 1.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			}
		};

		/// Pixel Constant Buffer
		ComPtr<ID3D11Buffer> pConstantBuffer2 = nullptr;
		D3D11_BUFFER_DESC cbd2 = { 0 };
		cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd2.Usage = D3D11_USAGE_DYNAMIC;
		cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd2.MiscFlags = 0;
		cbd2.ByteWidth = sizeof(cb2);
		cbd2.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA csd2 = { 0 };
		csd2.pSysMem = &cb2;
		pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);
		pContext->PSSetConstantBuffers(0, 1, pConstantBuffer2.GetAddressOf());



		/// Pixel Shader
		ComPtr<ID3D11PixelShader> pPixelShader = nullptr;
		ComPtr<ID3DBlob> pBlob = nullptr;
		D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
		pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
		pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);


		/// Vertex Shader
		ComPtr<ID3D11VertexShader> pVertexShader = nullptr;
		//ComPtr<ID3DBlob> pBlob = nullptr;
		D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
		pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);


		/// Input Layout
		ComPtr<ID3D11InputLayout> pInputLayout = nullptr;
		const D3D11_INPUT_ELEMENT_DESC ied[]{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }			
		};
		pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
		pContext->IASetInputLayout(pInputLayout.Get());

		
		/// Topology
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		/// Draw Call
		pContext->DrawIndexed((UINT)std::size(indicies), 0, 0);
	}
private:
	ComPtr<ID3D11Device> pDevice = nullptr;
	ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	ComPtr<ID3D11DeviceContext> pContext = nullptr;
	ComPtr<ID3D11RenderTargetView> pTarget = nullptr;
	ComPtr<ID3D11DepthStencilView> pDSV = nullptr;
};