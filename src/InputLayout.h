#pragma once
#include "Bindable.h"
#include <vector>

class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pBlob)
	{
		GetDevice(gfx)->CreateInputLayout(layout.data(), (UINT)layout.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	}

	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
	}

protected:
	ComPtr<ID3D11InputLayout> pInputLayout = nullptr;
};