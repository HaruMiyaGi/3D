#pragma once
#include "Drawable.h"
#include "BindableBase.h"

#include <string>

class Shape : public Drawable<Shape>
{
public:
	Shape(Graphics& gfx, std::string name, std::vector<float> rng)
		: name(name),
		roll(0.0f), pitch(0.0f), yaw(0.0f),
		theta(rng[0]), phi(rng[1]), chi(rng[2]),
		droll(rng[3]), dpitch(rng[4]), dyaw(rng[5]),
		dtheta(rng[6]), dphi(rng[7]), dchi(rng[8]),
		r(rng[9])
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

		AddBind(std::make_unique<TransformCbuf<Shape>>(gfx, *this));
	}

	void Update(float dt) override
	{
		roll += droll * dt;
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		theta += dtheta * dt;
		phi += dphi * dt;
		chi += dchi * dt;
	}

	DirectX::XMMATRIX GetTransformXM() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, pitch) *
			DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 15.0f);
	}

	void Gui(Graphics& gfx)
	{
		auto model = GetTransformXM();
		if (ImGui::Begin("Model Matrix", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", model.r->m128_f32[0], model.r->m128_f32[1], model.r->m128_f32[2], model.r->m128_f32[3]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", model.r->m128_f32[4], model.r->m128_f32[5], model.r->m128_f32[6], model.r->m128_f32[7]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", model.r->m128_f32[8], model.r->m128_f32[9], model.r->m128_f32[10], model.r->m128_f32[11]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", model.r->m128_f32[12], model.r->m128_f32[13], model.r->m128_f32[14], model.r->m128_f32[15]);
		}
		ImGui::End();

		auto camera = gfx.camera.GetMatrix();
		if (ImGui::Begin("Camera Matrix", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", camera.r->m128_f32[0], camera.r->m128_f32[1], camera.r->m128_f32[2], camera.r->m128_f32[3]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", camera.r->m128_f32[4], camera.r->m128_f32[5], camera.r->m128_f32[6], camera.r->m128_f32[7]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", camera.r->m128_f32[8], camera.r->m128_f32[9], camera.r->m128_f32[10], camera.r->m128_f32[11]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", camera.r->m128_f32[12], camera.r->m128_f32[13], camera.r->m128_f32[14], camera.r->m128_f32[15]);
		}
		ImGui::End();

		auto projection = gfx.GetProjection();
		if (ImGui::Begin("Projection Matrix", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", projection.r->m128_f32[0], projection.r->m128_f32[1], projection.r->m128_f32[2], projection.r->m128_f32[3]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", projection.r->m128_f32[4], projection.r->m128_f32[5], projection.r->m128_f32[6], projection.r->m128_f32[7]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", projection.r->m128_f32[8], projection.r->m128_f32[9], projection.r->m128_f32[10], projection.r->m128_f32[11]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", projection.r->m128_f32[12], projection.r->m128_f32[13], projection.r->m128_f32[14], projection.r->m128_f32[15]);
		}
		ImGui::End();

		auto mcp = DirectX::XMMatrixTranspose(model * camera * projection);
		if (ImGui::Begin("MCP Matrix", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", mcp.r->m128_f32[0], mcp.r->m128_f32[1], mcp.r->m128_f32[2], mcp.r->m128_f32[3]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", mcp.r->m128_f32[4], mcp.r->m128_f32[5], mcp.r->m128_f32[6], mcp.r->m128_f32[7]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", mcp.r->m128_f32[8], mcp.r->m128_f32[9], mcp.r->m128_f32[10], mcp.r->m128_f32[11]);
			ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]", mcp.r->m128_f32[12], mcp.r->m128_f32[13], mcp.r->m128_f32[14], mcp.r->m128_f32[15]);
		}
		ImGui::End();

	}

	const char* GetName()
	{
		return name.c_str();
	}

private:
	// Position
	float r;
	float roll, pitch, yaw;
	float theta, phi, chi;
	// Speed
	float droll, dpitch, dyaw;
	float dtheta, dphi, dchi;
	std::string name;
};

std::unique_ptr<VertexConstantBuffer<TransformCbuf<Shape>::Transforms>> TransformCbuf<Shape>::pVcbuf;