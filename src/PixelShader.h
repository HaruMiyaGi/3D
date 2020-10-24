#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::wstring& path)
	{
		ComPtr<ID3DBlob> pBlob = nullptr;
		D3DReadFileToBlob(path.c_str(), &pBlob);
		GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	}

	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0);
	}

protected:
	ComPtr<ID3D11PixelShader> pPixelShader = nullptr;
};