#pragma once
#include "Drawable.h"
#include "BindableBase.h"

#include <cmath>

class Shape2 : public Drawable<Shape2>
{
public:
	Shape2(Graphics& gfx)
	{
		if (!IsInit())
		{
			/// Data for Vertex Buffer
			struct Vertex {
				float x, y, z;
			};
			const std::vector<Vertex> vertices =
			{
				{ -1.0f,  1.0f,  1.0 },
				{  1.0f,  1.0f,  1.0 },
				{  1.0f, -1.0f,  1.0 },
				{ -1.0f, -1.0f,  1.0 },
				{ -1.0f,  1.0f, -1.0 },
				{  1.0f,  1.0f, -1.0 },
				{  1.0f, -1.0f, -1.0 },
				{ -1.0f, -1.0f, -1.0 }
			};

			/// Vertex Buffer
			AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

			/// Data for Index Buffer
			const std::vector<unsigned short> indicies =
			{
				4, 5, 6, 4, 6, 7,
				0, 4, 7, 0, 7, 3,
				5, 1, 2, 5, 2, 6,
				3, 2, 1, 3, 1, 0,
				0, 1, 5, 0, 5, 4,
				7, 6, 2, 7, 2, 3
			};

			/// Index Buffer
			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indicies));


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
			AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

			/// Pixel Shader
			AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

			/// Vertex Shader
			auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
			auto blob = pvs->GetBlob();
			AddStaticBind(std::move(pvs));

			/// Input Layout
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			AddStaticBind(std::make_unique<InputLayout>(gfx, ied, blob));

			/// Topology
			AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}

		AddBind(std::make_unique<TransformCbuf<Shape2>>(gfx, *this));
	}

	void Update(float dt, bool boolean) override
	{
		if (boolean)
		{
			roll += std::sin(dt) * 0.05f;
			pitch += std::sin(dt) * 0.05f;
		}
	}

	DirectX::XMMATRIX GetTransformXM() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, 0.0f) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	}
private:
	float roll = 0.0f;
	float pitch = 0.0f;
};

std::unique_ptr<VertexConstantBuffer<TransformCbuf<Shape2>::Transforms>> TransformCbuf<Shape2>::pVcbuf;