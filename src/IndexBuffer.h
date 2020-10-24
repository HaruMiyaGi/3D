#pragma once
#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indicies)
		: count((UINT)indicies.size())
	{
		D3D11_BUFFER_DESC ibd = { 0 };
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.ByteWidth = UINT(count * sizeof(unsigned short));
		ibd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA isd = { 0 };
		isd.pSysMem = indicies.data();
		GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	}

	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	UINT GetCount() const
	{
		return count;
	}

protected:
	ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;
	UINT count;
};