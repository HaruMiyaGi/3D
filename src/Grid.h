#pragma once
#include "Drawable.h"
#include "BindableBase.h"

#include "Math.h"

class Grid : public Drawable<Grid>
{
	/// Data for Vertex Buffer

public:
	Grid(Graphics& gfx)
	{

		if (!IsInit())
		{
			struct Vertex { float x, y, z; };

			std::vector<Vertex> build;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					float num = 0.1f * (float)i;
					float num_j = 0.1f * (float)j;

					build.push_back({ -1.0f,num_j, num });
					build.push_back({ 1.0f, num_j, num });
					build.push_back({ num, num_j, 1.0f });
					build.push_back({ num, num_j, -1.0f });
				}
			}
			const std::vector<Vertex> vertices = build;

			AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

			//struct ConstantBuffer
			//{
			//	DirectX::XMMATRIX transform;
			//};
			//const ConstantBuffer cb = {
			//		DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5f, 100.0f))
			//};
			//AddStaticBind(std::make_unique<VertexConstantBuffer<ConstantBuffer>>(gfx, cb));


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

		AddBind(std::make_unique<TransformCbuf<Grid>>(gfx, *this));
	}

	void Update(float dt) override {}

	void Update(Vec3 new_pos, float new_pitch, float new_yaw)
	{
		pos.x = new_pos.x;
		pos.y = new_pos.y;
		pos.z = new_pos.z;
		pitch = new_pitch;
		yaw = new_yaw;
	}


	void Gui()
	{
		if (ImGui::Begin("Line", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("Y", &pos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("Z", &pos.z, -10.0f, 10.0f);

			ImGui::SliderAngle("Pitch", &pitch, -90.0f, 90.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		}
		ImGui::End();
	}

	DirectX::XMMATRIX GetTransformXM() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
			DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z) *
			DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, pitch) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	}

private:
	Vec3 pos;
	float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
};

std::unique_ptr<VertexConstantBuffer<TransformCbuf<Grid>::Transforms>> TransformCbuf<Grid>::pVcbuf;