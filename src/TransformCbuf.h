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
		auto projection = DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f);

		Transforms tt =
		{
			DirectX::XMMatrixTranspose(model * projection)
		};

		pVcbuf->Update(gfx, tt);
		pVcbuf->Bind(gfx);
	}
private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable<T>& parent;
};