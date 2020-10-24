#pragma once
#include "Graphics.h"

class Camera
{
public:
	Camera()
	{
		Reset();
	}

	void Gui()
	{
		if (ImGui::Begin("Camera"))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &x, -4.0f, 4.0f, "%.1f");
			ImGui::SliderFloat("Y", &y, -4.0f, 4.0f, "%.1f");
			ImGui::SliderFloat("Z", &z, -4.0f, 4.0f, "%.1f");
			ImGui::SliderFloat("Distance", &distance, -10.0f, 10.0f, "%.1f");

			ImGui::Text("Orientation");
			ImGui::SliderAngle("Pitch", &pitch, -90.0f, 90.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);

			if (ImGui::Button("Reset"))
				Reset();

		}
		ImGui::End();
	}

	void Reset()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		distance = 0.0f;
		pitch = 0.0f;
		yaw = 0.0f;
	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetDistance() { return distance; }

private:
	float x, y, z;
	float distance;
	float pitch;
	float yaw;
	static constexpr float travel_speed = 60.0f;
	static constexpr float rotation_speed = 0.001f;
};