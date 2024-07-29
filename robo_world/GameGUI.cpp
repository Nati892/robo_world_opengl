#include "GameGUI.h"
#include"Scene.h"

void GOGuiWindow::CleanUp()
{
	//empty, to be derived
}

void GOGuiWindow::ShowGUI(Scene* current_scene)
{
	//empty, to be derived
}




void MainGuiWinodw::ShowGUI(Scene* CurrentScene)
{
	//check what happend last frame
	if (quit_clicked)
	{

		this->quit_clicked = false;
		exit(0);//Exit app, bye bye, thanks for playing!
	}

	if (help_clicked)
	{
		CurrentScene->AddGuiWindow(new HelpGuiWindow());
		this->help_clicked = false;
	}

	if (set_ambiant_light_clicked)
	{
		CurrentScene->AddGuiWindow(new LightSettingsGuiWindow());
		this->set_ambiant_light_clicked = false;
		return;
	}
	if (robot_arm_controls_clicked)
	{
		robot_arm_controls_clicked = false;
		CurrentScene->AddGuiWindow(new ArmControlSettingsGuiWindow());
		return;
	}
	ImGui::SetNextWindowSize( ImVec2(300, 180),ImGuiCond_Always);
	//run frame
	ImGui::Begin("Main settings");
	{
		ImGui::Text("Hello! enjoy this scene!\nPress: E/e to un/lock the mouse curser\n Q/q to exit ");
		if (ImGui::Button("Quit"))
		{
			quit_clicked = true;
		}

		if (ImGui::Button("Help"))
		{
			help_clicked = true;
		}

		if (ImGui::Button("Adjust ambiant light"))
		{
			set_ambiant_light_clicked = true;
		}
		if (ImGui::Button("control robot arm rotation"))
		{
			robot_arm_controls_clicked = true;
		}
	}
	ImGui::End();                          // Buttons return true when clicked (most widgets return true when edited/activated)

}

void MainGuiWinodw::CleanUp()
{
}



void HelpGuiWindow::ShowGUI(Scene* current_scene)
{
	//check what happend last frame
	if (quit_clicked)
	{
		current_scene->RemoveGuiWindow(this);
		this->quit_clicked = false;
		return;
	}

	//run frame
	ImGui::Begin("Help");
	{
		ImGui::Text("Controls:\n v/V to move from robot view, to third person view to free view.\n e/E to lock/unlock mouse curser\n q/Q to quit"
		);
		if (ImGui::Button("OK!"))
		{
			quit_clicked = true;
		}

	}
	ImGui::End();

}

void HelpGuiWindow::CleanUp()
{
}

void LightSettingsGuiWindow::CleanUp()
{
}

void LightSettingsGuiWindow::ShowGUI(Scene* current_scene)
{
	if (!this->light_source_searched)
	{
		this->light_source_searched = true;
		if (current_scene != nullptr)
		{
			auto light_source_obj = current_scene->FindObjectByName("main_ambiant_light");
			if (light_source_obj != nullptr && light_source_obj->IsLightSource() && light_source_obj->GetLightSourceData() != nullptr)
			{
				this->p_light_data = light_source_obj->GetLightSourceData();
				this->original_light_data = p_light_data->_light_ambient;
			}
			else
			{
				std::cout << "LightSettingsGuiWindow: error finding light in scene" << std::endl;
			}
		}
	}

	//check what happend last frame
	if (quit_clicked)
	{
		current_scene->RemoveGuiWindow(this);
		this->quit_clicked = false;
		return;
	}

	if (reset_light_clicked)
	{
		this->p_light_data->_light_ambient = original_light_data;
		this->quit_clicked = false;
	}

	//run frame
	ImGui::Begin("Light settings");
	{
		if (this->p_light_data != nullptr)
		{
			ImGui::Text("Please set the following values for the main light source at the center of scene");
			ImGui::SliderFloat3("R|G|B", (float*)&(this->p_light_data->_light_ambient), 0.0, 1.0f);

			reset_light_clicked = ImGui::Button("reset light");
			quit_clicked = ImGui::Button("OK!");
		}
		else
			ImGui::Text("Couldnt find the ambiant light object, so this ui is now just a bit different");


	}
	ImGui::End();
}

void ArmControlSettingsGuiWindow::CleanUp()
{
}

void ArmControlSettingsGuiWindow::ShowGUI(Scene* current_scene)
{

	if (!this->ObjectsSearched)
	{
		this->ObjectsSearched = true;
		if (current_scene != nullptr)
		{
			auto robo_arm_obj = current_scene->FindObjectByName("robo_arm");
			auto robo_forarm_obj = current_scene->FindObjectByName("robo_forarm");
			auto robo_hand_obj = current_scene->FindObjectByName("robo_hand");
			if (robo_arm_obj != nullptr && robo_forarm_obj != nullptr && robo_hand_obj != nullptr)
			{
				this->ArmTrans = robo_arm_obj->GetTransform();
				this->ForarmTrans = robo_forarm_obj->GetTransform();
				this->HandTrans = robo_hand_obj->GetTransform();

				this->ArmRotation = ArmTrans->GetRotation();
				this->ForarmRotation = ForarmTrans->GetRotation();
				this->ArmRotation = HandTrans->GetRotation();
			}
			else
			{
				std::cout << "ArmControlSettingsGuiWindow: error finding arm parts in scene" << std::endl;
			}
		}
	}

	if (quit_clicked)
	{
		current_scene->RemoveGuiWindow(this);
		this->quit_clicked = false;
		return;
	}

	ImGui::Begin("robot arm control");
	{
		if (this->ArmTrans != nullptr && this->ForarmTrans != nullptr && this->HandTrans != nullptr)
		{
			ImGui::Text("Arm rotation");
			ImGui::SliderFloat3("X|Y|Z arm", (float*)&(ArmRotation), 0.0, 360.0f);

			ImGui::Text("Forarm rotation");
			ImGui::SliderFloat3("X|Y|Z forarm", (float*)&(ForarmRotation), 0.0, 360.0f);

			ImGui::Text("Hand rotation");
			ImGui::SliderFloat3("X|Y|Z hand", (float*)&(HandRotation), 0.0, 360.0f);

			quit_clicked = ImGui::Button("OK!");
		}
		else
		{
			ImGui::Text("Couldnt find the ambiant light object, so this ui is now just a bit different");
		}
	}
	ImGui::End();

	ArmTrans->setRotation(this->ArmRotation);
	ForarmTrans->setRotation(this->ForarmRotation);
	HandTrans->setRotation(this->HandRotation);

}
