#pragma once
#include "Bindable.h"
#include <vector>

#include "Math.h"

class VertexBuffer : public Bindable
{
public:
	template <typename T>
	VertexBuffer(Graphics& gfx, const std::vector<T>& vertices)
		: stride(sizeof(T))
	{
		D3D11_BUFFER_DESC vbd = { 0 };
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.Usage = D3D11_USAGE_DYNAMIC;
		//vbd.CPUAccessFlags = 0;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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

	void Update(Graphics& gfx, Vec2 start, Vec2 end)
	{
		struct Vertex { float x, y, z; };
		const std::vector<Vertex> data =
		{
			{ start.x, start.y, 1.0f },
			{ end.x, end.y, 1.0f }
		};

		UINT size = sizeof(Vertex) * data.size();

		D3D11_MAPPED_SUBRESOURCE resource;
		GetContext(gfx)->Map(pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, data.data(), size);
		GetContext(gfx)->Unmap(pVertexBuffer.Get(), 0);
	}
protected:
	UINT stride;
	ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
};