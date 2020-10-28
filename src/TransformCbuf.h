#pragma once
#include "ConstantBuffer.h"
#include "Drawable.h"

template <typename T>
class TransformCbuf : public Bindable
{
	struct Transforms
	{
		DirectX::XMMATRIX model;
	};
public:
	TransformCbuf(Graphics& gfx, const Drawable<T>& parent)
		: parent(parent)
	{
		if (!pVcbuf)
			pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx);
	}

	void Bind(Graphics& gfx) noexcept override
	{
		auto model = parent.GetTransformXM();
		auto projection = gfx.GetProjection();
		auto camera = gfx.camera.GetMatrix();

		Transforms transform =
		{
			DirectX::XMMatrixTranspose(model * camera * projection)
		};

		pVcbuf->Update(gfx, transform);
		pVcbuf->Bind(gfx);
	}
private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable<T>& parent;
};