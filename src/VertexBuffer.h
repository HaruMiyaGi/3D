#pragma once
#include "Bindable.h"
#include <vector>

class VertexBuffer : public Bindable
{
public:
	template <typename T>
	VertexBuffer(Graphics& gfx, const std::vector<T>& vertices)
		: stride(sizeof(T))
	{
		D3D11_BUFFER_DESC vbd = { 0 };
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.ByteWidth = UINT(sizeof(T) * vertices.size());
		vbd.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA vsd = { 0 };
		vsd.pSysMem = vertices.data();
		GetDevice(gfx)->CreateBuffer(&vbd, &vsd, pVertexBuffer.GetAddressOf());
	}

	void Bind(Graphics& gfx) override
	{
		const UINT offset = 0;
		GetContext(gfx)->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	}

protected:
	UINT stride;
	ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
};