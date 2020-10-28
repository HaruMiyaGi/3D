#pragma once
#include "Drawable.h"
#include "BindableBase.h"

#include "Math.h"

class Line : public Drawable<Line>
{
	/// Data for Vertex Buffer

public:
	Line(Graphics& gfx)
	{

		if (!IsInit())
		{
			struct Vertex { float x, y, z; };
			const std::vector<Vertex> vertices =
			{
				{ 0.0f, 0.0f, 1.0f },
				{ 1.0f, 1.0f, 1.0f }
			};

			AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

			const std::vector<unsigned short> indicies = { 0, 1 };

			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indicies));


			struct ConstantBuffer
			{
				DirectX::XMMATRIX transform;
			};
			const ConstantBuffer cb = {
					DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5f, 100.0f))
			};
			AddStaticBind(std::make_unique<VertexConstantBuffer<ConstantBuffer>>(gfx, cb));


			struct ConstantBuffer2
			{
				struct
				{
					float rgba[4];
				} face_color[6];
			};
			const ConstantBuffer2 cb2 = {
				{
					{ 1.0f, 0.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 0.0f, 1.0f },
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					{ 0.0f, 0.0f, 1.0f, 1.0f },
					{ 0.0f, 0.0f, 0.0f, 1.0f }
				}
			};

			AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

			AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

			auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
			auto blob = pvs->GetBlob();
			AddStaticBind(std::move(pvs));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			AddStaticBind(std::make_unique<InputLayout>(gfx, ied, blob));

			AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_LINELIST));
		}

		//AddBind(std::make_unique<TransformCbuf<Line>>(gfx, *this));
	}

	void Update(float dt) override
	{
	}

	DirectX::XMMATRIX GetTransformXM() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	}

private:
};

std::unique_ptr<VertexConstantBuffer<TransformCbuf<Line>::Transforms>> TransformCbuf<Line>::pVcbuf;