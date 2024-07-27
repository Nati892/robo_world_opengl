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

	//run frame
	ImGui::Begin("Main settings");
	{
		ImGui::Text("Hello! enjoy this scene!\nPress: E/e to un/lock the mouse curser\n Q/q to exit ");
		if (ImGui::Button("quit"))
		{
			quit_clicked = true;
		}

		if (ImGui::Button("help"))
		{
			help_clicked = true;
		}

		if (ImGui::Button("adjust ambiant light"))
		{
			set_ambiant_light_clicked = true;
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

	//run frame
	ImGui::Begin("Light settings");
	{
		if (this->p_light_data != nullptr)
		{
			ImGui::Text("Please set the following values for the main light source at the center of scene");
			ImGui::SliderFloat3("R|G|B", (float*)&(this->p_light_data->_light_ambient), 0.0, 1.0f);

			if (ImGui::Button("OK!"))
			{
				quit_clicked = true;
			}
		}
		else
			ImGui::Text("Couldnt find the ambiant light object, so this ui is now just a bit different");


	}
	ImGui::End();
}
