#pragma once
#include "Graphics.h"
#include "Math.h"

class Camera
{
public:
	Camera()
	{
		Reset();
	}

	void Rotate(float delta_x, float delta_y)
	{
		yaw = wrap_angle<float>(yaw + delta_x * rotation_speed);
		pitch = std::clamp<float>(pitch + delta_y * rotation_speed, -PI / 2.0f, PI / 2.0f);
	}

	void Move(DirectX::XMFLOAT3 translation)
	{
		using namespace DirectX;

		XMStoreFloat3(&translation,
			XMVector3Transform(
				XMLoadFloat3(&translation),
				XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
				XMMatrixScaling(travel_speed, travel_speed, travel_speed)
			));

		pos = {
			pos.x + translation.x,
			pos.y + translation.y,
			pos.z + translation.z
		};
	}

	DirectX::XMMATRIX GetMatrix() const
	{
		using namespace DirectX;
		
		const XMVECTOR forward_base = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		
		const auto cam_position = XMLoadFloat3(&pos);
		const auto look_vector = XMVector3Transform(forward_base, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		const auto cam_target = cam_position + look_vector;
		
		return XMMatrixLookAtLH(cam_position, cam_target, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	}

	void Gui()
	{
		if (ImGui::Begin("Camera", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &pos.x, -4.0f, 4.0f, "%.1f");
			ImGui::SliderFloat("Y", &pos.y, -4.0f, 4.0f, "%.1f");
			ImGui::SliderFloat("Z", &pos.z, -4.0f, 4.0f, "%.1f");

			ImGui::Text("Orientation");
			ImGui::SliderAngle("Pitch", &pitch, -90.0f, 90.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
			ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);

			if (ImGui::Button("Reset"))
				Reset();
		}
		ImGui::End();
	}

	void Reset()
	{
		pos = { 0.0f, 0.0f, 0.0f };
		pitch = 0.0f;
		yaw = 0.0f;
		roll = 0.0f;
	}

private:
	DirectX::XMFLOAT3 pos;
	float pitch, yaw, roll;
	static constexpr float travel_speed = 60.0f;
	static constexpr float rotation_speed = 0.001f;
};