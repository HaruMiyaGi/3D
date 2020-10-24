#pragma once
#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::wstring& path)
	{
		D3DReadFileToBlob(path.c_str(), &pBlob);
		GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	}

	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0);
	}

	ID3DBlob* GetBlob() const
	{
		return pBlob.Get();
	}

protected:
	ComPtr<ID3DBlob> pBlob = nullptr;
	ComPtr<ID3D11VertexShader> pVertexShader = nullptr;
};