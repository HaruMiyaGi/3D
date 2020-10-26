#pragma once
#include "Drawable.h"
#include "BindableBase.h"

#include "Math.h"

class Line : public Drawable<Line>
{
public:
	Line(Graphics& gfx, Vec2 start, Vec2 end)
	{
		/// Data for Vertex Buffer
		struct Vertex {
			float x, y, z;
		};
		const std::vector<Vertex> vertices =
		{
			{ start.x, start.y, 1.0f },
			{ end.x, end.y, 1.0f }
		};

		/// Vertex Buffer
		AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

		/// Data for Index Buffer
		const std::vector<unsigned short> indicies = { 0, 1 };

		/// Index Buffer
		AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indicies));


		/// Vertex Constant Buffer (TransformCbuf is used instead)


		/// Data for Constant Buffer/s
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

		/// Constant Buffer/s
		AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

		/// Pixel Shader
		AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		/// Vertex Shader
		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto blob = pvs->GetBlob();
		AddBind(std::move(pvs));

		/// Input Layout
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		AddBind(std::make_unique<InputLayout>(gfx, ied, blob));

		/// Topology
		AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_LINELIST));

		AddBind(std::make_unique<TransformCbuf<Line>>(gfx, *this));

		Draw(gfx);
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